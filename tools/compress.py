#!/usr/bin/env python3

"""
Script for recompressing a decompressed baserom file

Original yoinked from:
https://github.com/Fluvian/mnsg/blob/main/tools/decompress.py

Modified from original contents to use @LiquidCat64's rework of @Fluvian's LZKN64 compression
"""

import sys
from typing import Optional

from liblzkn64 import (
    MAX_LZKN64_FILE_SIZE,
    MAX_ROM_SIZE,
    NISITENMA_ICHIGO_HEADER,
    compress_buffer,
    find_nisitenma_ichigo_offset,
)

# Address of the first file in the overlay table.
first_file_addr = None

# Sizes of all the decompressed files combined.
raw_size = None

# Sizes of all the compressed files combined plus the ROM's main buffer size.
new_raw_size = None

# List of files to skip.
skip_files = []

# List of all addresses for the files.
file_addrs = []

# List of all file sizes for the files.
file_sizes = []


def copy_buffer(input, output: bytearray) -> bytearray:
    output[0 : len(input)] = input

    return output


def copy_buffer_from_pos_with_len(
    input: bytearray, output: bytearray, pos: int, len: int
) -> bytearray:
    output[0:len] = input[pos : pos + len]

    return output


def copy_buffer_to_pos_with_len(
    input: bytearray, output: bytearray, pos: int, len: int
) -> bytearray:
    output[pos : pos + len] = input[0:len]

    return output


def zero_out_buffer_from_pos_with_len(
    output: bytearray, pos: int, len: int
) -> bytearray:
    for i in range(len):
        output[i + pos] = 0

    return output


def get_decompressed_file_addresses_and_sizes(input, table_addr: int):
    pos = 0
    file_addr = int.from_bytes(
        input[table_addr + pos + 1 : table_addr + pos + 4], byteorder="big"
    )
    next_file_addr = int.from_bytes(
        input[table_addr + pos + 5 : table_addr + pos + 8], byteorder="big"
    )

    global first_file_addr
    first_file_addr = file_addr

    while file_addr != 0:
        file_addrs.append(file_addr)

        # Highest bit of address is set, file is already compressed.
        if input[table_addr + pos] == 0:
            skip_files.append(0)

            if (next_file_addr - file_addr) > 0:
                file_sizes.append(next_file_addr - file_addr)
            else:
                file_sizes.append(0)
        else:
            skip_files.append(1)

            # Headers of compressed files have their compressed sizes within them.
            file_sizes.append(
                int.from_bytes(input[file_addr + 1 : file_addr + 4], byteorder="big")
            )

        pos += 4

        file_addr = int.from_bytes(
            input[table_addr + pos + 1 : table_addr + pos + 4], byteorder="big"
        )
        next_file_addr = int.from_bytes(
            input[table_addr + pos + 5 : table_addr + pos + 8], byteorder="big"
        )


def get_raw_file_sizes(input):
    # Max file size for a LZKN64 file.
    decompressed_buf = bytearray(MAX_LZKN64_FILE_SIZE)

    for i in range(len(file_sizes)):
        copy_buffer_from_pos_with_len(
            input, decompressed_buf, file_addrs[i], file_sizes[i]
        )


def get_raw_file_addresses():
    pos = first_file_addr

    for i in range(len(file_addrs)):
        pos += file_sizes[i]

    global raw_size
    raw_size = pos - first_file_addr


def write_raw_files(input, buffer, table_addr):
    # Max file size for a compressed LZKN64 file.
    file_buf = bytearray(MAX_LZKN64_FILE_SIZE)
    pos = first_file_addr

    print("New file addresses:")
    for i in range(0, len(file_addrs), 2):
        copy_buffer_from_pos_with_len(input, file_buf, file_addrs[i], file_sizes[i])

        if skip_files[i] != 1:
            file_buf = bytearray(compress_buffer(file_buf[0 : file_sizes[i]]))

        copy_buffer_to_pos_with_len(file_buf, buffer, pos, len(file_buf))

        # Write the new locations to the overlay table.
        buffer[table_addr + (i * 4) : table_addr + (i * 4) + 4] = (
            0x80000000 + pos
        ).to_bytes(4, "big")
        buffer[table_addr + (i * 4) + 4 : table_addr + (i * 4) + 8] = (
            len(file_buf) + pos
        ).to_bytes(4, "big")

        # Only log unique file addresses
        if i > 0 and (pos - last_pos) > 0:
            print(f"{hex(pos)}")

        last_pos = pos
        pos += len(file_buf)

    global new_raw_size
    new_raw_size = pos


# Find the nearest power of two for the final ROM size.
# (https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2)


def get_new_file_size(size):
    new_size = 0x400000  # Smallest size of an N64 cartridge
    while new_size < size:
        new_size += 0x400000

    return new_size


def compress(input: bytearray, table_addr: int) -> bytearray:
    buffer = bytearray(MAX_ROM_SIZE)  # 512Mbit (64Mbyte) is the maximum ROM size.
    buffer = copy_buffer(input, buffer)

    # List all the file addresses and sizes in a table.
    get_decompressed_file_addresses_and_sizes(input, table_addr)

    # Get the decompressed file sizes.
    get_raw_file_sizes(input)

    # Get the decompressed file addresses.
    get_raw_file_addresses()

    buffer = zero_out_buffer_from_pos_with_len(buffer, first_file_addr, raw_size)

    write_raw_files(input, buffer, table_addr)

    return buffer[: get_new_file_size(new_raw_size)]


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("LZKN64 compression Script", file=sys.stderr)
        print("", file=sys.stderr)
        print("compress.py input_file output_file", file=sys.stderr)
        print(
            "    input_file: Path to the ROM file for a decompressed LZKN64 game.",
            file=sys.stderr,
        )
        print(
            "    output_file: Path to the resulting compressed ROM file.",
            file=sys.stderr,
        )
        sys.exit(1)
    else:
        with open(sys.argv[1], "rb") as input_file:
            input_buf = bytearray(input_file.read())

        table_addr = find_nisitenma_ichigo_offset(input_buf)
        if table_addr is None:
            print(
                "File must be a valid ROM containing a Nisitenma-Ichigo table with decompressed file offsets!",
                file=sys.stderr,
            )
            sys.exit(1)

        with open(sys.argv[2], "wb") as output_file:
            output_file.write(compress(input_buf, table_addr))

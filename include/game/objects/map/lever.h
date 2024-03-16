#ifndef LEVER_H
#define LEVER_H

#include "actor.h"

#define LEVER_STATE_RAISED_UP 0
#define LEVER_STATE_PULL      1

typedef struct {
    u8 field_0x00[6];
    s16 field_0x06;
    u8 field_0x08[20];
} struct_56;

typedef struct {
    void* field_0x00; // A function pointer
    struct_56* field_0x04;
    u32 dlist;
    s32 file_ID;
    s32 event_flag_ID;
    u32 event_flag;
    s32 sound_ID;
} struct_21;

// ID 0x016F
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    cv64_model_inf_t* model;
    u8 field_0x28[12];
    struct_56* field_0x34;
    void* field_0x38; // A function pointer
    struct_21* field_0x3C;
    s32 field_0x40;
    s32 field_0x44;
    s32 current_lever_pull_time;
    s32 max_lever_pull_time;
    s32 model_pitch;
    u8 field_0x54[24];
    s32 state;
    cv64_actor_settings_t* settings;
} lever;

void lever_init(lever* self);
void lever_main_entrypoint(lever* self);
void lever_raisedUp(lever* self);
void lever_pull(lever* self);
void lever_doNothing(lever* self);

#endif

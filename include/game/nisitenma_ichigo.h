#ifndef NISITENMA_ICHIGO_H
#define NISITENMA_ICHIGO_H

#include <ultra64.h>

#define NI_ASSETS_MENU_BUFFER_SIZE 0x30000

/**
 * Nisitenma-Ichigo file IDs
 */
typedef enum NIFileID {
    NI_ASSETS_01                           = 0x01,
    NI_ASSETS_DEBUG_FONT                   = 0x02,
    NI_ASSETS_REINHARDT                    = 0x03,
    NI_ASSETS_REINHARDT_ALT_COSTUME        = 0x04,
    NI_ASSETS_REINHARDT_WHIP               = 0x05,
    NI_ASSETS_CARRIE                       = 0x06,
    NI_ASSETS_CARRIE_ALT_COSTUME           = 0x07,
    NI_ASSETS_ENEMY_TARGET_GRAPHIC         = 0x08,
    NI_ASSETS_UNUSED_3_HEAD_WOLF           = 0x09,
    NI_ASSETS_CERBERUS                     = 0x0A,
    NI_ASSETS_WHITE_DRAGON                 = 0x0B,
    NI_ASSETS_GARDENER                     = 0x0C,
    NI_ASSETS_STONE_DOG                    = 0x0D,
    NI_ASSETS_BEHEMOTH                     = 0x0E,
    NI_ASSETS_WERETIGER                    = 0x0F,
    NI_ASSETS_WEREWOLF                     = 0x10,
    NI_ASSETS_HELL_KNIGHT                  = 0x11,
    NI_ASSETS_GHOST                        = 0x12,
    NI_ASSETS_ICEMAN_PUDDLE                = 0x13,
    NI_ASSETS_MUDMAN_LAVAMAN               = 0x14,
    NI_ASSETS_BLOOD_JELLY                  = 0x15,
    NI_ASSETS_ICEMAN                       = 0x16,
    NI_ASSETS_FIRE_BAT                     = 0x17,
    NI_ASSETS_FLYING_SKULL                 = 0x18,
    NI_ASSETS_BAT                          = 0x19,
    NI_ASSETS_MEDUSA_HEAD                  = 0x1A,
    NI_ASSETS_PILLAR_OF_BONES              = 0x1B,
    NI_ASSETS_UNDEAD_MAIDEN                = 0x1C,
    NI_ASSETS_VAMPIRE_MAID                 = 0x1D,
    NI_ASSETS_VAMPIRE_VILLAGER             = 0x1E,
    NI_ASSETS_VAMPIRE_BUTLER               = 0x1F,
    NI_ASSETS_VINCENT                      = 0x20,
    NI_ASSETS_WEREJAGUAR                   = 0x21,
    NI_ASSETS_SPIDER_CENTAUR               = 0x22,
    NI_ASSETS_LIZARD_MAN                   = 0x23,
    NI_ASSETS_SKELETON_WARRIOR             = 0x24,
    NI_ASSETS_GLASS_KNIGHT                 = 0x25,
    NI_ASSETS_KING_SKELETON                = 0x26,
    NI_ASSETS_SKELETON_BIKER               = 0x27,
    NI_ASSETS_TRUE_DRACULA                 = 0x28,
    NI_ASSETS_MALUS                        = 0x29,
    NI_ASSETS_MALUS_HORSE                  = 0x2A,
    NI_ASSETS_DEMON_DRACULA                = 0x2B,
    NI_ASSETS_VAMPIRE_GILDRE               = 0x2C,
    NI_ASSETS_RENON                        = 0x2D,
    NI_ASSETS_RENON_DEMON                  = 0x2E,
    NI_ASSETS_DEATH                        = 0x2F,
    NI_ASSETS_DEMONIC_FISH                 = 0x30,
    NI_ASSETS_ROSA                         = 0x31,
    NI_ASSETS_32                           = 0x32,
    NI_ASSETS_CAMILLA                      = 0x33,
    NI_ASSETS_ACTRIESE                     = 0x34,
    NI_ASSETS_CAMILLA_FIGHT                = 0x35,
    NI_ASSETS_36                           = 0x36,
    NI_ASSETS_37                           = 0x37,
    NI_COMMON_GAMEPLAY_EFFECTS             = 0x38,
    NI_ASSETS_39                           = 0x39,
    NI_ASSETS_3A                           = 0x3A,
    NI_ASSETS_3B                           = 0x3B,
    NI_ASSETS_3C                           = 0x3C,
    NI_MAP_FOREST_OF_SILENCE               = 0x3D,
    NI_MAP_CASTLE_WALL_TOWERS              = 0x3E,
    NI_MAP_CASTLE_WALL_MAIN                = 0x3F,
    NI_MAP_VILLA_YARD                      = 0x40,
    NI_MAP_VILLA_FOYER                     = 0x41,
    NI_MAP_VILLA_HALLWAY                   = 0x42,
    NI_MAP_VILLA_MAZE_GARDEN               = 0x43,
    NI_MAP_TUNNEL                          = 0x44,
    NI_MAP_UNDERGROUND_WATERWAY            = 0x45,
    NI_MAP_CASTLE_CENTER_MAIN              = 0x46,
    NI_MAP_CASTLE_CENTER_BOTTOM_ELEVATOR   = 0x47,
    NI_MAP_CASTLE_CENTER_LIZARD            = 0x48,
    NI_MAP_CASTLE_CENTER_BROKEN_STAIRCASE  = 0x49,
    NI_MAP_CASTLE_CENTER_LIBRARY           = 0x4A,
    NI_MAP_CASTLE_CENTER_NITRO_ROOM        = 0x4B,
    NI_MAP_CASTLE_CENTER_TOP_ELEVATOR_ROOM = 0x4C,
    NI_MAP_TOWER_OF_EXECUTION              = 0x4D,
    NI_MAP_TOWER_OF_SORCERY                = 0x4E,
    NI_MAP_TOWER_OF_SCIENCE                = 0x4F,
    NI_MAP_DUEL_TOWER                      = 0x50,
    NI_MAP_CASTLE_KEEP_EXTERIOR            = 0x51,
    NI_MAP_CASTLE_KEEP                     = 0x52,
    NI_MAP_INTRO_NARRATION                 = 0x53,
    NI_MAP_CLOCK_TOWER                     = 0x54,
    NI_MAP_DRACULA_DESERT                  = 0x55,
    NI_MAP_ROSE_ACTRICE_MEET_ROOM          = 0x56,
    NI_MAP_VILLA_CRYPT_AREA                = 0x57,
    NI_MAP_ROOM_OF_CLOCKS                  = 0x58,
    NI_MAP_ENDING                          = 0x59,
    NI_ASSETS_PICKABLE_ITEM_ASSETS         = 0x5A,
    NI_ASSETS_SKYBOX                       = 0x5B,
    NI_MAP_TEST_GRID                       = 0x5C,
    NI_ASSETS_KONAMI_AND_KCEK_LOGOS        = 0x5D,
    NI_ASSETS_SCROLL                       = 0x5E,
    NI_ASSETS_TITLE                        = 0x5F,
    NI_ASSETS_MENU                         = 0x60,
    NI_ASSETS_NECRONOMICON                 = 0x61,
    NI_ASSETS_CHARACTER_SELECTION_SCREEN   = 0x62,
    NI_ASSETS_GAMEPLAY_HUD                 = 0x63,
    NI_ASSETS_GAME_OVER                    = 0x64,
    NI_ASSETS_FILE_SELECT                  = 0x65,
    NI_ASSETS_CONTROLLER_BUTTONS           = 0x66,
    NI_ASSETS_RENON_BRIEFCASE              = 0x67,
    NI_ASSETS_FILM_REEL_CUTSCENE_EFFECT    = 0x68,
    NI_ASSETS_CUTSCENE_01                  = 0x69,
    NI_ASSETS_CUTSCENE_02                  = 0x6A,
    NI_ASSETS_CUTSCENE_2B                  = 0x6B,
    NI_ASSETS_CUTSCENE_2C                  = 0x6C,
    NI_ASSETS_CUTSCENE_2E                  = 0x6D,
    NI_ASSETS_CUTSCENE_3F                  = 0x6E,
    NI_ASSETS_CUTSCENE_2D                  = 0x6F,
    NI_ASSETS_CUTSCENE_0A                  = 0x70,
    NI_ASSETS_SMILEY_FACE                  = 0x71,
    NI_OVL_CERBERUS                        = 0x72,
    NI_OVL_WHITE_DRAGON                    = 0x73,
    NI_OVL_GARDENER                        = 0x74,
    NI_OVL_STONE_DOG                       = 0x75,
    NI_OVL_MALUS                           = 0x76,
    NI_OVL_BEHEMOTH                        = 0x77,
    NI_OVL_WERETIGER                       = 0x78,
    NI_OVL_WEREWOLF                        = 0x79,
    NI_OVL_HELL_KNIGHT                     = 0x7A,
    NI_OVL_GHOST                           = 0x7B,
    NI_OVL_ICEMAN                          = 0x7C,
    NI_OVL_ICEMAN_ASSETS_LOADER            = 0x7D,
    NI_OVL_7E                              = 0x7E,
    NI_OVL_FLYING_SKULL                    = 0x7F,
    NI_OVL_BAT                             = 0x80,
    NI_OVL_MEDUSA_HEAD                     = 0x81,
    NI_OVL_PILLAR_OF_BONES                 = 0x82,
    NI_OVL_VAMPIRES                        = 0x83,
    NI_OVL_VINCENT                         = 0x84,
    NI_OVL_85                              = 0x85,
    NI_OVL_86                              = 0x86,
    NI_OVL_87                              = 0x87,
    NI_OVL_88                              = 0x88,
    NI_OVL_89                              = 0x89,
    NI_OVL_SPIDER_CENTAUR                  = 0x8A,
    NI_OVL_LIZARD_MAN                      = 0x8B,
    NI_OVL_SKELETON_WARRIOR                = 0x8C,
    NI_OVL_KING_SKELETON                   = 0x8D,
    NI_OVL_SKELETON_BIKER                  = 0x8E,
    NI_OVL_TRUE_DRACULA                    = 0x8F,
    NI_OVL_90                              = 0x90,
    NI_OVL_91                              = 0x91,
    NI_OVL_MALUS_CUTSCENE                  = 0x92,
    NI_OVL_MALUS_HORSE                     = 0x93,
    NI_OVL_DEMON_DRACULA                   = 0x94,
    NI_OVL_DEMON_DRACULA_ASSETS_LOADER     = 0x95,
    NI_OVL_96                              = 0x96,
    NI_OVL_97                              = 0x97,
    NI_OVL_VAMPIRE_GILDRE                  = 0x98,
    NI_OVL_99                              = 0x99,
    NI_OVL_RENON_DEMON                     = 0x9A,
    NI_OVL_DEATH                           = 0x9B,
    NI_OVL_9C                              = 0x9C,
    NI_OVL_ROSA                            = 0x9D,
    NI_OVL_CAMILLA                         = 0x9E,
    NI_OVL_ACTRISE                         = 0x9F,
    NI_OVL_A0                              = 0xA0,
    NI_OVL_A1                              = 0xA1,
    NI_OVL_A2                              = 0xA2,
    NI_OVL_A3                              = 0xA3,
    NI_OVL_A4                              = 0xA4,
    NI_OVL_HELL_KNIGHT_STATIC              = 0xA5,
    NI_OVL_A6                              = 0xA6,
    NI_OVL_MINI_SCROLL                     = 0xA7,
    NI_OVL_A8                              = 0xA8,
    NI_OVL_GAMENOTE_DELETE_MGR             = 0xA9,
    NI_OVL_TITLE_SCREEN                    = 0xAA,
    NI_OVL_AB                              = 0xAB,
    NI_OVL_AC                              = 0xAC,
    NI_OVL_TITLE_DEMO                      = 0xAD,
    NI_OVL_CREDITSMGR                      = 0xAE,
    NI_OVL_PAUSE_MENU                      = 0xAF,
    NI_OVL_CHARACTER_SELECT                = 0xB0,
    NI_OVL_GAME_OVER                       = 0xB1,
    NI_OVL_SAVE_GAME_RESULTS               = 0xB2,
    NI_OVL_B3                              = 0xB3,
    NI_OVL_SAVE_GAME                       = 0xB4,
    NI_OVL_TEXTBOX_ADVANCE_ARROW           = 0xB5,
    NI_OVL_BUTTON_CONFIG_OPTION_MENU       = 0xB6,
    NI_OVL_ENTRANCE_MAP_NAME_DISPLAY       = 0xB7,
    NI_OVL_CONTRACTMGR                     = 0xB8,
    NI_OVL_RENONS_BRIEFCASE                = 0xB9,
    NI_OVL_BA                              = 0xBA,
    NI_OVL_EASY_MODE_ENDING_MSG            = 0xBB,
    NI_OVL_BC                              = 0xBC,
    NI_OVL_NITRO_MANDRAGORA_DISPLAY        = 0xBD,
    NI_OVL_BE                              = 0xBE,
    NI_OVL_BF                              = 0xBF,
    NI_OVL_C0                              = 0xC0,
    NI_OVL_C1                              = 0xC1,
    NI_OVL_C2                              = 0xC2,
    NI_OVL_FILM_REEL_CUTSCENE_EFFECT       = 0xC3,
    NI_OVL_CUTSCENE_01                     = 0xC4,
    NI_OVL_CUTSCENE_03                     = 0xC5,
    NI_OVL_CUTSCENE_04                     = 0xC6,
    NI_OVL_CUTSCENE_05                     = 0xC7,
    NI_OVL_CUTSCENE_06                     = 0xC8,
    NI_OVL_CUTSCENE_07                     = 0xC9,
    NI_OVL_CUTSCENE_08                     = 0xCA,
    NI_OVL_CUTSCENE_09                     = 0xCB,
    NI_OVL_CUTSCENE_0A                     = 0xCC,
    NI_OVL_CUTSCENE_0B                     = 0xCD,
    NI_OVL_CUTSCENE_0C                     = 0xCE,
    NI_OVL_CUTSCENE_0D                     = 0xCF,
    NI_OVL_CUTSCENE_0E                     = 0xD0,
    NI_OVL_CUTSCENE_0F                     = 0xD1,
    NI_OVL_CUTSCENE_10                     = 0xD2,
    NI_OVL_CUTSCENE_11                     = 0xD3,
    NI_OVL_CUTSCENE_12                     = 0xD4,
    NI_OVL_CUTSCENE_13                     = 0xD5,
    NI_OVL_CUTSCENE_14                     = 0xD6,
    NI_OVL_CUTSCENE_15                     = 0xD7,
    NI_OVL_CUTSCENE_16                     = 0xD8,
    NI_OVL_CUTSCENE_17                     = 0xD9,
    NI_OVL_CUTSCENE_18                     = 0xDA,
    NI_OVL_CUTSCENE_19                     = 0xDB,
    NI_OVL_CUTSCENE_1A                     = 0xDC,
    NI_OVL_CUTSCENE_1B                     = 0xDD,
    NI_OVL_CUTSCENE_1C                     = 0xDE,
    NI_OVL_CUTSCENE_1E                     = 0xDF,
    NI_OVL_CUTSCENE_1F                     = 0xE0,
    NI_OVL_CUTSCENE_21                     = 0xE1,
    NI_OVL_CUTSCENE_22                     = 0xE2,
    NI_OVL_CUTSCENE_23                     = 0xE3,
    NI_OVL_CUTSCENE_24                     = 0xE4,
    NI_OVL_CUTSCENE_25                     = 0xE5,
    NI_OVL_CUTSCENE_26                     = 0xE6,
    NI_OVL_CUTSCENE_27                     = 0xE7,
    NI_OVL_CUTSCENE_28                     = 0xE8,
    NI_OVL_CUTSCENE_29                     = 0xE9,
    NI_OVL_CUTSCENE_2A                     = 0xEA,
    NI_OVL_CUTSCENE_2B                     = 0xEB,
    NI_OVL_CUTSCENE_2C                     = 0xEC,
    NI_OVL_CUTSCENE_2D                     = 0xED,
    NI_OVL_CUTSCENE_2E                     = 0xEE,
    NI_OVL_CUTSCENE_32                     = 0xEF,
    NI_OVL_CUTSCENE_33                     = 0xF0,
    NI_OVL_CUTSCENE_34                     = 0xF1,
    NI_OVL_CUTSCENE_35                     = 0xF2,
    NI_OVL_CUTSCENE_3C                     = 0xF3,
    NI_OVL_CUTSCENE_3D                     = 0xF4,
    NI_OVL_CUTSCENE_3E                     = 0xF5,
    NI_OVL_CUTSCENE_3F                     = 0xF6,
    NI_OVL_CUTSCENE_44                     = 0xF7,
    NI_OVL_CUTSCENE_45                     = 0xF8,
    NI_OVL_CUTSCENE_52                     = 0xF9,
    NI_OVL_CUTSCENE_54                     = 0xFA,
    NI_OVL_CUTSCENE_55                     = 0xFB,
    NI_OVL_CUTSCENE_56                     = 0xFC,
    NI_OVL_CUTSCENE_57                     = 0xFD,
    NI_OVL_CUTSCENE_63                     = 0xFE
} NIFileID;

extern u32 NisitenmaIchigo_checkAndStoreLoadedFile(u32 file_ID);
extern void* NisitenmaIchigoFiles_segmentToVirtual(u32 segment_address, s32 file_ID);

#endif

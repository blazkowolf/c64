#ifndef A9560_H
#define A9560_H

#include "objects/cutscene/interactuables.h"
#include "save.h"
#include "actor_settings.h"

#define INTERACT_TYPE_NONE      0
#define INTERACT_TYPE_ITEM      1
#define INTERACT_TYPE_TEXT_SPOT 2
#define INTERACT_TYPE_OTHERS    3 /* Special textboxes, doors, etc */

typedef struct door_item_open_verify_struct {
    s16 item_ID;
    s16 event_flag_IDs;
    u32 event_flag;
} door_item_open_verify_struct;

// Generic special textbox / text spot struct
typedef struct specialTextbox {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    s32 text_ID;
    u8 field_0x38[4];
    u32 interacting_with_interactuable;
    u32 textbox_is_active;
    u8 field_0x44[20];
    f32 trigger_size_X;
    f32 trigger_size_Z;
    mfds_state* message_textbox;
    vec3f position;
    cv64_actor_settings_t* settings;
} specialTextbox;

specialTextbox*
Player_getSpecialTextboxCurrentlyInteractingWith(s16 actor_ID, cv64_model_inf_t* player_model);
s32 playerCanInteractWithInteractuable(f32 pos_X, f32 pos_Y, f32 pos_Z, interactuables* actor);
s32 interactuables_getInteractingType(specialTextbox* actor);
void interactuables_enableTextbox(specialTextbox* actor);
void interactuables_setInteractingFlag(specialTextbox* actor);
u32 getMapEventFlagID(s16 stage_ID);
void spawnCastleWallGratingMechanismTextboxes(s16 index);
void checkDoorCanBeOpenedWithKey(s16 event_flag_IDs, u32 event_flag);

extern door_item_open_verify_struct door_item_open_verify_list[13];
extern cv64_actor_settings_t* castleWallGratingMechanism_textSpotsActorSettings[1][3];

#endif

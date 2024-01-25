/**
 * File: rose.c
 * Description: Contains the code for objects exclusive to ROSE
 * (Rosa / Actriese Fan Room)
 * Associated objects: 0x0220, 0x1221
 *
 * Mapped by the TLB? = No
 */

#include "objects/map/rose/rose.h"
#include "actor.h"
#include "gfx/figure.h"
#include "gfx/struct_47.h"
#include "objects/player/player.h"
#include "random.h"
#include "sound.h"
#include "system_work.h"

void cv64_ovl_rose_ventilator_entrypoint(cv64_ovl_rose_ventilator_t* self) {
    ENTER(self, cv64_ovl_rose_ventilator_funcs);
}

void cv64_ovl_rose_ventilator_init(cv64_ovl_rose_ventilator_t* self) {
    cv64_ovl_rose_ventilator_cfg_t* speed_settings = &self->speed_settings;
    cv64_model_inf_t* model =
        (*modelInfo_createRootNode)(FIG_TYPE_STANDALONE, D_8018CDE0[0]);
    u32 unused;

    if (model == NULL) {
        // VENTILATOR : Can't allocate F3D.\n
        self->header.destroy(self);
    } else {
        self->model = model;
        model->dlist = &ROSE_VENTILATOR_DL;
        model->assets_file_ID = sys.map_assets_file_IDs[0];
        model->flags |= (FIG_FLAG_0800 | FIG_FLAG_0100);
        CV64_COLOR_RGBA_TO_U32(model->primitive_color) =
            CV64_COLOR_RGBA_TO_U32(sys.primitive_color);
        CV64_COLOR_RGBA_TO_U32(model->fog_color) =
            CV64_COLOR_RGBA_TO_U32(sys.background_color);
        (*modelInfo_setMapActorModel)(model, &ROSE_VENTILATOR_DL);
        speed_settings->current_speed = speed_settings->max_speed =
            ((*rand)() & 0xFFF) + 16;
        speed_settings->time_until_changing_max_speed =
            ((*rand)() & 0x1FF) + 30;
        (*actor_model_set_pos_and_angle)(self, model);
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID);
    }
}

void cv64_ovl_rose_ventilator_loop(cv64_ovl_rose_ventilator_t* self) {
    cv64_model_inf_t* model = self->model;
    cv64_ovl_rose_ventilator_cfg_t* speed_settings = &self->speed_settings;

    CV64_COLOR_RGBA_TO_U32(model->primitive_color) =
        CV64_COLOR_RGBA_TO_U32(sys.primitive_color);
    CV64_COLOR_RGBA_TO_U32(model->fog_color) =
        CV64_COLOR_RGBA_TO_U32(sys.background_color);
    if ((*actor_checkSpawn)(self, model->position.x, model->position.y,
                            model->position.z) != FALSE) {
        // clang-format off
        /* @bug If the player is far away enough from the ventilator, it will try to go to the next function.
                However, `cv64_ovl_rose_ventilator_funcs` only has two functions. This will make the game
                read out of bounds into `cv64_ovl_rose_door_funcs` and essentially turn the current
                ventilator actor into a door.

                One of the side-effects is that the ventilator model will not be destroyed, so multiple ventilator
                models can be created, until `figures_array` is full.

                In practice this will never happen because the spawn radius for the ventilator is larger than the
                map itself, so there's no way to get far away enough from the ventilator to trigger this bug.

                The devs probably intended to create a destroy function specific to the ventilator actor,
                and then placing it into `cv64_ovl_rose_ventilator_funcs`, but no such function exists
                in the final game.
        */
        // clang-format on
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID);
    } else {
        model->angle.pitch -= speed_settings->current_speed;
        if (speed_settings->current_speed < speed_settings->max_speed) {
            speed_settings->current_speed += 17;
        } else if (speed_settings->max_speed < speed_settings->current_speed) {
            speed_settings->current_speed -= 17;
        }
        speed_settings->time_until_changing_max_speed--;
        if (speed_settings->time_until_changing_max_speed == 0) {
            speed_settings->max_speed = ((*rand)() & 0xFFF) + 16;
            speed_settings->time_until_changing_max_speed =
                ((*rand)() & 0x1FF) + 30;
        }
    }
}

void cv64_ovl_rose_door_entrypoint(cv64_ovl_rose_door_t* self) {
    ENTER(self, cv64_ovl_rose_door_funcs);
}

void cv64_ovl_rose_door_init(cv64_ovl_rose_door_t* self) {
    cv64_map_actor_model_t* map_actor_model;
    cv64_actor_settings_t* settings = self->settings;
    cv64_ovl_rose_door_cfg_t* height_settings = &self->height_settings;
    cv64_model_inf_t* model =
        (*modelInfo_createRootNode)(FIG_TYPE_STANDALONE, D_8018CDE0[0]);

    self->model = model;
    (*actor_model_set_pos_and_angle)(self, model);
    model->assets_file_ID = sys.map_assets_file_IDs[0];
    model->dlist = &ROSE_DOOR_DL;
    model->flags |= (FIG_FLAG_0800 | FIG_FLAG_0100);
    CV64_COLOR_RGBA_TO_U32(model->primitive_color) =
        CV64_COLOR_RGBA_TO_U32(sys.primitive_color);
    CV64_COLOR_RGBA_TO_U32(model->fog_color) =
        CV64_COLOR_RGBA_TO_U32(sys.background_color);
    self->header.ID |= OBJ_FLAG_STAGE_OBJECT;
    map_actor_model =
        (*getMapActorModelEntryFromArray)(model->dlist, model->assets_file_ID);
    model->map_actor_model = map_actor_model;
    self->map_actor_model = map_actor_model;
    (*object_curLevel_goToNextFuncAndClearTimer)(self->header.current_function,
                                                 &self->header.functionInfo_ID);
    height_settings->initial_height = model->position.y;
    height_settings->height = 25.0f;
    height_settings->closing_speed = 0.0f;
    model->position.y =
        height_settings->height + height_settings->initial_height;
    if (settings->variable_1 != FALSE) {
        (*object_nextLevel_goToFunc)(self->header.current_function,
                                     &self->header.functionInfo_ID,
                                     ROSE_DOOR_STATE_IDLE);
    }
}

void cv64_ovl_rose_door_loop(cv64_ovl_rose_door_t* self) {
    cv64_model_inf_t* model = self->model;
    cv64_ovl_rose_door_cfg_t* height_settings = &self->height_settings;

    CV64_COLOR_RGBA_TO_U32(model->primitive_color) =
        CV64_COLOR_RGBA_TO_U32(sys.primitive_color);
    CV64_COLOR_RGBA_TO_U32(model->fog_color) =
        CV64_COLOR_RGBA_TO_U32(sys.background_color);

    if ((*actor_checkSpawn)(self, model->position.x, model->position.y,
                            model->position.z) != FALSE) {
        self->header.destroy(self);
    } else {
        ENTER(self, cv64_ovl_rose_door_state_funcs);
        model->position.y =
            height_settings->initial_height + height_settings->height;
    }
}

void cv64_ovl_rose_door_state_startClosing(cv64_ovl_rose_door_t* self) {
    cv64_ovl_rose_door_cfg_t* height_settings = &self->height_settings;
    cv64_model_inf_t* model = self->model;

    if ((*checkIfOutsideEntityIsInsideMainEntityRadius)(
            model, ptr_PlayerData->visualData.model, 15.0f, AXIS_Z) == FALSE) {
        if (sys.SaveStruct_gameplay.character == REINHARDT) {
            (*play_sound_in_position_and_set_volume)(SD_ROSE_DOOR_CLOSING,
                                                     &model->position, 0.5f);
        } else {
            (*play_sound_in_position_and_set_volume)(SD_ROSE_DOOR_CLOSING,
                                                     &model->position, 1.0f);
        }
        // Cleaner version
        // (*play_sound_in_position_and_set_volume)(SD_ROSE_DOOR_CLOSING,
        // &model->position,
        // ((sys.SaveStruct_gameplay.character == REINHARDT) ? 0.5f : 1.0f));
        height_settings->closing_speed = 0.0f;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID);
    }
}

void cv64_ovl_rose_door_state_closing(cv64_ovl_rose_door_t* self) {
    cv64_ovl_rose_door_cfg_t* height_settings = &self->height_settings;
    cv64_model_inf_t* model = self->model;

    if (height_settings->closing_speed < 0.4166666666666667) {
        height_settings->closing_speed += 0.01388888888888889;
    }
    height_settings->height -= height_settings->closing_speed;
    if (height_settings->height < 0.0) {
        (*play_sound)(STOP_SOUND(SD_ROSE_DOOR_CLOSING));
        if (sys.SaveStruct_gameplay.character == REINHARDT) {
            (*play_sound_in_position_and_set_volume)(SD_ROSE_DOOR_CLOSE,
                                                     &model->position, 0.5f);
        } else {
            (*play_sound_in_position_and_set_volume)(SD_ROSE_DOOR_CLOSE,
                                                     &model->position, 1.0f);
        }
        height_settings->height = 0.0f;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID);
    }
}

void cv64_ovl_rose_door_state_idle(cv64_ovl_rose_door_t* self) {}

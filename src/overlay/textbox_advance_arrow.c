/*
 * File: textbox_advance_arrow.c
 * Description:
 *   The blinking red arrow that appears when you can press A to advance t the
 *   next string in a textbox. (Not to be confused with the red arrow used for
 *   selecting options in some textboxes)
 * Associated objects: 0x2138
 *
 * Mapped by the TLB? = Yes
 */

#include "gfx/camera.h"
#include "objects/menu/textboxAdvanceArrow.h"

void (*cv64_ovl_textboxadvancearrow_funcs[])(textboxAdvanceArrow* self
) = {textboxAdvanceArrow_init, textboxAdvanceArrow_loop, textboxAdvanceArrow_destroy};

void textboxAdvanceArrow_entrypoint(textboxAdvanceArrow* self) {
    ENTER(self, cv64_ovl_textboxadvancearrow_funcs);
}

void textboxAdvanceArrow_init(textboxAdvanceArrow* self) {
    struct_47* temp;
    cv64_model_inf_t* model;

    temp             = (*func_80004C40)(FIG_TYPE_STRUCT_47);
    self->field_0x28 = temp;
    (*func_80004CE8)(temp, common_camera_HUD);
    temp->primitive_color.r = temp->primitive_color.g = temp->primitive_color.b = 0xA0;
    temp->field5_0x3c                                                           = 1;
    temp->blend_color.r = temp->blend_color.g = temp->blend_color.b = 0xCF;
    (s8) temp->fog_color.r = 0xF0; // The s8 typecast is needed for matching here
    temp->fog_color.g      = 0;
    temp->fog_color.b      = 0x10;
    model                  = (*modelInfo_createRootNode)(FIG_TYPE_HUD_ELEMENT, temp);
    self->model            = model;
    model->dlist           = &TEXTBOX_ADVANCE_ARROW_DL;
    model->assets_file_ID  = NI_ASSETS_FILE_SELECT;
    BITS_SET(model->flags, FIG_FLAG_0080);
    BITS_SET(model->flags, FIG_FLAG_0800);
    model->primitive_color.integer = 0xFF0000FF; // Red (opaque)
    model->size.x                  = 1.3f;
    model->size.y                  = 1.3f;
    model->position.x              = 0.0f;
    model->position.z              = 0.0f;
    model->position.y              = -90.0f;
    self->disable_arrow            = FALSE;
    self->fade_timer               = 0;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void textboxAdvanceArrow_loop(textboxAdvanceArrow* self) {
    u32 fade_timer_prev     = self->fade_timer;
    cv64_model_inf_t* model = self->model;
    u8 red;
    u32 new_var;

    self->fade_timer++;
    if ((fade_timer_prev > 9) != (((fade_timer_prev > 9) != FALSE) * 0)) { // Likely a fakematch
        new_var = model->primitive_color.r;
        red     = new_var;
        if (red < 8.5) {
            model->primitive_color.r = 0xFF;
            model->primitive_color.a = 0xFF;
            self->fade_timer         = 0;
        } else {
            model->primitive_color.r = red - 8.5;
            model->primitive_color.a -= 8.5;
        }
    }
    if (self->disable_arrow) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void textboxAdvanceArrow_destroy(textboxAdvanceArrow* self) {
    self->header.destroy(self);
}

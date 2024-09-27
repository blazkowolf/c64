#include <ultra64.h>
#include "objects/cutscene/cs_film_reel.h"
#include "system_work.h"

// clang-format off

CSFilmReel_func CSFilmReel_functions[] = {
    CSFilmReel_CheckInitialConditions,
    CSFilmReel_Init,
    CSFilmReel_Loop,
    CSFilmReel_Destroy
};

// clang-format on

void CSFilmReel_Entrypoint(CSFilmReel* self) {
    ENTER(self, CSFilmReel_functions);
}

void CSFilmReel_CheckInitialConditions(CSFilmReel* self) {
    if (sys.cutscene_flags & CUTSCENE_FLAG_FILM_REEL_EFFECT) {
        if (sys.cutscene_flags & CUTSCENE_FLAG_DISPLAY_WIDESCREEN_BORDERS) {
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        }
    } else {
        self->header.destroy(self);
    }
}

// https://decomp.me/scratch/bftIF
#ifdef NON_MATCHING
    #pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cs_film_reel/CSFilmReel_Init.s")
#else
void CSFilmReel_Init(CSFilmReel* self) {
    CSFilmReelData* data;
    CSFilmReelGraphicContainer* graphic_container;
    Model* left_reel_model;
    Model* right_reel_model;
    CSFilmReelGraphicData* graphic_data;
    camera* display_camera;
    u32 material_dlist;
    CSFilmReelGraphicRawData* raw_data;
    Gfx* current_dlist;

    data =
        (*object_allocEntryInListAndClear)(self, HEAP_KIND_MULTIPURPOSE, sizeof(CSFilmReelData), 0);

    display_camera = (*camera_create)(FIG_TYPE_CAMERA_ORTHO, 8);
    (*figure_setSibling)(display_camera, common_camera_game_view);
    display_camera->position.y = 0.0f;
    display_camera->position.x = 0.0f;
    display_camera->position.z = 101.0f;

    left_reel_model        = (*Model_createAndSetChild)(FIG_TYPE_HUD_ELEMENT, display_camera);
    self->left_reel_model  = left_reel_model;
    left_reel_model->dlist = &CSFILMREEL_DL;
    left_reel_model->assets_file_ID = NI_ASSETS_FILM_REEL_CUTSCENE_EFFECT;
    left_reel_model->position.z     = 0.0f;
    left_reel_model->position.y     = 0.0f;
    left_reel_model->size.z         = 3.5f;
    left_reel_model->size.y         = 3.5f;
    left_reel_model->size.x         = 3.5f;
    left_reel_model->position.x     = -136.0f;

    right_reel_model        = (*Model_createAndSetChild)(FIG_TYPE_HUD_ELEMENT, display_camera);
    self->right_reel_model  = right_reel_model;
    right_reel_model->dlist = &CSFILMREEL_DL;
    right_reel_model->assets_file_ID = NI_ASSETS_FILM_REEL_CUTSCENE_EFFECT;
    right_reel_model->position.z     = 0.0f;
    right_reel_model->position.y     = 0.0f;
    right_reel_model->size.z         = 3.5f;
    right_reel_model->size.y         = 3.5f;
    right_reel_model->size.x         = 3.5f;
    right_reel_model->position.x     = 136.0f;

    graphic_data =
        (*object_allocEntryInList)(self, HEAP_KIND_MULTIPURPOSE, sizeof(CSFilmReelGraphicData), 3);
    data->graphic_data = graphic_data;
    graphic_container =
        (*func_80002264_2E64)(self, HEAP_KIND_MULTIPURPOSE, sizeof(CSFilmReelGraphicRawData), 4);
    graphic_data->graph_container = graphic_container;

    if (1) {
    }
    graphic_container = graphic_data->graph_container;
    raw_data          = graphic_container->header.data_ptrs[sys.current_graphic_buffer];
    current_dlist     = (Gfx*) ARRAY_START(raw_data->dlists);
    if (1) {
    }
    gSPEndDisplayList(current_dlist++);

    graphic_container = graphic_data->graph_container;
    raw_data          = graphic_container->header.data_ptrs[sys.previous_graphic_buffer];
    current_dlist     = (Gfx*) ARRAY_START(raw_data->dlists);
    gSPEndDisplayList(current_dlist++);

    graphic_data->field_0x04 =
        GET_UNMAPPED_ADDRESS(NI_ASSETS_FILM_REEL_CUTSCENE_EFFECT, &CSFILMREEL_06000258);
    graphic_data->texture_ptr =
        GET_UNMAPPED_ADDRESS(NI_ASSETS_FILM_REEL_CUTSCENE_EFFECT, &CSFILMREEL_TEXTURE);
    if (1) {
    }
    graphic_data->tile              = G_TX_RENDERTILE;
    graphic_data->height            = 0.0f;
    graphic_data->alpha_change_rate = 8;
    graphic_data->alpha = graphic_data->dont_increase_alpha = graphic_data->field_0x12 = 0;
    data->scrolling_speed                                                              = 2.0f;

    left_reel_model                  = self->left_reel_model;
    right_reel_model                 = self->right_reel_model;
    material_dlist                   = CSFilmReel_Draw(graphic_data);
    left_reel_model->material_dlist  = material_dlist;
    right_reel_model->material_dlist = material_dlist;

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}
#endif

void CSFilmReel_Loop(CSFilmReel* self) {
    CSFilmReelData* data                = self->data;
    CSFilmReelGraphicData* graphic_data = data->graphic_data;
    Model* left_reel_model              = self->left_reel_model;
    Model* right_reel_model             = self->right_reel_model;
    u32 material_dlist;

    if (sys.cutscene_flags & CUTSCENE_FLAG_FILM_REEL_EFFECT) {
        if (graphic_data->dont_increase_alpha == FALSE) {
            graphic_data->alpha += graphic_data->alpha_change_rate;
            if (graphic_data->alpha > 255) {
                graphic_data->alpha               = 255;
                graphic_data->dont_increase_alpha = TRUE;
            }
        }
    } else {
        if (graphic_data->alpha < graphic_data->alpha_change_rate) {
            graphic_data->alpha = FALSE;
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        } else {
            graphic_data->alpha -= graphic_data->alpha_change_rate;
        }
    }

    graphic_data->height += data->scrolling_speed;
    if (data->scrolling_speed < 0.0) {
        if (graphic_data->height < 0.0) {
            graphic_data->height += 32.0f;
        }
    } else {
        if (graphic_data->height > 32.0f) {
            graphic_data->height -= 32.0f;
        }
    }

    material_dlist                   = CSFilmReel_Draw(graphic_data);
    left_reel_model->material_dlist  = material_dlist;
    right_reel_model->material_dlist = material_dlist;
}

void CSFilmReel_Destroy(CSFilmReel* self) {
    self->header.destroy(self);
}

#define SET_TEXTURE_PARAMS(dlist, texture_ptr, tile, ult)                                          \
    gDPSetTextureImage(dlist++, G_IM_FMT_I, G_IM_SIZ_16b, 1, texture_ptr);                         \
    gDPSetTile(                                                                                    \
        dlist++,                                                                                   \
        G_IM_FMT_I,                                                                                \
        G_IM_SIZ_16b,                                                                              \
        0,                                                                                         \
        0x0000,                                                                                    \
        G_TX_LOADTILE,                                                                             \
        0,                                                                                         \
        G_TX_NOMIRROR | G_TX_WRAP,                                                                 \
        5,                                                                                         \
        G_TX_NOLOD,                                                                                \
        G_TX_NOMIRROR | G_TX_WRAP,                                                                 \
        5,                                                                                         \
        G_TX_NOLOD                                                                                 \
    );                                                                                             \
    gDPLoadSync(dlist++);                                                                          \
    gDPLoadBlock(dlist++, G_TX_LOADTILE, 0, 0, 255, 1024);                                         \
    gDPPipeSync(dlist++);                                                                          \
    gDPSetTile(                                                                                    \
        dlist++,                                                                                   \
        G_IM_FMT_I,                                                                                \
        G_IM_SIZ_4b,                                                                               \
        2,                                                                                         \
        0x0000,                                                                                    \
        tile,                                                                                      \
        0,                                                                                         \
        G_TX_NOMIRROR | G_TX_WRAP,                                                                 \
        5,                                                                                         \
        G_TX_NOLOD,                                                                                \
        G_TX_NOMIRROR | G_TX_WRAP,                                                                 \
        5,                                                                                         \
        G_TX_NOLOD                                                                                 \
    );                                                                                             \
    gDPSetTileSize(dlist++, tile, 0, ult, 124, 124);

u32 CSFilmReel_Draw(CSFilmReelGraphicData* graphic_data) {
    CSFilmReelGraphicRawData* raw_data =
        (CSFilmReelGraphicRawData*)
            graphic_data->graph_container->header.data_ptrs[sys.current_graphic_buffer];
    Gfx* current_dlist      = (Gfx*) ARRAY_START(raw_data->dlists);
    Gfx* dlist_buffer_start = current_dlist;

    gDPPipeSync(current_dlist++);
    gSPDisplayList(current_dlist++, graphic_data->field_0x04);
    gSPTexture(current_dlist++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(current_dlist++, G_CC_MODULATEIA_PRIM, G_CC_PASS2);
    gDPSetPrimColor(current_dlist++, 0, 0, 153, 153, 153, graphic_data->alpha);
    SET_TEXTURE_PARAMS(
        current_dlist,
        graphic_data->texture_ptr,
        graphic_data->tile,
        (s32) ((graphic_data->height * 4.0f) + 0.5)
    )
    gSPEndDisplayList(current_dlist++);
    return (*osVirtualToPhysical)(dlist_buffer_start);
}

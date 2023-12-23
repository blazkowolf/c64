#include "fade.h"
#include "cv64.h"
#include "unknown_struct.h"
#include <ultra64.h>

extern Gfx* gDisplayListHead;

extern Gfx cv64_dl_fade_normal[];
// Gfx DL_fade_normal[] = {
//     gsDPPipeSync(),
//     gsDPSetCycleType(G_CYC_1CYCLE),
//     gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG |
//                           G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
//                           G_LOD | G_SHADING_SMOOTH),
//     gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
//     gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
//     gsDPSetPrimDepth(-1, -1),
//     gsDPSetDepthSource(G_ZS_PRIM),
//     gsDPSetAlphaCompare(G_AC_NONE),
//     gsDPSetColorDither(G_CD_MAGICSQ),
//     gsDPSetAlphaDither(G_AD_NOISE),
//     gsDPFillRectangle(0, 0, 319, 239),
//     gsSPEndDisplayList(),
// };

extern Gfx cv64_dl_fade_with_outline[];
// Gfx DL_fade_with_outline[] = {
//     gsDPPipeSync(),
//     gsDPSetCycleType(G_CYC_2CYCLE),
//     gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG |
//                           G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
//                           G_LOD | G_SHADING_SMOOTH),
//     gsDPSetRenderMode(
//         IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL |
//             GBL_c1(G_BL_CLR_IN, G_BL_0, G_BL_CLR_FOG, G_BL_A_MEM),
//         IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL |
//             GBL_c2(G_BL_CLR_IN, G_BL_A_FOG, G_BL_CLR_MEM, G_BL_1MA)),
//     gsDPSetCombineLERP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
//     gsDPSetPrimDepth(-1, -1),
//     gsDPSetDepthSource(G_ZS_PRIM),
//     gsDPSetAlphaCompare(G_AC_NONE),
//     gsDPSetColorDither(G_CD_MAGICSQ),
//     gsDPSetAlphaDither(G_AD_NOISE),
//     gsDPFillRectangle(0, 0, 319, 239),
//     gsSPEndDisplayList(),
// };

void fade_setAllFlags(s16 flags) { D_80383AB8.fade_settings.flags = flags; }

void fade_setFlag(s16 flag) { D_80383AB8.fade_settings.flags |= flag; }

void fade_removeFlag(s16 flag) { D_80383AB8.fade_settings.flags &= ~flag; }

void fade_setColor(u8 R, u8 G, u8 B) {
    D_80383AB8.fade_settings.color.R = R;
    D_80383AB8.fade_settings.color.G = G;
    D_80383AB8.fade_settings.color.B = B;
}

// The cleaner version
// void fade_setSettings(s16 flags, u16 fade_time, u8 R, u8 G, u8 B) {
//     fade_setAllFlags(flags);
//     D_80383AB8.fade_settings.max_time = fade_time;
//     D_80383AB8.fade_settings.current_time =
//         (flags & FADE_OUT) ? 1 : fade_time - 1;
//     fade_setColor(R, G, B);
// }

// The matching version
void fade_setSettings(s16 flags, u16 fade_time, u8 R, u8 G, u8 B) {
    D_80383AB8.fade_settings.flags = flags;
    D_80383AB8.fade_settings.max_time = fade_time;

    D_80383AB8.fade_settings.current_time =
        (flags & FADE_OUT) ? 1 : fade_time - 1;

    D_80383AB8.fade_settings.color.R = R;
    D_80383AB8.fade_settings.color.G = G;
    D_80383AB8.fade_settings.color.B = B;
}

// The cleaner version
// u32 fade_isFading() {
//     if (!D_80383AB8.fade_settings.flags ||
//         ((D_80383AB8.fade_settings.flags & FADE_OUT) &&
//          (D_80383AB8.fade_settings.current_time ==
//           D_80383AB8.fade_settings.max_time))) {
//         return FALSE;
//     }
//
//     return D_80383AB8.fade_settings.flags & (FADE_IN | FADE_OUT);
// }

// The matching version
u32 fade_isFading() {
    if (D_80383AB8.fade_settings.flags != 0) {
        if ((D_80383AB8.fade_settings.flags & FADE_OUT) &&
            (D_80383AB8.fade_settings.current_time ==
             D_80383AB8.fade_settings.max_time)) {
            return FALSE;
        } else {
            return D_80383AB8.fade_settings.flags & (FADE_IN | FADE_OUT);
        }
    } else {
        return FALSE;
    }
}

#ifdef NON_MATCHING
#pragma GLOBAL_ASM("../asm/nonmatchings/fade/fade_calc.s")
#else

// 0x8000E6C4 (Matched by anon. Original scratch:
// https://decomp.me/scratch/j0Te1)

void fade_calc() {
    f32 alpha;
    s32 flags = D_80383AB8.fade_settings.flags;

    if ((flags != 0) && (D_80383AB8.fade_settings.current_time)) {
        alpha = (f32)D_80383AB8.fade_settings.current_time /
                D_80383AB8.fade_settings.max_time;

        if (flags & FADE_OUT) {
            if (D_80383AB8.fade_settings.current_time <
                D_80383AB8.fade_settings.max_time) {
                D_80383AB8.fade_settings.current_time++;
            }
        } else {
            D_80383AB8.fade_settings.current_time--;
            if (D_80383AB8.fade_settings.current_time == 0) {
                D_80383AB8.fade_settings.flags = 0;
            }
        }

        D_80383AB8.fade_settings.color.A = (s32)(alpha * 255.9999);

        if (flags & FADE_WITH_OUTLINE) {
            gDPSetFogColor(gDisplayListHead++, D_80383AB8.fade_settings.color.R,
                           D_80383AB8.fade_settings.color.G,
                           D_80383AB8.fade_settings.color.B,
                           D_80383AB8.fade_settings.color.A);
            gSPDisplayList(gDisplayListHead++, &cv64_dl_fade_with_outline);
        } else {
            gDPSetPrimColor(gDisplayListHead++, 0, 0,
                            D_80383AB8.fade_settings.color.R,
                            D_80383AB8.fade_settings.color.G,
                            D_80383AB8.fade_settings.color.B,
                            D_80383AB8.fade_settings.color.A);
            gSPDisplayList(gDisplayListHead++, &cv64_dl_fade_normal);
        }
    }
}

#endif // NON_MATCHING

// #pragma GLOBAL_ASM("../asm/nonmatchings/fade/D_800A27B0_A33B0.s")

// #pragma GLOBAL_ASM("../asm/nonmatchings/fade/D_800A27D8_A33D8.s")

// #pragma GLOBAL_ASM("../asm/nonmatchings/fade/D_800A27E4_A33E4.s")

// #pragma GLOBAL_ASM("../asm/nonmatchings/fade/D_800A27F0_A33F0.s")

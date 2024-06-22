// **************************************************************************
//
//       Copyright 1993-1999 NVIDIA, Corporation.  All rights reserved.
//
//     NOTICE TO USER:   The source code  is copyrighted under  U.S. and
//     international laws.  Users and possessors of this source code are
//     hereby granted a nonexclusive,  royalty-free copyright license to
//     use this code in individual and commercial software.
//
//     Any use of this source code must include,  in the user documenta-
//     tion and  internal comments to the code,  notices to the end user
//     as follows:
//
//       Copyright 1993-1999 NVIDIA, Corporation.  All rights reserved.
//
//     NVIDIA, CORPORATION MAKES NO REPRESENTATION ABOUT THE SUITABILITY
//     OF  THIS SOURCE  CODE  FOR ANY PURPOSE.  IT IS  PROVIDED  "AS IS"
//     WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.  NVIDIA, CORPOR-
//     ATION DISCLAIMS ALL WARRANTIES  WITH REGARD  TO THIS SOURCE CODE,
//     INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGE-
//     MENT,  AND FITNESS  FOR A PARTICULAR PURPOSE.   IN NO EVENT SHALL
//     NVIDIA, CORPORATION  BE LIABLE FOR ANY SPECIAL,  INDIRECT,  INCI-
//     DENTAL, OR CONSEQUENTIAL DAMAGES,  OR ANY DAMAGES  WHATSOEVER RE-
//     SULTING FROM LOSS OF USE,  DATA OR PROFITS,  WHETHER IN AN ACTION
//     OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  ARISING OUT OF
//     OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOURCE CODE.
//
//     U.S. Government  End  Users.   This source code  is a "commercial
//     item,"  as that  term is  defined at  48 C.F.R. 2.101 (OCT 1995),p
//     consisting  of "commercial  computer  software"  and  "commercial
//     computer  software  documentation,"  as such  terms  are  used in
//     48 C.F.R. 12.212 (SEPT 1995)  and is provided to the U.S. Govern-
//     ment only as  a commercial end item.   Consistent with  48 C.F.R.
//     12.212 and  48 C.F.R. 227.7202-1 through  227.7202-4 (JUNE 1995),
//     all U.S. Government End Users  acquire the source code  with only
//     those rights set forth herein.
//
// **************************************************************************
//
//  Module: nvprecomp.h
//     headers used frequently by D3D drivers for all architectures.
//     all are included via this file to enable pre-compiling.
//
// **************************************************************************
//
//  History:
//       Craig Duttweiler    (bertrem)   01Mar99     created
//
// **************************************************************************

#ifndef _NVPRECOMP_H
#define _NVPRECOMP_H

#ifdef __clang__
#pragma clang diagnostic ignored "-Wc++11-narrowing"
#pragma clang diagnostic ignored "-Wconditional-uninitialized"
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma clang diagnostic ignored "-Wformat"
#pragma clang diagnostic ignored "-Wuninitialized"
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wwritable-strings"
#endif

#include <math.h>

#include "nv32.h"

// NV Reference Manual register access definitions.
#define BIT(b)                  (1<<(b))
#define DEVICE_BASE(d)          (0?d)
#define DEVICE_EXTENT(d)        (1?d)
#define DRF_SHIFT(drf)          ((0?drf) % 32)
#define DRF_MASK(drf)           (0xFFFFFFFF>>(31-((1?drf) % 32)+((0?drf) % 32)))
#define DRF_DEF(d,r,f,c)        ((NV ## d ## r ## f ## c)<<DRF_SHIFT(NV ## d ## r ## f))
#define DRF_NUM(d,r,f,n)        (((n)&DRF_MASK(NV ## d ## r ## f))<<DRF_SHIFT(NV ## d ## r ## f))
#define DRF_VAL(d,r,f,v)        (((v)>>DRF_SHIFT(NV ## d ## r ## f))&DRF_MASK(NV ## d ## r ## f))
#define REG_WR_DRF_NUM(d,r,f,n) REG_WR32(NV ## d ## r, DRF_NUM(d,r,f,n))
#define REG_WR_DRF_DEF(d,r,f,c) REG_WR32(NV ## d ## r, DRF_DEF(d,r,f,c))
#define FLD_WR_DRF_NUM(d,r,f,n) REG_WR32(NV##d##r,(REG_RD32(NV##d##r)&~(DRF_MASK(NV##d##r##f)<<DRF_SHIFT(NV##d##r##f)))|DRF_NUM(d,r,f,n))
#define FLD_WR_DRF_DEF(d,r,f,c) REG_WR32(NV##d##r,(REG_RD32(NV##d##r)&~(DRF_MASK(NV##d##r##f)<<DRF_SHIFT(NV##d##r##f)))|DRF_DEF(d,r,f,c))
#define REG_RD_DRF(d,r,f)       (((REG_RD32(NV ## d ## r))>>DRF_SHIFT(NV ## d ## r ## f))&DRF_MASK(NV ## d ## r ## f))

#define NVCLASS_0056_CELSIUS    0x00000010
#define NVCLASS_0096_CELSIUS    0x00000020
#define NVCLASS_1196_CELSIUS    0x00000040

#define NVCLASS_0097_KELVIN     0x00000080

// class 0 collectives
#define NVCLASS_FAMILY_CELSIUS  (NVCLASS_0056_CELSIUS | NVCLASS_0096_CELSIUS | NVCLASS_1196_CELSIUS)
#define NVCLASS_FAMILY_KELVIN   (NVCLASS_0097_KELVIN)

// definitions for dbgLevel debug output level flags
#define NVDBG_LEVEL_ERROR               0x80000000
#define NVDBG_LEVEL_INFO                0x40000000
#define NVDBG_LEVEL_VERTEX_REUSE        0x20000000
#define NVDBG_LEVEL_COLORKEY_INFO       0x10000000
#define NVDBG_LEVEL_AA_INFO             0x08000000
#define NVDBG_LEVEL_FLIP                0x04000000
#define NVDBG_LEVEL_SURFACE             0x02000000  // shows info for CreateSurface, CreateSurfaceEx and DestroySurface
#define NVDBG_LEVEL_SURFACE_ACTIVITY    0x01000000  // shows surface activity
#define NVDBG_LEVEL_SURFACEALLOC        0x00800000  // print info about surface allocations
#define NVDBG_LEVEL_NVOBJ_INFO          0x00400000  // print reference/release access on CNVObjects
#define NVDBG_LEVEL_TEXMAN              0x00200000  // print info about texture fetches and evictions
#define NVDBG_LEVEL_HEAP_ACTIVITY       0x00100000  // print info about IPM heap activity
#define NVDBG_LEVEL_HEAP_USAGE          0x00080000  // print info about heap usage
#define NVDBG_LEVEL_PALETTE             0x00040000  // print info about palette usage
#define NVDBG_LEVEL_PERFORMANCE         0x00020000  // print performance issues
#define NVDBG_LEVEL_VSHADER_INFO        0x00010000  // print inner loop info about vertex shaders
#define NVDBG_LEVEL_VSHADER_IO          0x00008000  // print inner loop info about vertex shader input/output data
#define NVDBG_LEVEL_VSHADER_INS         0x00004000  // print vertex shader instructions
#define NVDBG_LEVEL_HOS_INFO            0x00002000  // print info on HOS processing
#define NVDBG_LEVEL_HOS_VERTEX_INFO     0x00001000  // print info on HOS vertex data
#define NVDBG_LEVEL_PIXEL_SHADER        0x00000800  // print pixel shader instructions (create info)
#define NVDBG_LEVEL_NV_AGP              0x00000400  // print info about nvidia managed AGP activity
#ifdef KPFS
#define NVDBG_LEVEL_VSHADER_MAN         0x00000200  // print info about the vertex shader manager
#endif

// DX8 stuff
#define CELSIUS_CAPS_MAX_STREAMS                  16
#define CELSIUS_CAPS_MAX_PSHADER_CONSTS           16
#define CELSIUS_CAPS_MAX_VSHADER_CONSTS           0
#define CELSIUS_CAPS_MAX_VSHADER_TEMPS            0

// general HW capabilities used internally by driver ------------------------

#define CELSIUS_NUM_COMBINERS            2           // virtual combiner stages
#define CELSIUS_NUM_TEXTURES             2           // texture units

#define KELVIN_NUM_COMBINERS            8           // virtual combiner stages
#define KELVIN_NUM_MATRICES             4           // blendable matrices
#define KELVIN_NUM_TEXTURES             4           // texture units
#define KELVIN_NUM_WINDOWS              8           // clip windows

// DX8 stuff
#define KELVIN_CAPS_MAX_STREAMS                     16
#define KELVIN_CAPS_MAX_PSHADER_CONSTS              16
#define KELVIN_CAPS_MAX_VSHADER_CONSTS              96
#define KELVIN_CAPS_MAX_VSHADER_TEMPS               16

// define global values to be the greatest of those required by the various architectures
#if (NVARCH >= 0x020)
#define NV_CAPS_MAX_COMBINERS       KELVIN_NUM_COMBINERS
#define NV_CAPS_MAX_TEXTURES        KELVIN_NUM_TEXTURES
#define NV_CAPS_MAX_MATRICES        KELVIN_NUM_MATRICES
#define NV_CAPS_MAX_UV_SETS         KELVIN_CAPS_MAX_UV_PAIRS
#define NV_CAPS_MAX_CLIPPLANES      KELVIN_CAPS_MAX_USER_CLIP_PLANES_ALLOWED
#define NV_CAPS_MAX_STREAMS         KELVIN_CAPS_MAX_STREAMS
#define NV_CAPS_MAX_PSHADER_CONSTS  KELVIN_CAPS_MAX_PSHADER_CONSTS
#define NV_CAPS_MAX_VSHADER_TEMPS   KELVIN_CAPS_MAX_VSHADER_TEMPS
#define NV_CAPS_MAX_VSHADER_CONSTS  KELVIN_CAPS_MAX_VSHADER_CONSTS
#elif (NVARCH >= 0x010)
#define NV_CAPS_MAX_COMBINERS       CELSIUS_NUM_COMBINERS
#define NV_CAPS_MAX_TEXTURES        CELSIUS_NUM_TEXTURES
#define NV_CAPS_MAX_MATRICES        CELSIUS_CAPS_MAX_VERTEX_BLEND_MATRICES
#define NV_CAPS_MAX_UV_SETS         CELSIUS_CAPS_MAX_UV_PAIRS
#define NV_CAPS_MAX_CLIPPLANES      CELSIUS_CAPS_MAX_USER_CLIP_PLANES
#define NV_CAPS_MAX_STREAMS         CELSIUS_CAPS_MAX_STREAMS
#define NV_CAPS_MAX_PSHADER_CONSTS  CELSIUS_CAPS_MAX_PSHADER_CONSTS
#define NV_CAPS_MAX_VSHADER_TEMPS   CELSIUS_CAPS_MAX_VSHADER_TEMPS
#define NV_CAPS_MAX_VSHADER_CONSTS  CELSIUS_CAPS_MAX_VSHADER_CONSTS
#else  // nv4
#define NV_CAPS_MAX_TEXTURES        2
#define NV_CAPS_MAX_STREAMS         1
#define NV_CAPS_MAX_MATRICES        NV4_CAPS_MAX_VERTEX_BLEND_MATRICES
#define NV_CAPS_MAX_UV_SETS         NV4_CAPS_MAX_UV_PAIRS
#define NV_CAPS_MAX_CLIPPLANES      NV4_CAPS_MAX_USER_CLIP_PLANES
#define NV_CAPS_MAX_PSHADER_CONSTS  0
#define NV_CAPS_MAX_VSHADER_TEMPS   0
#define NV_CAPS_MAX_VSHADER_CONSTS  0
#endif

// This max required number. Device could have more registers. Check caps.
#define D3DVS_CONSTREG_MAX_V1_1         96

// NV25
#define NV097_SET_SHADER_STAGE_PROGRAM_STAGE3_DEPENDENT_RGB_3D          0x00000013
#define NV097_SET_SHADER_STAGE_PROGRAM_STAGE3_DEPENDENT_RGB_CUBE_MAP    0x00000014
#define NV097_SET_SHADER_STAGE_PROGRAM_STAGE3_DOT_PASS_THROUGH          0x00000015
#define NV097_SET_SHADER_STAGE_PROGRAM_STAGE3_DOT_1D                    0x00000016
#define NV097_SET_SHADER_STAGE_PROGRAM_STAGE3_DOT_AFFINE_DEPTH_REPLACE  0x00000017

#define NV097_SET_COMBINER_COLOR_OCW_AB_TRUNC_ENABLE                    25:25
#define NV097_SET_COMBINER_COLOR_OCW_CD_TRUNC_ENABLE                    24:24
#define NV097_SET_COMBINER_COLOR_OCW_AB_ALPHA_ONLY                      21:21
#define NV097_SET_COMBINER_COLOR_OCW_CD_ALPHA_ONLY                      20:20

typedef struct _GLOBALDATA {
    struct {
        DWORD dwNVClasses;
    } nvD3DPerfData;
} GLOBALDATA;
extern GLOBALDATA* pDriverData;

typedef struct _VSHADERREGISTER {
    float x;
    float y;
    float z;
    float w;
} VSHADERREGISTER, *PVSHADERREGISTER;

// vertex shader constants
typedef struct _VertexShaderConsts {
    // The zero padding is here to handle the constant addressing offsets in software
    // efficiently.  Rather than performing a bounds check upon each memory
    VSHADERREGISTER zeroPadding[128];
    VSHADERREGISTER vertexShaderConstants[NV_CAPS_MAX_VSHADER_CONSTS];
    VSHADERREGISTER zeroPadding2[128];
    VSHADERREGISTER vertexShaderTemp[NV_CAPS_MAX_VSHADER_TEMPS];
} VertexShaderConsts;

typedef struct NVD3DCONTEXT {
    struct {
        struct {
            void set1(DWORD, DWORD) {};
            void set4(DWORD, DWORD, DWORD, DWORD, DWORD) {};
            void set4f(DWORD, FLOAT, FLOAT, FLOAT, FLOAT) {};
        } kelvin;
    } hwState;
    VertexShaderConsts* pVShaderConsts;
} NVD3DCONTEXT, *PNVD3DCONTEXT;

class CNvObject;
class CTexture;

#include "nvPShad.h"
#include "nvKelvinProgram.h"

#endif // _NVPRECOMP_H


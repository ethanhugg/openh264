#include <gtest/gtest.h>
#include "codec_def.h"
#include "mc.h"
#include "cpu.h"
using namespace WelsDec;

#define LUMA_FUNC(funcs, src, srcstride, dst, dststride, mvx, mvy, width, height) \
  sMcFunc.pMcLumaFunc (src, srcstride, dst, dststride, mvx, mvy, width, height)

#define CHROMA_FUNC sMcFunc.pMcChromaFunc

#include "mc_test_common.h"

DEF_MCCOPYTEST (, 2, 2)
DEF_MCCOPYTEST (, 2, 4)
DEF_MCCOPYTEST (, 4, 2)
DEF_MCCOPYTEST (, 4, 4)
DEF_MCCOPYTEST (, 4, 8)
DEF_MCCOPYTEST (, 8, 4)
DEF_MCCOPYTEST (, 8, 8)
DEF_MCCOPYTEST (, 16, 8)
DEF_MCCOPYTEST (, 8, 16)
DEF_MCCOPYTEST (, 16, 16)

DEF_LUMA_MCTEST (, 4, 4)
DEF_LUMA_MCTEST (, 4, 8)
DEF_LUMA_MCTEST (, 8, 4)
DEF_LUMA_MCTEST (, 8, 8)
DEF_LUMA_MCTEST (, 16, 8)
DEF_LUMA_MCTEST (, 8, 16)
DEF_LUMA_MCTEST (, 16, 16)

DEF_CHROMA_MCTEST (, 2, 2)
DEF_CHROMA_MCTEST (, 2, 4)
DEF_CHROMA_MCTEST (, 4, 2)
DEF_CHROMA_MCTEST (, 4, 4)
DEF_CHROMA_MCTEST (, 4, 8)
DEF_CHROMA_MCTEST (, 8, 4)
DEF_CHROMA_MCTEST (, 8, 8)

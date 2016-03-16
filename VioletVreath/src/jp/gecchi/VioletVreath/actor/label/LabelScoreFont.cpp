#include "LabelScoreFont.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardSetModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardSetEffect.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

int LabelScoreFont::blur_no_[600] = {
    3,0,2,1,0,0,0,3,0,3, 0,0,2,2,1,0,3,1,2,0, 1,1,0,1,1,2,3,3,1,1, 1,2,3,2,0,1,0,2,3,0, 2,3,2,1,0,3,1,2,2,2, 0,2,3,2,3,1,0,2,0,0,
    0,0,3,1,3,0,0,3,3,1, 3,0,3,1,1,2,3,3,0,1, 3,2,3,1,2,0,2,1,0,0, 1,3,1,1,0,0,2,2,0,0, 1,0,3,0,0,3,0,3,2,2, 2,2,3,3,1,0,1,3,0,0,
    3,2,1,2,2,1,3,1,1,0, 1,2,1,0,2,0,1,3,3,2, 1,1,2,2,3,0,1,3,0,1, 2,0,2,1,2,1,2,3,0,1, 2,1,1,0,0,1,1,2,3,2, 2,0,2,1,0,1,3,2,1,1,
    1,1,3,3,2,2,3,1,1,2, 3,3,2,2,3,2,3,3,3,3, 2,0,2,1,3,2,0,3,2,0, 0,2,1,2,0,2,3,3,3,0, 1,0,1,1,2,3,3,1,3,2, 1,1,3,1,1,1,3,2,1,1,
    2,2,0,1,2,0,1,0,3,3, 1,2,3,0,0,1,1,3,1,3, 0,2,2,3,1,1,3,1,3,1, 0,0,0,3,0,3,1,1,1,2, 1,2,2,0,1,0,1,1,0,3, 0,2,3,3,0,2,0,3,2,3,
    3,3,2,2,2,0,0,2,3,2, 0,2,3,0,0,3,3,0,1,0, 0,1,2,3,2,2,3,3,0,0, 1,2,3,1,0,2,0,3,2,3, 1,1,0,3,3,2,3,0,3,3, 0,0,3,0,0,0,2,0,2,0,
    2,1,2,2,0,0,0,2,0,1, 3,1,0,0,1,2,2,1,0,3, 0,1,2,0,2,1,1,3,3,1, 2,0,1,3,3,3,1,0,3,2, 1,1,1,1,2,2,1,1,2,1, 2,1,1,1,3,3,0,2,1,1,
    3,0,3,0,3,0,2,1,1,3, 1,0,0,0,0,2,2,2,3,2, 0,2,3,1,2,1,3,0,2,2, 0,1,1,0,0,1,3,0,0,0, 1,1,2,1,2,2,1,1,1,2, 3,1,1,1,2,1,0,3,3,1,
    1,1,3,3,2,3,3,3,1,0, 2,0,1,2,2,3,3,3,0,0, 2,1,3,0,3,0,2,0,3,0, 3,1,1,3,3,0,2,0,2,3, 3,3,1,3,3,2,1,1,3,0, 3,1,0,1,2,1,3,1,0,3,
    0,0,0,3,2,0,0,1,2,1, 2,0,1,3,0,0,3,2,2,3, 2,2,2,2,2,0,0,1,2,3, 1,2,3,2,0,0,3,2,3,0, 1,3,0,2,3,1,3,0,1,2, 3,3,3,2,2,1,2,0,1,3
};
int LabelScoreFont::bn_ = 0;
LabelScoreFont::LabelScoreFont(const char* prm_name) :
        FontBoardActor(prm_name, "ScoreFont")
{
    _class_name = "LabelScoreFont";
    _chr_ptn_zero = (int)('+');
    num_pno_ = 16;

    for (int i = 0; i < 4; i++) {
        _aWidthPx['0'+(i*num_pno_)] = 18;
        _aWidthPx['1'+(i*num_pno_)] = 18;
        _aWidthPx['2'+(i*num_pno_)] = 18;
        _aWidthPx['3'+(i*num_pno_)] = 18;
        _aWidthPx['4'+(i*num_pno_)] = 18;
        _aWidthPx['5'+(i*num_pno_)] = 18;
        _aWidthPx['6'+(i*num_pno_)] = 18;
        _aWidthPx['7'+(i*num_pno_)] = 18;
        _aWidthPx['8'+(i*num_pno_)] = 18;
        _aWidthPx['9'+(i*num_pno_)] = 18;
    }
//    _chr_width_px = _chr_width_px * 0.6;
//    +   ,   -   .   /   0   1   2
//    3   4   5   6   7   8   9   :
//    +   ,   -   .   /   0   1   2
//    3   4   5   6   7   8   9   :
//    +   ,   -   .   /   0   1   2
//    3   4   5   6   7   8   9   :
//    +   ,   -   .   /   0   1   2
//    3   4   5   6   7   8   9   :
    bk_draw_string_ = new int[256];
}

void LabelScoreFont::processBehavior() {

}

void LabelScoreFont::processPreDraw() {
    FontBoardActor::processPreDraw();

    _draw_string = bk_draw_string_;
    for (int p = 0; p < _len; p++) {
        _draw_string[p] = _buf[p] + (LabelScoreFont::blur_no_[LabelScoreFont::bn_]*num_pno_);
        if (LabelScoreFont::bn_ == 600-1) {
            LabelScoreFont::bn_ = 0;
        } else {
            LabelScoreFont::bn_++;
        }
    }
    _draw_string[_len] = (int)('\0');

    prepare2();
}

void LabelScoreFont::processAfterDraw()  {
    FontBoardActor::processAfterDraw();
    _draw_string = _buf;
}

LabelScoreFont::~LabelScoreFont() {
    GGAF_DELETEARR(bk_draw_string_);
}


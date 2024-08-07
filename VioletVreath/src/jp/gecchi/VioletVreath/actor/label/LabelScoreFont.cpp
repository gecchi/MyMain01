#include "LabelScoreFont.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/BoardSetModel.h"
#include "jp/ggaf/dx/effect/BoardSetEffect.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"



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
    num_pno_ = 16;

    setPatternZeroChr('+');
    setBaseChrWidth(_chr_base_width_px*0.6);
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


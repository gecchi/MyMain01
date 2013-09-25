#include "stdafx.h"
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
        StringBoardActor(prm_name, "ScoreFont")
{
    _class_name = "LabelScoreFont";
    _chr_ptn_zero = (int)('+');
    num_pno_ = 16;
    _chr_width_px = _chr_width_px * 0.6;
//    +   ,   -   .   /   0   1   2
//    3   4   5   6   7   8   9   :
//    +   ,   -   .   /   0   1   2
//    3   4   5   6   7   8   9   :
//    +   ,   -   .   /   0   1   2
//    3   4   5   6   7   8   9   :
//    +   ,   -   .   /   0   1   2
//    3   4   5   6   7   8   9   :

}

void LabelScoreFont::processBehavior() {
}
void LabelScoreFont::processDraw() {
    if (_len == 0) {
        return;
    }
    GgafDxBoardSetEffect* pBoardSetEffect = _pBoardSetEffect;
    ID3DXEffect* pID3DXEffect = pBoardSetEffect->_pID3DXEffect;
    GgafDxBoardSetModel* pBoardSetModel = _pBoardSetModel;
    HRESULT hr;
    pixcoord y = C_PX(_Y);
    hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_Y[0], y);
    checkDxException(hr, D3D_OK, "LabelScoreFont::processDraw() SetFloat(_ah_transformed_Y) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_depth_Z[0], float(C_PX(_Z)));
    checkDxException(hr, D3D_OK, "LabelScoreFont::processDraw() SetFloat(_ah_depth_Z) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_alpha[0], _alpha); //注意：アルファは文字ごとは不可
    checkDxException(hr, D3D_OK, "LabelScoreFont::processDraw() SetFloat(_ah_alpha) に失敗しました。");

    pixcoord X = C_PX(_X);
    if (_align == ALIGN_LEFT || _align == ALIGN_CENTER) {
        int nnn = 0; // num of \n now
        pixcoord x = X - (_align == ALIGN_CENTER ? _aWidth_line_px[nnn]/2 : 0);
        float u, v;
        int pos = 0;
        int pattno = 0;
        int draw_set_cnt = 0;
        while (true) {
            if (_draw_string[pos] == '\0') {
                if (draw_set_cnt > 0) {
                    pBoardSetModel->GgafDxBoardSetModel::draw(this, draw_set_cnt);
                }
                break; //おしまい
            } else {
                pattno = _draw_string[pos] - _chr_ptn_zero; //通常文字列
            }
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_X[draw_set_cnt], float(x));
            checkDxException(hr, D3D_OK, "LabelScoreFont::processDraw() SetFloat(_ah_transformed_X) に失敗しました。");
            _pUvFlipper->getUV(pattno + (LabelScoreFont::blur_no_[LabelScoreFont::bn_]*num_pno_), u, v); //(bn_*num_pno_)ニキシー光のブレのアニメーション
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_u[draw_set_cnt], u);
            checkDxException(hr, D3D_OK, "LabelScoreFont::processDraw() SetFloat(_h_offset_u) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_v[draw_set_cnt], v);
            checkDxException(hr, D3D_OK, "LabelScoreFont::processDraw() SetFloat(_h_offset_v) に失敗しました。");
            draw_set_cnt++;
            if (draw_set_cnt == pBoardSetModel->_set_num) {
                pBoardSetModel->GgafDxBoardSetModel::draw(this, draw_set_cnt);
                draw_set_cnt = 0;
            }
            pos++;

            x += _chr_width_px;
            if (LabelScoreFont::bn_ == 600-1) {
                LabelScoreFont::bn_ = 0;
            } else {
                LabelScoreFont::bn_++;
            }
        }
    } else if (_align == ALIGN_RIGHT) {
        pixcoord x = X - (int)(_pBoardSetModel->_fSize_BoardSetModelWidthPx);;
        float u, v;
        int pos = _len-1;
        int pattno = 0;
        int draw_set_cnt = 0;
        while (true) {
            if (pos == -1) {
                if (draw_set_cnt > 0) {
                    pBoardSetModel->GgafDxBoardSetModel::draw(this, draw_set_cnt);
                }
                break;
            } else {
                pattno = _draw_string[pos] - _chr_ptn_zero; //通常文字列
            }

            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_X[draw_set_cnt], float(x));
            checkDxException(hr, D3D_OK, "LabelScoreFont::processDraw() SetFloat(_ah_transformed_X) に失敗しました。");
            _pUvFlipper->getUV(pattno + (LabelScoreFont::blur_no_[LabelScoreFont::bn_]*num_pno_), u, v);
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_u[draw_set_cnt], u);
            checkDxException(hr, D3D_OK, "LabelScoreFont::processDraw() SetFloat(_h_offset_u) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_v[draw_set_cnt], v);
            checkDxException(hr, D3D_OK, "LabelScoreFont::processDraw() SetFloat(_h_offset_v) に失敗しました。");
            draw_set_cnt++;
            if (draw_set_cnt == pBoardSetModel->_set_num) {
                pBoardSetModel->GgafDxBoardSetModel::draw(this, draw_set_cnt);
                draw_set_cnt = 0;
            }

            pos--;

            x -= _chr_width_px;
            if (LabelScoreFont::bn_ == 600-1) {
                  LabelScoreFont::bn_ = 0;
              } else {
                  LabelScoreFont::bn_++;
              }
        }
    }
}

LabelScoreFont::~LabelScoreFont() {
}


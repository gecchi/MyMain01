#include "jp/ggaf/dxcore/actor/ex/GgafDxStringSpriteActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/model/GgafDxSpriteSetModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxSpriteSetEffect.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;


GgafDxStringSpriteActor::GgafDxStringSpriteActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
        GgafDxSpriteSetActor(prm_name, prm_model, "StringSpriteEffect", "StringSpriteTechnique", prm_pStat, nullptr) {

    _class_name = "GgafDxStringSpriteActor";
    _max_len = 8; //最初はバッファは8文字
    _chr_ptn_zero = (int)(' ');
    _len = 0;
    _buf = NEW int[_max_len];
    _buf[0] = (int)('\0');
    _draw_string = _buf;
    //デフォルトの１文字の幅(px)設定
    for (int i = 0; i < 256; i++) {
        _aWidthPx[i] = (int)(_pSpriteSetModel->_model_width_px);
        _aWidth_line_px[i] = 0;
    }
    _chr_width_px = (int)(_pSpriteSetModel->_model_width_px); //１文字の幅(px)
    _chr_height_px = (int)(_pSpriteSetModel->_model_height_px); //１文字の高さ(px)
    _nn = 0;
}

void GgafDxStringSpriteActor::chengeBufferLen(int prm_max_len) {
    _max_len = 8*((prm_max_len+8)/8); //直近８の倍数に切り上げ
    GGAF_DELETEARR(_buf);
    _buf = NEW int[_max_len];
    _buf[0] = (int)('\0');
}

void GgafDxStringSpriteActor::onCreateModel() {

}

void GgafDxStringSpriteActor::update(coord X, coord Y, const char* prm_str) {
    update(prm_str);
    position(X, Y);
}

void GgafDxStringSpriteActor::update(coord X, coord Y, coord Z, const char* prm_str) {
    update(prm_str);
    position(X, Y, Z);
}

void GgafDxStringSpriteActor::update(const char* prm_str) {
    _len = strlen(prm_str);
    if (_len+1 > _max_len) {
        chengeBufferLen(_len+1); //バッファ拡張
    }
    onUpdate(); //コールバック
    _draw_string = _buf;
    _aWidth_line_px[0] = 0;
    int nn = 0;
    pixcoord max_len_px = 0;
    const int len = _len;
    for (int i = 0; i < len+1; i++) {
        _draw_string[i] = prm_str[i]; //保持
        if (prm_str[i] == '\n') {
            if (max_len_px < _aWidth_line_px[_nn]) {
                max_len_px = _aWidth_line_px[_nn];
            }
            nn++;
            _aWidth_line_px[nn] = 0;
            continue;
        }
        if (prm_str[i] == '\0') {
            if (max_len_px < _aWidth_line_px[_nn]) {
                max_len_px = _aWidth_line_px[_nn];
            }
            nn++;
            _aWidth_line_px[nn] = 0;
            break;
        }
#ifdef MY_DEBUG
        if (nn > _max_len) {
            throwGgafCriticalException("GgafDxStringBoardActor::update 文字列の改行数が"<<_max_len<<"個を超えました。name="<<getName()<<" prm_str="<<prm_str);
        }
        if (0 > _draw_string[i] || _draw_string[i] > 256) {
            throwGgafCriticalException("GgafDxStringBoardActor::update 範囲外の扱えない文字種がありました _draw_string["<<i<<"]="<<_draw_string[i]<<"。 0〜255の範囲にして下さい。name="<<getName()<<" prm_str="<<prm_str);
        }
#endif
        _aWidth_line_px[nn] += _aWidthPx[_draw_string[i]];
    }
    _nn = nn;
    if (max_len_px > _chr_width_px) {
        setBoundingSphereRadiusRate(2*max_len_px/_chr_width_px);
    }
}

void GgafDxStringSpriteActor::update(coord X, coord Y, const char* prm_str, GgafDxAlign prm_align,
                                     GgafDxValign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    position(X, Y);
}

void GgafDxStringSpriteActor::update(coord X, coord Y, coord Z, const char* prm_str, GgafDxAlign prm_align,
                                     GgafDxValign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    position(X, Y, Z);
}

void GgafDxStringSpriteActor::update(const char* prm_str, GgafDxAlign prm_align, GgafDxValign prm_valign) {
    update(prm_str);
    setAlign(prm_align, prm_valign);
}

void GgafDxStringSpriteActor::processDraw() {
    if (_len == 0) {
        return;
    }
    GgafDxSpriteSetModel* pSpriteSetModel = _pSpriteSetModel;
    GgafDxSpriteSetEffect* pSpriteSetEffect = _pSpriteSetEffect;
    ID3DXEffect* pID3DXEffect = pSpriteSetEffect->_pID3DXEffect;
    HRESULT hr;
    pixcoord dy = 0;
    if (_align == ALIGN_LEFT || _align == ALIGN_CENTER) {
        if (_valign == VALIGN_BOTTOM) {
            dy = dy + (_chr_height_px*_nn) - (_chr_height_px/2);
        } else if (_valign == VALIGN_MIDDLE) {
            dy = dy + (_chr_height_px*_nn/2) - (_chr_height_px/2);
        } else { //VALIGN_TOP
            dy = dy - (_chr_height_px/2);
        }
    } else { //ALIGN_RIGHT
        if (_valign == VALIGN_BOTTOM) {
            dy = dy + (_chr_height_px/2);
        } else if (_valign == VALIGN_MIDDLE) {
            dy = dy - (_chr_height_px*_nn/2) + (_chr_height_px/2);
        } else { //VALIGN_TOP
            dy = dy - (_chr_height_px*_nn) + (_chr_height_px/2);
        }
    }
    hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_alpha[0], _alpha); //注意：アルファは文字ごとは不可
    checkDxException(hr, D3D_OK, "GgafDxStringSpriteActor::processDraw() SetFloat(_ah_alpha) に失敗しました。");
    hr = pID3DXEffect->SetMatrix(pSpriteSetEffect->_ah_matWorld[0], &_matWorld);
    checkDxException(hr, D3D_OK, "GgafDxStringSpriteActor::processDraw() SetMatrix(_ah_matWorld) に失敗しました。");

    if (_align == ALIGN_LEFT || _align == ALIGN_CENTER) {
        int nnn = 0; // num of \n now
        int pos = 0;
        pixcoord dx = (_align == ALIGN_CENTER ? -_aWidth_line_px[nnn] / 2 : 0) +
                        (_aWidthPx[_draw_string[pos]] / 2);
        pixcoord dx_tmp = dx;
        float u, v;
        int pattno = 0;
        int draw_set_cnt = 0;
        while (true) {
            if (_draw_string[pos] == (int)('\0')) {
                if (draw_set_cnt > 0) {
                    pSpriteSetModel->GgafDxSpriteSetModel::draw(this, draw_set_cnt);
                }
                break; //おしまい
            } else if (_draw_string[pos] == (int)('\n')) {
                nnn++;
                pos++;

                dx = (_align == ALIGN_CENTER ? -_aWidth_line_px[nnn] / 2 : 0) +
                        (_aWidthPx[_draw_string[pos]] / 2);
                dx_tmp = dx;
                dy -= _chr_height_px;

                continue;
            } else {
                pattno = _draw_string[pos] - _chr_ptn_zero; //通常文字列
            }
            //プロポーショナルな幅計算
            int w = ((_chr_width_px - _aWidthPx[_draw_string[pos]]) / 2);
            dx = dx_tmp - w;
            dx_tmp = dx + _chr_width_px - w;

            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_x[draw_set_cnt], PX_DX(dx));
            checkDxException(hr, D3D_OK, "GgafDxStringSpriteActor::processDraw() SetFloat(_ah_x) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_y[draw_set_cnt], PX_DX(dy));
            checkDxException(hr, D3D_OK, "GgafDxStringSpriteActor::processDraw() SetFloat(_ah_y) に失敗しました。");
            _pUvFlipper->getUV(pattno, u, v);
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_offset_u[draw_set_cnt], u);
            checkDxException(hr, D3D_OK, "GgafDxStringSpriteActor::processDraw() SetFloat(_ah_offset_u) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_offset_v[draw_set_cnt], v);
            checkDxException(hr, D3D_OK, "GgafDxStringSpriteActor::processDraw() SetFloat(_ah_offset_v) に失敗しました。");

            draw_set_cnt++;
            if (draw_set_cnt == pSpriteSetModel->_set_num) {
                pSpriteSetModel->draw(this, draw_set_cnt);
                draw_set_cnt = 0;
            }
            pos++;
        }
    } else if (_align == ALIGN_RIGHT) {
        int pos = _len-1;
        pixcoord dx = +1*(_aWidthPx[(int)(_draw_string[pos])] / 2);
        pixcoord dx_tmp = dx;
        float u, v;
        int pattno = 0;
        int draw_set_cnt = 0;
        int w;
        while (true) {
            if (pos == -1) {
                if (draw_set_cnt > 0) {
                    pSpriteSetModel->draw(this, draw_set_cnt);
                }
                break;
            } else if (_draw_string[pos] == (int)('\n')) {
                pos--;

                dx = +1*(_aWidthPx[(int)(_draw_string[pos])] / 2);
                dx_tmp = dx;
                dy += _chr_height_px;

                continue;
            } else {
                pattno = _draw_string[pos] - _chr_ptn_zero; //通常文字列
            }
            //プロポーショナルな幅計算
            w = ((_chr_width_px - _aWidthPx[_draw_string[pos]]) / 2);
            dx = dx_tmp - (w + _aWidthPx[_draw_string[pos]]);
            dx_tmp = dx + w;
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_x[draw_set_cnt], PX_DX(dx));
            checkDxException(hr, D3D_OK, "GgafDxStringSpriteActor::processDraw() SetFloat(_ah_x) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_y[draw_set_cnt], PX_DX(dy));
            checkDxException(hr, D3D_OK, "GgafDxStringSpriteActor::processDraw() SetFloat(_ah_y) に失敗しました。");
            _pUvFlipper->getUV(pattno, u, v);
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_offset_u[draw_set_cnt], u);
            checkDxException(hr, D3D_OK, "GgafDxStringSpriteActor::processDraw() SetFloat(_ah_offset_u) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_offset_v[draw_set_cnt], v);
            checkDxException(hr, D3D_OK, "GgafDxStringSpriteActor::processDraw() SetFloat(_ah_offset_v) に失敗しました。");

            draw_set_cnt++;
            if (draw_set_cnt == pSpriteSetModel->_set_num) {
                pSpriteSetModel->draw(this, draw_set_cnt);
                draw_set_cnt = 0;
            }
            pos--;
        }
    }
}

GgafDxStringSpriteActor::~GgafDxStringSpriteActor() {
    GGAF_DELETEARR(_buf);
}

#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxStringBoardActor::GgafDxStringBoardActor(const char* prm_name, const char* prm_model) :
        GgafDxBoardSetActor(prm_name, prm_model, "StringBoardEffect", "StringBoardTechnique") {

    _class_name = "GgafDxStringBoardActor";
    _draw_string = NULL;
    _len = 0;
    _buf = NEW char[1024];
    _buf[0] = '\0';
    //デフォルトの１文字の幅(px)設定
    for (int i = 0; i < 256; i++) {
        _aWidthPx[i] = (int)(_pBoardSetModel->_fSize_BoardSetModelWidthPx);
        _aWidth_line_px[i] = 0;
    }
    _chr_width_px = (int)(_pBoardSetModel->_fSize_BoardSetModelWidthPx); //１文字の幅(px)
    _chr_height_px = (int)(_pBoardSetModel->_fSize_BoardSetModelHeightPx); //１文字の高さ(px)
    _nn = 0;
}

void GgafDxStringBoardActor::onCreateModel() {

}

void GgafDxStringBoardActor::update(coord X, coord Y, const char* prm_str) {
    update(prm_str);
    locate(X, Y);
}

void GgafDxStringBoardActor::update(coord X, coord Y, char* prm_str) {
    update(prm_str);
    locate(X, Y);
}

void GgafDxStringBoardActor::update(coord X, coord Y, coord Z, const char* prm_str) {
    update(prm_str);
    locate(X, Y, Z);
}

void GgafDxStringBoardActor::update(coord X, coord Y, coord Z, char* prm_str) {
    update(prm_str);
    locate(X, Y, Z);
}

void GgafDxStringBoardActor::update(const char* prm_str) {
    if (prm_str == _draw_string) {
        return;
    }
    _len = strlen(prm_str);
#ifdef MY_DEBUG
    if (_len+1 > 1024 - 1) {
        throwGgafCriticalException("GgafDxStringBoardActor::update 引数文字列数が範囲外です。name="<<getName());
    }
#endif
    _draw_string = _buf;
    _aWidth_line_px[0] = 0;
    _nn = 0;
    for (int i = 0; i < _len+1; i++) {
        _draw_string[i] = prm_str[i]; //保持
        if (prm_str[i] == '\n') {
            _nn++;
            continue;
        }
        if (prm_str[i] == '\0') {
            _nn++;
            break;
        }
#ifdef MY_DEBUG
        if (_nn > 256) {
            throwGgafCriticalException("GgafDxStringBoardActor::update 文字列の改行数が256個を超えました。name="<<getName());
        }
#endif
        _aWidth_line_px[_nn] += _aWidthPx[_draw_string[i]];
    }
}

void GgafDxStringBoardActor::update(char* prm_str) {
    _len = strlen(prm_str);
#ifdef MY_DEBUG
    if (_len+1 > 1024 - 1) {
        throwGgafCriticalException("GgafDxStringBoardActor::update 引数文字列数が範囲外です。name="<<getName());
    }
#endif
    _draw_string = _buf;
    _aWidth_line_px[0] = 0;
    _nn = 0;
    for (int i = 0; i < _len+1; i++) {
        _draw_string[i] = prm_str[i]; //保持
        if (prm_str[i] == '\n') {
            _nn++;
            continue;
        }
        if (prm_str[i] == '\0') {
            _nn++;
            break;
        }
#ifdef MY_DEBUG
        if (_nn > 256) {
            throwGgafCriticalException("GgafDxStringBoardActor::update 文字列の改行数が256個を超えました。name="<<getName());
        }
#endif
        _aWidth_line_px[_nn] += _aWidthPx[_draw_string[i]];
    }
}

void GgafDxStringBoardActor::update(coord X, coord Y, const char* prm_str, GgafDxAlign prm_align,
                                    GgafDxValign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    locate(X, Y);
}

void GgafDxStringBoardActor::update(coord X, coord Y, char* prm_str, GgafDxAlign prm_align, GgafDxValign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    locate(X, Y);
}

void GgafDxStringBoardActor::update(coord X, coord Y, coord Z, const char* prm_str, GgafDxAlign prm_align,
                                    GgafDxValign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    locate(X, Y, Z);
}

void GgafDxStringBoardActor::update(coord X, coord Y, coord Z, char* prm_str, GgafDxAlign prm_align,
                                    GgafDxValign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    locate(X, Y, Z);
}

void GgafDxStringBoardActor::update(const char* prm_str, GgafDxAlign prm_align, GgafDxValign prm_valign) {
    update(prm_str);
    setAlign(prm_align, prm_valign);
}

void GgafDxStringBoardActor::update(char* prm_str, GgafDxAlign prm_align, GgafDxValign prm_valign) {
    update(prm_str);
    setAlign(prm_align, prm_valign);
}

void GgafDxStringBoardActor::processSettlementBehavior() {
}

void GgafDxStringBoardActor::processDraw() {
    if (_len == 0) {
        return;
    }
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    HRESULT hr;
    pixcoord y = C_PX(_Y);
    if (_align == ALIGN_LEFT || _align == ALIGN_CENTER) {
        if (_valign == VALIGN_BOTTOM) {
            y = y - (_chr_height_px*_nn);
        } else if (_valign == VALIGN_MIDDLE) {
            y = y - (_chr_height_px*_nn/2);
        } else {
            //VALIGN_TOP
        }
    } else {
        //ALIGN_RIGHT
        if (_valign == VALIGN_BOTTOM) {
            y = y + 0 - _chr_height_px;
        } else if (_valign == VALIGN_MIDDLE) {
            y = y + ((_chr_height_px*_nn/2) - _chr_height_px);
        } else {
            //VALIGN_TOP
            y = y + ((_chr_height_px*_nn) - _chr_height_px);
        }
    }
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_Y[0], y);
    checkDxException(hr, D3D_OK, "GgafDxStringBoardActor::processDraw() SetFloat(_ah_transformed_Y) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_depth_Z[0], float(C_PX(_Z)));
    checkDxException(hr, D3D_OK, "GgafDxStringBoardActor::processDraw() SetFloat(_ah_depth_Z) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_alpha[0], _alpha); //注意：アルファは文字ごとは不可
    checkDxException(hr, D3D_OK, "GgafDxStringBoardActor::processDraw() SetFloat(_ah_alpha) に失敗しました。");

    if (_align == ALIGN_LEFT || _align == ALIGN_CENTER) {
        int nnn = 0; // num of \n now
        pixcoord x = C_PX(_X) - (_align == ALIGN_CENTER ? _aWidth_line_px[nnn]/2 : 0);
        pixcoord x_tmp = x;
        float u, v;
        int strindex = 0;
        int pattno = 0;
        int draw_set_cnt = 0;
        while (true) {
            if (_draw_string[strindex] == '\0') {
                if (draw_set_cnt > 0) {
                    _pBoardSetModel->draw(this, draw_set_cnt);
                }
                break; //おしまい
            } else if (_draw_string[strindex] == '\n') {
                if (draw_set_cnt > 0) {
                    _pBoardSetModel->draw(this, draw_set_cnt);//改行はそこまで一度描画(Y座標を配列保持してないため)
                }
                draw_set_cnt = 0;

                nnn++;
                x = C_PX(_X) - (_align == ALIGN_CENTER ? _aWidth_line_px[nnn]/2 : 0);
                x_tmp = x;
                y += _chr_height_px;
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_Y[0], y);
                checkDxException(hr, D3D_OK, "GgafDxStringBoardActor::processDraw() SetFloat(_ah_transformed_Y) に失敗しました。");

                strindex++;
                continue;
            }

            if (_draw_string[strindex] - ' ' > '_' || _draw_string[strindex] - ' ' < 0) {
                pattno = '?' - ' '; //範囲外は"?"を表示
            } else {
                pattno = _draw_string[strindex] - ' '; //通常文字列
            }
            //プロポーショナルな幅計算
            int w = ((_chr_width_px - _aWidthPx[(unsigned char)(_draw_string[strindex])]) / 2);
            x = x_tmp - w;
            x_tmp = x + _chr_width_px - w;
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_X[draw_set_cnt], float(x));
            checkDxException(hr, D3D_OK,
                             "GgafDxStringBoardActor::processDraw() SetFloat(_ah_transformed_X) に失敗しました。");
            _pUvFlipper->getUV(pattno, u, v);
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_u[draw_set_cnt], u);
            checkDxException(hr, D3D_OK, "GgafDxStringBoardActor::processDraw() SetFloat(_h_offset_u) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_v[draw_set_cnt], v);
            checkDxException(hr, D3D_OK, "GgafDxStringBoardActor::processDraw() SetFloat(_h_offset_v) に失敗しました。");
            draw_set_cnt++;
            if (draw_set_cnt == _pBoardSetModel->_set_num) {
                _pBoardSetModel->draw(this, draw_set_cnt);
                draw_set_cnt = 0;
            }
            strindex++;
        }
    } else if (_align == ALIGN_RIGHT) {
        pixcoord x = C_PX(_X);
        pixcoord x_tmp = x;
        float u, v;
        int strindex = _len-1;
        int pattno = 0;
        int draw_set_cnt = 0;
        while (true) {
            if (strindex == -1) {
                if (draw_set_cnt > 0) {
                    _pBoardSetModel->draw(this, draw_set_cnt);
                }
                break;
            } else if (_draw_string[strindex] == '\n') {
                if (draw_set_cnt > 0) {
                    _pBoardSetModel->draw(this, draw_set_cnt); //改行はそこまで一度描画(Y座標を配列保持してないため)
                }
                draw_set_cnt = 0;

                x = C_PX(_X);
                x_tmp = x;
                y -= _chr_height_px;
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_Y[0], y);
                checkDxException(hr, D3D_OK, "GgafDxStringBoardActor::processDraw() SetFloat(_ah_transformed_Y) に失敗しました。");

                strindex--;
                continue;
            } else if (_draw_string[strindex] - ' ' > '_' || _draw_string[strindex] - ' ' < 0) {
                pattno = '?' - ' '; //範囲外は"?"を表示
            } else {
                pattno = _draw_string[strindex] - ' '; //通常文字列
            }
            //プロポーショナルな幅計算
            int w = ((_chr_width_px - _aWidthPx[(unsigned char)(_draw_string[strindex])]) / 2);
            x = x_tmp - (w + _aWidthPx[(unsigned char)(_draw_string[strindex])]);
            x_tmp = x + w;
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_X[draw_set_cnt], float(x));
            checkDxException(hr, D3D_OK, "GgafDxStringBoardActor::processDraw() SetFloat(_ah_transformed_X) に失敗しました。");
            _pUvFlipper->getUV(pattno, u, v);
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_u[draw_set_cnt], u);
            checkDxException(hr, D3D_OK, "GgafDxStringBoardActor::processDraw() SetFloat(_h_offset_u) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_v[draw_set_cnt], v);
            checkDxException(hr, D3D_OK, "GgafDxStringBoardActor::processDraw() SetFloat(_h_offset_v) に失敗しました。");
            draw_set_cnt++;
            if (draw_set_cnt == _pBoardSetModel->_set_num) {
                _pBoardSetModel->draw(this, draw_set_cnt);
                draw_set_cnt = 0;
            }

            strindex--;
        }
    }
}

GgafDxStringBoardActor::~GgafDxStringBoardActor() {
    DELETE_IMPOSSIBLE_NULL(_buf);
}


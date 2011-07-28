#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9StringBoardActor::GgafDx9StringBoardActor(const char* prm_name, const char* prm_model)
  : GgafDx9BoardSetActor(prm_name, prm_model, "StringBoardEffect", "StringBoardTechnique") {

    _class_name = "GgafDx9StringBoardActor";
    _draw_string = NULL;
    _len = 0;
    _buf = NEW char[1024];
    _buf[0] = '\0';
    //デフォルトの１文字の幅(px)設定
    for (int i = 0; i < 256; i++) {
        _aWidthPx[i] = (int)(_pBoardSetModel->_fSize_BoardSetModelWidthPx);
    }
    _chr_width_px = (int)(_pBoardSetModel->_fSize_BoardSetModelWidthPx); //１文字の幅(px)
    _align = ALIGN_LEFT;
    _X_offset_align = 0;
    _width_len_px = 0;
}

void GgafDx9StringBoardActor::onCreateModel() {

}


void GgafDx9StringBoardActor::update(coord X, coord Y, const char* prm_str, GgafDx9StringAlign prm_align) {
    update(prm_str, prm_align);
    locate(X, Y);
}

void GgafDx9StringBoardActor::update(coord X, coord Y, char* prm_str, GgafDx9StringAlign prm_align) {
    update(prm_str, prm_align);
    locate(X, Y);
}

void GgafDx9StringBoardActor::update(coord X, coord Y, coord Z, const char* prm_str, GgafDx9StringAlign prm_align) {
    update(prm_str, prm_align);
    locate(X, Y, Z);
}

void GgafDx9StringBoardActor::update(coord X, coord Y, coord Z, char* prm_str, GgafDx9StringAlign prm_align) {
    update(prm_str, prm_align);
    locate(X, Y, Z);
}

void GgafDx9StringBoardActor::update(const char* prm_str, GgafDx9StringAlign prm_align) {
    if (prm_str == _draw_string && _align == prm_align) {
        return;
    }
    _draw_string = (char*)prm_str;
    _len = strlen(prm_str);
    _len_pack_num = _len/_pBoardSetModel->_set_num;
    _remainder_len = _len%_pBoardSetModel->_set_num;
    _align = prm_align;

    if (_align == ALIGN_CENTER) {
        _width_len_px = 0;
        for (int i = 0; i < _len; i++) {
            _width_len_px += _aWidthPx[i];
        }
    }
}

void GgafDx9StringBoardActor::update(char* prm_str, GgafDx9StringAlign prm_align) {
    _draw_string = _buf;
    strcpy(_draw_string, prm_str);
    _len = strlen(prm_str);
    _len_pack_num = _len/_pBoardSetModel->_set_num;
    _remainder_len = _len%_pBoardSetModel->_set_num;
    _align = prm_align;


    if (_align == ALIGN_CENTER) {
        _width_len_px = 0;
        for (int i = 0; i < _len; i++) {
            _width_len_px += _aWidthPx[i];
        }
    }

//    if (_align == ALIGN_RIGHT) {
////        _width_len_px = 0;
////        for (int i = 0; i < _len; i++) {
////            _width_len_px += _aWidthPx[i];
////        }
////        _X_offset_align = Pix2App(-_width_len_px);
//    } else  else {
////        _X_offset_align = 0;
//    }
}


void GgafDx9StringBoardActor::processSettlementBehavior() {
}


void GgafDx9StringBoardActor::processDraw() {
    if (_len == 0) {
        return;
    }
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[0], float(App2Pix(_Y)));
    checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedY) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[0], float(App2Pix(_Z)));
    checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahDepthZ) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[0], _fAlpha); //注意：アルファは文字ごとは不可
    checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahAlpha) に失敗しました。");

    if (_align == ALIGN_LEFT || _align == ALIGN_CENTER) {
        int strindex, pattno;
        pixcoord x = App2Pix(_X) - (_width_len_px/2);
        pixcoord x_tmp = x;
        float u,v;
        for (int pack = 0; pack < _len_pack_num+(_remainder_len == 0 ? 0 : 1); pack++) {
            _draw_set_num = pack < _len_pack_num ? _pBoardSetModel->_set_num : _remainder_len;
            for (int i = 0; i < _draw_set_num; i++) {
                strindex = pack * _pBoardSetModel->_set_num + i;
                if (_draw_string[strindex] == '\0') {
                    break;
                } else if (_draw_string[strindex] - ' ' < 0) {
                    pattno = '?' - ' '; //範囲外は"?"を表示
                } else {
                    pattno = _draw_string[strindex] - ' '; //通常文字列
                }
                //プロポーショナルな幅計算
                int w = ((_chr_width_px - _aWidthPx[(unsigned char)(_draw_string[strindex])]) / 2);
                x = x_tmp - w;
                x_tmp = x + _chr_width_px - w;
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[i], float(x));
                checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedX) に失敗しました。");
                _pUvFlipper->getUV(pattno, u, v);
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[i], u);
                checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetU) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[i], v);
                checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetV) に失敗しました。");
            }
            _pBoardSetModel->draw(this, _draw_set_num);
        }
    } else if (_align == ALIGN_RIGHT) {
        int strindex, pattno;
        pixcoord x = App2Pix(_X)-_aWidthPx[_len-1];
        pixcoord x_tmp = x;
        float u,v;
        for (int pack = 0; pack < _len_pack_num+(_remainder_len == 0 ? 0 : 1); pack++) {
            _draw_set_num = pack < _len_pack_num ? _pBoardSetModel->_set_num : _remainder_len;
            for (int i = 0; i < _draw_set_num; i++) {
                strindex = _len - (pack * _pBoardSetModel->_set_num + i) - 1;
                if (_draw_string[strindex] == '\0') {
                    break;
                } else if (_draw_string[strindex] - ' ' < 0) {
                    pattno = '?' - ' '; //範囲外は"?"を表示
                } else {
                    pattno = _draw_string[strindex] - ' '; //通常文字列
                }
                //プロポーショナルな幅計算
                int w = ((_chr_width_px - _aWidthPx[(unsigned char)(_draw_string[strindex])]) / 2);
                x = x_tmp + w;
                x_tmp = x - _chr_width_px + w;
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[i], float(x));
                checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedX) に失敗しました。");
                _pUvFlipper->getUV(pattno, u, v);
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[i], u);
                checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetU) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[i], v);
                checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetV) に失敗しました。");
            }
            _pBoardSetModel->draw(this, _draw_set_num);
        }

    }
}

GgafDx9StringBoardActor::~GgafDx9StringBoardActor() {
    DELETE_IMPOSSIBLE_NULL(_buf);
}


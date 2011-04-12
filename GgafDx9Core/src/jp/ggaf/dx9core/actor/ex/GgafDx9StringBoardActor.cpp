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
    //デフォルトの１文字の幅(px)設定
    for (int i = 0; i < 256; i++) {
        _aWidthPx[i] = (int)(_pBoardSetModel->_fSize_BoardSetModelWidthPx);
    }
    _chr_width = (int)(_pBoardSetModel->_fSize_BoardSetModelWidthPx); //１文字の幅(px)
}

void GgafDx9StringBoardActor::onCreateModel() {

}


void GgafDx9StringBoardActor::update(float prm_x, float prm_y, const char* prm_str) {
    update(prm_str);
    _x = prm_x;
    _y = prm_y;
}

void GgafDx9StringBoardActor::update(float prm_x, float prm_y, char* prm_str) {
    update(prm_str);
    _x = prm_x;
    _y = prm_y;
}

void GgafDx9StringBoardActor::update(float prm_x, float prm_y, float prm_z, const char* prm_str) {
    update(prm_str);
    _x = prm_x;
    _y = prm_y;
    _z = prm_z;
}

void GgafDx9StringBoardActor::update(float prm_x, float prm_y, float prm_z, char* prm_str) {
    update(prm_str);
    _x = prm_x;
    _y = prm_y;
    _z = prm_z;

}

void GgafDx9StringBoardActor::update(const char* prm_str) {
    _draw_string = (char*)prm_str;
    _len = strlen(prm_str);
    _len_pack_num = _len/_pBoardSetModel->_set_num;
    _remainder_len = _len%_pBoardSetModel->_set_num;
}

void GgafDx9StringBoardActor::update(char* prm_str) {
    _draw_string = _buf;
    strcpy(_draw_string, prm_str);
    _len = strlen(prm_str);
    _len_pack_num = _len/_pBoardSetModel->_set_num;
    _remainder_len = _len%_pBoardSetModel->_set_num;
}

void GgafDx9StringBoardActor::update(float prm_x, float prm_y, float prm_z) {
    _x = prm_x;
    _y = prm_y;
    _z = prm_z;
}

void GgafDx9StringBoardActor::update(float prm_x, float prm_y) {
    _x = prm_x;
    _y = prm_y;
}

void GgafDx9StringBoardActor::processDraw() {
    if (_len == 0) {
        return;
    }
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    GgafDx9RectUV* pRectUV_Active;
    HRESULT hr;

    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[0], _y);
    checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedY) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[0], _z);
    checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahDepthZ) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[0], _fAlpha);
    checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahAlpha) に失敗しました。");
    int strindex;
    int x = _x;
    int x_next;
    for (int pack = 0; pack < _len_pack_num+(_remainder_len == 0 ? 0 : 1); pack++) {
        _draw_set_num = pack < _len_pack_num ? _pBoardSetModel->_set_num : _remainder_len;
        int pattno;
        for (int i = 0; i < _draw_set_num; i++) {
            strindex = pack * _pBoardSetModel->_set_num + i;
            if (_draw_string[strindex] == '\0') {
                break;
            }

            if (_draw_string[strindex] - ' ' < 0) {
                pattno = '?' - ' '; //範囲外は"?"を表示
            } else {
                pattno = _draw_string[strindex] - ' '; //通常文字列
            }

            //プロポーショナルな幅計算
            int w = ((_chr_width - _aWidthPx[(unsigned char)(_draw_string[strindex])]) / 2);
            if (strindex == 0) {
                x_next = x + w;
            } else {
                x = x_next - w;
                x_next = x + _chr_width - w;
            }
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[i], x);
            checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedX) に失敗しました。");
            pRectUV_Active = _pBoardSetModel->_paRectUV + pattno; //文字のテクスチャ
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[i], pRectUV_Active->_aUV[0].tu);
            checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetU) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[i], pRectUV_Active->_aUV[0].tv);
            checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetV) に失敗しました。");
        }
        _pBoardSetModel->draw(this, _draw_set_num);
    }
}

GgafDx9StringBoardActor::~GgafDx9StringBoardActor() {
    DELETE_IMPOSSIBLE_NULL(_buf);
}


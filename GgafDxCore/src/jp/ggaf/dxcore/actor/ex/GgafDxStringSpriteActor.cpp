#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxStringSpriteActor::GgafDxStringSpriteActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat)
  : GgafDxSpriteSetActor(prm_name,
                          prm_model,
                          "StringSpriteEffect",
                          "StringSpriteTechnique",
                          prm_pStat,
                          NULL) {

    _class_name = "GgafDxStringSpriteActor";
    _draw_string = NULL;
    _len = 0;
    _buf = NEW char[1024];
    for (int i = 0; i < 256; i++) {
        _aWidthPx[i] = _pSpriteSetModel->_fSize_SpriteSetModelWidthPx; //‚P•¶Žš‚Ì•(px)
    }
}

void GgafDxStringSpriteActor::onCreateModel() {

}


void GgafDxStringSpriteActor::update(float X, float Y, const char* prm_str) {
    update(prm_str);
    _X = X;
    _Y = Y;
}

void GgafDxStringSpriteActor::update(float X, float Y, char* prm_str) {
    update(prm_str);
    _X = X;
    _Y = Y;
}

void GgafDxStringSpriteActor::update(float X, float Y, float Z, const char* prm_str) {
    update(prm_str);
    _X = X;
    _Y = Y;
    _Z = Z;
    //_paVertex[0].Z = _Z;
    //_paVertex[1].Z = _Z;
    //_paVertex[2].Z = _Z;
    //_paVertex[3].Z = _Z;
}

void GgafDxStringSpriteActor::update(float X, float Y, float Z, char* prm_str) {
    update(prm_str);
    _X = X;
    _Y = Y;
    _Z = Z;
    //_paVertex[0].Z = _Z;
    //_paVertex[1].Z = _Z;
    //_paVertex[2].Z = _Z;
    //_paVertex[3].Z = _Z;

}

void GgafDxStringSpriteActor::update(const char* prm_str) {
    _draw_string = (char*)prm_str;
    _len = strlen(prm_str);
}

void GgafDxStringSpriteActor::update(char* prm_str) {
    _draw_string = _buf;
    strcpy(_draw_string, prm_str);
    _len = strlen(prm_str);
}

void GgafDxStringSpriteActor::processDraw() {
    if (_len == 0) {
        return;
    }
    ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pSpriteSetEffect->_pID3DXEffect;
    HRESULT hr;

    hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahAlpha[0], _fAlpha);
    checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw SetFloat(_ahAlpha) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    int len_pack_num = _len/_pSpriteSetModel->_set_num;
    int remainder_len = _len%_pSpriteSetModel->_set_num;
    int strindex;
    int X = _X;
    float u, v;
    for (int pack = 0; pack < len_pack_num+(remainder_len == 0 ? 0 : 1); pack++) {
        if (pack < len_pack_num) {
            _draw_set_num = _pSpriteSetModel->_set_num;
        } else {
            _draw_set_num = remainder_len;
        }

        for (int i = 0; i < _draw_set_num; i++) {
            strindex = pack * _pSpriteSetModel->_set_num + i;
            if (_draw_string[strindex] == '\0') {
              break;
            }
            int pattno;
            if (_draw_string[strindex] - ' ' < 0) {
                pattno = '?' - ' '; //”ÍˆÍŠO‚Í"?"
            } else {
                pattno = _draw_string[strindex] - ' '; //’Êí•¶Žš—ñ
            }
            if (strindex > 0) {
                X += _aWidthPx[(unsigned char)(_draw_string[strindex-1])];
            }

            _matWorld._41 = X;
            hr = pID3DXEffect->SetMatrix(_pSpriteSetEffect->_ah_matWorld[i], &_matWorld );
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::processDraw SetMatrix(_h_matWorld) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
            _pUvFlipper->getUV(pattno, u, v);
            hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahOffsetU[i], u);
            checkDxException(hr, D3D_OK, "GgafDxSpriteModel::draw() SetFloat(_hOffsetU) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
            hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahOffsetV[i], v);
            checkDxException(hr, D3D_OK, "GgafDxSpriteModel::draw() SetFloat(_hOffsetV) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
        }
        _pSpriteSetModel->draw(this, _draw_set_num);
    }
}

GgafDxStringSpriteActor::~GgafDxStringSpriteActor() {
    DELETE_IMPOSSIBLE_NULL(_buf);
}


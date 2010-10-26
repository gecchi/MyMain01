#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9StringSpriteActor::GgafDx9StringSpriteActor(const char* prm_name, const char* prm_model)
//: GgafDx9SpriteSetActor(prm_name, prm_model, "DefaultSpriteSetEffect", "DefaultSpriteSetTechnique") {
  : GgafDx9SpriteSetActor(prm_name,
                          prm_model,
                          "StringSpriteEffect",
                          "StringSpriteTechnique",
                          NULL) {

    _class_name = "GgafDx9StringSpriteActor";
    _draw_string = NULL;
    _len = 0;
    _buf = NEW char[1024];
    for (int i = 0; i < 256; i++) {
        _aWidthPx[i] = _pSpriteSetModel->_fSize_SpriteSetModelWidthPx; //‚P•¶Žš‚Ì•(px)
    }
}

void GgafDx9StringSpriteActor::onCreateModel() {

}


void GgafDx9StringSpriteActor::update(float prm_x, float prm_y, const char* prm_str) {
    update(prm_str);
    _X = prm_x;
    _Y = prm_y;
}

void GgafDx9StringSpriteActor::update(float prm_x, float prm_y, char* prm_str) {
    update(prm_str);
    _X = prm_x;
    _Y = prm_y;
}

void GgafDx9StringSpriteActor::update(float prm_x, float prm_y, float prm_z, const char* prm_str) {
    update(prm_str);
    _X = prm_x;
    _Y = prm_y;
    _Z = prm_z;
    //_paVertex[0].Z = _Z;
    //_paVertex[1].Z = _Z;
    //_paVertex[2].Z = _Z;
    //_paVertex[3].Z = _Z;
}

void GgafDx9StringSpriteActor::update(float prm_x, float prm_y, float prm_z, char* prm_str) {
    update(prm_str);
    _X = prm_x;
    _Y = prm_y;
    _Z = prm_z;
    //_paVertex[0].Z = _Z;
    //_paVertex[1].Z = _Z;
    //_paVertex[2].Z = _Z;
    //_paVertex[3].Z = _Z;

}

void GgafDx9StringSpriteActor::update(const char* prm_str) {
    _draw_string = (char*)prm_str;
    _len = strlen(prm_str);
}

void GgafDx9StringSpriteActor::update(char* prm_str) {
    _draw_string = _buf;
    strcpy(_draw_string, prm_str);
    _len = strlen(prm_str);
}

void GgafDx9StringSpriteActor::processDraw() {
    if (_len == 0) {
        return;
    }
    ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pSpriteSetEffect->_pID3DXEffect;
    GgafDx9RectUV* pRectUV_Active;
    HRESULT hr;

    hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahAlpha[0], _fAlpha);
    checkDxException(hr, D3D_OK, "GgafDx9SpriteSetModel::draw SetFloat(_ahAlpha) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    int len_pack_num = _len/_pSpriteSetModel->_set_num;
    int remainder_len = _len%_pSpriteSetModel->_set_num;
    int strindex;
    int X = _X;
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
                X += _aWidthPx[_draw_string[strindex-1]];
            }

            _matWorld._41 = X;
            hr = pID3DXEffect->SetMatrix(_pSpriteSetEffect->_ah_matWorld[i], &_matWorld );
            checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::processDraw SetMatrix(_h_matWorld) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");


            pRectUV_Active = _pSpriteSetModel->_paRectUV + pattno; //•¶Žš‚ÌƒeƒNƒXƒ`ƒƒ
            hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahOffsetU[i], pRectUV_Active->_aUV[0].tu);
            checkDxException(hr, D3D_OK, "GgafDx9SpriteModel::draw() SetFloat(_hOffsetU) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
            hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahOffsetV[i], pRectUV_Active->_aUV[0].tv);
            checkDxException(hr, D3D_OK, "GgafDx9SpriteModel::draw() SetFloat(_hOffsetV) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");

        }
        _pSpriteSetModel->draw(this);
    }




}

GgafDx9StringSpriteActor::~GgafDx9StringSpriteActor() {
    DELETE_IMPOSSIBLE_NULL(_buf);
}


#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteActor::GgafDx9SpriteActor(const char* prm_name,
                                       const char* prm_model_id,
                                       const char* prm_effect_id,
                                       const char* prm_technique,
                                       GgafDx9Checker* prm_pChecker) :

                                           GgafDx9DrawableActor(prm_name,
                                                                prm_model_id,
                                                                "S",
                                                                prm_effect_id,
                                                                "S",
                                                                prm_technique,
                                                                prm_pChecker) {
    _obj_class |= Obj_GgafDx9SpriteActor;
    _class_name = "GgafDx9SpriteActor";

    _pSpriteModel = (GgafDx9SpriteModel*)_pModel;
    _pSpriteEffect = (GgafDx9SpriteEffect*)_pEffect;
//    _pUvFlipper = NEW GgafDx9UvFlipper(this);
//    _pUvFlipper->forcePtnNoRange(0, _pSpriteModel->_pattno_uvflip_Max);
//    _pUvFlipper->setActivePtnNo(0);
//    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
    GgafDx9Texture* pTexture = _pSpriteModel->_papTextureCon[0]->use();
    _pUvFlipper = NEW GgafDx9UvFlipper(pTexture);
    _pUvFlipper->setRotation(_pSpriteModel->_col_texture_split,
                             _pSpriteModel->_row_texture_split
                            );
    _pUvFlipper->setActivePtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);

    _pFunc_calcRotMvWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
}

void GgafDx9SpriteActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pSpriteEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pSpriteEffect->_h_matView, &P_CAM->_matView );
//    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshEffect SetMatrix(g_matView) �Ɏ��s���܂����B");
    //(*_pFunc_calcRotMvWorldMatrix)(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pSpriteEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9SpriteActor::processDraw SetMatrix(_h_matWorld) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pSpriteEffect->_hAlpha, _fAlpha);
    checkDxException(hr, D3D_OK, "GgafDx9SpriteActor::processDraw SetFloat(_fAlpha) �Ɏ��s���܂����B");

//    // Z�o�b�t�@�𖳌���
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
//    // Z�o�b�t�@�������ݕs��
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

    _pSpriteModel->draw(this);

//    // Z�o�b�t�@��L����
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
//    // Z�o�b�t�@�������݉�
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

void GgafDx9SpriteActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //���ݒ�A���݃}�e���A����Diffuse�ȊO�֌W�Ȃ�
    _paMaterial[0].Ambient.a = _fAlpha;
    _paMaterial[0].Diffuse.a = _fAlpha;
}

void GgafDx9SpriteActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //���ݒ�A���݃}�e���A����Diffuse�ȊO�֌W�Ȃ�
    _paMaterial[0].Ambient.a = _fAlpha;
    _paMaterial[0].Diffuse.a = _fAlpha;
}


GgafDx9SpriteActor::~GgafDx9SpriteActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}

#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9PointSpriteActor::GgafDx9PointSpriteActor(const char* prm_name,
                                   const char* prm_model_id,
                                   const char* prm_effect_id,
                                   const char* prm_technique,
                                   GgafDx9Checker* prm_pChecker) :

                                       GgafDx9DrawableActor(prm_name,
                                                            prm_model_id,
                                                            "P",
                                                            prm_effect_id,
                                                            "P",
                                                            prm_technique,
                                                            prm_pChecker) {
    _actor_class |= Obj_GgafDx9PointSpriteActor;
    _class_name = "GgafDx9PointSpriteActor";
    _pPointSpriteModel = (GgafDx9PointSpriteModel*)_pGgafDx9Model;
    _pPointSpriteEffect = (GgafDx9PointSpriteEffect*)_pGgafDx9Effect;
    _pFunc_calcWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
    _pUvFlipper = NEW GgafDx9UvFlipper(this);
//    _pUvFlipper->setTextureUvRotation(_pPointSpriteModel->_texture_split_rowcol,
//                                      1.0 / _pPointSpriteModel->_texture_split_rowcol,
//                                      1.0 / _pPointSpriteModel->_texture_split_rowcol );
    _pUvFlipper->forcePtnNoRange(0, _pPointSpriteModel->_texture_split_rowcol * _pPointSpriteModel->_texture_split_rowcol - 1);
    _pUvFlipper->setPtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
}


void GgafDx9PointSpriteActor::setAlpha(float prm_fAlpha) {
    GgafDx9DrawableActor::setAlpha(prm_fAlpha);
    //GgafDx9PointSpriteActor�̓��b�V�������ݒ�i�V�F�[�_�[�ŎQ�Ƃ��邽�߁j
    _paD3DMaterial9[0].Ambient.a = _fAlpha;
    _paD3DMaterial9[0].Diffuse.a = _fAlpha;
}


void GgafDx9PointSpriteActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pPointSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pPointSpriteEffect->_hMatView, &pCAM->_vMatrixView );
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetMatrix(g_matView) �Ɏ��s���܂����B");
    //(*_pFunc_calcWorldMatrix)(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pPointSpriteEffect->_hMatWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pPointSpriteEffect->_hDist_VpPlnFront, -_fDist_VpPlnFront);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(g_hDist_VpPlnFront) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetInt(_pPointSpriteEffect->_hUvFlipPtnNo, _pUvFlipper->_pattno_uvflip_now);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetInt(_hUvFlipPtnNo) �Ɏ��s���܂����B");
    // Z�o�b�t�@�𖳌���
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    // Z�o�b�t�@�������ݕs��
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
    //�|�C���g�X�v���C�gON
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
    //�|�C���g�X�P�[��ON
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
    _pPointSpriteModel->draw(this);
    //�|�C���g�X�v���C�gOFF
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
    //�|�C���g�X�P�[��OFF
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
    // Z�o�b�t�@��L����
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Z�o�b�t�@�������݉�
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

GgafDx9PointSpriteActor::~GgafDx9PointSpriteActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}

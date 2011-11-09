#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxPointSpriteActor::GgafDxPointSpriteActor(const char* prm_name,
                                   const char* prm_model_id,
                                   const char* prm_effect_id,
                                   const char* prm_technique,
                                   GgafStatus* prm_pStat,
                                   GgafDxChecker* prm_pChecker) :

                                       GgafDxDrawableActor(prm_name,
                                                            prm_model_id,
                                                            "P",
                                                            prm_effect_id,
                                                            "P",
                                                            prm_technique,
                                                            prm_pStat,
                                                            prm_pChecker) {
    _obj_class |= Obj_GgafDxPointSpriteActor;
    _class_name = "GgafDxPointSpriteActor";
    _pPointSpriteModel = (GgafDxPointSpriteModel*)_pModel;
    _pPointSpriteEffect = (GgafDxPointSpriteEffect*)_pEffect;
    _pFunc_calcRotMvWorldMatrix = GgafDxUtil::setWorldMatrix_RxRzRyMv;

    GgafDxTexture* pTexture = _pPointSpriteModel->_papTextureCon[0]->use();
    _pUvFlipper = NEW GgafDxUvFlipper(pTexture);
    _pUvFlipper->setRotation(_pPointSpriteModel->_texture_split_rowcol,
                             _pPointSpriteModel->_texture_split_rowcol);
    _pUvFlipper->setActivePtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);


//    _pUvFlipper->setRotation(_pPointSpriteModel->_texture_split_rowcol,
//                                      1.0 / _pPointSpriteModel->_texture_split_rowcol,
//                                      1.0 / _pPointSpriteModel->_texture_split_rowcol );
//    _pUvFlipper->forcePtnNoRange(0, _pPointSpriteModel->_texture_split_rowcol * _pPointSpriteModel->_texture_split_rowcol - 1);
//    _pUvFlipper->setActivePtnNo(0);
//    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
    setZEnable(false);
    setZWriteEnable(false);
}


void GgafDxPointSpriteActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //GgafDxPointSpriteActor�̓��b�V�������ݒ�i�V�F�[�_�[�ŎQ�Ƃ��邽�߁j
    _paMaterial[0].Ambient.a = _fAlpha;
    _paMaterial[0].Diffuse.a = _fAlpha;
}

void GgafDxPointSpriteActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //GgafDxPointSpriteActor�̓��b�V�������ݒ�i�V�F�[�_�[�ŎQ�Ƃ��邽�߁j
    _paMaterial[0].Ambient.a = _fAlpha;
    _paMaterial[0].Diffuse.a = _fAlpha;
}

void GgafDxPointSpriteActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pPointSpriteEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pPointSpriteEffect->_h_matView, &P_CAM->_matView );
//    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetMatrix(g_matView) �Ɏ��s���܂����B");
    //(*_pFunc_calcRotMvWorldMatrix)(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pPointSpriteEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pPointSpriteEffect->_h_dist_VpFrontPlane, -_fDist_VpPlnFront);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(g_h_dist_VpFrontPlane) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetInt(_pPointSpriteEffect->_hUvFlipPtnNo, _pUvFlipper->_pattno_uvflip_now);
//    _TRACE_("_pUvFlipper->_pattno_uvflip_now="<<_pUvFlipper->_pattno_uvflip_now);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetInt(_hUvFlipPtnNo) �Ɏ��s���܂����B");
    // Z�o�b�t�@�𖳌���
    //�|�C���g�X�v���C�gON
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
    //�|�C���g�X�P�[��ON
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);//TRUE�̕K�v�͂Ȃ��H
    _pPointSpriteModel->draw(this);
    //�|�C���g�X�v���C�gOFF
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
    //�|�C���g�X�P�[��OFF
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
}

GgafDxPointSpriteActor::~GgafDxPointSpriteActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
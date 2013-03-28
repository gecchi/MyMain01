#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxMeshActor::GgafDxMeshActor(const char* prm_name,
                                 const char* prm_model_id,
                                 const char* prm_effect_id,
                                 const char* prm_technique,
                                 GgafStatus* prm_pStat,
                                 GgafDxChecker* prm_pChecker) :

                                     GgafDxDrawableActor(prm_name,
                                                         prm_model_id,
                                                         "X",
                                                         prm_effect_id,
                                                         "X",
                                                         prm_technique,
                                                         prm_pStat,
                                                         prm_pChecker) ,
                                            GgafDxIBumpMapActor() {
    _obj_class |= Obj_GgafDxMeshActor;
    _class_name = "GgafDxMeshActor";
    _pMeshModel = (GgafDxMeshModel*)_pModel;
    _pMeshEffect = (GgafDxMeshEffect*)_pEffect;
    _far_rate = -1.0f;
    _pFunc_calcRotMvWorldMatrix = UTIL::setWorldMatrix_RxRzRyMv;
}

GgafDxMeshActor::GgafDxMeshActor(const char* prm_name,
                                 const char* prm_model_id,
                                 const char* prm_model_type,
                                 const char* prm_effect_id,
                                 const char* prm_effect_type,
                                 const char* prm_technique,
                                 GgafStatus* prm_pStat,
                                 GgafDxChecker* prm_pChecker) :

                                   GgafDxDrawableActor(prm_name,
                                                       prm_model_id,
                                                       prm_model_type,
                                                       prm_effect_id,
                                                       prm_effect_type,
                                                       prm_technique,
                                                       prm_pStat,
                                                       prm_pChecker) ,
                                                   GgafDxIBumpMapActor() {

    _obj_class |= Obj_GgafDxMeshActor;
    _class_name = "GgafDxMeshActor";
    _pMeshModel = (GgafDxMeshModel*)_pModel;
    _pMeshEffect = (GgafDxMeshEffect*)_pEffect;
    _far_rate = -1.0f;
    _pFunc_calcRotMvWorldMatrix = UTIL::setWorldMatrix_RxRzRyMv;
}

void GgafDxMeshActor::setAlpha(float prm_alpha) {
    _alpha = prm_alpha;
    //GgafDxMeshActor�̓��b�V�������ݒ�i�V�F�[�_�[�ŎQ�Ƃ��邽�߁j
    for (DWORD i = 0; i < _pMeshModel->_num_materials; i++) {
        _paMaterial[i].Ambient.a = _alpha;
        _paMaterial[i].Diffuse.a = _alpha;
    }
}

void GgafDxMeshActor::addAlpha(float prm_alpha) {
    _alpha += prm_alpha;
    //GgafDxMeshActor�̓��b�V�������ݒ�i�V�F�[�_�[�ŎQ�Ƃ��邽�߁j
    for (DWORD i = 0; i < _pMeshModel->_num_materials; i++) {
        _paMaterial[i].Ambient.a = _alpha;
        _paMaterial[i].Diffuse.a = _alpha;
    }
}


void GgafDxMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetMatrix(_h_matWorld) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pMeshEffect->_h_far_rate, _far_rate );
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetFloat(_h_far_rate) �Ɏ��s���܂����B");
    if (_pBumpMapTextureConnection) {
        hr = GgafDxGod::_pID3DDevice9->SetTexture(2, getBumpMapTexture());
        checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetTexture() �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matInvWorld, getInvMatWorldRotMv() );
        checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetMatrix(_h_matInvWorld) �Ɏ��s���܂����B");
        //TODO:����t�s��������Ōv�Z����Ηǂ��A���A�����ł��͂₭���邽�߂�getInvMatWorldRotMv()�ő�p�B
        //getInvMatWorldRotMv() �Ȃ̂ŁA�g��k�����l������ĂȂ��B�����ƂɊg�嗦���Ⴄ�ꍇ�A�o���v�}�b�v�͂�����Ƃ��������Ȃ�B
    }
    _pMeshModel->draw(this);
}

void GgafDxMeshActor::effectBumpMapping(const char* prm_cubemap_tex, frame prm_frame) {
    setBumpMapTexture(prm_cubemap_tex);
    changeEffectTechniqueInterim("BumpMapping", prm_frame);
}

GgafDxMeshActor::~GgafDxMeshActor() {
}

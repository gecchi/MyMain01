#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxCubeMapMeshActor.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/effect/ex/GgafDxCubeMapMeshEffect.h"
#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMeshModel.h"

using namespace GgafCore;
using namespace GgafDxCore;


GgafDxCubeMapMeshActor::GgafDxCubeMapMeshActor(const char* prm_name,
                                   const char* prm_model_id,
                                   const char* prm_effect_id,
                                   const char* prm_technique,
                                   GgafStatus* prm_pStat,
                                   GgafDxChecker* prm_pChecker) :
                                           GgafDxMeshActor(prm_name,
                                                           prm_model_id,
                                                           "G",
                                                           prm_effect_id,
                                                           "G",
                                                           prm_technique,
                                                           prm_pStat,
                                                           prm_pChecker) ,
                                            GgafDxICubeMapActor() {
    _obj_class |= Obj_GgafDxCubeMapMeshActor;
    _class_name = "GgafDxCubeMapMeshActor";
    _pCubeMapMeshModel = (GgafDxCubeMapMeshModel*)_pModel;
    _pCubeMapMeshEffect = (GgafDxCubeMapMeshEffect*)_pEffect;
}

void GgafDxCubeMapMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pCubeMapMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxCubeMapMeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pCubeMapMeshEffect->_h_reflectance, getCubeMapReflectance());
    checkDxException(hr, D3D_OK, "GgafDxCubeMapMeshActor::processDraw() SetFloat(_h_reflectances) �Ɏ��s���܂����B");
    GgafDxGod::_pID3DDevice9->SetTexture(1, getCubeMapTexture());
    if (_pBumpMapTextureConnection) {
        hr = GgafDxGod::_pID3DDevice9->SetTexture(2, getBumpMapTexture());
        checkDxException(hr, D3D_OK, "GgafDxCubeMapMeshActor::processDraw() SetTexture() �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetMatrix(_pCubeMapMeshEffect->_h_matInvWorld, getInvMatWorldRotMv() );
        checkDxException(hr, D3D_OK, "GgafDxCubeMapMeshActor::processDraw() SetMatrix(_h_matInvWorld) �Ɏ��s���܂����B");
        //TODO:����t�s��������Ōv�Z����Ηǂ��A���A�����ł��͂₭���邽�߂�getInvMatWorldRotMv()�ő�p�B
        //getInvMatWorldRotMv() �Ȃ̂ŁA�g��k�����l������ĂȂ��B�����ƂɊg�嗦���Ⴄ�ꍇ�A�o���v�}�b�v�͂�����Ƃ��������Ȃ�B
    }
    _pCubeMapMeshModel->draw(this);
}

GgafDxCubeMapMeshActor::~GgafDxCubeMapMeshActor() {
}

#include "jp/ggaf/dx/actor/ex/CubeMapMeshActor.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/effect/ex/CubeMapMeshEffect.h"
#include "jp/ggaf/dx/model/ex/CubeMapMeshModel.h"


using namespace GgafDx;


CubeMapMeshActor::CubeMapMeshActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_effect_id,
                                   const char* prm_technique,
                                   CollisionChecker* prm_pChecker) :
                                           MeshActor(prm_name,
                                                     prm_model,
                                                     TYPE_CUBEMAPMESH_MODEL,
                                                     prm_effect_id,
                                                     TYPE_CUBEMAPMESH_EFFECT,
                                                     prm_technique,
                                                     prm_pChecker) ,
                                           ICubeMapActor() {
    _obj_class |= Obj_GgafDx_CubeMapMeshActor;
    _class_name = "CubeMapMeshActor";
    _pCubeMapMeshModel = (CubeMapMeshModel*)_pModel;
    _pCubeMapMeshEffect = (CubeMapMeshEffect*)_pEffect;
}

void CubeMapMeshActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pCubeMapMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pCubeMapMeshEffect->_h_reflectance, getCubeMapReflectance());
    checkDxException(hr, D3D_OK, "SetFloat(_h_reflectances) �Ɏ��s���܂����B");
    pCARETAKER->_pID3DDevice9->SetTexture(1, getCubeMapTexture());
    if (_pBumpMapTextureConnection) {
        hr = pCARETAKER->_pID3DDevice9->SetTexture(2, getBumpMapTexture());
        checkDxException(hr, D3D_OK, "SetTexture() �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetMatrix(_pCubeMapMeshEffect->_h_matInvWorld, getInvMatWorldRotMv() );
        checkDxException(hr, D3D_OK, "SetMatrix(_h_matInvWorld) �Ɏ��s���܂����B");
        //TODO:����t�s��������Ōv�Z����Ηǂ��A���A�����ł��͂₭���邽�߂�getInvMatWorldRotMv()�ő�p�B
        //getInvMatWorldRotMv() �Ȃ̂ŁA�g��k�����l������ĂȂ��B�����ƂɊg�嗦���Ⴄ�ꍇ�A�o���v�}�b�v�͂�����Ƃ��������Ȃ�B
    }
    ((MeshModel*)_pCubeMapMeshModel)->MeshModel::draw(this);
}

void CubeMapMeshActor::changeModel(int prm_model_index) {
    MeshActor::changeModel(prm_model_index);
    _pCubeMapMeshModel = (CubeMapMeshModel*)_pModel;
}

CubeMapMeshActor::~CubeMapMeshActor() {
}

#include "jp/ggaf/dx/actor/ex/CubeMapMorphMeshActor.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/effect/ex/CubeMapMorphMeshEffect.h"
#include "jp/ggaf/dx/model/ex/CubeMapMorphMeshModel.h"


using namespace GgafDx;

CubeMapMorphMeshActor::CubeMapMorphMeshActor(const char* prm_name,
                                             const char* prm_model,
                                             const char* prm_effect_id,
                                             const char* prm_technique) :

                                                 MorphMeshActor(prm_name,
                                                                prm_model,
                                                                TYPE_CUBEMAPMORPHMESH_MODEL,
                                                                prm_effect_id,
                                                                TYPE_CUBEMAPMORPHMESH_EFFECT,
                                                                prm_technique),
                                                 ICubeMapActor() {
    _obj_class |= Obj_GgafDx_CubeMapMorphMeshActor;
    _class_name = "CubeMapMorphMeshActor";
    _pCubeMapMorphMeshModel = (CubeMapMorphMeshModel*)_pModel;
    _pCubeMapMorphMeshEffect = (CubeMapMorphMeshEffect*)_pEffect;
}

void CubeMapMorphMeshActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pCubeMapMorphMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetInt(_pCubeMapMorphMeshEffect->_h_morph_target_num, _pCubeMapMorphMeshModel->_morph_target_num);
    checkDxException(hr, D3D_OK, "SetInt(_h_morph_target_num) に失敗しました。");
    for (int pattern = 1; pattern <= _pCubeMapMorphMeshModel->_morph_target_num; pattern++) {
        hr = pID3DXEffect->SetFloat(_pCubeMapMorphMeshEffect->_ah_weight[pattern], _weight[pattern]);
        checkDxException(hr, D3D_OK, "SetFloat(_ah_weight["<<pattern<<"]) に失敗しました。");
    }
    hr = pID3DXEffect->SetMatrix(_pCubeMapMorphMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pCubeMapMorphMeshEffect->_h_reflectance, getCubeMapReflectance());
    checkDxException(hr, D3D_OK, "SetFloat(_h_reflectances) に失敗しました。");
    pCARETAKER->_pID3DDevice9->SetTexture(1, getCubeMapTexture());

    _pCubeMapMorphMeshModel->draw(this);
}

void CubeMapMorphMeshActor::changeModelByIndex(int prm_model_index) {
    FigureActor::changeModelByIndex(prm_model_index);
    _pCubeMapMorphMeshModel = (CubeMapMorphMeshModel*)_pModel;
}

CubeMapMorphMeshActor::~CubeMapMorphMeshActor() {
}

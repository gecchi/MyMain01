#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9CubeMapMorphMeshActor::GgafDx9CubeMapMorphMeshActor(const char* prm_name,
                                             const char* prm_model_id,
                                             const char* prm_effect_id,
                                             const char* prm_technique,
                                             GgafDx9Checker* prm_pChecker) :

                                                 GgafDx9MorphMeshActor(prm_name,
                                                                       prm_model_id,
                                                                       "H",
                                                                       prm_effect_id,
                                                                       "H",
                                                                       prm_technique,
                                                                       prm_pChecker) {
    _obj_class |= Obj_GgafDx9CubeMapMorphMeshActor;
    _class_name = "GgafDx9CubeMapMorphMeshActor";
    _pCubeMapMorphMeshModel = (GgafDx9CubeMapMorphMeshModel*)_pGgafDx9Model;
    _pCubeMapMorphMeshEffect = (GgafDx9CubeMapMorphMeshEffect*)_pGgafDx9Effect;
}

void GgafDx9CubeMapMorphMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pCubeMapMorphMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pCubeMapMorphMeshEffect->_h_matView, &P_CAM->_vMatrixView );
    checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshActor::GgafDx9MeshEffect SetMatrix(g_matView) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    //(*_pFunc_calcRotMvWorldMatrix)(this, _matWorld);
    hr = pID3DXEffect->SetInt(_pCubeMapMorphMeshEffect->_h_morph_target_num, _pCubeMapMorphMeshModel->_morph_target_num);
    checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshActor::processDraw() SetInt(_h_morph_target_num) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    for (int pattern = 1; pattern <= _pCubeMapMorphMeshModel->_morph_target_num; pattern++) {
        hr = pID3DXEffect->SetFloat(_pCubeMapMorphMeshEffect->_ah_weight[pattern], _weight[pattern]);
        checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshActor::processDraw() SetFloat(_ah_weight["<<pattern<<"]) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    }
    hr = pID3DXEffect->SetMatrix(_pCubeMapMorphMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshActor::processDraw() SetMatrix(g_matWorld) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");

    _pCubeMapMorphMeshModel->draw(this);
}

GgafDx9CubeMapMorphMeshActor::~GgafDx9CubeMapMorphMeshActor() {
}

#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9WorldBoundActor::GgafDx9WorldBoundActor(const char* prm_name,
                                             const char* prm_model_id,
                                             const char* prm_effect_id,
                                             const char* prm_technique,
                                             GgafDx9Checker* prm_pChecker) :

                                                 GgafDx9MorphMeshActor(prm_name,
                                                                       prm_model_id,
                                                                       "W",
                                                                       prm_effect_id,
                                                                       "W",
                                                                       prm_technique,
                                                                       prm_pChecker),
                                                 GgafDx9ICubeMapActor() {
    _obj_class |= Obj_GgafDx9WorldBoundActor;
    _class_name = "GgafDx9WorldBoundActor";
    _pWorldBoundModel = (GgafDx9WorldBoundModel*)_pModel;
    _pWorldBoundEffect = (GgafDx9WorldBoundEffect*)_pEffect;
}

void GgafDx9WorldBoundActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pWorldBoundEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pWorldBoundEffect->_h_matView, &P_CAM->_matView );
//    checkDxException(hr, D3D_OK, "GgafDx9WorldBoundActor::processDraw() SetMatrix(g_matView) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    //(*_pFunc_calcRotMvWorldMatrix)(this, _matWorld);
    hr = pID3DXEffect->SetInt(_pWorldBoundEffect->_h_morph_target_num, _pWorldBoundModel->_morph_target_num);
    checkDxException(hr, D3D_OK, "GgafDx9WorldBoundActor::processDraw() SetInt(_h_morph_target_num) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    for (int pattern = 1; pattern <= _pWorldBoundModel->_morph_target_num; pattern++) {
        hr = pID3DXEffect->SetFloat(_pWorldBoundEffect->_ah_weight[pattern], _weight[pattern]);
        checkDxException(hr, D3D_OK, "GgafDx9WorldBoundActor::processDraw() SetFloat(_ah_weight["<<pattern<<"]) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    }
    hr = pID3DXEffect->SetMatrix(_pWorldBoundEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9WorldBoundActor::processDraw() SetMatrix(g_matWorld) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");

    GgafDx9God::_pID3DDevice9->SetTexture(0, getCubeMapTexture());

    _pWorldBoundModel->draw(this);
}

GgafDx9WorldBoundActor::~GgafDx9WorldBoundActor() {
}

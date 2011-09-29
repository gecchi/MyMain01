#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxWorldBoundActor::GgafDxWorldBoundActor(const char* prm_name,
                                             const char* prm_model_id,
                                             const char* prm_effect_id,
                                             const char* prm_technique,
                                             GgafStatus* prm_pStat,
                                             GgafDxChecker* prm_pChecker) :

                                                 GgafDxMorphMeshActor(prm_name,
                                                                       prm_model_id,
                                                                       "W",
                                                                       prm_effect_id,
                                                                       "W",
                                                                       prm_technique,
                                                                       prm_pStat,
                                                                       prm_pChecker),
                                                 GgafDxICubeMapActor() {
    _obj_class |= Obj_GgafDxWorldBoundActor;
    _class_name = "GgafDxWorldBoundActor";
    _pWorldBoundModel = (GgafDxWorldBoundModel*)_pModel;
    _pWorldBoundEffect = (GgafDxWorldBoundEffect*)_pEffect;
}

void GgafDxWorldBoundActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pWorldBoundEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pWorldBoundEffect->_h_matView, &P_CAM->_matView );
//    checkDxException(hr, D3D_OK, "GgafDxWorldBoundActor::processDraw() SetMatrix(g_matView) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    //(*_pFunc_calcRotMvWorldMatrix)(this, _matWorld);
    hr = pID3DXEffect->SetInt(_pWorldBoundEffect->_h_morph_target_num, _pWorldBoundModel->_morph_target_num);
    checkDxException(hr, D3D_OK, "GgafDxWorldBoundActor::processDraw() SetInt(_h_morph_target_num) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    for (int pattern = 1; pattern <= _pWorldBoundModel->_morph_target_num; pattern++) {
        hr = pID3DXEffect->SetFloat(_pWorldBoundEffect->_ah_weight[pattern], _weight[pattern]);
        checkDxException(hr, D3D_OK, "GgafDxWorldBoundActor::processDraw() SetFloat(_ah_weight["<<pattern<<"]) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    }
    hr = pID3DXEffect->SetMatrix(_pWorldBoundEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxWorldBoundActor::processDraw() SetMatrix(g_matWorld) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");

    GgafDxGod::_pID3DDevice9->SetTexture(0, getCubeMapTexture());

    _pWorldBoundModel->draw(this);
}

GgafDxWorldBoundActor::~GgafDxWorldBoundActor() {
}

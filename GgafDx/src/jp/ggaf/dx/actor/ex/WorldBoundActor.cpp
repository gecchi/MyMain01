#include "jp/ggaf/dx/actor/ex/WorldBoundActor.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/model/ex/WorldBoundModel.h"
#include "jp/ggaf/dx/effect/ex/WorldBoundEffect.h"


using namespace GgafDx;

WorldBoundActor::WorldBoundActor(const char* prm_name,
                                 const char* prm_model,
                                 const char* prm_effect_id,
                                 const char* prm_technique) :

                                     MorphMeshActor(prm_name,
                                                    prm_model,
                                                    TYPE_WORLDBOUND_MODEL,
                                                    prm_effect_id,
                                                    TYPE_WORLDBOUND_EFFECT,
                                                    prm_technique),
                                     ICubeMapActor() {
    _obj_class |= Obj_GgafDx_WorldBoundActor;
    _class_name = "WorldBoundActor";
    _pWorldBoundModel = (WorldBoundModel*)_pModel;
    _pWorldBoundEffect = (WorldBoundEffect*)_pEffect;
}

void WorldBoundActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pWorldBoundEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetInt(_pWorldBoundEffect->_h_morph_target_num, _pWorldBoundModel->_morph_target_num);
    checkDxException(hr, D3D_OK, "SetInt(_h_morph_target_num) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    for (int pattern = 1; pattern <= _pWorldBoundModel->_morph_target_num; pattern++) {
        hr = pID3DXEffect->SetFloat(_pWorldBoundEffect->_ah_weight[pattern], _weight[pattern]);
        checkDxException(hr, D3D_OK, "SetFloat(_ah_weight["<<pattern<<"]) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    }
    hr = pID3DXEffect->SetMatrix(_pWorldBoundEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");

    pCARETAKER->_pID3DDevice9->SetTexture(0, getCubeMapTexture());

    _pWorldBoundModel->draw(this);
}

void WorldBoundActor::changeModelByIndex(int prm_model_index) {
    FigureActor::changeModelByIndex(prm_model_index);
    _pWorldBoundModel = (WorldBoundModel*)_pModel;
}

WorldBoundActor::~WorldBoundActor() {
}

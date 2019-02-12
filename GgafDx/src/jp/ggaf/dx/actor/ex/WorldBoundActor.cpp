#include "jp/ggaf/dx/actor/ex/WorldBoundActor.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/model/ex/WorldBoundModel.h"
#include "jp/ggaf/dx/effect/ex/WorldBoundEffect.h"


using namespace GgafDx;

WorldBoundActor::WorldBoundActor(const char* prm_name,
                                             const char* prm_model_id,
                                             const char* prm_effect_id,
                                             const char* prm_technique,
                                             GgafCore::Status* prm_pStat,
                                             Checker* prm_pChecker) :

                                                 MorphMeshActor(prm_name,
                                                                      prm_model_id,
                                                                      TYPE_WORLDBOUND_MODEL,
                                                                      prm_effect_id,
                                                                      TYPE_WORLDBOUND_EFFECT,
                                                                      prm_technique,
                                                                      prm_pStat,
                                                                      prm_pChecker),
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
    checkDxException(hr, D3D_OK, "SetInt(_h_morph_target_num) �Ɏ��s���܂����B");
    for (int pattern = 1; pattern <= _pWorldBoundModel->_morph_target_num; pattern++) {
        hr = pID3DXEffect->SetFloat(_pWorldBoundEffect->_ah_weight[pattern], _weight[pattern]);
        checkDxException(hr, D3D_OK, "SetFloat(_ah_weight["<<pattern<<"]) �Ɏ��s���܂����B");
    }
    hr = pID3DXEffect->SetMatrix(_pWorldBoundEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) �Ɏ��s���܂����B");

    God::_pID3DDevice9->SetTexture(0, getCubeMapTexture());

    _pWorldBoundModel->draw(this);
}

WorldBoundActor::~WorldBoundActor() {
}

#include "jp/ggaf/lib/actor/SingleLaser.h"

#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/effect/MeshSetEffect.h"
#include "jp/ggaf/dx/model/MeshSetModel.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/effect/SingleLaserEffect.h"

using namespace GgafLib;

//注意：SingleLaser SetNum の最大は 26 に引き上げられる。定義側で26を設定推奨
SingleLaser::SingleLaser(const char* prm_name, const char* prm_model) :
             GgafDx::MeshSetActor(prm_name,
                                  prm_model,
                                  TYPE_SINGLELASER_MODEL,
                                  "SingleLaserEffect",
                                  TYPE_SINGLELASER_EFFECT,
                                  "SingleLaserTechnique") {
    _class_name = "SingleLaser";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();

    useZBufferDrawing(true);    //描画時、Zバッファ値は考慮される
    setZBufferWriteEnable(false);  //自身のZバッファを書き込みしない
}

void SingleLaser::processDraw() {
    int draw_set_num = 0; //MeshSetActorの同じモデルで同じテクニックが
                          //連続しているカウント数。同一描画深度は一度に描画する。
    SingleLaserEffect* pSingleLaserEffect = (SingleLaserEffect*)_pMeshSetEffect;
    ID3DXEffect* const pID3DXEffect = pSingleLaserEffect->_pID3DXEffect;
    HRESULT hr;
    //基本モデル頂点数
    GgafDx::FigureActor* pDrawActor = this;
    SingleLaser* pSingleLaserChip = nullptr;
    int model_Set_num = _pMeshSetModel->_draw_set_num;

    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pSingleLaserChip = (SingleLaser*)pDrawActor;
            hr = pID3DXEffect->SetMatrix(pSingleLaserEffect->_ah_matWorld[draw_set_num], &(pSingleLaserChip->_matWorld));
            checkDxException(hr, D3D_OK, "pDrawActor->_matWorld="<<pDrawActor->_matWorld<<" pDrawActor="<<pDrawActor->getName()<<" draw_set_num="<<draw_set_num<<" に失敗しました。");

            pDrawActor = pDrawActor->_pNextRenderActor;
            draw_set_num++;
            if (draw_set_num >= model_Set_num) {
                break;
            }
        } else {
            break;
        }
    }
    _pMeshSetModel->GgafDx::MeshSetModel::draw(this, draw_set_num);
    _pNextRenderActor = pDrawActor;
}

void SingleLaser::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* SingleLaser::createChecker(kind_t prm_kind) {
    return UTIL::createCollisionChecker(this, prm_kind);
}

SingleLaser::~SingleLaser() {
}

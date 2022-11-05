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
                                  "SingleLaserTechnique",
                                  UTIL::createCollisionChecker(this) ) {
    _class_name = "SingleLaser";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;

    setZEnableDraw(true);    //描画時、Zバッファ値は考慮される
    setZWriteEnable(false);  //自身のZバッファを書き込みしない
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
            draw_set_num++;
            if (draw_set_num >= model_Set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    GgafDx::Spacetime::_pActor_draw_active = pSingleLaserChip; //描画セットの最後アクターをセット
    _pMeshSetModel->GgafDx::MeshSetModel::draw(this, draw_set_num);
}

void SingleLaser::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

SingleLaser::~SingleLaser() {
    GGAF_DELETE(_pColliCollisionChecker);
}

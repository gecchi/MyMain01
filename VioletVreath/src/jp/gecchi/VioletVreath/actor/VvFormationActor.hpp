#ifndef VVFORMATIONACTOR_H_
#define VVFORMATIONACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/ggaf/core/util/Status.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

namespace VioletVreath {

template<class T>
class VvFormationActor : public T {

public:
    VvFormationActor(const char* prm_name, void* prm_pPrm1 = nullptr)
            : T(prm_name) {

        if (prm_pPrm1) {
            T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pPrm1);
#ifdef MY_DEBUG
            if (!(T::getDefaultKind() & KIND_FORMATION)) {
                throwCriticalException("KIND_FORMATION と、ステータスが異なっています。name="<<prm_name);
            }
#endif
        } else {
            T::getStatus()->reset(StatusReset(Default));
        }
    }

    /**
     * 編隊が全て自機側の攻撃で殲滅させられた場合の処理実装 .
     * @param prm_pActor_last_destroyed  最後に破壊されたアクター
     */
    virtual void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override {
        //フォーメーション全滅爆発エフェクト
        UTIL::activateExplosionEffectOf(this);
        //フォーメーション全滅アイテム出現
        UTIL::activateItemOf(this);
        //フォーメーション全滅やられ特殊エフェクト（ボーナス表示等）
        UTIL::activateDestroyedEffectOf(this);
        //編隊全滅時ボーナス加算
        GameGlobal::addDestroyedScoreBy(this);
    }

    virtual ~VvFormationActor() {
    }
};

}

#endif /* VVFORMATIONACTOR_H_ */

#ifndef VVFORMATIONACTOR_H_
#define VVFORMATIONACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvGeometricActor.hpp"

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

namespace VioletVreath {

template<class T>
class VvFormationActor : public VvGeometricActor<T> {

public:
    VvFormationActor(const char* prm_name, void* prm_pFuncResetStatus)
            : VvGeometricActor<T>(prm_name, prm_pFuncResetStatus) {
#ifdef MY_DEBUG
        if (!(T::_pChecker->_kind == KIND_FORMATION)) {
            throwCriticalException("KIND_FORMATION と、ステータスが異なっています。name="<<prm_name);
        }
#endif
        GgafCore::Status* pStatus = T::getStatus();
        GgafDx::SeTransmitterForActor* pSeXmtr = T::getSeXmtr();
    }

    /**
     * 編隊が全て自機側の攻撃で殲滅させられた場合の処理実装 .
     * @param prm_pActor_last_destroyed  最後に破壊されたアクター
     */
    virtual void onDestroyAll(GgafDx::GeometricActor* prm_pActor_last_destroyed) override {
        //フォーメーション全滅爆発エフェクト
        UTIL::activateCommonEffectOf(this, STAT_ExplosionEffectKind);
        //フォーメーション全滅アイテム出現
        UTIL::activateMyShipItemOf(this);
        //フォーメーション全滅やられ特殊エフェクト（ボーナス表示等）
        UTIL::activateCommonEffectOf(this, STAT_DestroyedEffectKind);
        UTIL::activateMyShipEffectOf(this, STAT_DestroyedEffectKind);
        //編隊全滅時ボーナス加算
        GameGlobal::addDestroyedScoreBy(this);
    }

    virtual ~VvFormationActor() {
    }
};

}

#endif /* VVFORMATIONACTOR_H_ */

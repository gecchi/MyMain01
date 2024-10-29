#ifndef VVFORMATIONACTOR_H_
#define VVFORMATIONACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/core/util/Status.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

namespace VioletVreath {

template<class T>
class VvFormationActor : public T {
public:
    GgafDx::SeTransmitterForActor* _pSeTransmitter;
public:
    VvFormationActor(const char* prm_name, void* prm_pFuncResetStatus = nullptr)
            : T(prm_name) {
        _pSeTransmitter = nullptr;
        if (prm_pFuncResetStatus) {
            T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pFuncResetStatus);
            _pSeTransmitter = NEW GgafDx::SeTransmitterForActor((GgafCore::Formation*)this);
            t_se_id se_id = T::getStatus()->get(STAT_ExplosionSeKind);
            if (se_id != SE_NOTHING) {
                _pSeTransmitter->set(se_id, MyStgUtil_SeKind::mapSeId[se_id]);
            }


#ifdef MY_DEBUG
//            if (!(T::_pChecker->_kind == KIND_FORMATION)) {
//                throwCriticalException("KIND_FORMATION と、ステータスが異なっています。name="<<prm_name);
//            }
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
        UTIL::activateEffectOf(this, STAT_ExplosionEffectKind);
        //フォーメーション全滅時爆発SE
        t_se_id se_id = T::getStatus()->get(STAT_ExplosionSeKind);
        if (se_id != SE_NOTHING) {
            _pSeTransmitter->play3D(se_id);
        }
        //フォーメーション全滅アイテム出現
        UTIL::activateItemOf(this);
        //フォーメーション全滅やられ特殊エフェクト（ボーナス表示等）
        UTIL::activateEffectOf(this, STAT_DestroyedEffectKind);
        //編隊全滅時ボーナス加算
        GameGlobal::addDestroyedScoreBy(this);
    }

    virtual ~VvFormationActor() {
        GGAF_DELETEARR_NULLABLE(_pSeTransmitter);
    }
};

}

#endif /* VVFORMATIONACTOR_H_ */

#ifndef VVENEMYACTOR_H_
#define VVENEMYACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvGeometricActor.hpp"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
namespace VioletVreath {

template<class T>
class VvEnemyActor : public VvGeometricActor<T> {

public:
    VvEnemyActor(const char* prm_name, const char* prm_model, void* prm_pFuncResetStatus = nullptr)
            : VvGeometricActor<T>(prm_name, prm_model, prm_pFuncResetStatus) {
#ifdef MY_DEBUG
        if (!(T::_pChecker->_kind & KIND_ENEMRY)) {
            throwCriticalException("KIND_ENEMRY と、ステータスが異なっています。name="<<prm_name);
        }
#endif
        GgafCore::Status* pStatus = T::getStatus();
        GgafDx::SeTransmitterForActor* pSeXmtr = T::getSeXmtr();

    }

    virtual void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor)  override {
        bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
        if (is_stamina_zero) {
            //破壊された時(スタミナ <= 0)
            VvGeometricActor<T>::sayonara();
        } else {
            //破壊されなかった時(スタミナ > 0)
        }
    }

    /**
     * 敵キャラヒット時の標準的な処理 .
     * ・破壊された場合<br>
     * ・破壊されなかった場合<br>
     * それぞれ、相手種別が MY*** （自機関連）である場合と、そうでない（地形など）の場合の共通処理
     * @param prm_pOther ヒットした相手のアクターを渡す
     * @return true:スタミナ0(破壊された)/false:スタミナ残あり(破壊されてない)
     */
    bool performEnemyHit(const GgafDx::GeometricActor* prm_pOther) {
        GgafCore::Status* pThisStatus  = VvGeometricActor<T>::getStatus();
        if (VvGeometricActor<T>::calcStamina(prm_pOther) <= 0) { //体力が無くなったら
            //＜破壊された場合＞
            VvGeometricActor<T>::setHitAble(false); //当たり判定消失
            //爆発エフェクト
            UTIL::activateCommonEffectOf(this, STAT_ExplosionEffectKind); 
            if ((prm_pOther->_pChecker->_kind) & KIND_MY) {
                //相手種別が MY*** （自機関連） ならば
                GameGlobal::addDestroyedScoreBy(this);
                VvGeometricActor<T>::notifyDestroyed(); //編隊全滅判定に有効な破壊のされ方でしたよ、と通知
                UTIL::activateMyShipItemOf(this);    //アイテム出現
                UTIL::activateCommonEffectOf(this, STAT_DestroyedEffectKind);  //編隊全滅判定に有効なやられ特殊エフェクト（今のところなし？）
                UTIL::activateMyShipEffectOf(this, STAT_DestroyedEffectKind);  //得点表示等（編隊はボーナス得点）
                UTIL::activateRevengeShotOf(this);     //打ち返し弾
            }
            return true;
        } else {
            //＜非破壊時、ダメージを受けた場合＞
            //ダメージエフェクト
            UTIL::activateCommonEffectOf(this, STAT_DamagedEffectKind); 
            if ((prm_pOther->_pChecker->_kind) & KIND_MY) {
                //相手種別が MY*** （自機関連） ならば
                GameGlobal::addDamagedScoreBy(this); //ダメージ時得点
            }
            if (pThisStatus->get(STAT_FlushAble)) { //ダメージフラッシュするかどうか
                VvGeometricActor<T>::effectFlush(2); //フラッシュ！
            }
            return false;
        }
    }

    virtual ~VvEnemyActor() {
    }
};

}

#endif /* VVTEKIACTOR_H_ */

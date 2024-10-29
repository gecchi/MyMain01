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

    /**
     * 敵キャラヒット時の標準的な処理 .
     * ＜破壊された場合＞<br>
     * ・破壊時得点加算<br>
     * ・ランク加算<br>
     * ・アイテム出現             activateItemOf()<br>
     * ・消滅時特殊エフェクト開始 activateDestroyedEffectOf()<br>
     * ・打ち返し弾出現           activateRevengeShotOf()<br>
     * ・爆発エフェクト出現       activateExplosionEffectOf()<br>
     * ・編隊全滅判定<br>
     * ・編隊全滅時アイテム出現(STAT_ItemKind)<br>
     * ＜破壊されなかった場合＞<br>
     * ・ダメージを与えた得点加算<br>
     * ・ダメージフラッシュ表示       STAT_FlushAble<br>
     * ・ダメージ時特殊エフェクト出現 activateDamagedEffectOf()<br>
     * @param prm_pOther ヒットした相手のアクターを渡す
     * @return true:スタミナ0(破壊された)/false:スタミナ残あり(破壊されてない)
     */
    bool performEnemyHit(const GgafDx::GeometricActor* prm_pOther) {
        GgafCore::Status* pThisStatus  = VvGeometricActor<T>::getStatus();
        if (VvGeometricActor<T>::calcStamina(prm_pOther) <= 0) { //体力が無くなったら
            //＜破壊された場合＞
            VvGeometricActor<T>::setHitAble(false); //当たり判定消失
            if ((prm_pOther->_pChecker->_kind) & KIND_MY) {
                //相手(自機)の種別が MY*** （自機関連） ならば
                GameGlobal::addDestroyedScoreBy(prm_pOther);
                VvGeometricActor<T>::notifyDestroyed(); //編隊全滅判定に有効な破壊のされ方でしたよ、と通知
                UTIL::activateItemOf(this);    //アイテム出現
                UTIL::activateEffectOf(this, STAT_DestroyedEffectKind);  //やられ特殊エフェクト（ボーナス表示等）
            }
            UTIL::activateRevengeShotOf(this);     //打ち返し弾
            UTIL::activateEffectOf(this, STAT_ExplosionEffectKind); //爆発エフェクト
            return true;
        } else {
            //＜非破壊時、ダメージを受けた場合＞
            if ((prm_pOther->_pChecker->_kind) & KIND_MY) { //相手(自機)の種別が MY*** （自機関連） ならば
                GameGlobal::addDamagedScoreBy(prm_pOther); //ダメージ時得点
            }
            if (pThisStatus->get(STAT_FlushAble)) { //ダメージフラッシュするかどうか
                VvGeometricActor<T>::effectFlush(2); //フラッシュ！
            }
            UTIL::activateEffectOf(this, STAT_DamagedEffectKind); //ダメージエフェクト
            return false;
        }
    }

    virtual ~VvEnemyActor() {
    }
};

}

#endif /* VVTEKIACTOR_H_ */

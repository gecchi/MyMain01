#ifndef VVMYACTOR_H_
#define VVMYACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvGeometricActor.hpp"

namespace VioletVreath {

template<class T>
class VvMyActor : public VvGeometricActor<T> {

public:
    VvMyActor(const char* prm_name, const char* prm_model, void* prm_pFuncResetStatus = nullptr)
            : VvGeometricActor<T>(prm_name, prm_model, prm_pFuncResetStatus) {
#ifdef MY_DEBUG
        if (!(T::_pChecker->_kind & KIND_MY)) {
            throwCriticalException("KIND_MY と、ステータスが異なっています。name="<<prm_name);
        }
#endif
    }


//    bool performMyHit(const GgafDx::GeometricActor* prm_pOther) {
//        GgafCore::Status* pThisStatus  = VvGeometricActor<T>::getStatus();
//        if (VvGeometricActor<T>::calcStamina(prm_pOther) <= 0) { //体力が無くなったら
//            //＜破壊された場合＞
//            VvGeometricActor<T>::setHitAble(false); //当たり判定消失
//            //爆発エフェクト
//            UTIL::activateCommonEffectOf(this, STAT_ExplosionEffectKind);
//            if ((prm_pOther->_pChecker->_kind) & KIND_ENEMY) {
//                //相手種別が MY*** （自機関連） ならば
//                GameGlobal::addDestroyedScoreBy(prm_pOther);
//                prm_pOther->notifyDestroyed(); //編隊全滅判定に有効な破壊のされ方でしたよ、と通知
//                UTIL::activateMyShipItemOf(prm_pOther);    //アイテム出現
//                //UTIL::activateCommonEffectOf(prm_pOther, STAT_DestroyedEffectKind);  //編隊全滅判定に有効なやられ特殊エフェクト（今のところなし？）
//                UTIL::activateMyShipEffectOf(prm_pOther, STAT_DestroyedEffectKind);  //得点表示等（編隊はボーナス得点）
//                //UTIL::activateRevengeShotOf(this);     //打ち返し弾
//            }
//            return true;
//        } else {
//            //＜非破壊時、ダメージを受けた場合＞
//            //ダメージエフェクト
//            UTIL::activateCommonEffectOf(this, STAT_DamagedEffectKind);
//            if ((prm_pOther->_pChecker->_kind) & KIND_ENEMY) {
//                //相手種別が MY*** （自機関連） ならば
//                GameGlobal::addDamagedScoreBy(prm_pOther); //ダメージ時得点
//            }
//            if (pThisStatus->get(STAT_FlushAble)) { //ダメージフラッシュするかどうか
//                VvGeometricActor<T>::effectFlush(2); //フラッシュ！
//            }
//            return false;
//        }
//    }



    virtual ~VvMyActor() {
    }
};

}

#endif /* VVMIKATAACTOR_H_ */

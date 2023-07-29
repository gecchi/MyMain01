#ifndef VVENEMYACTOR_H_
#define VVENEMYACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvActor.hpp"
#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
namespace VioletVreath {

template<class T>
class VvEnemyActor : public VvActor<T> {

public:
    VvEnemyActor(const char* prm_name, const char* prm_model, void* prm_pPrm1 = nullptr)
            : VvActor<T>(prm_name, prm_model) {
        T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pPrm1);
#ifdef MY_DEBUG
        if (!(T::getDefaultKind() & KIND_ENEMRY)) {
            throwCriticalException("KIND_ENEMRY と、ステータスが異なっています。name="<<prm_name);
        }
#endif
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
     * @return true:破壊された/false:破壊されてない
     */
    bool performEnemyHit(const GgafDx::GeometricActor* const prm_pOther) {
        GgafCore::Status* pThisStatus  = VvActor<T>::getStatus();
        if (VvActor<T>::calcStamina(prm_pOther) <= 0) { //体力が無くなったら
            //＜破壊された場合＞
            VvActor<T>::setHitAble(false); //当たり判定消失
            if (prm_pOther->_pGroupHead->_kind & KIND_MY) {
                //相手(自機)の種別が MY*** （自機関連） ならば
                G_SCORE += pThisStatus->get(STAT_AddDestroyScorePoint);   //破壊時得点
                double rp = pThisStatus->getDouble(STAT_AddRankPoint);    //加算初期ランク値
                if (!ZEROd_EQ(rp)) {
                    double rp_r = pThisStatus->getDouble(STAT_AddRankPoint_Reduction); //毎フレームのランク倍率
                    if (ZEROd_EQ(rp_r)) { //倍率が0.0ならば
                        //なにもしない
                    } else if (ONEd_EQ(rp_r)) {
                        G_RANK += rp; //倍率が1.0ならば、そのまま加算初期ランク値をプラス
                        if (G_RANK > G_MAX_RANK) {
                            G_RANK = G_MAX_RANK;
                        }
                        if (G_RANK < G_MIN_RANK) {
                            G_RANK = G_MIN_RANK;
                        }
                    } else if (rp_r > 0) {
                        frame n = VvActor<T>::getActiveFrame();   //稼働フレーム
                        G_RANK += (rp * pow(rp_r, (double)n)); //rp * (rp_r ^ n)  ランク加算
                        if (G_RANK > G_MAX_RANK) {
                            G_RANK = G_MAX_RANK;
                        }
                        if (G_RANK < G_MIN_RANK) {
                            G_RANK = G_MIN_RANK;
                        }
                    } else {
                        //なにもしない
                    }

                }
                VvActor<T>::notifyDestroyedToFormation();     //編隊全滅判定に有効な破壊のされ方でしたよ、と通知
                UTIL::activateItemOf(this);             //アイテム出現
                UTIL::activateDestroyedEffectOf(this);  //やられたエフェクト
                GgafCore::Scene* pThisPlatformScene = VvActor<T>::getSceneChief()->getPlatformScene();
                if (pThisPlatformScene->instanceOf(Obj_RankUpStage)) {
                    //ランクアップステージの敵ならば、
                    RankUpStage* pRankUpStage = (RankUpStage*)(pThisPlatformScene);
                    pRankUpStage->onDestroyedEnemy(this, prm_pOther);
                }
            }
            UTIL::activateRevengeShotOf(this);     //打ち返し弾
            UTIL::activateExplosionEffectOf(this); //爆発エフェクト
            return true;
        } else {
            //＜非破壊時、ダメージを受けた場合＞
            if (prm_pOther->_pGroupHead->_kind & KIND_MY) { //相手(自機)の種別が MY*** （自機関連） ならば
                G_SCORE += pThisStatus->get(STAT_AddDamagedScorePoint);   //ダメージ時得点
            }
            if (pThisStatus->get(STAT_FlushAble)) { //ダメージフラッシュするかどうか
                VvActor<T>::effectFlush(2); //フラッシュ！
            }
            UTIL::activateDamagedEffectOf(this); //ダメージエフェクト
            return false;
        }
    }

    virtual ~VvEnemyActor() {
    }
};

}

#endif /* VVTEKIACTOR_H_ */

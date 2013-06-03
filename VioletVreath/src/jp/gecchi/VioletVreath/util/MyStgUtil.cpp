#include "stdafx.h"
#include "MyStgUtil.h"

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/actor/my/MyStraightLaserChip001.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

int MyStgUtil::judgeMyAdvantage(actorkind attribute_my, actorkind attribute_enemy) {
    int ret = 0;
    if (attribute_my & ATTRIBUTE_GU) {
        if (attribute_enemy & ATTRIBUTE_CHOKI) {
            ret++;
        }
        if (attribute_enemy & ATTRIBUTE_PA) {
            ret--;
        }
    }

    if (attribute_my & ATTRIBUTE_CHOKI) {
        if (attribute_enemy & ATTRIBUTE_PA) {
            ret++;
        }
        if (attribute_enemy & ATTRIBUTE_GU) {
            ret--;
        }
    }

    if (attribute_my & ATTRIBUTE_PA) {
        if (attribute_enemy & ATTRIBUTE_GU) {
            ret++;
        }
        if (attribute_enemy & ATTRIBUTE_CHOKI) {
            ret--;
        }
    }
    return ret;
}

int MyStgUtil::judgeEnemyAdvantage(actorkind kattribute_enemy, actorkind attribute_my) {
    int ret = 0;
    if (kattribute_enemy & ATTRIBUTE_GU) {
        if (attribute_my & ATTRIBUTE_CHOKI) {
            ret++;
        }
        if (attribute_my & ATTRIBUTE_PA) {
            ret--;
        }
    }

    if (kattribute_enemy & ATTRIBUTE_CHOKI) {
        if (attribute_my & ATTRIBUTE_PA) {
            ret++;
        }
        if (attribute_my & ATTRIBUTE_GU) {
            ret--;
        }
    }

    if (kattribute_enemy & ATTRIBUTE_PA) {
        if (attribute_my & ATTRIBUTE_GU) {
            ret++;
        }
        if (attribute_my & ATTRIBUTE_CHOKI) {
            ret--;
        }
    }
    return ret;
}

int MyStgUtil::calcMyStamina(GgafMainActor* prm_pMy, GgafMainActor* prm_pOpp) {
    GgafStatus* pStatMy = prm_pMy->_pStatus;
    GgafStatus* pStatOpp = prm_pOpp->_pStatus;

    //優性劣性判定
    int my_domi = MyStgUtil::judgeMyAdvantage(pStatMy->getUint(STAT_Attribute),
                                              pStatOpp->getUint(STAT_Attribute));
    //相手(敵)攻撃力
    int opp_attack = pStatOpp->get(STAT_Attack);
    //優性劣性に応じて防御率を乗ずる
    if (my_domi > 0) {
        //自分が優性時
        return pStatMy->minus(STAT_Stamina,
                              (int)(opp_attack * pStatMy->getDouble(STAT_DominantDefenceRate)));
    } else if (my_domi < 0) {
        //自分が劣性時
        return pStatMy->minus(STAT_Stamina,
                              (int)(opp_attack * pStatMy->getDouble(STAT_RecessiveDefenceRate)));
    } else {
        //相手(敵)と同格時
        return pStatMy->minus(STAT_Stamina,
                              (int)(opp_attack * pStatMy->getDouble(STAT_DefaultDefenceRate)));
    }
}

int MyStgUtil::calcEnemyStamina(GgafMainActor* prm_pEnemy, GgafMainActor* prm_pOpp) {
    GgafStatus* pStatEnemy = prm_pEnemy->_pStatus;
    GgafStatus* pStatOpp = prm_pOpp->_pStatus;
    //優性劣性判定
    int enemy_domi = MyStgUtil::judgeEnemyAdvantage(pStatEnemy->getUint(STAT_Attribute),
                                                    pStatOpp->getUint(STAT_Attribute));
    //相手(自機)攻撃力
    int opp_attack = pStatOpp->get(STAT_Attack);
    //優性劣性に応じて防御率を乗ずる
    int enemy_stamina;
    if (enemy_domi > 0) {
        //自分（敵）が優性時
        enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                          (int)(opp_attack * pStatEnemy->getDouble(STAT_DominantDefenceRate)));
    } else if (enemy_domi < 0) {
        //自分（敵）が劣性時
        enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                          (int)(opp_attack * pStatEnemy->getDouble(STAT_RecessiveDefenceRate)));
    } else {
        //相手(自機)と同格時
        enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                          (int)(opp_attack * pStatEnemy->getDouble(STAT_DefaultDefenceRate)));
    }
    return enemy_stamina;
}

GgafDxDrawableActor* MyStgUtil::activateExplosionEffectOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pE = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_ExplosionEffectKind)) {
        case 0: {
            pE = nullptr; //爆発エフェクト無し
            break;
        }
        case EF_EXPLOSION001: {
            pE = dispatchFromCommon(EffectExplosion001);
            break;
        }
        case EF_EXPLOSION002: {
            pE = dispatchFromCommon(EffectExplosion002);
            break;
        }
        case EF_EXPLOSION003: {
            pE = dispatchFromCommon(EffectExplosion003);
            break;
        }
        default: {
            throwGgafCriticalException("対応 ExplosionEffect が定義されてない。prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pE = nullptr;
            break;
        }
    }

    if (pE) {
        //出現座標を設定
        pE->locateAs(prm_pActor);
        pE->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
    }
    return pE;
}


GgafDxDrawableActor* MyStgUtil::activateDamagedEffectOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pE = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_DamagedEffectKind)) {
        case 0: {
            pE = nullptr; //爆発エフェクト無し
            break;
        }
        case EF_DAMAGED001: {
            pE = dispatchFromCommon(EffectExplosion001);
            break;
        }
        default: {
            throwGgafCriticalException("対応 DamagedEffect が定義されてない。prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pE = nullptr;
            break;
        }
    }

    if (pE) {
        //出現座標を設定
        pE->locateAs(prm_pActor);
        pE->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
    }
    return pE;
}
GgafDxDrawableActor* MyStgUtil::activateAttackShotOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pI = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_AttackShotKind)) {
        case 0: {
            pI = nullptr; //ショット無し
            break;
        }
        case SHOT_SMALL001: {
            pI = dispatchFromCommon(Shot004);
            break;
        }
        default: {
            throwGgafCriticalException("対応 AttackShot が定義されてない。prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pI = nullptr;
            break;
        }
    }
    if (pI) {
        //出現座標を設定
        pI->locateAs(prm_pActor);
    }
    return pI;
}


GgafDxDrawableActor* MyStgUtil::activateRevengeShotOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pI = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_RevengeShotKind)) {
        case 0: {
            pI = nullptr; //ショット無し
            break;
        }
        case SHOT_RV_NOMAL001: {
            pI = UTIL::shotWay002(
                   prm_pActor,
                   getCommonDepository(Shot004),
                   PX_C(20),       //r
                   RF_SHOT_RV_NOMAL001_ShotWay(_RANK_),    //way数
                   RF_SHOT_RV_NOMAL001_Density(_RANK_),    //wayとwayの間隔
                   RF_SHOT_RV_ShotMvVelo(_RANK_),          //初期速度
                   RF_SHOT_RV_ShotMvAcce(_RANK_),          //加速度
                   RF_SHOT_RV_NOMAL001_ShotSetNum(_RANK_), //wayのセット数
                   8, //セットとセットの間隔フレーム
                   0.0f,
                   nullptr
                 );

            break;
        }

        case SHOT_RV_NOMAL002: {

            pI = UTIL::shotWay004(prm_pActor,
                                  getCommonDepository(Shot004),
                                  PX_C(20),
                                  8,
                                  D_ANG(10),
                                  RF_SHOT_RV_ShotMvVelo(_RANK_),
                                  RF_SHOT_RV_ShotMvAcce(_RANK_),
                                  12,
                                  3,
                                  0.9);


            break;
        }

        case SHOT_RV_GOLDEN_ANG_WAY: {
            MyShip* pM = P_MYSHIP;
            angle rz,ry;
            UTIL::convVectorToRzRy(pM->_X - prm_pActor->_X,
                                   pM->_Y - prm_pActor->_Y,
                                   pM->_Z - prm_pActor->_Z,
                                   rz, ry);

            pI = UTIL::shotWayGoldenAng(prm_pActor->_X,
                                        prm_pActor->_Y,
                                        prm_pActor->_Z,
                                        rz, ry,
                                        getCommonDepository(Shot004),
                                        PX_C(20),
                                        300,
                                        D_ANG(1), 100,
                                        2000, 200,
                                        2, 4, 0.9);

            break;
        }

        default: {
            throwGgafCriticalException("対応 RevengeShot が定義されてない。prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pI = nullptr;
            break;
        }
    }
    if (pI) {
    }
    return pI;
}

GgafDxDrawableActor* MyStgUtil::activateItemOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pI = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_ItemKind)) {
        case 0: {
            pI = nullptr; //アイテム無し
            break;
        }
        case ITEM_MP_SMALL: {
            pI = dispatchFromCommon(MagicPointItem001);
            break;
        }
        case ITEM_MP_MIDDLE: {
            pI = dispatchFromCommon(MagicPointItem002);
            break;
        }
        default: {
            throwGgafCriticalException("対応 Item が定義されてない。prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pI = nullptr;
            break;
        }
    }
    if (pI) {
        //出現座標を設定
        pI->locateAs(prm_pActor);
    }
    return pI;
}

GgafDxDrawableActor* MyStgUtil::activateDestroyedEffectOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pE = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_DestroyedEffectKind)) {
        case 0: {
            pE = nullptr; //爆発エフェクト無し
            break;
        }
        case EF_BONUS001: {
            //スコアが表示される消滅エフェクト
            SpriteLabelBonus001* pLabel = dispatchForceFromCommon(SpriteLabelBonus001);
            pLabel->locateAs(prm_pActor);
            pLabel->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
            std::string s = XTOS(prm_pActor->_pStatus->get(STAT_AddDestroyScorePoint));
            pLabel->update(s.c_str()); //破壊時得点が表示される
            pE = pLabel;
            break;
        }
        default: {
            throwGgafCriticalException("対応 DestroyedEffect が定義されてない。prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pE = nullptr;
            break;
        }
    }

    if (pE) {
        //出現座標を設定
        pE->locateAs(prm_pActor);
        pE->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
    }
    return pE;
}

GgafDxDrawableActor* MyStgUtil::activateEntryEffectOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pRet = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_EntryEffectKind)) {
        case 0: {
            pRet = nullptr; //入場エフェクト無し
            break;
        }
        case EF_ENTRY_SMALL001_LONG: {
            EffectEntry001* pE = dispatchFromCommon(EffectEntry001);
            if (pE) {
                pE->locateAs(prm_pActor);
                pE->config(30,120,60);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_F30: {
            EffectEntry001* pE = dispatchFromCommon(EffectEntry001);
            if (pE) {
                pE->locateAs(prm_pActor);
                pE->config(15,1,15);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_F60: {
            EffectEntry001* pE = dispatchFromCommon(EffectEntry001);
            if (pE) {
                pE->locateAs(prm_pActor);
                pE->config(30,1,30);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_MIDDLE001: {
            EffectEntry002* pE = dispatchFromCommon(EffectEntry002);
            if (pE) {
                pE->locateAs(prm_pActor);
//                pE->config(30,1,30);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_LARGE001: {
            EffectEntry003* pE = dispatchFromCommon(EffectEntry003);
            if (pE) {
                pE->locateAs(prm_pActor);
//                pE->config(30,1,30);
            }
            pRet = pE;
            break;
        }
        default: {
            throwGgafCriticalException("対応 EntryEffect が定義されてない。prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pRet = nullptr;
            break;
        }
    }
    if (pRet) {
    }
    return pRet;
}

GgafDxDrawableActor* MyStgUtil::activateLeaveEffectOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pRet = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_LeaveEffectKind)) {
        case 0: {
            pRet = nullptr; //退場エフェクト無し
            break;
        }
        case EF_LEAVE_SMALL001_F30: {
            EffectEntry001* pE = dispatchFromCommon(EffectEntry001);
            if (pE) {
                pE->locateAs(prm_pActor);
                pE->config(15,1,15);
            }
            pRet = pE;
            break;
        }
        case EF_LEAVE_SMALL001_F60: {
            EffectEntry001* pE = dispatchFromCommon(EffectEntry001);
            if (pE) {
                pE->locateAs(prm_pActor);
                pE->config(30,1,30);
            }
            pRet = pE;
            break;
        }
        case EF_LEAVE_MIDDLE001: {
            EffectEntry002* pE = dispatchFromCommon(EffectEntry002);
            if (pE) {
                pE->locateAs(prm_pActor);
            }
            pRet = pE;
            break;
        }
        case EF_LEAVE_LARGE001: {
            EffectEntry003* pE = dispatchFromCommon(EffectEntry003);
            if (pE) {
                pE->locateAs(prm_pActor);
            }
            pRet = pE;
            break;
        }
        default: {
            throwGgafCriticalException("対応 LeaveEffect が定義されてない。prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pRet = nullptr;
            break;
        }
    }
    if (pRet) {
    }
    return pRet;
}

GgafDxDrawableActor* MyStgUtil::activateFormationDestroyedEffectOf(GgafDxGeometricActor* prm_pActor) {

    GgafDxDrawableActor* pE = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_FormationDestroyedEffectKind)) {
        case 0: {
            pE = nullptr; //エフェクト無し
            break;
        }
        case EF_EXPLO_AND_BONUS001: {
            //1は通常のフォーメーションボーナススコア表示エフェクト
            SpriteLabelBonus001* pLabel = dispatchForceFromCommon(SpriteLabelBonus001);
            pLabel->locateAs(prm_pActor);
            pLabel->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
            int addscore = prm_pActor->_pStatus->get(STAT_FormationDestroyedAddScorePoint); //フォーメーション全滅得点
            std::string s = XTOS(addscore);
            pLabel->update(s.c_str());
            pE = pLabel;

            EffectTurbo002* pTurbo002 = dispatchForceFromCommon(EffectTurbo002);
            pTurbo002->locateAs(prm_pActor);
            pTurbo002->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
            break;
        }
//            case 2: {
//                pE = dispatchFromCommon(EffectExplosion002);
//                break;
//            }
//            case 3: {
//                pE = dispatchFromCommon(EffectExplosion003);
//                break;
//            }
        default: {
            throwGgafCriticalException("対応 FormationDestroyedEffect が定義されてない。prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pE = nullptr;
            break;
        }
    }

//        if (pE) {
//            //出現座標を設定
//            pE->locateAs(prm_pActor);
//            pE->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
//        }
    return pE;
}

GgafDxDrawableActor* MyStgUtil::activateFormationDestroyedItemOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pI = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_FormationDestroyedItemKind)) {
        case 0: {
            pI = nullptr; //アイテム無し
            break;
        }
        case ITEM_MP_SMALL: {
            pI = dispatchFromCommon(MagicPointItem001);
            break;
        }
        case ITEM_MP_MIDDLE: {
            pI = dispatchFromCommon(MagicPointItem002);
            break;
        }
        default: {
            throwGgafCriticalException("対応 FormationDestroyedItem が定義されてない。prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pI = nullptr;
            break;
        }
    }
    if (pI) {
        //出現座標を設定
        pI->locateAs(prm_pActor);
    }
    return pI;
}

GgafDxDrawableActor* MyStgUtil::activateProperEffect01Of(GgafDxCore::GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pE = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_ProperEffect01Kind)) {
        case 0: {
            pE = nullptr; //エフェクト無し
            break;
        }
        case EF_TURBO: {
            //ターボエフェクト
            pE = dispatchFromCommon(EffectTurbo002);
            break;
        }
        default: {
            throwGgafCriticalException("対応 ProperEffect01 が定義されてない。prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pE = nullptr;
            break;
        }
    }
    if (pE) {
        //出現座標を設定
        pE->locateAs(prm_pActor);
    }
    return pE;

}

bool MyStgUtil::proceedEnemyHit(GgafDxDrawableActor* prm_this, GgafDxGeometricActor* prm_pOther) {
    if (UTIL::calcEnemyStamina(prm_this, prm_pOther) <= 0) { //体力が無くなったら
        //＜破壊された場合＞
        prm_this->setHitAble(false); //当たり判定消失
        if (prm_pOther->getKind() & KIND_MY) {
            //相手(自機)の種別が MY*** （自機関連） ならば
            _SCORE_ += prm_this->_pStatus->get(STAT_AddDestroyScorePoint);   //破壊時得点
            _RANK_  += prm_this->_pStatus->getDouble(STAT_AddRankPoint);     //ランク加算

            prm_this->notifyDestroyedToFormation();     //編隊全滅判定に有効な破壊のされ方でしたよ、と通知
            UTIL::activateItemOf(prm_this);             //アイテム出現
            UTIL::activateDestroyedEffectOf(prm_this);  //やられたエフェクト
            if (prm_this->getPlatformScene()->instanceOf(Obj_RankUpStage)) {
                //ランクアップステージの敵ならば、
                RankUpStage* pRankUpStage = (RankUpStage*)(prm_this->getPlatformScene());
                pRankUpStage->hit_enemy_num_ ++; //ランクアップステージの敵倒したよ！カウントアップ
            }
        }
        UTIL::activateRevengeShotOf(prm_this);     //打ち返し弾
        UTIL::activateExplosionEffectOf(prm_this); //爆発エフェクト
        prm_this->sayonara();
        return true;
    } else {
        //＜非破壊時、ダメージを受けた場合＞
        if (prm_pOther->getKind() & KIND_MY) { //相手(自機)の種別が MY*** （自機関連） ならば
            _SCORE_ += prm_this->_pStatus->get(STAT_AddDamagedScorePoint);   //ダメージ時得点
        }
        if (prm_this->_pStatus->get(STAT_FlushAble)) { //ダメージフラッシュするかどうか
            prm_this->effectFlush(2); //フラッシュ！
        }
        UTIL::activateDamagedEffectOf(prm_this); //ダメージエフェクト
        return false;
    }
}

void MyStgUtil::proceedFormationDestroyAll(GgafDxDrawableActor* prm_pActor_last_destroyed) {
    //編隊全滅時ボーナス加算
    _SCORE_ += prm_pActor_last_destroyed->_pStatus->get(STAT_FormationDestroyedAddScorePoint);
    //編隊全滅時エフェクト出現
    UTIL::activateFormationDestroyedEffectOf(prm_pActor_last_destroyed);
    //編隊全滅アイテム出現
    UTIL::activateFormationDestroyedItemOf(prm_pActor_last_destroyed);
}


// 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
// コード変更は「ステータスCreater.xls」から行うこと。
// gen02 start
GgafStatus* MyStgUtil::resetMyStraightLaserChip001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, (int)(105+((MyStraightLaserChip001::tex_no_*0.5)*100)));  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetMyOptionWateringLaserChip001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 105 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetMyOptionStraightLaserChip001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 105 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetMyTorpedoStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 1000 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetMyTorpedoBlastStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetMyShipStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 1000000 );  //体力
    p->set(STAT_Attack, 2500 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_TURBO);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyStraightLaserChip001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 105 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyCurveLaserChip001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 105 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyCeresStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyCeresShot001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 10 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyAstraeaStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 300 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 3000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip002Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip003Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip004Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyRomulusStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 2000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyRemusStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 2000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyRemusLaserChip001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyMetisStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 30000 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 20000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_RV_GOLDEN_ANG_WAY);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyIrisStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 20 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 200 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyJunoStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 20 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyThaliaStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 300 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL002);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetShot001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 2 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.01000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetShot002Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 3 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.01000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyTamago01Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyCirceStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetShot003Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetShot004Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemySylviaStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 9999999 );  //体力
    p->set(STAT_Attack, 9999999 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 1.00000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 1.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetWall001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 9999999 );  //体力
    p->set(STAT_Attack, 9999999 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 1.00000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 1.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetWall001PrismStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 9999999 );  //体力
    p->set(STAT_Attack, 9999999 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 1.00000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 1.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyPallasStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyEunomiaStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetMyShot001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 205 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyMassaliaStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 1000 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 4000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyMassaliaFragmentStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 300 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 2000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyMassaliaFragment2Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyMassaliaFragment3Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetMyOptionStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_EFFECT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetMagicPointItem001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 500 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetMagicPointItem002Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 500 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetScoreItem001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 500 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetVreathItem001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 500 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyHebeStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 10000 );  //体力
    p->set(STAT_Attack, 99 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyThisbeStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyThisbe002Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyThisbeLaserChip001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyThisbeLaserChip002Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyThisbeLaserChip003Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyAdrasteaStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 30000 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 20000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyAtalanteStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyHesperiaStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 1000 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 3000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION002);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyHesperiaLaserChip001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetTestGuStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_GU);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 30000 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetTestChokiStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 30000 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetTestPaStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_PA);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 30000 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetTestNomalStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 30000 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetTestGuShotStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_GU);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetTestChokiShotStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetTestPaShotStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_PA);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetTestNomalShotStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemySylviaEyeStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 2000 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 3000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemySylviaEyeStraightLaserChip001Status(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 105 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyHermioneStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 5000 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 4000 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_TURBO);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_SMALL001);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyHermioneArmHeadStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 9999999 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_DAMAGED001);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_TURBO);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_SMALL001);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyHermioneArmBodyStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 9999999 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_DAMAGED001);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_TURBO);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyHermioneArmWeakStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 1000 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 400 );  //体力
    p->set(STAT_Attack, 100 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_DAMAGED001);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_TURBO);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemySapphoStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_SMALL001);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyAntiopeStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00100 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_F60);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_SMALL001);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyAdelheidStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 1 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.10000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 99 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 8000 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
GgafStatus* MyStgUtil::resetEnemyPalisanaStatus(GgafStatus* p) {
    p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
    p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
    p->set(STAT_LockonAble, 0 );  //ロックオン可否
    p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点
    p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
    p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
    p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク
    p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //破壊時加算ランク減少率
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 99 );  //攻撃力
    p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
    p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
    p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    p->set(STAT_EntryEffectKind, EF_ENTRY_LARGE001);  //出現エフェクト種別
    p->set(STAT_LeaveEffectKind, EF_LEAVE_LARGE001);  //退出エフェクト種別
    p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別
    p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
    p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられエフェクト種別
    p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別
    p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
    p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //編隊全滅時エフェクト
    p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
    p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //編隊全滅時アイテム種別
    p->set(STAT_AttackShotKind, SHOT_NOTHING);  //ショット種別
    p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
    return p;
}
// gen02 end

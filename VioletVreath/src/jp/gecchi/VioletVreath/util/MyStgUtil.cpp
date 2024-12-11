#include "MyStgUtil.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/core/actor/ex/ActorDepositoryStore.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/CollisionChecker.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshinWateringLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshinStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/actor/my/MyStraightLaserChip001.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

bool MyStgUtil::_was_MyStgUtil_inited_flg = false;
double MyStgUtil::SMOOTH_DV[3600+1];
angle MyStgUtil::GOLDEN_ANG[1000];
double MyStgUtil::SHOT_POWER[300+1];
std::map<int, const char*> MyStgUtil_SeKind::mapSeId;

void MyStgUtil::init() {
    StgUtil::init();
    if (MyStgUtil::_was_MyStgUtil_inited_flg) {
        return;
    }

    //黄金角配列
    for (int n = 0; n < 1000; n++) {
        // θは黄金角
        // 1 : (1+√5) / 2 = 2π-θ : θ
        // 2π-θ = { (1+√5) / 2 } θ
        // (2π-θ) / θ = (1+√5) / 2
        // (2π/θ) - 1 = (1+√5) / 2
        // 2π/θ = 1 + {(1+√5) / 2}
        // 2π =  ( 1 + {(1+√5) / 2} ) θ
        // θ = 2π/ ( 1 + {(1+√5) / 2} )
        double n_theta = n * ( PI2 / ( 1.0 + ((1.0+sqrt(5.0))/2.0) ) );
        //標準化
        while (n_theta >= PI2) {
            n_theta -= PI2;
        }
        while (n_theta < 0) {
            n_theta += PI2;
        }
        GOLDEN_ANG[n] = (angle)(D360ANG*n_theta / PI2);
        //_TRACE_("GOLDEN_ANG["<<n<<"]="<<GOLDEN_ANG[n]);
    }

    // v = 1 - cos(2πt)の解テーブル
    for (int i = 0; i <= 3600; i++) {
        double t = double(i / 3600.0);
        //D = 1 - cos(2πt)
        SMOOTH_DV[i] = 1.0 - cos(2.0*PI*t);
    }

    for (int f = 0; f <= 300; f++) {
        double x = (double)f;
        SHOT_POWER[f] = (3.0 / ( (x/5.0) + 1 ) ) + 0.5;
    }

    MyStgUtil_SeKind::initMapSeId();//グローバル

    MyStgUtil::_was_MyStgUtil_inited_flg = true;

}

GgafDx::FigureActor* MyStgUtil::shotWayGoldenAng(coord prm_x, coord prm_y, coord prm_z,
                                                  angle prm_rz, angle prm_ry,
                                                  GgafCore::ActorDepository* prm_pDepo_shot,
                                                  coord prm_r,
                                                  int prm_way_num,
                                                  angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                                  velo prm_velo_first, acce prm_acce,
                                                  int prm_draw_set_num, frame prm_interval_frames, float prm_attenuated,
                                                  void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int)) {
    if (prm_way_num <= 0 || prm_draw_set_num <= 0) {  return nullptr;  }
    GgafDx::GeoElem* paGeo = NEW GgafDx::GeoElem[prm_way_num];
    angle expanse_rz = (D180ANG - prm_first_expanse_angle)/2;

    D3DXMATRIX matWorldRot;
    GgafDx::Util::setWorldMatrix_RzRy(GgafDx::Util::simplifyAng(prm_rz-D90ANG),prm_ry, matWorldRot);

    double vx, vy, vz;
    double tx, ty, tz; //最終方向の絶対座標の単位ベクトル
    for (int i = 0; i < prm_way_num; i++) {
        GgafDx::Util::convRzRyToVector(expanse_rz, GOLDEN_ANG[i], vx, vy, vz);
        tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
        ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
        tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
        paGeo[i].x = (coord)(tx * prm_r);
        paGeo[i].y = (coord)(ty * prm_r);
        paGeo[i].z = (coord)(tz * prm_r);
        GgafDx::Util::convVectorToRzRy(tx, ty, tz,
                                       paGeo[i].rz, paGeo[i].ry);
        expanse_rz -= (prm_inc_expanse_angle/2);
    }
    GgafDx::FigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_draw_set_num; n++) {
        for (int i = 0; i < prm_way_num; i++) {
            pActor_shot = (GgafDx::FigureActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
            if (pActor_shot) {
                dispatch_num++;
                pActor_shot->setPosition(prm_x + paGeo[i].x,
                                      prm_y + paGeo[i].y,
                                      prm_z + paGeo[i].z);
                pActor_shot->getLocusVehicle()->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_shot->getLocusVehicle()->setMvVelo(now_velo);
                pActor_shot->getLocusVehicle()->setMvAcce(now_acce);
//                pActor_shot->_rz = Rz;
//                pActor_shot->_ry = Ry;
                if (pFunc_call_back_dispatched) {
                    pFunc_call_back_dispatched(pActor_shot, dispatch_num, n, i);
                }
            }
        }
        now_velo *= prm_attenuated;
    }
    GGAF_DELETEARR(paGeo);
    return pActor_shot;
}

GgafDx::FigureActor* MyStgUtil::shotWayGoldenAng(GgafDx::GeometricActor* prm_pFrom,
                                                  GgafCore::ActorDepository* prm_pDepo_shot,
                                                  coord prm_r,
                                                  int prm_way_num,
                                                  angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                                  velo prm_velo_first, acce prm_acce,
                                                  int prm_draw_set_num, frame prm_interval_frames, float prm_attenuated,
                                                  void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int)) {
    return shotWayGoldenAng(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                            prm_pFrom->_rz, prm_pFrom->_ry,
                            prm_pDepo_shot,
                            prm_r,
                            prm_way_num,
                            prm_first_expanse_angle, prm_inc_expanse_angle,
                            prm_velo_first, prm_acce,
                            prm_draw_set_num, prm_interval_frames, prm_attenuated,
                            pFunc_call_back_dispatched);
}


int MyStgUtil::judgeAdvantage(uint32_t attribute_this, uint32_t attribute_opp) {
    int ret = 0;
    if (attribute_this & ATTRIBUTE_GU) {
        if (attribute_opp & ATTRIBUTE_CHOKI) {
            ret++;
        }
        if (attribute_opp & ATTRIBUTE_PA) {
            ret--;
        }
    }

    if (attribute_this & ATTRIBUTE_CHOKI) {
        if (attribute_opp & ATTRIBUTE_PA) {
            ret++;
        }
        if (attribute_opp & ATTRIBUTE_GU) {
            ret--;
        }
    }

    if (attribute_this & ATTRIBUTE_PA) {
        if (attribute_opp & ATTRIBUTE_GU) {
            ret++;
        }
        if (attribute_opp & ATTRIBUTE_CHOKI) {
            ret--;
        }
    }
    return ret;
}

GgafDx::FigureActor* MyStgUtil::activateCommonAttackShotOf(GgafDx::GeometricActor* prm_pActor) {
    GgafDx::FigureActor* pI = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_AttackShotKind)) {
        case 0: {
            pI = nullptr; //ショット無し
            break;
        }
        case SHOT_SMALL001: {
            pI = CommonScene_dispatch(Shot004);
            break;
        }
        default: {
            throwCriticalException("対応 AttackShot が定義されてない。prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pI = nullptr;
            break;
        }
    }
    if (pI) {
        //出現座標を設定
        pI->setPositionAt(prm_pActor);
    }
    return pI;
}

GgafCore::ActorDepository* MyStgUtil::getCommonDepositoryOf(GgafDx::GeometricActor* prm_pActor) {
    GgafCore::ActorDepository* pDepo = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_DepositoryKind)) {
        case 0: {
            pDepo = nullptr; //無し
            break;
        }
        case DEPO_LASER001: {
            pDepo = CommonScene_dispatchDepoStore(EnemyWateringLaserChip001);
            break;
        }
        case DEPO_LASER002: {
            pDepo = CommonScene_dispatchDepoStore(EnemyStraightLaserChip001);
            break;
        }
        default: {
            throwCriticalException("対応 DepositoryKind が定義されてない。prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pDepo = nullptr;
            break;
        }
    }
    return pDepo;
}


GgafDx::FigureActor* MyStgUtil::activateRevengeShotOf(GgafDx::GeometricActor* prm_pActor) {
    GgafDx::FigureActor* pI = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_RevengeShotKind)) {
        case 0: {
            pI = nullptr; //ショット無し
            break;
        }
        case SHOT_RV_NOMAL001: {
            pI = UTIL::shotWay002(
                   prm_pActor,
                   CommonScene_getDepository(Shot004),
                   PX_C(20),       //r
                   RF_SHOT_RV_NOMAL001_ShotWay(G_RANK),    //way数
                   RF_SHOT_RV_NOMAL001_Density(G_RANK),    //wayとwayの間隔
                   RF_SHOT_RV_ShotMvVelo(G_RANK),          //初期速度
                   RF_SHOT_RV_ShotMvAcce(G_RANK),          //加速度
                   RF_SHOT_RV_NOMAL001_ShotSetNum(G_RANK), //wayのセット数
                   8, //セットとセットの間隔フレーム
                   0.0f,
                   nullptr
                 );

            break;
        }

        case SHOT_RV_NOMAL002: {

            pI = UTIL::shotWay004(prm_pActor,
                                  CommonScene_getDepository(Shot004),
                                  PX_C(20),
                                  8,
                                  D_ANG(10),
                                  RF_SHOT_RV_ShotMvVelo(G_RANK),
                                  RF_SHOT_RV_ShotMvAcce(G_RANK),
                                  12,
                                  3,
                                  0.9);


            break;
        }

        case SHOT_RV_GOLDEN_ANG_WAY: {
            MyShip* pM = pMYSHIP;
            angle rz,ry;
            UTIL::convVectorToRzRy(pM->_x - prm_pActor->_x,
                                   pM->_y - prm_pActor->_y,
                                   pM->_z - prm_pActor->_z,
                                   rz, ry);

            pI = UTIL::shotWayGoldenAng(prm_pActor->_x,
                                        prm_pActor->_y,
                                        prm_pActor->_z,
                                        rz, ry,
                                        CommonScene_getDepository(Shot004),
                                        PX_C(20),
                                        300,
                                        D_ANG(1), 100,
                                        2000, 200,
                                        2, 4, 0.9);

            break;
        }

        default: {
            throwCriticalException("対応 RevengeShot が定義されてない。prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pI = nullptr;
            break;
        }
    }
    if (pI) {
    }
    return pI;
}

GgafDx::FigureActor* MyStgUtil::activateCommonItemOf(GgafDx::GeometricActor* prm_pActor) {
    GgafDx::FigureActor* pI = nullptr;
    GgafCore::Status* pPrmActorStatus = prm_pActor->getStatus();
    GgafDx::GeometricActor* pTargetActor = prm_pActor;
    if (prm_pActor->instanceOf(Obj_GgafDx_Formation)) {
        //フォーメーション場合は、最後に破壊されたアクターの座標に発生させる
        GgafDx::Formation* pFormation = (GgafDx::Formation*)prm_pActor;
        GgafDx::GeometricActor* pLastDestroyedActor = pFormation->_pLastDestroyedActor;
        if (pLastDestroyedActor) {
            pTargetActor->setPositionAt(pLastDestroyedActor);
        }
    }
    if (pTargetActor) {
        switch (pPrmActorStatus->get(STAT_ItemKind)) {
            case 0: {
                pI = nullptr; //アイテム無し
                break;
            }
            case ITEM_MP_SMALL: {
                pI = CommonScene_dispatch(MagicPointItem001);
                break;
            }
            case ITEM_MP_MIDDLE: {
                pI = CommonScene_dispatch(MagicPointItem002);
                break;
            }
            case ITEM_MP_LARGE: {
                pI = CommonScene_dispatch(MagicPointItem003);
                break;
            }
            default: {
                throwCriticalException("STAT_ItemKind が範囲外。pTargetActor="<<pTargetActor->getName()<<"("<<pTargetActor<<"),prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
                pI = nullptr;
                break;
            }
        }
    }
    if (pI) {
        //出現座標を設定
        pI->setPositionAt(pTargetActor);
    }
    return pI;
}


void MyStgUtil::adjustHitCoord(GgafDx::GeometricActor* prm_pTargetAtor, bool prm_is_adjust_part, coord& out_x, coord& out_y, coord& out_z) {
    out_x = prm_pTargetAtor->_x;
    out_y = prm_pTargetAtor->_y;
    out_z = prm_pTargetAtor->_z;
    if (prm_is_adjust_part || prm_pTargetAtor->instanceOf(Obj_LaserChip)) {
        //ヒットパートレベルに爆発位置を補正
        GgafDx::CollisionChecker* pChecker = prm_pTargetAtor->getChecker();
        if (pChecker) {
            GgafDx::CollisionArea* pCollisionArea = pChecker->_pCollisionArea;
            if (pCollisionArea) {
                GgafDx::CollisionPart* pHitPart = pCollisionArea->getHitPart();
                out_x += pHitPart->_cx;
                out_y += pHitPart->_cy;
                out_z += pHitPart->_cz;
            }
        }
    }
}
GgafDx::FigureActor* MyStgUtil::activateCommonEffectOf(GgafDx::GeometricActor* prm_pActor, int prm_status_kind, bool prm_is_adjust_part) {
    GgafCore::Status* pPrmActorStatus = prm_pActor->getStatus();
    GgafDx::GeometricActor* pTargetActor =  prm_pActor;

    //SE効果
    switch (prm_status_kind) {
        case STAT_ExplosionEffectKind: {
            //爆発SE
            int explosion_se_id = pPrmActorStatus->get(STAT_ExplosionSeKind);
            if (explosion_se_id != SE_NOTHING) {
                pTargetActor->getSeXmtr()->play3D((t_se_id) explosion_se_id);
            }
            break;
        }
        case STAT_DamagedEffectKind: {
            //ダメージSE
            int damaged_se_id = pPrmActorStatus->get(STAT_DamagedSeKind);
            if (damaged_se_id != SE_NOTHING) {
                pTargetActor->getSeXmtr()->play3D((t_se_id) damaged_se_id);
            }
            break;
        }
        //TODO:入場SE、退場SE
        default: {
            //共通SE1なし？
            break;
        }

    }

    //フォーメーション場合は、最後に破壊されたアクターの座標に発生させる(pTargetActor座標置き換え)
    if (pTargetActor->instanceOf(Obj_GgafDx_Formation)) {
        GgafDx::Formation* pFormation = (GgafDx::Formation*)pTargetActor;
        GgafDx::GeometricActor* pLastDestroyedActor = pFormation->_pLastDestroyedActor;
        if (pLastDestroyedActor) {
            pTargetActor->setPositionAt(pLastDestroyedActor);
        }
    }


/////////////
    GgafDx::FigureActor* pRet = nullptr;
    int effect_kind =  pPrmActorStatus->get(prm_status_kind);

    switch (effect_kind) {
        case 0: {
            //エフェクト無し
            pRet = nullptr;
            break;
        }
        case EF_EXPLOSION001: {
            EffectExplosion001* pE = CommonScene_dispatchForce(EffectExplosion001);
            coord out_x, out_y, out_z;
            MyStgUtil::adjustHitCoord(pTargetActor, prm_is_adjust_part, out_x, out_y, out_z);
            pE->setPosition(out_x, out_y, out_z);
            pE->getLocusVehicle()->takeoverFrom(pTargetActor->getLocusVehicle());
            pRet = pE;
            break;
        }
        case EF_EXPLOSION002: {
            EffectExplosion002* pE = CommonScene_dispatchForce(EffectExplosion002);
            coord out_x, out_y, out_z;
            MyStgUtil::adjustHitCoord(pTargetActor, prm_is_adjust_part, out_x, out_y, out_z);
            pE->setPosition(out_x, out_y, out_z);
            pE->getLocusVehicle()->takeoverFrom(pTargetActor->getLocusVehicle());
            pRet = pE;
            break;
        }
        case EF_EXPLOSION003: {
            EffectExplosion003* pE = CommonScene_dispatchForce(EffectExplosion003);
            coord out_x, out_y, out_z;
            MyStgUtil::adjustHitCoord(pTargetActor, prm_is_adjust_part, out_x, out_y, out_z);
            pE->setPosition(out_x, out_y, out_z);
            pE->getLocusVehicle()->takeoverFrom(pTargetActor->getLocusVehicle());
            pRet = pE;
            break;
        }
        case EF_EXPLOSION001_STAY: {
            EffectExplosion001* pE = CommonScene_dispatchForce(EffectExplosion001);
            coord out_x, out_y, out_z;
            MyStgUtil::adjustHitCoord(pTargetActor, prm_is_adjust_part, out_x, out_y, out_z);
            pE->setPosition(out_x, out_y, out_z);
            pE->getLocusVehicle()->setMvVelo(0);
            pE->getLocusVehicle()->setMvAcce(0);
            pRet = pE;
            break;
        }
/////////
        case EF_DAMAGED001: {
            EffectExplosion001* pE = CommonScene_dispatchForce(EffectExplosion001);
            //出現座標を設定
            pE->setPositionAt(pTargetActor);
            pE->getLocusVehicle()->takeoverFrom(pTargetActor->getLocusVehicle());
            pRet = pE;
            break;
        }
/////////
        case EF_ENTRY_SMALL001_LONG: { //EffectBlink001で210F。アクターに追従する。
            EffectBlink001* pE = CommonScene_dispatchForce(EffectBlink001);
            pE->blink(30, 120, 60, pTargetActor);
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_F30: { //EffectBlink001で30F。アクターに追従する。
            EffectBlink001* pE = CommonScene_dispatchForce(EffectBlink001);
            pE->blink(12, 6, 12, pTargetActor);
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_F60: { //EffectBlink001で60F。アクターに追従する。
            EffectBlink001* pE = CommonScene_dispatchForce(EffectBlink001);
            pE->blink(25, 10, 25, pTargetActor);
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_F90: { //EffectBlink001で60F。アクターに追従する。
            EffectBlink001* pE = CommonScene_dispatchForce(EffectBlink001);
            pE->blink(35, 20, 35, pTargetActor);
            pRet = pE;
            break;
        }

        case EF_ENTRY_SMALL001_STAY_F30: { //EffectBlink001で60F。その場にとどまる、アクター追従無し。
            EffectBlink001* pE = CommonScene_dispatchForce(EffectBlink001);
            pE->setPositionAt(pTargetActor);
            pE->blink(12, 6, 12, nullptr);
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_STAY_F60: {  //EffectBlink001で60F。その場にとどまる、アクター追従無し。
            EffectBlink001* pE = CommonScene_dispatchForce(EffectBlink001);
            pE->setPositionAt(pTargetActor);
            pE->blink(25, 10, 25, nullptr);
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_STAY_F90: {  //EffectBlink001で60F。その場にとどまる、アクター追従無し。
            EffectBlink001* pE = CommonScene_dispatchForce(EffectBlink001);
            pE->setPositionAt(pTargetActor);
            pE->blink(35, 20, 35, nullptr);
            pRet = pE;
            break;
        }
        case EF_ENTRY_MIDDLE001: {  //EffectBlink002で180F。アクターに追従する。
            EffectBlink002* pE = CommonScene_dispatchForce(EffectBlink002);
            pE->blink(60, 60, 60, pTargetActor);
            pRet = pE;
            break;
        }
        case EF_ENTRY_LARGE001: {
            EffectBlink003* pE = CommonScene_dispatchForce(EffectBlink003);
            pE->blink(60, 60, 60, pTargetActor);
            pRet = pE;
            break;
        }
//////////////////
        case EF_LEAVE_SMALL001_F30: {
            EffectBlink001* pE = CommonScene_dispatchForce(EffectBlink001);
            pE->blink(10, 1, 20, pTargetActor);
            break;
        }
        case EF_LEAVE_SMALL001_F60: {
            EffectBlink001* pE = CommonScene_dispatchForce(EffectBlink001);
            pE->blink(20, 0, 40, pTargetActor);
            pRet = pE;
            break;
        }
        case EF_LEAVE_SMALL001_F90: {
            EffectBlink001* pE = CommonScene_dispatchForce(EffectBlink001);
            pE->blink(30, 0, 60, pTargetActor);
            pRet = pE;
            break;
        }
        case EF_LEAVE_MIDDLE001: {
            EffectBlink002* pE = CommonScene_dispatchForce(EffectBlink002);
            pE->blink(20, 0, 40, pTargetActor);
            pRet = pE;
            break;
        }
        case EF_LEAVE_LARGE001: {
            EffectBlink003* pE = CommonScene_dispatchForce(EffectBlink003);
            pE->blink(20, 0, 40, pTargetActor);
            pRet = pE;
            break;
        }
        ///////
        case EF_BONUS001: {
            //スコアが表示される消滅エフェクト
            SpriteLabelBonus001* pLabel = CommonScene_dispatchForce(SpriteLabelBonus001);
            pLabel->onDispatched(pTargetActor); //初期設定が行われる
            std::string s = XTOS(pPrmActorStatus->get(STAT_AddDestroyScorePoint));
            pLabel->update(s.c_str()); //破壊時得点が表示される
            pRet = pLabel;
            break;
        }
        case EF_BONUS_FORMATION: {
            //スコアが表示される消滅エフェクト
            SpriteLabelBonus002* pLabel = CommonScene_dispatchForce(SpriteLabelBonus002);
            pLabel->onDispatched(pTargetActor); //初期設定が行われる
            std::string s = XTOS(pPrmActorStatus->get(STAT_AddDestroyScorePoint));
            pLabel->update(s.c_str()); //破壊時得点が表示される
            pRet = pLabel;
            break;
        }

        case EF_TURBO: {
            //ターボエフェクト
            EffectTurbo002* pE = CommonScene_dispatch(EffectTurbo002);
            pRet = pE;
            break;
        }
        default: {
            throwCriticalException("対応 Effect が定義されてない。prm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<") prm_status_kind="<<prm_status_kind<<" effect_kind="<< effect_kind);
            pRet = nullptr;
            break;
        }
    }
    return pRet;
}

void MyStgUtil::registerCommonSeOf(GgafDx::GeometricActor* prm_pActor) {
    t_se_id se_id = prm_pActor->getStatus()->get(STAT_ExplosionSeKind);
    if (se_id != SE_NOTHING) {
        prm_pActor->getSeXmtr()->set(se_id, MyStgUtil_SeKind::mapSeId[se_id]);
    }
    se_id = prm_pActor->getStatus()->get(STAT_DamagedSeKind);
    if (se_id != SE_NOTHING) {
        prm_pActor->getSeXmtr()->set(se_id, MyStgUtil_SeKind::mapSeId[se_id]);
    }
}
// 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
// コード変更は「ステータスCreater.xls」から行うこと。
// gen02 start
GgafCore::Status* MyStgUtil::resetDefaultStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_EFFECT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_NOTHING);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyShipStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 600000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_TURBO);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyShot001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 205 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_PA);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMySnipeShot001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 305 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_PA);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyMagicEnergyCoreStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_NOTHING);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyStraightLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, (int)(105+((MyStraightLaserChip001::tex_no_*0.5)*100)));  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyBunshinStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_EFFECT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyBunshinShot001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 205 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_PA);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyBunshinSnipeShot001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 305 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_PA);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyBunshinStraightLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, (int)(105+((MyBunshinStraightLaserChip001::tex_no_*0.5)*100)));  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyBunshinWateringLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, (int)(105+((MyBunshinWateringLaserChip001::tex_no_*0.5)*100)));  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyTorpedoStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 1000 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_GU);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyTorpedoBlastStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_GU);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetShot001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 2 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_002);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetShot002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 3 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_002);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetShot003Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetShot004Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyStraightLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 105 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyWateringLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 105 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEresStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEresShot001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 10 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationEres001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 3000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationEres002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 5000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyStraeaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 3000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 300 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_MIDDLE001);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyStraeaLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyStraeaLaserChip002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyStraeaLaserChip003Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyStraeaLaserChip004Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOmulusStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 2000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEmusStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 2000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_LASER001);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEmusLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEtisStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 20000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 30000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_RV_GOLDEN_ANG_WAY);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationEtis001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 12345 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyRisStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 20 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationRis001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 3000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationRis002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 4000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyGeriaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 20 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F60);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyHaliaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 300 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_F90);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL002);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationHaliaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 1000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyTamago01Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyIrceStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyRatislaviaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 9999999 );  //体力
    p->set(STAT_Attack, 9999999 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 1.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 1.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyAllasStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationAllas001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 1000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationAllas002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 2000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyUnomiaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationUnomia001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 5000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationUnomia002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 6000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEmiliaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 4000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 1000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEmiliaFragmentStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 2000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 300 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEmiliaFragment2Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEmiliaFragment3Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMagicPointItem001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMagicPointItem002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMagicPointItem003Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetScoreItem001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 500 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetVreathItem001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 500 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEbeStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 10000 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationEbe001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 5000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyHisbeStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyHisbe002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyHisbeLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyHisbeLaserChip002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyHisbeLaserChip003Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyDrasteaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 20000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 30000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationDrastea001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 5000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyTalanteStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEsperiaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 3000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 1000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_MIDDLE001);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION002);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEsperiaLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestGuStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_GU);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 30000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestChokiStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 30000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestPaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_PA);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 30000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestNomalStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 30000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestGuShotStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_GU);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestChokiShotStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestPaShotStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_PA);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestNomalShotStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyRatislaviaEyeStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 3000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 2000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_LARGE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyRatislaviaEyeStraightLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 105 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyErmioneStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 4000 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 5000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_TURBO);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_SMALL001);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyErmioneArmHeadStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 9999999 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_DAMAGED001);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_TURBO);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_SMALL001);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_LASER001);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyErmioneArmBodyStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 9999999 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_DAMAGED001);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_TURBO);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyErmioneArmWeakStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 400 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 1000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_DAMAGED001);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_TURBO);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyApphoStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_SMALL001);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationAppho001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 5000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyAntiopeStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_SMALL001);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyDelheidStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationDelheid001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 5000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyAlisanaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_LARGE001);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_LARGE001);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyIdaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 10000 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_F60);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationIda001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 999 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyThagorasStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 300 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationThagoras001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 121212 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationThagoras002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 343434 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOrtunaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_SMALL001);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationOrtuna001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 5000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyGlajaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 1000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 10 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_F60);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_SMALL001);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyGlajaLance001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyDunaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 400 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 300 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_SMALL001);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOzartiaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 50000 );  //体力
    p->set(STAT_Attack, 300 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 5000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 100 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_LARGE001);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_DAMAGED001);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_LARGE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOzartiaShot01Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 5000 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 1 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 100 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 1 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_F60);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOzartiaLaserChip01Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 105 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOzartiaPillar01Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //体力
    p->set(STAT_Attack, 1000 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_F60);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_NOTHING);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOebiusStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 300 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOebiusCoreStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 5000 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 300 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_MIDDLE001);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationOebius001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 111111 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationOebius002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 222222 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyErelmanStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 300 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationErelman001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 6000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationErelman002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 7000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationErelman003Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 8000 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyErelmanCoreStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 5000 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 300 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_MIDDLE001);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyUrydikeStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 99 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 300 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00001 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationUrydike001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 56789 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetFormationUrydike002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //体力
    p->set(STAT_Attack, 0 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_FORMATION);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 98765 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_MIDDLE_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_BONUS_FORMATION);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetAliceShotStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //体力
    p->set(STAT_Attack, 100 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_NOTHING);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_NOTHING);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_NOTHING);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetWall01Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 9999999 );  //体力
    p->set(STAT_Attack, 9999999 );  //基本攻撃力
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //種別(デフォルト)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //優劣属性
        p->set(STAT_LockonAble, 0 );  //ロックオン可否(1:可/0:不可)
        p->set(STAT_AddDestroyScorePoint, 0 );  //破壊時加算得点(編隊は全滅時)
        p->set(STAT_AddDamagedScorePoint, 0 );  //ダメージ時加算得点
        p->set(STAT_FlushAble, 0 );  //ダメージ時フラッシュ要否
        p->set(STAT_AddRankPoint, 0.00000 );  //破壊時加算ランク初期値
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //フレーム毎ランク縮小倍率
        p->set(STAT_AttackPowerRate, 1.00000 );  //攻撃力に乗じられる率
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 1.00000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 1.00000 );  //劣性時の防御率
        p->set(STAT_EntryEffectKind, EF_NOTHING);  //出現エフェクト種別
        p->set(STAT_LeaveEffectKind, EF_NOTHING);  //退出エフェクト種別
        p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //爆発エフェクト種別(編隊は全滅時)
        p->set(STAT_ExplosionSeKind, SE_EXPLOSION_001);  //爆発SE種別(編隊は全滅時)
        p->set(STAT_DamagedEffectKind, EF_NOTHING);  //ダメージエフェクト種別
        p->set(STAT_DamagedSeKind, SE_ENEMY_DAMAGED_001);  //ダメージSE種別
        p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //やられ特殊エフェクト種別(編隊は全滅時)
        p->set(STAT_ItemKind, ITEM_MP_SMALL);  //やられアイテム種別(編隊は全滅時)
        p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //その他固有エフェクト０１
        p->set(STAT_AttackShotKind, SHOT_NOTHING);  //通常ショット種別
        p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //打ち返し種別
        p->set(STAT_DepositoryKind, DEPO_NOTHING);  //デポジトリ種別
    }
    return p;
}
// gen02 end

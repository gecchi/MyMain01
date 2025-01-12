#include "EnemyStraeaLaserChip002.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafLib;
using namespace VioletVreath;

EnemyStraeaLaserChip002::EnemyStraeaLaserChip002(const char* prm_name) :
        VvEnemyActor<RefractionLaserChip>(prm_name, "StraeaLaserChip001", StatusReset(EnemyStraeaLaserChip002)) {
    _class_name = "EnemyStraeaLaserChip002";
    pConn_pRefractionEffectDepository_ = nullptr;
}

void EnemyStraeaLaserChip002::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);
}

void EnemyStraeaLaserChip002::onActive() {
    RefractionLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setMvVelo(80000);
    //_pLocusVehicle->setMvAcce(300);
    //_pLocusVehicle->forceRyMvAngVeloRange(-90000, 90000);
    pLocusVehicle->linkFaceAngByMvAng(true);
}

void EnemyStraeaLaserChip002::onRefractionInto(int prm_num_refraction)  {

}

void EnemyStraeaLaserChip002::onRefractionOutOf(int prm_num_refraction)  {
    if (prm_num_refraction == 0) {

    } else {
        GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
        angle out_rz_Target;
        angle out_ry_Target;
        angle out_d_rz;
        angle out_d_ry;
        UTIL::convVectorToRzRy(pMYSHIP->_x - _x,
                               pMYSHIP->_y - _y,
                               pMYSHIP->_z - _z,
                               out_rz_Target,
                               out_ry_Target);
        out_d_rz = pLocusVehicle->getRzMvAngDistance(out_rz_Target, TURN_CLOSE_TO);
        out_d_ry = pLocusVehicle->getRyMvAngDistance(out_ry_Target, TURN_CLOSE_TO);
        pLocusVehicle->addRzMvAng(SGN(out_d_rz)*20000);
        pLocusVehicle->addRyMvAng(SGN(out_d_ry)*30000);
//        pLocusVehicle->turnMvAngTwd(
//                        pMYSHIP,
//                        90000, 0,
//                        TURN_CLOSE_TO, false);

//        pLocusVehicle->setMvAngTwd(pMYSHIP);
    }
}

void EnemyStraeaLaserChip002::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

EnemyStraeaLaserChip002::~EnemyStraeaLaserChip002() {
}


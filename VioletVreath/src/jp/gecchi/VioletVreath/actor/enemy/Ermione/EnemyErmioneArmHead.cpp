#include "stdafx.h"
#include "EnemyErmioneArmHead.h"
#include "EnemyErmione.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyErmioneArmHead::EnemyErmioneArmHead(const char* prm_name) :
        EnemyErmioneArm(prm_name, "ErmioneArmHead", STATUS(EnemyErmioneArmHead)) {
    _class_name = "EnemyErmioneArmHead";
//    pDepoConnection_ = connect_DepositoryManager("Shot004"); //弾
//    pDepo_Fired_ = pDepoConnection_->peek();
}

void EnemyErmioneArmHead::onCreateModel() {
}

void EnemyErmioneArmHead::initialize() {
    EnemyErmioneArm::initialize();
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
    _pScaler->setScale(1000);
    _pScaler->forceRange(1000, 1200);
    _pScaler->beat(30, 5, 5, -1);
}


void EnemyErmioneArmHead::processBehavior() {
    EnemyErmioneArm::processBehavior();

    if (getActiveFrame() % 10U == 0 &&
        (_pProg->get() == PROG_NOTHING || _pProg->get() == PROG_AIMING)) { //出現間隔
        GgafDxDrawableActor* pShot = UTIL::activateAttackShotOf(this);
        if (pShot) {
            //＜現在の最終的な向きを、RzRyで取得する＞
            //方向ベクトルはワールド変換行列の積（_matWorldRotMv)で変換され、現在の最終的な向きに向く。
            //元の方向ベクトルを(x_org_,y_org_,z_org_)、
            //ワールド変換行列の回転部分の積（_matWorldRotMv)の成分を mat_xx、
            //最終的な方向ベクトルを(vX, vY, vZ) とすると
            //
            //                          | mat_11 mat_12 mat_13 |
            // | x_org_ y_org_ z_org_ | | mat_21 mat_22 mat_23 | = | vX vY vZ |
            //                          | mat_31 mat_32 mat_33 |
            //
            //vX = x_org_*mat_11 + y_org_*mat_21 + z_org_*mat_31
            //vY = x_org_*mat_12 + y_org_*mat_22 + z_org_*mat_32
            //vZ = x_org_*mat_13 + y_org_*mat_23 + z_org_*mat_33
            //
            //さてここで、元々が前方の単位方向ベクトル(1,0,0)の場合はどうなるか考えると
            //
            //vX = x_org_*mat_11
            //vY = x_org_*mat_12
            //vZ = x_org_*mat_13
            //
            //となる。本アプリでは、モデルは全て(1,0,0)を前方としているため
            //最終的な方向ベクトルは（x_org_*mat_11, x_org_*mat_12, x_org_*mat_13) である。
            angle rz, ry;
            UTIL::convVectorToRzRy(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13,
                                   rz, ry); //現在の最終的な向きを、RzRyで取得！
            pShot->_pKurokoA->setRzRyMvAng(rz, ry); //RzRyでMoverに設定
            pShot->positionAs(this);
            pShot->reset();
        }
    }

}


void EnemyErmioneArmHead::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
//        setHitAble(false);
//        //爆発効果
//        UTIL::activateExplosionEffectOf(this);
//        _pSeTx->play3D(SE_EXPLOSION);
//
//        //自機側に撃たれて消滅の場合、
//        if (pOther->getKind() & KIND_MY) {
//            //アイテム出現
//            UTIL::activateItemOf(this);
//        }
//        sayonara();
//    } else {
//        //非破壊時
//        effectFlush(2); //フラッシュ
//        _pSeTx->play3D(SE_DAMAGED);
//    }
}


EnemyErmioneArmHead::~EnemyErmioneArmHead() {
//    pDepoConnection_->close();
}

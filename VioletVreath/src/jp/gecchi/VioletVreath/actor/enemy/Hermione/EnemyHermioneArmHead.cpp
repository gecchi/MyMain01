#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyHermioneArmHead::EnemyHermioneArmHead(const char* prm_name) :
        EnemyHermioneArm(prm_name, "HermioneArmHead", STATUS(EnemyHermioneArmHead)) {
    _class_name = "EnemyHermioneArmHead";
    pDpcon_ = connectToDepositoryManager("Conn_Shot004", nullptr); //弾
    pDepo_Fired_ = pDpcon_->fetch();
}

void EnemyHermioneArmHead::onCreateModel() {
}

void EnemyHermioneArmHead::initialize() {
    EnemyHermioneArm::initialize();
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(1000, 1200);
    _pScaler->beat(30, 5, 5, -1);
}


void EnemyHermioneArmHead::processBehavior() {
    EnemyHermioneArm::processBehavior();

    //弾発射
    if (getActivePartFrame() % 10 == 0) { //出現間隔
        GgafDxDrawableActor* pActor = (GgafDxDrawableActor*)pDepo_Fired_->dispatch();
        if (pActor) {
            //＜現在の最終的な向きを、RzRyで取得する＞
            //方向ベクトルはワールド変換行列の積（_matWorldRotMv)で変換され、現在の最終的な向きに向く。
            //元の方向ベクトルを(Xorg_,Yorg_,Zorg_)、
            //ワールド変換行列の回転部分の積（_matWorldRotMv)の成分を mat_xx、
            //最終的な方向ベクトルを(vX, vY, vZ) とすると
            //
            //                      | mat_11 mat_12 mat_13 |
            //| Xorg_ Yorg_ Zorg_ | | mat_21 mat_22 mat_23 | = | vX vY vZ |
            //                      | mat_31 mat_32 mat_33 |
            //
            //vX = Xorg_*mat_11 + Yorg_*mat_21 + Zorg_*mat_31
            //vY = Xorg_*mat_12 + Yorg_*mat_22 + Zorg_*mat_32
            //vZ = Xorg_*mat_13 + Yorg_*mat_23 + Zorg_*mat_33
            //
            //さてここで、元々が前方の単位方向ベクトル(1,0,0)の場合はどうなるか考えると
            //
            //vX = Xorg_*mat_11
            //vY = Xorg_*mat_12
            //vZ = Xorg_*mat_13
            //
            //となる。本アプリでは、モデルは全て(1,0,0)を前方としているため
            //最終的な方向ベクトルは（Xorg_*mat_11, Xorg_*mat_12, Xorg_*mat_13) である。
            angle Rz, Ry;
            UTIL::getRzRyAng(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13,
                             Rz, Ry); //現在の最終的な向きを、RzRyで取得！
            pActor->_pKurokoA->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
            pActor->locateWith(this);
            pActor->reset();
        }
    }

}


void EnemyHermioneArmHead::onHit(GgafActor* prm_pOtherActor) {
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


EnemyHermioneArmHead::~EnemyHermioneArmHead() {
    pDpcon_->close();
}

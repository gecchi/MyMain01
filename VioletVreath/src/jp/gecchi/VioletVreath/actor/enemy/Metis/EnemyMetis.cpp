#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMetis::EnemyMetis(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Metis", STATUS(EnemyMetis)) {
    _class_name = "EnemyMetis";
    width_X_ = 220*2*LEN_UNIT;
    height_Z_ = 220*2*LEN_UNIT;
    depth_Y_ = 36*2*LEN_UNIT;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");

    pConn_ShotDepo_ = connectToDepositoryManager("Conn_Shot004", nullptr);
    pDepo_Shot_ = pConn_ShotDepo_->fetch();
}

void EnemyMetis::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyMetis::initialize() {
    int nArea = 0;
    for (int i = 0; i < (width_X_ - depth_Y_) ; i+= depth_Y_) {
        nArea++;
    }
    _pColliChecker->makeCollision(nArea);
    for (int i = 0, n = 0; i < width_X_-depth_Y_; i += depth_Y_, n++) {
        _pColliChecker->setColliAAB(n,
                                    i - ((depth_Y_/2.0)/1.5)-(width_X_/2 - depth_Y_/2.0), -((depth_Y_/2.0)/1.5), -(height_Z_/2.0),
                                    i + ((depth_Y_/2.0)/1.5)-(width_X_/2 - depth_Y_/2.0),  ((depth_Y_/2.0)/1.5),  (height_Z_/2.0),
                                    false, false, true );
    }
}

void EnemyMetis::onActive() {
    _pStatus->reset();
    setAlpha(1.0);
    _pKurokoA->setMvVelo(0);
    _pKurokoB->setVxMvVelo(-3000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 1000);
    static coord appearances_renge_Z = (MyShip::lim_zleft_ - MyShip::lim_zright_) * 3;
    static coord appearances_renge_Y = (MyShip::lim_top_ - MyShip::lim_bottom_) * 3;
    _X = GgafDxUniverse::_X_goneRight - 1000;
    _Y = RND(-(appearances_renge_Y/2) , +(appearances_renge_Y/2));
    _Z = RND(-(appearances_renge_Z/2) , +(appearances_renge_Z/2));
    setHitAble(true);
}

void EnemyMetis::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //座標に反映
    _pKurokoA->behave();
    _pKurokoB->behave();
    _pSeTx->behave();
}

void EnemyMetis::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyMetis::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //爆発効果
        UTIL::activateExplosionEffectOf(this);
        _pSeTx->play3D(SE_EXPLOSION);

        //打ち返し弾
        if (pDepo_Shot_) {
            MyShip* pM = P_MYSHIP;
            angle rz,ry;
            UTIL::getRzRyAng(pM->_X - _X,
                             pM->_Y - _Y,
                             pM->_Z - _Z,
                             rz, ry);
            UTIL::shotWayGoldenAng(_X, _Y, _Z,
                                   rz, ry,
                                   pDepo_Shot_,
                                   PX_C(20),
                                   300,
                                   D_ANG(1), 100,
                                   2000, 200,
                                   2, 4, 0.9);
        }
        //自機側に撃たれて消滅の場合、
        if (pOther->getKind() & KIND_MY) {
            //アイテム出現
            UTIL::activateItemOf(this);
        }
        sayonara();
    } else {
        //非破壊時
        effectFlush(2); //フラッシュ
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyMetis::onInactive() {
    sayonara();
}

EnemyMetis::~EnemyMetis() {
    pConn_ShotDepo_->close();
}


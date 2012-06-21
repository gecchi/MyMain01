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
    iMovePatternNo_ = 0;
    _pSeTx->useSe(2);
    _pSeTx->set(0, "yume_shototsu", GgafRepeatSeq::nextVal("CH_MetisHit"));
    _pSeTx->set(1, "bom10", GgafRepeatSeq::nextVal("CH_MetisDestroy"));     //爆発

    pCon_ShotDepo_ = connectDepositoryManager("DpCon_Shot004", NULL);
    pDepo_Shot_ = pCon_ShotDepo_->fetch();
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
    for (int i = 0, n = 0; i < (width_X_ - depth_Y_)  ; i+= depth_Y_, n++) {
        _pColliChecker->setColliAAB(n, i - ((depth_Y_/2.0)/1.5)-(width_X_/2 - depth_Y_/2.0), -((depth_Y_/2.0)/1.5), -(height_Z_/2.0),
                                           i + ((depth_Y_/2.0)/1.5)-(width_X_/2 - depth_Y_/2.0),  ((depth_Y_/2.0)/1.5),  (height_Z_/2.0),
                                           false, false, true
                                       );
    }
}

void EnemyMetis::onActive() {
    _pStatus->reset();
    iMovePatternNo_ = 0;
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
    //_pSeTx->behave();
}

void EnemyMetis::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyMetis::onHit(GgafActor* prm_pOtherActor) {
    if (_pStatus->get(STAT_Stamina) < 0) {
        return;
    }
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    //ここにヒットエフェクト
    effectFlush(2); //フラッシュ
    _pSeTx->play3D(0);
        //ここに消滅エフェクト
    if (pOther->getKind() & KIND_MY) {
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        if (pExplo001) {
            pExplo001->locateWith((GgafDxGeometricActor*)prm_pOtherActor);
            pExplo001->activate();
        }
    } else {
        //地形だったらエフェクトなし（地形の真ん中に表示されてしまうため);
    }
    if (UTIL::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //ここに消滅エフェクト

        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        _pSeTx->play3D(1);
        if (pExplo001) {
            pExplo001->locateWith((GgafDxGeometricActor*)prm_pOtherActor);
            pExplo001->activate();
        }
        sayonara();

        //アイテム出現
        Item* pItem = employFromCommon(MagicPointItem001);
        if (pItem) {
            pItem->locateWith(this);
        }

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
    }
}

void EnemyMetis::onInactive() {
    sayonara();
}
EnemyMetis::~EnemyMetis() {
    pCon_ShotDepo_->close();
}

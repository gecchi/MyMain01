#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Torus::Torus(const char* prm_name) : GroundMeshActor(prm_name, "Torus") {
    _class_name = "Torus";
    MyStgUtil::resetTorusStatus(_pStatus);
    _r1 = 2000*1000; //トーラス半径1
    _r2 = 800*1000;  //トーラス半径2
    EnemyVesta* pEV1 = NEW EnemyVesta("pEV1");
    EnemyVesta* pEV2 = NEW EnemyVesta("pEV2");
    EnemyVesta* pEV3 = NEW EnemyVesta("pEV3");
    EnemyVesta* pEV4 = NEW EnemyVesta("pEV4");

    this->addSubBone(pEV1,  _r2  ,  _r1    ,     0, ANGLE0, ANGLE0, ANGLE0);
    this->addSubBone(pEV2,  0    ,  _r1+_r2,     0, ANGLE0, ANGLE90, ANGLE0);
    this->addSubBone(pEV4,  -_r2 ,  _r1    ,     0, ANGLE0, ANGLE180, ANGLE0);
    this->addSubBone(pEV3,  0    ,  _r1-_r2,     0, ANGLE0, ANGLE270, ANGLE0);
}

void Torus::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.4, 3.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.5);
    _pGgafDx9Model->_pTextureBlinker->beat(60*20, 60*9, 60*3, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.7;
}

void Torus::initialize() {
    setHitAble(true);

    int nSphere = 16;    //当たり判定球の数;
    angle* paAngRadial = NEW angle[nSphere];
    GgafDx9Util::getRadialAngle2D(0, nSphere, paAngRadial);
    _pCollisionChecker->makeCollision(nSphere);
    for (int i = 0; i < nSphere; i++) {
        _pCollisionChecker->setColliSphere(
                i,
                0 , GgafDx9Util::SIN[paAngRadial[i]/ANGLE_RATE] * _r1, GgafDx9Util::COS[paAngRadial[i]/ANGLE_RATE] * _r1,
                _r2*0.95,
                false, true, true
                );
    }
    DELETE_IMPOSSIBLE_NULL(paAngRadial);
    setAlpha(1.00);
    _X = GgafDx9Core::GgafDx9Universe::_X_goneRight+_r1+_r2;
    _pMover->setRzRyMvAng(ANGLE180, 0);
    _pMover->setMvVelo(1000);
    _pMover->setFaceAngVelo(AXIS_Z, 100);
    _pMover->setFaceAngVelo(AXIS_Y, 200);
}

void Torus::onActive() {
    MyStgUtil::resetTorusStatus(_pStatus);
}

void Torus::processBehavior() {
    //座標に反映
    _pMover->behave();
}

void Torus::processJudgement() {
}

void Torus::onHit(GgafActor* prm_pOtherActor) {
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry((GgafDx9GeometricActor*)prm_pOtherActor);
        pExplo001->activate();
    }
}

Torus::~Torus() {
}

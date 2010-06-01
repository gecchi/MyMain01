#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Torus::Torus(const char* prm_name, const char* prm_model, int prm_r1, int prm_r2) : GroundMeshActor(prm_name, prm_model) {
    _class_name = "Torus";
    MyStgUtil::resetTorusStatus(_pStatus);
    _r1 = prm_r1;
    _r2 = prm_r2;
}

void Torus::addSubBoneOnSurface(GgafDx9GeometricActor* prm_pGeoActor, angle prm_angPos1, angle prm_angPos2) {
    //トーラスはZY平面に円
    s_ang angPos1 = prm_angPos1 /ANGLE_RATE;
    s_ang angPos2 = prm_angPos2 /ANGLE_RATE;
    //位置を求める
    //平行移動( +_r2, +0, +0) > angPos2のY軸回転 > 平行移動( +0, +0, -_r1) > angPos1のX軸回転 変換行列の dx, dy, dz を使用
    //    | COS[angPos2]    , -SIN[angPos2]*-SIN[angPos1]             , -SIN[angPos2]*COS[angPos1]             , 0 |
    //    | 0               , COS[angPos1]                            , SIN[angPos1]                           , 0 |
    //    | SIN[angPos2]    , COS[angPos2]*-SIN[angPos1]              , COS[angPos2]*COS[angPos1]              , 0 |
    //    | _r2*COS[angPos2], (_r2*-SIN[angPos2] + -_r1)*-SIN[angPos1], (_r2*-SIN[angPos2] + -_r1)*COS[angPos1], 1 |
    double X = _r2*GgafDx9Util::COS[angPos2];
    double Y = (_r2*-GgafDx9Util::SIN[angPos2] - _r1) * -GgafDx9Util::SIN[angPos1];
    double Z = (_r2*-GgafDx9Util::SIN[angPos2] - _r1) *  GgafDx9Util::COS[angPos1];

    //向きを求める
    //平行移動( +0, +0, -_r1) > angPos1のX軸回転 変換行列の dx, dy, dz を使用
    //    | 1, 0                 , 0                , 0 |
    //    | 0, COS[angPos1]      , SIN[angPos1]     , 0 |
    //    | 0, -SIN[angPos1]     , COS[angPos1]     , 0 |
    //    | 0, -_r1*-SIN[angPos1], -_r1*COS[angPos1], 1 |
    double CX = 0;
    double CY = -_r1*-GgafDx9Util::SIN[angPos1];
    double CZ = -_r1*GgafDx9Util::COS[angPos1];
    angle angRz, angRy;
    GgafDx9Util::getRzRyAng((int)(X - CX), (int)(Y - CY), (int)(Z - CZ), angRz, angRy);
    //ボーンとして追加
    this->addSubBone(prm_pGeoActor, X, Y, Z, ANGLE0, angRz, angRy);
}

void Torus::makeCollisionArea(int prm_nSphere){
    angle* paAngRadial = NEW angle[prm_nSphere];
    GgafDx9Util::getRadialAngle2D(0, prm_nSphere, paAngRadial);
    _pCollisionChecker->makeCollision(prm_nSphere);
    for (int i = 0; i < prm_nSphere; i++) {
        _pCollisionChecker->setColliSphere(
                i,
                0 , GgafDx9Util::SIN[paAngRadial[i]/ANGLE_RATE] * _r1, GgafDx9Util::COS[paAngRadial[i]/ANGLE_RATE] * _r1,
                _r2*0.98,
                false, true, true
                );
    }
    DELETE_IMPOSSIBLE_NULL(paAngRadial);
}

void Torus::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.2, 3.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.5);
    _pGgafDx9Model->_pTextureBlinker->beat(60*20, 60*9, 60*3, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.7;
}

void Torus::onActive() {
    MyStgUtil::resetTorusStatus(_pStatus);
}

void Torus::processJudgement() {
    if (wasDeclaredEnd() == false && isOutOfGameSpace()) {
        sayonara(2000);
    }
}

void Torus::onHit(GgafActor* prm_pOtherActor) {
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry((GgafDx9GeometricActor*)prm_pOtherActor);
        pExplo001->activate();
    }
}

int Torus::isOffscreen() {
    //視野外判定不要
    return 0;
}
Torus::~Torus() {
}

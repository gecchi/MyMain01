#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Torus::Torus(const char* prm_name, const char* prm_model) : GroundMeshActor(prm_name, prm_model) {
    _class_name = "Torus";
    MyStgUtil::resetTorusStatus(_pStatus);
    _r1 = 2000*1000; //ƒg[ƒ‰ƒX”¼Œa1
    _r2 = 800*1000;  //ƒg[ƒ‰ƒX”¼Œa2
}

void Torus::addSubBoneOnSurface(GgafDx9GeometricActor* prm_pGeoActor, angle prm_angPos1, angle prm_angPos2) {
    //ƒg[ƒ‰ƒX‚ÍZY•½–Ê‚É‰~
    s_ang angPos1 = prm_angPos1 /ANGLE_RATE;
    s_ang angPos2 = prm_angPos2 /ANGLE_RATE;

    //•½sˆÚ“®( +_r2, +0, +0) > angPos2‚ÌYŽ²‰ñ“] > •½sˆÚ“®( +0, +0, -_r1) > angPos1‚ÌXŽ²‰ñ“]
    //    | COS[angPos2]    , -SIN[angPos2]*-SIN[angPos1]             , -SIN[angPos2]*COS[angPos1]             , 0 |
    //    | 0               , COS[angPos1]                            , SIN[angPos1]                           , 0 |
    //    | SIN[angPos2]    , COS[angPos2]*-SIN[angPos1]              , COS[angPos2]*COS[angPos1]              , 0 |
    //    | _r2*COS[angPos2], (_r2*-SIN[angPos2] + -_r1)*-SIN[angPos1], (_r2*-SIN[angPos2] + -_r1)*COS[angPos1], 1 |
//  _TRACE_("GgafDx9Util::COS[angPos2]="<<GgafDx9Util::COS[angPos2]);
//  _TRACE_("_r2="<<_r2);
//  _TRACE_("_r2*GgafDx9Util::COS[angPos2]="<<_r2*GgafDx9Util::COS[angPos2]);
    double X = _r2*GgafDx9Util::COS[angPos2];
    double Y = (_r2*-GgafDx9Util::SIN[angPos2] - _r1) * -GgafDx9Util::SIN[angPos1];
    double Z = (_r2*-GgafDx9Util::SIN[angPos2] - _r1) *  GgafDx9Util::COS[angPos1];

    //Œü‚«‚ð‹‚ß‚é
    //•½sˆÚ“®( +0, +0, -_r1) > angPos1‚ÌXŽ²‰ñ“]
    //    | 1, 0                 , 0                , 0 |
    //    | 0, COS[angPos1]      , SIN[angPos1]     , 0 |
    //    | 0, -SIN[angPos1]     , COS[angPos1]     , 0 |
    //    | 0, -_r1*-SIN[angPos1], -_r1*COS[angPos1], 1 |

    double CX = 0;
    double CY = -_r1*-GgafDx9Util::SIN[angPos1];
    double CZ = -_r1*GgafDx9Util::COS[angPos1];
    angle angRz, angRy;
    GgafDx9Util::getRzRyAng((int)(X - CX), (int)(Y - CY), (int)(Z - CZ), angRz, angRy);
//  _TRACE_("angPos1="<<angPos1<<" angPos2="<<angPos2);
//  _TRACE_("X="<<(int)(X)<<" Y="<<(int)(Y)<<" Z="<<(int)(Z));
//  _TRACE_("CX="<<(int)(CY)<<" CY="<<(int)(CY)<<" CZ="<<(int)(CZ));
//  _TRACE_("(int)(X - CX)="<<(int)(X - CX)<<" (int)(Y - CY)="<<(int)(Y - CY)<<" (int)(Z - CZ)="<<(int)(Z - CZ));
//  _TRACE_("angRz="<<angRz<<" angRy="<<angRz);
    this->addSubBone(prm_pGeoActor, X, Y, Z, ANGLE0, angRz, angRy);
}

void Torus::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.4, 3.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.5);
    _pGgafDx9Model->_pTextureBlinker->beat(60*20, 60*9, 60*3, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.7;
}

void Torus::initialize() {
    setHitAble(true);

    int nSphere = 16;    //“–‚½‚è”»’è‹…‚Ì”;
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
    //À•W‚É”½‰f
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

#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Torus::Torus(const char* prm_name, const char* prm_model, coord prm_r1, coord prm_r2) :
        CubeMapMeshActor(prm_name, prm_model, STATUS(Torus)) {
    _class_name = "Torus";
    pEnemyTorusEye_ = NEW EnemyTorusEye("EnemyTorusEye", this);
    addSubGroup(pEnemyTorusEye_);

    setCubeMap("BkSky_cubemap.dds", 0.4);
    r1_ = prm_r1;
    r2_ = prm_r2;
}

void Torus::addSubFkOnSurface(GgafDxGeometricActor* prm_pGeoActor, angle prm_angPos1, angle prm_angPos2) {
    //トーラスはZY平面に円
    //位置を求める
    //平行移動( +r2_, +0, +0) > angPos2のY軸回転 > 平行移動( +0, +0, -r1_) > angPos1のX軸回転 変換行列の dx, dy, dz が欲しい
    //
    //    | COS[angPos2]    , -SIN[angPos2]*-SIN[angPos1]             , -SIN[angPos2]*COS[angPos1]             , 0 |
    //    | 0               ,  COS[angPos1]                           ,  SIN[angPos1]                          , 0 |
    //    | SIN[angPos2]    ,  COS[angPos2]*-SIN[angPos1]             ,  COS[angPos2]*COS[angPos]              , 0 |
    //    | r2_*COS[angPos2], (r2_*-SIN[angPos2] + -r1_)*-SIN[angPos1], (r2_*-SIN[angPos2] + -r1_)*COS[angPos1], 1 |
    //より
    double X = r2_*ANG_COS(prm_angPos2);
    double Y = (r2_*-ANG_SIN(prm_angPos2) - r1_) * -ANG_SIN(prm_angPos1);
    double Z = (r2_*-ANG_SIN(prm_angPos2) - r1_) *  ANG_COS(prm_angPos1);

    //向きを求める
    //平行移動( +0, +0, -r1_) > angPos1のX軸回転 変換行列の dx, dy, dz を使用
    //    | 1, 0                 , 0                , 0 |
    //    | 0, COS[angPos1]      , SIN[angPos1]     , 0 |
    //    | 0, -SIN[angPos1]     , COS[angPos1]     , 0 |
    //    | 0, -r1_*-SIN[angPos1], -r1_*COS[angPos1], 1 |
    //より
    double CX = 0;
    double CY = -r1_*-ANG_SIN(prm_angPos1);
    double CZ = -r1_*ANG_COS(prm_angPos1);
    angle angRz, angRy;
    UTIL::getRzRyAng((int)(X - CX), (int)(Y - CY), (int)(Z - CZ), angRz, angRy);
    //ボーンとして追加
    this->addSubFk(prm_pGeoActor, X, Y, Z, D0ANG, angRz, angRy);
}

void Torus::makeCollisionArea(int prm_nSphere){
    angle* paAngRadial = NEW angle[prm_nSphere];
    UTIL::getRadialAngle2D(0, prm_nSphere, paAngRadial);
    _pColliChecker->makeCollision(prm_nSphere);
    for (int i = 0; i < prm_nSphere; i++) {
        _pColliChecker->setColliSphere(
                i,
                0 , ANG_SIN(paAngRadial[i]) * r1_, ANG_COS(paAngRadial[i]) * r1_,
                r2_,
                false, true, true
                );
    }
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_BIGOBJ-2);
    DELETE_IMPOSSIBLE_NULL(paAngRadial);
}

void Torus::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.7, 0.2, 3.0);
    _pModel->_pTextureBlinker->setBlink(0.5);
    _pModel->_pTextureBlinker->beat(60*20, 60*9, 60*3, -1);
}

void Torus::onActive() {
    _pStatus->reset();
}

void Torus::processJudgement() {
    if (wasDeclaredEnd() == false && isOutOfUniverse()) {
        pEnemyTorusEye_ = NULL;
        sayonara();
    }

    if (pEnemyTorusEye_) {
    } else {
        //爆発
        setHitAble(false);
        for (int i = 0; i < 40; i++) {
            GgafDxDrawableActor* pE = employDelayFromCommon(EffectExplosion002, (i+1)*2);
            if (pE) {
                pE->locate(this->_X + RND(-300000, +300000),
                           this->_Y + RND(-300000, +300000),
                           this->_Z + RND(-300000, +300000));
            }
        }
        sayonara();
    }
}

void Torus::onHit(GgafActor* prm_pOtherActor) {

}

int Torus::isOutOfView() {
    //視野外判定無し
    return 0;
}
Torus::~Torus() {
}

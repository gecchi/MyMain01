#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Torus::Torus(const char* prm_name, const char* prm_model, coord prm_r1, coord prm_r2) :
        CubeMapMeshActor(prm_name, prm_model, STATUS(Torus)) {
    _class_name = "Torus";
    setCubeMapTexture("BkSky_cubemap.dds");
    r1_ = prm_r1;
    r2_ = prm_r2;
}

void Torus::addSubBoneOnSurface(GgafDxGeometricActor* prm_pGeoActor, angle prm_angPos1, angle prm_angPos2) {
    //トーラスはZY平面に円
    s_ang angPos1 = prm_angPos1 /SANG_RATE;
    s_ang angPos2 = prm_angPos2 /SANG_RATE;
    //位置を求める
    //平行移動( +r2_, +0, +0) > angPos2のY軸回転 > 平行移動( +0, +0, -r1_) > angPos1のX軸回転 変換行列の dx, dy, dz が欲しい
    //
    //    | COS[angPos2]    , -SIN[angPos2]*-SIN[angPos1]             , -SIN[angPos2]*COS[angPos1]             , 0 |
    //    | 0               ,  COS[angPos1]                           ,  SIN[angPos1]                          , 0 |
    //    | SIN[angPos2]    ,  COS[angPos2]*-SIN[angPos1]             ,  COS[angPos2]*COS[angPos]              , 0 |
    //    | r2_*COS[angPos2], (r2_*-SIN[angPos2] + -r1_)*-SIN[angPos1], (r2_*-SIN[angPos2] + -r1_)*COS[angPos1], 1 |
    //より
    double X = r2_*GgafDxUtil::COS[angPos2];
    double Y = (r2_*-GgafDxUtil::SIN[angPos2] - r1_) * -GgafDxUtil::SIN[angPos1];
    double Z = (r2_*-GgafDxUtil::SIN[angPos2] - r1_) *  GgafDxUtil::COS[angPos1];

    //向きを求める
    //平行移動( +0, +0, -r1_) > angPos1のX軸回転 変換行列の dx, dy, dz を使用
    //    | 1, 0                 , 0                , 0 |
    //    | 0, COS[angPos1]      , SIN[angPos1]     , 0 |
    //    | 0, -SIN[angPos1]     , COS[angPos1]     , 0 |
    //    | 0, -r1_*-SIN[angPos1], -r1_*COS[angPos1], 1 |
    //より
    double CX = 0;
    double CY = -r1_*-GgafDxUtil::SIN[angPos1];
    double CZ = -r1_*GgafDxUtil::COS[angPos1];
    angle angRz, angRy;
    GgafDxUtil::getRzRyAng((int)(X - CX), (int)(Y - CY), (int)(Z - CZ), angRz, angRy);
    //ボーンとして追加
    this->addSubBone(prm_pGeoActor, X, Y, Z, D0ANG, angRz, angRy);
}

void Torus::makeCollisionArea(int prm_nSphere){
    angle* paAngRadial = NEW angle[prm_nSphere];
    GgafDxUtil::getRadialAngle2D(0, prm_nSphere, paAngRadial);
    _pCollisionChecker->makeCollision(prm_nSphere);
    for (int i = 0; i < prm_nSphere; i++) {
        _pCollisionChecker->setColliSphere(
                i,
                0 , GgafDxUtil::SIN[paAngRadial[i]/SANG_RATE] * r1_, GgafDxUtil::COS[paAngRadial[i]/SANG_RATE] * r1_,
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
        sayonara(2000);
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

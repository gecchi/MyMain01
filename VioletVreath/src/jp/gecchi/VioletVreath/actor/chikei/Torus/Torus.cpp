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
    _r1 = prm_r1;
    _r2 = prm_r2;
}

void Torus::addSubBoneOnSurface(GgafDxGeometricActor* prm_pGeoActor, angle prm_angPos1, angle prm_angPos2) {
    //�g�[���X��ZY���ʂɉ~
    s_ang angPos1 = prm_angPos1 /SANG_RATE;
    s_ang angPos2 = prm_angPos2 /SANG_RATE;
    //�ʒu�����߂�
    //���s�ړ�( +_r2, +0, +0) > angPos2��Y����] > ���s�ړ�( +0, +0, -_r1) > angPos1��X����] �ϊ��s��� dx, dy, dz ���~����
    //
    //    | COS[angPos2]    , -SIN[angPos2]*-SIN[angPos1]             , -SIN[angPos2]*COS[angPos1]             , 0 |
    //    | 0               ,  COS[angPos1]                           ,  SIN[angPos1]                          , 0 |
    //    | SIN[angPos2]    ,  COS[angPos2]*-SIN[angPos1]             ,  COS[angPos2]*COS[angPos]              , 0 |
    //    | _r2*COS[angPos2], (_r2*-SIN[angPos2] + -_r1)*-SIN[angPos1], (_r2*-SIN[angPos2] + -_r1)*COS[angPos1], 1 |
    //���
    double X = _r2*GgafDxUtil::COS[angPos2];
    double Y = (_r2*-GgafDxUtil::SIN[angPos2] - _r1) * -GgafDxUtil::SIN[angPos1];
    double Z = (_r2*-GgafDxUtil::SIN[angPos2] - _r1) *  GgafDxUtil::COS[angPos1];

    //���������߂�
    //���s�ړ�( +0, +0, -_r1) > angPos1��X����] �ϊ��s��� dx, dy, dz ���g�p
    //    | 1, 0                 , 0                , 0 |
    //    | 0, COS[angPos1]      , SIN[angPos1]     , 0 |
    //    | 0, -SIN[angPos1]     , COS[angPos1]     , 0 |
    //    | 0, -_r1*-SIN[angPos1], -_r1*COS[angPos1], 1 |
    //���
    double CX = 0;
    double CY = -_r1*-GgafDxUtil::SIN[angPos1];
    double CZ = -_r1*GgafDxUtil::COS[angPos1];
    angle angRz, angRy;
    GgafDxUtil::getRzRyAng((int)(X - CX), (int)(Y - CY), (int)(Z - CZ), angRz, angRy);
    //�{�[���Ƃ��Ēǉ�
    this->addSubBone(prm_pGeoActor, X, Y, Z, D0ANG, angRz, angRy);
}

void Torus::makeCollisionArea(int prm_nSphere){
    angle* paAngRadial = NEW angle[prm_nSphere];
    GgafDxUtil::getRadialAngle2D(0, prm_nSphere, paAngRadial);
    _pCollisionChecker->makeCollision(prm_nSphere);
    for (int i = 0; i < prm_nSphere; i++) {
        _pCollisionChecker->setColliSphere(
                i,
                0 , GgafDxUtil::SIN[paAngRadial[i]/SANG_RATE] * _r1, GgafDxUtil::COS[paAngRadial[i]/SANG_RATE] * _r1,
                _r2,
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
    //����O���薳��
    return 0;
}
Torus::~Torus() {
}

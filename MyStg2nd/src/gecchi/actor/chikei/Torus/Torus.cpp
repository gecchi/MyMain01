#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Torus::Torus(const char* prm_name) : GroundMeshActor(prm_name, "Torus") {
    _class_name = "Torus";
}

void Torus::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.4, 2.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.5);
    _pGgafDx9Model->_pTextureBlinker->beat(60*10, 60*5, 60*1, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.7;
}

void Torus::initialize() {
    setHitAble(true);
    int r1 = 2000*1000; //�g�[���X���a1
    int r2 = 750*1000;  //�g�[���X���a2
    int nSphere = 12;    //�����蔻�苅�̐�;
    angle* paAngRadial = NEW angle[nSphere];
    GgafDx9Util::getRadialAngle2D(0, nSphere, paAngRadial);
    _pCollisionChecker->makeCollision(nSphere);
    for (int i = 0; i < nSphere; i++) {
        _pCollisionChecker->setColliSphere(
                i,
                0 , GgafDx9Util::SIN[paAngRadial[i]/ANGLE_RATE] * r1, GgafDx9Util::COS[paAngRadial[i]/ANGLE_RATE] * r1,
                r2,
                false, true, true
                );
    }
    DELETE_IMPOSSIBLE_NULL(paAngRadial);
    setAlpha(1.00);
    _X = 000000;
    _pMover->setRzMvAngVelo(100);
    _pMover->setRyMvAngVelo(200);
    _pMover->relateRzRyFaceAngToMvAng(true);
}

void Torus::processBehavior() {
    //���W�ɔ��f
    _pMover->behave();
}

void Torus::processJudgement() {
}

void Torus::onHit(GgafActor* prm_pOtherActor) {
    _TRACE_("Torus�q�b�g���܂����B("<<_X<<","<<_Y<<","<<_Z<<")");
}

Torus::~Torus() {
}

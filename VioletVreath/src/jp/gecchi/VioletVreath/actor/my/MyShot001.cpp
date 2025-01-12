#include "MyShot001.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafLib;
using namespace VioletVreath;

MyShot001::MyShot001(const char* prm_name) :
        VvMyActor<SingleLaser>(prm_name, "MyShot001", StatusReset(MyShot001)) { //SingleLaser�͍ő�27�Z�b�g�ł���
    _class_name = "MyShot001";
}

void MyShot001::initialize() {
    setHitAble(false);
    _sx = R_SC(45);
    _sy = _sz = R_SC(35);
    setBoundingSphereRadiusRate(45.0f);
    setCullingDraw(false);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAABox(0, -PX_C(50), -PX_C(50), -PX_C(50),
                                PX_C(50),  PX_C(50),  PX_C(50));

    // �g��
    WorldCollisionChecker* pExChecker = (WorldCollisionChecker*)pChecker->addExChecker(KIND_CHECK_CHIKEI_HIT);
    pExChecker->addCollisionArea(1);
    //���@ pChecker->setColliAACube(0, PX_C(40));
    pExChecker->setColliAACube(0, PX_C(40));

    getLocusVehicle()->setRollFaceAngVelo(D_ANG(12));
    getLocusVehicle()->linkFaceAngByMvAng(true);
}

void MyShot001::onActive() {
    getStatus()->reset();
    setHitAble(true);
}

void MyShot001::processBehavior() {
    getLocusVehicle()->behave();
}

void MyShot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void MyShot001::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)(prm_pOppHitChecker->_pActor);
    if (prm_pOppHitChecker->_kind & KIND_CHIKEI) {
        //�q�b�g���肪�n�`�Ȃ�Ύ��@�̑傫���Ŕ��肵�A�q�b�g���Ȃ���Ώ������Ȃ� TODO: ����ł͂���
        MyShip* pMyShip = pMYSHIP;
        WorldCollisionChecker* pMyShipChecker = pMyShip->getWorldCollisionChecker();
        coord x = pMyShip->_x;
        coord y = pMyShip->_y;
        coord z = pMyShip->_z;
        pMyShip->setPositionAt(this); //���W��������������
        WorldCollisionChecker* pOtherChecker = (WorldCollisionChecker*)pOther->getChecker();
        bool r = pOtherChecker->isHit(pMyShipChecker);
        pMyShip->_x = x;
        pMyShip->_y = y;
        pMyShip->_z = z;
        if (!r) {
            //���@�̑傫���Ŕ��肵�A�q�b�g���Ȃ��̂Ŗ����
            return;
        }
    }
    setHitAble(false);
    UTIL::activateCommonEffectOf(this, STAT_ExplosionEffectKind);
    sayonara(); //�K���ђʂ��Ȃ�
}


//void MyShot001::drawHitArea() {
//    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
//}
MyShot001::~MyShot001() {
}

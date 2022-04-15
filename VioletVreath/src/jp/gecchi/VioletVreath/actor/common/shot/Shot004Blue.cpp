#include "Shot004Blue.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

Shot004Blue::Shot004Blue(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Shot004Blue", StatusReset(Shot004)) { //SingleLaser�͍ő�27�Z�b�g�ł���
        //SingleLaser(prm_name, "27,laser_single") { //SingleLaser�͍ő�27�Z�b�g�ł���
    _class_name = "Shot004Blue";
    view_in_ = false;
}

void Shot004Blue::initialize() {
    setHitAble(false);
    setZEnableDraw(true);   //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ�
    effectBlendOne();       //���Z����
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(16));
}
void Shot004Blue::onReset() {
    setScaleR(3.0);
    setCullingDraw(false);
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    pVecVehicle->setRollFaceAngVelo(D_ANG(3));
    pVecVehicle->setMvVelo(40000);             //�ړ����x
    pVecVehicle->setMvAcce(1000);             //�ړ����x
    pVecVehicle->linkFaceAngByMvAng(true);
}

void Shot004Blue::onActive() {
    getStatus()->reset();
    setHitAble(true, false);
    view_in_ = false;
}

void Shot004Blue::processBehavior() {
    //���W�ɔ��f
    getVecVehicle()->behave();
}

void Shot004Blue::processJudgement() {
    if (isOutOfView()) {
        if (view_in_) {
            sayonara();
        }
        if (getActiveFrame() > 60) {
            sayonara();
        }
    } else {
        view_in_ = true;
    }
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void Shot004Blue::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

Shot004Blue::~Shot004Blue() {
}

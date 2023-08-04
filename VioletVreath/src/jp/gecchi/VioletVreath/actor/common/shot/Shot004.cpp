#include "Shot004.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

Shot004::Shot004(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Shot004", StatusReset(Shot004)) {
        //SingleLaser(prm_name, "laser_single") { //SingleLaser�͍ő�26�Z�b�g�ł���
    _class_name = "Shot004";
    view_in_ = false;
}

void Shot004::initialize() {
    setHitAble(false);
    setZEnableDraw(true);   //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ�
    effectBlendOne();       //���Z����
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(16));
}
void Shot004::onReset() {
    setScaleR(3.0);
    setCullingDraw(false);
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->setRollFaceAngVelo(D_ANG(3));
    pLocoVehicle->setMvVelo(30000);
    pLocoVehicle->setMvAcce(1000);
    pLocoVehicle->linkFaceAngByMvAng(true);
}

void Shot004::onActive() {
    getStatus()->reset();
    setHitAble(true, false);
    view_in_ = false;
}

void Shot004::processBehavior() {
    //�e�Ȃ̂ŕs�v

    //���W�ɔ��f
    getLocoVehicle()->behave();
}

void Shot004::processJudgement() {
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

void Shot004::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

Shot004::~Shot004() {
}

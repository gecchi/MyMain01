#include "Shot003.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"

using namespace GgafLib;
using namespace VioletVreath;

Shot003::Shot003(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "laser_single", StatusReset(Shot003)) {
    _class_name = "Shot003";
}

void Shot003::initialize() {
    setHitAble(false);
    _sx = _sy = _sz = R_SC(50);
    setCullingDraw(false);
    setZEnableDraw(true);   //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ�
    effectBlendOne();       //���Z����
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(16));
}

void Shot003::onActive() {
    getStatus()->reset();
    setHitAble(true, false);
    getVecVehicle()->setMvVelo(20000);

}

void Shot003::processBehavior() {
    //���Z�����N�|�C���g������
    //���W�ɔ��f
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->behave();
}

void Shot003::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void Shot003::onHit(const GgafCore::Actor* prm_pOtherActor) {
//    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
//    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
//    if (MyStgUtil::calcEnemyStamina(this, pOther) <= 0) {
//        //�j�󂳂ꂽ�ꍇ
//        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
//        EffectExplosion003* pExplo003 = (EffectExplosion003*)pCOMMON_SCENE->pDepo_EffectExplosion003_->dispatch();
//        playSe3D1();
//        if (pExplo003) {
//            pExplo003->setPositionAt(this);
//        }
//        sayonara();
//    }
}

Shot003::~Shot003() {
}

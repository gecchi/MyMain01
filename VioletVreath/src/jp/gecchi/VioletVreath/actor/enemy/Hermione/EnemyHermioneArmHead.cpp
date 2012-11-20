#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyHermioneArmHead::EnemyHermioneArmHead(const char* prm_name) :
        EnemyHermioneArm(prm_name, "HermioneArmHead", STATUS(EnemyHermioneArmHead)) {
    _class_name = "EnemyHermioneArmHead";
    pDpcon_ = connectToDepositoryManager("Conn_Shot004", nullptr); //�e
    pDepo_Fired_ = pDpcon_->fetch();
}

void EnemyHermioneArmHead::onCreateModel() {
}

void EnemyHermioneArmHead::initialize() {
    EnemyHermioneArm::initialize();
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(1000, 1200);
    _pScaler->beat(30, 5, 5, -1);
}


void EnemyHermioneArmHead::processBehavior() {
    EnemyHermioneArm::processBehavior();

    //�e����
    if (getActivePartFrame() % 10 == 0) { //�o���Ԋu
        GgafDxDrawableActor* pActor = (GgafDxDrawableActor*)pDepo_Fired_->dispatch();
        if (pActor) {
            //�����݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾���遄
            //�����x�N�g���̓��[���h�ϊ��s��̐ρi_matWorldRotMv)�ŕϊ�����A���݂̍ŏI�I�Ȍ����Ɍ����B
            //���̕����x�N�g����(Xorg_,Yorg_,Zorg_)�A
            //���[���h�ϊ��s��̉�]�����̐ρi_matWorldRotMv)�̐����� mat_xx�A
            //�ŏI�I�ȕ����x�N�g����(vX, vY, vZ) �Ƃ����
            //
            //                      | mat_11 mat_12 mat_13 |
            //| Xorg_ Yorg_ Zorg_ | | mat_21 mat_22 mat_23 | = | vX vY vZ |
            //                      | mat_31 mat_32 mat_33 |
            //
            //vX = Xorg_*mat_11 + Yorg_*mat_21 + Zorg_*mat_31
            //vY = Xorg_*mat_12 + Yorg_*mat_22 + Zorg_*mat_32
            //vZ = Xorg_*mat_13 + Yorg_*mat_23 + Zorg_*mat_33
            //
            //���Ă����ŁA���X���O���̒P�ʕ����x�N�g��(1,0,0)�̏ꍇ�͂ǂ��Ȃ邩�l�����
            //
            //vX = Xorg_*mat_11
            //vY = Xorg_*mat_12
            //vZ = Xorg_*mat_13
            //
            //�ƂȂ�B�{�A�v���ł́A���f���͑S��(1,0,0)��O���Ƃ��Ă��邽��
            //�ŏI�I�ȕ����x�N�g���́iXorg_*mat_11, Xorg_*mat_12, Xorg_*mat_13) �ł���B
            angle Rz, Ry;
            UTIL::getRzRyAng(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13,
                             Rz, Ry); //���݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾�I
            pActor->_pKurokoA->setRzRyMvAng(Rz, Ry); //RzRy��Mover�ɐݒ�
            pActor->locateWith(this);
            pActor->reset();
        }
    }

}


void EnemyHermioneArmHead::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
//        setHitAble(false);
//        //��������
//        UTIL::activateExplosionEffectOf(this);
//        _pSeTx->play3D(SE_EXPLOSION);
//
//        //���@���Ɍ�����ď��ł̏ꍇ�A
//        if (pOther->getKind() & KIND_MY) {
//            //�A�C�e���o��
//            UTIL::activateItemOf(this);
//        }
//        sayonara();
//    } else {
//        //��j��
//        effectFlush(2); //�t���b�V��
//        _pSeTx->play3D(SE_DAMAGED);
//    }
}


EnemyHermioneArmHead::~EnemyHermioneArmHead() {
    pDpcon_->close();
}

#include "MyTorpedo.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "MyTorpedoBlast.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoController.h"
#include "MyTorpedoTail.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION,
};

MyTorpedo::MyTorpedo(const char* prm_name, MyTorpedoController* prm_pTorpedoController)
               : VvMyActor<DefaultMeshSetActor>(prm_name, "EffectLaserRefraction001", StatusReset(MyTorpedo)) {
    _class_name = "MyTorpedo";
    pTorpedoCtrler_ = prm_pTorpedoController;
    length_TailEffect_ = 5;
    begin_x_ = _x;
    begin_y_ = _y;
    begin_z_ = _z;

    pTailEffectDepository_ = NEW LaserChipDepository("Depo_TorpedoTailEffect");
    pTailEffectDepository_->config(length_TailEffect_, 0, nullptr);
    for (int i = 0; i < length_TailEffect_; i++) {
        std::string name = std::string(getName())+"'s Tail("+XTOS(i)+")";
        pTailEffectDepository_->put(NEW MyTorpedoTail(name.c_str(), this));
    }
    move_section_ = 0;
    appendGroupChild(pTailEffectDepository_);
    effectBlendOne(); //���Z��������Technique�w��
    setZEnableDraw(true);        //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false);  //���g��Z�o�b�t�@���������݂��Ȃ�
    pTarget_ = nullptr;
    trz_ = try_ = 0;
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_EXPLOSION, "SE_EXPLOSION_TORPEDO");
}

void MyTorpedo::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 70000);
}

void MyTorpedo::onReset() {
    pTarget_ = nullptr;
}

void MyTorpedo::onActive() {
    getStatus()->reset();
    setAlpha(0.3);
    _sx = _sy = _sz = 100;
    setScale(100);
    getScaler()->transitionLinearStep(7000, 500);
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->setRollPitchYawFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
    if (pTarget_) {
        pLocoVehicle->forceMvVeloRange(4000, 100000);
        pLocoVehicle->setMvVelo(20000);
        pLocoVehicle->setMvAcce(-600); //�ŏ�����
    } else {
        pLocoVehicle->forceMvVeloRange(4000, 70000);
        pLocoVehicle->setMvVelo(10000);
        pLocoVehicle->setMvAcce(-500); //�ŏ�����
    }

    pLocoVehicle->forceRzRyMvAngVeloRange(-40000, 40000);
    pLocoVehicle->setRzRyMvAngVelo(0,0);
    pLocoVehicle->setRzRyMvAngAcce(0,0);
    pLocoVehicle->stopTurningMvAng();
    begin_x_ = _x;
    begin_y_ = _y;
    begin_z_ = _z;
    setHitAble(true);
    getPhase()->reset(MyTorpedo_IN_FIRE);
    move_section_ = 0;
    //��^�[�Q�b�g���̕����A�I�v�V�����̌����Ă�����ɔ�΂�
    trz_ = pTorpedoCtrler_->pOrg_->_rz;
    try_ = pTorpedoCtrler_->pOrg_->_ry;
}

void MyTorpedo::processBehavior() {
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafCore::Phase* pPhase = getPhase();
    if (pPhase->getCurrent() == MyTorpedo_RELEASE) {
        if (pTailEffectDepository_->_num_chip_active == 0) {
            //�O�ՃG�t�F�N�g���S�Ĕ񊈓��ɂȂ����ꍇ
            inactivate(); //���g���Ō��inactivate()
        } else {
            addAlpha(-0.05);
        }
    }

    if (pPhase->getCurrent() == MyTorpedo_IN_FIRE) {
        //�����ۃG�t�F�N�g�ǉ�����
        if (pTailEffectDepository_->_num_chip_active < length_TailEffect_) {
            MyTorpedoTail* pTailEffect = (MyTorpedoTail*)pTailEffectDepository_->dispatch();
            if (pTailEffect) {
                pTailEffect->setPosition(begin_x_,begin_y_,begin_z_);
            }
        }
        //�����̃��[�u
        if (move_section_ == 0) { //���ˊJ�n�`���������܂�
            if (pLocoVehicle->_velo_mv == pLocoVehicle->_bottom_velo_mv) { //�����I����

                if (pTarget_) {
                    //�^�[�Q�b�e�B���O���́ATURN_CLOSE_TO �œ����������ă^�[�Q�b�g
                    pLocoVehicle->setMvAcce(600);
                    pLocoVehicle->turnMvAngTwd(pTarget_,
                                          1000, 100,
                                          TURN_CLOSE_TO, false);
                } else {
                    //�m�[�^�[�Q�b�e�B���O���́ATURN_ANTICLOSE_TO �œ�����^������
                    pLocoVehicle->setMvAcce(500);
                    pLocoVehicle->turnRzRyMvAngTo(
                                trz_, try_,
                                2000, 200,
                                TURN_ANTICLOSE_TO, false);
                }
                move_section_++;
            }
        }

        //���[�u�P ���������`�����]������
        if (move_section_ == 1) {
            if (pLocoVehicle->isTurningMvAng()) {
                //TURN_ANTICLOSE_TO�^�[�Q�b�g������҂�
            } else {
                //TURN_ANTICLOSE_TO�^�[�Q�b�g����
                move_section_++;
            }
        }
        //���[�u�Q �����]�������`120�t���[���Ԃ͂�⋭���p���x�Ń^�[�Q�b�g�␳
        if (move_section_ == 2) {
            if (getActiveFrame() < 120) {
                if (getActiveFrame() % 16U == 0) {
                    if (pTarget_) {
                        if (pTarget_->isActiveInTheTree())  {
                            //�^�[�Q�b�g�L��
                            pLocoVehicle->turnMvAngTwd(pTarget_,
                                                  1000, 200,
                                                  TURN_CLOSE_TO, false);

                        } else {
                            //�^�[�Q�b�g�������A���̂܂܂܂�����
                            pLocoVehicle->setRzRyMvAngVelo(0, 0);
                            pLocoVehicle->setRzRyMvAngAcce(0, 0);
                        }
                    } else {
                        //�^�[�Q�b�g�����i�I�v�V�����̌����Ă�������ցj
                        pLocoVehicle->turnRzRyMvAngTo(
                                    trz_, try_,
                                    1000, 200,
                                    TURN_CLOSE_TO, false);
                    }
                } else {
                   //
                }
            } else {
                move_section_++;
            }
        }
        //���[�u�R �`300�t���[���Ԃ͊ɂ₩�Ȋp���x�Ń^�[�Q�b�g�␳
        if (move_section_ == 3) {
            if (getActiveFrame() < 300) {
                if (getActiveFrame() % 16U == 0) {
                    if (pTarget_) {
                        if (pTarget_->isActiveInTheTree())  {
                            //�^�[�Q�b�g�L��
                            pLocoVehicle->turnMvAngTwd(pTarget_,
                                                  500, 0,
                                                  TURN_CLOSE_TO, false);
                        } else {
                            //�^�[�Q�b�g�������A���̂܂܂܂�����
                            pLocoVehicle->setRzRyMvAngVelo(0,0);
                            pLocoVehicle->setRzRyMvAngAcce(0,0);
                        }
                    } else {
                        //�^�[�Q�b�g�����i�I�v�V�����̌����Ă�������ցj
                        pLocoVehicle->turnRzRyMvAngTo(
                                    trz_, try_,
                                    300, 0,
                                    TURN_CLOSE_TO, false);

                    }
                } else {
                   //
                }
            } else {
                move_section_++;
            }
        }
        //���[�u�S
        if (move_section_ == 4) {
            pLocoVehicle->setRzRyMvAngVelo(0,0);
            pLocoVehicle->setRzRyMvAngAcce(0,0);
        }
        pLocoVehicle->behave();
        getScaler()->behave();
    }
}

void MyTorpedo::processJudgement() {
    GgafCore::Phase* pPhase = getPhase();
    if (isOutOfSpacetime() && pPhase->getCurrent() == MyTorpedo_IN_FIRE) {
        setHitAble(false);
        pPhase->change(MyTorpedo_RELEASE);
        GgafCore::MainActor* pTailEffect = (GgafCore::MainActor*)pTailEffectDepository_->getChildFirst();
        for (int i = 0; i < length_TailEffect_; i++) {
            pTailEffect->inactivateDelay(i+1); //�O�ՃG�t�F�N�g�����X�ɏ�����悤�ɗ\��
            pTailEffect = pTailEffect->getNext();
        }
        getLocoVehicle()->setMvVelo(0);
        //���g��inactive()��processBehavior()�ōs���
        //�����̈ړ��G�t�F�N�g���S��inactive()�ɂȂ����ۂɎ��g��inactive()����
    }

}

void MyTorpedo::onInactive() {
}

void MyTorpedo::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
    //�q�b�g���ʊт͂��܂���
    int sta = UTIL::calcMyStamina(this, pOther);
    setHitAble(false);

    GgafCore::Phase* pPhase = getPhase();
    pPhase->change(MyTorpedo_RELEASE);
    GgafCore::MainActor* pTailEffect = (GgafCore::MainActor*)pTailEffectDepository_->getChildFirst();
    for (int i = 0; i < length_TailEffect_; i++) {
        pTailEffect->inactivateDelay(i+1); //�O�ՃG�t�F�N�g�����X�ɏ�����悤�ɗ\��
        pTailEffect = pTailEffect->getNext();
    }
    getLocoVehicle()->setMvVelo(0);
    //���g��inactive()��processBehavior()�ōs���
    //�����̈ړ��G�t�F�N�g���S��inactive()�ɂȂ����ۂɎ��g��inactive()����

    //��������
    MyTorpedoBlast* pBlast = (MyTorpedoBlast*)(pTorpedoCtrler_->pDepo_TorpedoBlast_->dispatchForce());
    getSeXmtr()->play3D(SE_EXPLOSION);
    pBlast->reset();
    pBlast->setPositionAt(this);
}

MyTorpedo::~MyTorpedo() {
}

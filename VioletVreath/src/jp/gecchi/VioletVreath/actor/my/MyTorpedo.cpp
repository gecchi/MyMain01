#include "MyTorpedo.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
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
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_TORPEDO");
}

void MyTorpedo::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
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
    GgafDx::Rikisha* const pRikisha = callRikisha();
    pRikisha->setRollPitchYawFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
    if (pTarget_) {
        pRikisha->forceMvVeloRange(4000, 100000);
        pRikisha->setMvVelo(20000);
        pRikisha->setMvAcce(-600); //�ŏ�����
    } else {
        pRikisha->forceMvVeloRange(4000, 70000);
        pRikisha->setMvVelo(10000);
        pRikisha->setMvAcce(-500); //�ŏ�����
    }

    pRikisha->forceRzRyMvAngVeloRange(-40000, 40000);
    pRikisha->setRzRyMvAngVelo(0,0);
    pRikisha->setRzRyMvAngAcce(0,0);
    pRikisha->stopTurningMvAng();
    begin_x_ = _x;
    begin_y_ = _y;
    begin_z_ = _z;
    setHitAble(true);
    getProgress()->reset(MyTorpedo_IN_FIRE);
    move_section_ = 0;
    //��^�[�Q�b�g���̕����A�I�v�V�����̌����Ă�����ɔ�΂�
    trz_ = pTorpedoCtrler_->pOrg_->_rz;
    try_ = pTorpedoCtrler_->pOrg_->_ry;
}

void MyTorpedo::processBehavior() {
    GgafDx::Rikisha* const pRikisha = callRikisha();
    GgafCore::Progress* const pProg = getProgress();
    if (pProg->get() == MyTorpedo_RELEASE) {
        if (pTailEffectDepository_->_num_chip_active == 0) {
            //�O�ՃG�t�F�N�g���S�Ĕ񊈓��ɂȂ����ꍇ
            inactivate(); //���g���Ō��inactivate()
        } else {
            addAlpha(-0.05);
        }
    }

    if (pProg->get() == MyTorpedo_IN_FIRE) {
        //�����ۃG�t�F�N�g�ǉ�����
        if (pTailEffectDepository_->_num_chip_active < length_TailEffect_) {
            MyTorpedoTail* pTailEffect = (MyTorpedoTail*)pTailEffectDepository_->dispatch();
            if (pTailEffect) {
                pTailEffect->setPosition(begin_x_,begin_y_,begin_z_);
            }
        }
        //�����̃��[�u
        if (move_section_ == 0) { //���ˊJ�n�`���������܂�
            if (pRikisha->_velo_mv == pRikisha->_bottom_velo_mv) { //�����I����

                if (pTarget_) {
                    //�^�[�Q�b�e�B���O���́ATURN_CLOSE_TO �œ����������ă^�[�Q�b�g
                    pRikisha->setMvAcce(600);
                    pRikisha->turnMvAngTwd(pTarget_,
                                          1000, 100,
                                          TURN_CLOSE_TO, false);
                } else {
                    //�m�[�^�[�Q�b�e�B���O���́ATURN_ANTICLOSE_TO �œ�����^������
                    pRikisha->setMvAcce(500);
                    pRikisha->turnRzRyMvAngTo(
                                trz_, try_,
                                2000, 200,
                                TURN_ANTICLOSE_TO, false);
                }
                move_section_++;
            }
        }

        //���[�u�P ���������`�����]������
        if (move_section_ == 1) {
            if (pRikisha->isTurningMvAng()) {
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
                            pRikisha->turnMvAngTwd(pTarget_,
                                                  1000, 200,
                                                  TURN_CLOSE_TO, false);

                        } else {
                            //�^�[�Q�b�g�������A���̂܂܂܂�����
                            pRikisha->setRzRyMvAngVelo(0, 0);
                            pRikisha->setRzRyMvAngAcce(0, 0);
                        }
                    } else {
                        //�^�[�Q�b�g�����i�I�v�V�����̌����Ă�������ցj
                        pRikisha->turnRzRyMvAngTo(
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
                            pRikisha->turnMvAngTwd(pTarget_,
                                                  500, 0,
                                                  TURN_CLOSE_TO, false);
                        } else {
                            //�^�[�Q�b�g�������A���̂܂܂܂�����
                            pRikisha->setRzRyMvAngVelo(0,0);
                            pRikisha->setRzRyMvAngAcce(0,0);
                        }
                    } else {
                        //�^�[�Q�b�g�����i�I�v�V�����̌����Ă�������ցj
                        pRikisha->turnRzRyMvAngTo(
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
            pRikisha->setRzRyMvAngVelo(0,0);
            pRikisha->setRzRyMvAngAcce(0,0);
        }
        pRikisha->behave();
        getScaler()->behave();
    }
}

void MyTorpedo::processJudgement() {
    GgafCore::Progress* const pProg = getProgress();
    if (isOutOfSpacetime() && pProg->get() == MyTorpedo_IN_FIRE) {
        setHitAble(false);
        pProg->change(MyTorpedo_RELEASE);
        GgafCore::MainActor* pTailEffect = (GgafCore::MainActor*)pTailEffectDepository_->getChildFirst();
        for (int i = 0; i < length_TailEffect_; i++) {
            pTailEffect->inactivateDelay(i+1); //�O�ՃG�t�F�N�g�����X�ɏ�����悤�ɗ\��
            pTailEffect = pTailEffect->getNext();
        }
        callRikisha()->setMvVelo(0);
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

    GgafCore::Progress* const pProg = getProgress();
    pProg->change(MyTorpedo_RELEASE);
    GgafCore::MainActor* pTailEffect = (GgafCore::MainActor*)pTailEffectDepository_->getChildFirst();
    for (int i = 0; i < length_TailEffect_; i++) {
        pTailEffect->inactivateDelay(i+1); //�O�ՃG�t�F�N�g�����X�ɏ�����悤�ɗ\��
        pTailEffect = pTailEffect->getNext();
    }
    callRikisha()->setMvVelo(0);
    //���g��inactive()��processBehavior()�ōs���
    //�����̈ړ��G�t�F�N�g���S��inactive()�ɂȂ����ۂɎ��g��inactive()����

    //��������
    MyTorpedoBlast* pBlast = (MyTorpedoBlast*)(pTorpedoCtrler_->pDepo_TorpedoBlast_->dispatchForce());
    getSeTransmitter()->play3D(SE_EXPLOSION);
    pBlast->reset();
    pBlast->setPositionAt(this);
}

MyTorpedo::~MyTorpedo() {
}

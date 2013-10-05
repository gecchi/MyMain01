#include "stdafx.h"
#include "MyTorpedo.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "MyTorpedoBlast.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoController.h"
#include "MyTorpedoTail.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyTorpedo::MyTorpedo(const char* prm_name, MyTorpedoController* prm_pOptionTorpedoController)
               : DefaultMeshSetActor(prm_name, "EffectLaserRefraction001", STATUS(MyTorpedo)) {
    _class_name = "MyTorpedo";
    pOptionTorpedoCtrler_ = prm_pOptionTorpedoController;
    length_TailEffect_ = 8;
    begin_X_ = _X;
    begin_Y_ = _Y;
    begin_Z_ = _Z;

    pTailEffectDepository_ = NEW LaserChipDepository("Depo_TorpedoTailEffect");
    pTailEffectDepository_->config(length_TailEffect_, 0, nullptr);
    for (int i = 0; i < length_TailEffect_; i++) {
        std::string name = std::string(getName())+"'s Tail("+XTOS(i)+")";
        pTailEffectDepository_->put(NEW MyTorpedoTail(name.c_str(), this));
    }
    move_section_ = 0;
    addSubGroup(pTailEffectDepository_);
    effectBlendOne(); //���Z��������Technique�w��
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
    pTarget_ = nullptr;
    useProgress(10);

    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_TORPEDO");
}

void MyTorpedo::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 70000);
}

void MyTorpedo::onReset() {
    pTarget_ = nullptr;
}

void MyTorpedo::onActive() {
    GgafDxKurokoA* const pKurokoA = _pKurokoA;
    _pStatus->reset();
    setAlpha(0.3);
    _SX = _SY = _SZ = 100;
    _pScaler->setScale(100);
    _pScaler->scaleLinerStep(7000, 500);
    pKurokoA->setFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
    if (pTarget_) {
        pKurokoA->forceMvVeloRange(4000, 100000);
        pKurokoA->setMvVelo(20000);
        pKurokoA->setMvAcce(-600); //�ŏ�����
    } else {
        pKurokoA->forceMvVeloRange(4000, 70000);
        pKurokoA->setMvVelo(10000);
        pKurokoA->setMvAcce(-500); //�ŏ�����
    }

    pKurokoA->forceRzRyMvAngVeloRange(-40000, 40000);
    pKurokoA->setRzRyMvAngVelo(0);
    pKurokoA->setRzRyMvAngAcce(0);
    pKurokoA->stopTurnMvAngSequence();
    begin_X_ = _X;
    begin_Y_ = _Y;
    begin_Z_ = _Z;
    setHitAble(true);
    _pProg->reset(MyTorpedo_IN_FIRE);
    move_section_ = 0;
}

void MyTorpedo::processBehavior() {
    GgafDxKurokoA* const pKurokoA = _pKurokoA;
    if (_pProg->get() == MyTorpedo_RELEASE) {
        if (pTailEffectDepository_->_num_chip_active == 0) {
            //�O�ՃG�t�F�N�g���S�Ĕ񊈓��ɂȂ����ꍇ
            inactivate(); //���g���Ō��inactivate()
        } else {
            addAlpha(-0.05);
        }
    }

    if (_pProg->get() == MyTorpedo_IN_FIRE) {
        //�����ۃG�t�F�N�g�ǉ�����
        if (pTailEffectDepository_->_num_chip_active < length_TailEffect_) {
            MyTorpedoTail* pTailEffect = (MyTorpedoTail*)pTailEffectDepository_->dispatch();
            if (pTailEffect) {
                pTailEffect->position(begin_X_,begin_Y_,begin_Z_);
            }
        }
        //�����̃��[�u
        if (move_section_ == 0) {
            if (pKurokoA->_veloMv == pKurokoA->_veloBottomMv) { //�����I��
                pKurokoA->setMvAcce(500);
                if (pTarget_) {
                    pKurokoA->turnMvAngTwd(pTarget_,
                                           2000, 200,
                                           TURN_ANTICLOSE_TO, false);
                } else {
                    pKurokoA->turnRzRyMvAngTo(
                                pOptionTorpedoCtrler_->pOrg_->_RZ, pOptionTorpedoCtrler_->pOrg_->_RY,
                                1000, 100,
                                TURN_CLOSE_TO, false);

//                    pKurokoA->turnMvAngTwd(
//                                GgafDxUniverse::_X_gone_right, P_MYSHIP->_Y, P_MYSHIP->_Z,
//                                2000, 200,
//                                TURN_ANTICLOSE_TO, false);
                }
                move_section_++;
            }
        }

        //���[�u�P
        if (move_section_ == 1) {
            if (pKurokoA->isTurningMvAng()) {
                //TURN_ANTICLOSE_TO�^�[�Q�b�g������҂�
            } else {
                //TURN_ANTICLOSE_TO�^�[�Q�b�g����
                move_section_++;
            }
        }
        //���[�u�Q
        if (move_section_ == 2) {
            if (getActiveFrame() < 120) {
                if (getActiveFrame() % 16U == 0) {
                    if (pTarget_) {
                        if (pTarget_->isActiveInTheTree())  {

                            pKurokoA->turnMvAngTwd(pTarget_,
                                                   1000, 200,
                                                   TURN_CLOSE_TO, false);

                        } else {
                            //�܂�����
                            pKurokoA->setRzRyMvAngVelo(0);
                            pKurokoA->setRzRyMvAngAcce(0);
                        }
                    } else {
                        pKurokoA->turnRzRyMvAngTo(
                                    pOptionTorpedoCtrler_->pOrg_->_RZ, pOptionTorpedoCtrler_->pOrg_->_RY,
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
        //���[�u�R
        if (move_section_ == 3) {
            if (getActiveFrame() < 300) {
                if (getActiveFrame() % 16U == 0) {
                    if (pTarget_) {
                        if (pTarget_->isActiveInTheTree())  {

                            pKurokoA->turnMvAngTwd(pTarget_,
                                                   500, 0,
                                                   TURN_CLOSE_TO, false);

//                            //�J�N�J�N���Ɣ��˂��ۂ�
//                            angle out_angRz_Target;
//                            angle out_angRy_Target;
//                            angle out_d_angRz;
//                            angle out_d_angRy;
//                            UTIL::convVectorToRzRy(pTarget_->_X - _X,
//                                                   pTarget_->_Y - _Y,
//                                                   pTarget_->_Z - _Z,
//                                                   out_angRz_Target,
//                                                   out_angRy_Target);
//                            out_d_angRz = pKurokoA->getRzMvAngDistance(out_angRz_Target, TURN_CLOSE_TO);
//                            out_d_angRy = pKurokoA->getRyMvAngDistance(out_angRy_Target, TURN_CLOSE_TO);
//                            pKurokoA->addRzMvAng(SGN(out_d_angRz)*30000);
//                            pKurokoA->addRyMvAng(SGN(out_d_angRy)*30000);

                        } else {
                            //�܂�����
                            pKurokoA->setRzRyMvAngVelo(0);
                            pKurokoA->setRzRyMvAngAcce(0);
                        }
                    } else {
                        pKurokoA->turnRzRyMvAngTo(
                                    pOptionTorpedoCtrler_->pOrg_->_RZ, pOptionTorpedoCtrler_->pOrg_->_RY,
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
            pKurokoA->setRzRyMvAngVelo(0);
            pKurokoA->setRzRyMvAngAcce(0);
        }

        pKurokoA->behave();
        _pScaler->behave();
    }
}

void MyTorpedo::processJudgement() {
    if (isOutOfUniverse() && _pProg->get() == MyTorpedo_IN_FIRE) {
        setHitAble(false);
        _pProg->change(MyTorpedo_RELEASE);
        GgafMainActor* pTailEffect = (GgafMainActor*)pTailEffectDepository_->getSubFirst();
        for (int i = 0; i < length_TailEffect_; i++) {
            pTailEffect->inactivateDelay(i+1); //�O�ՃG�t�F�N�g�����X�ɏ�����悤�ɗ\��
            pTailEffect = pTailEffect->getNext();
        }
        _pKurokoA->setMvVelo(0);
        //���g��inactive()��processBehavior()�ōs���
        //�����̈ړ��G�t�F�N�g���S��inactive()�ɂȂ����ۂɎ��g��inactive()����
    }

}

void MyTorpedo::onInactive() {
}

void MyTorpedo::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�q�b�g���ʊт͂��܂���
    int sta = UTIL::calcMyStamina(this, pOther);
    setHitAble(false);
    _pProg->change(MyTorpedo_RELEASE);
    GgafMainActor* pTailEffect = (GgafMainActor*)pTailEffectDepository_->getSubFirst();
    for (int i = 0; i < length_TailEffect_; i++) {
        pTailEffect->inactivateDelay(i+1); //�O�ՃG�t�F�N�g�����X�ɏ�����悤�ɗ\��
        pTailEffect = pTailEffect->getNext();
    }
    _pKurokoA->setMvVelo(0);
    //���g��inactive()��processBehavior()�ōs���
    //�����̈ړ��G�t�F�N�g���S��inactive()�ɂȂ����ۂɎ��g��inactive()����

    //��������
    MyTorpedoBlast* pBlast = (MyTorpedoBlast*)(pOptionTorpedoCtrler_->pDepo_TorpedoBlast_->dispatchForce());
    _pSeTx->play3D(SE_EXPLOSION);
    pBlast->reset();
    pBlast->positionAs(this);
}

MyTorpedo::~MyTorpedo() {
}

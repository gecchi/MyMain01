#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyTorpedo::MyTorpedo(const char* prm_name,MyOptionTorpedoController* prm_pOptionTorpedoController)
               : DefaultMeshSetActor(prm_name, "EffectLaserRefraction001", STATUS(MyTorpedo)) {
    _class_name = "MyTorpedo";
    pOptionTorpedoCtrlr_ = prm_pOptionTorpedoController;
    length_TailEffect_ = 8;

    pTailEffectDepository_ = NEW LaserChipDepository("DP_TailEffect");
    pTailEffectDepository_->config(length_TailEffect_, 0, NULL);
    for (int i = 0; i < length_TailEffect_; i++) {
        stringstream name;
        name <<  "MYOPTION"<<(pOptionTorpedoCtrlr_->pOption_->no_)<<"'s Torpedo's TailEffect["<<i<<"]";
        MyTorpedoTail* pChip = NEW MyTorpedoTail(name.str().c_str(), this);

        pChip->inactivateImmed();
        pTailEffectDepository_->addSubLast(pChip);
    }
    addSubGroup(pTailEffectDepository_);
    changeEffectTechnique("DestBlendOne"); //���Z��������Technique�w��
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
    pTarget_ = NULL;
    useProgress(10);
}

void MyTorpedo::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 70000);
}

void MyTorpedo::onReset() {
    pTarget_ = NULL;
}

void MyTorpedo::onActive() {
    _pStatus->reset();
    setAlpha(0.3);
    _SX = _SY = _SZ = 100;
    _pScaler->setScale(100);
    _pScaler->intoTargetScaleLinerStep(7000, 500);
    _pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(3));
    _pKurokoA->setFaceAngVelo(AXIS_Y, D_ANG(5));
    _pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(7));
    _pKurokoA->setMvVelo(20000);
    _pKurokoA->setMvAcce(-1000);
    _pKurokoA->setRzMvAngVelo(0);
    _pKurokoA->setRyMvAngVelo(0);
    _pKurokoA->setRzMvAngAcce(0);
    _pKurokoA->setRyMvAngAcce(0);
    _pKurokoA->forceMvVeloRange(200, 80000);
    _pKurokoA->forceRzMvAngVeloRange(-40000, 40000);
    _pKurokoA->forceRyMvAngVeloRange(-40000, 40000);
    _pKurokoA->stopTurnMvAngSequence();
    begin_X_ = _X;
    begin_Y_ = _Y;
    begin_Z_ = _Z;
    setHitAble(true);
    _pProg->set(MyTorpedo_IN_FIRE);
    move_section_ = 0;
}

void MyTorpedo::processBehavior() {
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
                pTailEffect->locate(begin_X_,begin_Y_,begin_Z_);
            }
        }
        //�����̃��[�u
        if (move_section_ == 0) {
            if (_pKurokoA->_veloMv == _pKurokoA->_veloBottomMv) {
                //�����I��
                _pKurokoA->setMvAcce(500);
                if (pTarget_) {
                    _pKurokoA->execTurnMvAngSequence(
                                pTarget_,
                                2000, 200,
                                TURN_ANTICLOSE_TO, false);
                } else {
                    _pKurokoA->execTurnMvAngSequence(
                                GgafDxUniverse::_X_goneRight, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                2000, 200,
                                TURN_ANTICLOSE_TO, false);
                }
                move_section_++;
            }
        }

        //���[�u�P
        if (move_section_ == 1) {
            if (_pKurokoA->isTurningMvAng()) {
                //�^�[�Q�b�g������҂�
            } else {
                //�^�[�Q�b�g����
                move_section_++;
            }
        }
        //���[�u�Q
        if (move_section_ == 2) {
            if (getActivePartFrame() < 120) {
                if (getActivePartFrame() % 10 == 0) {
                    if (pTarget_) {
                        if (pTarget_->isActiveInTheTree())  {
                            _pKurokoA->execTurnMvAngSequence(
                                        pTarget_,
                                        1000, 200,
                                        TURN_CLOSE_TO, false);
                        } else {
                            //�܂�����
                            _pKurokoA->setRzMvAngVelo(0);
                            _pKurokoA->setRyMvAngVelo(0);
                            _pKurokoA->setRzMvAngAcce(0);
                            _pKurokoA->setRyMvAngAcce(0);
                        }
                    } else {
                            _pKurokoA->execTurnMvAngSequence(
                                        GgafDxUniverse::_X_goneRight, _Y, _Z,
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
            if (getActivePartFrame() < 300) {
                if (getActivePartFrame() % 20 == 0) {
                    if (pTarget_) {
                        if (pTarget_->isActiveInTheTree())  {
                            _pKurokoA->execTurnMvAngSequence(
                                        pTarget_,
                                        300, 0,
                                        TURN_CLOSE_TO, false);
                        } else {
                            //�܂�����
                            _pKurokoA->setRzMvAngVelo(0);
                            _pKurokoA->setRyMvAngVelo(0);
                            _pKurokoA->setRzMvAngAcce(0);
                            _pKurokoA->setRyMvAngAcce(0);
                        }
                    } else {
                            _pKurokoA->execTurnMvAngSequence(
                                        GgafDxUniverse::_X_goneRight, _Y, _Z,
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
            _pKurokoA->setRzMvAngVelo(0);
            _pKurokoA->setRyMvAngVelo(0);
            _pKurokoA->setRzMvAngAcce(0);
            _pKurokoA->setRyMvAngAcce(0);
        }

        _pKurokoA->behave();
        _pScaler->behave();
    }
}

void MyTorpedo::processJudgement() {
    if (isOutOfUniverse() && _pProg->get() == MyTorpedo_IN_FIRE) {
        setHitAble(false);
        _pProg->change(MyTorpedo_RELEASE);
        GgafMainActor* pTailEffect = pTailEffectDepository_->getSubFirst();
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
    int sta = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
    setHitAble(false);
    _pProg->change(MyTorpedo_RELEASE);
    GgafMainActor* pTailEffect = pTailEffectDepository_->getSubFirst();
    for (int i = 0; i < length_TailEffect_; i++) {
        pTailEffect->inactivateDelay(i+1); //�O�ՃG�t�F�N�g�����X�ɏ�����悤�ɗ\��
        pTailEffect = pTailEffect->getNext();
    }
    _pKurokoA->setMvVelo(0);
    //���g��inactive()��processBehavior()�ōs���
    //�����̈ړ��G�t�F�N�g���S��inactive()�ɂȂ����ۂɎ��g��inactive()����

    //��������
    MyTorpedoBlast* pBlast = (MyTorpedoBlast*)pOptionTorpedoCtrlr_->pDepo_TorpedoBlast_->dispatch();
    if (pBlast) {
        pBlast->locatedBy(this);
        pBlast->reset();
    }

}

MyTorpedo::~MyTorpedo() {
}

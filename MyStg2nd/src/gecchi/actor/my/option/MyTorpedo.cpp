#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

MyTorpedo::MyTorpedo(const char* prm_name,MyOptionTorpedoController* prm_pMyOptionTorpedoController)
               : DefaultMeshSetActor(prm_name, "EffectLaserRefraction001", STATUS(MyTorpedo)) {
    _class_name = "MyTorpedo";
    _pMyOptionTorpedoController = prm_pMyOptionTorpedoController;
    _length_TailEffect = 4;

    _pTailEffectDepository = NEW LaserChipDepository("DP_TailEffect");
    _pTailEffectDepository->config(_length_TailEffect, 0, NULL);
    for (int i = 0; i < _length_TailEffect; i++) {
        stringstream name;
        name <<  "MYOPTION"<<(_pMyOptionTorpedoController->_pMyOption->_no)<<"'s Torpedo's TailEffect["<<i<<"]";
        MyTorpedoTail* pChip = NEW MyTorpedoTail(name.str().c_str(), this);

        pChip->inactivateImmediately();
        _pTailEffectDepository->addSubLast(pChip);
    }
    addSubGroup(_pTailEffectDepository);
    changeEffectTechnique("DestBlendOne"); //���Z��������Technique�w��
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
    _pTarget = NULL;
    useProgress(10);
}

void MyTorpedo::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 70000);
}

void MyTorpedo::onReset() {
    _pTarget = NULL;
}

void MyTorpedo::onActive() {
    _pStatus->reset();
    setAlpha(0.3);
    _SX = _SY = _SZ = 100;
    _pScaler->setScale(100);
    _pScaler->intoTargetScaleLinerStep(7000, 500);
    _pKurokoA->setFaceAngVelo(AXIS_X, DEG2ANG(3));
    _pKurokoA->setFaceAngVelo(AXIS_Y, DEG2ANG(5));
    _pKurokoA->setFaceAngVelo(AXIS_Z, DEG2ANG(7));
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
    _begin_X = _X;
    _begin_Y = _Y;
    _begin_Z = _Z;
    setHitAble(true);
    _pProg->set(MyTorpedo_IN_FIRE);
    _move_section = 0;
}

void MyTorpedo::processBehavior() {
    if (_pProg->get() == MyTorpedo_RELEASE) {
        if (_pTailEffectDepository->_num_chip_active == 0) {
            //�O�ՃG�t�F�N�g���S�Ĕ񊈓��ɂȂ����ꍇ
            inactivate(); //���g���Ō��inactivate()
        } else {
            addAlpha(-0.05);
        }
    }

    if (_pProg->get() == MyTorpedo_IN_FIRE) {
        //�����ۃG�t�F�N�g�ǉ�����
        if (_pTailEffectDepository->_num_chip_active < _length_TailEffect) {
            MyTorpedoTail* pTailEffect = (MyTorpedoTail*)_pTailEffectDepository->dispatch();
            if (pTailEffect) {
                pTailEffect->locate(_begin_X,_begin_Y,_begin_Z);
            }
        }
        //�����̃��[�u
        if (_move_section == 0) {
            if (_pKurokoA->_veloMv == _pKurokoA->_veloBottomMv) {
                //�����I��
                _pKurokoA->setMvAcce(500);
                if (_pTarget) {
                    _pKurokoA->execTurnMvAngSequence(
                                _pTarget,
                                2000, 200,
                                TURN_CLOSE_TO, false);
                } else {
                    _pKurokoA->execTurnMvAngSequence(
                                GgafDxUniverse::_X_goneRight, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                2000, 200,
                                TURN_CLOSE_TO, false);
                }
                _move_section++;
            }
        }

        //���[�u�P
        if (_move_section == 1) {
            if (_pKurokoA->isTurningMvAng()) {
                //�^�[�Q�b�g������҂�
            } else {
                //�^�[�Q�b�g����
                _move_section++;
            }

        }
        //���[�u�Q
        if (_move_section == 2) {
            if (getActivePartFrame() < 120) {
                if (getActivePartFrame() % 10 == 0) {
                    if (_pTarget) {
                        if (_pTarget->isActiveInTheWorld())  {
                            _pKurokoA->execTurnMvAngSequence(
                                        _pTarget,
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
                _move_section++;
            }
        }
        //���[�u�R
        if (_move_section == 3) {
            if (getActivePartFrame() < 300) {
                if (getActivePartFrame() % 20 == 0) {
                    if (_pTarget) {
                        if (_pTarget->isActiveInTheWorld())  {
                            _pKurokoA->execTurnMvAngSequence(
                                        _pTarget,
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
                _move_section++;
            }
        }
        //���[�u�S
        if (_move_section == 4) {
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
        GgafMainActor* pTailEffect = _pTailEffectDepository->getSubFirst();
        for (int i = 0; i < _length_TailEffect; i++) {
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
    GgafMainActor* pTailEffect = _pTailEffectDepository->getSubFirst();
    for (int i = 0; i < _length_TailEffect; i++) {
        pTailEffect->inactivateDelay(i+1); //�O�ՃG�t�F�N�g�����X�ɏ�����悤�ɗ\��
        pTailEffect = pTailEffect->getNext();
    }
    _pKurokoA->setMvVelo(0);
    //���g��inactive()��processBehavior()�ōs���
    //�����̈ړ��G�t�F�N�g���S��inactive()�ɂȂ����ۂɎ��g��inactive()����

    //��������
    MyTorpedoBlast* pBlast = (MyTorpedoBlast*)_pMyOptionTorpedoController->_pDepo_TorpedoBlast->dispatch();
    if (pBlast) {
        pBlast->locateAs(this);
        pBlast->reset();
    }

}

MyTorpedo::~MyTorpedo() {
}

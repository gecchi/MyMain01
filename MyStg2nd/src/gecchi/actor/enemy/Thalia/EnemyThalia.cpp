#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

enum {
    THALIA_PROG_MOVE = 1  ,
    THALIA_PROG_TURN_OPEN ,
    THALIA_PROG_FIRE_BEGIN,
    THALIA_PROG_IN_FIRE   ,
    THALIA_PROG_CLOSE     ,
};

EnemyThalia::EnemyThalia(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Thalia", STATUS(EnemyThalia)) {
        //CubeMapMorphMeshActor(prm_name, "1/ThaliaCM", STATUS(EnemyThalia)) {

    _class_name = "EnemyThalia";
    _veloTopMv = 20000;
    _iMovePatternNo = 0;
    _pSplSeq = NULL;
    _pDepo_Shot = NULL;
    _pDepo_ShotEffect = NULL;

    _pLaserChipDepo = NEW LaserChipDepository("MyRotLaser");
    _pLaserChipDepo->config(100, 0, NULL);
    EnemyStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //���[�U�[�X�g�b�N
        stringstream name;
        name <<  "EnemyStraightLaserChip001[" << i << "]";
        pChip = NEW EnemyStraightLaserChip001(name.str().c_str());
        pChip->setSource(this); //�ʒu��������
        pChip->inactivateImmed();
        _pLaserChipDepo->addSubLast(pChip);
    }
    addSubGroup(_pLaserChipDepo);

    _pSeTransmitter->useSe(2);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
    _pSeTransmitter->set(1, "laser001", GgafRepeatSeq::nextVal("CH_laser001"));     //����
    useProgress(THALIA_PROG_CLOSE);
    //�����J����Z�ʒu
    _dZ_camera_init = -1 * P_CAM->_cameraZ_org * LEN_UNIT * PX_UNIT;
}

void EnemyThalia::onCreateModel() {

    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyThalia::initialize() {
    setHitAble(true);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, 90000);
    setScaleRate(0.3);
}

void EnemyThalia::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);
    _pKurokoA->setFaceAngVelo(AXIS_X, 1000);
    _pKurokoA->execSmoothMvVeloSequenceD(_veloTopMv, 1000,
                                             MyShip::_lim_front - _X, 0.4, 0.6);
    _pProg->set(THALIA_PROG_MOVE);
    _iMovePatternNo = 0; //�s���p�^�[�����Z�b�g

}

void EnemyThalia::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));



    switch (_pProg->get()) {
        case THALIA_PROG_MOVE: {
            if (!_pKurokoA->isMoveingSmooth()) {
                _pMorpher->intoTargetAcceStep(1, 1.0, 0.0, 0.0005);
                _pKurokoA->execTurnMvAngSequence(P_MYSHIP->_X, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                                    0, 100,
                                                    TURN_CLOSE_TO);

                _pProg->changeNext();
            }
            break;
        }
        case THALIA_PROG_TURN_OPEN: {
            if (_pMorpher->_method[1] == NOMORPH ) {
                _pProg->changeNext();
            }
            break;
        }

        case THALIA_PROG_FIRE_BEGIN: {
            if ( _X - P_MYSHIP->_X > -_dZ_camera_init) {
                _pProg->change(THALIA_PROG_IN_FIRE);
            } else {
                _pProg->change(THALIA_PROG_CLOSE);
            }
            break;
        }
        case THALIA_PROG_IN_FIRE: {
            if (getActivePartFrame() % 10 == 0) {
                _pKurokoA->execTurnMvAngSequence(P_MYSHIP->_X, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                                    100, 0,
                                                    TURN_CLOSE_TO);
            }
            EnemyStraightLaserChip001* pLaser = (EnemyStraightLaserChip001*)_pLaserChipDepo->dispatch();
            if (pLaser) {
                if (pLaser->_pChip_front == NULL) {
                    _pSeTransmitter->play3D(1);
                    _pKurokoA->setFaceAngVelo(AXIS_X, 4000);
                }
            } else {
                _pProg->change(THALIA_PROG_CLOSE);
            }
            break;
        }
        case THALIA_PROG_CLOSE: {
            //�P�T�C�N�����[�U�[�ł��؂���
            _pMorpher->intoTargetLinerUntil(1, 0.0, 60);
            _pKurokoA->execSmoothMvVeloSequenceD(_veloTopMv, 1000, 1500000, 0.4, 0.6);
//            _pKurokoA->execSmoothMvVeloSequence(200, 1000000, 180);
            _pKurokoA->setFaceAngVelo(AXIS_X, 1000);
            _pProg->change(THALIA_PROG_MOVE);
        }
            break;
        default:
            break;
    }


    _pKurokoA->behave();
    _pMorpher->behave();
    _pSeTransmitter->behave();
}

void EnemyThalia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyThalia::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (_pProg->get() != THALIA_PROG_MOVE && (pOther->getKind() & KIND_MY) ) {
        changeEffectTechniqueInterim("Flush", 2); //�t���b�V��
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        if (pExplo001) {
            pExplo001->locateAs(this);
        }
        _pSeTransmitter->play3D(0);


        if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
            EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
            if (pExplo001) {
                pExplo001->locateAs(this);
            }
            _pSeTransmitter->play3D(0);


            //�ł��Ԃ��e
            if (_pDepo_Shot) {
//                MyStgUtil::shotWay001(this,
//                                       _pDepo_Shot,
//                                       P_MYSHIP,
//                                       10+_RANK_*10, 10000,
//                                       2000, 200);
//                MyStgUtil::shotWay001v2(this,
//                                       _pDepo_Shot,
//                                       P_MYSHIP,
//                                       10+_RANK_*10, 10000,
//                                       3000, 200,
//                                       5, 0.8);
//                MyStgUtil::shotWay002(this,
//                                       _pDepo_Shot,
//                                       P_MYSHIP,
//                                       20+_RANK_*10, 0,
//                                       2000, 200);
                  StgUtil::shotWay002v2(this,
                                       _pDepo_Shot,
                                       P_MYSHIP,
                                       R_EnemyThalia_ShotWay, 0,
                                       2000, 200,
                                       5, 0.8);

            }

            sayonara();
        }

    } else {

    }

}

void EnemyThalia::onInactive() {
    //sayonara();
}

EnemyThalia::~EnemyThalia() {
    DELETE_POSSIBLE_NULL(_pSplSeq);
}

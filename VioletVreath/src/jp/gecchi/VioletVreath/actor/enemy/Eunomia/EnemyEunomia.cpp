#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEunomia::EnemyEunomia(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Eunomia", STATUS(EnemyEunomia)) {
    _class_name = "EnemyEunomia";
    iMovePatternNo_ = 0;
    pSplSeq_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
    useProgress(10);
}

void EnemyEunomia::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyEunomia::initialize() {
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, -4000);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyEunomia::onReset() {

}

void EnemyEunomia::config(
        GgafLib::SplineSequence* prm_pSplSeq,
        GgafCore::GgafActorDepository* prm_pDepo_Shot,
        GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
        ) {
    DELETE_POSSIBLE_NULL(pSplSeq_);
    pSplSeq_ = prm_pSplSeq;
    pDepo_Shot_ = prm_pDepo_Shot;
    pDepo_ShotEffect_ = prm_pDepo_ShotEffect;
}


void EnemyEunomia::onActive() {
    if (pSplSeq_ == nullptr) {
        throwGgafCriticalException("EnemyEunomia�̓X�v���C���K�{�ł�config���ĉ�����");
    }
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->setFaceAng(AXIS_X, 0);
    iMovePatternNo_ = 0; //�s���p�^�[�����Z�b�g
    _pProg->set(PROG_ENTRY);
}

void EnemyEunomia::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    switch (_pProg->get()) {
        case PROG_ENTRY: {
            pSplSeq_->exec(SplineSequence::ABSOLUTE_COORD); //�X�v���C���ړ����J�n(1:���W����)
            _pProg->changeNext();
            break;
        }
        case PROG_SPLINE_MOVE: {
            if (pSplSeq_->isExecuting()) {
                //�X�v���C���ړ��I���̑҂��ڂ���
            } else {
                _pProg->changeNext(); //����
            }
            break;
        }
        case PROG_MOVE01_1: {
            if (_pProg->isJustChanged()) {
                //���@�֕����]��
                _pKurokoA->execTurnRzRyMvAngSequenceTwd(
                               P_MYSHIP->_X, _Y, P_MYSHIP->_Z,
                               2000, 0,
                               TURN_CLOSE_TO, true
                           );
            }

//            if (pDepo_Shot_) {
//                //���ˏ�V���b�g
//                int way = RR_EnemyEunomia_ShotWay(_RANK_); //�V���b�gWAY��
//                angle* paAng_way = NEW angle[way];
//                UTIL::getRadialAngle2D(0, way, paAng_way);
//                GgafDxDrawableActor* pActor_Shot;
//                for (int i = 0; i < way; i++) {
//                    pActor_Shot = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
//                    if (pActor_Shot) {
//                        pActor_Shot->locateWith(this);
//                        pActor_Shot->_pKurokoA->setRzRyMvAng(paAng_way[i], D90ANG);
//                    }
//                }
//                DELETEARR_IMPOSSIBLE_NULL(paAng_way);
//                //�V���b�g���˃G�t�F�N�g
//                if (pDepo_ShotEffect_) {
//                    GgafDxDrawableActor* pTestActor_Shot = (GgafDxDrawableActor*)pDepo_ShotEffect_->dispatch();
//                    if (pTestActor_Shot) {
//                        pTestActor_Shot->locateWith(this);
//                    }
//                }
//            }
            break;
        }
        default:
            break;
    }

//
//
//
//
//    //�y�p�^�[��1�F�X�v���C���ړ��z
//    if (_pProg->isJustChangedTo(1)) {
//        pSplSeq_->exec(SplineSequence::ABSOLUTE_COORD); //�X�v���C���ړ����J�n(1:���W����)
//    }
//    if (_pProg->get() == 1) {
//        //�X�v���C���ړ��I���҂�
//        if (pSplSeq_->isExecuting()) {
//            //�҂��ڂ���
//        } else {
//            _pProg->changeNext(); //���̃p�^�[����
//        }
//    }
//
//    switch (iMovePatternNo_) {
//        case 0:  //�y�p�^�[���O�F�X�v���C���ړ��J�n�z
//            if (pSplSeq_) {
//                pSplSeq_->exec(SplineSequence::ABSOLUTE_COORD); //�X�v���C���ړ����J�n(1:���W����)
//            }
//            iMovePatternNo_++; //���̍s���p�^�[����
//            break;
//
//        case 1:  //�y�p�^�[���P�F�X�v���C���ړ��I���҂��z
//            if (pSplSeq_) {
//                //�X�v���C���ړ��L��
//                if (!(pSplSeq_->isExecuting())) {
//                    iMovePatternNo_++; //�X�v���C���ړ����I�������玟�̍s���p�^�[����
//                }
//            } else {
//                //�X�v���C���ړ�����
//                iMovePatternNo_++; //�����Ɏ��̍s���p�^�[����
//            }
//            break;
//
//        case 2:  //�y�p�^�[���Q�F���ˏ�V���b�g���˂Ǝ��@�֕����]���z
//            if (pDepo_Shot_) {
//                //���ˏ�V���b�g
//                int way = RR_EnemyEunomia_ShotWay(_RANK_); //�V���b�gWAY��
//                angle* paAng_way = NEW angle[way];
//                UTIL::getRadialAngle2D(0, way, paAng_way);
//                GgafDxDrawableActor* pActor_Shot;
//                for (int i = 0; i < way; i++) {
//                    pActor_Shot = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
//                    if (pActor_Shot) {
//                        pActor_Shot->locateWith(this);
//                        pActor_Shot->_pKurokoA->setRzRyMvAng(paAng_way[i], D90ANG);
//                    }
//                }
//                DELETEARR_IMPOSSIBLE_NULL(paAng_way);
//                //�V���b�g���˃G�t�F�N�g
//                if (pDepo_ShotEffect_) {
//                    GgafDxDrawableActor* pTestActor_Shot = (GgafDxDrawableActor*)pDepo_ShotEffect_->dispatch();
//                    if (pTestActor_Shot) {
//                        pTestActor_Shot->locateWith(this);
//                    }
//                }
//            }
////            //���@�֕����]��
//            _pKurokoA->execTurnRzRyMvAngSequenceTwd(P_MYSHIP->_X, _Y, P_MYSHIP->_Z,
//                                                2000, 0,
//                                                TURN_CLOSE_TO);
//            iMovePatternNo_++; //���̍s���p�^�[����
//            break;
//
//        case 3:  //�y�s���p�^�[���R�z
//
//            break;
//        default:
//            break;
//    }

    pSplSeq_->behave(); //�X�v���C���ړ���U�镑��
    _pKurokoA->behave();
}

void EnemyEunomia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyEunomia::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        setHitAble(false); //�ȍ~����t���[�����Ńq�b�g�����Ȃ��B
        UTIL::activateExplosionEffectOf(this); //�����G�t�F�N�g�o��
        _pSeTx->play3D(SE_EXPLOSION);          //�������Đ�
        if (pOther->getKind() & KIND_MY) { //���@���Ɍ�����ď��ł̏ꍇ��
            UTIL::activateItemOf(this); //�A�C�e���o��
        }
        sayonara();
    } else {
        //�ꔭ�Ŏ��ʂ̂ŃR�R�͒ʂ�Ȃ��n�Y�B
    }
}

void EnemyEunomia::onInactive() {
    DELETE_POSSIBLE_NULL(pSplSeq_);
}

EnemyEunomia::~EnemyEunomia() {
    DELETE_POSSIBLE_NULL(pSplSeq_);
}



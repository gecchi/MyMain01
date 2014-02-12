#include "stdafx.h"
#include "EnemyUnomia.h"

#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyUnomia::EnemyUnomia(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Unomia", STATUS(EnemyUnomia)) {
    _class_name = "EnemyUnomia";
    iMovePatternNo_ = 0;
    pKurokoLeader_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
    useProgress(PROG_BANPEI);
}

void EnemyUnomia::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyUnomia::initialize() {
    _pKuroko->relateFaceWithMvAng(true);
    _pKuroko->setFaceAngVelo(AXIS_X, -4000);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyUnomia::onReset() {
}

void EnemyUnomia::config(
        GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
        GgafCore::GgafActorDepository* prm_pDepo_Shot,
        GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
        ) {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
    pKurokoLeader_ = prm_pKurokoLeader;
    pDepo_Shot_ = prm_pDepo_Shot;
    pDepo_ShotEffect_ = prm_pDepo_ShotEffect;
}


void EnemyUnomia::onActive() {
    if (pKurokoLeader_ == nullptr) {
        throwGgafCriticalException("EnemyUnomia�̓X�v���C���K�{�ł�config���ĉ�����");
    }
    _pStatus->reset();
    setHitAble(true);
    setRzFaceAng(0);
    iMovePatternNo_ = 0; //�s���p�^�[�����Z�b�g
    _pProg->reset(PROG_ENTRY);
}

void EnemyUnomia::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    switch (_pProg->get()) {
        case PROG_ENTRY: {
            pKurokoLeader_->start(SplineKurokoLeader::ABSOLUTE_COORD);
            _pProg->changeNext();
            break;
        }
        case PROG_SPLINE_MOVE: {
            if (pKurokoLeader_->isFinished()) {
                _pProg->changeNext(); //����
            }
            break;
        }
        case PROG_MOVE01_1: {
            if (_pProg->isJustChanged()) {
                //���@�֕����]��
                _pKuroko->turnMvAngTwd(
                               P_MYSHIP->_x, _y, P_MYSHIP->_z,
                               2000, 0,
                               TURN_CLOSE_TO, true
                           );
            }

//            if (pDepo_Shot_) {
//                //���ˏ�V���b�g
//                int way = RF_EnemyUnomia_ShotWay(G_RANK); //�V���b�gWAY��
//                angle* paAng_way = NEW angle[way];
//                UTIL::getRadialAngle2D(0, way, paAng_way);
//                GgafDxDrawableActor* pActor_Shot;
//                for (int i = 0; i < way; i++) {
//                    pActor_Shot = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
//                    if (pActor_Shot) {
//                        pActor_Shot->positionAs(this);
//                        pActor_Shot->_pKuroko->setRzRyMvAng(paAng_way[i], D90ANG);
//                    }
//                }
//                GGAF_DELETEARR(paAng_way);
//                //�V���b�g���˃G�t�F�N�g
//                if (pDepo_ShotEffect_) {
//                    GgafDxDrawableActor* pTestActor_Shot = (GgafDxDrawableActor*)pDepo_ShotEffect_->dispatch();
//                    if (pTestActor_Shot) {
//                        pTestActor_Shot->positionAs(this);
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
//        pKurokoLeader_->start(SplineKurokoLeader::ABSOLUTE_COORD); //�X�v���C���ړ����J�n(1:���W����)
//    }
//    if (_pProg->get() == 1) {
//        //�X�v���C���ړ��I���҂�
//        if (pKurokoLeader_->isLeading()) {
//            //�҂��ڂ���
//        } else {
//            _pProg->changeNext(); //���̃p�^�[����
//        }
//    }
//
//    switch (iMovePatternNo_) {
//        case 0:  //�y�p�^�[���O�F�X�v���C���ړ��J�n�z
//            if (pKurokoLeader_) {
//                pKurokoLeader_->start(SplineKurokoLeader::ABSOLUTE_COORD); //�X�v���C���ړ����J�n(1:���W����)
//            }
//            iMovePatternNo_++; //���̍s���p�^�[����
//            break;
//
//        case 1:  //�y�p�^�[���P�F�X�v���C���ړ��I���҂��z
//            if (pKurokoLeader_) {
//                //�X�v���C���ړ��L��
//                if (!(pKurokoLeader_->isLeading())) {
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
//                int way = RF_EnemyUnomia_ShotWay(G_RANK); //�V���b�gWAY��
//                angle* paAng_way = NEW angle[way];
//                UTIL::getRadialAngle2D(0, way, paAng_way);
//                GgafDxDrawableActor* pActor_Shot;
//                for (int i = 0; i < way; i++) {
//                    pActor_Shot = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
//                    if (pActor_Shot) {
//                        pActor_Shot->positionAs(this);
//                        pActor_Shot->_pKuroko->setRzRyMvAng(paAng_way[i], D90ANG);
//                    }
//                }
//                GGAF_DELETEARR(paAng_way);
//                //�V���b�g���˃G�t�F�N�g
//                if (pDepo_ShotEffect_) {
//                    GgafDxDrawableActor* pTestActor_Shot = (GgafDxDrawableActor*)pDepo_ShotEffect_->dispatch();
//                    if (pTestActor_Shot) {
//                        pTestActor_Shot->positionAs(this);
//                    }
//                }
//            }
////            //���@�֕����]��
//            _pKuroko->turnMvAngTwd(P_MYSHIP->_x, _y, P_MYSHIP->_z,
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

    pKurokoLeader_->behave(); //�X�v���C���ړ���U�镑��
    _pKuroko->behave();
}

void EnemyUnomia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyUnomia::onHit(GgafActor* prm_pOtherActor) {
    if (strcmp(_name, "Unomia[0]") == 0) {
        _TRACE_("EnemyUnomia::onHit()");
    }

    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //��j��
    }
}

void EnemyUnomia::onInactive() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

EnemyUnomia::~EnemyUnomia() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}



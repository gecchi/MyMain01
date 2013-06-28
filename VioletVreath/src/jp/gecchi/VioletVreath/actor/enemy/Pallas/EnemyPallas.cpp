#include "stdafx.h"
#include "EnemyPallas.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyPallas::EnemyPallas(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Pallas", STATUS(EnemyPallas)) {
    _class_name = "EnemyPallas";
    iMovePatternNo_ = 0;
    pKurokoLeader_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
    useProgress(10);
}

void EnemyPallas::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyPallas::initialize() {
    setHitAble(true);
    _pKurokoA->setFaceAngVelo(AXIS_Z, -7000);
    _pKurokoA->relateMvFaceAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyPallas::onActive() {
    if (pKurokoLeader_ == nullptr) {
        throwGgafCriticalException("EnemyPallas�̓X�v���C���K�{�ł�config���ĉ�����");
    }

    _pStatus->reset();
   iMovePatternNo_ = 0; //�s���p�^�[�����Z�b�g
    _pProg->change(1);
}

void EnemyPallas::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //�y�p�^�[��1�F�X�v���C���ړ��z
    if (_pProg->isJustChangedTo(1)) {
        pKurokoLeader_->start(SplineKurokoLeader::ABSOLUTE_COORD); //�X�v���C���ړ����J�n(1:���W����)
    }
    if (_pProg->get() == 1) {
        //�X�v���C���ړ��I���҂�
        if (pKurokoLeader_->isFinished()) {
            _pProg->changeNext(); //���̃p�^�[����
        }
    }

    switch (iMovePatternNo_) {
        case 0:  //�y�p�^�[���O�F�X�v���C���ړ��J�n�z
            if (pKurokoLeader_) {
                pKurokoLeader_->start(SplineKurokoLeader::ABSOLUTE_COORD); //�X�v���C���ړ����J�n(1:���W����)
            }
            iMovePatternNo_++; //���̍s���p�^�[����
            break;

        case 1:  //�y�p�^�[���P�F�X�v���C���ړ��I���҂��z
            if (pKurokoLeader_) {
                //�X�v���C���ړ��L��
                if (pKurokoLeader_->isFinished()) {
                    iMovePatternNo_++; //�X�v���C���ړ����I�������玟�̍s���p�^�[����
                }
            } else {
                //�X�v���C���ړ�����
                iMovePatternNo_++; //�����Ɏ��̍s���p�^�[����
            }
            break;

        case 2:  //�y�p�^�[���Q�F���ˏ�V���b�g���˂Ǝ��@�֕����]���z
            if (pDepo_Shot_) {
                //���ˏ�V���b�g
                int way = RF_EnemyPallas_ShotWay(G_RANK); //�V���b�gWAY��
                angle* paAng_way = NEW angle[way];
                UTIL::getRadialAngle2D(0, way, paAng_way);
                GgafDxDrawableActor* pActor_Shot;
                for (int i = 0; i < way; i++) {
                    pActor_Shot = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
                    if (pActor_Shot) {
                        pActor_Shot->positionAs(this);
                        pActor_Shot->_pKurokoA->setRzRyMvAng(paAng_way[i], D90ANG);
                        pActor_Shot->activate();
                    }
                }
                GGAF_DELETEARR(paAng_way);
                //�V���b�g���˃G�t�F�N�g
                if (pDepo_ShotEffect_) {
                    GgafDxDrawableActor* pTestActor_Shot = (GgafDxDrawableActor*)pDepo_ShotEffect_->dispatch();
                    if (pTestActor_Shot) {
                        pTestActor_Shot->positionAs(this);
                    }
                }
            }
//            //���@�֕����]��
            _pKurokoA->turnMvAngTwd(P_MYSHIP->_X, _Y, P_MYSHIP->_Z,
                                    2000, 0,
                                    TURN_CLOSE_TO, true);
            iMovePatternNo_++; //���̍s���p�^�[����
            break;

        case 3:  //�y�s���p�^�[���R�z

            break;
        default:
            break;
    }

    if (pKurokoLeader_) {
        pKurokoLeader_->behave(); //�X�v���C���ړ���U�镑��
    }
    _pKurokoA->behave();
    //_pSeTx->behave();
}

void EnemyPallas::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyPallas::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //��j��
    }
}

void EnemyPallas::onInactive() {
    sayonara();
}

EnemyPallas::~EnemyPallas() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

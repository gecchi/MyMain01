#include "EnemyAllas.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
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

EnemyAllas::EnemyAllas(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Allas", STATUS(EnemyAllas)) {
    _class_name = "EnemyAllas";
    iMovePatternNo_ = 0;
    pKurokoLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
    useProgress(10);
}

void EnemyAllas::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyAllas::initialize() {
    setHitAble(true);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setFaceAngVelo(AXIS_Z, -7000);
    pKuroko->relateFaceByMvAng(true);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 40000);
}

void EnemyAllas::onActive() {
    if (pKurokoLeader_ == nullptr) {
        throwGgafCriticalException("EnemyAllas�̓X�v���C���K�{�ł�config���ĉ�����");
    }

    getStatus()->reset();
   iMovePatternNo_ = 0; //�s���p�^�[�����Z�b�g
   getProgress()->change(1);
}

void EnemyAllas::processBehavior() {
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    //�y�p�^�[��1�F�X�v���C���ړ��z
    if (pProg->isJustChangedTo(1)) {
        pKurokoLeader_->start(SplineKurokoLeader::ABSOLUTE_COORD); //�X�v���C���ړ����J�n(1:���W����)
    }
    if (pProg->get() == 1) {
        //�X�v���C���ړ��I���҂�
        if (pKurokoLeader_->isFinished()) {
            pProg->changeNext(); //���̃p�^�[����
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
            if (pDepo_shot_) {
                //���ˏ�V���b�g
                int way = RF_EnemyAllas_ShotWay(G_RANK); //�V���b�gWAY��
                angle* paAng_way = NEW angle[way];
                UTIL::getRadialAngle2D(0, way, paAng_way);
                GgafDxDrawableActor* pActor_shot;
                for (int i = 0; i < way; i++) {
                    pActor_shot = (GgafDxDrawableActor*)pDepo_shot_->dispatch();
                    if (pActor_shot) {
                        pActor_shot->positionAs(this);
                        pActor_shot->getKuroko()->setRzRyMvAng(paAng_way[i], D90ANG);
                        pActor_shot->activate();
                    }
                }
                GGAF_DELETEARR(paAng_way);
                //�V���b�g���˃G�t�F�N�g
                if (pDepo_effect_) {
                    GgafDxDrawableActor* pTestActor_Shot = (GgafDxDrawableActor*)pDepo_effect_->dispatch();
                    if (pTestActor_Shot) {
                        pTestActor_Shot->positionAs(this);
                    }
                }
            }
//            //���@�֕����]��
            pKuroko->turnMvAngTwd(P_MYSHIP->_x, _y, P_MYSHIP->_z,
                                    2000, 0,
                                    TURN_CLOSE_TO, true);
            iMovePatternNo_++; //���̍s���p�^�[����
            break;

        case 3:   //�y�s���p�^�[���R�z

            break;
        default:
            break;
    }

    if (pKurokoLeader_) {
        pKurokoLeader_->behave(); //�X�v���C���ړ���U�镑��
    }
    pKuroko->behave();
    //getSeTx()->behave();
}

void EnemyAllas::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAllas::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //��j��
    }
}

void EnemyAllas::onInactive() {
    sayonara();
}

EnemyAllas::~EnemyAllas() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

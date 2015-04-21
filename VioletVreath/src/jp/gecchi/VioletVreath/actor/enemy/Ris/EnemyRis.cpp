#include "EnemyRis.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyRis::EnemyRis(const char* prm_name)
      : DefaultMeshSetActor(prm_name, "Ris", STATUS(EnemyRis)) {
    _class_name = "EnemyRis";
    iMovePatternNo_ = 0;
    pKurokoLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
}

void EnemyRis::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setBlinkPower(0.5, 0.9);
    pModel->getTexBlinker()->setRange(0.5, 2.0);
    pModel->getTexBlinker()->beat(60, 3, 0, 57, -1);
}

void EnemyRis::initialize() {
    setHitAble(true);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->setRollFaceAngVelo(5000);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB(0, -30000, -30000, -30000, 30000, 30000, 30000);
}

void EnemyRis::onActive() {
    getStatus()->reset();
    iMovePatternNo_ = 0; //�s���p�^�[�����Z�b�g
}

void EnemyRis::processBehavior() {
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* const pKuroko = getKuroko();
    switch (iMovePatternNo_) {
        case 0:  //�y�p�^�[���O�F�X�v���C���ړ��J�n�z
            if (pKurokoLeader_) {
                pKurokoLeader_->start(ABSOLUTE_COORD); //�X�v���C���ړ����J�n
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
                int way = RF_EnemyRis_ShotWay(G_RANK); //�V���b�gWAY��
                UTIL::shotWay004(_x, _y, _z,
                                 D180ANG, D0ANG,
                                 pDepo_shot_,
                                 PX_C(20), way, D_ANG(120),
                                 0, 0,  //�V���b�g���ő��x��ݒ�
                                 1, 0, 1.0,
                                 nullptr );
                //�V���b�g���˃G�t�F�N�g
                if (pDepo_effect_) {
                    GgafDxFigureActor* pTestActor_Shot = (GgafDxFigureActor*)pDepo_effect_->dispatch();
                    if (pTestActor_Shot) {
                        pTestActor_Shot->positionAs(this);
                    }
                }
            }
            //���@�֕����]��
            pKuroko->turnMvAngTwd(P_MYSHIP,
                                  3000, 0,
                                  TURN_CLOSE_TO, true);
            iMovePatternNo_++; //���̍s���p�^�[����
            break;

        case 3:  //�y�s���p�^�[���R�F���@�փO���b�Ƌt��]�ŕ����]���J�n�z
            if (_z-10000 < P_MYSHIP->_z && P_MYSHIP->_z < _z+10000) {
                //���@��Z�����ڋ߂�����O���b�Ƌt��]�ŕ����]��
                pKuroko->turnMvAngTwd(MyShip::lim_x_behaind_ - 500000 , _y, _z,
                                      10000, 0,
                                      TURN_CLOSE_TO, true);
                pKuroko->setMvAcce(100);
                iMovePatternNo_++;
            } else {
                //���@��Z�����ڋ߂���܂ő҂�
            }
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

void EnemyRis::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyRis::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyRis::onInactive() {
    sayonara();
}

EnemyRis::~EnemyRis() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

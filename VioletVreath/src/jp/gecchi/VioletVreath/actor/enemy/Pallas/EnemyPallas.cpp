#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyPallas::EnemyPallas(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Pallas", STATUS(EnemyPallas)) {
    _class_name = "EnemyPallas";
    iMovePatternNo_ = 0;
    pSplSeq_ = nullptr;
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
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyPallas::onActive() {
    if (pSplSeq_ == nullptr) {
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
    if (_pProg->hasJustChangedTo(1)) {
        pSplSeq_->exec(SplineSequence::ABSOLUTE_COORD); //�X�v���C���ړ����J�n(1:���W����)
    }
    if (_pProg->get() == 1) {
        //�X�v���C���ړ��I���҂�
        if (pSplSeq_->isExecuting()) {
            //�҂��ڂ���
        } else {
            _pProg->changeNext(); //���̃p�^�[����
        }
    }

    switch (iMovePatternNo_) {
        case 0:  //�y�p�^�[���O�F�X�v���C���ړ��J�n�z
            if (pSplSeq_) {
                pSplSeq_->exec(SplineSequence::ABSOLUTE_COORD); //�X�v���C���ړ����J�n(1:���W����)
            }
            iMovePatternNo_++; //���̍s���p�^�[����
            break;

        case 1:  //�y�p�^�[���P�F�X�v���C���ړ��I���҂��z
            if (pSplSeq_) {
                //�X�v���C���ړ��L��
                if (!(pSplSeq_->isExecuting())) {
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
                int way = RR_EnemyPallas_ShotWay(_RANK_); //�V���b�gWAY��
                angle* paAng_way = NEW angle[way];
                UTIL::getRadialAngle2D(0, way, paAng_way);
                GgafDxDrawableActor* pActor_Shot;
                for (int i = 0; i < way; i++) {
                    pActor_Shot = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
                    if (pActor_Shot) {
                        pActor_Shot->locateWith(this);
                        pActor_Shot->_pKurokoA->setRzRyMvAng(paAng_way[i], D90ANG);
                        pActor_Shot->activate();
                    }
                }
                DELETEARR_IMPOSSIBLE_NULL(paAng_way);
                //�V���b�g���˃G�t�F�N�g
                if (pDepo_ShotEffect_) {
                    GgafDxDrawableActor* pTestActor_Shot = (GgafDxDrawableActor*)pDepo_ShotEffect_->dispatch();
                    if (pTestActor_Shot) {
                        pTestActor_Shot->locateWith(this);
                    }
                }
            }
//            //���@�֕����]��
            _pKurokoA->execTurnRzRyMvAngSequenceTwd(P_MYSHIP->_X, _Y, P_MYSHIP->_Z,
                                                2000, 0,
                                                TURN_CLOSE_TO, true);
            iMovePatternNo_++; //���̍s���p�^�[����
            break;

        case 3:  //�y�s���p�^�[���R�z

            break;
        default:
            break;
    }

    if (pSplSeq_) {
        pSplSeq_->behave(); //�X�v���C���ړ���U�镑��
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
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //��������
        UTIL::activateExplosionEffectOf(this);
        _pSeTx->play3D(SE_EXPLOSION);

        //���@���Ɍ�����ď��ł̏ꍇ�A
        if (pOther->getKind() & KIND_MY) {
            //�A�C�e���o��
            UTIL::activateItemOf(this);
        }
        sayonara();
    }
}

void EnemyPallas::onInactive() {
    sayonara();
}

EnemyPallas::~EnemyPallas() {
    DELETE_POSSIBLE_NULL(pSplSeq_);
}

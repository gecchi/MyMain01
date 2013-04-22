#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHebe::EnemyHebe(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Hebe", STATUS(EnemyHebe)) {
    _class_name = "EnemyHebe";
    pKurokoStepper_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
    useProgress(PROG_MOVE02_2);
}

void EnemyHebe::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyHebe::initialize() {
    _pKurokoA->relateMvFaceAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyHebe::config(
        GgafLib::SplineKurokoStepper* prm_pKurokoStepper,
        GgafCore::GgafActorDepository* prm_pDepo_Shot,
        GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
        ) {
    GGAF_DELETE_NULLABLE(pKurokoStepper_);
    pKurokoStepper_ = prm_pKurokoStepper;
    pDepo_Shot_ = prm_pDepo_Shot;
    pDepo_ShotEffect_ = prm_pDepo_ShotEffect;
}

void EnemyHebe::onActive() {
    if (pKurokoStepper_ == nullptr) {
        throwGgafCriticalException("EnemyHebe�̓X�v���C���K�{�ł�config���ĉ�����");
    }
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->setFaceAng(AXIS_X, 0);
    _pKurokoA->setMvAcce(0);
    _pProg->reset(PROG_MOVE01_1);
}

void EnemyHebe::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;

    switch (_pProg->get()) {
        case PROG_MOVE01_1: {
            if (_pProg->getFrameInProgress() > (PX_C(300) / ABS(_pKurokoA->_veloMv))) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_SPLINE_MOVE: {
            if (_pProg->isJustChanged()) {
                pKurokoStepper_->start(SplineKurokoStepper::RELATIVE_COORD);
            }
            if (pKurokoStepper_->isFinished()) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE02_1: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->turnMvAngTwd(_X - PX_C(300), _Y, _Z,
                                        D_ANG(1), 0, TURN_CLOSE_TO, false);
            }

            break;
        }
    }

    pKurokoStepper_->behave(); //�X�v���C���ړ���U�镑��
    _pKurokoA->behave();
}

void EnemyHebe::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyHebe::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //�j��
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
    } else {
        //��j��
        effectFlush(2); //�t���b�V��
    }
}

void EnemyHebe::onInactive() {
    GGAF_DELETE_NULLABLE(pKurokoStepper_);
}

EnemyHebe::~EnemyHebe() {
    GGAF_DELETE_NULLABLE(pKurokoStepper_);
}



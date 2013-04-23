#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAdelheid::EnemyAdelheid(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Adelheid", STATUS(EnemyAdelheid)) {
    _class_name = "EnemyAdelheid";
    pKurokoStepper_ = nullptr;
    pDepo_Shot_ = nullptr;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
    useProgress(PROG_FINISH);
}

void EnemyAdelheid::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAdelheid::initialize() {
    _pKurokoA->relateMvFaceAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyAdelheid::config(
        GgafLib::SplineKurokoStepper* prm_pKurokoStepper,
        GgafCore::GgafActorDepository* prm_pDepo_Shot
        ) {
    GGAF_DELETE_NULLABLE(pKurokoStepper_);
    pKurokoStepper_ = prm_pKurokoStepper;
    pDepo_Shot_ = prm_pDepo_Shot;
}

void EnemyAdelheid::onActive() {
    if (pKurokoStepper_ == nullptr) {
        throwGgafCriticalException("EnemyAdelheid�̓X�v���C���K�{�ł�config���ĉ�����");
    }
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->setFaceAng(AXIS_X, 0);
    _pKurokoA->setMvAcce(0);
    _pProg->reset(PROG_INIT);
}

void EnemyAdelheid::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;

    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->changeNext();
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

        case PROG_FINISH: {
            if (_pProg->isJustChanged()) {
               sayonara();
            }
            break;
        }
    }

    pKurokoStepper_->behave(); //�X�v���C���ړ���U�镑��
    _pKurokoA->behave();
}

void EnemyAdelheid::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAdelheid::onHit(GgafActor* prm_pOtherActor) {
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

void EnemyAdelheid::onInactive() {
    GGAF_DELETE_NULLABLE(pKurokoStepper_);
}

EnemyAdelheid::~EnemyAdelheid() {
    GGAF_DELETE_NULLABLE(pKurokoStepper_);
}



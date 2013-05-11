#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAdelheid::EnemyAdelheid(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Adelheid", STATUS(EnemyAdelheid)) {
    _class_name = "EnemyAdelheid";
    pKurokoLeader_ = nullptr;
    pDepo_Shot_ = nullptr;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
    pFormation_ = nullptr;
    useProgress(PROG_MOVING_AFTER_LEAD);
}

void EnemyAdelheid::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAdelheid::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
    setScaleR(0.3);

}

void EnemyAdelheid::config(
        GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
        GgafCore::GgafActorDepository* prm_pDepo_Shot
        ) {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
    pKurokoLeader_ = prm_pKurokoLeader;
    pDepo_Shot_ = prm_pDepo_Shot;
}

void EnemyAdelheid::onActive() {
    if (pKurokoLeader_ == nullptr) {
        throwGgafCriticalException("EnemyAdelheid�̓X�v���C���K�{�ł�config���ĉ������B this="<<this<<" name="<<getName());
    }
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->setFaceAng(AXIS_X, 0);
    _pKurokoA->setMvAcce(0);
    _pKurokoA->keepOnTurningFaceAngTwd(P_MYSHIP,
                                       D_ANG(2), 0, TURN_CLOSE_TO, false);
    pFormation_ = (FormationAdelheid*)getFormation();
    _pProg->reset(PROG_INIT);
    _TRACE_("EnemyAdelheid::onActive() PROG_INIT�փ��Z�b�g this="<<getName()<<"("<<this<<")");
}

void EnemyAdelheid::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;

    switch (_pProg->get()) {
        case PROG_INIT: {
            _TRACE_("EnemyAdelheid::processBehavior() PROG_INIT this="<<getName()<<"("<<this<<")");
            
            pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION);
            _pProg->changeNext();
            break;
        }
        case PROG_MOVING: {
            if (_pProg->isJustChanged()) {
                _TRACE_("EnemyAdelheid::processBehavior() PROG_MOVING this="<<getName()<<"("<<this<<")");
            }
            if (pFormation_) {
                _pKurokoA->_veloMv = pFormation_->mv_velo_member_;
            }
            //pKurokoLeader_->isFinished() �҂�
            break;
        }

        //�S�[���̃p���T�i�����Ȃ��ꍇ�A���̌�̈ړ�
        case PROG_MOVING_AFTER_LEAD: {
            if (_pProg->isJustChanged()) {
                _TRACE_("EnemyAdelheid::processBehavior() pPalisana_goal ������(T_T)�B�Ȃ�ƂȂ����@��_���IPROG_MOVING_AFTER_LEAD this="<<getName()<<"("<<this<<")");
                _pKurokoA->turnMvAngTwd(P_MYSHIP,
                                        D_ANG(2), 0, TURN_ANTICLOSE_TO, false);
                _pKurokoA->setMvAcce(100);
            }
            //isOutOfUniverse() �܂ŁE�E�E
            break;
        }
    }


    pKurokoLeader_->behave(); //�X�v���C���ړ���U�镑��
    _pKurokoA->behave();
}

void EnemyAdelheid::processJudgement() {
    if (_pProg->get() == PROG_MOVING) {
        if (pKurokoLeader_->isFinished()) {
            if (pFormation_) {
                if (pFormation_->pPalisana_goal) {
                    _TRACE_("EnemyAdelheid::processJudgement() pPalisana_goal pPalisana_goal �����݁B�ʏ�I�� this="<<getName()<<"("<<this<<")");
                    _pProg->changeNothing();
                    sayonara();
                } else {
                    _TRACE_("EnemyAdelheid::processJudgement() pPalisana_goal pPalisana_goal �������BPROG_MOVING_AFTER_LEAD�փC�N�X this="<<getName()<<"("<<this<<")");
                    _pProg->change(PROG_MOVING_AFTER_LEAD);
                }
            } else {
                //�_�~�[�̎����A���Ȃ��n�Y
            }
        }
    }

    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAdelheid::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //��j��
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyAdelheid::onInactive() {
    pFormation_ = nullptr;
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

EnemyAdelheid::~EnemyAdelheid() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}



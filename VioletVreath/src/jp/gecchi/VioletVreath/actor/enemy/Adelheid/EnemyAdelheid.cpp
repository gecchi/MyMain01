#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAdelheid::EnemyAdelheid(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Adelheid", STATUS(EnemyAdelheid)) {
    _class_name = "EnemyAdelheid";
    pKurokoLeader_ = nullptr;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
    useProgress(PROG_MOVING_AFTER_LEAD);
    pProg2_ = createProgress(PROG2_CLOSE);
    shot_begin_frame_ = 0;
}

void EnemyAdelheid::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAdelheid::nextFrame() {
    DefaultMorphMeshActor::nextFrame();
    if (!_was_paused_flg && _is_active_in_the_tree_flg) {
        pProg2_->update();
    }
}
void EnemyAdelheid::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
    setScaleR(0.3);
}

void EnemyAdelheid::onActive() {
    if (getFormation()) {
        GGAF_DELETE_NULLABLE(pKurokoLeader_);
        pKurokoLeader_ = ((FormationAdelheid*)getFormation())->getSplManuf()->createKurokoLeader(_pKurokoA);
    }
    if (pKurokoLeader_ == nullptr) {
        throwGgafCriticalException("EnemyAdelheid�̓X�v���C���K�{�ł�config���ĉ������B this="<<this<<" name="<<getName());
    }
    _pStatus->reset();
    setHitAble(true);
    _pMorpher->reset();
    _pKurokoA->setFaceAng(AXIS_X, 0);
    _pKurokoA->setMvAcce(0);
    _pKurokoA->keepOnTurningFaceAngTwd(P_MYSHIP,
                                       D_ANG(1), 0, TURN_CLOSE_TO, false);
    _pProg->reset(PROG_INIT);
    pProg2_->reset(PROG2_WAIT);
}

void EnemyAdelheid::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;

    //�ړ��̏�ԑJ��------------------------------
    switch (_pProg->get()) {
        case PROG_INIT: {
            pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION);
            _pProg->changeNext();
            break;
        }
        case PROG_MOVING: {
            if (_pProg->isJustChanged()) {
            }

            //pKurokoLeader_->isFinished() �҂�
            break;
        }

        //�S�[���̃p���T�i�����Ȃ��ꍇ�A���̌�̈ړ�
        case PROG_MOVING_AFTER_LEAD: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->setMvAcce(100);
            }

            //isOutOfUniverse() �܂ŁE�E�E
            break;
        }
    }

    //�V���b�g���˂̏�ԑJ��-----------------------------------
    switch (pProg2_->get()) {
        case PROG2_WAIT: {
            //open_shot() �҂��E�E�E
            break;
        }
        case PROG2_OPEN: {
            if (pProg2_->isJustChanged()) {
                _pMorpher->morphAcceStep(MPH_OPEN, 1.1, 0, 0.001);
            }
            if (!_pMorpher->isMorphing()) {
                _pMorpher->setWeight(MPH_OPEN, 1.0);
                pProg2_->changeNext();
            }
            break;
        }

        case PROG2_SHOT: {
            if (pProg2_->isJustChanged()) {
                shot_begin_frame_ = RND(120, 240);
            }
            if (pProg2_->getFrameInProgress() == shot_begin_frame_) {
                UTIL::shotWay002(
                       this,
                       ((FormationAdelheid*)getFormation())->pConnection_ShotDepo_->peek(),
                       PX_C(20),     //r
                       5,            //way��
                       D_ANG(10),    //way��way�̊Ԋu
                       PX_C(5),      //�������x
                       100,          //�����x
                       2,            //way�̃Z�b�g��
                       0,            //�Z�b�g�ƃZ�b�g�̊Ԋu�t���[��
                       0.8f,         //�Z�b�g�����ɔ����������x������
                       nullptr
                     );
            }
            if (pProg2_->getFrameInProgress() == 240) {
                pProg2_->changeNext();
            }
            break;
        }
        case PROG2_CLOSE: {
            if (pProg2_->isJustChanged()) {
                _pMorpher->morphAcceStep(MPH_OPEN, 0.0, 0, -0.01);
            }
            if (!_pMorpher->isMorphing()) {
                pProg2_->changeNothing();
            }

            break;
        }
    }
    //-----------------------------------------------

    if (getFormation()) {
        _pKurokoA->_veloMv = ((FormationAdelheid*)getFormation())->mv_velo_member_;
        _pKurokoA->_angveloFace[AXIS_X] = ((FormationAdelheid*)getFormation())->mv_velo_member_ / 2;
    }

    pKurokoLeader_->behave(); //�X�v���C���ړ���U�镑��
    _pKurokoA->behave();
    _pMorpher->behave();
}

void EnemyAdelheid::processJudgement() {
    if (_pProg->get() == PROG_MOVING) {
        if (pKurokoLeader_->isFinished()) {
            if (getFormation()) {
                if (((FormationAdelheid*)getFormation())->pPalisana_goal) {
                    _pProg->changeNothing();
                    sayonara();
                } else {
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
    if (pProg2_->isNothing() || pProg2_->get() == PROG2_WAIT) {
        //�J���ĂȂ��̂œ�����Ȃ�
    } else {
        bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
        if (was_destroyed) {
            //�j��
            _pSeTx->play3D(SE_EXPLOSION);
        } else {
            //��j��
            _pSeTx->play3D(SE_DAMAGED);
        }
    }
}

void EnemyAdelheid::onInactive() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

void EnemyAdelheid::open_shot() {
    pProg2_->change(PROG2_OPEN);
}

EnemyAdelheid::~EnemyAdelheid() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
    GGAF_DELETE(pProg2_);
}



#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemySappho::EnemySappho(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Sappho", STATUS(EnemySappho)) {
    _class_name = "EnemySappho";
    _SX=_SY=_SZ=100;
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_MOVE04);
}

void EnemySappho::onCreateModel() {
//    _pModel->setSpecular(5.0, 1.0);
}

void EnemySappho::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemySappho::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
}

void EnemySappho::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    switch (_pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             locate(entry_pos_._X, entry_pos_._Y, entry_pos_._Z);
             _pAFader->setAlpha(0);
             _pKurokoA->setMvVelo(0);
             _pKurokoA->relateMvFaceAng(true);
             _pKurokoA->setMvAngTwd(&hanging_pos_);
             _pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(3));
             UTIL::activateEntryEffectOf(this);
             _pProg->changeNext();
             break;
         }
         case PROG_ENTRY: {
             if (_pProg->getFrameInProgress() == 60) {
                 _pAFader->fadeLinerUntil(1.0, 60);
             }
             if (getAlpha() > 0.5) {
                 setHitAble(true);
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE01: {
             if (_pProg->isJustChanged()) {
                 //�ؗ��|�C���g��GO!
                 velo mv_velo = RR_EnemySappho_MvVelo(_RANK_);
                 coord d = UTIL::getDistance(this, &hanging_pos_);
                 _pKurokoA->slideMvByVD(mv_velo,
                                        RND(-PX_C(0.5),PX_C(0.5)),
                                        d, 0.2, 0.8);
             }
             //�ؗ��|�C���g�܂ňړ���
             if (_pProg->getFrameInProgress() % 32 == 0) {
                 //���傭���傭���@�����߂�
                 _pKurokoA->turnFaceAngTwd(P_MYSHIP, D_ANG(0.5), 0,
                                           TURN_CLOSE_TO, true);
             }
             if (_pKurokoA->isJustFinishSlidingMv()) {
                 _pProg->changeNext();
             }
             //_TRACE_("PROG_MOVE01:"<<_X<<","<<_Y<<","<<_Z<<","<<_pKurokoA->_veloMv<<","<<_pKurokoA->_accMv);
             break;
         }

         case PROG_MOVE02: {
             if (_pProg->isJustChanged()) {
                 //�ړ������ƌ����̘A�g����
                 _pKurokoA->relateMvFaceAng(false);
                 //�ؗ��|�C���g�����A�ӂ�ӂ�C�܂܂ȕ����ֈړ�������
                 _pKurokoA->turnMvAngTwd(_X + RND(-PX_C(100),PX_C(100)),
                                         _Y + RND(-PX_C(100),PX_C(100)),
                                         _Z + RND(-PX_C(100),PX_C(100)),
                                         100, 0, TURN_CLOSE_TO, false);
                 //������莩�@�̕��֌�������
                 _pKurokoA->turnFaceAngTwd(P_MYSHIP,
                                           D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             //�ؗ���
             if (_pProg->getFrameInProgress() % 16 == 0) {
                 //���傭���傭���@�����߂�
                 _pKurokoA->turnFaceAngTwd(P_MYSHIP,
                                           D_ANG(1), 0, TURN_CLOSE_TO, true);
             }

             if (_pProg->getFrameInProgress() == 180) {
                 //���@�̕��Ɍ�������G�e���ˁI
                 int shot_num = RR_EnemySappho_ShotWay(_RANK_); //�e���A�����N�ϓ�
                 velo shot_velo = RR_EnemySappho_ShotMvVelo(_RANK_); //�e���A�����N�ϓ�
                 for (int i = 0; i < shot_num; i++) {
                     GgafDxDrawableActor* pShot = UTIL::activateShotOf(this);
                     if (pShot) {
                         pShot->activateDelay(1+(i*10)); //�΂�����Bactivate �^�C�~���O�㏑���I
                         pShot->_pKurokoA->setRzRyMvAng(_pKurokoA->_angFace[AXIS_Z],
                                                        _pKurokoA->_angFace[AXIS_Y]);
                         pShot->_pKurokoA->setMvVelo(shot_velo);
                         pShot->_pKurokoA->setMvAcce(100);
                     }
                 }
             }
             if (_pProg->getFrameInProgress() == 240) {
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE03: {
             //����Ȃ珀��
             if (_pProg->isJustChanged()) {
                 //������肳��Ȃ�|�C���g�֌�����
                 _pKurokoA->turnMvAngTwd(&leave_pos_,
                                         D_ANG(1), D_ANG(1), TURN_CLOSE_TO, false);
                 _pKurokoA->setMvAcce(10);
             }
             if (_pProg->getFrameInProgress() % 16 == 0) {
                 _pKurokoA->turnFaceAngTwd(P_MYSHIP,
                                           D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             if (!_pKurokoA->isTurningMvAng()) {
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE04: {
             //����Ȃ�`
             if (_pProg->isJustChanged()) {
                 _pKurokoA->turnMvAngTwd(&leave_pos_,
                                         D_ANG(1), 0, TURN_CLOSE_TO, false);
                 _pKurokoA->setMvAcce(100+(_RANK_*200));
             }
             if (_pProg->getFrameInProgress() % 16 == 0) {
                 //���傭���傭���@�����߂�
                 _pKurokoA->turnFaceAngTwd(P_MYSHIP,
                                           D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             break;
         }
         default:
             break;
     }

    _pKurokoA->behave();
    //_pSeTx->behave();
}

void EnemySappho::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemySappho::onHit(GgafActor* prm_pOtherActor) {
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

void EnemySappho::onInactive() {
    sayonara();
}

EnemySappho::~EnemySappho() {
}

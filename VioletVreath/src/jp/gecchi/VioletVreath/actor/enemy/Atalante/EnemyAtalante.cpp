#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAtalante::EnemyAtalante(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Atalante", STATUS(EnemyAtalante)) {
    _class_name = "EnemyAtalante";
    pDepo_Shot_ = NULL;
    _pSeTxer->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_EXPLOSION, "bomb1"        , GgafRepeatSeq::nextVal("CH_bomb1"));     //����
    Z_ok_ = Y_ok_ = false;
    useProgress(10);
}

void EnemyAtalante::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAtalante::initialize() {
    _pKurokoA->relateFaceAngWithMvAng(false); //false�ł��I
    _pKurokoA->setFaceAngVelo(AXIS_X, 5000);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyAtalante::config(
        GgafCore::GgafActorDepository* prm_pDepo_Shot
        ) {
    pDepo_Shot_ = prm_pDepo_Shot;
}

void EnemyAtalante::onActive() {
    _pStatus->reset();
    setHitAble(true);
    Z_ok_ = Y_ok_ = false;
    _pKurokoA->setMvAcce(0);
    _pKurokoA->setMvVelo(4000);
    _pKurokoA->forceMvVeloRange(50000);
    _pProg->set(PROG_INIT);
}

void EnemyAtalante::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;

    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->changeNext();
            break;
        }

        case PROG_MOVE01_1: {
            //������Ƃ��̂܂ܐ^�������i��
            if (_pProg->hasJustChanged()) {
            }
            if (_pProg->getFrameInProgress() > 60) {
                _pProg->changeNext(); //���̓�����
            }
            break;
        }

        case PROG_MOVE01_2: {
            if (_pProg->hasJustChanged()) {
            }
            MyShip* pMyShip = P_MYSHIP;
            if (Z_ok_ == false && pMyShip->_Z - PX_C(10) <= _Z && _Z <= pMyShip->_Z + PX_C(10)) {
                //Z���W������
                Z_ok_ = true;
                _pKurokoA->addMvVelo(2000);
                if (pMyShip->_Y <= _Y) {
                    //�^���֐܂��
                    _pKurokoA->execTurnMvAngSequence(D270ANG, 0,
                                                     D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //�^��֐܂��
                    _pKurokoA->execTurnMvAngSequence(D90ANG, 0,
                                                     D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (Y_ok_ == false && pMyShip->_Y - PX_C(10) <= _Y && _Y <= pMyShip->_Y + PX_C(10)) {
                //Y���W������
                Y_ok_ = true;
                _pKurokoA->addMvVelo(2000);
                if (pMyShip->_Z <= _Z) {
                    //���̎��@�̕����܂��
                    _pKurokoA->execTurnMvAngSequence(0, D90ANG,
                                                     D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //��O�̎��@�̕����܂��
                    _pKurokoA->execTurnMvAngSequence(0, D270ANG,
                                                     D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (_pKurokoA->isRunnigTurnMvAngSequence() == false) {
                if (Y_ok_ && Z_ok_) {
                    _pProg->changeNext(); //���̓�����
                }
                if (_pProg->getFrameInProgress() >= 480) {
                    _pProg->changeNext(); //���̓�����
                }
            }
            break;
        }

        case PROG_MOVE01_3: {
            if (_pProg->hasJustChanged()) {
                //X�������ɓ���
                MyShip* pMyShip = P_MYSHIP;
                if (pMyShip->_X <= _X) {
                    //���֐܂��
                    _pKurokoA->execTurnMvAngSequence(D180ANG, 0,
                                                     D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //�E�֐܂��
                    _pKurokoA->execTurnMvAngSequence(0, 0,
                                                     D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                }
            }
            if (_pKurokoA->isRunnigTurnMvAngSequence() == false) {
                _pProg->changeNext(); //���̓�����
            }
            break;
        }

        case PROG_MOVE01_4: {
            if (_pProg->hasJustChanged()) {
                _pKurokoA->setMvAcce(300);
            }
            break;
        }

    }
    _pKurokoA->behave();

    //_pSeTxer->behave();
}

void EnemyAtalante::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAtalante::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (getActivePartFrame() < 50 && (pOther->getKind() & KIND_CHIKEI)) {
        //�o��50�t���[���ȓ��Ńq�b�g���肪�n�`�Ȃ�Ζ����i�o�����n�`�ɂ��j�󂳂������j
        return;
    }

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //�j��
        setHitAble(false);
        //��������
        UTIL::activateExplosionEffectOf(this);
        _pSeTxer->play3D(SE_EXPLOSION);

//        //���@���Ɍ�����ď��ł̏ꍇ�A
//        if (pOther->getKind() & KIND_MY) {
//            //�A�C�e���o��
//            UTIL::activateItemOf(this);
//        }
        sayonara();
    } else {
        //��j��
        effectFlush(2); //�t���b�V��
    }
}

void EnemyAtalante::onInactive() {
}

EnemyAtalante::~EnemyAtalante() {
}



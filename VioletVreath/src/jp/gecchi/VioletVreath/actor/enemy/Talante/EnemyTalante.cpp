#include "stdafx.h"
#include "EnemyTalante.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyTalante::EnemyTalante(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Talante", STATUS(EnemyTalante)) {
    _class_name = "EnemyTalante";
    pDepo_Shot_ = nullptr;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
    Z_ok_ = Y_ok_ = false;
    useProgress(_BANPEI_-1);
}

void EnemyTalante::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyTalante::initialize() {
    _pKurokoA->relateFaceWithMvAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, 5000);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyTalante::config(
        GgafCore::GgafActorDepository* prm_pDepo_Shot
        ) {
    pDepo_Shot_ = prm_pDepo_Shot;
}

void EnemyTalante::onActive() {
    _pStatus->reset();
    setHitAble(true);
    Z_ok_ = Y_ok_ = false;
    _pKurokoA->setMvAcce(0);
    _pKurokoA->setMvVelo(4000);
    _pKurokoA->forceMvVeloRange(50000);
    _pProg->reset(PROG_INIT);
}

void EnemyTalante::processBehavior() {
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
            if (_pProg->isJustChanged()) {
            }
            if (_pProg->getFrameInProgress() > 60) {
                _pProg->changeNext(); //���̓�����
            }
            break;
        }

        case PROG_MOVE01_2: {
            if (_pProg->isJustChanged()) {
            }
            if (Z_ok_ == false && pMyShip->_z - PX_C(5) <= _z && _z <= pMyShip->_z + PX_C(5)) {
                //Z���W������
                Z_ok_ = true;
                _pKurokoA->addMvVelo(2000);
                if (pMyShip->_y <= _y) {
                    //�^���֐܂��
                    _pKurokoA->turnRzRyMvAngTo(D270ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //�^��֐܂��
                    _pKurokoA->turnRzRyMvAngTo(D90ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (Y_ok_ == false && pMyShip->_y - PX_C(5) <= _y && _y <= pMyShip->_y + PX_C(5)) {
                //Y���W������
                Y_ok_ = true;
                _pKurokoA->addMvVelo(2000);
                if (pMyShip->_z <= _z) {
                    //���̎��@�̕����܂��
                    _pKurokoA->turnRzRyMvAngTo(D0ANG, D90ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //��O�̎��@�̕����܂��
                    _pKurokoA->turnRzRyMvAngTo(D0ANG, D270ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (_pKurokoA->isTurningMvAng() == false) {
                if (Y_ok_ && Z_ok_) {
                    //Z���WY���W�������玟�̓�����
                    _pProg->changeNext();
                } else if (_pProg->getFrameInProgress() >= 480) {
                    //Z���WY���W���킸�Ƃ���莞�ԂŎ��̓�����
                    _pProg->changeNext();
                }
            }
            break;
        }

        case PROG_MOVE01_3: {
            if (_pProg->isJustChanged()) {
                //X�������ɓ���
                if (pMyShip->_x <= _x) {
                    //���֐܂��
                    _pKurokoA->turnRzRyMvAngTo(D180ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //�E�֐܂��
                    _pKurokoA->turnRzRyMvAngTo(D0ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }
            if (_pKurokoA->isTurningMvAng() == false) {
                _pProg->changeNext(); //���̓�����
            }
            break;
        }

        case PROG_MOVE01_4: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->setMvAcce(300);//�����J�n
            }
            break;
        }

    }
    _pKurokoA->behave();

    //_pSeTx->behave();
}

void EnemyTalante::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyTalante::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (getActiveFrame() < 30 && (pOther->getKind() & KIND_CHIKEI)) {
         //�o��30�t���[���ȓ��Ńq�b�g���肪�n�`�Ȃ�Ζ����i�o�����n�`�ɂ��j�󂳂������j
         return;
    }

    bool was_destroyed = UTIL::proceedEnemyHit(this, pOther);
    if (was_destroyed) {
        //�j��
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //��j��
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyTalante::onInactive() {
}

EnemyTalante::~EnemyTalante() {
}



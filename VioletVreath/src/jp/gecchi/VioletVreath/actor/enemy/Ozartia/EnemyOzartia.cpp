#include "stdafx.h"
#include "EnemyOzartia.h"

#include "EnemyOzartiaShot01.h"
#include "EnemyOzartiaLaserChip01.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define D_MOVE (PX_C(500))
#define ASOBI (RND(-30,30))
EnemyOzartia::EnemyOzartia(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Ozartia", STATUS(EnemyOzartia)) {
    _class_name = "EnemyOzartia";
    pAFader_ = NEW GgafDxAlphaFader(this);
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI1_-1);
    pProg2_ = createProgress(PROG2_BANPEI-1);
    is_hit_ = false;
    _sx=_sy=_sz=100;

//    //�o���A�u���b�N
//    pDepo_Shot01_ = NEW GgafActorDepository("Depo_OzartiaBlock");
//    for (int i = 0; i < 9; i++) {
//        std::string name = "EnemyOzartiaShot01["+XTOS(i)+"]";
//        pDepo_Shot01_->put(NEW EnemyOzartiaShot01(name.c_str()));
//        Sleep(1);
//    }
//    addSubGroup(pDepo_Shot01_);
//
//    pDepo_Shot02_ = NEW LaserChipDepository("MyRotLaser");
//    pDepo_Shot02_->config(60, 1, nullptr); //Halia�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
//    EnemyOzartiaLaserChip01* pChip;
//    for (int i = 0; i < 65; i++) { //���[�U�[�X�g�b�N
//        std::string name = "EnemyOzartiaLaserChip01["+XTOS(i)+"]";
//        pChip = NEW EnemyOzartiaLaserChip01(name.c_str());
//        pChip->setSource(this); //�ʒu��������
//        pDepo_Shot02_->put(pChip);
//    }
//    addSubGroup(pDepo_Shot02_);
    faceang_to_ship_ = false;
    effectBlendOne(); //���Z����
}

void EnemyOzartia::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyOzartia::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
    _pKuroko->relateFaceWithMvAng(false); //�Ɨ�
    _pKuroko->forceMvVeloRange(PX_C(1), PX_C(8));
    setHitAble(false);
}

void EnemyOzartia::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG1_INIT);
    pProg2_->reset(PROG2_WAIT);
    faceang_to_ship_ = false;
}

void EnemyOzartia::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    MyShip* pMyShip = P_MYSHIP;
    //�{�̈ړ��n�̏��� �������� --->
    switch (_pProg->get()) {
        case PROG1_INIT: {
            setHitAble(false);
            pAFader_->setAlpha(0);
            UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            break;
        }
        case PROG1_ENTRY: {
            if (_pProg->isJustChanged()) {
                pAFader_->fadeLinerUntil(1.0, 30);
            }
            if (_pProg->getFrameInProgress() == 15) {
                setHitAble(true);
                _pProg->change(PROG1_STAY);
            }
            break;
        }
        case PROG1_STAY: {
            if (_pProg->isJustChanged()) {
                faceang_to_ship_ = true;
                _pKuroko->setMvAcce(0);
                _pKuroko->turnMvAngTwd(pMyShip, D_ANG(1), 0, TURN_ANTICLOSE_TO, false);
            }
            if (is_hit_ || _pProg->getFrameInProgress() == 5*60) {
                //�q�b�g���邩�A���΂炭�{�[���Ƃ��Ă�ƈړ��J�n
                _pProg->changeProbab(18, PROG1_MV_POS0,
                                     16, PROG1_MV_POS1,
                                     16, PROG1_MV_POS2,
                                     16, PROG1_MV_POS3,
                                     16, PROG1_MV_POS4,
                                     18, PROG1_MV_POS5 );
            }
            break;
        }
        //////////// �ړ��挈�� ////////////
        case PROG1_MV_POS0: {
            //���@�̐��ʕt�߂�
            posMvTarget_.set(pMyShip->_x + D_MOVE + ASOBI,
                             pMyShip->_y          + ASOBI,
                             pMyShip->_z          + ASOBI );
            _pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS1: {
            //���@�̏�
            posMvTarget_.set(pMyShip->_x            + ASOBI,
                             pMyShip->_y + D_MOVE/2 + ASOBI,
                             pMyShip->_z            + ASOBI );
            _pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS2: {
            //���@�̉E
            posMvTarget_.set(pMyShip->_x          + ASOBI,
                             pMyShip->_y          + ASOBI,
                             pMyShip->_z - D_MOVE + ASOBI );
            _pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS3: {
            //���@�̉�
            posMvTarget_.set(pMyShip->_x            + ASOBI,
                             pMyShip->_y - D_MOVE/2 + ASOBI,
                             pMyShip->_z            + ASOBI );
            _pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS4: {
            //���@�̍�
            posMvTarget_.set(pMyShip->_x          + ASOBI,
                             pMyShip->_y          + ASOBI,
                             pMyShip->_z + D_MOVE + ASOBI );
            _pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS5: {
            //���@�̌��
            posMvTarget_.set(pMyShip->_x - D_MOVE + ASOBI,
                             pMyShip->_y          + ASOBI,
                             pMyShip->_z          + ASOBI );
            _pProg->change(PROG1_MOVE_START);
            break;
        }
        //////////// �ړ��J�n ////////////
        case PROG1_MOVE_START: {
            if (_pProg->isJustChanged()) {
                //�^�[��
                faceang_to_ship_ = false;
                _pKuroko->setMvVeloBottom();
                _pKuroko->setMvAcce(10); //�����ɉ���
                _pKuroko->turnMvAngTwd(&posMvTarget_, D_ANG(2), 0, TURN_CLOSE_TO, false);
            }
            if (!_pKuroko->isTurningMvAng()) {
                //�^�[��������ړ���
                _pProg->change(PROG1_MOVING);
            }
            break;
        }
        case PROG1_MOVING: {
            if (_pProg->isJustChanged()) {
                //���@�̐��ʕt�߂փX�C�[���ƍs���܂�
                _pKuroko->helperA()->slideMvByVd(_pKuroko->getMvVeloTop(), UTIL::getDistance(this, &posMvTarget_),
                                       0.3f, 0.7f, _pKuroko->getMvVeloBottom(), true);
            }
            if (!_pKuroko->helperA()->isSlidingMv()) {
                //����������I��
                _pProg->change(PROG1_STAY);
            }
            break;
        }

        case PROG1_LEAVE: {
            if (_pProg->isJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAFader_->fadeLinerUntil(0.0, 30);
            }
            if (_pProg->getFrameInProgress() == 60) {
                sayonara();
                _pProg->changeNothing(); //�����܂��I
            }
            break;
        }
        default :
            break;
    }
    //<-- �{�̈ړ��n�̏��� �����܂�

    //////////////////////////////////////////////////////////////////////

    //�V���b�g���ˌn���� �������� --->
    switch (pProg2_->get()) {
        case PROG2_WAIT: {
            if (_pProg->isJustChanged()) {
            }
            break;
        }
        case PROG2_SHOT01_01: {
            if (_pProg->isJustChanged()) {
                faceang_to_ship_ = true;
                _pMorpher->morphLinerUntil(MPH_SHOT01, 1.0, 120);
            }
            if (_pProg->getFrameInProgress() == 120) {
                _pProg->change(PROG2_SHOT01_02);
            }
            break;
        }
        default :
            break;
    }
    pProg2_->update();
    //<-- �V���b�g���ˌn���� �����܂�

    if (faceang_to_ship_) {
        //���@�������[�h
        if (!_pKuroko->isTurningFaceAng()) {
            _pKuroko->turnFaceAngTwd(pMyShip, D_ANG(5), 0, TURN_CLOSE_TO, false);
        }
    } else {
        //�i�s�����������[�h
        if (!_pKuroko->isTurningFaceAng()) {
            _pKuroko->turnRzRyFaceAngTo(_pKuroko->_angRzMv,_pKuroko->_angRyMv,
                                          D_ANG(2), 0, TURN_CLOSE_TO, false);
        }
    }
    pAFader_->behave();
    _pKuroko->behave();
    is_hit_ = false;
}

void EnemyOzartia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyOzartia::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //��j��
    }
    is_hit_ = true;
}

void EnemyOzartia::onInactive() {
    sayonara();
}

EnemyOzartia::~EnemyOzartia() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETE(pProg2_);
}


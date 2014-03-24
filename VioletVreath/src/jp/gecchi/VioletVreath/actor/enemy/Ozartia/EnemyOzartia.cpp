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
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
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
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyOzartia::initialize() {
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliAAB_Cube(0, 40000);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->relateFaceWithMvAng(false); //�Ɨ�
    pKuroko->forceMvVeloRange(PX_C(1), PX_C(8));
    setHitAble(false);
}

void EnemyOzartia::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG1_INIT);
    pProg2_->reset(PROG2_WAIT);
    faceang_to_ship_ = false;
}

void EnemyOzartia::processBehavior() {
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);

    MyShip* pMyShip = P_MYSHIP;
    //�{�̈ړ��n�̏��� �������� --->
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG1_INIT: {
            setHitAble(false);
            setAlpha(0);
            UTIL::activateEntryEffectOf(this);
            pProg->changeNext();
            break;
        }
        case PROG1_ENTRY: {
            if (pProg->isJustChanged()) {
                pAFader_->transitionLinerUntil(1.0, 30);
            }
            if (pProg->getFrameInProgress() == 15) {
                setHitAble(true);
                pProg->change(PROG1_STAY);
            }
            break;
        }
        case PROG1_STAY: {
            if (pProg->isJustChanged()) {
                faceang_to_ship_ = true;
                pKuroko->setMvAcce(0);
                pKuroko->turnMvAngTwd(pMyShip, D_ANG(1), 0, TURN_ANTICLOSE_TO, false);
            }
            if (is_hit_ || pProg->getFrameInProgress() == 5*60) {
                //�q�b�g���邩�A���΂炭�{�[���Ƃ��Ă�ƈړ��J�n
                pProg->changeProbab(18, PROG1_MV_POS0,
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
            pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS1: {
            //���@�̏�
            posMvTarget_.set(pMyShip->_x            + ASOBI,
                             pMyShip->_y + D_MOVE/2 + ASOBI,
                             pMyShip->_z            + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS2: {
            //���@�̉E
            posMvTarget_.set(pMyShip->_x          + ASOBI,
                             pMyShip->_y          + ASOBI,
                             pMyShip->_z - D_MOVE + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS3: {
            //���@�̉�
            posMvTarget_.set(pMyShip->_x            + ASOBI,
                             pMyShip->_y - D_MOVE/2 + ASOBI,
                             pMyShip->_z            + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS4: {
            //���@�̍�
            posMvTarget_.set(pMyShip->_x          + ASOBI,
                             pMyShip->_y          + ASOBI,
                             pMyShip->_z + D_MOVE + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS5: {
            //���@�̌��
            posMvTarget_.set(pMyShip->_x - D_MOVE + ASOBI,
                             pMyShip->_y          + ASOBI,
                             pMyShip->_z          + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        //////////// �ړ��J�n ////////////
        case PROG1_MOVE_START: {
            if (pProg->isJustChanged()) {
                //�^�[��
                faceang_to_ship_ = false;
                pKuroko->setMvVeloBottom();
                pKuroko->setMvAcce(10); //�����ɉ���
                pKuroko->turnMvAngTwd(&posMvTarget_, D_ANG(2), 0, TURN_CLOSE_TO, false);
            }
            if (!pKuroko->isTurningMvAng()) {
                //�^�[��������ړ���
                pProg->change(PROG1_MOVING);
            }
            break;
        }
        case PROG1_MOVING: {
            if (pProg->isJustChanged()) {
                //���@�̐��ʕt�߂փX�C�[���ƍs���܂�
                pKuroko->hlprA()->slideMvByVd(pKuroko->getMvVeloTop(), UTIL::getDistance(this, &posMvTarget_),
                                       0.3f, 0.7f, pKuroko->getMvVeloBottom(), true);
            }
            if (!pKuroko->hlprA()->isSlidingMv()) {
                //����������I��
                pProg->change(PROG1_STAY);
            }
            break;
        }

        case PROG1_LEAVE: {
            if (pProg->isJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAFader_->transitionLinerUntil(0.0, 30);
            }
            if (pProg->getFrameInProgress() == 60) {
                sayonara();
                pProg->changeNothing(); //�����܂��I
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
            if (pProg->isJustChanged()) {
            }
            break;
        }
        case PROG2_SHOT01_01: {
            if (pProg->isJustChanged()) {
                faceang_to_ship_ = true;
                getMorpher()->transitionLinerUntil(MPH_SHOT01, 1.0, 120);
            }
            if (pProg->getFrameInProgress() == 120) {
                pProg->change(PROG2_SHOT01_02);
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
        if (!pKuroko->isTurningFaceAng()) {
            pKuroko->turnFaceAngTwd(pMyShip, D_ANG(5), 0, TURN_CLOSE_TO, false);
        }
    } else {
        //�i�s�����������[�h
        if (!pKuroko->isTurningFaceAng()) {
            pKuroko->turnRzRyFaceAngTo(pKuroko->_angRzMv,pKuroko->_angRyMv,
                                          D_ANG(2), 0, TURN_CLOSE_TO, false);
        }
    }
    pAFader_->behave();
    pKuroko->behave();
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
        getSeTx()->play3D(SE_EXPLOSION);
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


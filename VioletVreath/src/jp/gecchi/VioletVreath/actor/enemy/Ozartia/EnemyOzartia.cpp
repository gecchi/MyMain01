#include "stdafx.h"
#include "EnemyOzartia.h"

#include "EnemyOzartiaShot01.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "EnemyOzartiaLaserChip01.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyOzartia::EnemyOzartia(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Ozartia", STATUS(EnemyOzartia)) {
    _class_name = "EnemyOzartia";
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(_BANPEI1_-1);
    pProg2_ = createProgress(_BANPEI2_-1);
    is_hit_ = false;

    //�o���A�u���b�N
    pDepo_Shot01_ = NEW GgafActorDepository("Depo_OzartiaBlock");
    for (int i = 0; i < 9; i++) {
        std::string name = "EnemyOzartiaShot01["+XTOS(i)+"]";
        pDepo_Shot01_->put(NEW EnemyOzartiaShot01(name.c_str()));
        Sleep(1);
    }
    addSubGroup(pDepo_Shot01_);

    pDepo_Shot02_ = NEW LaserChipDepository("MyRotLaser");
    pDepo_Shot02_->config(60, 1, nullptr); //Halia�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
    EnemyOzartiaLaserChip01* pChip;
    for (int i = 0; i < 65; i++) { //���[�U�[�X�g�b�N
        std::string name = "EnemyOzartiaLaserChip01["+XTOS(i)+"]";
        pChip = NEW EnemyOzartiaLaserChip01(name.c_str());
        pChip->setSource(this); //�ʒu��������
        pDepo_Shot02_->put(pChip);
    }
    addSubGroup(pDepo_Shot02_);
}

void EnemyOzartia::onCreateModel() {
//    _pModel->setSpecular(5.0, 1.0);
}

void EnemyOzartia::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
    _pKurokoA->relateMvFaceAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, 2000);
    _pKurokoA->forceMvVeloRange(PX_C(15));
    setHitAble(false);
}

void EnemyOzartia::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG1_INIT);
    pProg2_->reset(PROG2_WAIT);
}

void EnemyOzartia::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //�{�̈ړ��n�̏��� �������� --->
    switch (_pProg->get()) {
        case PROG1_INIT: {
            setHitAble(false);
            _pAFader->setAlpha(0);
            UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            break;
        }
        case PROG1_ENTRY: {
            if (_pProg->isJustChanged()) {
                _pAFader->fadeLinerUntil(1.0, 30);
            }
            if (_pProg->getFrameInProgress() == 15) {
                setHitAble(true);
                _pProg->change(PROG1_STAY);
            }
            break;
        }
        case PROG1_STAY: {
            if (_pProg->isJustChanged()) {
            }
            if (is_hit_ || _pProg->getFrameInProgress() == 10*60) {
                //�q�b�g���邩�A���΂炭�{�[���Ƃ��Ă�ƈړ��J�n
                _pProg->changeProbability(25, PROG1_MOVE01,
                                          25, PROG1_MOVE02,
                                          25, PROG1_MOVE03,
                                          25, PROG1_MOVE04 );
            }
            break;
        }
        case PROG1_MOVE01: {
            if (_pProg->isJustChanged()) {
            }
            break;
        }

        case PROG1_LEAVE: {
            if (_pProg->isJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                _pAFader->fadeLinerUntil(0.0, 30);
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

    //�V���b�g���ˌn���� �������� --->
    switch (pProg2_->get()) {
        case PROG2_WAIT: {
            if (_pProg->isJustChanged()) {
            }
            break;
        }
        default :
            break;
    }
    pProg2_->update();
    //<-- �V���b�g���ˌn���� �����܂�

    _pAFader->behave();
    _pKurokoA->behave();
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
}



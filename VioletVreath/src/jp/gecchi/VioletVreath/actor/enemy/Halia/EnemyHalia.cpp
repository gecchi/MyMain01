#include "stdafx.h"
#include "EnemyHalia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/common/laserchip/EnemyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHalia::EnemyHalia(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Halia", STATUS(EnemyHalia)) {
        //CubeMapMorphMeshActor(prm_name, "1/HaliaCM", STATUS(EnemyHalia)) {

    _class_name = "EnemyHalia";
    veloTopMv_ = 20000;
    iMovePatternNo_ = 0;
    pKurokoLeader_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;

    pLaserChipDepo_ = NEW LaserChipDepository("MyRotLaser");
    pLaserChipDepo_->config(60, 1, nullptr); //Halia�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
    EnemyStraightLaserChip001* pChip;
    for (int i = 0; i < 65; i++) { //���[�U�[�X�g�b�N
        std::stringstream name;
        name <<  "EnemyStraightLaserChip001[" << i << "]";
        pChip = NEW EnemyStraightLaserChip001(name.str().c_str());
        pChip->setSource(this); //�ʒu��������
        pChip->inactivateImmed();
        pLaserChipDepo_->addSubLast(pChip);
    }
    addSubGroup(pLaserChipDepo_);

    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_UNDAMAGED, "WAVE_ENEMY_UNDAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    _pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    useProgress(PROG_CLOSE);
    //�����J����Z�ʒu
    dZ_camera_init_ = -1 * P_CAM->_cameraZ_org * LEN_UNIT * PX_UNIT;
}

void EnemyHalia::onCreateModel() {
    _pModel->_pTexBlinker->setBlinkableRange(0.9, 0.1, 1.0);
    _pModel->_pTexBlinker->setPower(0.1);
    _pModel->_pTexBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyHalia::initialize() {
    setHitAble(true);
    _pKurokoA->relateMvFaceAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 90000);
    setScaleR(0.3);
}

void EnemyHalia::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);
    _pKurokoA->setFaceAngVelo(AXIS_X, 1000);
    _pKurokoA->slideMvByVD(veloTopMv_, 1000,
                                         MyShip::lim_X_front_-_X, 0.4, 0.6);
    _pProg->reset(PROG_MOVE);
    iMovePatternNo_ = 0; //�s���p�^�[�����Z�b�g
}

void EnemyHalia::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    switch (_pProg->get()) {
        case PROG_MOVE: {
            if (!_pKurokoA->isSlidingMv()) {
                _pMorpher->morphAcceStep(1, 1.0, 0.0, 0.0004); //�J�� 0.0004 �J������
                _pKurokoA->turnMvAngTwd(P_MYSHIP,
                                        0, 100,
                                        TURN_CLOSE_TO, false);
                _pProg->changeNext();
            }
            break;
        }
        case PROG_TURN_OPEN: {
            if (_pProg->getFrameInProgress() > 120) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_FIRE_BEGIN: {
            if ( _X - P_MYSHIP->_X > -dZ_camera_init_) {
                _pProg->change(PROG_IN_FIRE);
            } else {
                //�w�ォ��͌����Ȃ��B
                _pProg->change(PROG_CLOSE);
            }
            break;
        }
        case PROG_IN_FIRE: {
            if (getActiveFrame() % 16 == 0) {
                _pKurokoA->turnMvAngTwd(P_MYSHIP,
                                        10, 0,
                                        TURN_CLOSE_TO, false);
            }
            EnemyStraightLaserChip001* pLaser = (EnemyStraightLaserChip001*)pLaserChipDepo_->dispatch();
            if (pLaser) {
                if (pLaser->_pChip_front == nullptr) {
                    _pSeTx->play3D(SE_FIRE);
                    _pKurokoA->setFaceAngVelo(AXIS_X, 5000);//���˒��͑�����]
                }
            } else {
                _pProg->change(PROG_CLOSE);
            }
            break;
        }
        case PROG_CLOSE: {
            //�P�T�C�N�����[�U�[�ł��؂���
            _pMorpher->morphLinerUntil(1, 0.0, 60); //����
            _pKurokoA->slideMvByVD(veloTopMv_, 1000, 1500000, 0.4, 0.6);
//            _pKurokoA->slideMvByDT(200, 1000000, 180);
            _pKurokoA->setFaceAngVelo(AXIS_X, 1000);
            _pProg->change(PROG_MOVE);
            break;
        }

        default:
            break;
    }

    _pKurokoA->behave();
    _pMorpher->behave();
    _pSeTx->behave();
}

void EnemyHalia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyHalia::onHit(GgafActor* prm_pOtherActor) {
    if (_pMorpher->_weight[1] > 0.1) { //�����󂢂Ă���
        bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
        if (was_destroyed) {
            //�j��
            _pSeTx->play3D(SE_EXPLOSION);
        } else {
            //��j��
            _pSeTx->play3D(SE_DAMAGED);
        }
    } else {
    	_pSeTx->play3D(SE_UNDAMAGED);
    }
}

void EnemyHalia::onInactive() {
    //sayonara();
}

EnemyHalia::~EnemyHalia() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

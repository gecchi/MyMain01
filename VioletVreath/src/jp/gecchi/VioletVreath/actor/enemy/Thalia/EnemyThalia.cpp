#include "stdafx.h"
#include "EnemyThalia.h"

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

EnemyThalia::EnemyThalia(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Thalia", STATUS(EnemyThalia)) {
        //CubeMapMorphMeshActor(prm_name, "1/ThaliaCM", STATUS(EnemyThalia)) {

    _class_name = "EnemyThalia";
    veloTopMv_ = 20000;
    iMovePatternNo_ = 0;
    pKurokoLeader_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;

    pLaserChipDepo_ = NEW LaserChipDepository("MyRotLaser");
    pLaserChipDepo_->config(60, 1, nullptr); //Thaliaは弾切れフレームを1にしないとパクパクしちゃいます。
    EnemyStraightLaserChip001* pChip;
    for (int i = 0; i < 65; i++) { //レーザーストック
        std::stringstream name;
        name <<  "EnemyStraightLaserChip001[" << i << "]";
        pChip = NEW EnemyStraightLaserChip001(name.str().c_str());
        pChip->setSource(this); //位置向き同期
        pChip->inactivateImmed();
        pLaserChipDepo_->addSubLast(pChip);
    }
    addSubGroup(pLaserChipDepo_);

    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    _pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    useProgress(PROG_CLOSE);
    //初期カメラZ位置
    dZ_camera_init_ = -1 * P_CAM->_cameraZ_org * LEN_UNIT * PX_UNIT;
}

void EnemyThalia::onCreateModel() {
    _pModel->_pTexBlinker->setBlinkableRange(0.9, 0.1, 1.0);
    _pModel->_pTexBlinker->setPower(0.1);
    _pModel->_pTexBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyThalia::initialize() {
    setHitAble(true);
    _pKurokoA->relateMvFaceAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 90000);
    setScaleR(0.3);
}

void EnemyThalia::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);
    _pKurokoA->setFaceAngVelo(AXIS_X, 1000);
    _pKurokoA->slideMvByVD(veloTopMv_, 1000,
                                         MyShip::lim_front_-_X, 0.4, 0.6);
    _pProg->reset(PROG_MOVE);
    iMovePatternNo_ = 0; //行動パターンリセット
}

void EnemyThalia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    switch (_pProg->get()) {
        case PROG_MOVE: {
            if (!_pKurokoA->isSlidingMv()) {
                _pMorpher->morphAcceStep(1, 1.0, 0.0, 0.0004); //開く 0.0004 開く速さ
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
                //背後からは撃たない。
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
                    _pKurokoA->setFaceAngVelo(AXIS_X, 5000);//発射中は速い回転
                }
            } else {
                _pProg->change(PROG_CLOSE);
            }
            break;
        }
        case PROG_CLOSE: {
            //１サイクルレーザー打ち切った
            _pMorpher->morphLinerUntil(1, 0.0, 60); //閉じる
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

void EnemyThalia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyThalia::onHit(GgafActor* prm_pOtherActor) {
    if (_pProg->get() == PROG_MOVE) {
        bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
        if (was_destroyed) {
            //破壊時
            _pSeTx->play3D(SE_EXPLOSION);
        } else {
            //非破壊時
            _pSeTx->play3D(SE_DAMAGED);
        }
    }

}

void EnemyThalia::onInactive() {
    //sayonara();
}

EnemyThalia::~EnemyThalia() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

#include "stdafx.h"
#include "EnemyRatislaviaEye.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EffectRatislaviaEye001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislavia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislaviaEyeStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyRatislaviaEye::EnemyRatislaviaEye(const char* prm_name, EnemyRatislavia* prm_pRatislavia) :
        DefaultMorphMeshActor(prm_name, "1/RatislaviaEye", STATUS(EnemyRatislaviaEye)) {
        //CubeMapMorphMeshActor(prm_name, "1/HaliaCM", STATUS(EnemyRatislaviaEye)) {

    _class_name = "EnemyRatislaviaEye";
    setScaleR(0.3*10);
    pRatislavia_ = prm_pRatislavia;
    positionAs(pRatislavia_);

    pLaserChipDepo_ = NEW LaserChipDepository("DepoLaserChip");
    pLaserChipDepo_->config(60, 1, nullptr); //Haliaは弾切れフレームを1にしないとパクパクしちゃいます。
    EnemyRatislaviaEyeStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //レーザーストック
        std::string name = "LaserChip("+ XTOS(i) + ")";
        pChip = NEW EnemyRatislaviaEyeStraightLaserChip001(name.c_str());
        pChip->setSource(this); //位置向き同期
        pLaserChipDepo_->put(pChip);
    }
    addSubGroup(pLaserChipDepo_);

    pEffect_ = NEW EffectRatislaviaEye001("EffectRatislaviaEye001");
    pEffect_->inactivate();
    addSubGroup(pEffect_);

    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
    _pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");
    useProgress(PROG_BANPEI);

    is_wake_ = false;
}

void EnemyRatislaviaEye::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
    _pModel->setBlinkPower(0.1, 0.9);
    _pModel->_pTexBlinker->forceRange(0.1, 1.0);
    _pModel->_pTexBlinker->beat(120, 60, 0, 60, -1);
}

void EnemyRatislaviaEye::initialize() {
    setHitAble(true);
    _pKuroko->relateFaceWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 200000);
}

void EnemyRatislaviaEye::onActive() {
    _pStatus->reset();
    setWeight(0, 1.0);
    setWeight(1, 0.0);
    _pProg->reset(PROG_MOVE);
    positionAs(pRatislavia_);
    setFaceAngAs(pRatislavia_);
    _pKuroko->setRzRyMvAngVelo(pRatislavia_->_pKuroko->_angveloFace[AXIS_Z],
                                pRatislavia_->_pKuroko->_angveloFace[AXIS_Y]);
}

void EnemyRatislaviaEye::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    positionAs(pRatislavia_);
    switch (_pProg->get()) {
        case PROG_MOVE: {
            break;
        }
        case PROG_OPEN: {
            if (_pProg->isJustChanged()) {
                _pMorpher->transitionLinerUntil(1, 1.0, 180); //開く
            }
            if (_pProg->getFrameInProgress() > 240) {
                _pProg->changeNext();
            }
            _pKuroko->takeoverMvFrom(pRatislavia_->_pKuroko);
            _pKuroko->setRzRyMvAngVelo(pRatislavia_->_pKuroko->_angveloFace[AXIS_Z],
                                        pRatislavia_->_pKuroko->_angveloFace[AXIS_Y]);
            break;
        }

        case PROG_TURN: {
            if (_pProg->isJustChanged()) {
                _pKuroko->turnMvAngTwd(P_MYSHIP,
                                        D_ANG(1), 0, TURN_CLOSE_TO, false);
            }
            if (_pProg->getFrameInProgress() > 240) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE_BEGIN: {
            if (_pProg->isJustChanged()) {
                //_pKuroko->turnMvAngTwd(P_MYSHIP, D_ANG(1), 0, TURN_ANTICLOSE_TO, false);
                pEffect_->activate();
            }
            pEffect_->positionAs(this);
            if (pEffect_->onChangeToInactive()) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_IN_FIRE: {
            if (_pProg->isJustChanged()) {
                _pKuroko->turnMvAngTwd(P_MYSHIP,
                                        10, 0, TURN_CLOSE_TO, false);
            }
            LaserChip* pChip = pLaserChipDepo_->dispatch();
            if (pChip) {
                if (pChip->_pChip_front == nullptr) {
                    _pSeTx->play3D(SE_FIRE);
                }
            } else {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_FIRE_END: {
            if (_pProg->isJustChanged()) {
                _pMorpher->transitionLinerUntil(1, 0.0, 180); //閉じる
                _pKuroko->setRzRyMvAngVelo(pRatislavia_->_pKuroko->_angveloFace[AXIS_Z],
                                            pRatislavia_->_pKuroko->_angveloFace[AXIS_Y]);
            }
            //硬直
            if (_pProg->getFrameInProgress() >= 300) {
                _pProg->change(PROG_OPEN);
            }
            break;
        }

        default:
            break;
    }

    _pKuroko->behave();
    _pMorpher->behave();
    _pSeTx->behave();
}

void EnemyRatislaviaEye::processJudgement() {
//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void EnemyRatislaviaEye::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
        _TRACE_("EnemyRatislaviaEye::onHit() 上位になげるっす throwEventUpperTree(RATISLAVIA_EXPLOSION)");
        throwEventUpperTree(RATISLAVIA_EXPLOSION); //親のEnemyRatislaviaを破壊するイベントを投げる
    } else {
        //非破壊時
        _pSeTx->play3D(SE_DAMAGED);
        pRatislavia_->effectFlush(2);
    }
}

void EnemyRatislaviaEye::onInactive() {
    //sayonara();
}

void EnemyRatislaviaEye::wake() {
    is_wake_ = true;
    _pProg->change(PROG_OPEN);
}

EnemyRatislaviaEye::~EnemyRatislaviaEye() {
}

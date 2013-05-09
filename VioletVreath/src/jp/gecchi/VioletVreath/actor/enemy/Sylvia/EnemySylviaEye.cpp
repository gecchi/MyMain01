#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemySylviaEye::EnemySylviaEye(const char* prm_name, EnemySylvia* prm_pSylvia) :
        DefaultMorphMeshActor(prm_name, "1/SylviaEye", STATUS(EnemySylviaEye)) {
        //CubeMapMorphMeshActor(prm_name, "1/ThaliaCM", STATUS(EnemySylviaEye)) {

    _class_name = "EnemySylviaEye";
    setScaleR(0.3*10);
    pSylvia_ = prm_pSylvia;
    locateAs(pSylvia_);

    pLaserChipDepo_ = NEW LaserChipDepository("DepoLaserChip");
    pLaserChipDepo_->config(60, 1, nullptr); //Thaliaは弾切れフレームを1にしないとパクパクしちゃいます。
    EnemySylviaEyeStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //レーザーストック
        std::string name = "LaserChip("+ XTOS(i) + ")";
        pChip = NEW EnemySylviaEyeStraightLaserChip001(name.c_str());
        pChip->setSource(this); //位置向き同期
        pLaserChipDepo_->addSubLast(pChip);
    }
    addSubGroup(pLaserChipDepo_);

    pEffect_ = NEW EffectSylviaEye001("EffectSylviaEye001");
    pEffect_->inactivateImmed();
    addSubGroup(pEffect_);

    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
    _pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");
    useProgress(PROG_CLOSE);

    is_wake_ = false;
}

void EnemySylviaEye::onCreateModel() {
    _pModel->_pTexBlinker->setBlinkableRange(0.9, 0.1, 1.0);
    _pModel->_pTexBlinker->setPower(0.1);
    _pModel->_pTexBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemySylviaEye::initialize() {
    setHitAble(true);
    _pKurokoA->relateMvFaceAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 200000);
}

void EnemySylviaEye::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);
    _pProg->reset(PROG_MOVE);
    locateAs(pSylvia_);
    rotateAs(pSylvia_);
    _pKurokoA->setRzRyMvAngVelo(pSylvia_->_pKurokoA->_angveloFace[AXIS_Z],
                                pSylvia_->_pKurokoA->_angveloFace[AXIS_Y]);
}

void EnemySylviaEye::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    locateAs(pSylvia_);
    switch (_pProg->get()) {
        case PROG_MOVE: {
            break;
        }
        case PROG_OPEN: {
            if (_pProg->isJustChanged()) {
                _pMorpher->morphLinerUntil(1, 1.0, 180); //開く
            }
            if (_pProg->getFrameInProgress() > 240) {
                _pProg->changeNext();
            }
            _pKurokoA->followMvFrom(pSylvia_->_pKurokoA);
            _pKurokoA->setRzRyMvAngVelo(pSylvia_->_pKurokoA->_angveloFace[AXIS_Z],
                                        pSylvia_->_pKurokoA->_angveloFace[AXIS_Y]);
            break;
        }

        case PROG_TURN: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->turnMvAngTwd(P_MYSHIP,
                                        D_ANG(1), 0, TURN_CLOSE_TO, false);
            }
            if (_pProg->getFrameInProgress() > 240) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE_BEGIN: {
            if (_pProg->isJustChanged()) {
                //_pKurokoA->turnMvAngTwd(P_MYSHIP, D_ANG(1), 0, TURN_ANTICLOSE_TO, false);
                pEffect_->activate();
            }
            pEffect_->locateAs(this);
            if (pEffect_->onChangeToInactive()) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_IN_FIRE: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->turnMvAngTwd(P_MYSHIP,
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
                _pMorpher->morphLinerUntil(1, 0.0, 180); //閉じる
                _pKurokoA->setRzRyMvAngVelo(pSylvia_->_pKurokoA->_angveloFace[AXIS_Z],
                                            pSylvia_->_pKurokoA->_angveloFace[AXIS_Y]);
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

    _pKurokoA->behave();
    _pMorpher->behave();
    _pSeTx->behave();
}

void EnemySylviaEye::processJudgement() {
//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void EnemySylviaEye::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
        _TRACE_("EnemySylviaEye::onHit() 上位になげるっす throwEventUpperTree(SYLVIA_EXPLOSION)");
        throwEventUpperTree(SYLVIA_EXPLOSION); //親のEnemySylviaを破壊するイベントを投げる
    } else {
        //非破壊時
        _pSeTx->play3D(SE_DAMAGED);
        pSylvia_->effectFlush(2);
    }
}

void EnemySylviaEye::onInactive() {
    //sayonara();
}

void EnemySylviaEye::wake() {
    is_wake_ = true;
    _pProg->change(PROG_OPEN);
}

EnemySylviaEye::~EnemySylviaEye() {
}

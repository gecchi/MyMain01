#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    THALIA_PROG_MOVE = 1  ,
    THALIA_PROG_TURN_OPEN ,
    THALIA_PROG_FIRE_BEGIN,
    THALIA_PROG_IN_FIRE   ,
    THALIA_PROG_CLOSE     ,
};

EnemyThalia::EnemyThalia(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Thalia", STATUS(EnemyThalia)) {
        //CubeMapMorphMeshActor(prm_name, "1/ThaliaCM", STATUS(EnemyThalia)) {

    _class_name = "EnemyThalia";
    veloTopMv_ = 20000;
    iMovePatternNo_ = 0;
    pSplSeq_ = NULL;
    pDepo_Shot_ = NULL;
    pDepo_ShotEffect_ = NULL;

    pLaserChipDepo_ = NEW LaserChipDepository("MyRotLaser");
    pLaserChipDepo_->config(60, 1, NULL);
    EnemyStraightLaserChip001* pChip;
    for (int i = 0; i < 65; i++) { //レーザーストック
        stringstream name;
        name <<  "EnemyStraightLaserChip001[" << i << "]";
        pChip = NEW EnemyStraightLaserChip001(name.str().c_str());
        pChip->setSource(this); //位置向き同期
        pChip->inactivateImmed();
        pLaserChipDepo_->addSubLast(pChip);
    }
    addSubGroup(pLaserChipDepo_);

    _pSeTransmitter->useSe(2);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
    _pSeTransmitter->set(1, "laser001", GgafRepeatSeq::nextVal("CH_laser001"));     //爆発
    useProgress(THALIA_PROG_CLOSE);
    //初期カメラZ位置
    dZ_camera_init_ = -1 * P_CAM->_cameraZ_org * LEN_UNIT * PX_UNIT;
}

void EnemyThalia::onCreateModel() {

    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyThalia::initialize() {
    setHitAble(true);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 90000);
    setScaleR(0.3);
}

void EnemyThalia::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);
    _pKurokoA->setFaceAngVelo(AXIS_X, 1000);
    _pKurokoA->execSmoothMvSequenceD(veloTopMv_, 1000,
                                     MyShip::lim_front_-_X, 0.4, 0.6);
    _pProg->set(THALIA_PROG_MOVE);
    iMovePatternNo_ = 0; //行動パターンリセット

}

void EnemyThalia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));



    switch (_pProg->get()) {
        case THALIA_PROG_MOVE: {
            if (!_pKurokoA->isMoveingSmooth()) {
                _pMorpher->intoTargetAcceStep(1, 1.0, 0.0, 0.0004); //0.0004 開く速さ
                _pKurokoA->execTurnMvAngSequence(P_MYSHIP->_X, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                                 0, 100,
                                                 TURN_CLOSE_TO);

                _pProg->changeNext();
            }
            break;
        }
        case THALIA_PROG_TURN_OPEN: {
            if (_pMorpher->_method[1] == NOMORPH ) {
                _pProg->changeNext();
            }
            break;
        }

        case THALIA_PROG_FIRE_BEGIN: {
            if ( _X - P_MYSHIP->_X > -dZ_camera_init_) {
                _pProg->change(THALIA_PROG_IN_FIRE);
            } else {
                _pProg->change(THALIA_PROG_CLOSE);
            }
            break;
        }
        case THALIA_PROG_IN_FIRE: {
            if (getActivePartFrame() % 10 == 0) {
                _pKurokoA->execTurnMvAngSequence(P_MYSHIP->_X, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                                 10, 0,
                                                 TURN_CLOSE_TO);
            }
            EnemyStraightLaserChip001* pLaser = (EnemyStraightLaserChip001*)pLaserChipDepo_->dispatch();
            if (pLaser) {
                if (pLaser->_pChip_front == NULL) {
                    _pSeTransmitter->play3D(1);
                    _pKurokoA->setFaceAngVelo(AXIS_X, 5000);//発射中は速い回転
                }
            } else {
                _pProg->change(THALIA_PROG_CLOSE);
            }
            break;
        }
        case THALIA_PROG_CLOSE: {
            //１サイクルレーザー打ち切った
            _pMorpher->intoTargetLinerUntil(1, 0.0, 60); //閉じる
            _pKurokoA->execSmoothMvSequenceD(veloTopMv_, 1000, 1500000, 0.4, 0.6);
//            _pKurokoA->execSmoothMvSequence(200, 1000000, 180);
            _pKurokoA->setFaceAngVelo(AXIS_X, 1000);
            _pProg->change(THALIA_PROG_MOVE);
            break;
        }

        default:
            break;
    }


    _pKurokoA->behave();
    _pMorpher->behave();
    _pSeTransmitter->behave();
}

void EnemyThalia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyThalia::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (_pProg->get() != THALIA_PROG_MOVE && (pOther->getKind() & KIND_MY) ) {
        changeEffectTechniqueInterim("Flush", 2); //フラッシュ
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        if (pExplo001) {
            pExplo001->locatedBy(this);
        }
        _pSeTransmitter->play3D(0);


        if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
            EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
            if (pExplo001) {
                pExplo001->locatedBy(this);
            }
            _pSeTransmitter->play3D(0);


            //打ち返し弾
            if (pDepo_Shot_) {
//                MyStgUtil::shotWay001(this,
//                                       pDepo_Shot_,
//                                       P_MYSHIP,
//                                       10+_RANK_*10, 10000,
//                                       2000, 200);
//                MyStgUtil::shotWay001v2(this,
//                                       pDepo_Shot_,
//                                       P_MYSHIP,
//                                       10+_RANK_*10, 10000,
//                                       3000, 200,
//                                       5, 0.8);
//                MyStgUtil::shotWay002(this,
//                                       pDepo_Shot_,
//                                       P_MYSHIP,
//                                       20+_RANK_*10, 0,
//                                       2000, 200);
                  StgUtil::shotWay002v2(this,
                                       pDepo_Shot_,
                                       P_MYSHIP,
                                       R_EnemyThalia_ShotWay, 0,
                                       2000, 200,
                                       5, 0.8);

            }

            sayonara();
        }

    } else {

    }

}

void EnemyThalia::onInactive() {
    //sayonara();
}

EnemyThalia::~EnemyThalia() {
    DELETE_POSSIBLE_NULL(pSplSeq_);
}

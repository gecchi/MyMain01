#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyThalia::EnemyThalia(const char* prm_name) : DefaultMorphMeshActor(prm_name, "1/Thalia") {
//EnemyThalia::EnemyThalia(const char* prm_name) : CubeMapMorphMeshActor(prm_name, "1/ThaliaCM") {


    _class_name = "EnemyThalia";
    MyStgUtil::resetEnemyThaliaStatus(_pStatus);
    _iMovePatternNo = 0;
    _pSplineProgram = NULL;
    _pDispatcher_Shot = NULL;
    _pDispatcher_ShotEffect = NULL;

    _pLaserChipDispatcher = NEW LaserChipDispatcher("MyRotLaser");
    _pLaserChipDispatcher->config(100, 0, NULL);
    EnemyStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //レーザーストック
        stringstream name;
        name <<  "EnemyStraightLaserChip001" << i;
        string name2 = name.str();
        pChip = NEW EnemyStraightLaserChip001(name2.c_str());
        pChip->setSource(this); //位置向き同期
        pChip->inactivateImmediately();
        _pLaserChipDispatcher->addSubLast(pChip);
    }
    addSubGroup(_pLaserChipDispatcher);

    _pSeTransmitter->useSe(2);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
    _pSeTransmitter->set(1, "laser001", GgafRepeatSeq::nextVal("CH_laser001"));     //爆発
    _veloTopMv = 40000;
    useProgress(10);
    //初期カメラZ位置
    _dZ_camera_init = -1 * P_CAM->_cameraZ_org * LEN_UNIT * PX_UNIT;
}

void EnemyThalia::onCreateModel() {

    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 60, 1, -1);
    _pGgafDx9Model->setSpecular(5.0, 1.0);
}

void EnemyThalia::initialize() {
    setHitAble(true);
    _pKuroko->relateRzRyFaceAngToMvAng(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, 90000);
    _SX=_SY=_SZ=500;
}

void EnemyThalia::onActive() {
    MyStgUtil::resetEnemyThaliaStatus(_pStatus);
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);
    _pKuroko->setFaceAngVelo(AXIS_X, 1000);
    _pKuroko->orderSmoothMvVeloSequence(_veloTopMv, 300, MyShip::_lim_front - _X);
//    _TRACE_("orderSmoothMvVeloSequence START ("<<_X<<","<<_Y<<","<<_Z<<") 目標距離="<<(MyShip::_lim_front - _X)<<" veloMv="<<(_pKuroko->_veloMv));

    _pPrg->set(THALIA_SCENE_PROG_MOVE);
    _iMovePatternNo = 0; //行動パターンリセット

}

void EnemyThalia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));



    switch (_pPrg->get()) {
        case THALIA_SCENE_PROG_MOVE: {
            if (!_pKuroko->isMoveingSmooth()) {
                _pMorpher->intoTargetAcceStep(1, 1.0, 0.0, 0.0005);
                _pKuroko->orderTagettingMvAngSequence(P_MYSHIP->_X, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                                    0, 100,
                                                    TURN_CLOSE_TO);

                _pPrg->changeNext();
            }
            break;
        }
        case THALIA_SCENE_PROG_TURN_OPEN: {
            if (_pMorpher->_method[1] == NOMORPH ) {
                _pPrg->changeNext();
            }
            break;
        }

        case THALIA_SCENE_PROG_FIRE_BEGIN: {
            if ( _X - P_MYSHIP->_X > -_dZ_camera_init) {
                _pPrg->change(THALIA_SCENE_PROG_IN_FIRE);
            } else {
                _pPrg->change(THALIA_SCENE_PROG_CLOSE);
            }
            break;
        }
        case THALIA_SCENE_PROG_IN_FIRE: {
            if (getActivePartFrame() % 10 == 0) {
                _pKuroko->orderTagettingMvAngSequence(P_MYSHIP->_X, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                                    100, 0,
                                                    TURN_CLOSE_TO);
            }
            EnemyStraightLaserChip001* pLaser = (EnemyStraightLaserChip001*)_pLaserChipDispatcher->employ();
            if (pLaser) {
                pLaser->activate();
                if (pLaser->_pChip_front == NULL) {
                    _pSeTransmitter->play3D(1);
                    _pKuroko->setFaceAngVelo(AXIS_X, 4000);
                }
            } else {
                _pPrg->change(THALIA_SCENE_PROG_CLOSE);
            }
            break;
        }
        case THALIA_SCENE_PROG_CLOSE: {
            //１サイクルレーザー打ち切った
            _pMorpher->intoTargetLinerUntil(1, 0.0, 60);
            _pKuroko->orderSmoothMvVeloSequence(_veloTopMv, 200, 4000000);
            _pKuroko->setFaceAngVelo(AXIS_X, 1000);
            _pPrg->change(THALIA_SCENE_PROG_MOVE);
        }
        default:
            break;
    }


    _pKuroko->behave();
    _pMorpher->behave();
    _pSeTransmitter->behave();
}

void EnemyThalia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyThalia::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;

    if (_pPrg->get() != THALIA_SCENE_PROG_MOVE && (pOther->getKind() & KIND_MY) ) {
        changeEffectTechniqueInterim("Flush", 2); //フラッシュ
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
        if (pExplo001) {
            pExplo001->activate();
            pExplo001->locateAs(this);
        }
        _pSeTransmitter->play3D(0);


        if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
            EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
            if (pExplo001) {
                pExplo001->activate();
                pExplo001->locateAs(this);
            }
            _pSeTransmitter->play3D(0);


            //打ち返し弾
            if (_pDispatcher_Shot) {
//                MyStgUtil::shotWay001(this,
//                                       _pDispatcher_Shot,
//                                       P_MYSHIP,
//                                       10+_RANK_*10, 10000,
//                                       2000, 200);
//                MyStgUtil::shotWay001v2(this,
//                                       _pDispatcher_Shot,
//                                       P_MYSHIP,
//                                       10+_RANK_*10, 10000,
//                                       3000, 200,
//                                       5, 0.8);
//                MyStgUtil::shotWay002(this,
//                                       _pDispatcher_Shot,
//                                       P_MYSHIP,
//                                       20+_RANK_*10, 0,
//                                       2000, 200);
                  StgUtil::shotWay002v2(this,
                                       _pDispatcher_Shot,
                                       P_MYSHIP,
                                       20+_RANK_*10, 0,
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
    DELETE_POSSIBLE_NULL(_pSplineProgram);
}

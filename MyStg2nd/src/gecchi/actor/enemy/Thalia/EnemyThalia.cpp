#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

//EnemyThalia::EnemyThalia(const char* prm_name) : DefaultMorphMeshActor(prm_name, "1/Thalia") {
EnemyThalia::EnemyThalia(const char* prm_name) : CubeMapMorphMeshActor(prm_name, "1/ThaliaCM") {


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
//    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.5, 2.0);
//    _pGgafDx9Model->_pTextureBlinker->setBlink(0.5);
//    _pGgafDx9Model->_pTextureBlinker->beat(60, 3, 1, -1);
}

void EnemyThalia::initialize() {
    setHitAble(true);
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, 90000);
_SX=_SY=_SZ=500;
}

void EnemyThalia::onActive() {
    MyStgUtil::resetEnemyThaliaStatus(_pStatus);
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);
    _pMover->setFaceAngVelo(AXIS_X, 1000);
    _pMover->execSmoothMvVeloSequence(_veloTopMv, 300, MyShip::_lim_front - _X);
//    _TRACE_("execSmoothMvVeloSequence START ("<<_X<<","<<_Y<<","<<_Z<<") 目標距離="<<(MyShip::_lim_front - _X)<<" veloMv="<<(_pMover->_veloMv));

    _pProgress->change(THALIA_SCENE_PROG_MOVE);
    _iMovePatternNo = 0; //行動パターンリセット

}

void EnemyThalia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));



    switch (_pProgress->get()) {
        case THALIA_SCENE_PROG_MOVE: {
            if (!_pMover->isMoveingSmooth()) {
                _pMorpher->intoTargetAcceStep(1, 1.0, 0.0, 0.0005);
                _pMover->execTagettingMvAngSequence(P_MYSHIP->_X, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                                    0, 100,
                                                    TURN_CLOSE_TO);

                _pProgress->change(THALIA_SCENE_PROG_TURN_OPEN);
            }
            break;
        }
        case THALIA_SCENE_PROG_TURN_OPEN: {
            if (_pMorpher->_method[1] == NOMORPH ) {
                _pProgress->change(THALIA_SCENE_PROG_FIRE_BEGIN);
            }
            break;
        }
        case THALIA_SCENE_PROG_FIRE_BEGIN: {
            if ( _X - P_MYSHIP->_X > -_dZ_camera_init) {
                _pProgress->change(THALIA_SCENE_PROG_IN_FIRE);
            } else {
                _pProgress->change(THALIA_SCENE_PROG_CLOSE);
            }
            break;
        }
        case THALIA_SCENE_PROG_IN_FIRE: {
            if (getActivePartFrame() % 10 == 0) {
                _pMover->execTagettingMvAngSequence(P_MYSHIP->_X, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                                    100, 0,
                                                    TURN_CLOSE_TO);
            }
            EnemyStraightLaserChip001* pLaser = (EnemyStraightLaserChip001*)_pLaserChipDispatcher->employ();
            if (pLaser != NULL) {
                pLaser->activate();
                if (pLaser->_pChip_front == NULL) {
                    _pSeTransmitter->play3D(1);
                    _pMover->setFaceAngVelo(AXIS_X, 4000);
                }
            } else {
                _pProgress->change(THALIA_SCENE_PROG_CLOSE);
            }
            break;
        }
        case THALIA_SCENE_PROG_CLOSE: {
            //１サイクルレーザー打ち切った
            _pMorpher->intoTargetLinerUntil(1, 0.0, 60);
            _pMover->execSmoothMvVeloSequence(_veloTopMv, 200, 4000000);
            _pMover->setFaceAngVelo(AXIS_X, 1000);
            _pProgress->change(THALIA_SCENE_PROG_MOVE);
        }
        default:
            break;


    }


    _pMover->behave();
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

    if (_pProgress->get() != THALIA_SCENE_PROG_MOVE) {
        changeEffectTechniqueInterim("Flush", 2); //フラッシュ
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDispatcher_EffectExplosion001->employ();
        if (pExplo001 != NULL) {
            pExplo001->activate();
            pExplo001->setCoordinateBy(this);
        }
        _pSeTransmitter->play3D(0);


        if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
            EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDispatcher_EffectExplosion001->employ();
            if (pExplo001 != NULL) {
                pExplo001->activate();
                pExplo001->setCoordinateBy(this);
            }
            _pSeTransmitter->play3D(0);


            //打ち返し弾
            if (_pDispatcher_Shot) {
                int way = 10+_RANK_*10; //ショットWAY数
                angle* paAngWay = NEW angle[way];
                angle rz,ry;
                GgafDx9Util::getRzRyAng(P_MYSHIP->_X-_X, P_MYSHIP->_Y-_Y, P_MYSHIP->_Z-_Z,
                                        rz, ry);
                GgafDx9Util::getWayAngle2D(0,way,10000,paAngWay);
                GgafDx9DrawableActor* pActor_Shot;
                for (int i = 0; i < way; i++) {
                    pActor_Shot = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                    if (pActor_Shot) {
                        pActor_Shot->setCoordinateBy(this);
                        pActor_Shot->_pMover->setRzRyMvAng(rz+paAngWay[i], ry);
                        pActor_Shot->_pMover->setMvVelo(2000);
                        pActor_Shot->_pMover->setMvAcce(200);
                        pActor_Shot->activate();
                    }
                }
                DELETEARR_IMPOSSIBLE_NULL(paAngWay);
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

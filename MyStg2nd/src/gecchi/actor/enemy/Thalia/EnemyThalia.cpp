#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyThalia::EnemyThalia(const char* prm_name) : DefaultMorphMeshActor(prm_name, "1/Thalia") {
    _class_name = "EnemyThalia";
    MyStgUtil::resetEnemyThaliaStatus(_pStatus);
    _iMovePatternNo = 0;
    _pSplineProgram = NULL;
    _pDispatcher_Shot = NULL;
    _pDispatcher_ShotEffect = NULL;

    _pLaserChipDispatcher = NEW LaserChipDispatcher("MyRotLaser");
    EnemyStraightLaserChip001* pChip;
    for (int i = 0; i < 100; i++) { //レーザーストック
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
}

void EnemyThalia::onCreateModel() {
//    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.5, 2.0);
//    _pGgafDx9Model->_pTextureBlinker->setBlink(0.5);
//    _pGgafDx9Model->_pTextureBlinker->beat(60, 3, 1, -1);
}

void EnemyThalia::initialize() {
    setHitAble(true);
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMover->setFaceAngVelo(AXIS_X, 1000);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, 10000);
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);
}

void EnemyThalia::onActive() {
    MyStgUtil::resetEnemyThaliaStatus(_pStatus);
    _pMover->setMvAcce(pMYSHIP->_X-_X, 180);
    _TRACE_("_pMover->_accMv="<<_pMover->_accMv);
    _iMovePatternNo = 0; //行動パターンリセット
}

void EnemyThalia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    if (_iMovePatternNo == 0) {
        if (getActivePartFrame() == 180) {
            _pMover->setMvAcce(0);
            _pMover->setMvVelo(0);
            _pMorpher->intoTargetLinerUntil(1, 1.0, 120);
            _pMover->execTagettingMvAngSequence(pMYSHIP->_X, pMYSHIP->_Y, pMYSHIP->_Z,
                                                1000, 0,
                                                TURN_CLOSE_TO);
            _pMover->setFaceAngVelo(AXIS_X, 5000);
            _iMovePatternNo++;
        }

    }

    if (_iMovePatternNo == 1) {
        if (getActivePartFrame() == 220) {
            _iMovePatternNo++;
        }
    }

    if (_iMovePatternNo == 2) {
        EnemyStraightLaserChip001* pLaser = (EnemyStraightLaserChip001*)_pLaserChipDispatcher->employ();
        if (pLaser != NULL) {
            pLaser->activate();
            if (pLaser->_pChip_front == NULL) {
                _pSeTransmitter->play3D(1);
            }
        } else {
            _iMovePatternNo++;
        }
    }

    if (_iMovePatternNo == 3) {
        _pMorpher->intoTargetLinerUntil(1, 0.0, 60);
        _pMover->setMvAcce(200);
        _pMover->setFaceAngVelo(AXIS_X, 1000);
    }
    _pMover->behave();
    _pMorpher->behave();
    _pSeTransmitter->behave();
}

void EnemyThalia::processJudgement() {
    if (isOutOfGameSpace()) {
        sayonara();
    }
}

void EnemyThalia::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("EnemyThalia::onHit!!! this="<<getName()<<"("<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    //_TRACE_("EnemyThalia::onHit!!! prm_pOtherActor="<<prm_pOtherActor->getName()<<"("<<prm_pOtherActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {

        EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        _pSeTransmitter->play3D(0);
        if (pExplo001 != NULL) {
            pExplo001->activate();
            pExplo001->setGeometry(this);
        }
        sayonara();
    }
}

void EnemyThalia::onInactive() {
    sayonara();
}

EnemyThalia::~EnemyThalia() {
    DELETE_POSSIBLE_NULL(_pSplineProgram);
}

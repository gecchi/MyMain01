#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

#define MORPHTARGET_VESTA_HATCH_OPENED 1
#define VESTA_HATCH_CLOSED      0
#define VESTA_HATCH_OPENED      1

EnemyVesta::EnemyVesta(const char* prm_name)
                       : DefaultMorphMeshActor(prm_name, "1/donatu") {
    _class_name = "EnemyVesta";
    MyStgUtil::resetEnemyVestaStatus(_pStatus);
    _pActor_Foundation = NULL;
    _iMovePatternNo = 0;
    _is_open_hatch = false;
    _frame_of_open_interval  = 3*60;
    _frame_of_close_interval = 4*60;
    _frame_of_moment_nextopen = 0;
    _frame_of_moment_nextclose = 0;
    _frame_of_morph_interval   = 60;
    prepareSe2("bomb1");     //爆発
    _pDispatcher_Fired = NULL;
    defineWorldMatrix(GgafDx9Util::mulWorldMatrix_ScRxRzRyMv);
}

void EnemyVesta::onCreateModel() {
    _pGgafDx9Model->_fBlinkThreshold = 0.9;
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.1, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 60, 1, -1);
}

void EnemyVesta::initialize() {
    setHitAble(false);
    _pMorpher->forceWeightRange(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f, 1.0f);
    _pMorpher->setWeight(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, 90000);
}

void EnemyVesta::onActive() {
    MyStgUtil::resetEnemyVestaStatus(_pStatus);
    _pMorpher->setWeight(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f);
    _is_open_hatch = false;
    _iMovePatternNo = VESTA_HATCH_CLOSED;
    _frame_of_moment_nextopen = 60;
}

void EnemyVesta::processBehavior() {
    switch (_iMovePatternNo) {
        case VESTA_HATCH_CLOSED:
            if (getPartFrame() == _frame_of_moment_nextopen-(_frame_of_morph_interval/2)) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_VESTA_HATCH_OPENED,
                                                1.0f, _frame_of_morph_interval);
            }
            if (getPartFrame() == _frame_of_moment_nextopen) {
                _frame_of_moment_nextclose = getPartFrame() + _frame_of_close_interval;
                _iMovePatternNo = VESTA_HATCH_OPENED;
            }
            break;
        case VESTA_HATCH_OPENED:
            if (getPartFrame() == _frame_of_moment_nextclose - (_frame_of_morph_interval/2)) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_VESTA_HATCH_OPENED,
                                                0.0f, _frame_of_morph_interval);
            }
            if (getPartFrame() == _frame_of_moment_nextclose) {
                _frame_of_moment_nextopen = getPartFrame() + _frame_of_open_interval;
                _iMovePatternNo = VESTA_HATCH_CLOSED;
            }
        default :
            break;
    }
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));


    if (_iMovePatternNo == VESTA_HATCH_OPENED) {
        int openningFrame = getPartFrame() - _frame_of_moment_nextopen; //開いてからのフレーム数。
        //_frame_of_moment_nextopenは、ここの処理の時点では直近でオープンしたフレームとなる。
        if (openningFrame % (int)(10/_RANK_) == 0) {
            if (_pDispatcher_Fired) {
                GgafDx9DrawableActor* pActor = (GgafDx9DrawableActor*)_pDispatcher_Fired->employ();
                if (pActor) {
                    pActor->setGeometry(this);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(_pMover->_angRzMv, _pMover->_angRyMv);
                    pActor->activate();
                }
            }
        }
    }



    _pMorpher->behave();
    _pMover->behave();
}

void EnemyVesta::processJudgement() {
    if (_pActor_Foundation == NULL || (_pActor_Foundation != NULL && !_pActor_Foundation->isActive())) {
        inactivate();
    } else {

        (*(_pActor_Foundation->_pFunc_calcWorldMatrix))(this, _matWorld);
    }
//    if (isOutOfGameSpace()) {
//        inactivate();
//    }
}

void EnemyVesta::onHit(GgafActor* prm_pOtherActor) {
//    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
//    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
//    playSe2();
//    if (pExplo001 != NULL) {
//        pExplo001->activate();
//        pExplo001->setGeometry(this);
//    }
//
//    if (MyStgUtil::calcEnemyStamina(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        inactivate();
//    }
}

void EnemyVesta::onInactive() {
    sayonara();
}

EnemyVesta::~EnemyVesta() {
}

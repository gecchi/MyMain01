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
                       : DefaultMorphMeshActor(prm_name, "1/hachi") {
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
    _pDpcon = (DispatcherConnection*)God::_dispatcherManager.connect("DpCon_Shot001");
}

void EnemyVesta::onCreateModel() {
    _pGgafDx9Model->_fBlinkThreshold = 0.9;
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.1, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 60, 1, -1);
}

void EnemyVesta::initialize() {
    setHitAble(true);
    //_pMover->setRzMvAngVelo(1000);
    //_pMover->setRyMvAngVelo(500);
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMorpher->forceWeightRange(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f, 1.0f);
    _pMorpher->setWeight(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -10000, -10000, -10000, 10000, 10000, 10000);
    _pScaler->setScale(1000);

    _pDispatcher_Fired = _pDpcon->view();

    //_pFunc_calcWorldMatrix = NULL;//ワールド変換は独自に行う
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
        if (openningFrame % (int)(20/_RANK_+5) == 0) {
            if (_pDispatcher_Fired) {
                GgafDx9DrawableActor* pActor = (GgafDx9DrawableActor*)_pDispatcher_Fired->employ();
                if (pActor) {
                    pActor->setGeometry(this);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
               		float vX, vY, vZ;
					angle rz, ry;
					vX = _matWorld_RM._11;//*_pMover->_vX + _matWorld_RM._21*_pMover->_vY + _matWorld_RM._31*_pMover->_vZ;
					vY = _matWorld_RM._12;//*_pMover->_vX + _matWorld_RM._22*_pMover->_vY + _matWorld_RM._32*_pMover->_vZ;
					vZ = _matWorld_RM._13;//*_pMover->_vX + _matWorld_RM._23*_pMover->_vY + _matWorld_RM._33*_pMover->_vZ;
					GgafDx9Util::getRzRyAng(vX, vY, vZ,
                                            rz, ry);
					pActor->_pMover->setRzRyMvAng(rz, ry);
                    pActor->activate();
                }
            }
        }
    }


    _pScaler->behave();
    _pMorpher->behave();

    chengeGeoLocal();
    _pMover->behave();
    chengeGeoFinal();

}

void EnemyVesta::processJudgement() {
    if (_pActor_Foundation != NULL && _pActor_Foundation->isActive()) {
//        (*(_pActor_Foundation->_pFunc_calcWorldMatrix))(_pActor_Foundation, _matWorld);
//        defineWorldMatrix(GgafDx9Util::mulWorldMatrix_RxRzRyMv);
    } else {
        //土台がなければ自分も死ぬ
        inactivate();
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
//    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        inactivate();
//    }
}

void EnemyVesta::onInactive() {
    sayonara();
}

EnemyVesta::~EnemyVesta() {
    _pDpcon->close();
}

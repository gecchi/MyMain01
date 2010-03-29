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
    _pActor_Base = NULL;
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
                    //向きのベクトルは_matWorldRotMvで変換される。
                    //_matWorldRotMv の成分を mat_xx とすると
                    //
                    //                      | mat_11 mat_12 mat_13 |
                    //| _Xorg _Yorg _Zorg | | mat_21 mat_22 mat_23 | = | vX vY vZ |
                    //                      | mat_31 mat_32 mat_33 |
                    //
                    //vX = _Xorg*mat_11 + _Yorg*mat_21 + _Zorg*mat_31
                    //vY = _Xorg*mat_12 + _Yorg*mat_22 + _Zorg*mat_32
                    //vZ = _Xorg*mat_13 + _Yorg*mat_23 + _Zorg*mat_33
                    //
                    //さてここで、モデルの前方である単位方向ベクトル(1,0,0)はどうなるか考えると
                    //
                    //vX = _Xorg*mat_11
                    //vY = _Xorg*mat_12
                    //vZ = _Xorg*mat_13

                    float vX, vY, vZ;
                    angle rz, ry;
                    vX = _matWorldRotMv._11;
                    vY = _matWorldRotMv._12;
                    vZ = _matWorldRotMv._13;
                    GgafDx9Util::getRzRyAng(vX, vY, vZ,
                                            rz, ry);
                    pActor->_pMover->setRzRyMvAng(rz, ry);
                    pActor->activate();
                }
            }
        }
    }


    if (getPartFrame() % 10 == 0) {
        //自機へ方向を向ける

        //土台の_matWorldRotMv の成分を mat_xx とし、
        //自機への向きのベクトルを、(MvX, MvY, MvZ) とすると
        //
        //             | mat_11 mat_12 mat_13 |
        //| vX vY vZ | | mat_21 mat_22 mat_23 | = | MvX MvY MvZ |
        //             | mat_31 mat_32 mat_33 |
        //
        //となるような(vX, vY, vZ) を求めたいのだから、
        //
        //                | mat_11 mat_12 mat_13 | -1
        //| MvX MvY MvZ | | mat_21 mat_22 mat_23 |    = | vX vY vZ |
        //                | mat_31 mat_32 mat_33 |
        //

        //MvX MvY MvZ を求める
        int MvX = pMYSHIP->_X - _X;
        int MvY = pMYSHIP->_Y - _Y;
        int MvZ = pMYSHIP->_Z - _Z;
        D3DXMATRIX* pBaseInvMatRM = _pActor_Base->gatInvMatWorldRotMv();
        int vX = MvX*pBaseInvMatRM->_11 + MvY*pBaseInvMatRM->_21 + MvZ * pBaseInvMatRM->_31;
        int vY = MvX*pBaseInvMatRM->_12 + MvY*pBaseInvMatRM->_22 + MvZ * pBaseInvMatRM->_32;
        int vZ = MvX*pBaseInvMatRM->_13 + MvY*pBaseInvMatRM->_23 + MvZ * pBaseInvMatRM->_33;
        angle angRz_Target, angRy_Target;
        GgafDx9Util::getRzRyAng(vX, vY, vZ,
                                angRz_Target, angRy_Target);
        _pMover->execTagettingMvAngSequence(angRz_Target, angRy_Target,
                                           1000, 0,
                                           TURN_CLOSE_TO);

    }


    _pScaler->behave();
    _pMorpher->behave();

    chengeGeoLocal();
    _pMover->behave();
    chengeGeoFinal();

}

void EnemyVesta::processJudgement() {
    if (_pActor_Base != NULL && _pActor_Base->isActive()) {
//        (*(_pActor_Base->_pFunc_calcWorldMatrix))(_pActor_Base, _matWorld);
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

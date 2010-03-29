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
                    //向きのベクトルは_matWorld_RMで変換される。
                    //_matWorld_RM の成分を mat_xx とすると
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
                    vX = _matWorld_RM._11;
                    vY = _matWorld_RM._12;
                    vZ = _matWorld_RM._13;
                    GgafDx9Util::getRzRyAng(vX, vY, vZ,
                                            rz, ry);
                    pActor->_pMover->setRzRyMvAng(rz, ry);
                    pActor->activate();
                }
            }
        }
    }


    if (getPartFrame() % 120 == 0) {
        //_matWorld_RM の成分を mat_xx とし、
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
        float MvX, MvY, MvZ;
        GgafDx9Util::getNormalizeVector(pMYSHIP->_X - _X,
                                        pMYSHIP->_Y - _Y,
                                        pMYSHIP->_Z - _Z,
                                        MvX,
                                        MvY,
                                        MvZ);
        D3DXMATRIX matInvRM;
        D3DXMatrixInverse(&matInvRM, NULL, &_matWorld_RM);
        float vX, vY, vZ;
        vX = MvX*matInvRM._11 + MvY*matInvRM._21 + MvZ*matInvRM._31;
        vY = MvX*matInvRM._12 + MvY*matInvRM._22 + MvZ*matInvRM._32;
        vZ = MvX*matInvRM._13 + MvY*matInvRM._23 + MvZ*matInvRM._33;
        angle angRz_Target, angRy_Target;
        GgafDx9Util::getRzRyAng(vX, vY, vZ,
                                angRz_Target, angRy_Target);
        _pMover->execTagettingMvAngSequence(angRz_Target, angRy_Target,
                                           2000, 0,
                                           TURN_CLOSE_TO);

//        //逆行列を求める。
//        double det = (
//                         (_matWorld_RM._11 * (_matWorld_RM._22*_matWorld_RM._33 - _matWorld_RM._23*_matWorld_RM._32))
//                       + (_matWorld_RM._21 * (_matWorld_RM._32*_matWorld_RM._13 - _matWorld_RM._33*_matWorld_RM._12))
//                       + (_matWorld_RM._31 * (_matWorld_RM._12*_matWorld_RM._23 - _matWorld_RM._13*_matWorld_RM._22))
//                     );
//        double inv[3][3];
//        inv[0][0] = (_matWorld_RM._22*_matWorld_RM._33 - _matWorld_RM._23*_matWorld_RM._32)/det;
//        inv[0][1] = (_matWorld_RM._32*_matWorld_RM._13 - _matWorld_RM._33*_matWorld_RM._12)/det;
//        inv[0][2] = (_matWorld_RM._12*_matWorld_RM._23 - _matWorld_RM._13*_matWorld_RM._22)/det;
//
//        inv[1][0] = (_matWorld_RM._23*_matWorld_RM._31 - _matWorld_RM._21*_matWorld_RM._33)/det;
//        inv[1][1] = (_matWorld_RM._33*_matWorld_RM._11 - _matWorld_RM._31*_matWorld_RM._13)/det;
//        inv[1][2] = (_matWorld_RM._13*_matWorld_RM._21 - _matWorld_RM._11*_matWorld_RM._23)/det;
//
//        inv[2][0] = (_matWorld_RM._21*_matWorld_RM._32 - _matWorld_RM._22*_matWorld_RM._31)/det;
//        inv[2][1] = (_matWorld_RM._31*_matWorld_RM._12 - _matWorld_RM._32*_matWorld_RM._11)/det;
//        inv[2][2] = (_matWorld_RM._11*_matWorld_RM._22 - _matWorld_RM._12*_matWorld_RM._21)/det;
//
//        //ローカルの方向を求める
//        float vX, vY, vZ;
//        vX = inv[0][0]*MvX + inv[1][0]*MvY + inv[2][0]*MvZ;
//        vY = inv[0][1]*MvX + inv[1][1]*MvY + inv[2][1]*MvZ;
//        vZ = inv[0][2]*MvX + inv[1][2]*MvY + inv[2][2]*MvZ;
//
//        float vX2, vY2, vZ2;
//        vX2 = vX*_matWorld_RM._11 + vY*_matWorld_RM._21 + vZ*_matWorld_RM._31;
//        vY2 = vX*_matWorld_RM._12 + vY*_matWorld_RM._22 + vZ*_matWorld_RM._32;
//        vZ2 = vX*_matWorld_RM._13 + vY*_matWorld_RM._23 + vZ*_matWorld_RM._33;
//        angle angRz_Target, angRy_Target;
//        GgafDx9Util::getRzRyAng(vX2, vY2, vZ2,
//                                angRz_Target, angRy_Target);
//        _pMover->execTagettingMvAngSequence(angRz_Target, angRy_Target,
//                                           3000, 0,
//                                           TURN_CLOSE_TO);
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

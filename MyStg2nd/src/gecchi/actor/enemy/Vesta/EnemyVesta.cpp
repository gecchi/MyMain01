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
                       : DefaultMorphMeshActor(prm_name, "1/Vesta") {
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

    _pDispatcher_Fired = NULL;
    _pDpcon = (DispatcherConnection*)(P_GOD->_pDispatcherManager->getConnection("DpCon_Shot004"));

    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "explos3", GgafRepeatSeq::nextVal("CH_explos3"));
    setAlpha(1.0);
}

void EnemyVesta::onCreateModel() {
    _pGgafDx9Model->_fBlinkThreshold = 0.9;
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.1, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 60, 1, -1);
}

void EnemyVesta::initialize() {
    setHitAble(true);
    //_pKuroko->setRzMvAngVelo(1000);
    //_pKuroko->setRyMvAngVelo(500);
    _pKuroko->relateRzRyFaceAngToMvAng(true);
    _pMorpher->forceWeightRange(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f, 1.0f);
    _pMorpher->setWeight(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 200000);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(1000, 1200);
    _pScaler->beat(30, 5, 5, -1);
    _pDispatcher_Fired = _pDpcon->refer();
}

void EnemyVesta::onActive() {
    MyStgUtil::resetEnemyVestaStatus(_pStatus);
    _pMorpher->setWeight(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f);
    _is_open_hatch = false;
    _iMovePatternNo = VESTA_HATCH_CLOSED;
    _frame_of_moment_nextopen = 60;
}

void EnemyVesta::processBehavior() {
    //ボーンにあたるアクターのメモ
    //_X, _Y, _Z, _RX, _RY, _RZ について２つの座標系セットを切り替えが必要な仕様です。
    //それぞれローカル座標、最終（絶対）座標と呼ぶことにします。
    //・最終（絶対）座標 ・・・ 普通のワールド座標系の事です。
    //・ローカル座標     ・・・ 親アクターの基点(0,0,0)からの相対的な座標系を意味します。
    //                          座標計算はこちらで行って下さい。
    //＜方針＞
    //  ①座標計算は主にローカル座標系の計算である。GgafDx9Kuroko でローカル座標系の操作を行うこととする。
    //    しかし、８分木登録や、当たり判定や、ターゲット座標など、他のオブジェクトからワールド座標を参照することが多いため。
    //    基本的にprocessBehavior()開始時は 最終（絶対）座標系(changeGeoFinal())の状態とする。
    //  ②processBehavior()内で必要に応じて changeGeoLocal() で _X, _Y, _Z, _RX, _RY, _RZ の切り替えを行い座標計算を行う。
    //  ③但し processBehavior() を抜ける際には必ず最終座標(changeGeoFinal())の状態に戻しておく事。
    //  ④オブジェクト自体のワールド変換行列は、ローカル座標系の行列積で変換行列が作成される。

    //＜changeGeoLocal(); 実行時＞
    //ローカル座標系に切替えます。
    //・_X, _Y, _Z     ・・・ は、ローカル座標を意味するようになります。
    //                        changeGeoLocal(); を実行すると自動的に_X, _Y, _Z に
    //                        ローカル座標値に切り替わります。
    //・_RX, _RY, _RZ  ・・・ は、ローカル座標での軸回転値を意味するようになります。
    //                        changeGeoLocal(); を実行すると自動的に_RX, _RY, _RZに
    //                        ローカル座標軸回転値に切り替わります。

    //＜changeGeoFinal(); 実行時＞
    //最終（絶対）座標系に切り替えます。
    //・_X, _Y, _Z    ・・・ 毎フレーム GgafDx9GeometricActor::processSettlementBehavior() で計算され自動更新されてます。
    //                       processBehavior() で changeGeoFinal() を行うと、１フレーム前の_X, _Y, _Zに切り替わる事になります。
    //                       _X, _Y, _Z は参照専用。値を代入しても意味が有りません
    //・_RX, _RY, _RZ ・・・ 毎フレーム GgafDx9GeometricActor::processSettlementBehavior() 自動代入されません！
    //                       changeGeoFinal(); を実行しても、_RX, _RY, _RZ は以前の最終（絶対）座標系の値が
    //                       入りっぱなしで変化しません。
    //                       他のオブジェクトから、ボーンにあたるアクターを参照するとき、_RX, _RY, _RZは全く信用できません。

    //＜注意＞
    //・GgafDx9Kuroko(_pKuroko)の behave() 以外メソッドは、常にローカル座標の操作とする。
    //  behave()以外メソッドは実際に座標計算しているわけではないので、
    //  changeGeoFinal()時、changeGeoLocal()時に関係なく、呼び出し可能。
    //・GgafDx9Kuroko(_pKuroko)の behave() メソッドは座標を１フレーム後の状態にする計算を行う。
    //  したがって、次のように ローカル座標時(changeGeoLocal()時)で呼び出す事とする。
    //    changeGeoLocal();
    //    _pKuroko->behave();
    //    changeGeoFinal();
    //TODO:混在感をもっとなくす。

    switch (_iMovePatternNo) {
        case VESTA_HATCH_CLOSED:
            if (getActivePartFrame() == _frame_of_moment_nextopen-(_frame_of_morph_interval/2)) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_VESTA_HATCH_OPENED,
                                                1.0f, _frame_of_morph_interval);
            }
            if (getActivePartFrame() == _frame_of_moment_nextopen) {
                _frame_of_moment_nextclose = getActivePartFrame() + _frame_of_close_interval;
                _iMovePatternNo = VESTA_HATCH_OPENED;
            }
            break;
        case VESTA_HATCH_OPENED:
            if (getActivePartFrame() == _frame_of_moment_nextclose - (_frame_of_morph_interval/2)) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_VESTA_HATCH_OPENED,
                                                0.0f, _frame_of_morph_interval);
            }
            if (getActivePartFrame() == _frame_of_moment_nextclose) {
                _frame_of_moment_nextopen = getActivePartFrame() + _frame_of_open_interval;
                _iMovePatternNo = VESTA_HATCH_CLOSED;
            }
        default :
            break;
    }
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //オープン時敵出現
    if (_iMovePatternNo == VESTA_HATCH_OPENED) {
        int openningFrame = getActivePartFrame() - _frame_of_moment_nextopen; //開いてからのフレーム数。
        //_frame_of_moment_nextopenは、ここの処理の時点では直近でオープンしたフレームとなる。
        if (openningFrame % (int)(25-_RANK_*5) == 0) {
            if (_pDispatcher_Fired) {
                GgafDx9DrawableActor* pActor = (GgafDx9DrawableActor*)_pDispatcher_Fired->employ();
                if (pActor) {
                    pActor->locateAs(this);
                    pActor->_pKuroko->relateRzRyFaceAngToMvAng(true);
                    //＜現在の最終的な向きを、RzRyで取得する＞
                    //方向ベクトルはワールド変換行列の積（_matWorldRotMv)で変換され、現在の最終的な向きに向く。
                    //元の方向ベクトルを(_Xorg,_Yorg,_Zorg)、
                    //ワールド変換行列の回転部分の積（_matWorldRotMv)の成分を mat_xx、
                    //最終的な方向ベクトルを(vX, vY, vZ) とすると
                    //
                    //                      | mat_11 mat_12 mat_13 |
                    //| _Xorg _Yorg _Zorg | | mat_21 mat_22 mat_23 | = | vX vY vZ |
                    //                      | mat_31 mat_32 mat_33 |
                    //
                    //vX = _Xorg*mat_11 + _Yorg*mat_21 + _Zorg*mat_31
                    //vY = _Xorg*mat_12 + _Yorg*mat_22 + _Zorg*mat_32
                    //vZ = _Xorg*mat_13 + _Yorg*mat_23 + _Zorg*mat_33
                    //
                    //さてここで、元々が前方の単位方向ベクトル(1,0,0)の場合はどうなるか考えると
                    //
                    //vX = _Xorg*mat_11
                    //vY = _Xorg*mat_12
                    //vZ = _Xorg*mat_13
                    //
                    //となる。本アプリでは、モデルは全て(1,0,0)を前方としているため
                    //最終的な方向ベクトルは（_Xorg*mat_11, _Xorg*mat_12, _Xorg*mat_13) である。
                    angle Rz, Ry;
                    GgafDx9Util::getRzRyAng(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13,
                                            Rz, Ry); //現在の最終的な向きを、RzRyで取得！
                    pActor->_pKuroko->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->reset();
                    pActor->activate();
                }
            }
        }
    }

    if (getActivePartFrame() % 10 == 0                   && 1 == 2) {
        //自機へ方向を向ける
        //考え方：ローカル座標系で予めどの方向に向いておけば、最終的に自機に向くことになるかを求める
        //
        //自機への向くための変換前状態でのターゲット位置を(TvX, TvY, TvZ) とおき、
        //「土台まで」の行列の積（_pActor_Base->_matWorldRotMv) を b_mat_xx とする。
        //現在の最終座標から自機への向きのベクトルを、(MvX, MvY, MvZ) とすると、
        //
        //                | b_mat_11 b_mat_12 b_mat_13 |
        //| TvX TvY TvZ | | b_mat_21 b_mat_22 b_mat_23 | = | MvX MvY MvZ |
        //                | b_mat_31 b_mat_32 b_mat_33 |
        //
        //となる。ローカル座標で(TvX, TvY, TvZ) の方向を向けると、
        //最終的に自機に向くことになる。
        //逆行列を掛けて(TvX, TvY, TvZ) を求めれば良い
        //
        //                                   | b_mat_11 b_mat_12 b_mat_13 | -1
        // | TvX TvY TvZ | = | MvX MvY MvZ | | b_mat_21 b_mat_22 b_mat_23 |
        //                                   | b_mat_31 b_mat_32 b_mat_33 |
        //

        //MvX MvY MvZ を求める
        int MvX = P_MYSHIP->_X - _X;
        int MvY = P_MYSHIP->_Y - _Y;
        int MvZ = P_MYSHIP->_Z - _Z;
        //逆行列取得
        D3DXMATRIX* pBaseInvMatRM = _pActor_Base->gatInvMatWorldRotMv();
        //ローカル座標でのターゲットとなる方向ベクトル計算
        int TvX = MvX*pBaseInvMatRM->_11 + MvY*pBaseInvMatRM->_21 + MvZ * pBaseInvMatRM->_31;
        int TvY = MvX*pBaseInvMatRM->_12 + MvY*pBaseInvMatRM->_22 + MvZ * pBaseInvMatRM->_32;
        int TvZ = MvX*pBaseInvMatRM->_13 + MvY*pBaseInvMatRM->_23 + MvZ * pBaseInvMatRM->_33;
        //自動方向向きシークエンス開始
        angle angRz_Target, angRy_Target;
        GgafDx9Util::getRzRyAng(TvX, TvY, TvZ,
                                angRz_Target, angRy_Target);
        _pKuroko->orderTagettingMvAngSequence(angRz_Target, angRy_Target,
                                           1000, 0,
                                           TURN_CLOSE_TO);
    }

    _pScaler->behave();
    _pMorpher->behave();
    //_pSeTransmitter->behave();

    //_pKurokoの計算はローカルで行う
    changeGeoLocal();
    _pKuroko->behave();
    changeGeoFinal();

}

void EnemyVesta::processJudgement() {
    if (_pActor_Base != NULL && _pActor_Base->isActiveActor()) {
//        (*(_pActor_Base->_pFunc_calcRotMvWorldMatrix))(_pActor_Base, _matWorld);
    } else {
        //土台がなければ自分も死ぬ
        sayonara();
    }


//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void EnemyVesta::onHit(GgafActor* prm_pOtherActor) {
    changeEffectTechniqueInterim("Flush", 2); //フラッシュ

    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();

    if (pExplo001) {
        pExplo001->activate();
        pExplo001->locateAs(this);
    }

    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        _pSeTransmitter->play3D(0);
        sayonara();
    }
}

void EnemyVesta::onInactive() {
    sayonara();
}

EnemyVesta::~EnemyVesta() {
    _pDpcon->close();
}

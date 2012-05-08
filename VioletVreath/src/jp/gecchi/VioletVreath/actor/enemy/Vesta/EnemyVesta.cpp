#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_VESTA_HATCH_OPENED 1
#define VESTA_HATCH_CLOSED      0
#define VESTA_HATCH_OPENED      1

EnemyVesta::EnemyVesta(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Vesta", STATUS(EnemyVesta)) {
    _class_name = "EnemyVesta";
    _pActor_Base = NULL;
    iMovePatternNo_ = 0;
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 4*60;
    frame_of_moment_nextopen_ = 0;
    frame_of_moment_nextclose_ = 0;
    frame_of_morph_interval_   = 60;

    pDepo_Fired_ = NULL;
    pDpcon_ = connectDepositoryManager("DpCon_Shot004", NULL);

    _pSeTx->useSe(1);
    _pSeTx->set(0, "explos3", GgafRepeatSeq::nextVal("CH_explos3"));
}

void EnemyVesta::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);

}

void EnemyVesta::initialize() {
    setHitAble(true);
    //_pKurokoA->setRzMvAngVelo(1000);
    //_pKurokoA->setRyMvAngVelo(500);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pMorpher->forceWeightRange(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f, 1.0f);
    _pMorpher->setWeight(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 200000);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(1000, 1200);
    _pScaler->beat(30, 5, 5, -1);
    pDepo_Fired_ = pDpcon_->fetch();
}

void EnemyVesta::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f);
    is_open_hatch_ = false;
    iMovePatternNo_ = VESTA_HATCH_CLOSED;
    frame_of_moment_nextopen_ = 60;
}

void EnemyVesta::processBehavior() {
    //ボーンにあたるアクターのメモ
    //_X, _Y, _Z, _RX, _RY, _RZ について２つの座標系セットを切り替えが必要な仕様です。
    //それぞれローカル座標、最終（絶対）座標と呼ぶことにします。
    //・最終（絶対）座標 ・・・ 普通のワールド座標系の事です。
    //・ローカル座標     ・・・ 親アクターの基点(0,0,0)からの相対的な座標系を意味します。
    //                          座標計算はこちらで行って下さい。
    //＜方針＞
    //  �@座標計算は主にローカル座標系の計算である。GgafDxKurokoA でローカル座標系の操作を行うこととする。
    //    しかし、８分木登録や、当たり判定や、ターゲット座標など、他のオブジェクトからワールド座標を参照する等、
    //    基本状態は最終（絶対）座標系。
    //    processBehavior()開始時は 最終（絶対）座標系(changeGeoFinal())の状態とする。
    //  �AprocessBehavior()内で必要に応じて changeGeoLocal() でメンバー _X, _Y, _Z, _RX, _RY, _RZ をローカル座標系に
    //    切り替えることが可能。移動等の座標計算を行う。
    //  �B但し processBehavior() を抜ける際には必ず最終座標(changeGeoFinal())の状態に戻しておく事。
    //  �C最終（絶対）座標と、ローカル座標は互いに独立し、干渉はしないが、
    //    表示時のワールド変換行列作成時、行列積で合成され、最終的な表示位置が決定する。

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
    //・_X, _Y, _Z    ・・・ 毎フレーム GgafDxGeometricActor::processSettlementBehavior() で計算され自動更新されてます。
    //                       processBehavior() で changeGeoFinal() を行うと、１フレーム前の_X, _Y, _Zに切り替わる事になります。
    //                       _X, _Y, _Z は参照専用。値を代入しても意味が有りません
    //・_RX, _RY, _RZ ・・・ 毎フレーム GgafDxGeometricActor::processSettlementBehavior() 自動代入されません！
    //                       changeGeoFinal(); を実行しても、_RX, _RY, _RZ は以前の最終（絶対）座標系の値が
    //                       入りっぱなしで変化しません。
    //                       他のオブジェクトから、ボーンにあたるアクターを参照するとき、_RX, _RY, _RZは全く信用できません。

    //＜注意＞
    //・GgafDxKurokoA(_pKurokoA)の behave() 以外メソッドは、常にローカル座標の操作とする。
    //  behave()以外メソッドは実際に座標計算しているわけではないので、
    //  changeGeoFinal()時、changeGeoLocal()時に関係なく、呼び出し可能。
    //・GgafDxKurokoA(_pKurokoA)の behave() メソッドは座標を１フレーム後の状態にする計算を行う。
    //  したがって、次のように ローカル座標時(changeGeoLocal()時)で呼び出す事とする。
    //    changeGeoLocal();
    //    _pKurokoA->behave();
    //    changeGeoFinal();
    //TODO:混在感をもっとなくす。

    switch (iMovePatternNo_) {
        case VESTA_HATCH_CLOSED:
            if (getActivePartFrame() == frame_of_moment_nextopen_-(frame_of_morph_interval_/2)) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_VESTA_HATCH_OPENED,
                                                1.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, -3000);
            }
            if (getActivePartFrame() == frame_of_moment_nextopen_) {
                frame_of_moment_nextclose_ = getActivePartFrame() + frame_of_close_interval_;
                iMovePatternNo_ = VESTA_HATCH_OPENED;
            }
            break;
        case VESTA_HATCH_OPENED:
            if (getActivePartFrame() == frame_of_moment_nextclose_ - (frame_of_morph_interval_/2)) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_VESTA_HATCH_OPENED,
                                                0.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, 0);
            }
            if (getActivePartFrame() == frame_of_moment_nextclose_) {
                frame_of_moment_nextopen_ = getActivePartFrame() + frame_of_open_interval_;
                iMovePatternNo_ = VESTA_HATCH_CLOSED;
            }
            break;
        default :
            break;
    }
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //オープン時敵出現
    if (iMovePatternNo_ == VESTA_HATCH_OPENED) {
        int openningFrame = getActivePartFrame() - frame_of_moment_nextopen_; //開いてからのフレーム数。
        //frame_of_moment_nextopen_は、ここの処理の時点では直近でオープンしたフレームとなる。
        if (openningFrame % (int)(R_EnemyVesta_ShotInterval) == 0) {
            if (pDepo_Fired_) {
                GgafDxDrawableActor* pActor = (GgafDxDrawableActor*)pDepo_Fired_->dispatch();
                if (pActor) {
                    pActor->locatedBy(this);
                    pActor->_pKurokoA->relateFaceAngWithMvAng(true);
                    //＜現在の最終的な向きを、RzRyで取得する＞
                    //方向ベクトルはワールド変換行列の積（_matWorldRotMv)で変換され、現在の最終的な向きに向く。
                    //元の方向ベクトルを(Xorg_,Yorg_,Zorg_)、
                    //ワールド変換行列の回転部分の積（_matWorldRotMv)の成分を mat_xx、
                    //最終的な方向ベクトルを(vX, vY, vZ) とすると
                    //
                    //                      | mat_11 mat_12 mat_13 |
                    //| Xorg_ Yorg_ Zorg_ | | mat_21 mat_22 mat_23 | = | vX vY vZ |
                    //                      | mat_31 mat_32 mat_33 |
                    //
                    //vX = Xorg_*mat_11 + Yorg_*mat_21 + Zorg_*mat_31
                    //vY = Xorg_*mat_12 + Yorg_*mat_22 + Zorg_*mat_32
                    //vZ = Xorg_*mat_13 + Yorg_*mat_23 + Zorg_*mat_33
                    //
                    //さてここで、元々が前方の単位方向ベクトル(1,0,0)の場合はどうなるか考えると
                    //
                    //vX = Xorg_*mat_11
                    //vY = Xorg_*mat_12
                    //vZ = Xorg_*mat_13
                    //
                    //となる。本アプリでは、モデルは全て(1,0,0)を前方としているため
                    //最終的な方向ベクトルは（Xorg_*mat_11, Xorg_*mat_12, Xorg_*mat_13) である。
                    angle Rz, Ry;
                    GgafDxUtil::getRzRyAng(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13,
                                            Rz, Ry); //現在の最終的な向きを、RzRyで取得！
                    pActor->_pKurokoA->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->reset();
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
        D3DXMATRIX* pBaseInvMatRM = _pActor_Base->getInvMatWorldRotMv();
        //ローカル座標でのターゲットとなる方向ベクトル計算
        int TvX = MvX*pBaseInvMatRM->_11 + MvY*pBaseInvMatRM->_21 + MvZ * pBaseInvMatRM->_31;
        int TvY = MvX*pBaseInvMatRM->_12 + MvY*pBaseInvMatRM->_22 + MvZ * pBaseInvMatRM->_32;
        int TvZ = MvX*pBaseInvMatRM->_13 + MvY*pBaseInvMatRM->_23 + MvZ * pBaseInvMatRM->_33;
        //自動方向向きシークエンス開始
        angle angRz_Target, angRy_Target;
        GgafDxUtil::getRzRyAng(TvX, TvY, TvZ,
                                angRz_Target, angRy_Target);
        _pKurokoA->execTurnMvAngSequence(angRz_Target, angRy_Target,
                                           1000, 0,
                                           TURN_CLOSE_TO);
    }

    _pScaler->behave();
    _pMorpher->behave();
    //_pSeTx->behave();

    //_pKurokoAの計算はローカルで行う
    changeGeoLocal();
    _pKurokoA->behave();
    changeGeoFinal();

}

void EnemyVesta::processJudgement() {
    if (_pActor_Base != NULL && _pActor_Base->isActiveInTheTree()) {
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

    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);

    if (pExplo001) {
        pExplo001->locatedBy(this);
    }

    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        _pSeTx->play3D(0);
        sayonara();

        //アイテム出現
        Item* pItem = employFromCommon(MagicPointItem001);
        if (pItem) {
            pItem->locatedBy(this);
        }
    }
}

void EnemyVesta::onInactive() {
    sayonara();
}

EnemyVesta::~EnemyVesta() {
    pDpcon_->close();
}

#include "stdafx.h"
#include "EnemyRomulus.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_HATCH_OPEN 1

EnemyRomulus::EnemyRomulus(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Romulus", STATUS(EnemyRomulus)) {
    _class_name = "EnemyRomulus";
    _pActor_Base = nullptr;
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 20*60;
    frame_of_morph_interval_   = 120;

    pDepo_Fired_ = nullptr;
    pDepoConnection_ = connectToDepositoryManager("Atalante");

    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_HATCH_OPEN);
}

void EnemyRomulus::onCreateModel() {
    _pModel->_pTexBlinker->setBlinkableRange(0.9, 0.1, 1.0);
    _pModel->_pTexBlinker->setPower(0.1);
    _pModel->_pTexBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyRomulus::initialize() {
    setHitAble(true);
    _pKurokoA->relateMvFaceAng(true);
    _pMorpher->forceWeightRange(MORPHTARGET_HATCH_OPEN, 0.0f, 1.0f);
    _pMorpher->setWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 200000);
    _pScaler->setScale(1000);
    _pScaler->forceRange(1000, 1200);
    _pScaler->beat(30, 5, 5, -1);
    pDepo_Fired_ = pDepoConnection_->peek();
}

void EnemyRomulus::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    is_open_hatch_ = false;
//    frame_of_moment_nextopen_ = frame_of_close_interval_;
    _pProg->reset(PROG_HATCH_CLOSE);
}

void EnemyRomulus::processBehavior() {
    //ボーンにあたるアクターのメモ
    //_X, _Y, _Z, _RX, _RY, _RZ について２つの座標系セットを切り替えが必要な仕様です。
    //それぞれローカル座標、最終（絶対）座標と呼ぶことにします。
    //・最終（絶対）座標 ・・・ 普通のワールド座標系の事です。
    //・ローカル座標     ・・・ 親アクターの基点(0,0,0)からの相対的な座標系を意味します。
    //                          座標計算はこちらで行って下さい。
    //＜方針＞
    //  ①座標計算は主にローカル座標系の計算である。GgafDxKurokoA でローカル座標系の操作を行うこととする。
    //    しかし、８分木登録や、当たり判定や、ターゲット座標など、他のオブジェクトからワールド座標を参照する等、
    //    基本状態は最終（絶対）座標系。
    //    processBehavior()開始時は 最終（絶対）座標系(changeGeoFinal())の状態となっている。
    //  ②processBehavior()内で必要に応じて changeGeoLocal() でメンバー _X, _Y, _Z, _RX, _RY, _RZ をローカル座標系に
    //    切り替えることが可能。移動等の座標計算を行う。
    //  ③但し processBehavior() を抜ける際には必ず最終座標(changeGeoFinal())の状態に戻しておく事。
    //  ④最終（絶対）座標と、ローカル座標は互いに独立し、干渉はしないが、
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

    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->change(PROG_HATCH_CLOSE);
            break;
        }
        case PROG_HATCH_CLOSE: {
            if (_pProg->isJustChanged()) {
                _pMorpher->morphLinerUntil(MORPHTARGET_HATCH_OPEN,
                                                0.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, -3000);
            }

            //次へ
            if (_pProg->getFrameInProgress() >= frame_of_close_interval_ + frame_of_morph_interval_) {
                _pProg->change(PROG_HATCH_OPEN);
            }
            break;
        }
        case PROG_HATCH_OPEN: {
            if (_pProg->isJustChanged()) {
                _pMorpher->morphLinerUntil(MORPHTARGET_HATCH_OPEN,
                                                1.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, 0);
            }

            //オープン時敵出現処理
            if (_pMorpher->_weight[MORPHTARGET_HATCH_OPEN] > 0.5) { //モーションが半分以上まで到達したなら
                if (_pProg->getFrameInProgress() % (frame)(RF_EnemyRomulus_ShotInterval(G_RANK)) == 0) { //出現間隔
                    if (pDepo_Fired_) {
                        GgafDxDrawableActor* pActor = (GgafDxDrawableActor*)pDepo_Fired_->dispatch();
                        if (pActor) {
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
                            UTIL::convVectorToRzRy(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13,
                                                   Rz, Ry); //現在の最終的な向きを、RzRyで取得！
                            pActor->_pKurokoA->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                            pActor->locateAs(this);
                            pActor->reset();
                        }
                    }
                }
            }
            if (_pProg->getFrameInProgress() >= frame_of_open_interval_+ frame_of_morph_interval_) {
                _pProg->change(PROG_HATCH_CLOSE);
            }
            break;
        }
        default :
            break;
    }
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    if (getActiveFrame() % 10 == 0                   && 1 == 2) {
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
        UTIL::convVectorToRzRy(TvX, TvY, TvZ, angRz_Target, angRy_Target);
        _pKurokoA->turnRzRyMvAngTo(angRz_Target, angRy_Target,
                                   1000, 0,
                                   TURN_CLOSE_TO, false);
    }

    _pScaler->behave();
    _pMorpher->behave();

    //_pKurokoAの計算はローカルで行う
    changeGeoLocal();
    _pKurokoA->behave();
    changeGeoFinal();

}

void EnemyRomulus::processJudgement() {
    if (_pActor_Base != nullptr && _pActor_Base->isActiveInTheTree()) {
//        (*(_pActor_Base->_pFunc_calcRotMvWorldMatrix))(_pActor_Base, _matWorld);
    } else {
        //土台がなければ自分も死ぬ
        sayonara();
    }


//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void EnemyRomulus::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyRomulus::onInactive() {
    sayonara();
}

EnemyRomulus::~EnemyRomulus() {
    pDepoConnection_->close();
}

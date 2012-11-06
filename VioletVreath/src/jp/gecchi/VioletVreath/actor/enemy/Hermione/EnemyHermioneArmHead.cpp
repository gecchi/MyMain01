#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_HATCH_OPEN 1

EnemyHermioneArmHead::EnemyHermioneArmHead(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "HermioneArmHead", STATUS(EnemyHermioneArmHead)) {
    _class_name = "EnemyHermioneArmHead";
    _pActor_Base = NULL;
    pDpcon_ = connectToDepositoryManager("Conn_Shot004", NULL); //弾
    pDepo_Fired_ = pDpcon_->fetch();
    aim_ang_velo_ = 0;
    aim_movable_limit_ang_ = 0;

    _pSeTxer->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_EXPLOSION, "bomb1"   , GgafRepeatSeq::nextVal("CH_bomb1"));
    useProgress(10);
}

void EnemyHermioneArmHead::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
}

void EnemyHermioneArmHead::initialize() {
    setHitAble(true);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(1000, 1200);
    _pScaler->beat(30, 5, 5, -1);
}

void EnemyHermioneArmHead::onActive() {
    _pStatus->reset();
//    frame_of_moment_nextopen_ = frame_of_close_interval_;
    _pProg->set(PROG_INIT);
}

void EnemyHermioneArmHead::processBehavior() {
    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->change(PROG_AIMING);
            break;
        }
        case PROG_AIMING: {
            if (_pProg->hasJustChanged() ) {
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
                MyShip* pMyShip = P_MYSHIP;
                int MvX = pMyShip->_X - _X; //ここでの _X, _Y, _Z は絶対座標であることがポイント
                int MvY = pMyShip->_Y - _Y;
                int MvZ = pMyShip->_Z - _Z;
                //逆行列取得
                D3DXMATRIX* pBaseInvMatRM = _pActor_Base->getInvMatWorldRotMv();
                //ローカル座標でのターゲットとなる方向ベクトル計算
                int TvX = MvX*pBaseInvMatRM->_11 + MvY*pBaseInvMatRM->_21 + MvZ * pBaseInvMatRM->_31;
                int TvY = MvX*pBaseInvMatRM->_12 + MvY*pBaseInvMatRM->_22 + MvZ * pBaseInvMatRM->_32;
                int TvZ = MvX*pBaseInvMatRM->_13 + MvY*pBaseInvMatRM->_23 + MvZ * pBaseInvMatRM->_33;
                //自動方向向きシークエンス開始
                angle angRz_Target, angRy_Target;
                UTIL::getRzRyAng(TvX, TvY, TvZ,
                                 angRz_Target, angRy_Target);
                //計算の結果、angRz_Target angRy_Target に向けば、自機に向ける

                //angRz_Target、angRy_Target 可動範囲内に制限する
                if (aim_movable_limit_ang_ <= angRz_Target && angRz_Target <= D180ANG) {
                    angRz_Target = aim_movable_limit_ang_;
                } else if (D180ANG <= angRz_Target && angRz_Target <= D360ANG - aim_movable_limit_ang_) {
                    angRz_Target = D360ANG - aim_movable_limit_ang_;
                }
                if (aim_movable_limit_ang_ <= angRy_Target && angRy_Target <= D180ANG) {
                    angRy_Target = aim_movable_limit_ang_;
                } else if (D180ANG <= angRy_Target && angRy_Target <= D360ANG - aim_movable_limit_ang_) {
                    angRy_Target = D360ANG - aim_movable_limit_ang_;
                }
                _pKurokoA->execTurnMvAngSequence(angRz_Target, angRy_Target,
                                                 aim_ang_velo_, 0,
                                                 TURN_CLOSE_TO);

            }
            if (_pKurokoA->isRunnigTurnMvAngSequence()) {
                // 待機
            } else {
                _pProg->change(PROG_NOTHING);
            }
            break;
        }
        case PROG_NOTHING: {
            _pProg->change(PROG_AIMING);
            break;
        }
        default :
            break;
    }

    //＜注意＞
    //・GgafDxKurokoA(_pKurokoA)の behave() 以外メソッドは、常にローカル座標の操作とする。
    //  behave()以外メソッドは実際に座標計算しているわけではないので、
    //  changeGeoFinal()時、changeGeoLocal()時に関係なく、呼び出し可能。
    //・GgafDxKurokoA(_pKurokoA)の behave() メソッドは座標を１フレーム後の状態にする計算を行う。
    //  したがって、次のように ローカル座標時(changeGeoLocal()時)で呼び出す事とする。
    //    changeGeoLocal();
    //    _pKurokoA->behave();
    //    changeGeoFinal();
    changeGeoLocal();
    _pKurokoA->behave();
    changeGeoFinal();


    if (_pProg->getFrameInProgress() % 20 == 0) { //出現間隔
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
            UTIL::getRzRyAng(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13,
                             Rz, Ry); //現在の最終的な向きを、RzRyで取得！
            pActor->_pKurokoA->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
            pActor->locateWith(this);
            pActor->reset();
        }
    }

}

void EnemyHermioneArmHead::processJudgement() {
    if (_pActor_Base != NULL && _pActor_Base->isActiveInTheTree()) {
    } else {
        //土台がなければ自分も死ぬ
        sayonara();
    }
}

void EnemyHermioneArmHead::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//
//    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
//        setHitAble(false);
//        //爆発効果
//        UTIL::activateExplosionEffectOf(this);
//        _pSeTxer->play3D(SE_EXPLOSION);
//
//        //自機側に撃たれて消滅の場合、
//        if (pOther->getKind() & KIND_MY) {
//            //アイテム出現
//            UTIL::activateItemOf(this);
//        }
//        sayonara();
//    } else {
//        //非破壊時
//        effectFlush(2); //フラッシュ
//        _pSeTxer->play3D(SE_DAMAGED);
//    }
}

void EnemyHermioneArmHead::onInactive() {
    sayonara();
}

EnemyHermioneArmHead::~EnemyHermioneArmHead() {
    pDpcon_->close();
}

#include "stdafx.h"
#include "MyOption.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/util/GgafDxQuaternion.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "MyOptionWateringLaserChip001.h"
#include "EffectMyOption.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShot001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoController.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

//MyOption::MyOption(const char* prm_name, uint32_t prm_no, MyOptionController* prm_pOptCtrler) : DefaultMorphMeshActor(prm_name, "4/Eres") {
//MyOption::MyOption(const char* prm_name, uint32_t prm_no, MyOptionController* prm_pOptCtrler) : CubeMapMeshSetActor(prm_name, "4/Core4cm_") {
MyOption::MyOption(const char* prm_name, uint32_t prm_no, MyOptionController* prm_pOptCtrler) :
        DefaultMeshSetActor(prm_name, "8/CORE4", STATUS(MyOption)) {

    _TRACE_("MyOption::MyOption("<<prm_name<<","<<prm_no<<")");
    _class_name = "MyOption";
    pOptionCtrler_ = prm_pOptCtrler;
    no_ = prm_no;
    angveloMove_ = 0;//旋廻移動角速度（読み出し専用）

    angPosition_ = 0;     //円周上初期位置角度（周囲角）（上書き初期設定可）
    veloMv_ = 5000;     //旋廻移動速度（上書き初期設定可）
    angExpanse_ = 0;      //オプションの広がり角の回転角（上書き初期設定可）

    adjust_angPos_seq_progress_ = 0;
    adjust_angPos_seq_new_angPosition_base_ = angPosition_;
    adjust_angPos_seq_spent_frame_ = 0;

    angPosition_base_ = angPosition_;
    radiusPosition_base_ = 150000; //旋廻半径距離（上書き初期設定可）
    radiusPosition_= radiusPosition_base_;
    radiusPosition_stopping_ = radiusPosition_base_;
    radiusPosition_velo_ = 3000 * (radiusPosition_base_/60000);

    angExpanse_default_ = angExpanse_;
    veloMv_base_ = veloMv_;

    return_to_base_radiusPosition_seq_ = false;
    return_to_base_angExpanse_seq_ = false;

    angveloExpanseNomal_ = 3000;
    angveloExpanseSlow_ = 1000;

    x_org_ = _x;
    y_org_ = _y;
    z_org_ = _z;

    //TODO::EffectMyOption
    pEffect_ = NEW EffectMyOption("EffectMyOption", this);
    addSubGroup(pEffect_);

    //レーザー発射エフェクト
//    pEffect_LaserIrradiate_ = NEW EffectLockon001_Main("OP_Eff_Ref");
//    pEffect_LaserIrradiate_->inactivate();
//    addSubGroup(pEffect_LaserIrradiate_);
    pEffect_LaserIrradiate_ = nullptr;
    pLaserChipDepo_ = NEW LaserChipDepository("ROTLaser");
    MyOptionWateringLaserChip001* pChip;
//    MyOptionStraightLaserChip001* pChip;
    for (int i = 0; i < 80; i++) { //レーザーストック
        std::string name = std::string(getName()) + "'s LaserChip(" + XTOS(i) + ")";
        pChip = NEW MyOptionWateringLaserChip001(name.c_str());
        //pChip = NEW MyOptionStraightLaserChip001(name2.c_str());
        //MyOptionStraightLaserChip001の場合以下が必要
        //ストレート用
//        pChip->setSource(this);
//        pChip->pSource_vX_ = &Q._x;
//        pChip->pSource_vY_ = &Q._y;
//        pChip->pSource_vZ_ = &Q._z;

        pLaserChipDepo_->put(pChip);
    }
    pLaserChipDepo_->config(80, 25, pEffect_LaserIrradiate_);
    addSubGroup(pLaserChipDepo_);

    pDepo_MyShots001_ = NEW GgafActorDepository("RotShot001");
    for (int i = 0; i < 25; i++) { //自弾ストック
        std::string name = std::string(getName()) + "'s Shot001(" + XTOS(i) + ")";
        pDepo_MyShots001_->put(NEW MyShot001(name.c_str()));
    }
    addSubGroup(pDepo_MyShots001_);

    //ロックオンコントローラー
    pLockonCtrler_ = NEW MyLockonController("LockonController");
    addSubGroup(pLockonCtrler_);

    //フォトンコントローラー
    pTorpedoCtrler_ = NEW MyTorpedoController("TorpedoController", this, pLockonCtrler_);
    addSubGroup(pTorpedoCtrler_);
    _pSeTx->set(SE_FIRE_LASER,   "WAVE_MY_FIRE_LASER_002");
    _pSeTx->set(SE_FIRE_SHOT,    "WAVE_MY_FIRE_SHOT_002");
    _pSeTx->set(SE_FIRE_TORPEDO, "WAVE_MY_FIRE_TORPEDO_002");
    //prepareSe(0,"bse5", GgafRepeatSeq::nextVal("CH_bse5"));
    need_adjust_pos_flg_ = false;
}

void MyOption::onCreateModel() {
//    _pModel->_pTexBlinker->setBlinkableRange(0.9, 0.3, 2.0);
//    _pModel->_pTexBlinker->setPower(1.0);
//    _pModel->_pTexBlinker->beat(120, 10, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void MyOption::initialize() {
    _sx=_sy=_sz=100;
}

void MyOption::onReset() {
    angveloMove_ = ((1.0f*veloMv_ / radiusPosition_)*(double)D180ANG)/PI;
    _pKurokoA->setMvVelo(veloMv_);
    _pKurokoA->setRzMvAng(angPosition_+D90ANG);
    _pKurokoA->setRyMvAng(-D90ANG);
    _pKurokoA->setRzMvAngVelo(angveloMove_);//∵半径Ｒ＝速度Ｖ／角速度ω
    _pKurokoA->setRyMvAngVelo(0);//∵半径Ｒ＝速度Ｖ／角速度ω
    _z = ANG_COS(angPosition_)*radiusPosition_; //X軸中心回転なのでXYではなくてZY
    _y = ANG_SIN(angPosition_)*radiusPosition_; //X軸の正の方向を向いて時計回りに配置
                                                //ワールド変換の（左手法）のX軸回転とはと逆の回転なので注意
    _x = 0;
    _pKurokoA->setFaceAngVelo(AXIS_X, 4000);
    //ローカル座標系を、(x_org_,y_org_,z_org_) へ退避
    x_org_ = _x;
    y_org_ = _y;
    z_org_ = _z;
    angPosition_ = _pKurokoA->_angRzMv;

    adjust_angPos_seq_progress_ = 0;
    adjust_angPos_seq_new_angPosition_base_ = angPosition_;
    adjust_angPos_seq_spent_frame_ = 0;

    radiusPosition_stopping_ = radiusPosition_base_;
}

void MyOption::onActive() {
    //レーザーやロックンターゲットや魚雷がサブにいるため
    //個別に呼び出す
    pLockonCtrler_->onActive();
    pTorpedoCtrler_->onActive();
}

void MyOption::addRadiusPosition(int prm_radius_offset, int prm_min_radius, int prm_max_radius) {
    //    _x = x_org_;
    //    _y = y_org_;
    //    _z = z_org_;
    //より後
    //    x_org_ = _x;
    //    y_org_ = _y;
    //    z_org_ = _z;
    //より前
    //でしか呼び出してはいけません。


//負の半径も許す場合は如何のロジックのコメントを外す
//    int radius;
//    if (radiusPosition_ == -1 * prm_radius_offset) { //差分を加えると0になる場合
//        //半径は0にしてはいけない。0割り算を避けるため
//        if (radiusPosition_ > 0) {
//            radius = -100;
//        } else {
//            radius = 100;
//        }
//    } else {
//        radius = radiusPosition_ + prm_radius_offset;
//    }
//    setRadiusPosition(radius);

    int radius;
    radius = radiusPosition_ + prm_radius_offset;
    if (radius < prm_min_radius) {
        radius = prm_min_radius; //オプション最低半径距離
    } else if (radius > prm_max_radius) {
        radius = prm_max_radius; //オプション最低半径距離
    }

    setRadiusPosition(radius);
}


void MyOption::setRadiusPosition(int prm_radius) {
//    _x = x_org_;
//    _y = y_org_;
//    _z = z_org_;
//より後
//    x_org_ = _x;
//    y_org_ = _y;
//    z_org_ = _z;
//より前
//でしか呼び出してはいけません。
    radiusPosition_ = prm_radius;
    if (radiusPosition_ == -1  || radiusPosition_ == 0 || radiusPosition_ == 1) {
        _z = _y = 0;
        _pKurokoA->setRzMvAng(D90ANG);
        angveloMove_ = 0;
        _pKurokoA->setRzMvAngVelo(angveloMove_);
        return;

    }

    angle angZY_ROTANG_x;
    if (radiusPosition_ > 0) {
        angZY_ROTANG_x = UTIL::getAngle2D(_z, _y); //自分の位置
        _z = radiusPosition_ * ANG_COS(angZY_ROTANG_x);
        _y = radiusPosition_ * ANG_SIN(angZY_ROTANG_x);
    } else {
        angZY_ROTANG_x = UTIL::getAngle2D(-_z, -_y); //自分の位置
        _z = radiusPosition_ * ANG_COS(angZY_ROTANG_x);
        _y = radiusPosition_ * ANG_SIN(angZY_ROTANG_x);
    }
    //もしprm_lenが0の場合、理論的には元の位置に戻るはずなのだが、
    //誤差丸め込みのため、微妙に位置が変わる。
    //よって、移動方角、移動角速度を現在の位置(_z,_y)で再設定しなければズレる。
    _pKurokoA->setRzMvAng(angZY_ROTANG_x + D90ANG);
    angveloMove_ = ((1.0*veloMv_ / radiusPosition_)*(double)D180ANG)/PI;
    _pKurokoA->setRzMvAngVelo(angveloMove_);
}


void MyOption::adjustAngPosition(angle prm_new_angPosition_base, frame prm_spent_frame) {
    adjust_angPos_seq_progress_ = 1;
    adjust_angPos_seq_new_angPosition_base_ = UTIL::simplifyAng(prm_new_angPosition_base);
    adjust_angPos_seq_spent_frame_ = prm_spent_frame + 1;
}



void MyOption::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    VirtualButton* pVbPlay = VB_PLAY;
    GgafDxKurokoA* const pKurokoA = _pKurokoA;
    //処理メイン

    //退避していたローカル座標系を、(x_org_,y_org_,z_org_) を
    //_pKurokoAのメソッドを利用するため、(_x,_y,_z)へコピー
    //これ以降processBehavior()内の(_x,_y,_z)はローカル座標系
    _x = x_org_;
    _y = y_org_;
    _z = z_org_;

    if (return_to_base_radiusPosition_seq_) {
        //半径ポジション自動戻り中
        if (radiusPosition_ == radiusPosition_base_) {
            //kk
            return_to_base_radiusPosition_seq_ = false;
        } else if (radiusPosition_ > radiusPosition_base_) {
            addRadiusPosition(-10000, radiusPosition_base_);
        } else if (radiusPosition_ < radiusPosition_base_) {
            addRadiusPosition(10000, 1, radiusPosition_base_);
        }

        radiusPosition_stopping_ = radiusPosition_base_;
    } else {

        //オプション独立移動制御時
        if (pVbPlay->isBeingPressed(VB_OPTION) && pOptionCtrler_->is_handle_move_mode_) {
            //オプションの広がり角より、オプション移動速度と、旋回半径増加速度にベクトル分解。
            //そのうちの旋回半径増加速度のみを設定。
            addRadiusPosition(ANG_SIN(angExpanse_) * pOptionCtrler_->veloOptionsMv_);
            //オプション移動速度の処理はMyOptionクラスで行う。
        }
    }

    if (return_to_base_angExpanse_seq_) {
        //オプション広がり自動戻り中
        if (angExpanse_ > angExpanse_default_) {
            angExpanse_ -= 2000;
        }
        if (angExpanse_ < angExpanse_default_) {
            angExpanse_ += 2000;
        }
        if (-2000 <= angExpanse_default_-angExpanse_ && angExpanse_default_-angExpanse_ <= 2000) {
            angExpanse_ = angExpanse_default_;
            return_to_base_angExpanse_seq_ = false;
        }
        angExpanse_ = UTIL::simplifyAng(angExpanse_);
    } else {
        //オプション広がりと向き制御
        if (pVbPlay->isBeingPressed(VB_OPTION) && pVbPlay->isBeingPressed(VB_TURBO)) {
            int pos_camera = P_VAM->pos_camera_;
            if (pos_camera == VAM_POS_RIGHT) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    addRadiusPosition(radiusPosition_velo_);
                    radiusPosition_stopping_ += radiusPosition_velo_;
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-radiusPosition_velo_);
                    radiusPosition_stopping_ -= radiusPosition_velo_;
                    //angExpanse_ -= angveloExpanseSlow_;
                }
            } else if (pos_camera == VAM_POS_LEFT) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    addRadiusPosition(radiusPosition_velo_);
                    radiusPosition_stopping_ += radiusPosition_velo_;
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-radiusPosition_velo_);
                    radiusPosition_stopping_ -= radiusPosition_velo_;
                    //angExpanse_ -= angveloExpanseSlow_;
                }
            } else if (pos_camera == VAM_POS_TOP) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    addRadiusPosition(radiusPosition_velo_);
                    radiusPosition_stopping_ += radiusPosition_velo_;
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    addRadiusPosition(-radiusPosition_velo_);
                    radiusPosition_stopping_ -= radiusPosition_velo_;
                    //angExpanse_ -= angveloExpanseSlow_;
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
            } else if (pos_camera == VAM_POS_BOTTOM) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    addRadiusPosition(-radiusPosition_velo_);
                    radiusPosition_stopping_ -= radiusPosition_velo_;
                    //angExpanse_ -= angveloExpanseSlow_;
                }
                if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    addRadiusPosition(radiusPosition_velo_);
                    radiusPosition_stopping_ += radiusPosition_velo_;
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
            } else if (pos_camera > VAM_POS_TO_BEHIND) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    addRadiusPosition(radiusPosition_velo_);
                    radiusPosition_stopping_ += radiusPosition_velo_;
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-radiusPosition_velo_);
                    radiusPosition_stopping_ -= radiusPosition_velo_;
                    //angExpanse_ -= angveloExpanseSlow_;
                }
            }

            if (radiusPosition_stopping_ < OPT_RADIUS_POS_MIN) {
                radiusPosition_stopping_ = OPT_RADIUS_POS_MIN;
            }
            if (radiusPosition_stopping_ > OPT_RADIUS_POS_MAX) {
                radiusPosition_stopping_ = OPT_RADIUS_POS_MAX;
            }
            angExpanse_ = UTIL::simplifyAng(angExpanse_);
        } else {
            if (pOptionCtrler_->is_free_from_myship_mode_) {
                //
            } else {
                GgafDxGeoElem* pGeoOpCtrl = pOptionCtrler_->pRing_OptCtrlGeoHistory_->getPrev();
                if (pVbPlay->isBeingPressed(VB_OPTION)) {
                    //オプションボタン押下時は
                    //radiusPositionをいじらない
                } else if (pGeoOpCtrl->x == pOptionCtrler_->_x &&
                           pGeoOpCtrl->y == pOptionCtrler_->_y &&
                           pGeoOpCtrl->z == pOptionCtrler_->_z )
                {
                    //オプションコントローラー非移動時、
                    //元の軌道に戻るために半径座標を増やす。
                    if (!pMyShip->is_trace_waiting_) {
                        if (radiusPosition_stopping_ == radiusPosition_) {
                            //kk
                        } else if (radiusPosition_stopping_ > radiusPosition_) {
                            addRadiusPosition(+2000, 1, radiusPosition_stopping_);
                        } else if (radiusPosition_stopping_ < radiusPosition_) {
                            addRadiusPosition(-2000, radiusPosition_);
                        }
                        if (veloMv_ == veloMv_base_) {

                        } else {
                            veloMv_ += 100;
                            if (veloMv_ >= veloMv_base_) {
                                if (need_adjust_pos_flg_) { //位置の再設定要求あり
                                    MyOptionController::adjustDefaltAngPosition(radiusPosition_stopping_ / 1000);
                                    need_adjust_pos_flg_ = false;
                                }
                                veloMv_ = veloMv_base_;
                            }
                        }
                    } else {
                        //トレースちょっと待ち
                    }
                } else {
                    //オプションコントローラーが移動時、
                    //オプションコントローラーに向かっていくように、半径座標を減らす。
                    if (1 < radiusPosition_) {
                        addRadiusPosition(-3000, 1);
                    }
                    if (radiusPosition_ < 10000) { //かなり半径が小さくなってしまった場合
                        need_adjust_pos_flg_ = true; //非移動時に位置の再設定要求（↑を見よ）
                    }

                    veloMv_ -= 200;
                    if (veloMv_ < 0) {
                        veloMv_ = 0;
                    }
                }
            }
        }
    }

    if (adjust_angPos_seq_progress_ > 0) {
        if (adjust_angPos_seq_progress_ == 1) {
            //初期処理
            adjust_angPos_seq_progress_ = 2;
        }

        if (adjust_angPos_seq_progress_ == 2) {
            angle angPosition_now;
            //自分の角度位置取得
            if (radiusPosition_ > 0) {
                angPosition_now = UTIL::getAngle2D(_z, _y);
            } else {
                angPosition_now = UTIL::getAngle2D(-_z, -_y);
            }
            //現在の角距離
            angle ang_diff = UTIL::getAngDiff(angPosition_now, adjust_angPos_seq_new_angPosition_base_, SGN(veloMv_));
            if (ABS(ang_diff) > D_ANG(350)) {
                ang_diff = UTIL::getAngDiff(angPosition_now, adjust_angPos_seq_new_angPosition_base_, TURN_CLOSE_TO);
            }
            //残フレームと残移動角より必要な角速度
            angvelo angvelo_need = ang_diff / (angvelo)adjust_angPos_seq_spent_frame_;
            //必要な角速度差分
            angvelo angvelo_offset = angvelo_need - angveloMove_;
            //必要な角速度差分に対応する移動速度を求める
            velo veloMv_offset =  (2.0*PI*radiusPosition_ * angvelo_offset) / D360ANG;
            //速度設定
            pKurokoA->setRzMvAngVelo(angveloMove_ + angvelo_offset);
            pKurokoA->setMvVelo(veloMv_ + veloMv_offset);
            adjust_angPos_seq_spent_frame_--;

            if (adjust_angPos_seq_spent_frame_ == 0) {
                angPosition_base_ = adjust_angPos_seq_new_angPosition_base_;
                //誤差修正のため理想位置に再設定
                angveloMove_ = ((1.0*veloMv_ / radiusPosition_)*(double)D180ANG)/PI;
                pKurokoA->setMvVelo(veloMv_);
                pKurokoA->setRzMvAng(UTIL::simplifyAng(angPosition_base_ + D90ANG));
                pKurokoA->setRzMvAngVelo(angveloMove_);//∵半径Ｒ＝速度Ｖ／角速度ω
                _z = ANG_COS(angPosition_base_)*radiusPosition_; //X軸中心回転なのでXYではなくてZY
                _y = ANG_SIN(angPosition_base_)*radiusPosition_; //X軸の正の方向を向いて時計回りに配置
                _x = 0;
                adjust_angPos_seq_progress_ = 0;
            }
        }
    } else {
         //通常時
        pKurokoA->setMvVelo(veloMv_);
    }
    angPosition_ = UTIL::simplifyAng(angPosition_+angveloMove_);

    pKurokoA->behave();
    //pKurokoAを使って、(_x,_y,_z)ローカル座標系の計算ができたので、
    //(_x,_y,_z)のローカル座標系結果を、(x_org_,y_org_,z_org_) に上書きコピーで更新する。
    x_org_ = _x;
    y_org_ = _y;
    z_org_ = _z;

    //＜メモ＞
    //ここまでで、GgafDxKurokoAの機能のみで、
    //以下のような状態までもっていく。
    //(100,0,0) 辺りから原点を見たイメージ、自（MyOptionController）は原点
    //↑y軸  →z軸  ・x軸（奥から手前、手前が正）
    //
    //
    //              YZ平面に平行でぐるぐる回ってる。
    //        ←○
    //
    //
    //                    ↑
    //○        自        ○
    //↓     (0,0,0)      (-50000, 0, radiusPosition_)
    //
    //
    //          ○→
    //          (-50000, -1*radiusPosition_, 0)
    //
    //しかしまだ色々と回転したいため。あとは普通に計算（力技）で、座標回転、向き回転を行なう。
    //ダミーのアクターを連結しようとしたがいろいろ難しい、Quaternion を使わざるを得ない（のではないか；）。
    //TODO:最適化すべし、Quaternionは便利だが避けたい。いつか汎用化
    GgafDxKurokoA* const pOptionCtrler_pKurokoA = pOptionCtrler_->_pKurokoA;
    float sin_rz = ANG_SIN(pOptionCtrler_pKurokoA->_angFace[AXIS_Z]);
    float cos_rz = ANG_COS(pOptionCtrler_pKurokoA->_angFace[AXIS_Z]);
    float sin_ry = ANG_SIN(pOptionCtrler_pKurokoA->_angFace[AXIS_Y]);
    float cos_ry = ANG_COS(pOptionCtrler_pKurokoA->_angFace[AXIS_Y]);
    //全オプションを一つの塊としてOptionControllerを中心にWORLD変換のような旋廻
    coord X = cos_ry*cos_rz*x_org_ + cos_ry*-sin_rz*y_org_ + sin_ry*z_org_;
    coord Y = sin_rz*x_org_ + cos_rz*y_org_;
    coord Z = -sin_ry*cos_rz*x_org_ + -sin_ry*-sin_rz*y_org_ + cos_ry*z_org_;


    //懐中電灯の照射角が広がるような回転（Quaternionで実現）
    //＜メモ＞
    //ある座標(x, y, z)において、回転の軸が(α, β, γ)で、θ回す回転したあとの座標を求める。
    //P,Q,R を四元数（ベクトル表現）とおく、
    //P = (0; x, y, z)
    //Q = (cos(θ/2);  α sin(θ/2),  β sin(θ/2),  γ sin(θ/2))
    //R = (cos(θ/2); -α sin(θ/2), -β sin(θ/2), -γ sin(θ/2))
    //とした時、ハミルトン積
    //R P Q = (0; 答え)
    //が答えとなる

    //ある座標(x, y, z)＝方向ベクトル(pOptionCtrler_pKurokoA->_vX,pOptionCtrler_pKurokoA->_vY,pOptionCtrler_pKurokoA->_vZ)
    //回転軸  (α, β, γ)=(vX_axis, vY_axis, vZ_axis) 、
    //回転角θ= angExpanse_
    float vX_axis = cos_ry*cos_rz*pKurokoA->_vX + cos_ry*-sin_rz*pKurokoA->_vY + sin_ry*pKurokoA->_vZ;
    float vY_axis = sin_rz*pKurokoA->_vX + cos_rz*pKurokoA->_vY;
    float vZ_axis = -sin_ry*cos_rz*pKurokoA->_vX + -sin_ry*-sin_rz*pKurokoA->_vY + cos_ry*pKurokoA->_vZ;
    float sinHalf = ANG_SIN(angExpanse_/2); //angExpanse_=回転させたい角度
    float cosHalf = ANG_COS(angExpanse_/2);

    GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf); //R
    Q.mul(0,
          pOptionCtrler_pKurokoA->_vX,
          pOptionCtrler_pKurokoA->_vY,
          pOptionCtrler_pKurokoA->_vZ); //R*P 回転軸が現在の進行方向ベクトルとなる
    Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
    //Q._x, Q._y, Q._z が回転後の座標となる
    //Z軸回転、Y軸回転角度を計算
    UTIL::convVectorToRzRy(Q._x, Q._y, Q._z, _rz, _ry);

    //最終的にな(_x,_y,_z)に絶対座標系の座標値に更新。
    _x = X + pOptionCtrler_->_x;
    _y = Y + pOptionCtrler_->_y;
    _z = Z + pOptionCtrler_->_z;
    //ちなみにローカル座標系結果は、(x_org_,y_org_,z_org_)


    //レーザー発射。TODO:最適化
    if (pMyShip->is_shooting_laser_ && pVbPlay->isBeingPressed(VB_SHOT1)) {
        MyOptionWateringLaserChip001* pLaserChip = (MyOptionWateringLaserChip001*)pLaserChipDepo_->dispatch();
        if (pLaserChip) {
//            if (pLaserChipDepo_->_pEffectActor_Irradiate) {
//                pLaserChipDepo_->_pEffectActor_Irradiate->positionAs(this);
//            }
            //カーブ用
            int max_velo_renge = pLaserChip->max_velo_renge_;
            int r_max_acce = pLaserChip->r_max_acce_;
            velo veloVx = Q._x*max_velo_renge;
            velo veloVy = Q._y*max_velo_renge;
            velo veloVz = Q._z*max_velo_renge;
            pLaserChip->_pKurokoB->setVxyzMvVelo(veloVx, veloVy, veloVz);
            pLaserChip->_pKurokoB->setVxyzMvAcce(veloVx / r_max_acce,
                                                 veloVy / r_max_acce,
                                                 veloVz / r_max_acce );
            pLaserChip->_pKurokoB->behave();

            pLaserChip->positionAs(this);
            pLaserChip->_rz = _rz;
            pLaserChip->_ry = _ry;
            pLaserChip->pOrg_ = this;

            if (pLaserChip->_pChip_front == nullptr) {
                _pSeTx->play3D(SE_FIRE_LASER);
            }
        }
    } else {
        pLockonCtrler_->releaseAllLockon(); //ロックオン解除
    }

    //ショット発射
    if (pMyShip->just_shot_) {
        MyShot001* pShot = (MyShot001*)pDepo_MyShots001_->dispatch();
        if (pShot) {
            GgafDxKurokoA* const pShot_pKurokoA = pShot->_pKurokoA;
            _pSeTx->play3D(SE_FIRE_SHOT);
            pShot->positionAs(this);
            pShot_pKurokoA->setFaceAng(_rx, _ry, _rz);
            pShot_pKurokoA->setRzRyMvAng(_rz, _ry);
        }
    }
    //光子魚雷発射
    if (pVbPlay->isPushedDown(VB_SHOT2)) {
        if (pTorpedoCtrler_->fire()) {
            _pSeTx->play3D(SE_FIRE_TORPEDO);
        }
    }
//    _pSeTx->behave();

//    if (no_ == 3 ) {
//        if (_pKurokoA->_angveloRzMv == 0 || _pKurokoA->_angveloRzMv == 360000) {
//            if (veloMv_ == 1000) {
//                if (radiusPosition_ == 1) {
//                    _TRACE_(getBehaveingFrame()<<":before 遠ざかる成立！！！");
//                }
//            }
//
//        }
//        _TRACE_(getBehaveingFrame()<<":after  radiusPosition_="<<radiusPosition_<<" radiusPosition_stopping_="<<radiusPosition_stopping_<<" _angveloRzMv="<<(_pKurokoA->_angveloRzMv)<<" veloMv_="<<veloMv_);
//    }

}

void MyOption::processJudgement() {
}

void MyOption::onInactive() {
    //レーザーやロックンターゲットや魚雷がサブにいるため
    //個別に呼び出す
    pLockonCtrler_->onInactive();
    pTorpedoCtrler_->onInactive();
    //pLaserChipDepo_->reset();
}

void MyOption::onHit(GgafActor* prm_pOtherActor) {
    sayonara();
}

MyOption::~MyOption() {
}



//オブションについて備忘録2013/10/21
//自機(MyShip) -> オプションコントローラー(MyOptionController) x 9
//                       それぞれのコントローラーに オプション(MyOption)
//＜基本動作＞
//自機はグラディウスオプショントレースの動きをオプションコントローラーについて行っている。
//オプションは、オプションコントローラーの(0,0,0)の周りを周回軌道で回っている。
//オプション周回軌道の半径の距離は、オプションコントローラーが移動すると短くなる。
//オプションコントローラーが移動し続けると、オプションコントローラーの(0,0,0)
//付近で停止しているように見えるほど半径が小さくなる。
//オプションコントローラー停止すると、オプションは元の半径の距離に戻ろうとする。





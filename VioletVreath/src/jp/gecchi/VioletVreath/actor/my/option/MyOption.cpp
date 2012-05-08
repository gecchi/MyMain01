#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


/** １オプション当たりの最大可能ロックオン数 */
int MyOption::max_lockon_num_ = 9;
int MyOption::lockon_num_ = 8;
//MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pOptCtrlr) : DefaultMorphMeshActor(prm_name, "4/Ceres") {
//MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pOptCtrlr) : CubeMapMeshSetActor(prm_name, "4/Core4cm_") {
MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pOptCtrlr) :
        DefaultMeshSetActor(prm_name, "8/CORE4", STATUS(MyOption)) {

    _TRACE_("MyOption::MyOption("<<prm_name<<","<<prm_no<<")");
    _class_name = "MyOption";
    pOptionCtrlr_ = prm_pOptCtrlr;
    no_ = prm_no;
    angveloMove_ = 0;//旋廻移動角速度（読み出し専用）

    angPosition_ = 0;     //円周上初期位置角度（周囲角）（上書き初期設定可）
    radiusPosition_ = 150000;     //旋廻半径距離（上書き初期設定可）
    veloMv_ = 5000;     //旋廻移動速度（上書き初期設定可）
    angExpanse_ = 0;      //オプションの広がり角の回転角（上書き初期設定可）

    angPosition_base_ = angPosition_;
    radiusPosition_base_ = radiusPosition_;
    radiusPosition_stopping_ = radiusPosition_;

    angExpanse_default_ = angExpanse_;
    veloMv_base_ = veloMv_;

    return_to_base_radiusPosition_seq_ = false;
    return_to_base_angExpanse_seq_ = false;

    angveloExpanseNomal_ = 3000;
    angveloExpanseSlow_ = 1000;

    pEffect_ = NEW EffectMyOption("EffectMyOption", this);
    addSubGroup(pEffect_);

    //レーザー発射エフェクト
//    pEffect_LaserIrradiate_ = NEW EffectLockon001_Main("OP_Eff_Ref");
//    pEffect_LaserIrradiate_->inactivateImmed();
//    addSubGroup(pEffect_LaserIrradiate_);
    pEffect_LaserIrradiate_ = NULL;
    pLaserChipDepo_ = NEW LaserChipDepository("ROTLaser");
    MyOptionWateringLaserChip001* pChip;
//    MyOptionStraightLaserChip001* pChip;
    for (int i = 0; i < 80; i++) { //レーザーストック
        std::stringstream name;
        name <<  getName() << "'s MYS_LaserChip" << i;
        std::string name2 = name.str();
        pChip = NEW MyOptionWateringLaserChip001(name2.c_str());
        //pChip = NEW MyOptionStraightLaserChip001(name2.c_str());
        //MyOptionStraightLaserChip001の場合以下が必要
        //ストレート用
//        pChip->setSource(this);
//        pChip->pSource_vX_ = &Q._x;
//        pChip->pSource_vY_ = &Q._y;
//        pChip->pSource_vZ_ = &Q._z;

        pLaserChipDepo_->addSubLast(pChip);
    }
    pLaserChipDepo_->config(80, 25, pEffect_LaserIrradiate_);
    addSubGroup(pLaserChipDepo_);

    pDepo_MyShots001_ = NEW GgafActorDepository("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 25; i++) { //自弾ストック
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateImmed();
        pDepo_MyShots001_->addSubLast(pShot);
    }
    addSubGroup(pDepo_MyShots001_);

    //ロックオンコントローラー
    pLockonCtrlr_ = NEW MyOptionLockonController("LockonController");
    addSubGroup(pLockonCtrlr_);

    //フォトンコントローラー
    pTorpedoCtrlr_ = NEW MyOptionTorpedoController("TorpedoController", this);
    addSubGroup(pTorpedoCtrlr_);

    _pSeTx->useSe(3);
    _pSeTx->set(0, "laser001", GgafRepeatSeq::nextVal("CH_laser001"));
    _pSeTx->set(1, "fire01", GgafRepeatSeq::nextVal("CH_fire01"));
    _pSeTx->set(2, "bse5", GgafRepeatSeq::nextVal("CH_torpedo"));
    //prepareSe(0,"bse5", GgafRepeatSeq::nextVal("CH_bse5"));
    need_adjust_pos_flg_ = false;
}

void MyOption::onCreateModel() {
//    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.3, 2.0);
//    _pModel->_pTextureBlinker->setBlink(1.0);
//    _pModel->_pTextureBlinker->beat(120, 10, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void MyOption::initialize() {
    _SX=_SY=_SZ=100;
}

void MyOption::onReset() {
    angveloMove_ = ((1.0f*veloMv_ / radiusPosition_)*(double)D180ANG)/PI;
    _pKurokoA->setMvVelo(veloMv_);
    _pKurokoA->setRzMvAng(angPosition_+D90ANG);
    _pKurokoA->setRyMvAng(-D90ANG);
    _pKurokoA->setRzMvAngVelo(angveloMove_);//∵半径Ｒ＝速度Ｖ／角速度ω
    _pKurokoA->setRyMvAngVelo(0);//∵半径Ｒ＝速度Ｖ／角速度ω
    _Z = GgafDxUtil::COS[angPosition_/SANG_RATE]*radiusPosition_; //X軸中心回転なのでXYではなくてZY
    _Y = GgafDxUtil::SIN[angPosition_/SANG_RATE]*radiusPosition_; //X軸の正の方向を向いて時計回りに配置
                                                                    //ワールド変換の（左手法）のX軸回転とはと逆の回転なので注意
    _X = 0;
    _pKurokoA->setFaceAngVelo(AXIS_X, 4000);
    Xorg_ = _X;
    Yorg_ = _Y;
    Zorg_ = _Z;
    angPosition_ = _pKurokoA->_angRzMv;

    adjust_angPos_seq_progress_ = 0;
    adjust_angPos_seq_new_angPosition_base_ = angPosition_;
    adjust_angPos_seq_spent_frame_ = 0;

    radiusPosition_stopping_ = radiusPosition_;
}

void MyOption::onActive() {
    //レーザーやロックンターゲットや魚雷がサブにいるため
    //個別に呼び出す
    pLockonCtrlr_->onActive();
    pTorpedoCtrlr_->onActive();
}

void MyOption::addRadiusPosition(int prm_radius_offset, int prm_min_radius, int prm_max_radius) {
    //    _X = Xorg_;
    //    _Y = Yorg_;
    //    _Z = Zorg_;
    //より後
    //    Xorg_ = _X;
    //    Yorg_ = _Y;
    //    Zorg_ = _Z;
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
//    _X = Xorg_;
//    _Y = Yorg_;
//    _Z = Zorg_;
//より後
//    Xorg_ = _X;
//    Yorg_ = _Y;
//    Zorg_ = _Z;
//より前
//でしか呼び出してはいけません。
    radiusPosition_ = prm_radius;
    if (radiusPosition_ == -1  || radiusPosition_ == 0 || radiusPosition_ == 1) {
        _Z = _Y = 0;
        _pKurokoA->setRzMvAng(D90ANG);
        angveloMove_ = 0;
        _pKurokoA->setRzMvAngVelo(angveloMove_);
        return;

    }

    angle angZY_ROTANG_X;
    if (radiusPosition_ > 0) {
        angZY_ROTANG_X = MyStgUtil::getAngle2D(_Z, _Y); //自分の位置
        _Z = radiusPosition_ * GgafDxUtil::COS[GgafDxUtil::simplifyAng(angZY_ROTANG_X)/SANG_RATE];
        _Y = radiusPosition_ * GgafDxUtil::SIN[GgafDxUtil::simplifyAng(angZY_ROTANG_X)/SANG_RATE];
    } else {
        angZY_ROTANG_X = MyStgUtil::getAngle2D(-_Z, -_Y); //自分の位置
        _Z = radiusPosition_ * GgafDxUtil::COS[GgafDxUtil::simplifyAng(angZY_ROTANG_X)/SANG_RATE];
        _Y = radiusPosition_ * GgafDxUtil::SIN[GgafDxUtil::simplifyAng(angZY_ROTANG_X)/SANG_RATE];
    }
    //もしprm_lenが0の場合、理論的には元の位置に戻るはずなのだが、
    //誤差丸め込みのため、微妙に位置が変わる。
    //よって、移動方角、移動角速度を現在の位置(_Z,_Y)で再設定しなければズレる。
    _pKurokoA->setRzMvAng(angZY_ROTANG_X + D90ANG);
    angveloMove_ = ((1.0*veloMv_ / radiusPosition_)*(double)D180ANG)/PI;
    _pKurokoA->setRzMvAngVelo(angveloMove_);
}


void MyOption::adjustAngPosition(angle prm_new_angPosition_base, frame prm_spent_frame) {
    adjust_angPos_seq_progress_ = 1;
    adjust_angPos_seq_new_angPosition_base_ = MyStgUtil::simplifyAng(prm_new_angPosition_base);
    adjust_angPos_seq_spent_frame_ = prm_spent_frame + 1;
}



void MyOption::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    //処理メイン
    _X = Xorg_;
    _Y = Yorg_;
    _Z = Zorg_;

    if (return_to_base_radiusPosition_seq_) {
        //自動戻り
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
        if (VB_PLAY->isBeingPressed(VB_OPTION) && pOptionCtrlr_->is_handle_move_mode_) {
            //オプションの広がり角より、オプション移動速度と、旋回半径増加速度にベクトル分解。
            //そのうちの旋回半径増加速度のみを設定。
            addRadiusPosition(GgafDxUtil::SIN[angExpanse_/ SANG_RATE] * pOptionCtrlr_->veloOptionsMv_);
            //オプション移動速度の処理はMyOptionクラスで行う。
        }
    }

    if (return_to_base_angExpanse_seq_) {

        //自動戻り
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
        angExpanse_ = GgafDxUtil::simplifyAng(angExpanse_);
    } else {
        //オプション広がりと向き制御
        if (VB_PLAY->isBeingPressed(VB_OPTION) && VB_PLAY->isBeingPressed(VB_TURBO)) {
            int pos_camera = P_VAM->pos_camera_;
            if (pos_camera == VAM_POS_RIGHT) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(3000 * (radiusPosition_base_/60000));
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(-3000 * (radiusPosition_base_/60000));
                    //angExpanse_ -= angveloExpanseSlow_;
                }
            } else if (pos_camera == VAM_POS_LEFT) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(+3000 * (radiusPosition_base_/60000));
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(-3000 * (radiusPosition_base_/60000));
                    //angExpanse_ -= angveloExpanseSlow_;
                }
            } else if (pos_camera == VAM_POS_TOP) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    addRadiusPosition(3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(3000 * (radiusPosition_base_/60000));
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    addRadiusPosition(-3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(-3000 * (radiusPosition_base_/60000));
                    //angExpanse_ -= angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
            } else if (pos_camera == VAM_POS_BOTTOM) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    addRadiusPosition(-3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(-3000 * (radiusPosition_base_/60000));
                    //angExpanse_ -= angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    addRadiusPosition(3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(3000 * (radiusPosition_base_/60000));
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
            } else if (pos_camera > VAM_POS_TO_BEHIND) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(3000 * (radiusPosition_base_/60000));
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(-3000 * (radiusPosition_base_/60000));
                    //angExpanse_ -= angveloExpanseSlow_;
                }
            }
            angExpanse_ = GgafDxUtil::simplifyAng(angExpanse_);
        } else {
            if (pOptionCtrlr_->is_free_from_myship_mode_) {
                //
            } else {
                    GgafDxGeoElem* pGeoOpCon = pOptionCtrlr_->pRing_OptCtrlGeoHistory_->getPrev();
                    if (VB_PLAY->isBeingPressed(VB_OPTION)) {
                        //オプションボタン押下時は
                        //radiusPositionをいじらない
                    } else if (pGeoOpCon->_X == pOptionCtrlr_->_X &&
                               pGeoOpCon->_Y == pOptionCtrlr_->_Y &&
                               pGeoOpCon->_Z == pOptionCtrlr_->_Z )
                    {
                        //非移動時
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
                                if (need_adjust_pos_flg_) {
                                    MyOptionController::adjustDefaltAngPosition(radiusPosition_stopping_ / 1000);
                                    need_adjust_pos_flg_ = false;
                                }
                                veloMv_ = veloMv_base_;
                            }
                        }
                    } else {
                        //移動時
                        if (1 < radiusPosition_) {
                            addRadiusPosition(-3000, 1);
                        }
                        if (radiusPosition_ < 10000) {
                            need_adjust_pos_flg_ = true;
                        }

                        veloMv_ -= 200;
                        if (veloMv_ < 0) {
                            veloMv_ = 0;
                        }
                    }
//                }

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
                angPosition_now = MyStgUtil::getAngle2D(_Z, _Y);
            } else {
                angPosition_now = MyStgUtil::getAngle2D(-_Z, -_Y);
            }
            //現在の角距離
            angle ang_diff = MyStgUtil::getAngDiff(angPosition_now, adjust_angPos_seq_new_angPosition_base_, sgn(veloMv_));
            if (GgafUtil::abs(ang_diff) > D_ANG(350)) {
                ang_diff = MyStgUtil::getAngDiff(angPosition_now, adjust_angPos_seq_new_angPosition_base_, TURN_CLOSE_TO);
            }
            //残フレームと残移動角より必要な角速度
            angvelo angvelo_need = ang_diff / (angvelo)adjust_angPos_seq_spent_frame_;
            //必要な角速度差分
            angvelo angvelo_offset = angvelo_need - angveloMove_;
            //必要な角速度差分に対応する移動速度を求める
            velo veloMv_offset =  (2.0*PI*radiusPosition_ * angvelo_offset) / D360ANG;
            //速度設定
            _pKurokoA->setRzMvAngVelo(angveloMove_ + angvelo_offset);
            _pKurokoA->setMvVelo(veloMv_ + veloMv_offset);
            adjust_angPos_seq_spent_frame_ --;

            if (adjust_angPos_seq_spent_frame_ == 0) {
                angPosition_base_ = adjust_angPos_seq_new_angPosition_base_;
                //誤差修正のため理想位置に再設定
                angveloMove_ = ((1.0*veloMv_ / radiusPosition_)*(double)D180ANG)/PI;
                _pKurokoA->setMvVelo(veloMv_);
                _pKurokoA->setRzMvAng(GgafDxUtil::simplifyAng(angPosition_base_ + D90ANG));
                _pKurokoA->setRzMvAngVelo(angveloMove_);//∵半径Ｒ＝速度Ｖ／角速度ω
                _Z = GgafDxUtil::COS[angPosition_base_/SANG_RATE]*radiusPosition_; //X軸中心回転なのでXYではなくてZY
                _Y = GgafDxUtil::SIN[angPosition_base_/SANG_RATE]*radiusPosition_; //X軸の正の方向を向いて時計回りに配置
                _X = 0;
                adjust_angPos_seq_progress_ = 0;
            }
        }
    } else {
         //通常時
        _pKurokoA->setMvVelo(veloMv_);
    }
    angPosition_ = GgafDxUtil::simplifyAng(angPosition_+angveloMove_);

    _pKurokoA->behave();
    //_pKurokoB->behave();

    Xorg_ = _X;
    Yorg_ = _Y;
    Zorg_ = _Z;

    //＜メモ＞
    //ここまでで、GgafDxKurokoAの機能のみで、
    //以下のような状態までもっていく。
    //(100,0,0) から原点を見たイメージ、自は原点
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

    float sinRZ = GgafDxUtil::SIN[pOptionCtrlr_->_pKurokoA->_angFace[AXIS_Z] / SANG_RATE];
    float cosRZ = GgafDxUtil::COS[pOptionCtrlr_->_pKurokoA->_angFace[AXIS_Z] / SANG_RATE];
    float sinRY = GgafDxUtil::SIN[pOptionCtrlr_->_pKurokoA->_angFace[AXIS_Y] / SANG_RATE];
    float cosRY = GgafDxUtil::COS[pOptionCtrlr_->_pKurokoA->_angFace[AXIS_Y] / SANG_RATE];
    //全オプションを一つの塊としてOptionControllerを中心にWORLD変換のような旋廻
    _X = cosRY*cosRZ*Xorg_ + cosRY*-sinRZ*Yorg_ + sinRY*Zorg_;
    _Y = sinRZ*Xorg_ + cosRZ*Yorg_;
    _Z = -sinRY*cosRZ*Xorg_ + -sinRY*-sinRZ*Yorg_ + cosRY*Zorg_;


    //懐中電灯の照射角が広がるような回転（Quaternionで実現）
    float vX_axis = cosRY*cosRZ*_pKurokoA->_vX + cosRY*-sinRZ*_pKurokoA->_vY + sinRY*_pKurokoA->_vZ;
    float vY_axis = sinRZ*_pKurokoA->_vX + cosRZ*_pKurokoA->_vY;
    float vZ_axis = -sinRY*cosRZ*_pKurokoA->_vX + -sinRY*-sinRZ*_pKurokoA->_vY + cosRY*_pKurokoA->_vZ;
    float sinHalf = GgafDxUtil::SIN[angExpanse_/SANG_RATE/2]; //angExpanse_=回転させたい角度
    float cosHalf = GgafDxUtil::COS[angExpanse_/SANG_RATE/2];

    //計算
    //ある座標(x, y, z)において、回転の軸が(α, β, γ)で、θ回す回転
    //P = (0; x, y, z)
    //Q = (cos(θ/2); α sin(θ/2), β sin(θ/2), γ sin(θ/2))
    //R = (cos(θ/2); -α sin(θ/2), -β sin(θ/2), -γ sin(θ/2))
    //
    //R P Q = (0; 答え)
    //
    //回転軸 は(vX_axis, vY_axis, vZ_axis) 回転角は angExpanse_
    GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf); //R
//    Q.set(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
    Q.mul(0, pOptionCtrlr_->_pKurokoA->_vX,
             pOptionCtrlr_->_pKurokoA->_vY,
             pOptionCtrlr_->_pKurokoA->_vZ); //R*P 回転軸が現在の進行方向ベクトルとなる
    Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
    //Q._x, Q._y, Q._z が回転後の座標となる
    //Z軸回転、Y軸回転角度を計算
    GgafDxUtil::getRzRyAng(Q._x, Q._y, Q._z,
                           _RZ, _RY);


    _X += pOptionCtrlr_->_X;
    _Y += pOptionCtrlr_->_Y;
    _Z += pOptionCtrlr_->_Z;


    //TODO
    //最適化
    if (pMyShip->is_shooting_laser_ && VB_PLAY->isBeingPressed(VB_SHOT1)) {
        MyOptionWateringLaserChip001* pLaserChip = (MyOptionWateringLaserChip001*)pLaserChipDepo_->dispatch();
//        MyOptionStraightLaserChip001* pLaserChip = (MyOptionStraightLaserChip001*)pLaserChipDepo_->dispatch();

        if (pLaserChip) {
            if (pLaserChipDepo_->_pEffectActor_Irradiate) {
                pLaserChipDepo_->_pEffectActor_Irradiate->locatedBy(this);
            }
            //ストレート用
//            pLaserChip->_pKurokoA->behave();
//            pLaserChip->_pKurokoB->behave();
//            pLaserChip->pOrg_ = this;
//            pLaserChip->activate();

              //カーブ用
//            pLaserChip->_pKurokoA->_vX = Q._x;
//            pLaserChip->_pKurokoA->_vY = Q._y;
//            pLaserChip->_pKurokoA->_vZ = Q._z;
//            pLaserChip->_pKurokoA->_angRzMv = _RZ;
//            pLaserChip->_pKurokoA->_angRyMv = _RY;
////            pLaserChip->_pKurokoA->_angFace[AXIS_X] = _pKurokoA->_angFace[AXIS_X];
//            pLaserChip->_pKurokoA->_angFace[AXIS_Z] = _RZ;
//            pLaserChip->_pKurokoA->_angFace[AXIS_Y] = _RY;

            pLaserChip->_pKurokoB->setVxMvVelo(Q._x*pLaserChip->max_velo_renge_);
            pLaserChip->_pKurokoB->setVyMvVelo(Q._y*pLaserChip->max_velo_renge_);
            pLaserChip->_pKurokoB->setVzMvVelo(Q._z*pLaserChip->max_velo_renge_);
            pLaserChip->_pKurokoB->setVxMvAcce(Q._x*pLaserChip->max_velo_renge_/pLaserChip->r_max_acce_);
            pLaserChip->_pKurokoB->setVyMvAcce(Q._y*pLaserChip->max_velo_renge_/pLaserChip->r_max_acce_);
            pLaserChip->_pKurokoB->setVzMvAcce(Q._z*pLaserChip->max_velo_renge_/pLaserChip->r_max_acce_);
//            pLaserChip->_pKurokoA->behave();
            pLaserChip->_pKurokoB->behave();
            pLaserChip->_X = _X;
            pLaserChip->_Y = _Y;
            pLaserChip->_Z = _Z;
            pLaserChip->_RZ = _RZ;
            pLaserChip->_RY = _RY;
            pLaserChip->pOrg_ = this;

            if (pLaserChip->_pChip_front == NULL) {
                _pSeTx->play3D(0);
            }
        }
    } else {
        pLockonCtrlr_->releaseAllLockon();
    }
    if (pMyShip->just_shot_) {
        MyShot001* pShot = (MyShot001*)pDepo_MyShots001_->dispatch();
        if (pShot) {
            _pSeTx->play3D(1);
            pShot->locatedBy(this);
            pShot->_pKurokoA->_angFace[AXIS_X] = _RX;
            pShot->_pKurokoA->_angFace[AXIS_Z] = _RZ;
            pShot->_pKurokoA->_angFace[AXIS_Y] = _RY;
            pShot->_pKurokoA->setRzRyMvAng(_RZ, _RY);
        }
    }

    _pSeTx->behave();

}

void MyOption::processJudgement() {
}

void MyOption::onInactive() {
    //レーザーやロックンターゲットや魚雷がサブにいるため
    //個別に呼び出す
    pLockonCtrlr_->onInactive();
    pTorpedoCtrlr_->onInactive();
    pLaserChipDepo_->reset();

}

void MyOption::onHit(GgafActor* prm_pOtherActor) {
    sayonara();
}

MyOption::~MyOption() {
}


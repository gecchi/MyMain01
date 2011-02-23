#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


/** １オプション当たりの最大可能ロックオン数 */
int MyOption::_max_lockon_num = 7;
int MyOption::_lockon_num = 1;
//MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pMyOptionController) : DefaultMorphMeshActor(prm_name, "4/Ceres") {
MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pMyOptionController) : DefaultMeshSetActor(prm_name, "8/Astraea") {
//MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pMyOptionController) : CubeMapMeshSetActor(prm_name, "4/Core4_cm") {


_TRACE_("MyOption::MyOption("<<prm_name<<","<<prm_no<<")");
    _class_name = "MyOption";
    _pMyOptionController = prm_pMyOptionController;
    _no = prm_no;
    _angveloMove = 0;//旋廻移動角速度（読み出し専用）

    _angPosition = 0;     //円周上初期位置角度（周囲角）（上書き初期設定可）
    _radiusPosition = 150000;     //旋廻半径距離（上書き初期設定可）
    _veloMv = 5000;     //旋廻移動速度（上書き初期設定可）
    _angExpanse = 0;      //オプションの広がり角の回転角（上書き初期設定可）

    _angPosition_base = _angPosition;
    _radiusPosition_base = _radiusPosition;
    _angExpanse_default = _angExpanse;
    _veloMv_base = _veloMv;

    _return_to_base_radiusPosition_seq = false;
    _return_to_base_angExpanse_seq = false;

    _angveloExpanseNomal = 3000;
    _angveloExpanseSlow = 1000;

    //レーザー発射エフェクト
//    _pEffect_LaserIrradiate = NEW EffectLockon001_Main("OP_Eff_Ref");
//    _pEffect_LaserIrradiate->inactivateImmediately();
//    addSubGroup(_pEffect_LaserIrradiate);
    _pEffect_LaserIrradiate = NULL;


    _pLaserChipDispatcher = NEW LaserChipDispatcher("ROTLaser");
    MyCurveLaserChip001* pChip;
    for (int i = 0; i < 90; i++) { //レーザーストック
        stringstream name;
        name <<  getName() << "'s MYS_LaserChip" << i;
        string name2 = name.str();
        pChip = NEW MyCurveLaserChip001(name2.c_str());
//        pChip->setSource(this);
//        pChip->_pSource_vX = &_Q._x;
//        pChip->_pSource_vY = &_Q._y;
//        pChip->_pSource_vZ = &_Q._z;
       // pChip->_pSeTransmitter->useSe(1);
       // pChip->_pSeTransmitter->set(0, "laser001", _no);
        //pChip->inactivateImmediately();
        _pLaserChipDispatcher->addSubLast(pChip);
    }
    _pLaserChipDispatcher->config(
                               90, 25, _pEffect_LaserIrradiate
                           );
    addSubGroup(_pLaserChipDispatcher);

    _pDispatcher_MyShots001 = NEW GgafActorDispatcher("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 25; i++) { //自弾ストック
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateImmediately();
        _pDispatcher_MyShots001->addSubLast(pShot);
    }
    addSubGroup(_pDispatcher_MyShots001);

    //ロックオンコントローラー
    _pLockonController = NEW MyOptionLockonController("LockonController");
    addSubGroup(_pLockonController);

    //フォトンコントローラー
    _pTorpedoController = NEW MyOptionTorpedoController("TorpedoController", this);
    addSubGroup(_pTorpedoController);


    _pSeTransmitter->useSe(2);
    _pSeTransmitter->set(0, "laser001", GgafRepeatSeq::nextVal("CH_laser001"));
    _pSeTransmitter->set(1, "fire01", GgafRepeatSeq::nextVal("CH_fire01"));

    //prepareSe(0,"bse5", GgafRepeatSeq::nextVal("CH_bse5"));

}

void MyOption::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.3, 2.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(1.0);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 10, 1, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.9;
}

void MyOption::initialize() {
    _SX=_SY=_SZ=100;
}

void MyOption::onReset() {
    _angveloMove = ((1.0f*_veloMv / _radiusPosition)*(double)ANGLE180)/PI;
    _pKuroko->setMvVelo(_veloMv);
    _pKuroko->setRzMvAng(_angPosition+ANGLE90);
    _pKuroko->setRyMvAng(-ANGLE90);
    _pKuroko->setRzMvAngVelo(_angveloMove);//∵半径Ｒ＝速度Ｖ／角速度ω
    _pKuroko->setRyMvAngVelo(0);//∵半径Ｒ＝速度Ｖ／角速度ω
    _Z = GgafDx9Util::COS[_angPosition/ANGLE_RATE]*_radiusPosition; //X軸中心回転なのでXYではなくてZY
    _Y = GgafDx9Util::SIN[_angPosition/ANGLE_RATE]*_radiusPosition; //X軸の正の方向を向いて時計回りに配置
                                                                    //ワールド変換の（左手法）のX軸回転とはと逆の回転なので注意
    _X = 0;
    _pKuroko->setFaceAngVelo(AXIS_X, 4000);
    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;
    //P_COMMON_SCENE->getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pLaserChipDispatcher->extract());
    _angPosition = _pKuroko->_angRzMv;

    _adjust_angPos_seq_progress = 0;
    _adjust_angPos_seq_new_angPosition_base = _angPosition;
    _adjust_angPos_seq_spent_frame = 0;
    _adjust_angPos_seq_angPosition = 0;
}

void MyOption::onActive() {
}

void MyOption::addRadiusPosition(int prm_radius_offset) {
    //    _X = _Xorg;
    //    _Y = _Yorg;
    //    _Z = _Zorg;
    //より後
    //    _Xorg = _X;
    //    _Yorg = _Y;
    //    _Zorg = _Z;
    //より前
    //でしか呼び出してはいけません。


//負の半径も許す場合は如何のロジックのコメントを外す
//    int radius;
//    if (_radiusPosition == -1 * prm_radius_offset) { //差分を加えると0になる場合
//        //半径は0にしてはいけない。0割り算を避けるため
//        if (_radiusPosition > 0) {
//            radius = -100;
//        } else {
//            radius = 100;
//        }
//    } else {
//        radius = _radiusPosition + prm_radius_offset;
//    }
//    setRadiusPosition(radius);

    int radius;
    radius = _radiusPosition + prm_radius_offset;
    if (_radiusPosition < 30000) {
        radius = 30000; //オプション最低半径距離
    }
    setRadiusPosition(radius);
}


void MyOption::setRadiusPosition(int prm_radius) {
//    _X = _Xorg;
//    _Y = _Yorg;
//    _Z = _Zorg;
//より後
//    _Xorg = _X;
//    _Yorg = _Y;
//    _Zorg = _Z;
//より前
//でしか呼び出してはいけません。

    if (_radiusPosition == -1 * prm_radius) {
        if (_radiusPosition > 0) {
            _radiusPosition = -100;
        } else {
            _radiusPosition = 100;
        }
    } else {
        _radiusPosition += prm_radius;
    }

    _radiusPosition = prm_radius;
    angle angZY_ROTANG_X;
    if (_radiusPosition > 0) {
        angZY_ROTANG_X = MyStgUtil::getAngle2D(_Z, _Y); //自分の位置
        _Z = _radiusPosition * GgafDx9Util::COS[GgafDx9Util::simplifyAng(angZY_ROTANG_X)/ANGLE_RATE];
        _Y = _radiusPosition * GgafDx9Util::SIN[GgafDx9Util::simplifyAng(angZY_ROTANG_X)/ANGLE_RATE];
    } else {
        angZY_ROTANG_X = MyStgUtil::getAngle2D(-_Z, -_Y); //自分の位置
        _Z = _radiusPosition * GgafDx9Util::COS[GgafDx9Util::simplifyAng(angZY_ROTANG_X)/ANGLE_RATE];
        _Y = _radiusPosition * GgafDx9Util::SIN[GgafDx9Util::simplifyAng(angZY_ROTANG_X)/ANGLE_RATE];
    }
    //もしprm_lenが0の場合、理論的には元の位置に戻るはずなのだが、
    //誤差丸め込みのため、微妙に位置が変わる。
    //よって、移動方角、移動角速度を現在の位置(_Z,_Y)で再設定しなければズレる。
    _pKuroko->setRzMvAng(GgafDx9Util::simplifyAng(angZY_ROTANG_X + ANGLE90));
    _angveloMove = ((1.0*_veloMv / _radiusPosition)*(double)ANGLE180)/PI;
    _pKuroko->setRzMvAngVelo(_angveloMove);
}


void MyOption::adjustAngPosition(angle prm_new_angPosition_base, frame prm_spent_frame) {
    _adjust_angPos_seq_progress = 1;
    _adjust_angPos_seq_new_angPosition_base = MyStgUtil::simplifyAng(prm_new_angPosition_base);
    _adjust_angPos_seq_spent_frame = prm_spent_frame + 1;
}



void MyOption::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    //処理メイン
    _X = _Xorg;
    _Y = _Yorg;
    _Z = _Zorg;


    if (_return_to_base_radiusPosition_seq) {
        //自動戻り
        if (_radiusPosition > _radiusPosition_base) {
            addRadiusPosition(-10000);
        }
        if (_radiusPosition < _radiusPosition_base) {
            addRadiusPosition(10000);
        }
        if (-10000 < _radiusPosition_base-_radiusPosition && _radiusPosition_base-_radiusPosition < 10000) {
            setRadiusPosition(_radiusPosition_base);
            _return_to_base_radiusPosition_seq = false;
        }

    } else {

        //オプション独立移動制御時
        if (VB_PLAY->isBeingPressed(VB_OPTION) && _pMyOptionController->_is_handle_move_mode) {
            //オプションの広がり角より、オプション移動速度と、旋回半径増加速度にベクトル分解。
            //そのうちの旋回半径増加速度のみを設定。
            addRadiusPosition(GgafDx9Util::SIN[_angExpanse/ ANGLE_RATE] * _pMyOptionController->_veloOptionsMv);
            //オプション移動速度の処理はMyOptionクラスで行う。
        }
    }

    if (_return_to_base_angExpanse_seq) {

        //自動戻り
        if (_angExpanse > _angExpanse_default) {
            _angExpanse -= 3000;
        }
        if (_angExpanse < _angExpanse_default) {
            _angExpanse += 3000;
        }
        if (-3000 <= _angExpanse_default-_angExpanse && _angExpanse_default-_angExpanse <= 3000) {
            _angExpanse = _angExpanse_default;
            _return_to_base_angExpanse_seq = false;
        }
        _angExpanse = GgafDx9Util::simplifyAng(_angExpanse);
    } else {
        //オプション広がりと向き制御
        if (VB_PLAY->isBeingPressed(VB_OPTION) && VB_PLAY->isBeingPressed(VB_TURBO)) {
//            if (P_VAM->_pos_camera == VAM_POS_RIGHT) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    _angExpanse += _angveloExpanseNomal;
                } else if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    _angExpanse -= _angveloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
                    //_angExpanse += _angveloExpanseSlow;
                } else if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
                    //_angExpanse -= _angveloExpanseSlow;
                }
//            } else if (P_VAM->_pos_camera == VAM_POS_LEFT) {
//                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
//                    _angExpanse -= _angveloExpanseNomal;
//                }
//                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
//                    _angExpanse += _angveloExpanseNomal;
//                }
//                if (VB_PLAY->isBeingPressed(VB_UP)) {
//                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
//                    //_angExpanse += _angveloExpanseSlow;
//                }
//                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
//                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
//                    //_angExpanse -= _angveloExpanseSlow;
//                }
//            } else if (P_VAM->_pos_camera == VAM_POS_TOP) {
//                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
//                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
//                    //_angExpanse += _angveloExpanseSlow;
//                }
//                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
//                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
//                    //_angExpanse -= _angveloExpanseSlow;
//                }
//                if (VB_PLAY->isBeingPressed(VB_UP)) {
//                    _angExpanse += _angveloExpanseNomal;
//                }
//                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
//                    _angExpanse -= _angveloExpanseNomal;
//                }
//            } else if (P_VAM->_pos_camera == VAM_POS_BOTTOM) {
//                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
//                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
//                    //_angExpanse -= _angveloExpanseSlow;
//                }
//                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
//                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
//                    //_angExpanse += _angveloExpanseSlow;
//                }
//                if (VB_PLAY->isBeingPressed(VB_UP)) {
//                    _angExpanse -= _angveloExpanseNomal;
//                }
//                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
//                    _angExpanse += _angveloExpanseNomal;
//                }
//            } else if (P_VAM->_pos_camera > VAM_POS_TO_BEHIND) {
//                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
//                    _angExpanse += _angveloExpanseNomal;
//                }
//                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
//                    _angExpanse -= _angveloExpanseNomal;
//                }
//                if (VB_PLAY->isBeingPressed(VB_UP)) {
//                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
//                    //_angExpanse += _angveloExpanseSlow;
//                }
//                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
//                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
//                    //_angExpanse -= _angveloExpanseSlow;
//                }
//            }
            _angExpanse = GgafDx9Util::simplifyAng(_angExpanse);
        }
    }


//    if (GgafDx9Input::isBeingPressedKey(DIK_Q)) {
//        addRadiusPosition(1000);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
//        addRadiusPosition(-1000);
//    }

    if (_adjust_angPos_seq_progress > 0) {
        if (_adjust_angPos_seq_progress == 1) {
            //初期処理

            _adjust_angPos_seq_progress = 2;
        }


        if (_adjust_angPos_seq_progress == 2) {
            //自分の角度位置取得
            if (_radiusPosition > 0) {
                _adjust_angPos_seq_angPosition = MyStgUtil::getAngle2D(_Z, _Y);
            } else {
                _adjust_angPos_seq_angPosition = MyStgUtil::getAngle2D(-_Z, -_Y);
            }
            //現在の角距離
            angle ang_diff = MyStgUtil::getAngDiff(_adjust_angPos_seq_angPosition, _adjust_angPos_seq_new_angPosition_base, sgn(_veloMv));
            //残フレームと残移動角より必要な角速度
            angvelo angvelo_need = ang_diff / (angvelo)_adjust_angPos_seq_spent_frame;
            //必要な角速度差分
            angvelo angvelo_offset = angvelo_need - _angveloMove;
            //必要な角速度差分に対応する移動速度を求める
            velo veloMv_offset =  (2.0*PI*_radiusPosition * angvelo_offset) / ANGLE360;
            //速度設定
            _pKuroko->setRzMvAngVelo(_angveloMove + angvelo_offset);
            _pKuroko->setMvVelo(_veloMv + veloMv_offset);
            _adjust_angPos_seq_spent_frame --;

            if (_adjust_angPos_seq_spent_frame == 0) {
                _angPosition_base = _adjust_angPos_seq_new_angPosition_base;
                //誤差修正のため理想位置に再設定
                _angveloMove = ((1.0*_veloMv / _radiusPosition)*(double)ANGLE180)/PI;
                _pKuroko->setMvVelo(_veloMv);
                _pKuroko->setRzMvAng(GgafDx9Util::simplifyAng(_angPosition_base + ANGLE90));
                _pKuroko->setRzMvAngVelo(_angveloMove);//∵半径Ｒ＝速度Ｖ／角速度ω
                _Z = GgafDx9Util::COS[_angPosition_base/ANGLE_RATE]*_radiusPosition; //X軸中心回転なのでXYではなくてZY
                _Y = GgafDx9Util::SIN[_angPosition_base/ANGLE_RATE]*_radiusPosition; //X軸の正の方向を向いて時計回りに配置
                _X = 0;
                _adjust_angPos_seq_progress = 0;
            }
        }
    } else {
         //通常時
        _pKuroko->setMvVelo(_veloMv);
    }
    _angPosition = GgafDx9Util::simplifyAng(_angPosition+_angveloMove);

    _pKuroko->behave();

    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;

    //＜メモ＞
    //ここまでで、GgafDx9Kurokoの機能のみで、
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
    //↓     (0,0,0)      (-50000, 0, _radiusPosition)
    //
    //
    //          ○→
    //          (-50000, -1*_radiusPosition, 0)
    //
    //しかしまだ色々と回転したいため。あとは普通に計算（力技）で、座標回転、向き回転を行なう。
    //ダミーのアクターを連結しようとしたがいろいろ難しい、Quaternion を使わざるを得ない（のではないか；）。
    //TODO:最適化すべし、Quaternionは便利だが避けたい。いつか汎用化

    float sinRZ = GgafDx9Util::SIN[_pMyOptionController->_pKuroko->_angFace[AXIS_Z] / ANGLE_RATE];
    float cosRZ = GgafDx9Util::COS[_pMyOptionController->_pKuroko->_angFace[AXIS_Z] / ANGLE_RATE];
    float sinRY = GgafDx9Util::SIN[_pMyOptionController->_pKuroko->_angFace[AXIS_Y] / ANGLE_RATE];
    float cosRY = GgafDx9Util::COS[_pMyOptionController->_pKuroko->_angFace[AXIS_Y] / ANGLE_RATE];
    //全オプションを一つの塊としてOptionControllerを中心にWORLD変換のような旋廻
    _X = cosRY*cosRZ*_Xorg + cosRY*-sinRZ*_Yorg + sinRY*_Zorg;
    _Y = sinRZ*_Xorg + cosRZ*_Yorg;
    _Z = -sinRY*cosRZ*_Xorg + -sinRY*-sinRZ*_Yorg + cosRY*_Zorg;



    //懐中電灯の照射角が広がるような回転（Quaternionで実現）
    float vX_axis = cosRY*cosRZ*_pKuroko->_vX + cosRY*-sinRZ*_pKuroko->_vY + sinRY*_pKuroko->_vZ;
    float vY_axis = sinRZ*_pKuroko->_vX + cosRZ*_pKuroko->_vY;
    float vZ_axis = -sinRY*cosRZ*_pKuroko->_vX + -sinRY*-sinRZ*_pKuroko->_vY + cosRY*_pKuroko->_vZ;
    float sinHalf = GgafDx9Util::SIN[_angExpanse/ANGLE_RATE/2]; //_angExpanse=回転させたい角度
    float cosHalf = GgafDx9Util::COS[_angExpanse/ANGLE_RATE/2];

    //計算
    GgafDx9Quaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
//    _Q.set( cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
    Q.mul(0,
           _pMyOptionController->_pKuroko->_vX,
           _pMyOptionController->_pKuroko->_vY,
           _pMyOptionController->_pKuroko->_vZ); //R*P 回転軸が現在の進行方向ベクトルとなる
    Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
    //Q._x, Q._y, Q._z が回転後の座標となる
    //Z軸回転、Y軸回転角度を計算
    GgafDx9Util::getRzRyAng(
        Q._x, Q._y, Q._z,
        _RZ, _RY
     );

//    _RZ = GgafDx9Util::simplifyAng(_RZ);
//    _RY = GgafDx9Util::simplifyAng(_RY);
    _X += _pMyOptionController->_X;
    _Y += _pMyOptionController->_Y;
    _Z += _pMyOptionController->_Z;

    //TODO
    //最適化
    _pKuroko->_veloVxMv = 0;
    _pKuroko->_veloVyMv = 0;
    _pKuroko->_veloVzMv = 0;
            //_TRACE_("_pVBMap_Active->_state="<<(vbsta)(VB_PLAY->_pVBMap_Active->_state));
    if (pMyShip->_is_shooting_laser && VB_PLAY->isBeingPressed(VB_SHOT1)) {


        MyCurveLaserChip001* pLaserChip = (MyCurveLaserChip001*)_pLaserChipDispatcher->employ();
        if (pLaserChip) {
            if (_pLaserChipDispatcher->_pEffectActor_Irradiate) {
                _pLaserChipDispatcher->_pEffectActor_Irradiate->setCoordinateBy(this);
            }
            pLaserChip->_pKuroko->_vX = Q._x;
            pLaserChip->_pKuroko->_vY = Q._y;
            pLaserChip->_pKuroko->_vZ = Q._z;
            pLaserChip->_pKuroko->_angRzMv = _RZ;
            pLaserChip->_pKuroko->_angRyMv = _RY;
//            pLaserChip->_pKuroko->_angFace[AXIS_X] = _pKuroko->_angFace[AXIS_X];
            pLaserChip->_pKuroko->_angFace[AXIS_Z] = _RZ;
            pLaserChip->_pKuroko->_angFace[AXIS_Y] = _RY;
            pLaserChip->_pKuroko->setVxMvVelo(Q._x*150000);
            pLaserChip->_pKuroko->setVyMvVelo(Q._y*150000);
            pLaserChip->_pKuroko->setVzMvVelo(Q._z*150000);
            pLaserChip->_pKuroko->setVxMvAcce(0);
            pLaserChip->_pKuroko->setVyMvAcce(0);
            pLaserChip->_pKuroko->setVzMvAcce(0);
            pLaserChip->_pKuroko->behave();
            pLaserChip->_X = _X;
            pLaserChip->_Y = _Y;
            pLaserChip->_Z = _Z;
            pLaserChip->_pOrg = this;
            pLaserChip->activate();
            if (pLaserChip->_pChip_front == NULL) {
                //pLaserChip->_pSeTransmitter->play3D(0);
                _pSeTransmitter->play3D(0);
                //playSe3D(0);
            }
        }
    } else {
        _pLockonController->releaseAllLockon();
    }

//    if (_pLockonTarget) {
//        //if (_pLockonTarget->isOutOfView() || _pLockonTarget->isActiveActor() == false) { //非アクティブのみと視野外はロックオン解除
//        if (_pLockonTarget->isActiveActor() == false) {  //非アクティブのみ解除（視野外でもロックオン維持）
//            _pLockonController->releaseLockon();
//            _pLockonTarget = NULL;
//        } else {
//            _pLockonController->lockon(_pLockonTarget);
//        }
//
//    } else {
//        _pLockonController->releaseLockon();
//        _pLockonTarget = NULL;
//    }

    if (pMyShip->_just_shot) {
        MyShot001* pShot = (MyShot001*)_pDispatcher_MyShots001->employ();
        if (pShot) {
            _pSeTransmitter->play3D(1);
            pShot->setCoordinateBy(this);
            pShot->_pKuroko->_angFace[AXIS_X] = _RX;
            pShot->_pKuroko->_angFace[AXIS_Z] = _RZ;
            pShot->_pKuroko->_angFace[AXIS_Y] = _RY;
            pShot->_pKuroko->setRzRyMvAng(_RZ, _RY);
            pShot->activate();
        }
    }

//    if (VB_PLAY->isPushedDown(VB_SHOT1)) {
//        MyShot001* pShot = (MyShot001*)_pDispatcher_MyShots001->employ();
//        if (pShot) {
//            _pSeTransmitter->play3D(1);
//            pShot->setCoordinate(this);
//            pShot->_pKuroko->_angFace[AXIS_X] = _RX;
//            pShot->_pKuroko->_angFace[AXIS_Z] = _RZ;
//            pShot->_pKuroko->_angFace[AXIS_Y] = _RY;
//            pShot->_pKuroko->setRzRyMvAng(_RZ, _RY);
//            pShot->activate();
//        }
//    }


    _pSeTransmitter->behave();

}

void MyOption::processJudgement() {
}

void MyOption::onHit(GgafActor* prm_pOtherActor) {
    sayonara();
}

void MyOption::processFinal() {
//    //ロックオンが体力が無くなれば、存在してようが切る
//    if (_pLockonTarget) {
//        if (_pLockonTarget->_pStatus->get(STAT_Stamina) <= 0) {
//            _pLockonController->releaseLockon();
//            _pLockonTarget = NULL;
//        }
//    }
}
MyOption::~MyOption() {
}


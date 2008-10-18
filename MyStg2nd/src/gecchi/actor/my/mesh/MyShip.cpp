#include "stdafx.h"

#define newState(H,X) do { H->e = new State*[X]; for (int i = 0; i < X; i++) {H->e[i] = new State(); } } while(0)
#define S_OPTION 0

//1/√2
#define NANAME 0.7






MyShip::MyShip(string prm_name, string prm_xname) : DefaultMeshActor(prm_name, prm_xname) {
	GameGlobal::_pMyShip = this;
	/** 移動スピードレベル */
	_lv_MoveSpeed = 2;
	/** 移動スピードレベルに相応する移動スピード */
	_iMoveSpeed = 2000;

	//CommonSceneがnewの場合設定
	_iShotKind01 = 0;
	_iShotKind02 = 0;
	_iShotKind03 = 0;

	//キャッシュロード
	GgafDx9SeManager::get("laser001");

//	_angRXVelo_BeginMZ = 100;
//	_angRXAcce_MZ = 100;
//	_angRXTopVelo_MZ = 5000;
//	_angRXStop_MZ = 85000;
//
//	_iMvVelo_BeginMT = 5000;
//	_iMvAcce_MT = -100;
//	_iMvBtmVelo_MT = 1000;
//
//	_angRXVelo_BeginMZT = 10000;
//	_angRXAcce_MZT = -200;
//	_angRXBtmVelo_MZT = _angRXTopVelo_MZ;
//
//
//	_angRXTopVelo_MNZ = 2000;
//	_angRXAcce_MNZ = 100;

	_tmpX = _X;
	_tmpY = _Y;
	_tmpZ = _Z;



	_angRZVelo_BeginMY = 100;	//上又は下へ通常移動開始時のX軸回転角速度の初速度
	_angRZTopVelo_MY = 3000;	//上又は下へ移動中のZ軸回転角速度の上限角速度
	_angRZAcce_MY = 300;		//上又は下へ通常移動中のZ軸回転角速度の角加速度
	_angRZStop_MY = 45000;		//上又は下へ通常Z移動中のZ軸回転角の停止角度

	_iMvBtmVelo_MT = _iMoveSpeed*3;		//TURBO移動中の移動速度の最低速度
	_iMvVelo_BeginMT = _iMoveSpeed*6;	//TURBO移動開始時の移動速度の初速度
	_iMvAcce_MT = -300;					//TURBO移動中の移動速度の加速度

	_angRZVelo_BeginMYT = 30000;//上又は下へTURBO移動開始時のZ軸回転角速度の初速度
	_angRZAcce_MYT = -200;		//上又は下へTURBO移動中のZ軸回転角速度の角加速度
	_angRZBtmVelo_MYT = 4000;	//上又は下へTURBO移動中のZ軸回転角速度の最低速度

	_angRZTopVelo_MNY = 1000;	//上又は下へ通常移動時、自動的にAngle0に戻ろうとするZ軸回転角速度の上限角速度
	_angRZAcce_MNY = 100;		//上又は下へ通常移動時、自動的にAngle0に戻ろうとする時のY軸回転角加速度(正負共通)

	_angRXVelo_BeginMZT = 30000;	//奥又は手前へTURBO移動開始時のX軸回転角速度の初速度
	_angRXAcce_MZT = -200;			//奥又は手前へTURBO移動中のX軸回転角速度の角加速度
	_angRXBtmVelo_MZT = 4000;		//奥又は手前へTURBO移動中のX軸回転角速度の最低速度

	_angRXTopVelo_MNZ = 1000; 		//奥又は手前以外の通常移動時、自動的にAngle0に戻ろうとするX軸回転角速度の上限角速度
	_angRXAcce_MNZ = 100;			//奥又は手前以外の通常移動時、自動的にAngle0に戻ろうとする時のX軸回転角加速度(正負共通)



	_dwFrameNextXYTurboOut = 0;	//XY次回ターボ終了フレーム
	_dwIntervalXYTurbo = 60;	//XYターボ終了フレーム間隔

	_dwFrameNextZTurboOut = 0;	//Z次回ターボ終了フレーム
	_dwIntervalZTurbo = 60;		//Zターボ終了フレーム間隔

	_dwFrameTurbo = 0;			//ターボ経過フレーム
	_isMoveZX = false;
	_wayTurbo = NONE;
	_dRate_TurboControl = 0.8; //ターボ中移動制御できる割合
}

void MyShip::initialize() {
	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);
	_pMover -> setXYMoveVelocity(0);
}

void MyShip::processBehavior() {

	_tmpX = _X;
	_tmpY = _Y;
	_tmpZ = _Z;
	_dwFrameTurbo++; // ターボ経過フレーム

	//奥手前移動初めのTURBOか否か
	if (_dwFrameTurbo > 2) {
		if (VB::areNotBeingPressedAfterPushedDownAtOnce(VB_TURBO, VB_UP_STC))  {               //奥、始動
			_wayTurbo = ZLEFT;
			beginTurboZX(VB_UP_STC);
		} else if (VB::areNotBeingPressedAfterPushedDownAtOnce(VB_TURBO, VB_DOWN_STC))  {      //手前、始動
			_wayTurbo = ZRIGHT;
			beginTurboZX(VB_DOWN_STC);
		} else if (VB::areNotBeingPressedAfterPushedDownAtOnce(VB_TURBO, VB_UP_LEFT_STC)) {    //左斜め奥、始動
			_wayTurbo = ZLEFT_BEHIND;
			beginTurboZX(VB_UP_LEFT_STC);
		} else if (VB::areNotBeingPressedAfterPushedDownAtOnce(VB_TURBO, VB_UP_RIGHT_STC)) {   //右斜め奥、始動
			_wayTurbo = ZLEFT_FRONT;
			beginTurboZX(VB_UP_RIGHT_STC);
		} else if (VB::areNotBeingPressedAfterPushedDownAtOnce(VB_TURBO, VB_DOWN_LEFT_STC)) {  //左斜め手前、始動
			_wayTurbo = ZRIGHT_BEHIND;
			beginTurboZX(VB_DOWN_LEFT_STC);
		} else if (VB::areNotBeingPressedAfterPushedDownAtOnce(VB_TURBO, VB_DOWN_RIGHT_STC)) { //右斜め手前、始動
			_wayTurbo = ZRIGHT_FRONT;
			beginTurboZX(VB_DOWN_RIGHT_STC);
		} else {
			//上下左右移動初めのTURBOか否か
			if (VB::isPushedDown(VB_TURBO)) {
				if (VB::isBeingPressed(VB_UP_STC)) {                 //上、始動
					_wayTurbo = UP;
					beginTurboXY(VB_UP_STC);
				} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {    //右上、始動
					_wayTurbo = UP_FRONT;
					beginTurboXY(VB_UP_RIGHT_STC);
				} else if (VB::isBeingPressed(VB_RIGHT_STC)) {       //右、始動
					_wayTurbo = FRONT;
					beginTurboXY(VB_RIGHT_STC);
				} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {  //右下、始動
					_wayTurbo = DOWN_FRONT;
					beginTurboXY(VB_DOWN_RIGHT_STC);
				} else if (VB::isBeingPressed(VB_DOWN_STC)) {        //下、始動
					_wayTurbo = DOWN;
					beginTurboXY(VB_DOWN_STC);
				} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {   //左下、始動
					_wayTurbo = DOWN_BEHIND;
					beginTurboXY(VB_DOWN_LEFT_STC);
				} else if (VB::isBeingPressed(VB_LEFT_STC)) {        //左、始動
					_wayTurbo = BEHIND;
					beginTurboXY(VB_LEFT_STC);
				} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {     //左上、始動
					_wayTurbo = UP_BEHIND;
					beginTurboXY(VB_UP_LEFT_STC);
				} else {

				}
			}
		}
	}

	//ターボ終了判定
	if (_dwFrameNextXYTurboOut == _dwFrame) {
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = true;
		_pMover -> setXYMoveVelocityRenge(0, 10000000);
		_wayTurbo = NONE;
	}
	if (_dwFrameNextZTurboOut == _dwFrame) {
		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = true;
		_pMover -> setZMoveVelocityRenge(0, sgn(_pMover->_iVelocity_ZMove)*10000000);
		_wayTurbo = NONE;
	}

	if (VB::isBeingPressed(VB_TURBO) && _isMoveZX) {
		int iTurboControl = abs(_pMover->_iVelocity_ZMove*_dRate_TurboControl);
		int iTurboControlRevers = abs(_pMover->_iVelocity_ZMove*_dRate_TurboControl);//どーすっかな

		//ZX通常移動
		if (VB::isBeingPressed(VB_UP_STC)) {
			if (VB::isPushedDown(VB_UP_STC)) {
				beginMoveZX(VB_UP_STC);
			}
			_Z += _iMoveSpeed + iTurboControl;
		} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {
			if (VB::isPushedDown(VB_UP_RIGHT_STC)) {
				beginMoveZX(VB_UP_RIGHT_STC);
			}
			_X += NANAME * (_iMoveSpeed + iTurboControl);
			_Z += NANAME * (_iMoveSpeed + iTurboControl);
		} else if (VB::isBeingPressed(VB_RIGHT_STC)) {
			if (VB::isPushedDown(VB_RIGHT_STC)) {
				beginMoveZX(VB_RIGHT_STC);
			}
			_X += _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {
			if (VB::isPushedDown(VB_DOWN_RIGHT_STC)) {
				beginMoveZX(VB_DOWN_RIGHT_STC);
			}
			_X += NANAME * (_iMoveSpeed + iTurboControl);
			_Z -= NANAME * (_iMoveSpeed + iTurboControl);
		} else if (VB::isBeingPressed(VB_DOWN_STC)) {
			if (VB::isPushedDown(VB_DOWN_STC)) {
				beginMoveZX(VB_DOWN_STC);
			}
			_Z -= _iMoveSpeed + iTurboControl;
		} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {
			if (VB::isPushedDown(VB_DOWN_LEFT_STC)) {
				beginMoveZX(VB_DOWN_LEFT_STC);
			}
			_X -= NANAME * (_iMoveSpeed + iTurboControl);
			_Z -= NANAME * (_iMoveSpeed + iTurboControl);
		} else if (VB::isBeingPressed(VB_LEFT_STC)) {
			if (VB::isPushedDown(VB_LEFT_STC)) {
				beginMoveZX(VB_LEFT_STC);
			}
			_X -= _iMoveSpeed + iTurboControl;
		} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {
			if (VB::isPushedDown(VB_UP_LEFT_STC)) {
				beginMoveZX(VB_UP_LEFT_STC);
			}
			_X -= NANAME * (_iMoveSpeed + iTurboControl);
			_Z += NANAME * (_iMoveSpeed + iTurboControl);
		} else {

		}
	} else {
		_isMoveZX = false;
		int iTurboControl = _pMover->_iVelocity_XYMove*_dRate_TurboControl;
		int iTurboControlRevers = _pMover->_iVelocity_XYMove*_dRate_TurboControl;//どーすっかな

		//XY通常移動
		if (VB::isBeingPressed(VB_UP_STC)) {
			if (VB::isPushedDown(VB_UP_STC)) {
				beginMoveXY(VB_UP_STC);
			}

			_Y += _iMoveSpeed + iTurboControl;
		} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {
			if (VB::isPushedDown(VB_UP_RIGHT_STC)) {
				beginMoveXY(VB_UP_RIGHT_STC);
			}
			_X += NANAME * (_iMoveSpeed + iTurboControl);
			_Y += NANAME * (_iMoveSpeed + iTurboControl);
		} else if (VB::isBeingPressed(VB_RIGHT_STC)) {
			if (VB::isPushedDown(VB_RIGHT_STC)) {
				beginMoveXY(VB_RIGHT_STC);
			}
			_X += _iMoveSpeed + iTurboControl;
		} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {
			if (VB::isPushedDown(VB_DOWN_RIGHT_STC)) {
				beginMoveXY(VB_DOWN_RIGHT_STC);
			} else {
				_X += NANAME * (_iMoveSpeed + iTurboControl);
				_Y -= NANAME * (_iMoveSpeed + iTurboControl);
			}
		} else if (VB::isBeingPressed(VB_DOWN_STC)) {
			if (VB::isPushedDown(VB_DOWN_STC)) {
				beginMoveXY(VB_DOWN_STC);
			}
			_Y -= _iMoveSpeed + iTurboControl;
		} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {
			if (VB::isPushedDown(VB_DOWN_LEFT_STC)) {
				beginMoveXY(VB_DOWN_LEFT_STC);
			}
			_X -= NANAME * (_iMoveSpeed + iTurboControl);
			_Y -= NANAME * (_iMoveSpeed + iTurboControl);
		} else if (VB::isBeingPressed(VB_LEFT_STC)) {
			if (VB::isPushedDown(VB_LEFT_STC)) {
				beginMoveXY(VB_LEFT_STC);
			}
			_X -= _iMoveSpeed + iTurboControl;
		} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {
			if (VB::isPushedDown(VB_UP_LEFT_STC)) {
				beginMoveXY(VB_UP_LEFT_STC);
			}
			_X -= NANAME * (_iMoveSpeed + iTurboControl);
			_Y += NANAME * (_iMoveSpeed + iTurboControl);
		} else {

		}
	}

//	if (_isMoveZX && VB::isReleasedUp(VB_TURBO)) {
//		_isMoveZX = false;
//	}

	//ショットボタン
	if (VB::isPushedDown(VB_SHOT1)) {
		MyShot001* pShot = (MyShot001*)GameGlobal::_pSceneCommon->_pMyShots001Rotation->obtain();
		if (pShot) {
			pShot->declarePlay();

			EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
			if (pExplo001) {
				pExplo001->declarePlay();
			}
		}
	}

	if (VB::isBeingPressed(VB_SHOT2)) {
		//RotationActorの性質上、末尾アクターが play していなければ、全ての要素が play していないことになる。
		RotationActor* pLasersStock = GameGlobal::_pSceneCommon->_pMyLaser001Rotation;
		MyLaser001* pLastLaser = (MyLaser001*)pLasersStock->getSubFirst()->getPrev();
		if (!pLastLaser->isPlaying() && !pLastLaser->_willPlayNextFrame) {
			MyLaser001* pLaser = (MyLaser001*)pLasersStock->obtain();
			if (pLaser) {
				MyLaser001::_pHeadMyLaser001 = pLaser;
				pLaser->declarePlay();
				GgafDx9SeManager::get("laser001")->play();
			}
		} else if (MyLaser001::_pHeadMyLaser001 != NULL) {
			MyLaser001* pLaser = (MyLaser001*)pLasersStock->obtain();
			if (pLaser) {
				pLaser->declarePlay();
			}
		}
	}


	if (VB::isBeingPressed(VB_POWERUP)) {
		_SX -= 100;
		_SY -= 100;
		_SZ -= 100;
	}
	if (VB::isBeingPressed(VB_GUARD)) {
		_SX+= 100;
		_SY+= 100;
		_SZ+= 100;
	}



	//ロール（仰角、俯角）を元に戻すフラグ発生
	if (_wayTurbo != UP &&
		_wayTurbo != UP_FRONT &&
		_wayTurbo != UP_BEHIND &&
		_wayTurbo != DOWN &&
		_wayTurbo != DOWN_FRONT &&
		_wayTurbo != DOWN_BEHIND &&
		_pMover->_angAxisRot[AXIS_Z] != 0 &&
		!VB::isBeingPressed(VB_UP_STC) &&
		!VB::isBeingPressed(VB_UP_RIGHT_STC) &&
		!VB::isBeingPressed(VB_UP_LEFT_STC) &&
		!VB::isBeingPressed(VB_DOWN_STC) &&
		!VB::isBeingPressed(VB_DOWN_RIGHT_STC) &&
		!VB::isBeingPressed(VB_DOWN_LEFT_STC) )
	{
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MNY, _angRZTopVelo_MNY);
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(_pMover->getDistanceFromAxisRotAngleTo(AXIS_Z, 0, TURN_CLOSE_TO))*_angRZAcce_MNY);
		_pMover -> setTargetAxisRotAngle(AXIS_Z, 0, TURN_BOTH);
	}

	//ピッチ（左右の傾き）を元に戻すフラグ発生
	if (_wayTurbo != ZLEFT &&
		_wayTurbo != ZLEFT_FRONT &&
		_wayTurbo != ZLEFT_BEHIND &&
		_wayTurbo != ZRIGHT &&
		_wayTurbo != ZRIGHT_FRONT &&
		_wayTurbo != ZRIGHT_BEHIND &&
		_pMover->_angAxisRot[AXIS_X] != 0 &&
		!VB::isBeingPressed(VB_UP_STC) &&
		!VB::isBeingPressed(VB_UP_RIGHT_STC) &&
		!VB::isBeingPressed(VB_UP_LEFT_STC) &&
		!VB::isBeingPressed(VB_DOWN_STC) &&
		!VB::isBeingPressed(VB_DOWN_RIGHT_STC) &&
		!VB::isBeingPressed(VB_DOWN_LEFT_STC) )
	{
		int rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_X, 0, TURN_CLOSE_TO);
		_pMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXAcce_MNZ);
		_pMover -> setTargetAxisRotAngle(AXIS_X, 0, TURN_BOTH);
	}


	//座標に反映
	_pMover -> behave();
}

//画面奥手前移動初め処理
void MyShip::beginTurboZX(int prm_VB) {
	switch(prm_VB) {

	case VB_UP_STC: //奥
		_isMoveZX = true;
		_dwFrameNextZTurboOut = _dwFrame + _dwIntervalZTurbo; //ターボ期間
		_dwFrameTurbo = 0; //リセット

		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT);
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRXAcce_MZT);

		_pMover -> setZMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setZMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setZMoveAcceleration(_iMvAcce_MT);
		break;

	case VB_UP_RIGHT_STC:
		break;

	case VB_RIGHT_STC:
		beginTurboXY(VB_RIGHT_STC);
		break;

	case VB_DOWN_RIGHT_STC:
		break;

	case VB_DOWN_STC:
		_isMoveZX = true;
		_dwFrameNextZTurboOut = _dwFrame + _dwIntervalZTurbo; //ターボ期間
		_dwFrameTurbo = 0; //リセット

		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -3000000, -1*_angRXBtmVelo_MZT);
		_pMover -> setAxisRotAngleVelocity(AXIS_X, -1*_angRXVelo_BeginMZT);
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRXAcce_MZT);
		_pMover -> setZMoveVelocityRenge(-1*_iMvBtmVelo_MT, -1*10000000);
		_pMover -> setZMoveVelocity(-1*_iMvVelo_BeginMT);
		_pMover -> setZMoveAcceleration(-1*_iMvAcce_MT);

		break;

	case VB_DOWN_LEFT_STC:
		break;

	case VB_LEFT_STC:
		beginTurboXY(VB_LEFT_STC);
		break;

	case VB_UP_LEFT_STC:
		break;

	default:
		throw_GgafCriticalException("MyShip::beginTurboZX prm_VB="<<prm_VB<<"はありえません");
		break;
	}

}

//XY座標ターボ始動時
void MyShip::beginTurboXY(int prm_VB) {

	_dwFrameNextXYTurboOut = _dwFrame + _dwIntervalXYTurbo; //ターボ期間
	_dwFrameTurbo = 0; //リセット

	switch(prm_VB) {

	case VB_UP_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, 3000000, _angRZBtmVelo_MYT);
		_pMover -> setAxisRotAngleVelocity(AXIS_Z, _angRZVelo_BeginMYT);
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MYT);
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(ANGLE90);
		break;

	case VB_UP_RIGHT_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, 3000000, _angRZBtmVelo_MYT);
		_pMover -> setAxisRotAngleVelocity(AXIS_Z, _angRZVelo_BeginMYT*NANAME); //斜めなので回転力減
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MYT);
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(ANGLE45);
		break;

	case VB_UP_LEFT_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, 3000000, _angRZBtmVelo_MYT);
		_pMover -> setAxisRotAngleVelocity(AXIS_Z, _angRZVelo_BeginMYT*NANAME); //斜めなので回転力減
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MYT);
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(ANGLE135);
		break;

	case VB_LEFT_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(ANGLE180);
		break;

	case VB_RIGHT_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(0);
		break;

	case VB_DOWN_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -300000, -1*_angRZBtmVelo_MYT);
		_pMover -> setAxisRotAngleVelocity(AXIS_Z, -1*_angRZVelo_BeginMYT);
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MYT);
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(-1*ANGLE90);
		break;

	case VB_DOWN_RIGHT_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -300000, -1*_angRZBtmVelo_MYT);
		_pMover -> setAxisRotAngleVelocity(AXIS_Z, -1*_angRZVelo_BeginMYT*NANAME);
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MYT);
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(-1*ANGLE45);
		break;

	case VB_DOWN_LEFT_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -300000, -1*_angRZBtmVelo_MYT);
		_pMover -> setAxisRotAngleVelocity(AXIS_Z, -1*_angRZVelo_BeginMYT*NANAME);
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MYT);
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(-1*ANGLE135);
		break;

	default:
		throw_GgafCriticalException("MyShip::beginTurboXY prm_VB="<<prm_VB<<"はありえません");
		break;
	}

}


//画面奥手前移動初め処理
void MyShip::beginMoveZX(int prm_VB) {
	switch(prm_VB) {

	case VB_UP_STC:
	case VB_UP_LEFT_STC:
	case VB_UP_RIGHT_STC:
//		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //Z回転角速度は引き継ぐため
//			_pMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZ);
//		}
//		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXTopVelo_MZ, -1*_angRXTopVelo_MZ);
//		_pMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
//		_pMover -> setTargetAxisRotAngle(AXIS_X, _angRXStop_MZ);
		break;

	case VB_RIGHT_STC:
		beginTurboXY(VB_RIGHT_STC);
		break;


	case VB_DOWN_STC:
	case VB_DOWN_LEFT_STC:
	case VB_DOWN_RIGHT_STC:
//		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //Z回転角速度は引き継ぐため
//			_pMover -> setAxisRotAngleVelocity(AXIS_X, -1.0*_angRXVelo_BeginMZ);
//		}
//		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXTopVelo_MZ, -1*_angRXTopVelo_MZ);
//		_pMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
//		_pMover -> setTargetAxisRotAngle(AXIS_X, -1*_angRXStop_MZ);
		break;

	case VB_LEFT_STC:
		beginTurboXY(VB_LEFT_STC);
		break;

	default:
		throw_GgafCriticalException("MyShip::beginMoveZX prm_VB="<<prm_VB<<"はありえません");
		break;
	}

}


//XY前移動初め処理
void MyShip::beginMoveXY(int prm_VB) {
	int rd;
	switch(prm_VB) {

	case VB_UP_STC: //仰角発生（＝正方向周り発生）
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) {  //けっこうな勢いで正方向(順)周りに回ってた場合
			//徐々にゆるやかに
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, _angRZTopVelo_MY, ANGLE180);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2); //角加速は負で徐々にゆるやかに
		} else if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //けっこうな勢いで負方向(逆)周りに回ってた場合                                          //負方向に回ってる場合
			//反発して逆周り
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*ANGLE180, _angRZTopVelo_MY);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2); //反発する正方向に角加速、通常の２倍角加速でいく
		} else {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_Z, _angRZStop_MY, TURN_CLOSE_TO);
			if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //停止している場合
				_pMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //初速
			}
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY); //近いほうに角加速
		}
		_pMover -> setTargetAxisRotAngle(AXIS_Z, _angRZStop_MY, TURN_BOTH, _angRZBtmVelo_MYT);
		break;

	case VB_UP_LEFT_STC:
	case VB_UP_RIGHT_STC:
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) {  //けっこうな勢いで正方向(順)周りに回ってた場合
			//徐々にゆるやかに
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, _angRZTopVelo_MY, ANGLE180);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2*NANAME); //角加速は負で徐々にゆるやかに
		} else if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //けっこうな勢いで負方向(逆)周りに回ってた場合                                          //負方向に回ってる場合
			//反発して逆周り
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*ANGLE180, _angRZTopVelo_MY);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2*NANAME); //反発する正方向に角加速、通常の２倍角加速でいく
		} else {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_Z, _angRZStop_MY*NANAME, TURN_CLOSE_TO);
			if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //停止している場合
				_pMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //初速
			}
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY*NANAME); //近いほうに角加速
		}
		_pMover -> setTargetAxisRotAngle(AXIS_Z, _angRZStop_MY*NANAME, TURN_BOTH, _angRZBtmVelo_MYT);
		break;

	case VB_RIGHT_STC:
		break;

	case VB_DOWN_STC: //俯角発生（＝負方向周り発生）
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) { //けっこうな勢いで正方向(逆)周りに回ってた場合
			//反発して逆周り
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, ANGLE180, -1*_angRZTopVelo_MY);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2); //反発する負方向に角加速、通常の２倍角加速でいく
		} else if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //けっこうな勢いで負方向(順)周りに回ってた場合                                           //負方向に回ってる場合
			//徐々にゆるやかに
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, -1*ANGLE180);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2); //角加速は正で徐々にゆるやかに
		} else {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_Z, -1*_angRZStop_MY, TURN_CLOSE_TO);
			if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //停止している場合
				_pMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //初速
			}
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY); //近いほうに角加速
		}
		_pMover -> setTargetAxisRotAngle(AXIS_Z, -1*_angRZStop_MY, TURN_BOTH, _angRZBtmVelo_MYT);
		break;

	case VB_DOWN_LEFT_STC:
	case VB_DOWN_RIGHT_STC:
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) { //けっこうな勢いで正方向(逆)周りに回ってた場合
			//反発して逆周り
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, ANGLE180, -1*_angRZTopVelo_MY);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2*NANAME); //反発する負方向に角加速、通常の２倍角加速でいく
		} else if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //けっこうな勢いで負方向(順)周りに回ってた場合                                           //負方向に回ってる場合
			//徐々にゆるやかに
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, -1*ANGLE180);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2*NANAME); //角加速は正で徐々にゆるやかに
		} else {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_Z, -1*_angRZStop_MY*NANAME, TURN_CLOSE_TO);
			if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //停止している場合
				_pMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //初速
			}
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY*NANAME); //近いほうに角加速
		}
		_pMover -> setTargetAxisRotAngle(AXIS_Z, -1*_angRZStop_MY*NANAME, TURN_BOTH, _angRZBtmVelo_MYT);
		break;

	case VB_LEFT_STC:
		break;

	default:
		throw_GgafCriticalException("MyShip::beginMoveXY prm_VB="<<prm_VB<<"はありえません");
		break;
	}

}







//画面奥へ移動終了X軸回転処理
void MyShip::onMoveZFinish() {
	//目標Angle0
	_pMover -> setTargetAxisRotAngle(AXIS_X, 0);
	//角度0に近いほうを探す
	int rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_X, _pMover->_angTarget_AxisRot[AXIS_X], TURN_CLOSE_TO);
	_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXTopVelo_MNZ, -1*_angRXTopVelo_MNZ);
	_pMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXAcce_MNZ);
}



void MyShip::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}


void MyShip::processOnHit(GgafActor* prm_pActor_Opponent) {
	declareFinishLife();
}


MyShip::~MyShip() {
}

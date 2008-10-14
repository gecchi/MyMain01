#include "stdafx.h"

#define newState(H,X) do { H->e = new State*[X]; for (int i = 0; i < X; i++) {H->e[i] = new State(); } } while(0)
#define S_OPTION 0

//√2
#define ROOT2 1.41421356






MyShip::MyShip(string prm_name, string prm_xname) : DefaultMeshActor(prm_name, prm_xname) {
	GameGlobal::_pMyShip = this;
	/** 移動スピードレベル */
	_lv_MoveSpeed = 1;
	/** 移動スピードレベルに相応する移動スピード */
	_iMoveSpeed = 1000;

	//CommonSceneがnewの場合設定
	_iShotKind01 = 0;
	_iShotKind02 = 0;
	_iShotKind03 = 0;

	//キャッシュロード
	GgafDx9SeManager::get("laser001");

	_iRXVelo_BMZ = 100;
	_iRXAcce_MZ = 100;
	_iRXTopVelo_MZ = 5000;
	_iRXStopAng_MZ = 85000;

	_iMVelo_BMT = 5000;
	_iMAcce_MT = -100;
	_iMBtmVelo_MT = 1000;

	_iRXVelo_BMZT = 10000;
	_iRXAcce_MZT = -200;
	_iRXBtmVelo_MZT = _iRXTopVelo_MZ;
	_iRXVelo_FMZT = _iRXTopVelo_MZ;

	_iRXTopVelo_NMZ = 2000;
	_iRXAcce_NMZ = 100;

}

void MyShip::initialize() {
	_isTurbo = false;
	_isZTurbo = false;
	_isMoveZX = false;
	_iVB_turbo = 0;
	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);
	_pMover -> setXYMoveVelocity(0);
}

void MyShip::processBehavior() {


	if (_isTurbo == false) {

		//奥手前移動初めのTURBOか否か
		if (VB::arePushedDownAtOnce(VB_TURBO, VB_UP_STC))  {               //奥、始動
			_isMoveZX = true;
			beginTurboZX(VB_UP_STC);
		} else if (VB::arePushedDownAtOnce(VB_TURBO, VB_DOWN_STC))  {      //手前、始動
			_isMoveZX = true;
			beginTurboZX(VB_DOWN_STC);
		} else if (VB::arePushedDownAtOnce(VB_TURBO, VB_UP_LEFT_STC)) {    //左斜め奥、始動
			_isMoveZX = true;
			beginTurboZX(VB_UP_LEFT_STC);
		} else if (VB::arePushedDownAtOnce(VB_TURBO, VB_UP_RIGHT_STC)) {   //右斜め奥、始動
			_isMoveZX = true;
			beginTurboZX(VB_UP_RIGHT_STC);
		} else if (VB::arePushedDownAtOnce(VB_TURBO, VB_DOWN_LEFT_STC)) {  //左斜め手前、始動
			_isMoveZX = true;
			beginTurboZX(VB_DOWN_LEFT_STC);
		} else if (VB::arePushedDownAtOnce(VB_TURBO, VB_DOWN_RIGHT_STC)) { //右斜め手前、始動
			_isMoveZX = true;
			beginTurboZX(VB_DOWN_RIGHT_STC);
		} else {
			//上下左右移動初めのTURBOか否か
			if (VB::isPushedDown(VB_TURBO)) {
				if (VB::isBeingPressed(VB_UP_STC)) {                 //上、始動
					beginTurboXY(VB_UP_STC);
				} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {    //右上、始動
					beginTurboXY(VB_UP_RIGHT_STC);
				} else if (VB::isBeingPressed(VB_RIGHT_STC)) {       //右、始動
					beginTurboXY(VB_RIGHT_STC);
				} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {  //右下、始動
					beginTurboXY(VB_DOWN_RIGHT_STC);
				} else if (VB::isBeingPressed(VB_DOWN_STC)) {        //下、始動
					beginTurboXY(VB_DOWN_STC);
				} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {   //右下、始動
					beginTurboXY(VB_DOWN_LEFT_STC);
				} else if (VB::isBeingPressed(VB_LEFT_STC)) {        //左、始動
					beginTurboXY(VB_LEFT_STC);
				} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {     //左上、始動
					beginTurboXY(VB_UP_LEFT_STC);
				} else {

				}
			}
		}
	} else { //turbo == true
		if (VB::isNotBeingPressed(VB_TURBO)) {
			_isTurbo = false;
		}
	}

	if (VB::isBeingPressed(VB_TURBO) && _isMoveZX) {
		//ZX通常移動
		if (VB::isBeingPressed(VB_UP_STC)) {
			if (VB::isPushedDown(VB_UP_STC)) {
				beginMoveZX(VB_UP_STC);
			}
			_Z += _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {
			if (VB::isPushedDown(VB_UP_RIGHT_STC)) {
				beginMoveZX(VB_UP_RIGHT_STC);
			}
			_X += ROOT2*_iMoveSpeed;
			_Z += ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_RIGHT_STC)) {
			if (VB::isPushedDown(VB_RIGHT_STC)) {
				beginMoveZX(VB_RIGHT_STC);
			}
			_X += _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {
			if (VB::isPushedDown(VB_DOWN_RIGHT_STC)) {
				beginMoveZX(VB_DOWN_RIGHT_STC);
			}
			_X += ROOT2*_iMoveSpeed;
			_Z -= ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_STC)) {
			if (VB::isPushedDown(VB_DOWN_STC)) {
				beginMoveZX(VB_DOWN_STC);
			}
			_Z -= _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {
			if (VB::isPushedDown(VB_DOWN_LEFT_STC)) {
				beginMoveZX(VB_DOWN_LEFT_STC);
			}
			_X -= ROOT2*_iMoveSpeed;
			_Z -= ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_LEFT_STC)) {
			if (VB::isPushedDown(VB_LEFT_STC)) {
				beginMoveZX(VB_LEFT_STC);
			}
			_X -= _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {
			if (VB::isPushedDown(VB_UP_LEFT_STC)) {
				beginMoveZX(VB_UP_LEFT_STC);
			}
			_X -= ROOT2*_iMoveSpeed;
			_Z += ROOT2*_iMoveSpeed;
		} else {

		}
	} else {
		//XY通常移動
		if (VB::isBeingPressed(VB_UP_STC)) {
			if (VB::isPushedDown(VB_UP_STC)) {
				beginMoveXY(VB_UP_STC);
			}
			_Y += _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {
			if (VB::isPushedDown(VB_UP_RIGHT_STC)) {
				beginMoveXY(VB_UP_RIGHT_STC);
			}
			_X += ROOT2*_iMoveSpeed;
			_Y += ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_RIGHT_STC)) {
			if (VB::isPushedDown(VB_RIGHT_STC)) {
				beginMoveXY(VB_RIGHT_STC);
			}
			_X += _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {
			if (VB::isPushedDown(VB_DOWN_RIGHT_STC)) {
				beginMoveXY(VB_DOWN_RIGHT_STC);
			} else {
				_X += ROOT2*_iMoveSpeed;
				_Y -= ROOT2*_iMoveSpeed;
			}
		} else if (VB::isBeingPressed(VB_DOWN_STC)) {
			if (VB::isPushedDown(VB_DOWN_STC)) {
				beginMoveXY(VB_DOWN_STC);
			}
			_Y -= _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {
			if (VB::isPushedDown(VB_DOWN_LEFT_STC)) {
				beginMoveXY(VB_DOWN_LEFT_STC);
			}
			_X -= ROOT2*_iMoveSpeed;
			_Y -= ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_LEFT_STC)) {
			if (VB::isPushedDown(VB_LEFT_STC)) {
				beginMoveXY(VB_LEFT_STC);
			}
			_X -= _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {
			if (VB::isPushedDown(VB_UP_LEFT_STC)) {
				beginMoveXY(VB_UP_LEFT_STC);
			}
			_X -= ROOT2*_iMoveSpeed;
			_Y += ROOT2*_iMoveSpeed;
		} else {

		}
	}

	if (_isMoveZX && VB::isReleasedUp(VB_TURBO)) {
		_isMoveZX = false;
	}

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

	//座標に反映
	_pMover -> behave();


}

//画面奥手前移動初め処理
void MyShip::beginTurboZX(int prm_VB) {
	_isTurbo = true;
	switch(prm_VB) {

	case VB_UP_STC:
		//?????
		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pMover -> setZMoveVelocityRenge(_iMBtmVelo_MT, 10000000);
		_pMover -> setZMoveVelocity(_iMVelo_BMT); //初速
		_pMover -> setZMoveAcceleration(_iMAcce_MT);
		//_pMover -> setXYMoveAngle(ANGLE90);

		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, _iRXBtmVelo_MZT, 360000);
		_pMover -> setAxisRotAngleVelocity(AXIS_X, _iRXVelo_BMZT);
		_pMover -> setAxisRotAngleAcceleration(AXIS_X, _iRXAcce_MZT);
		break;

	case VB_UP_RIGHT_STC:
		break;

	case VB_RIGHT_STC:
		beginTurboXY(VB_RIGHT_STC);
		break;

	case VB_DOWN_RIGHT_STC:
		break;

	case VB_DOWN_STC:
		//?????
		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pMover -> setZMoveVelocityRenge(-10000000, -1*_iMBtmVelo_MT);
		_pMover -> setZMoveVelocity(-1*_iMVelo_BMT); //初速
		_pMover -> setZMoveAcceleration(-1*_iMAcce_MT);
		//_pMover -> setXYMoveAngle(ANGLE90);

		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -360000, -1*_iRXBtmVelo_MZT);
		_pMover -> setAxisRotAngleVelocity(AXIS_X, -1*_iRXVelo_BMZT);
		_pMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_iRXAcce_MZT);
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


void MyShip::beginTurboXY(int prm_VB) {
	_isTurbo = true;
	switch(prm_VB) {

	case VB_UP_STC:

		break;

	case VB_UP_RIGHT_STC:
		break;

	case VB_RIGHT_STC:
		break;

	case VB_DOWN_RIGHT_STC:
		break;

	case VB_DOWN_STC:
		break;

	case VB_DOWN_LEFT_STC:
		break;

	case VB_LEFT_STC:
		break;

	case VB_UP_LEFT_STC:
		break;

	default:
		throw_GgafCriticalException("MyShip::beginTurboXY prm_VB="<<prm_VB<<"はありえません");
		break;
	}

}


//画面奥手前移動初め処理
void MyShip::beginMoveZX(int prm_VB) {
	_isTurbo = true;
	switch(prm_VB) {

	case VB_UP_STC:
	case VB_UP_LEFT_STC:
	case VB_UP_RIGHT_STC:
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //Z回転角速度は引き継ぐため
			_pMover -> setAxisRotAngleVelocity(AXIS_X, _iRXVelo_BMZ);
		}
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, _iRXTopVelo_MZ, -1*_iRXTopVelo_MZ);
		_pMover -> setAxisRotAngleAcceleration(AXIS_X, _iRXAcce_MZ);
		_pMover -> setTargetAxisRotAngle(AXIS_X, _iRXStopAng_MZ);
		break;

	case VB_RIGHT_STC:
		beginTurboXY(VB_RIGHT_STC);
		break;


	case VB_DOWN_STC:
	case VB_DOWN_LEFT_STC:
	case VB_DOWN_RIGHT_STC:
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //Z回転角速度は引き継ぐため
			_pMover -> setAxisRotAngleVelocity(AXIS_X, -1.0*_iRXVelo_BMZ);
		}
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, _iRXTopVelo_MZ, -1*_iRXTopVelo_MZ);
		_pMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_iRXAcce_MZ);
		_pMover -> setTargetAxisRotAngle(AXIS_X, -1*_iRXStopAng_MZ);
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
	switch(prm_VB) {

	case VB_UP_STC:
		break;

	case VB_UP_RIGHT_STC:
		break;

	case VB_RIGHT_STC:
		break;

	case VB_DOWN_RIGHT_STC:
		break;

	case VB_DOWN_STC:
		break;

	case VB_DOWN_LEFT_STC:
		break;

	case VB_LEFT_STC:
		beginTurboXY(VB_LEFT_STC);
		break;

	case VB_UP_LEFT_STC:
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
	_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, _iRXTopVelo_NMZ, -1*_iRXTopVelo_NMZ);
	_pMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_iRXAcce_NMZ);
}



void MyShip::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

/*
bool MyShip::processBumpChkLogic(GgafDx9UntransformedActor* prm_pActor_Opponent) {
	//TRACE("MyShip::processBumpChkLogic "+getPlatformScene()->getName()+"."+getName()+"ｘ"+prm_pActor_Opponent->getPlatformScene()->getName()+"."+prm_pActor_Opponent->getName());
	return false;
}
*/

void MyShip::processOnHit(GgafActor* prm_pActor_Opponent) {
	declareFinishLife();
}


MyShip::~MyShip() {
}

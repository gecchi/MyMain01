#include "stdafx.h"

#define newState(H,X) do { H->e = new State*[X]; for (int i = 0; i < X; i++) {H->e[i] = new State(); } } while(0)
#define S_OPTION 0

//√2
#define ROOT2 1.41421356

//画面奥へ通常移動する時のX軸回転角速度の初速度(>0)
//Rot X Velocity when I Move Z Plus Begin
#define RXV_MZPB 100
//画面奥へ通常移動中のX軸回転角速度の角加速度
//Rot X Acceleration while I Move Z Plus
#define RXA_MZP 100

//画面手前へ通常移動する時のX軸回転角速度の初速度(<0)
//Rot X Velocity when I Move Z Minus Begin
#define RXV_MZMB (-100)
//画面手前へ通常移動中のX軸回転角速度の角加速度
//Rot X Acceleration while I Move Z Minus
#define RXA_MZM (-100)

//通常Z移動中のX軸回転角速度の上限角速度
//Rot X Top Velocity while I Move Z
#define RXTV_MZ 4000
//通常Z移動中のX軸回転角速度の下限角速度
//Rot X Bottom Velocity while I Move Z
#define RXBV_MZ (-4000)

//画面奥へ通常Z移動中のX軸回転角の停止角度
//Rot X Stop Angle while I Move Z Plus
#define RXSAn_MZP 85000
//画面手前へ移動中のX軸回転角速度の上限角度
//Rot X Stop Angle while I Move Z Minus
#define RXSAn_MZM (-85000)

//自動的にAngle0に戻ろうとするX軸回転角速度の上限角度
//Rot X Top Velocity while I do Not Move Z
#define RXTV_NMZ 2000
//自動的にAngle0に戻ろうとするX軸回転角速度の下限角度
//Rot X Bottom Velocity while I do Not Move Z
#define RXBV_NMZ (-2000)
//自動的にAngle0に戻ろうとするX軸回転角加速度(正負共通)
//Rot X Acceleration while I do Not Move Z
#define RXA_NMZ 100






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


	//_state->e = new State[10];

}

void MyShip::initialize() {
	_turboFlg = false;
	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);
	_pMover -> setXYMoveVelocity(0);
}

void MyShip::processBehavior() {


	if (VB::isBeingPressed(VB_TURBO)) {
		if (VB::isPushedDown(VB_TURBO)) {
			//奥手前移動初め
			if (VB::isBeingPressed(VB_UP_STC))  {
				onMoveZPlusBegin();
			} else if (VB::isBeingPressed(VB_DOWN_STC))  {
				onMoveZMinusBegin();
			} else if (VB::isBeingPressed(VB_UP_LEFT_STC) || VB::isBeingPressed(VB_UP_RIGHT_STC)) 	{
				onMoveZPlusBegin();
			} else if (VB::isBeingPressed(VB_DOWN_STC) || VB::isBeingPressed(VB_DOWN_STC)) {
				onMoveZMinusBegin();
			} else {

			}
		} else {
			//奥手前移動初め
			if (VB::isPushedDown(VB_UP_STC))  {
				onMoveZPlusBegin();
			} else if (VB::isPushedDown(VB_DOWN_STC))  {
				onMoveZMinusBegin();
			} else if (VB::isPushedDown(VB_UP_LEFT_STC) || VB::isPushedDown(VB_UP_RIGHT_STC)) 	{
				onMoveZPlusBegin();
			} else if (VB::isPushedDown(VB_DOWN_STC) || VB::isPushedDown(VB_DOWN_STC)) {
				onMoveZMinusBegin();
			} else {
			}
		}

		//奥手前移動終了
		if (VB::isReleasedUp(VB_UP_STC))  {
			onMoveZFinish();
		} else if (VB::isReleasedUp(VB_DOWN_STC))  {
			onMoveZFinish();
		} else if (VB::isReleasedUp(VB_UP_LEFT_STC) || VB::isReleasedUp(VB_UP_RIGHT_STC)) 	{
			onMoveZFinish();
		} else if (VB::isReleasedUp(VB_DOWN_STC) || VB::isReleasedUp(VB_DOWN_STC)) {
			onMoveZFinish();
		} else {

		}

		//ZY移動
		if (VB::isBeingPressed(VB_UP_STC)) {
			_Z += _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {
			_X += ROOT2*_iMoveSpeed;
			_Z += ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_RIGHT_STC)) {
			_X += _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {
			_X += ROOT2*_iMoveSpeed;
			_Z -= ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_STC)) {
			_Z -= _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {
			_X -= ROOT2*_iMoveSpeed;
			_Z -= ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_LEFT_STC)) {
			_X -= _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {
			_X -= ROOT2*_iMoveSpeed;
			_Z += ROOT2*_iMoveSpeed;
		} else {

		}

	} else {
		if (VB::isReleasedUp(VB_TURBO)) {
			//奥手前移動終了
			if (VB::isBeingPressed(VB_UP_STC))  {
				onMoveZFinish();
			} else if (VB::isBeingPressed(VB_DOWN_STC))  {
				onMoveZFinish();
			} else if (VB::isBeingPressed(VB_UP_LEFT_STC) || VB::isBeingPressed(VB_UP_RIGHT_STC)) 	{
				onMoveZFinish();
			} else if (VB::isBeingPressed(VB_DOWN_STC) || VB::isBeingPressed(VB_DOWN_STC)) {
				onMoveZFinish();
			} else {

			}
		} else {
		}

		//XY移動
		if (VB::isBeingPressed(VB_UP_STC)) {
			_Y += _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {
			_X += ROOT2*_iMoveSpeed;
			_Y += ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_RIGHT_STC)) {
			_X += _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {
			_X += ROOT2*_iMoveSpeed;
			_Y -= ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_STC)) {
			_Y -= _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {
			_X -= ROOT2*_iMoveSpeed;
			_Y -= ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_LEFT_STC)) {
			_X -= _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {
			_X -= ROOT2*_iMoveSpeed;
			_Y += ROOT2*_iMoveSpeed;
		} else {

		}
	}

//	//奥手前移動初め
//	if (VB::isPushedDown(VB_UP_STC))  {
//		onMoveZPlusBegin();
//	} else if (VB::isPushedDown(VB_DOWN_STC))  {
//		onMoveZMinusBegin();
//	} else if (VB::isPushedDown(VB_UP_LEFT_STC) || VB::isPushedDown(VB_UP_RIGHT_STC)) 	{
//		onMoveZPlusBegin();
//	} else if (VB::isPushedDown(VB_DOWN_STC) || VB::isPushedDown(VB_DOWN_STC)) {
//		onMoveZMinusBegin();
//	}

//	//奥手前移動初め
//	if (VB::arePushedDownAtOnce(VB_TURBO, VB_UP_STC))  {
//		onMoveZPlusBegin();
//	} else if (VB::arePushedDownAtOnce(VB_TURBO, VB_DOWN_STC))  {
//		onMoveZMinusBegin();
//	} else if (VB::arePushedDownAtOnce(VB_TURBO, VB_UP_LEFT_STC) ||
//			   VB::arePushedDownAtOnce(VB_TURBO, VB_UP_RIGHT_STC) )
//	{
//		onMoveZPlusBegin();
//	} else if (VB::arePushedDownAtOnce(VB_TURBO, VB_DOWN_STC) ||
//				   VB::arePushedDownAtOnce(VB_TURBO, VB_DOWN_STC) )
//	{
//		onMoveZMinusBegin();
//	}


//	if (VB::isBeingPressed(VB_TURBO) && VB::isPushedDown(VB_UP) ) {
//		_pMover -> setTargetAxisRotAngle(AXIS_X, 85*1000);
//		int rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_X, _pMover->_angTarget_AxisRot[AXIS_X], TURN_CLOSE_TO);
//		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 360*1000, 1*1000);
//		_pMover -> setAxisRotAngleVelocity(AXIS_X, rd/13);
//		_pMover -> setAxisRotAngleAcceleration(AXIS_X, -700);
//
//	} else if ( (VB::isBeingPressed(VB_TURBO) && VB::isPushedDown(VB_DOWN) && VB::isNotBeingPressed(VB_UP)) ||
//	            (VB::isBeingPressed(VB_TURBO) && VB::isBeingPressed(VB_DOWN) && VB::isReleasedUp(VB_UP) )) {
//		_pMover -> setTargetAxisRotAngle(AXIS_X, 275*1000);
//		int rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_X, _pMover->_angTarget_AxisRot[AXIS_X], TURN_CLOSE_TO);
//		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*1000, -360*1000);
//		_pMover -> setAxisRotAngleVelocity(AXIS_X, rd/13);
//		_pMover -> setAxisRotAngleAcceleration(AXIS_X, +700);
//	}
//
//	if (VB::isNotBeingPressed(VB_TURBO) && _pMover ->_iVelocity_XYMove < 2*2000) {
//		_turboFlg = false;
//		_pMover -> setXYMoveVelocityRenge(100*1000, -100*1000);
//		_pMover -> setXYMoveVelocity(0);
//		_pMover -> setXYMoveAcceleration(0);
//
//		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = true;
//		if (sgn(_pMover->_angVelocity_AxisRotAngle[AXIS_X]) > 0) {
//			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 360*1000, 1*1000);
//			_pMover -> setAxisRotAngleVelocity(AXIS_X, 6*1000);
//			_pMover -> setAxisRotAngleAcceleration(AXIS_X, 0);
//		} else if (sgn(_pMover->_angVelocity_AxisRotAngle[AXIS_X]) < 0) {
//			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*1000, -360*1000);
//			_pMover -> setAxisRotAngleVelocity(AXIS_X, -6*1000);
//			_pMover -> setAxisRotAngleAcceleration(AXIS_X, 0);
//		}
//		if (VB::isBeingPressed(VB_UP)) {
//			_pMover -> setTargetAxisRotAngle(AXIS_X, 85*1000);
//		} else if (VB::isBeingPressed(VB_DOWN)) {
//			_pMover -> setTargetAxisRotAngle(AXIS_X, 275*1000);
//		}
//	}
//
//
//	if (_turboFlg != true && VB::isPushedDown(VB_TURBO) && !VB::isBeingPressed(VB_NEUTRAL_STC)) {
//		_turboFlg = true;
//		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
//		_pMover -> setXYMoveVelocityRenge(100*1000, 1*1000);
//		_pMover -> setXYMoveVelocity(12*1000); //初速15px
//		_pMover -> setXYMoveAcceleration(-500); //毎フレーム初速0.5px減速
//
//		if (VB::isBeingPressed(VB_UP_STC)) {
//			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 360*1000, 1*1000);
//			_pMover -> setAxisRotAngleVelocity(AXIS_X, 20*1000);
//			_pMover -> setAxisRotAngleAcceleration(AXIS_X, 0);
//			_pMover -> setXYMoveAngle(ANGLE90);
//		} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {
//			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 360*1000, 1*1000);
//			_pMover -> setAxisRotAngleVelocity(AXIS_X, 20*1000);
//			_pMover -> setAxisRotAngleAcceleration(AXIS_X, -500);
//			_pMover -> setXYMoveAngle(ANGLE45);
//		} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {
//			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 360*1000, 1*1000);
//			_pMover -> setAxisRotAngleVelocity(AXIS_X, 20*1000);
//			_pMover -> setAxisRotAngleAcceleration(AXIS_X, -500);
//			_pMover -> setXYMoveAngle(ANGLE135);
//		} else if (VB::isBeingPressed(VB_DOWN_STC)) {
//			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*1000, -360*1000);
//			_pMover -> setAxisRotAngleVelocity(AXIS_X, -20*1000);
//			_pMover -> setAxisRotAngleAcceleration(AXIS_X, +500);
//			_pMover -> setXYMoveAngle(ANGLE270);
//		} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {
//			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*1000, -360*1000);
//			_pMover -> setAxisRotAngleVelocity(AXIS_X, -20*1000);
//			_pMover -> setAxisRotAngleAcceleration(AXIS_X, +500);
//			_pMover -> setXYMoveAngle(ANGLE315);
//		} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {
//			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*1000, -360*1000);
//			_pMover -> setAxisRotAngleVelocity(AXIS_X, -20*1000);
//			_pMover -> setAxisRotAngleAcceleration(AXIS_X, +500);
//			_pMover -> setXYMoveAngle(ANGLE225);
//		} else if (VB::isBeingPressed(VB_LEFT_STC)) {
//			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 0, 0);
//			_pMover -> setAxisRotAngleVelocity(AXIS_X, 0);
//			_pMover -> setAxisRotAngleAcceleration(AXIS_X, 0);
//			_pMover -> setXYMoveAngle(ANGLE180);
//		} else if (VB::isBeingPressed(VB_RIGHT_STC)) {
//			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 0, 0);
//			_pMover -> setAxisRotAngleVelocity(AXIS_X, 0);
//			_pMover -> setAxisRotAngleAcceleration(AXIS_X, 0);
//			_pMover -> setXYMoveAngle(0);
//		}  else {
//			_TRACE_("ぶおーん！");
//		}
//	}
//


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

//画面奥へ移動初めX軸回転処理
void MyShip::onMoveZPlusBegin() {
	if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //Z回転角速度は引き継ぐため
		_pMover -> setAxisRotAngleVelocity(AXIS_X, RXV_MZPB);
	}
	_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, RXTV_MZ, RXBV_MZ);
	_pMover -> setAxisRotAngleAcceleration(AXIS_X, RXA_MZP);
	_pMover -> setTargetAxisRotAngle(AXIS_X, RXSAn_MZP);
}

//画面手前へ移動初めX軸回転処理
void MyShip::onMoveZMinusBegin() {
	if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //Z回転角速度は引き継ぐため
		_pMover -> setAxisRotAngleVelocity(AXIS_X, RXV_MZMB);
	}
	_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, RXTV_MZ, RXBV_MZ);
	_pMover -> setAxisRotAngleAcceleration(AXIS_X, RXA_MZM);
	_pMover -> setTargetAxisRotAngle(AXIS_X, RXSAn_MZM);
}

//画面奥へ移動終了X軸回転処理
void MyShip::onMoveZFinish() {
	//目標Angle0
	_pMover -> setTargetAxisRotAngle(AXIS_X, 0);
	//角度0に近いほうを探す
	int rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_X, _pMover->_angTarget_AxisRot[AXIS_X], TURN_CLOSE_TO);
	_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, RXTV_NMZ, RXBV_NMZ);
	_pMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*RXA_NMZ);
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

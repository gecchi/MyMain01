#include "stdafx.h"

#define newState(H,X) do { H->e = new State*[X]; for (int i = 0; i < X; i++) {H->e[i] = new State(); } } while(0)
#define S_OPTION 0

//1/√2
#define NANAME 0.7






MyShip::MyShip(string prm_name, string prm_model) : DefaultMeshActor(prm_name, prm_model) {
	_class_name = "MyShip";
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
	//GgafDx9SeManager::get("laser001");

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



	_angRZVelo_BeginMY = 100;	//上又は下へ通常移動開始時のZ軸回転角速度の初速度
	_angRZTopVelo_MY = 2000;	//上又は下へ移動中のZ軸回転角速度の上限角速度
	_angRZAcce_MY = 200;		//上又は下へ通常移動中のZ軸回転角速度の角加速度
	_angRZStop_MY = 30000;		//上又は下へ通常Z移動中のZ軸回転角の停止角度

	_iMvBtmVelo_MT = -1*_iMoveSpeed;		//TURBO移動中の移動速度の最低速度
	_iMvVelo_BeginMT = _iMoveSpeed*3;	//TURBO移動開始時の移動速度の初速度
	_iMvAcce_MT = -100;					//TURBO移動中の移動速度の加速度

	_iMvAcce_EOD_MT = 100;			//TURBO中に逆方向に入力される事により減速する速度

	_angRZVelo_BeginMYT = 13000;	//上又は下へTURBO移動開始時のZ軸回転角速度の初速度
	_angRZAcce_MYT = -200;			//上又は下へTURBO移動中のZ軸回転角速度の角加速度
	_angRZBtmVelo_MYT = 3000;		//上又は下へTURBO移動中のZ軸回転角速度の最低速度

	_angRZTopVelo_MNY = 2000;		//上又は下へ通常移動時、自動的にAngle0に戻ろうとするZ軸回転角速度の上限角速度
	_angRZAcce_MNY = 100;			//上又は下へ通常移動時、自動的にAngle0に戻ろうとする時のZ軸回転角加速度(正負共通)

	_angRXVelo_BeginMZT = 15000;	//奥又は手前へTURBO移動開始時のX軸回転角速度の初速度
	_angRXAcce_MZT = -300;			//奥又は手前へTURBO移動中のX軸回転角速度の角加速度
	_angRXBtmVelo_MZT = 5000;		//奥又は手前へTURBO移動中のX軸回転角速度の最低速度

	_angRXTopVelo_MNZ = 2000; 		//奥又は手前以外の通常移動時、自動的にAngle0に戻ろうとするX軸回転角速度の上限角速度
	_angRXAcce_MNZ = 100;			//奥又は手前以外の通常移動時、自動的にAngle0に戻ろうとする時のX軸回転角加速度(正負共通)

	_angRXTopVelo_MZ = 4000;		//奥又は手前へ移動中のX軸回転角速度の上限角速度
	_angRXAcce_MZ = 200;			//奥又は手前へ通常移動中のX軸回転角速度の角加速度
	_angRXStop_MZ = 80000;			//奥又は手前へ通常Z移動中のX軸回転角の停止角度
	_angRXVelo_BeginMZ = 500;		//奥又は手前へ通常移動開始時のX軸回転角速度の初速度

	_dwFrameNextXYTurboOut = 0;	//XY次回ターボ終了フレーム
	_dwIntervalXYTurbo = 60;	//XYターボ終了フレーム間隔

	_dwFrameNextZXTurboOut = 0;	//Z次回ターボ終了フレーム
	_dwIntervalZXTurbo = 60;		//Zターボ終了フレーム間隔

	_dwFrameTurboMove = 0;			//ターボ経過フレーム
	_dwFrameNomalMove = 0;			//通常移動経過フレーム
	_isMoveZX = false;
	_wayTurbo = NONE;
	_dRate_TurboControl = 0.8; //ターボ中移動制御できる割合
	_iTurboControl = 0;

	_pMyShots001Rotation = NEW RotationActor("RotShot001");
	addSubLast(_pMyShots001Rotation); //仮所属
	MyShot001* pShot;
	for (int i = 0; i < 50; i++) { //自弾ストック
		pShot = NEW MyShot001("MY_S"+GgafUtil::itos(i), "moji2");
		pShot->stopImmediately();
		_pMyShots001Rotation->addSubLast(pShot);
	}

	_pMyWaves001Rotation = NEW RotationActor("RotWave001");
	addSubLast(_pMyWaves001Rotation);//仮所属
	MyWave001* pWave;
	for (int i = 0; i < 50; i++) { //自弾ストック
		pWave = NEW MyWave001("MY_W"+GgafUtil::itos(i), "wave");
		pWave->stopImmediately();
		_pMyWaves001Rotation->addSubLast(pWave);
	}


	_pMyLaserChipRotation = NEW RotationActor("RotLaser001");
	addSubLast(_pMyLaserChipRotation);//仮所属
	MyLaserChip* pChip;
	for (int i = 0; i < 100; i++) { //レーザーストック
		pChip = NEW MyLaserChip("MY_L"+GgafUtil::itos(i), "laserchip9");
		pChip->stopImmediately();
		_pMyLaserChipRotation->addSubLast(pChip);
	}

	for (int i = 0; i < 10; i++) { //レーザーストック
		MyOption* pOption = NEW MyOption("MY_OPTION"+GgafUtil::itos(i), "ebi");
		pOption->stopImmediately();
		addSubLast(pOption);
	}


}

void MyShip::initialize() {
	_TRACE_("MyShip::initialize!!!!!!!!!!!!!!!!!!!!!!");
	getLordActor()->accept(KIND_MY_SHOT_GU, _pMyShots001Rotation->tear());
	getLordActor()->accept(KIND_MY_SHOT_GU, _pMyWaves001Rotation->tear());
	getLordActor()->accept(KIND_MY_SHOT_GU, _pMyLaserChipRotation->tear());

	_pChecker -> useHitArea(1);
	_pChecker -> setHitArea(0, -10000, -10000, 10000, 10000);
	_pGeoMover -> setMoveVelocity(0);
	//_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Y, -300000, -300000);
	_pGeoMover -> setAxisRotAngleVelocity(AXIS_Y,1000);
	//_RZ = ANGLE90;
	//setAlpha(0.2);


//	LPDIRECT3DVERTEXBUFFER9 pIDirect3DVertexBuffer9_MyShip;
//	BYTE*              pVertexSrc;
//	DWORD  vtxFmt;
//	DWORD  FVFSize;
//
//	DWORD numV = _pMeshModel->_pID3DXMesh->GetNumVertices();
//	_pMeshModel->_pID3DXMesh->GetVertexBuffer(&pIDirect3DVertexBuffer9_MyShip);
//	pIDirect3DVertexBuffer9_MyShip->Lock(0, 0, (void**)&pVertexSrc,0);
//
//	//頂点フォーマットのサイズを取得
//	vtxFmt = _pMeshModel->_pID3DXMesh->GetFVF();
//	FVFSize = D3DXGetFVFVertexSize( vtxFmt );
//
//
//	for(int i = 0; i < numV; i++){
//		D3DVECTOR* pV;
//
//	  //D3DFVF_XYZは先頭にあるので、オフセットは０
//	  pV = (D3DVECTOR*)( pVertexSrc + (FVFSize * i) + 0 );
//	  _TRACE_("頂点"<<(i+1)<<":("<<(pV->x)<<","<<(pV->y)<<","<<(pV->z)<<")");
//
////	  //次にUVがあるので、D3DFVF_XYZのサイズ分だけ進めた位置から取り出す
////	  uv = *(D3DXVECTOR2*)( pVtx + (FVFSize * i) + sizeof(D3DXVECTOR3) );
////
////	  ～v0が頂点座標,uvがその頂点のテクスチャー座標～
//
//	}
//
//
//    pIDirect3DVertexBuffer9_MyShip->Unlock();
//    RELEASE_IMPOSSIBLE_NULL(pIDirect3DVertexBuffer9_MyShip);



}

void MyShip::processBehavior() {


	_tmpX = _X;
	_tmpY = _Y;
	_tmpZ = _Z;
	_dwFrameTurboMove++; // ターボ経過フレーム
	_dwFrameNomalMove++; // 通常移動経過フレーム
	//奥手前移動初めのTURBOか否か
	if (_dwFrameTurboMove > 1 && _dwFrameNomalMove > 1 && VB::isBeingPressed(VB_TURBO)) {
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
					_isMoveZX = true;
				}
			}
		}
	}

	//ターボ終了判定
	if (_dwFrameNextXYTurboOut == _dwFrame) {
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_Z] = true;
		_pGeoMover -> setMoveVelocityRenge(0, 10000000);
		_wayTurbo = NONE;
	}
	if (_dwFrameNextZXTurboOut == _dwFrame) {
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_X] = true;
		_pGeoMover -> setMoveVelocityRenge(0, 10000000);
		_wayTurbo = NONE;
	}

	if (_wayTurbo == NONE) {
		_iTurboControl = 0;
	} else {
		_iTurboControl = _pGeoMover->_iVelocity_Move*_dRate_TurboControl;
	}

	if (VB::isBeingPressed(VB_TURBO) && _isMoveZX) {
		//ZX通常移動
		if (VB::isBeingPressed(VB_UP_STC)) {
			if (VB::isPushedDown(VB_UP_STC)) {
				beginMoveZX(VB_UP_STC);
			} else if (_wayTurbo == ZRIGHT) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_Z += _iMoveSpeed + _iTurboControl;
			}
		} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {
			if (VB::isPushedDown(VB_UP_RIGHT_STC)) {
				beginMoveZX(VB_UP_RIGHT_STC);
			} else if (_wayTurbo == ZRIGHT_BEHIND) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_X += NANAME * (_iMoveSpeed + _iTurboControl);
				_Z += NANAME * (_iMoveSpeed + _iTurboControl);
			}
		} else if (VB::isBeingPressed(VB_RIGHT_STC)) {
			if (VB::isPushedDown(VB_RIGHT_STC)) {
				beginMoveZX(VB_RIGHT_STC);
			} else if (_wayTurbo == BEHIND) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_X += _iMoveSpeed;
			}
		} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {
			if (VB::isPushedDown(VB_DOWN_RIGHT_STC)) {
				beginMoveZX(VB_DOWN_RIGHT_STC);
			} else if (_wayTurbo == ZLEFT_BEHIND) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_X += NANAME * (_iMoveSpeed + _iTurboControl);
				_Z -= NANAME * (_iMoveSpeed + _iTurboControl);
			}
		} else if (VB::isBeingPressed(VB_DOWN_STC)) {
			if (VB::isPushedDown(VB_DOWN_STC)) {
				beginMoveZX(VB_DOWN_STC);
			} else if (_wayTurbo == ZLEFT) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_Z -= _iMoveSpeed + _iTurboControl;
			}
		} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {
			if (VB::isPushedDown(VB_DOWN_LEFT_STC)) {
				beginMoveZX(VB_DOWN_LEFT_STC);
			} else if (_wayTurbo == ZLEFT_FRONT) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_X -= NANAME * (_iMoveSpeed + _iTurboControl);
				_Z -= NANAME * (_iMoveSpeed + _iTurboControl);
			}
		} else if (VB::isBeingPressed(VB_LEFT_STC)) {
			if (VB::isPushedDown(VB_LEFT_STC)) {
				beginMoveZX(VB_LEFT_STC);
			} else if (_wayTurbo == FRONT) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_X -= _iMoveSpeed + _iTurboControl;
			}
		} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {
			if (VB::isPushedDown(VB_UP_LEFT_STC)) {
				beginMoveZX(VB_UP_LEFT_STC);
			} else if (_wayTurbo == ZRIGHT_FRONT) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_X -= NANAME * (_iMoveSpeed + _iTurboControl);
				_Z += NANAME * (_iMoveSpeed + _iTurboControl);
			}
		} else {

		}
	} else {
		_isMoveZX = false;
		//XY通常移動
		if (VB::isBeingPressed(VB_UP_STC)) {
			if (VB::isPushedDown(VB_UP_STC)) {
				beginMoveXY(VB_UP_STC);
			} else if (_wayTurbo == DOWN) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_Y += _iMoveSpeed + _iTurboControl;
			}
		} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {
			if (VB::isPushedDown(VB_UP_RIGHT_STC)) {
				beginMoveXY(VB_UP_RIGHT_STC);
			} else if (_wayTurbo == DOWN_BEHIND) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_X += NANAME * (_iMoveSpeed + _iTurboControl);
				_Y += NANAME * (_iMoveSpeed + _iTurboControl);
			}
		} else if (VB::isBeingPressed(VB_RIGHT_STC)) {
			if (VB::isPushedDown(VB_RIGHT_STC)) {
				beginMoveXY(VB_RIGHT_STC);
			} else if (_wayTurbo == BEHIND) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_X += _iMoveSpeed + _iTurboControl;
			}
		} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {
			if (VB::isPushedDown(VB_DOWN_RIGHT_STC)) {
				beginMoveXY(VB_DOWN_RIGHT_STC);
			} else if (_wayTurbo == UP_BEHIND) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_X += NANAME * (_iMoveSpeed + _iTurboControl);
				_Y -= NANAME * (_iMoveSpeed + _iTurboControl);
			}
		} else if (VB::isBeingPressed(VB_DOWN_STC)) {
			if (VB::isPushedDown(VB_DOWN_STC)) {
				beginMoveXY(VB_DOWN_STC);
			} else if (_wayTurbo == UP) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_Y -= _iMoveSpeed + _iTurboControl;
			}
		} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {
			if (VB::isPushedDown(VB_DOWN_LEFT_STC)) {
				beginMoveXY(VB_DOWN_LEFT_STC);
			} else if (_wayTurbo == UP_FRONT) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_X -= NANAME * (_iMoveSpeed + _iTurboControl);
				_Y -= NANAME * (_iMoveSpeed + _iTurboControl);
			}
		} else if (VB::isBeingPressed(VB_LEFT_STC)) {
			if (VB::isPushedDown(VB_LEFT_STC)) {
				beginMoveXY(VB_LEFT_STC);
			} else if (_wayTurbo == FRONT) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_X -= _iMoveSpeed + _iTurboControl;
			}
		} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {
			if (VB::isPushedDown(VB_UP_LEFT_STC)) {
				beginMoveXY(VB_UP_LEFT_STC);
			} else if (_wayTurbo == DOWN_FRONT) {
				_pGeoMover->setMoveVelocity(_pGeoMover->_iVelocity_Move - _iMvAcce_EOD_MT);
			} else {
				_X -= NANAME * (_iMoveSpeed + _iTurboControl);
				_Y += NANAME * (_iMoveSpeed + _iTurboControl);
			}
		} else {

		}
	}

	//ショット関連処理
	//MyShip::transactShot(this);
	if (VB::isPushedDown(VB_SHOT1)) {
		MyShot001* pShot = (MyShot001*)_pMyShots001Rotation->obtain();
		if (pShot != NULL) {
			pShot->declarePlay();

			EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
			if (pExplo001 != NULL) {
				pExplo001->setGeometry(this);
				pExplo001->declarePlay();
			}
		}
	}

	if (VB::isBeingPressed(VB_SHOT2)) {
		//RotationActorの性質上、末尾アクターが play していなければ、全ての要素が play していないことになる。
		MyLaserChip* pLaser = (MyLaserChip*)_pMyLaserChipRotation->obtain();
		if (pLaser != NULL) {
			pLaser->setRadicalActor(this);
			pLaser->_dwFrame_switchedToPlay = _dwFrame;
			pLaser->declarePlay();
		}
	}

	//ショットボタン
	if (VB::arePushedDownAtOnce(VB_SHOT1, VB_SHOT2)) {
		MyWave001* pWave = (MyWave001*)_pMyWaves001Rotation->obtain();
		if (pWave != NULL) {
			pWave->declarePlay();

			EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
			if (pExplo001 != NULL) {
				pExplo001->setGeometry(this);
				pExplo001->declarePlay();
			}
		}
	}


	if (VB::isPushedDown(VB_SHOT3)) {
		equipOption();
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
		_pGeoMover->_angAxisRot[AXIS_Z] != 0 &&
		!VB::isBeingPressed(VB_UP_STC) &&
		!VB::isBeingPressed(VB_UP_RIGHT_STC) &&
		!VB::isBeingPressed(VB_UP_LEFT_STC) &&
		!VB::isBeingPressed(VB_DOWN_STC) &&
		!VB::isBeingPressed(VB_DOWN_RIGHT_STC) &&
		!VB::isBeingPressed(VB_DOWN_LEFT_STC) )
	{
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MNY, _angRZTopVelo_MNY);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(_pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_Z, 0, TURN_CLOSE_TO))*_angRZAcce_MNY);
		_pGeoMover -> setTargetAxisRotAngle(AXIS_Z, 0, TURN_BOTH);
	}

	//ピッチ（左右の傾き）を元に戻すフラグ発生
	if (_wayTurbo != ZLEFT &&
		_wayTurbo != ZLEFT_FRONT &&
		_wayTurbo != ZLEFT_BEHIND &&
		_wayTurbo != ZRIGHT &&
		_wayTurbo != ZRIGHT_FRONT &&
		_wayTurbo != ZRIGHT_BEHIND &&
		_pGeoMover->_angAxisRot[AXIS_X] != 0 &&
		!VB::isBeingPressed(VB_UP_STC) &&
		!VB::isBeingPressed(VB_UP_RIGHT_STC) &&
		!VB::isBeingPressed(VB_UP_LEFT_STC) &&
		!VB::isBeingPressed(VB_DOWN_STC) &&
		!VB::isBeingPressed(VB_DOWN_RIGHT_STC) &&
		!VB::isBeingPressed(VB_DOWN_LEFT_STC) )
	{
		int rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_X, 0, TURN_CLOSE_TO);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXAcce_MNZ);
		_pGeoMover -> setTargetAxisRotAngle(AXIS_X, 0, TURN_BOTH);
	}


	//座標に反映
	_pGeoMover -> behave();
}

//画面奥手前移動初め処理
void MyShip::beginTurboZX(int prm_VB) {
	beginMoveZX(prm_VB);

	_isMoveZX = true;
	_dwFrameNextZXTurboOut = _dwFrame + _dwIntervalZXTurbo; //ターボ期間
	_dwFrameTurboMove = 0; //リセット
	_pGeoMover -> setMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
	_pGeoMover -> setMoveVelocity(_iMvVelo_BeginMT);
	_pGeoMover -> setMoveAcceleration(_iMvAcce_MT);

	switch(prm_VB) {

	case VB_UP_STC: //奥
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);

		_pGeoMover -> setMoveAngleRzRy(0, ANGLE270);

	break;

	case VB_UP_RIGHT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT*NANAME);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);

		_pGeoMover -> setMoveAngleRzRy(0, ANGLE315);
		break;

	case VB_UP_LEFT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT*NANAME);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);

		_pGeoMover -> setMoveAngleRzRy(0, ANGLE225);
		break;

	case VB_RIGHT_STC:
		_pGeoMover -> setMoveAngleRzRy(0, ANGLE0);
		break;

	case VB_LEFT_STC:
		_pGeoMover -> setMoveAngleRzRy(0, ANGLE180);
		break;

	case VB_DOWN_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -3000000, -1*_angRXBtmVelo_MZT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, -1*_angRXVelo_BeginMZT);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZT);

		_pGeoMover -> setMoveAngleRzRy(0, ANGLE90);
		break;

	case VB_DOWN_RIGHT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT*NANAME);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);

		_pGeoMover -> setMoveAngleRzRy(0, ANGLE45);
		break;

	case VB_DOWN_LEFT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT*NANAME);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);

		_pGeoMover -> setMoveAngleRzRy(0, ANGLE135);
		break;



	default:
		throw_GgafCriticalException("MyShip::beginTurboZX prm_VB="<<prm_VB<<"はありえません");
		break;
	}

}

//XY座標ターボ始動時
void MyShip::beginTurboXY(int prm_VB) {
	beginMoveXY(prm_VB);

	_isMoveZX = false;
	_dwFrameNextXYTurboOut = _dwFrame + _dwIntervalXYTurbo; //ターボ期間
	_dwFrameTurboMove = 0; //リセット


	_pGeoMover -> setMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
	_pGeoMover -> setMoveVelocity(_iMvVelo_BeginMT);
	_pGeoMover -> setMoveAcceleration(_iMvAcce_MT);

	switch(prm_VB) {

	case VB_UP_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, 3000000, _angRZBtmVelo_MYT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, _angRZVelo_BeginMYT);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MYT);
		_pGeoMover -> setMoveAngleRzRy(ANGLE90, 0);
		break;

	case VB_UP_RIGHT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, 3000000, _angRZBtmVelo_MYT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, _angRZVelo_BeginMYT*NANAME); //斜めなので回転力減
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MYT);
		_pGeoMover -> setMoveAngleRzRy(ANGLE45, 0);
		break;

	case VB_UP_LEFT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, 3000000, _angRZBtmVelo_MYT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, _angRZVelo_BeginMYT*NANAME); //斜めなので回転力減
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MYT);
		_pGeoMover -> setMoveAngleRzRy(ANGLE135, 0);
		break;

	case VB_LEFT_STC:
		_pGeoMover -> setMoveAngleRzRy(ANGLE180, 0);
		break;

	case VB_RIGHT_STC:
		_pGeoMover -> setMoveAngleRzRy(ANGLE0, 0);
		break;

	case VB_DOWN_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -300000, -1*_angRZBtmVelo_MYT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, -1*_angRZVelo_BeginMYT);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MYT);
		_pGeoMover -> setMoveAngleRzRy(-1*ANGLE90, 0);
		break;

	case VB_DOWN_RIGHT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -300000, -1*_angRZBtmVelo_MYT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, -1*_angRZVelo_BeginMYT*NANAME);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MYT);
		_pGeoMover -> setMoveAngleRzRy(-1*ANGLE45, 0);
		break;

	case VB_DOWN_LEFT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -300000, -1*_angRZBtmVelo_MYT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, -1*_angRZVelo_BeginMYT*NANAME);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MYT);
		_pGeoMover -> setMoveAngleRzRy(-1*ANGLE135, 0);
		break;

	default:
		throw_GgafCriticalException("MyShip::beginTurboXY prm_VB="<<prm_VB<<"はありえません");
		break;
	}

}


//画面奥手前移動初め処理
void MyShip::beginMoveZX(int prm_VB) {
	_dwFrameNomalMove = 0;
	int rd;
	switch(prm_VB) {

	case VB_UP_STC:
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] > _angRXTopVelo_MZ) {  //けっこうな勢いで正方向(順)周りに回ってた場合
			//徐々にゆるやかに
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXTopVelo_MZ, ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ*2); //角加速は負で徐々にゆるやかに
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] < -1*_angRXTopVelo_MZ) { //けっこうな勢いで負方向(逆)周りに回ってた場合                                          //負方向に回ってる場合
			//反発して逆周り
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*ANGLE180, _angRXTopVelo_MZ);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZ*2); //反発する正方向に角加速、通常の２倍角加速でいく
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*_angRXTopVelo_MZ, _angRXTopVelo_MZ);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_X, _angRXStop_MZ, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //停止している場合
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, sgn(rd)*_angRXVelo_BeginMZ); //初速
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXAcce_MZ); //近いほうに角加速
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_X, _angRXStop_MZ, TURN_BOTH, _angRXBtmVelo_MZT);
		break;

	case VB_UP_LEFT_STC:
	case VB_UP_RIGHT_STC:
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] > _angRXTopVelo_MZ) {  //けっこうな勢いで正方向(順)周りに回ってた場合
			//徐々にゆるやかに
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXTopVelo_MZ, ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ*2*NANAME); //角加速は負で徐々にゆるやかに
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] < -1*_angRXTopVelo_MZ) { //けっこうな勢いで負方向(逆)周りに回ってた場合                                          //負方向に回ってる場合
			//反発して逆周り
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*ANGLE180, _angRXTopVelo_MZ);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXTopVelo_MZ*2*NANAME); //反発する正方向に角加速、通常の２倍角加速でいく
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*_angRXTopVelo_MZ, _angRXTopVelo_MZ);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_X, _angRXStop_MZ*NANAME, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //停止している場合
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, sgn(rd)*_angRXVelo_BeginMZ); //初速
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXTopVelo_MZ*NANAME); //近いほうに角加速
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_X, _angRXStop_MZ*NANAME, TURN_BOTH, _angRXBtmVelo_MZT);
		break;

	case VB_RIGHT_STC:
		beginMoveXY(VB_RIGHT_STC);
		break;


	case VB_DOWN_STC:
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] > _angRXTopVelo_MZ) { //けっこうな勢いで正方向(逆)周りに回ってた場合
			//反発して逆周り
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, ANGLE180, -1*_angRXTopVelo_MZ);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ*2); //反発する負方向に角加速、通常の２倍角加速でいく
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] < -1*_angRXTopVelo_MZ) { //けっこうな勢いで負方向(順)周りに回ってた場合                                           //負方向に回ってる場合
			//徐々にゆるやかに
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*_angRXTopVelo_MZ, -1*ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZ*2); //角加速は正で徐々にゆるやかに
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*_angRXTopVelo_MZ, _angRXTopVelo_MZ);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_X, -1*_angRXStop_MZ, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //停止している場合
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, sgn(rd)*_angRXVelo_BeginMZ); //初速
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXAcce_MZ); //近いほうに角加速
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_X, -1*_angRXStop_MZ, TURN_BOTH, _angRXBtmVelo_MZT);
		break;

	case VB_DOWN_LEFT_STC:
	case VB_DOWN_RIGHT_STC:
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] > _angRXTopVelo_MZ) {  //けっこうな勢いで正方向(順)周りに回ってた場合
			//徐々にゆるやかに
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXTopVelo_MZ, ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ*2*NANAME); //角加速は負で徐々にゆるやかに
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] < -1*_angRXTopVelo_MZ) { //けっこうな勢いで負方向(逆)周りに回ってた場合                                          //負方向に回ってる場合
			//反発して逆周り
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*ANGLE180, _angRXTopVelo_MZ);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZ*2*NANAME); //反発する正方向に角加速、通常の２倍角加速でいく
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*_angRXTopVelo_MZ, _angRXTopVelo_MZ);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_X, _angRXStop_MZ*NANAME, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //停止している場合
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, sgn(rd)*_angRXVelo_BeginMZ); //初速
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXAcce_MZ*NANAME); //近いほうに角加速
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_X, _angRZStop_MY*NANAME, TURN_BOTH, _angRXBtmVelo_MZT);
		break;

	case VB_LEFT_STC:
		beginMoveXY(VB_LEFT_STC);
		break;

	default:
		throw_GgafCriticalException("MyShip::beginMoveZX prm_VB="<<prm_VB<<"はありえません");
		break;
	}

}


//XY前移動初め処理
void MyShip::beginMoveXY(int prm_VB) {
	_dwFrameNomalMove = 0;

	int rd;
	switch(prm_VB) {

	case VB_UP_STC: //仰角発生（＝正方向周り発生）
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) {  //けっこうな勢いで正方向(順)周りに回ってた場合
			//徐々にゆるやかに
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, _angRZTopVelo_MY, ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2); //角加速は負で徐々にゆるやかに
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //けっこうな勢いで負方向(逆)周りに回ってた場合                                          //負方向に回ってる場合
			//反発して逆周り
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*ANGLE180, _angRZTopVelo_MY);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2); //反発する正方向に角加速、通常の２倍角加速でいく
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_Z, _angRZStop_MY, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //停止している場合
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //初速
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY); //近いほうに角加速
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_Z, _angRZStop_MY, TURN_BOTH, _angRZBtmVelo_MYT);
		break;

	case VB_UP_LEFT_STC:
	case VB_UP_RIGHT_STC:
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) {  //けっこうな勢いで正方向(順)周りに回ってた場合
			//徐々にゆるやかに
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, _angRZTopVelo_MY, ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2*NANAME); //角加速は負で徐々にゆるやかに
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //けっこうな勢いで負方向(逆)周りに回ってた場合                                          //負方向に回ってる場合
			//反発して逆周り
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*ANGLE180, _angRZTopVelo_MY);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2*NANAME); //反発する正方向に角加速、通常の２倍角加速でいく
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_Z, _angRZStop_MY*NANAME, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //停止している場合
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //初速
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY*NANAME); //近いほうに角加速
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_Z, _angRZStop_MY*NANAME, TURN_BOTH, _angRZBtmVelo_MYT);
		break;

	case VB_RIGHT_STC:
		break;

	case VB_DOWN_STC: //俯角発生（＝負方向周り発生）
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) { //けっこうな勢いで正方向(逆)周りに回ってた場合
			//反発して逆周り
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, ANGLE180, -1*_angRZTopVelo_MY);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2); //反発する負方向に角加速、通常の２倍角加速でいく
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //けっこうな勢いで負方向(順)周りに回ってた場合                                           //負方向に回ってる場合
			//徐々にゆるやかに
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, -1*ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2); //角加速は正で徐々にゆるやかに
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_Z, -1*_angRZStop_MY, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //停止している場合
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //初速
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY); //近いほうに角加速
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_Z, -1*_angRZStop_MY, TURN_BOTH, _angRZBtmVelo_MYT);
		break;

	case VB_DOWN_LEFT_STC:
	case VB_DOWN_RIGHT_STC:
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) { //けっこうな勢いで正方向(逆)周りに回ってた場合
			//反発して逆周り
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, ANGLE180, -1*_angRZTopVelo_MY);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2*NANAME); //反発する負方向に角加速、通常の２倍角加速でいく
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //けっこうな勢いで負方向(順)周りに回ってた場合                                           //負方向に回ってる場合
			//徐々にゆるやかに
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, -1*ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2*NANAME); //角加速は正で徐々にゆるやかに
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_Z, -1*_angRZStop_MY*NANAME, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //停止している場合
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //初速
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY*NANAME); //近いほうに角加速
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_Z, -1*_angRZStop_MY*NANAME, TURN_BOTH, _angRZBtmVelo_MYT);
		break;

	case VB_LEFT_STC:
		break;

	default:
		throw_GgafCriticalException("MyShip::beginMoveXY prm_VB="<<prm_VB<<"はありえません");
		break;
	}

}



void MyShip::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}


void MyShip::processOnHit(GgafActor* prm_pActor_Opponent) {
	declareFinishLife();
}


void MyShip::transactShot(GgafDx9UntransformedActor* prm_pActor) {


}


void MyShip::equipOption() {

	MyOption* pOption = (MyOption*)_pSubFirst;
	for (int i = 0; i < _state.eq_option; i++) {
		pOption = (MyOption*)(pOption -> getNext());
	}
	if (_state.eq_option == 0) {
		pOption->setRadicalActor(this);
	} else {
		pOption->setRadicalActor((GgafDx9UntransformedActor*)pOption->getPrev());
	}
	_state.eq_option++;
	pOption->declarePlay();

}



MyShip::~MyShip() {
	RELEASE_POSSIBLE_NULL(MyLaserChip::_pIDirect3DVertexBuffer9_MyLaserChip);
	DELETE_POSSIBLE_NULL(MyLaserChip::_pTetra_EFGH);
}



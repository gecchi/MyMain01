#include "stdafx.h"


VirtualButton::VBMap* VirtualButton::_pVBMap = NULL;


VirtualButton::KEYBOARDMAP VirtualButton::_keymap = {
	DIK_Z,       // SHOT1
	DIK_Q,       // SHOT2
	DIK_W,       // SHOT3
	DIK_X,       // TURBO
	DIK_C,       // GUARD
	DIK_V,       // POWERUP
	DIK_ESCAPE,  // PAUSE
	DIK_UP,      // UP
	DIK_DOWN,    // DOWN
	DIK_LEFT,    // LEFT
	DIK_RIGHT,   // RIGHT
	DIK_UP,      // UI_UP
	DIK_DOWN,    // UI_DOWN
	DIK_LEFT,    // UI_LEFT
	DIK_RIGHT,   // UI_RIGHT
	DIK_RETURN,  // UI_EXECUTE
	DIK_ESCAPE   // UI_CANCEL
};

VirtualButton::JOYSTICKMAP VirtualButton::_joymap = {
	0,    // SHOT1
	7,    // SHOT2
	8,    // SHOT3
	1,    // TURBO
	2,    // GUARD
	3,    // POWERUP
	6,    // PAUSE
	0,    // UI_EXECUTE
	4     // UI_CANCEL
};




VirtualButton::VBMap* VirtualButton::getVirtualButtonMapHistory(DWORD prm_dwFrameAgo) {
	VBMap* pVBMTemp = _pVBMap;
	for (DWORD i = 0; i < prm_dwFrameAgo; i++) {
		pVBMTemp = pVBMTemp->_prev;
	}
	return pVBMTemp;
}


bool VirtualButton::isBeingPressed(int prm_VB) {
	return _pVBMap->_state[prm_VB];
}

bool VirtualButton::wasBeingPressed(int prm_VB, DWORD prm_dwFrameAgo) {
	return getVirtualButtonMapHistory(prm_dwFrameAgo)->_state[prm_VB];
}


bool VirtualButton::isNotBeingPressed(int prm_VB) {
	if (_pVBMap->_state[prm_VB]) {
		return false;
	} else {
		return true;
	}
}

bool VirtualButton::wasNotBeingPressed(int prm_VB, DWORD prm_dwFrameAgo) {
	if (getVirtualButtonMapHistory(prm_dwFrameAgo)->_state[prm_VB]) {
		return false;
	} else {
		return true;
	}
}

bool VirtualButton::isPushedDown(int prm_VB) {
	if (_pVBMap->_state[prm_VB] && _pVBMap->_prev->_state[prm_VB] == false) {
		return true;
	} else {
		return false;
	}
}

bool VirtualButton::arePushedDownAtOnce(int prm_aVB[], int prm_iButtonNum) {

	//現在は全て押されていなければならない
	for (int i = 0; i < prm_iButtonNum; i++) {
		if (_pVBMap->_state[prm_aVB[i]] == false) {
			return false;
		}
	}

	//全ボタンについて、それぞれが以下のいづれかの動作になっているかチェック。
	//↑ > ↓ > ↓ > ↓
	//↑ > ↑ > ↓ > ↓
	//↑ > ↑ > ↑ > ↓
	//↓ > ↓ > ↑ > ↓
	//↓ > ↑ > ↑ > ↓
	//↓ > ↑ > ↓ > ↓
	static VBMap* pVBMap_Prev1;
	static VBMap* pVBMap_Prev2;
	static VBMap* pVBMap_Prev3;
	pVBMap_Prev1 = _pVBMap -> _prev;
	pVBMap_Prev2 = pVBMap_Prev1 -> _prev;
	pVBMap_Prev3 = pVBMap_Prev2 -> _prev;
	static bool prev1Flg, prev2Flg, prev3Flg;
	for (int i = 0; i < prm_iButtonNum; i++) {
		prev1Flg = pVBMap_Prev1 -> _state[prm_aVB[i]];
		prev2Flg = pVBMap_Prev2 -> _state[prm_aVB[i]];
		prev3Flg = pVBMap_Prev3 -> _state[prm_aVB[i]];
		if (!prev3Flg && prev2Flg && prev1Flg) {
			continue;
		} else if (!prev3Flg && !prev2Flg &&  prev1Flg) {
			continue;
		} else if (!prev3Flg && !prev2Flg && !prev1Flg) {
			continue;
		} else if ( prev3Flg &&  prev2Flg && !prev1Flg) {
			continue;
		} else if ( prev3Flg && !prev2Flg && !prev1Flg) {
			continue;
		} else if ( prev3Flg && !prev2Flg &&  prev1Flg) {
			continue;
		} else {
			return false;
		}
	}

	//但し1つ前のフレームで、全て押されていては成立しない。
	//（この条件入れないと、「同時押し→押しっぱなし」の場合、３フレーム連続で成立してしまう）
	pVBMap_Prev1 = _pVBMap -> _prev;
	for (int i = 0; i < prm_iButtonNum; i++) {
		if (pVBMap_Prev1->_state[prm_aVB[i]] == false) {
			return true;
		}
	}
	return false;
}



bool VirtualButton::wasPushedDown(int prm_VB, DWORD prm_dwFrameAgo) {
	VBMap* pVBMapOld = getVirtualButtonMapHistory(prm_dwFrameAgo);
	if (pVBMapOld->_state[prm_VB] && pVBMapOld->_prev->_state[prm_VB] == false) {
		return true;
	} else {
		return false;
	}
}


bool VirtualButton::isReleasedUp(int prm_VB) {
	if (_pVBMap->_state[prm_VB] == false && _pVBMap->_prev->_state[prm_VB]) {
		return true;
	} else {
		return false;
	}
}

bool VirtualButton::wasReleasedUp(int prm_VB, DWORD prm_dwFrameAgo) {
	VBMap* pVBMapOld = getVirtualButtonMapHistory(prm_dwFrameAgo);
	if (pVBMapOld->_state[prm_VB] == false && pVBMapOld->_prev->_state[prm_VB]) {
		return true;
	} else {
		return false;
	}
}




void VirtualButton::clear() {
	VBMap* pLast = _pVBMap->_next;
	for (VBMap* p = _pVBMap->_prev; p != _pVBMap; p = p->_prev) {
		delete p->_next;
	}
	delete pLast;
}



void VirtualButton::init() {

	//環状双方向連結リスト構築
	_pVBMap = NEW VBMap();
	VBMap* pVBMTemp = _pVBMap;
	for (int i = 1; i < VB_MAP_BUFFER-1; i++) {
		VBMap* pVBMapWork = NEW VBMap();
		pVBMapWork->_next = pVBMTemp;
		pVBMTemp->_prev = pVBMapWork;
		pVBMTemp = pVBMapWork;
	}
	VBMap* pVBMapOldest = NEW VBMap();
	pVBMTemp->_prev = pVBMapOldest;
	pVBMapOldest->_next = pVBMTemp;
	pVBMapOldest->_prev = _pVBMap;
	_pVBMap->_next = pVBMapOldest;

}



void VirtualButton::update() {
	if (_pVBMap == NULL) {
		throw_GgafCriticalException("VirtualButton::update() 利用前に一度 init() を呼び出して下さい。");
	}

	GgafDx9Input::updateKeyboardState();
	GgafDx9Input::updateJoystickState();

    _pVBMap = _pVBMap -> _next;

	for (int i = 0; i < VB_NUM; i++) { //ボタンクリア
		_pVBMap->_state[i] = false;
	}

	_pVBMap->_state[VB_SHOT1]   = GgafDx9Input::isBeingPressedKey(_keymap.SHOT1)   || GgafDx9Input::isBeingPressedJoyRgbButton(_joymap.SHOT1);
	_pVBMap->_state[VB_SHOT2]   = GgafDx9Input::isBeingPressedKey(_keymap.SHOT2)   || GgafDx9Input::isBeingPressedJoyRgbButton(_joymap.SHOT2);
	_pVBMap->_state[VB_SHOT3]   = GgafDx9Input::isBeingPressedKey(_keymap.SHOT3)   || GgafDx9Input::isBeingPressedJoyRgbButton(_joymap.SHOT3);
	_pVBMap->_state[VB_TURBO]   = GgafDx9Input::isBeingPressedKey(_keymap.TURBO)   || GgafDx9Input::isBeingPressedJoyRgbButton(_joymap.TURBO);
	_pVBMap->_state[VB_GUARD]   = GgafDx9Input::isBeingPressedKey(_keymap.GUARD)   || GgafDx9Input::isBeingPressedJoyRgbButton(_joymap.GUARD);
	_pVBMap->_state[VB_POWERUP] = GgafDx9Input::isBeingPressedKey(_keymap.POWERUP) || GgafDx9Input::isBeingPressedJoyRgbButton(_joymap.PAUSE);
	_pVBMap->_state[VB_PAUSE]   = GgafDx9Input::isBeingPressedKey(_keymap.PAUSE)   || GgafDx9Input::isBeingPressedJoyRgbButton(_joymap.POWERUP);

	_pVBMap->_state[VB_UP]      = GgafDx9Input::isBeingPressedKey(_keymap.UP)    || GgafDx9Input::isBeingPressedJoyUp();
	_pVBMap->_state[VB_DOWN]    = GgafDx9Input::isBeingPressedKey(_keymap.DOWN)  || GgafDx9Input::isBeingPressedJoyDown();
	_pVBMap->_state[VB_LEFT]    = GgafDx9Input::isBeingPressedKey(_keymap.LEFT)  || GgafDx9Input::isBeingPressedJoyLeft();
	_pVBMap->_state[VB_RIGHT]   = GgafDx9Input::isBeingPressedKey(_keymap.RIGHT) || GgafDx9Input::isBeingPressedJoyRight();

	_pVBMap->_state[VB_UI_UP]    = GgafDx9Input::isBeingPressedKey(_keymap.UI_UP)    || GgafDx9Input::isBeingPressedJoyUp();
	_pVBMap->_state[VB_UI_DOWN]  = GgafDx9Input::isBeingPressedKey(_keymap.UI_DOWN)  || GgafDx9Input::isBeingPressedJoyDown();
	_pVBMap->_state[VB_UI_LEFT]  = GgafDx9Input::isBeingPressedKey(_keymap.UI_LEFT)  || GgafDx9Input::isBeingPressedJoyLeft();
	_pVBMap->_state[VB_UI_RIGHT] = GgafDx9Input::isBeingPressedKey(_keymap.UI_RIGHT) || GgafDx9Input::isBeingPressedJoyRight();

	_pVBMap->_state[VB_UI_EXECUTE] = GgafDx9Input::isBeingPressedKey(_keymap.UI_EXECUTE) || GgafDx9Input::isBeingPressedJoyRgbButton(_joymap.UI_EXECUTE);
	_pVBMap->_state[VB_UI_CANCEL]  = GgafDx9Input::isBeingPressedKey(_keymap.UI_CANCEL)  || GgafDx9Input::isBeingPressedJoyRgbButton(_joymap.UI_CANCEL);

	if (_pVBMap->_state[VB_UP])	{
		if (_pVBMap->_state[VB_RIGHT]) {
			_pVBMap->_state[VB_UP_RIGHT_STC] = true;
		} else if (_pVBMap->_state[VB_LEFT]) {
			_pVBMap->_state[VB_UP_LEFT_STC] = true;
		} else {
			_pVBMap->_state[VB_UP_STC] = true;
		}
	} else if (_pVBMap->_state[VB_DOWN]) {
		if (_pVBMap->_state[VB_UI_RIGHT]) {
			_pVBMap->_state[VB_DOWN_RIGHT_STC] = true;
		} else if (_pVBMap->_state[VB_UI_LEFT]) {
			_pVBMap->_state[VB_DOWN_LEFT_STC] = true;
		} else {
			_pVBMap->_state[VB_DOWN_STC] = true;
		}
	} else if (_pVBMap->_state[VB_UI_RIGHT]) {
		_pVBMap->_state[VB_RIGHT_STC] = true;
	} else if (_pVBMap->_state[VB_UI_LEFT]) {
		_pVBMap->_state[VB_LEFT_STC] = true;
	} else {
		_pVBMap->_state[VB_NEUTRAL_STC] = true;
	}
}



#include "stdafx.h"
using namespace std;

using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


VirtualButton::VBMap* VirtualButton::_s_pVBMap = NULL;


VirtualButton::KEYBOARDMAP VirtualButton::_s_tagKeymap = {
	DIK_Z,       // SHOT1
	DIK_X,       // SHOT2
	DIK_A,       // SHOT3
	DIK_Q,       // TURBO
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
	DIK_ESCAPE,   // UI_CANCEL
	DIK_D        //UI_DEBUG
};

VirtualButton::JOYSTICKMAP VirtualButton::_s_tagJoymap = {
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



VirtualButton::VBMap* VirtualButton::getPastVBMap(DWORD prm_dwFrameAgo) {
	static VBMap* pVBMTemp;
	pVBMTemp = _s_pVBMap;
	for (DWORD i = 0; i < prm_dwFrameAgo; i++) {
		pVBMTemp = pVBMTemp->_prev;
	}
	return pVBMTemp;
}


bool VirtualButton::isBeingPressed(int prm_VB) {
	//��肱�ڂ��l���ŁA����A�O��A�O�X��̉��ꂩ���^�ł����OK�Ƃ���
	return _s_pVBMap->_state[prm_VB] || _s_pVBMap->_prev->_state[prm_VB] || _s_pVBMap->_prev->_prev->_state[prm_VB];
}

bool VirtualButton::wasBeingPressed(int prm_VB, DWORD prm_dwFrameAgo) {
	static VBMap* pVBMTemp;
	pVBMTemp = getPastVBMap(prm_dwFrameAgo);
	return pVBMTemp->_state[prm_VB] || pVBMTemp->_prev->_state[prm_VB] || pVBMTemp->_prev->_prev->_state[prm_VB];
}


bool VirtualButton::isNotBeingPressed(int prm_VB) {
	if (isBeingPressed(prm_VB)) {
		return false;
	} else {
		return true;
	}
}

bool VirtualButton::wasNotBeingPressed(int prm_VB, DWORD prm_dwFrameAgo) {
	if (wasBeingPressed(prm_VB, prm_dwFrameAgo)) {
		return false;
	} else {
		return true;
	}
}

bool VirtualButton::isPushedDown(int prm_VB) {
	if (isBeingPressed(prm_VB) && wasNotBeingPressed(prm_VB, 1)) {
		return true;
	} else {
		return false;
	}
}

////������������Ă��Ȃ���������
//bool VirtualButton::isNonAfterPushedDown(int prm_VB) {
//	if (_s_pVBMap->_state[prm_VB]) {
//		for (int i = 0; i < VB_NUM; i++) {
//			if (_s_pVBMap->_prev->_state[i]) {
//				return false;
//			}
//		}
//		return true;
//	} else {
//		return false;
//	}
//}

bool VirtualButton::arePushedDownAtOnce(int prm_aVB[], int prm_iButtonNum) {

	//���݂͑S�ĉ�����Ă��Ȃ���΂Ȃ�Ȃ�
	for (int i = 0; i < prm_iButtonNum; i++) {
		if (isBeingPressed(prm_aVB[i]) == false) {
			return false;
		}
	}

	//�R�t���[���]�T������
	//�S�{�^���ɂ��āA���ꂼ�ꂪ�ȉ��̂��Âꂩ�̓���ɂȂ��Ă��邩�`�F�b�N�B
	//�� > �� > �� > ��
	//�� > �� > �� > ��
	//�� > �� > �� > ��
	//�� > �� > �� > ��
	//�� > �� > �� > ��
	//�� > �� > �� > ��
	static bool prev1Flg, prev2Flg, prev3Flg;
	for (int i = 0; i < prm_iButtonNum; i++) {
		prev1Flg = wasNotBeingPressed(prm_aVB[i], 1);
		prev2Flg = wasNotBeingPressed(prm_aVB[i], 2);
		prev3Flg = wasNotBeingPressed(prm_aVB[i], 3);
		if        (                          prev1Flg) { //�� > �� > �� >
			continue;
		} else if (             prev2Flg             ) { //�� > �� > �� >
			continue;
		} else if (prev3Flg                          ) { //�� > �� > �� >
			continue;
		} else {
			return false;
		}
	}

	//�A��1�O�̃t���[���ŁA�S�ĉ�����Ă��Ă͐������Ȃ��B
	//�i���̏�������Ȃ��ƁA�u�����������������ςȂ��v�̏ꍇ�A�R�t���[���A���Ő������Ă��܂��j
	for (int i = 0; i < prm_iButtonNum; i++) {
		if (wasNotBeingPressed(prm_aVB[i], 1)) {
			return true;
		}
	}
	return false;
}



bool VirtualButton::wasPushedDown(int prm_VB, DWORD prm_dwFrameAgo) {
	if (wasBeingPressed(prm_VB, prm_dwFrameAgo) && wasNotBeingPressed(prm_VB, prm_dwFrameAgo+1)) {
		return true;
	} else {
		return false;
	}
}


bool VirtualButton::isReleasedUp(int prm_VB) {
	if (isNotBeingPressed(prm_VB) && wasBeingPressed(prm_VB, 1)) {
		return true;
	} else {
		return false;
	}
}

bool VirtualButton::wasReleasedUp(int prm_VB, DWORD prm_dwFrameAgo) {
	if (wasNotBeingPressed(prm_VB, prm_dwFrameAgo) && wasBeingPressed(prm_VB, prm_dwFrameAgo+1)) {
		return true;
	} else {
		return false;
	}
}

int VirtualButton::getBeingPressedStick() {
	for (int i = VB_UP_RIGHT_STC; i <= VB_LEFT_STC; i++) {
		if (isBeingPressed(i)) {
			return i;
		}
	}
	return 0;
}

int VirtualButton::getPushedDownStick() {
	for (int i = VB_UP_RIGHT_STC; i <= VB_LEFT_STC; i++) {
		if (isPushedDown(i)) {
			return i;
		}
	}
	return 0;
}

int VirtualButton::getPushedDownStickWith(int prm_VB) {
	if (isBeingPressed(prm_VB)) {
		static bool prev1Flg, prev2Flg, prev3Flg;
		//�{�^���ɉ�����Ă��Ȃ����Ԃ����O�ɂ�������
		prev1Flg = wasNotBeingPressed(prm_VB, 1);
		prev2Flg = wasNotBeingPressed(prm_VB, 2);
		prev3Flg = wasNotBeingPressed(prm_VB, 3);
		if (                               prev1Flg) { //�� > �� > �� >
			//OK
		} else if (            prev2Flg            ) { //�� > �� > �� >
			//OK
		} else if (prev3Flg                        ) { //�� > �� > �� >
			//OK
		} else {
			//NG
			return 0;
		}

		//�X�e�B�b�N�ɉ�����Ă��Ȃ����Ԃ����O�ɂ�������
		static bool prev1N_Flg, prev2N_Flg, prev3N_Flg;
		prev1N_Flg = wasBeingPressed(VB_NEUTRAL_STC, 1);
		prev2N_Flg = wasBeingPressed(VB_NEUTRAL_STC, 2);
		prev3N_Flg = wasBeingPressed(VB_NEUTRAL_STC, 3);
		if (                                   prev1N_Flg) { //�� > �� > �m >
			//OK
		} else if (              prev2N_Flg              ) { //�� > �m > �� >
			//OK
		} else if (prev3N_Flg                            ) { //�m > �� > �� >
			//OK
		} else {
			//NG
			return 0;
		}

		for (int i = VB_UP_RIGHT_STC; i <= VB_LEFT_STC; i++) {
			//���͉����Ă���
			if (isBeingPressed(i)) {

				//�A��1�O�̃t���[���ŁA����������Ă��Ă͐������Ȃ��B
				//�i���̏�������Ȃ��ƁA�u�����������������ςȂ��v�̏ꍇ�A���t���[���A���Ő������Ă��܂��j
				if (wasBeingPressed(prm_VB, 1) && wasBeingPressed(i, 1)) {
					//NG
					continue;
				} else {
					//OK
					return i;
				}

			}
		}
		return 0;
	} else {
		return 0;
	}

}


void VirtualButton::clear() {
	VBMap* pLast = _s_pVBMap->_next;
	VBMap* pWk;
	for (VBMap* p = _s_pVBMap->_prev; p != _s_pVBMap; p = p->_prev) {
		pWk = p->_next;
		DELETE_IMPOSSIBLE_NULL(pWk);
	}
	DELETE_IMPOSSIBLE_NULL(pLast);
}



void VirtualButton::init() {

	//��o�����A�����X�g�\�z
	_s_pVBMap = NEW VBMap();
	VBMap* pVBMTemp = _s_pVBMap;
	for (int i = 1; i < VB_MAP_BUFFER-1; i++) {
		VBMap* pVBMapWork = NEW VBMap();
		pVBMapWork->_next = pVBMTemp;
		pVBMTemp->_prev = pVBMapWork;
		pVBMTemp = pVBMapWork;
	}
	VBMap* pVBMapOldest = NEW VBMap();
	pVBMTemp->_prev = pVBMapOldest;
	pVBMapOldest->_next = pVBMTemp;
	pVBMapOldest->_prev = _s_pVBMap;
	_s_pVBMap->_next = pVBMapOldest;

}



void VirtualButton::update() {
	if (_s_pVBMap == NULL) {
		throw_GgafCriticalException("VirtualButton::update() ���p�O�Ɉ�x init() ���Ăяo���ĉ������B");
	}

	GgafDx9Input::updateKeyboardState();
	GgafDx9Input::updateJoystickState();


    _s_pVBMap = _s_pVBMap->_next;

	_s_pVBMap->_state[VB_SHOT1]    = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.SHOT1)   || GgafDx9Input::isBeingPressedJoyRgbButton(_s_tagJoymap.SHOT1);
	_s_pVBMap->_state[VB_SHOT2]    = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.SHOT2)   || GgafDx9Input::isBeingPressedJoyRgbButton(_s_tagJoymap.SHOT2);
	_s_pVBMap->_state[VB_SHOT3]    = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.SHOT3)   || GgafDx9Input::isBeingPressedJoyRgbButton(_s_tagJoymap.SHOT3);
	_s_pVBMap->_state[VB_TURBO]    = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.TURBO)   || GgafDx9Input::isBeingPressedJoyRgbButton(_s_tagJoymap.TURBO);
	_s_pVBMap->_state[VB_GUARD]    = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.GUARD)   || GgafDx9Input::isBeingPressedJoyRgbButton(_s_tagJoymap.GUARD);
	_s_pVBMap->_state[VB_POWERUP]  = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.POWERUP) || GgafDx9Input::isBeingPressedJoyRgbButton(_s_tagJoymap.PAUSE);
	_s_pVBMap->_state[VB_PAUSE]    = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.PAUSE)   || GgafDx9Input::isBeingPressedJoyRgbButton(_s_tagJoymap.POWERUP);
	_s_pVBMap->_state[VB_UP]       = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.UP)    || GgafDx9Input::isBeingPressedJoyUp();
	_s_pVBMap->_state[VB_DOWN]     = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.DOWN)  || GgafDx9Input::isBeingPressedJoyDown();
	_s_pVBMap->_state[VB_LEFT]     = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.LEFT)  || GgafDx9Input::isBeingPressedJoyLeft();
	_s_pVBMap->_state[VB_RIGHT]    = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.RIGHT) || GgafDx9Input::isBeingPressedJoyRight();
	_s_pVBMap->_state[VB_UI_UP]    = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.UI_UP)    || GgafDx9Input::isBeingPressedJoyUp();
	_s_pVBMap->_state[VB_UI_DOWN]  = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.UI_DOWN)  || GgafDx9Input::isBeingPressedJoyDown();
	_s_pVBMap->_state[VB_UI_LEFT]  = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.UI_LEFT)  || GgafDx9Input::isBeingPressedJoyLeft();
	_s_pVBMap->_state[VB_UI_RIGHT] = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.UI_RIGHT) || GgafDx9Input::isBeingPressedJoyRight();

	_s_pVBMap->_state[VB_UI_EXECUTE] = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.UI_EXECUTE) || GgafDx9Input::isBeingPressedJoyRgbButton(_s_tagJoymap.UI_EXECUTE);
	_s_pVBMap->_state[VB_UI_CANCEL]  = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.UI_CANCEL)  || GgafDx9Input::isBeingPressedJoyRgbButton(_s_tagJoymap.UI_CANCEL);

	_s_pVBMap->_state[VB_UI_DEBUG] = GgafDx9Input::isBeingPressedKey(_s_tagKeymap.UI_DEBUG);


	_s_pVBMap->_state[VB_UP_RIGHT_STC] = false;
	_s_pVBMap->_state[VB_UP_LEFT_STC] = false;
	_s_pVBMap->_state[VB_DOWN_RIGHT_STC] = false;
	_s_pVBMap->_state[VB_DOWN_LEFT_STC] = false;
	_s_pVBMap->_state[VB_UP_STC] = false;
	_s_pVBMap->_state[VB_DOWN_STC] = false;
	_s_pVBMap->_state[VB_RIGHT_STC] = false;
	_s_pVBMap->_state[VB_LEFT_STC] = false;
	_s_pVBMap->_state[VB_NEUTRAL_STC] = false;

	if (_s_pVBMap->_state[VB_UP])	{
		if (_s_pVBMap->_state[VB_RIGHT]) {
			_s_pVBMap->_state[VB_UP_RIGHT_STC] = true;
		} else if (_s_pVBMap->_state[VB_LEFT]) {
			_s_pVBMap->_state[VB_UP_LEFT_STC] = true;
		} else {
			_s_pVBMap->_state[VB_UP_STC] = true;
		}
	} else if (_s_pVBMap->_state[VB_DOWN]) {
		if (_s_pVBMap->_state[VB_UI_RIGHT]) {
			_s_pVBMap->_state[VB_DOWN_RIGHT_STC] = true;
		} else if (_s_pVBMap->_state[VB_UI_LEFT]) {
			_s_pVBMap->_state[VB_DOWN_LEFT_STC] = true;
		} else {
			_s_pVBMap->_state[VB_DOWN_STC] = true;
		}
	} else if (_s_pVBMap->_state[VB_UI_RIGHT]) {
		_s_pVBMap->_state[VB_RIGHT_STC] = true;
	} else if (_s_pVBMap->_state[VB_UI_LEFT]) {
		_s_pVBMap->_state[VB_LEFT_STC] = true;
	} else {
		_s_pVBMap->_state[VB_NEUTRAL_STC] = true;
	}
}


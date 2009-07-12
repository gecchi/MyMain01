#include "stdafx.h"
using namespace std;

using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

VirtualButton::VBMap* VirtualButton::_pVBMap = NULL;

VirtualButton::KEYBOARDMAP VirtualButton::_tagKeymap = {
                              DIK_Z, // SHOT1
                              DIK_X, // SHOT2
                              DIK_A, // SHOT3
                              DIK_Q, // ZMOVE
                              DIK_C, // CONTROL
                              DIK_V, // POWERUP
                              DIK_ESCAPE, // PAUSE
                              DIK_UP, // UP
                              DIK_DOWN, // DOWN
                              DIK_LEFT, // LEFT
                              DIK_RIGHT, // RIGHT
                              DIK_UP, // UI_UP
                              DIK_DOWN, // UI_DOWN
                              DIK_LEFT, // UI_LEFT
                              DIK_RIGHT, // UI_RIGHT
                              DIK_RETURN, // UI_EXECUTE
                              DIK_ESCAPE, // UI_CANCEL
                              DIK_D //UI_DEBUG
                           };

VirtualButton::JOYSTICKMAP VirtualButton::_tagJoymap = {
                              0, // SHOT1
                              7, // SHOT2
                              8, // SHOT3
                              1, // ZMOVE
                              2, // CONTROL
                              3, // POWERUP
                              6, // PAUSE
                              0, // UI_EXECUTE
                              4 // UI_CANCEL
                           };

VirtualButton::VBMap* VirtualButton::getPastVBMap(DWORD prm_dwFrameAgo) {
    static VBMap* pVBMTemp;
    pVBMTemp = _pVBMap;
    for (DWORD i = 0; i < prm_dwFrameAgo; i++) {
        pVBMTemp = pVBMTemp->_prev;
    }
    return pVBMTemp;
}

bool VirtualButton::isBeingPressed(int prm_VB) {
    //取りこぼし考慮で、今回、前回、前々回の何れかが真であればOKとする
    return _pVBMap->_state[prm_VB] || _pVBMap->_prev->_state[prm_VB] || _pVBMap->_prev->_prev->_state[prm_VB];
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


////何所も押されていない→押した
//bool VirtualButton::isNonAfterPushedDown(int prm_VB) {
//	if (_pVBMap->_state[prm_VB]) {
//		for (int i = 0; i < VB_NUM; i++) {
//			if (_pVBMap->_prev->_state[i]) {
//				return false;
//			}
//		}
//		return true;
//	} else {
//		return false;
//	}
//}

bool VirtualButton::arePushedDownAtOnce(int prm_aVB[], int prm_iButtonNum) {

    //現在は全て押されていなければならない
    for (int i = 0; i < prm_iButtonNum; i++) {
        if (isBeingPressed(prm_aVB[i]) == false) {
            return false;
        }
    }

    //３フレーム余裕を見る
    //全ボタンについて、それぞれが以下のいづれかの動作になっているかチェック。
    //↑ > ↓ > ↓ > ↓
    //↑ > ↑ > ↓ > ↓
    //↑ > ↑ > ↑ > ↓
    //↓ > ↓ > ↑ > ↓
    //↓ > ↑ > ↑ > ↓
    //↓ > ↑ > ↓ > ↓
    static bool prev1Flg, prev2Flg, prev3Flg;
    for (int i = 0; i < prm_iButtonNum; i++) {
        prev1Flg = wasNotBeingPressed(prm_aVB[i], 1);
        prev2Flg = wasNotBeingPressed(prm_aVB[i], 2);
        prev3Flg = wasNotBeingPressed(prm_aVB[i], 3);
        if (prev1Flg) { //＊ > ＊ > ↑ >
            continue;
        } else if (prev2Flg) { //＊ > ↑ > ＊ >
            continue;
        } else if (prev3Flg) { //↑ > ＊ > ＊ >
            continue;
        } else {
            return false;
        }
    }

    //但し1つ前のフレームで、全て押されていては成立しない。
    //（この条件入れないと、「同時押し→押しっぱなし」の場合、３フレーム連続で成立してしまう）
    for (int i = 0; i < prm_iButtonNum; i++) {
        if (wasNotBeingPressed(prm_aVB[i], 1)) {
            return true;
        }
    }
    return false;
}

bool VirtualButton::wasPushedDown(int prm_VB, DWORD prm_dwFrameAgo) {
    if (wasBeingPressed(prm_VB, prm_dwFrameAgo) && wasNotBeingPressed(prm_VB, prm_dwFrameAgo + 1)) {
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
    if (wasNotBeingPressed(prm_VB, prm_dwFrameAgo) && wasBeingPressed(prm_VB, prm_dwFrameAgo + 1)) {
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
        //ボタンに押されていない期間が直前にあったか
        prev1Flg = wasNotBeingPressed(prm_VB, 1);
        prev2Flg = wasNotBeingPressed(prm_VB, 2);
        prev3Flg = wasNotBeingPressed(prm_VB, 3);
        if (prev1Flg) { //＊ > ＊ > ↑ >
            //OK
        } else if (prev2Flg) { //＊ > ↑ > ＊ >
            //OK
        } else if (prev3Flg) { //↑ > ＊ > ＊ >
            //OK
        } else {
            //NG
            return 0;
        }

        //スティックに押されていない期間が直前にあったか
        static bool prev1N_Flg, prev2N_Flg, prev3N_Flg;
        prev1N_Flg = wasBeingPressed(VB_NEUTRAL_STC, 1);
        prev2N_Flg = wasBeingPressed(VB_NEUTRAL_STC, 2);
        prev3N_Flg = wasBeingPressed(VB_NEUTRAL_STC, 3);
        if (prev1N_Flg) { //＊ > ＊ > Ｎ >
            //OK
        } else if (prev2N_Flg) { //＊ > Ｎ > ＊ >
            //OK
        } else if (prev3N_Flg) { //Ｎ > ＊ > ＊ >
            //OK
        } else {
            //NG
            return 0;
        }

        for (int i = VB_UP_RIGHT_STC; i <= VB_LEFT_STC; i++) {
            //今は押している
            if (isBeingPressed(i)) {

                //但し1つ前のフレームで、両方押されていては成立しない。
                //（この条件入れないと、「同時押し→押しっぱなし」の場合、数フレーム連続で成立してしまう）
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
    VBMap* pLast = _pVBMap->_next;
    VBMap* pWk;
    for (VBMap* p = _pVBMap->_prev; p != _pVBMap; p = p->_prev) {
        pWk = p->_next;
        DELETE_IMPOSSIBLE_NULL(pWk);
    }
    DELETE_IMPOSSIBLE_NULL(pLast);
}

void VirtualButton::init() {

    //環状双方向連結リスト構築
    _pVBMap = NEW VBMap();
    VBMap* pVBMTemp = _pVBMap;
    for (int i = 1; i < VB_MAP_BUFFER - 1; i++) {
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
        throwGgafCriticalException("VirtualButton::update() 利用前に一度 init() を呼び出して下さい。");
    }

    GgafDx9Input::updateKeyboardState();
    GgafDx9Input::updateJoystickState();

    _pVBMap = _pVBMap->_next;

    _pVBMap->_state[VB_SHOT1] = GgafDx9Input::isBeingPressedKey(_tagKeymap.SHOT1) ||
                                  GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.SHOT1);

    _pVBMap->_state[VB_SHOT2] = GgafDx9Input::isBeingPressedKey(_tagKeymap.SHOT2) ||
                                  GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.SHOT2);

    _pVBMap->_state[VB_SHOT3] = GgafDx9Input::isBeingPressedKey(_tagKeymap.SHOT3) ||
                                  GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.SHOT3);

    _pVBMap->_state[VB_XMOVE] = GgafDx9Input::isBeingPressedKey(_tagKeymap.ZMOVE) ||
                                  GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.ZMOVE);

    _pVBMap->_state[VB_CONTROL] = GgafDx9Input::isBeingPressedKey(_tagKeymap.CONTROL) ||
                                  GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.CONTROL);

    _pVBMap->_state[VB_POWERUP] = GgafDx9Input::isBeingPressedKey(_tagKeymap.POWERUP) ||
                                    GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.PAUSE);

    _pVBMap->_state[VB_PAUSE] = GgafDx9Input::isBeingPressedKey(_tagKeymap.PAUSE) ||
                                  GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.POWERUP);

    _pVBMap->_state[VB_UP] = GgafDx9Input::isBeingPressedKey(_tagKeymap.UP) ||
                               GgafDx9Input::isBeingPressedJoyUp();

    _pVBMap->_state[VB_DOWN] = GgafDx9Input::isBeingPressedKey(_tagKeymap.DOWN) ||
                                 GgafDx9Input::isBeingPressedJoyDown();

    _pVBMap->_state[VB_LEFT] = GgafDx9Input::isBeingPressedKey(_tagKeymap.LEFT) ||
                                 GgafDx9Input::isBeingPressedJoyLeft();

    _pVBMap->_state[VB_RIGHT] = GgafDx9Input::isBeingPressedKey(_tagKeymap.RIGHT) ||
                                  GgafDx9Input::isBeingPressedJoyRight();

    _pVBMap->_state[VB_UI_UP] = GgafDx9Input::isBeingPressedKey(_tagKeymap.UI_UP) ||
                                  GgafDx9Input::isBeingPressedJoyUp();

    _pVBMap->_state[VB_UI_DOWN] = GgafDx9Input::isBeingPressedKey(_tagKeymap.UI_DOWN) ||
                                    GgafDx9Input::isBeingPressedJoyDown();

    _pVBMap->_state[VB_UI_LEFT] = GgafDx9Input::isBeingPressedKey(_tagKeymap.UI_LEFT) ||
                                    GgafDx9Input::isBeingPressedJoyLeft();

    _pVBMap->_state[VB_UI_RIGHT] = GgafDx9Input::isBeingPressedKey(_tagKeymap.UI_RIGHT) ||
                                     GgafDx9Input::isBeingPressedJoyRight();


    _pVBMap->_state[VB_UI_EXECUTE] = GgafDx9Input::isBeingPressedKey(_tagKeymap.UI_EXECUTE) ||
                                       GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.UI_EXECUTE);

    _pVBMap->_state[VB_UI_CANCEL] = GgafDx9Input::isBeingPressedKey(_tagKeymap.UI_CANCEL) ||
                                      GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.UI_CANCEL);

    _pVBMap->_state[VB_UI_DEBUG] = GgafDx9Input::isBeingPressedKey(_tagKeymap.UI_DEBUG);

    _pVBMap->_state[VB_UP_RIGHT_STC] = false;
    _pVBMap->_state[VB_UP_LEFT_STC] = false;
    _pVBMap->_state[VB_DOWN_RIGHT_STC] = false;
    _pVBMap->_state[VB_DOWN_LEFT_STC] = false;
    _pVBMap->_state[VB_UP_STC] = false;
    _pVBMap->_state[VB_DOWN_STC] = false;
    _pVBMap->_state[VB_RIGHT_STC] = false;
    _pVBMap->_state[VB_LEFT_STC] = false;
    _pVBMap->_state[VB_NEUTRAL_STC] = false;

    if (_pVBMap->_state[VB_UP]) {
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


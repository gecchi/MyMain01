#include "stdafx.h"
using namespace std;

using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

keymap VirtualButton::_mapDIK;
bool VirtualButton::_is_init = false;

//標準キーボード割り当て
VirtualButton::KEYBOARDMAP VirtualButton::_tagKeymap = {
                              DIK_Z,      // BUTTON1
                              DIK_X,      // BUTTON2
                              DIK_C,      // BUTTON3
                              DIK_A,      // BUTTON4
                              DIK_S,      // BUTTON5
                              DIK_D,      // BUTTON6
                              DIK_ESCAPE, // PAUSE
                              DIK_UP,     // UP
                              DIK_DOWN,   // DOWN
                              DIK_LEFT,   // LEFT
                              DIK_RIGHT,  // RIGHT
                              DIK_UP,     // UI_UP
                              DIK_DOWN,   // UI_DOWN
                              DIK_LEFT,   // UI_LEFT
                              DIK_RIGHT,  // UI_RIGHT
                              DIK_RETURN, // UI_EXECUTE
                              DIK_ESCAPE, // UI_CANCEL
                              DIK_Q       // UI_DEBUG
                           };

VirtualButton::JOYSTICKMAP VirtualButton::_tagJoymap = {
                              0, // BUTTON1
                              1, // BUTTON2
                              2, // BUTTON3
                              3, // BUTTON4
                              4, // TURBO
                              5, // BUTTON6
                              6, // PAUSE
                              0, // UI_EXECUTE
                              1  // UI_CANCEL
                           };

VirtualButton::VirtualButton() {
    //環状双方向連結リスト構築
    _pVBMap_Active = NEW VBMap();
    VBMap* pVBMTemp = _pVBMap_Active;
    for (int i = 1; i < VB_MAP_BUFFER - 1; i++) {
        VBMap* pVBMapWork = NEW VBMap();
        pVBMapWork->_next = pVBMTemp;
        pVBMTemp->_prev = pVBMapWork;
        pVBMTemp = pVBMapWork;
    }
    VBMap* pVBMapOldest = NEW VBMap();
    pVBMTemp->_prev = pVBMapOldest;
    pVBMapOldest->_next = pVBMTemp;
    pVBMapOldest->_prev = _pVBMap_Active;
    _pVBMap_Active->_next = pVBMapOldest;

    _pVBMap_Reset =  getPastVBMap((VB_MAP_BUFFER - 1) / 2);
    //リセットするタイミングのポインタを設定
    for (int i = 1; i < (VB_MAP_BUFFER - 1)/2; i++) {

    }
    if (!_is_init) {
        init();
    }
}

void VirtualButton::init() {
    _mapDIK["DIK_ESCAPE"]       = 0x01;
    _mapDIK["DIK_1"]            = 0x02;
    _mapDIK["DIK_2"]            = 0x03;
    _mapDIK["DIK_3"]            = 0x04;
    _mapDIK["DIK_4"]            = 0x05;
    _mapDIK["DIK_5"]            = 0x06;
    _mapDIK["DIK_6"]            = 0x07;
    _mapDIK["DIK_7"]            = 0x08;
    _mapDIK["DIK_8"]            = 0x09;
    _mapDIK["DIK_9"]            = 0x0A;
    _mapDIK["DIK_0"]            = 0x0B;
    _mapDIK["DIK_MINUS"]        = 0x0C;
    _mapDIK["DIK_EQUALS"]       = 0x0D;
    _mapDIK["DIK_BACK"]         = 0x0E;
    _mapDIK["DIK_TAB"]          = 0x0F;
    _mapDIK["DIK_Q"]            = 0x10;
    _mapDIK["DIK_W"]            = 0x11;
    _mapDIK["DIK_E"]            = 0x12;
    _mapDIK["DIK_R"]            = 0x13;
    _mapDIK["DIK_T"]            = 0x14;
    _mapDIK["DIK_Y"]            = 0x15;
    _mapDIK["DIK_U"]            = 0x16;
    _mapDIK["DIK_I"]            = 0x17;
    _mapDIK["DIK_O"]            = 0x18;
    _mapDIK["DIK_P"]            = 0x19;
    _mapDIK["DIK_LBRACKET"]     = 0x1A;
    _mapDIK["DIK_RBRACKET"]     = 0x1B;
    _mapDIK["DIK_RETURN"]       = 0x1C;
    _mapDIK["DIK_LCONTROL"]     = 0x1D;
    _mapDIK["DIK_A"]            = 0x1E;
    _mapDIK["DIK_S"]            = 0x1F;
    _mapDIK["DIK_D"]            = 0x20;
    _mapDIK["DIK_F"]            = 0x21;
    _mapDIK["DIK_G"]            = 0x22;
    _mapDIK["DIK_H"]            = 0x23;
    _mapDIK["DIK_J"]            = 0x24;
    _mapDIK["DIK_K"]            = 0x25;
    _mapDIK["DIK_L"]            = 0x26;
    _mapDIK["DIK_SEMICOLON"]    = 0x27;
    _mapDIK["DIK_APOSTROPHE"]   = 0x28;
    _mapDIK["DIK_GRAVE"]        = 0x29;
    _mapDIK["DIK_LSHIFT"]       = 0x2A;
    _mapDIK["DIK_BACKSLASH"]    = 0x2B;
    _mapDIK["DIK_Z"]            = 0x2C;
    _mapDIK["DIK_X"]            = 0x2D;
    _mapDIK["DIK_C"]            = 0x2E;
    _mapDIK["DIK_V"]            = 0x2F;
    _mapDIK["DIK_B"]            = 0x30;
    _mapDIK["DIK_N"]            = 0x31;
    _mapDIK["DIK_M"]            = 0x32;
    _mapDIK["DIK_COMMA"]        = 0x33;
    _mapDIK["DIK_PERIOD"]       = 0x34;
    _mapDIK["DIK_SLASH"]        = 0x35;
    _mapDIK["DIK_RSHIFT"]       = 0x36;
    _mapDIK["DIK_MULTIPLY"]     = 0x37;
    _mapDIK["DIK_LMENU"]        = 0x38;
    _mapDIK["DIK_SPACE"]        = 0x39;
    _mapDIK["DIK_CAPITAL"]      = 0x3A;
    _mapDIK["DIK_F1"]           = 0x3B;
    _mapDIK["DIK_F2"]           = 0x3C;
    _mapDIK["DIK_F3"]           = 0x3D;
    _mapDIK["DIK_F4"]           = 0x3E;
    _mapDIK["DIK_F5"]           = 0x3F;
    _mapDIK["DIK_F6"]           = 0x40;
    _mapDIK["DIK_F7"]           = 0x41;
    _mapDIK["DIK_F8"]           = 0x42;
    _mapDIK["DIK_F9"]           = 0x43;
    _mapDIK["DIK_F10"]          = 0x44;
    _mapDIK["DIK_NUMLOCK"]      = 0x45;
    _mapDIK["DIK_SCROLL"]       = 0x46;
    _mapDIK["DIK_NUMPAD7"]      = 0x47;
    _mapDIK["DIK_NUMPAD8"]      = 0x48;
    _mapDIK["DIK_NUMPAD9"]      = 0x49;
    _mapDIK["DIK_SUBTRACT"]     = 0x4A;
    _mapDIK["DIK_NUMPAD4"]      = 0x4B;
    _mapDIK["DIK_NUMPAD5"]      = 0x4C;
    _mapDIK["DIK_NUMPAD6"]      = 0x4D;
    _mapDIK["DIK_ADD"]          = 0x4E;
    _mapDIK["DIK_NUMPAD1"]      = 0x4F;
    _mapDIK["DIK_NUMPAD2"]      = 0x50;
    _mapDIK["DIK_NUMPAD3"]      = 0x51;
    _mapDIK["DIK_NUMPAD0"]      = 0x52;
    _mapDIK["DIK_DECIMAL"]      = 0x53;
    _mapDIK["DIK_OEM_102"]      = 0x56;
    _mapDIK["DIK_F11"]          = 0x57;
    _mapDIK["DIK_F12"]          = 0x58;
    _mapDIK["DIK_F13"]          = 0x64;
    _mapDIK["DIK_F14"]          = 0x65;
    _mapDIK["DIK_F15"]          = 0x66;
    _mapDIK["DIK_KANA"]         = 0x70;
    _mapDIK["DIK_ABNT_C1"]      = 0x73;
    _mapDIK["DIK_CONVERT"]      = 0x79;
    _mapDIK["DIK_NOCONVERT"]    = 0x7B;
    _mapDIK["DIK_YEN"]          = 0x7D;
    _mapDIK["DIK_ABNT_C2"]      = 0x7E;
    _mapDIK["DIK_NUMPADEQUALS"] = 0x8D;
    _mapDIK["DIK_PREVTRACK"]    = 0x90;
    _mapDIK["DIK_AT"]           = 0x91;
    _mapDIK["DIK_COLON"]        = 0x92;
    _mapDIK["DIK_UNDERLINE"]    = 0x93;
    _mapDIK["DIK_KANJI"]        = 0x94;
    _mapDIK["DIK_STOP"]         = 0x95;
    _mapDIK["DIK_AX"]           = 0x96;
    _mapDIK["DIK_UNLABELED"]    = 0x97;
    _mapDIK["DIK_NEXTTRACK"]    = 0x99;
    _mapDIK["DIK_NUMPADENTER"]  = 0x9C;
    _mapDIK["DIK_RCONTROL"]     = 0x9D;
    _mapDIK["DIK_MUTE"]         = 0xA0;
    _mapDIK["DIK_CALCULATOR"]   = 0xA1;
    _mapDIK["DIK_PLAYPAUSE"]    = 0xA2;
    _mapDIK["DIK_MEDIASTOP"]    = 0xA4;
    _mapDIK["DIK_VOLUMEDOWN"]   = 0xAE;
    _mapDIK["DIK_VOLUMEUP"]     = 0xB0;
    _mapDIK["DIK_WEBHOME"]      = 0xB2;
    _mapDIK["DIK_NUMPADCOMMA"]  = 0xB3;
    _mapDIK["DIK_DIVIDE"]       = 0xB5;
    _mapDIK["DIK_SYSRQ"]        = 0xB7;
    _mapDIK["DIK_RMENU"]        = 0xB8;
    _mapDIK["DIK_PAUSE"]        = 0xC5;
    _mapDIK["DIK_HOME"]         = 0xC7;
    _mapDIK["DIK_UP"]           = 0xC8;
    _mapDIK["DIK_PRIOR"]        = 0xC9;
    _mapDIK["DIK_LEFT"]         = 0xCB;
    _mapDIK["DIK_RIGHT"]        = 0xCD;
    _mapDIK["DIK_END"]          = 0xCF;
    _mapDIK["DIK_DOWN"]         = 0xD0;
    _mapDIK["DIK_NEXT"]         = 0xD1;
    _mapDIK["DIK_INSERT"]       = 0xD2;
    _mapDIK["DIK_DELETE"]       = 0xD3;
    _mapDIK["DIK_LWIN"]         = 0xDB;
    _mapDIK["DIK_RWIN"]         = 0xDC;
    _mapDIK["DIK_APPS"]         = 0xDD;
    _mapDIK["DIK_POWER"]        = 0xDE;
    _mapDIK["DIK_SLEEP"]        = 0xDF;
    _mapDIK["DIK_WAKE"]         = 0xE3;
    _mapDIK["DIK_WEBSEARCH"]    = 0xE5;
    _mapDIK["DIK_WEBFAVORITES"] = 0xE6;
    _mapDIK["DIK_WEBREFRESH"]   = 0xE7;
    _mapDIK["DIK_WEBSTOP"]      = 0xE8;
    _mapDIK["DIK_WEBFORWARD"]   = 0xE9;
    _mapDIK["DIK_WEBBACK"]      = 0xEA;
    _mapDIK["DIK_MYCOMPUTER"]   = 0xEB;
    _mapDIK["DIK_MAIL"]         = 0xEC;
    _mapDIK["DIK_MEDIASELECT"]  = 0xED;
    _mapDIK["DIK_BACKSPACE"]    = 0x0E;
    _mapDIK["DIK_NUMPADSTAR"]   = 0x37;
    _mapDIK["DIK_LALT"]         = 0x38;
    _mapDIK["DIK_CAPSLOCK"]     = 0x3A;
    _mapDIK["DIK_NUMPADMINUS"]  = 0x4A;
    _mapDIK["DIK_NUMPADPLUS"]   = 0x4E;
    _mapDIK["DIK_NUMPADPERIOD"] = 0x53;
    _mapDIK["DIK_NUMPADSLASH"]  = 0xB5;
    _mapDIK["DIK_RALT"]         = 0xB8;
    _mapDIK["DIK_UPARROW"]      = 0xC8;
    _mapDIK["DIK_PGUP"]         = 0xC9;
    _mapDIK["DIK_LEFTARROW"]    = 0xCB;
    _mapDIK["DIK_RIGHTARROW"]   = 0xCD;
    _mapDIK["DIK_DOWNARROW"]    = 0xD0;
    _mapDIK["DIK_PGDN"]         = 0xD1;

    _mapDIK["JOY_BUTTON_00"]    = 0;
    _mapDIK["JOY_BUTTON_01"]    = 1;
    _mapDIK["JOY_BUTTON_02"]    = 2;
    _mapDIK["JOY_BUTTON_03"]    = 3;
    _mapDIK["JOY_BUTTON_04"]    = 4;
    _mapDIK["JOY_BUTTON_05"]    = 5;
    _mapDIK["JOY_BUTTON_06"]    = 6;
    _mapDIK["JOY_BUTTON_07"]    = 7;
    _mapDIK["JOY_BUTTON_08"]    = 8;
    _mapDIK["JOY_BUTTON_09"]    = 9;
}


VirtualButton::VBMap* VirtualButton::getPastVBMap(DWORD prm_dwFrameAgo) {
    VBMap* pVBMTemp = _pVBMap_Active;
    for (DWORD i = 0; i < prm_dwFrameAgo; i++) {
        pVBMTemp = pVBMTemp->_prev;
    }
    return pVBMTemp;
}

vbsta VirtualButton::isBeingPressed(vbsta prm_VB) {
    return _pVBMap_Active->_state & prm_VB;
}

vbsta VirtualButton::wasBeingPressed(vbsta prm_VB, DWORD prm_dwFrameAgo) {
    VBMap* pVBMTemp = getPastVBMap(prm_dwFrameAgo);
    return pVBMTemp->_state & prm_VB;
}

vbsta VirtualButton::isNotBeingPressed(vbsta prm_VB) {
    if (isBeingPressed(prm_VB)) {
        return false;
    } else {
        return true;
    }
}

vbsta VirtualButton::wasNotBeingPressed(vbsta prm_VB, DWORD prm_dwFrameAgo) {
    if (wasBeingPressed(prm_VB, prm_dwFrameAgo)) {
        return false;
    } else {
        return true;
    }
}

vbsta VirtualButton::isPushedDown(vbsta prm_VB) {
    if (isBeingPressed(prm_VB) && wasNotBeingPressed(prm_VB, 1)) {
        return true;
    } else {
        return false;
    }
}
vbsta VirtualButton::isDoublePushedDown(vbsta prm_VB, DWORD prm_frame_push, DWORD prm_frame_delay) {
    //-------oooo-----o
    //       <--><--->
    //         |    `-- prm_frame_delay
    //         `-- prm_frame_push
    //過去に遡りながら検証
    VirtualButton::VBMap* pVBMap;
    pVBMap = _pVBMap_Active;
    if (pVBMap->_state & prm_VB) {
        //OK
    } else {
        return false;
    }
    pVBMap = pVBMap->_prev;
    //直前は必ず押されていては駄目
    if (pVBMap->_state & prm_VB) {
        return false;
    }
    bool ok = false;
    for (DWORD i = 0; i < prm_frame_delay; i++) {
        pVBMap = pVBMap->_prev;
        if (pVBMap->_state & prm_VB) {
            //OK
            ok = true;
            break;
        }
    }
    if (ok) {

    } else {
        return false;
    }
    ok = false;
    for (DWORD i = 0; i < prm_frame_push; i++) {
        pVBMap = pVBMap->_prev;
        if (pVBMap->_state & prm_VB) {

        } else {
            //OK
            ok = true;
            break;
        }
    }
    if (ok) {
        return true;
    } else {
        return false;
    }
}



////何所も押されていない→押した
//bool VirtualButton::isNonAfterPushedDown(int prm_VB) {
//	if (_pVBMap_Active->_state[prm_VB]) {
//		for (int i = 0; i < VB_NUM; i++) {
//			if (_pVBMap_Active->_prev->_state[i]) {
//				return false;
//			}
//		}
//		return true;
//	} else {
//		return false;
//	}
//}

vbsta VirtualButton::arePushedDownAtOnce(vbsta prm_aVB[], int prm_iButtonNum) {

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

vbsta VirtualButton::wasPushedDown(vbsta prm_VB, DWORD prm_dwFrameAgo) {
    if (wasBeingPressed(prm_VB, prm_dwFrameAgo) && wasNotBeingPressed(prm_VB, prm_dwFrameAgo + 1)) {
        return true;
    } else {
        return false;
    }
}

vbsta VirtualButton::isReleasedUp(vbsta prm_VB) {
    if (isNotBeingPressed(prm_VB) && wasBeingPressed(prm_VB, 1)) {
        return true;
    } else {
        return false;
    }
}

vbsta VirtualButton::wasReleasedUp(vbsta prm_VB, DWORD prm_dwFrameAgo) {
    if (wasNotBeingPressed(prm_VB, prm_dwFrameAgo) && wasBeingPressed(prm_VB, prm_dwFrameAgo + 1)) {
        return true;
    } else {
        return false;
    }
}

vbsta VirtualButton::getBeingPressedStick() {

    return _pVBMap_Active->_state & VB_STC_MASK;

//    for (int i = VB_UP_RIGHT_STC; i <= VB_LEFT_STC; i++) {
//        if (isBeingPressed(i)) {
//            return i;
//        }
//    }
//    return 0;
}

vbsta VirtualButton::getPushedDownStick() {
    if ((_pVBMap_Active->_prev->_state & VB_STC_MASK) == VB_NEUTRAL_STC) {
        return _pVBMap_Active->_state & VB_STC_MASK;
    } else {
        return 0;
    }
}


vbsta VirtualButton::isDoublePushedDownStick(DWORD prm_frame_push, DWORD prm_frame_delay) {
    vbsta STC = getPushedDownStick();
    if (STC == 0 || STC == VB_NEUTRAL_STC) {
        return 0;
    }
    //-------oooo-----o
    //       <--><--->
    //         |    `-- prm_frame_delay
    //         `-- prm_frame_push
    //過去に遡りながら検証
    VirtualButton::VBMap* pVBMap;
    pVBMap = _pVBMap_Active;
    pVBMap = pVBMap->_prev; //上のgetPushedDownStickで調査済みなので飛ばす。
    bool ok = false;
    for (DWORD i = 0; i < prm_frame_delay; i++) {
        pVBMap = pVBMap->_prev;
        if (pVBMap->_state & STC) {
            //OK
            ok = true;
            break;
        }
    }
    if (ok) {

    } else {
        return 0;
    }
    ok = false;
    for (DWORD i = 0; i < prm_frame_push; i++) {
        pVBMap = pVBMap->_prev;
        if (pVBMap->_state & STC) {

        } else {
            //OK
            ok = true;
            break;
        }
    }
    if (ok) {
        return STC;
    } else {
        return 0;
    }
}


bool VirtualButton::isRoundPush(vbsta prm_VB, DWORD prm_frame_delay) {
    if (isPushedDown(prm_VB)) {
        VBMap* pVBMap;
        pVBMap = _pVBMap_Active;
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
        for (DWORD i = 0; i < prm_frame_delay; i++) {
            pVBMap = pVBMap->_prev;
            if (pVBMap->_state & VB_UP) {
                up = true;
                continue;
            }
            if (pVBMap->_state & VB_RIGHT) {
                right = true;
                continue;
            }
            if (pVBMap->_state & VB_DOWN) {
                down = true;
                continue;
            }
            if (pVBMap->_state & VB_LEFT) {
                left = true;
                continue;
            }
        }
        if (up && down && left && right) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}



//vbsta VirtualButton::getPushedDownStickWith(vbsta prm_VB) {
//    if (isBeingPressed(prm_VB)) {
//        static bool prev1Flg, prev2Flg, prev3Flg;
//        //ボタンに押されていない期間が直前にあったか
//        prev1Flg = wasNotBeingPressed(prm_VB, 1);
//        prev2Flg = wasNotBeingPressed(prm_VB, 2);
//        prev3Flg = wasNotBeingPressed(prm_VB, 3);
//        if (prev1Flg) { //＊ > ＊ > ↑ >
//            //OK
//        } else if (prev2Flg) { //＊ > ↑ > ＊ >
//            //OK
//        } else if (prev3Flg) { //↑ > ＊ > ＊ >
//            //OK
//        } else {
//            //NG
//            return 0;
//        }
//
//        //スティックに押されていない期間が直前にあったか
//        static bool prev1N_Flg, prev2N_Flg, prev3N_Flg;
//        prev1N_Flg = wasBeingPressed(VB_NEUTRAL_STC, 1);
//        prev2N_Flg = wasBeingPressed(VB_NEUTRAL_STC, 2);
//        prev3N_Flg = wasBeingPressed(VB_NEUTRAL_STC, 3);
//        if (prev1N_Flg) { //＊ > ＊ > Ｎ >
//            //OK
//        } else if (prev2N_Flg) { //＊ > Ｎ > ＊ >
//            //OK
//        } else if (prev3N_Flg) { //Ｎ > ＊ > ＊ >
//            //OK
//        } else {
//            //NG
//            return 0;
//        }
//
//        for (int i = VB_UP_RIGHT_STC; i <= VB_LEFT_STC; i++) {
//            //今は押している
//            if (isBeingPressed(i)) {
//
//                //但し1つ前のフレームで、両方押されていては成立しない。
//                //（この条件入れないと、「同時押し→押しっぱなし」の場合、数フレーム連続で成立してしまう）
//                if (wasBeingPressed(prm_VB, 1) && wasBeingPressed(i, 1)) {
//                    //NG
//                    continue;
//                } else {
//                    //OK
//                    return i;
//                }
//
//            }
//        }
//        return 0;
//    } else {
//        return 0;
//    }
//
//}




void VirtualButton::update() {
#ifdef MY_DEBUG
    if (_pVBMap_Active == NULL) {
        throwGgafCriticalException("VirtualButton::update() 利用前に一度 init() を呼び出して下さい。");
    }
#endif
    GgafDx9Input::updateKeyboardState();
    GgafDx9Input::updateJoystickState();

    _pVBMap_Active = _pVBMap_Active->_next;

    //連結リングの反対側でリセット
    _pVBMap_Reset = _pVBMap_Reset->_next;
    _pVBMap_Reset->_state = 0;

    _pVBMap_Active->_state |= (VB_BUTTON1 * (GgafDx9Input::isBeingPressedKey(_tagKeymap.BUTTON1) ||
                                      GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.BUTTON1)));

    _pVBMap_Active->_state |= (VB_BUTTON2 * (GgafDx9Input::isBeingPressedKey(_tagKeymap.BUTTON2) ||
                                      GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.BUTTON2)));

    _pVBMap_Active->_state |= (VB_BUTTON3 * (GgafDx9Input::isBeingPressedKey(_tagKeymap.BUTTON3) ||
                                      GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.BUTTON3)));

    _pVBMap_Active->_state |= (VB_BUTTON4 * (GgafDx9Input::isBeingPressedKey(_tagKeymap.BUTTON4) ||
                                      GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.BUTTON4)));

    _pVBMap_Active->_state |= (VB_BUTTON5 * (GgafDx9Input::isBeingPressedKey(_tagKeymap.BUTTON5) ||
                                      GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.BUTTON5)));

    _pVBMap_Active->_state |= (VB_BUTTON6 * (GgafDx9Input::isBeingPressedKey(_tagKeymap.BUTTON6) ||
                                      GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.BUTTON6)));

    _pVBMap_Active->_state |= (VB_PAUSE * (GgafDx9Input::isBeingPressedKey(_tagKeymap.PAUSE) ||
                                    GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.PAUSE)));

    _pVBMap_Active->_state |= (VB_UP * (GgafDx9Input::isBeingPressedKey(_tagKeymap.UP) ||
                                 GgafDx9Input::isBeingPressedJoyUp()));

    _pVBMap_Active->_state |= (VB_DOWN * (GgafDx9Input::isBeingPressedKey(_tagKeymap.DOWN) ||
                                   GgafDx9Input::isBeingPressedJoyDown()));

    _pVBMap_Active->_state |= (VB_LEFT * (GgafDx9Input::isBeingPressedKey(_tagKeymap.LEFT) ||
                                   GgafDx9Input::isBeingPressedJoyLeft()));

    _pVBMap_Active->_state |= (VB_RIGHT * (GgafDx9Input::isBeingPressedKey(_tagKeymap.RIGHT) ||
                                    GgafDx9Input::isBeingPressedJoyRight()));

    _pVBMap_Active->_state |= (VB_UI_UP * (GgafDx9Input::isBeingPressedKey(_tagKeymap.UI_UP) ||
                                    GgafDx9Input::isBeingPressedJoyUp()));

    _pVBMap_Active->_state |= (VB_UI_DOWN * (GgafDx9Input::isBeingPressedKey(_tagKeymap.UI_DOWN) ||
                                      GgafDx9Input::isBeingPressedJoyDown()));

    _pVBMap_Active->_state |= (VB_UI_LEFT * (GgafDx9Input::isBeingPressedKey(_tagKeymap.UI_LEFT) ||
                                      GgafDx9Input::isBeingPressedJoyLeft()));

    _pVBMap_Active->_state |= (VB_UI_RIGHT * (GgafDx9Input::isBeingPressedKey(_tagKeymap.UI_RIGHT) ||
                                       GgafDx9Input::isBeingPressedJoyRight()));

    _pVBMap_Active->_state |= (VB_UI_EXECUTE * (GgafDx9Input::isBeingPressedKey(_tagKeymap.UI_EXECUTE) ||
                                         GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.UI_EXECUTE)));

    _pVBMap_Active->_state |= (VB_UI_CANCEL * (GgafDx9Input::isBeingPressedKey(_tagKeymap.UI_CANCEL) ||
                                        GgafDx9Input::isBeingPressedJoyRgbButton(_tagJoymap.UI_CANCEL)));

    _pVBMap_Active->_state |= (VB_UI_DEBUG * (GgafDx9Input::isBeingPressedKey(_tagKeymap.UI_DEBUG)));


//
//    _pVBMap_Active->_state[VB_UP_RIGHT_STC] = false;
//    _pVBMap_Active->_state[VB_UP_LEFT_STC] = false;
//    _pVBMap_Active->_state[VB_DOWN_RIGHT_STC] = false;
//    _pVBMap_Active->_state[VB_DOWN_LEFT_STC] = false;
//    _pVBMap_Active->_state[VB_UP_STC] = false;
//    _pVBMap_Active->_state[VB_DOWN_STC] = false;
//    _pVBMap_Active->_state[VB_RIGHT_STC] = false;
//    _pVBMap_Active->_state[VB_LEFT_STC] = false;
//    _pVBMap_Active->_state[VB_NEUTRAL_STC] = false;

    if (_pVBMap_Active->_state & VB_UP) {
        if (_pVBMap_Active->_state & VB_RIGHT) {
            _pVBMap_Active->_state |= VB_UP_RIGHT_STC;
        } else if (_pVBMap_Active->_state & VB_LEFT) {
            _pVBMap_Active->_state |= VB_UP_LEFT_STC;
        } else {
            _pVBMap_Active->_state |= VB_UP_STC;
        }
    } else if (_pVBMap_Active->_state & VB_DOWN) {
        if (_pVBMap_Active->_state & VB_UI_RIGHT) {
            _pVBMap_Active->_state |= VB_DOWN_RIGHT_STC;
        } else if (_pVBMap_Active->_state & VB_UI_LEFT) {
            _pVBMap_Active->_state |= VB_DOWN_LEFT_STC;
        } else {
            _pVBMap_Active->_state |= VB_DOWN_STC;
        }
    } else if (_pVBMap_Active->_state & VB_UI_RIGHT) {
        _pVBMap_Active->_state |= VB_RIGHT_STC;
    } else if (_pVBMap_Active->_state & VB_UI_LEFT) {
        _pVBMap_Active->_state |= VB_LEFT_STC;
    } else {
        _pVBMap_Active->_state |= VB_NEUTRAL_STC;
    }
}

VirtualButton::~VirtualButton() {
    VBMap* pLast = _pVBMap_Active->_next;
    VBMap* pWk;
    for (VBMap* p = _pVBMap_Active->_prev; p != _pVBMap_Active; p = p->_prev) {
        pWk = p->_next;
        DELETE_IMPOSSIBLE_NULL(pWk);
    }
    DELETE_IMPOSSIBLE_NULL(pLast);
}

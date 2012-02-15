#include "stdafx.h"
using namespace std;

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

keymap VirtualButton::_mapDIK;
bool VirtualButton::_is_init = false;

//組み込み標準キーボード割り当て
VirtualButton::KEYBOARDMAP VirtualButton::_tagKeymap = {
                              DIK_Z,      // BUTTON1
                              DIK_X,      // BUTTON2
                              DIK_C,      // BUTTON3
                              DIK_A,      // BUTTON4
                              DIK_S,      // BUTTON5
                              DIK_D,      // BUTTON6
                              DIK_V,      // BUTTON7
                              DIK_B,      // BUTTON8
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
                              4, // BUTTON5
                              5, // BUTTON6
                              6, // BUTTON7
                              7, // BUTTON8
                              9, // PAUSE
                              0, // UI_EXECUTE
                              1  // UI_CANCEL
                           };

VirtualButton::VirtualButton(const char* prm_replay_file) : GgafObject() {
    //環状双方向連結リスト構築
    _pVBRecord_Active = NEW VBRecord();
    VBRecord* pVBRecord_Temp = _pVBRecord_Active;
    for (int i = 1; i < VB_MAP_BUFFER - 1; i++) {
        VBRecord* pVBRecordWork = NEW VBRecord();
        pVBRecordWork->_next = pVBRecord_Temp;
        pVBRecord_Temp->_prev = pVBRecordWork;
        pVBRecord_Temp = pVBRecordWork;
    }
    VBRecord* pVBRecordOldest = NEW VBRecord();
    pVBRecord_Temp->_prev = pVBRecordOldest;
    pVBRecordOldest->_next = pVBRecord_Temp;
    pVBRecordOldest->_prev = _pVBRecord_Active;
    _pVBRecord_Active->_next = pVBRecordOldest;
    _is_auto_repeat = false;

    _pRpy = NEW VBReplayRecorder();
    if (_pRpy->importFile(prm_replay_file) ) {
        //読み込めた場合リプレイモード
        _TRACE_("VirtualButton::VirtualButton("<<prm_replay_file<<") リプレイモードです。");
        _is_replaying = true;
    } else {
        //読み込めない場合は通常記録モード
        _is_replaying = false;
        _TRACE_("VirtualButton::VirtualButton("<<prm_replay_file<<") 通常記録モード。");
    }
    if (!_is_init) {
        init();
    }
    _was_replay_done = false;
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
    _mapDIK["JOY_BUTTON_10"]    = 10;
    _mapDIK["JOY_BUTTON_11"]    = 11;
    _mapDIK["JOY_BUTTON_12"]    = 12;

}

VirtualButton::VBRecord* VirtualButton::getPastVBRecord(frame prm_frame_ago) {
    VBRecord* pVBRecord_Temp = _pVBRecord_Active;
    for (frame i = 0; i < prm_frame_ago; i++) {
        pVBRecord_Temp = pVBRecord_Temp->_prev;
    }
    return pVBRecord_Temp;
}

vbsta VirtualButton::isBeingPressed(vbsta prm_VB) {
    return _pVBRecord_Active->_state & prm_VB;
}

vbsta VirtualButton::isAutoRepeat(vbsta prm_VB, frame prm_begin_repeat, frame prm_while_repeat) {
    vbsta sta = _pVBRecord_Active->_state & prm_VB;
    if (sta) {
        _is_auto_repeat = true;
        if (sta == (_pVBRecord_Active->_prev->_state & prm_VB)) {
            _auto_repeat_counter[prm_VB] ++;
        } else {
            _auto_repeat_counter[prm_VB] = 0;
        }
    } else {
        _is_auto_repeat = false;
        _auto_repeat_counter[prm_VB] = 0;
    }

    if (_is_auto_repeat) {
        if (_auto_repeat_counter[prm_VB] == 0) {
            //キーイン時にまず成立
            return sta;
        } else if (_auto_repeat_counter[prm_VB] > prm_begin_repeat && _auto_repeat_counter[prm_VB] % prm_while_repeat == 0) {
            //オートリピート時成立(デフォルトでは、20フレーム後以降は5フレーム毎に成立)
            return sta;
        }
    }
    return false;
}



vbsta VirtualButton::wasBeingPressed(vbsta prm_VB, frame prm_frame_ago) {
    VBRecord* pVBRecord_Temp = getPastVBRecord(prm_frame_ago);
    return pVBRecord_Temp->_state & prm_VB;
}

vbsta VirtualButton::isNotBeingPressed(vbsta prm_VB) {
    if (isBeingPressed(prm_VB)) {
        return false;
    } else {
        return true;
    }
}

vbsta VirtualButton::wasNotBeingPressed(vbsta prm_VB, frame prm_frame_ago) {
    if (wasBeingPressed(prm_VB, prm_frame_ago)) {
        return false;
    } else {
        return true;
    }
}

vbsta VirtualButton::isPushedDown(vbsta prm_VB) {
    if (!(_pVBRecord_Active->_prev->_state & prm_VB) && (_pVBRecord_Active->_state & prm_VB)) {
        return true;
    } else {
        return false;
    }
}
vbsta VirtualButton::isDoublePushedDown(vbsta prm_VB, frame prm_frame_push, frame prm_frame_delay) {
    //-------oooo-----o
    //       <--><--->
    //         |    `-- prm_frame_delay
    //         `-- prm_frame_push
    //過去に遡りながら検証
    VirtualButton::VBRecord* pVBRecord;
    pVBRecord = _pVBRecord_Active;
    if (pVBRecord->_state & prm_VB) {
        //OK
    } else {
        return false;
    }
    pVBRecord = pVBRecord->_prev;
    //直前は必ず押されていては駄目
    if (pVBRecord->_state & prm_VB) {
        return false;
    }
    bool ok = false;
    for (frame i = 0; i < prm_frame_delay; i++) {
        pVBRecord = pVBRecord->_prev;
        if (pVBRecord->_state & prm_VB) {
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
    for (frame i = 0; i < prm_frame_push; i++) {
        pVBRecord = pVBRecord->_prev;
        if (pVBRecord->_state & prm_VB) {

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
//	if (_pVBRecord_Active->_state[prm_VB]) {
//		for (int i = 0; i < VB_NUM; i++) {
//			if (_pVBRecord_Active->_prev->_state[i]) {
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
    // ↑ > ？ > ？ > ↓
    //       or
    // ？ > ↑ > ？ > ↓
    //       or
    // ？ > ？ > ↑ > ↓
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
    //この条件入れないと、「同時押し→押しっぱなし」の場合、最大３フレーム連続で成立してしまう場合がある。
    for (int i = 0; i < prm_iButtonNum; i++) {
        if (wasNotBeingPressed(prm_aVB[i], 1)) {
            return true;
        }
    }
    return false;
}

vbsta VirtualButton::wasPushedDown(vbsta prm_VB, frame prm_frame_ago) {
    if (wasBeingPressed(prm_VB, prm_frame_ago) && wasNotBeingPressed(prm_VB, prm_frame_ago + 1)) {
        return true;
    } else {
        return false;
    }
}

vbsta VirtualButton::isReleasedUp(vbsta prm_VB) {
    if ((_pVBRecord_Active->_prev->_state & prm_VB) && !(_pVBRecord_Active->_state & prm_VB)) {
        return true;
    } else {
        return false;
    }
}

vbsta VirtualButton::isPushedUp(vbsta prm_VB, frame prm_frame_push) {
    //←過去      現在
    //            ↓
    //---------ooo-
    //       <--->
    //         |
    //         `-- prm_frame_push

    //過去に遡りながら検証
    VirtualButton::VBRecord* pVBRecord;
    pVBRecord = _pVBRecord_Active;
    //現在は押されていては駄目
    if (pVBRecord->_state & prm_VB) {
        return false;
    } else {
        //OK
    }
    pVBRecord = pVBRecord->_prev;
    //直前は押されていなければいけない
    if (pVBRecord->_state & prm_VB) {
        //OK
    } else {
        return false;
    }
    pVBRecord = pVBRecord->_prev;
    bool ok = false;
    for (frame i = 0; i < prm_frame_push; i++) {
        pVBRecord = pVBRecord->_prev;
        if (pVBRecord->_state & prm_VB) {

        } else {
            //prm_frame_push期間内に離していればOK
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


vbsta VirtualButton::wasReleasedUp(vbsta prm_VB, frame prm_frame_ago) {
    if (wasNotBeingPressed(prm_VB, prm_frame_ago) && wasBeingPressed(prm_VB, prm_frame_ago + 1)) {
        return true;
    } else {
        return false;
    }
}

vbsta VirtualButton::getBeingPressedStick() {

    return _pVBRecord_Active->_state & VB_STC_MASK;

//    for (int i = VB_UP_RIGHT_STC; i <= VB_LEFT_STC; i++) {
//        if (isBeingPressed(i)) {
//            return i;
//        }
//    }
//    return 0;
}

vbsta VirtualButton::getPushedDownStick() {
    if ((_pVBRecord_Active->_prev->_state & VB_STC_MASK) == VB_NEUTRAL_STC) {
        return _pVBRecord_Active->_state & VB_STC_MASK;
    } else {
        return 0;
    }
}


vbsta VirtualButton::isDoublePushedDownStick(frame prm_frame_push, frame prm_frame_delay) {
    vbsta STC = getPushedDownStick();
    if (STC == 0 || STC == VB_NEUTRAL_STC) {
        return 0;
    }
    //-------oooo-----o
    //       <--><--->
    //         |    `-- prm_frame_delay
    //         `-- prm_frame_push
    //過去に遡りながら検証
    VirtualButton::VBRecord* pVBRecord;
    pVBRecord = _pVBRecord_Active;
    pVBRecord = pVBRecord->_prev; //上のgetPushedDownStickで調査済みなので飛ばす。
    bool ok = false;
    for (frame i = 0; i < prm_frame_delay; i++) {
        pVBRecord = pVBRecord->_prev;
        if (pVBRecord->_state & STC) {
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
    for (frame i = 0; i < prm_frame_push; i++) {
        pVBRecord = pVBRecord->_prev;
        if (pVBRecord->_state & STC) {

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


bool VirtualButton::isRoundPushDown(vbsta prm_VB, frame prm_frame_delay) {
    if (isPushedDown(prm_VB)) {
        VBRecord* pVBRecord;
        pVBRecord = _pVBRecord_Active;
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
        for (frame i = 0; i < prm_frame_delay; i++) {
            pVBRecord = pVBRecord->_prev;
            if (pVBRecord->_state & VB_UP) {
                up = true;
                continue;
            }
            if (pVBRecord->_state & VB_RIGHT) {
                right = true;
                continue;
            }
            if (pVBRecord->_state & VB_DOWN) {
                down = true;
                continue;
            }
            if (pVBRecord->_state & VB_LEFT) {
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

vbsta VirtualButton::getState() {
    return _pVBRecord_Active->_state;
}


void VirtualButton::update() {
#ifdef MY_DEBUG
    if (_pVBRecord_Active == NULL) {
        throwGgafCriticalException("VirtualButton::update() 利用前に一度 init() を呼び出して下さい。");
    }
#endif
    GgafDxInput::updateKeyboardState();
    GgafDxInput::updateJoystickState();

    if (_is_replaying) {
        //リプレイモード時
        _pVBRecord_Active = _pVBRecord_Active->_next;
        _pVBRecord_Active->_state = _pRpy->read();
        if (_pVBRecord_Active->_state == 0) {
            _was_replay_done = true;
        }
        return;

    } else {

        //通常操作時
        _pVBRecord_Active = _pVBRecord_Active->_next;

        vbsta state = 0;
        state |= (VB_BUTTON1 * (GgafDxInput::isBeingPressedKey(_tagKeymap.BUTTON1) ||
                                GgafDxInput::isBeingPressedJoyRgbButton(_tagJoymap.BUTTON1)));

        state |= (VB_BUTTON2 * (GgafDxInput::isBeingPressedKey(_tagKeymap.BUTTON2) ||
                                GgafDxInput::isBeingPressedJoyRgbButton(_tagJoymap.BUTTON2)));

        state |= (VB_BUTTON3 * (GgafDxInput::isBeingPressedKey(_tagKeymap.BUTTON3) ||
                                GgafDxInput::isBeingPressedJoyRgbButton(_tagJoymap.BUTTON3)));

        state |= (VB_BUTTON4 * (GgafDxInput::isBeingPressedKey(_tagKeymap.BUTTON4) ||
                                GgafDxInput::isBeingPressedJoyRgbButton(_tagJoymap.BUTTON4)));

        state |= (VB_BUTTON5 * (GgafDxInput::isBeingPressedKey(_tagKeymap.BUTTON5) ||
                                GgafDxInput::isBeingPressedJoyRgbButton(_tagJoymap.BUTTON5)));

        state |= (VB_BUTTON6 * (GgafDxInput::isBeingPressedKey(_tagKeymap.BUTTON6) ||
                                GgafDxInput::isBeingPressedJoyRgbButton(_tagJoymap.BUTTON6)));

        state |= (VB_BUTTON7 * (GgafDxInput::isBeingPressedKey(_tagKeymap.BUTTON7) ||
                                GgafDxInput::isBeingPressedJoyRgbButton(_tagJoymap.BUTTON7)));

        state |= (VB_BUTTON8 * (GgafDxInput::isBeingPressedKey(_tagKeymap.BUTTON8) ||
                                GgafDxInput::isBeingPressedJoyRgbButton(_tagJoymap.BUTTON8)));

        state |= (VB_PAUSE * (GgafDxInput::isBeingPressedKey(_tagKeymap.PAUSE) ||
                              GgafDxInput::isBeingPressedJoyRgbButton(_tagJoymap.PAUSE)));

        state |= (VB_UP * (GgafDxInput::isBeingPressedKey(_tagKeymap.UP) ||
                           GgafDxInput::isBeingPressedJoyUp()));

        state |= (VB_DOWN * (GgafDxInput::isBeingPressedKey(_tagKeymap.DOWN) ||
                             GgafDxInput::isBeingPressedJoyDown()));

        state |= (VB_LEFT * (GgafDxInput::isBeingPressedKey(_tagKeymap.LEFT) ||
                             GgafDxInput::isBeingPressedJoyLeft()));

        state |= (VB_RIGHT * (GgafDxInput::isBeingPressedKey(_tagKeymap.RIGHT) ||
                              GgafDxInput::isBeingPressedJoyRight()));

        state |= (VB_UI_UP * (GgafDxInput::isBeingPressedKey(_tagKeymap.UI_UP) ||
                              GgafDxInput::isBeingPressedJoyUp()));

        state |= (VB_UI_DOWN * (GgafDxInput::isBeingPressedKey(_tagKeymap.UI_DOWN) ||
                                GgafDxInput::isBeingPressedJoyDown()));

        state |= (VB_UI_LEFT * (GgafDxInput::isBeingPressedKey(_tagKeymap.UI_LEFT) ||
                                GgafDxInput::isBeingPressedJoyLeft()));

        state |= (VB_UI_RIGHT * (GgafDxInput::isBeingPressedKey(_tagKeymap.UI_RIGHT) ||
                                 GgafDxInput::isBeingPressedJoyRight()));

        state |= (VB_UI_EXECUTE * (GgafDxInput::isBeingPressedKey(_tagKeymap.UI_EXECUTE) ||
                                   GgafDxInput::isBeingPressedJoyRgbButton(_tagJoymap.UI_EXECUTE)));

        state |= (VB_UI_CANCEL * (GgafDxInput::isBeingPressedKey(_tagKeymap.UI_CANCEL) ||
                                  GgafDxInput::isBeingPressedJoyRgbButton(_tagJoymap.UI_CANCEL)));

        state |= (VB_UI_DEBUG * (GgafDxInput::isBeingPressedKey(_tagKeymap.UI_DEBUG)));


        if (state & VB_UP) {
            if (state & VB_RIGHT) {
                state |= VB_UP_RIGHT_STC;
            } else if (state & VB_LEFT) {
                state |= VB_UP_LEFT_STC;
            } else {
                state |= VB_UP_STC;
            }
        } else if (state & VB_DOWN) {
            if (state & VB_UI_RIGHT) {
                state |= VB_DOWN_RIGHT_STC;
            } else if (state & VB_UI_LEFT) {
                state |= VB_DOWN_LEFT_STC;
            } else {
                state |= VB_DOWN_STC;
            }
        } else if (state & VB_UI_RIGHT) {
            state |= VB_RIGHT_STC;
        } else if (state & VB_UI_LEFT) {
            state |= VB_LEFT_STC;
        } else {
            state |= VB_NEUTRAL_STC; //何も入力しなかった場合、結果は VB_NEUTRAL_STC になる
        }

        _pVBRecord_Active->_state = state;
    }
    _pRpy->write(_pVBRecord_Active->_state); //リプレイ情報記録

}


void VirtualButton::clear() {
    VBRecord* pVBRecord = _pVBRecord_Active;
    for (int i = 0; i < VB_MAP_BUFFER; i++) {
        pVBRecord->_state = 0;
        pVBRecord = pVBRecord->_next;
    }
}

VirtualButton::~VirtualButton() {
    DELETE_IMPOSSIBLE_NULL(_pRpy);
    VBRecord* pLast = _pVBRecord_Active->_next;
    VBRecord* pWk;
    for (VBRecord* p = _pVBRecord_Active->_prev; p != _pVBRecord_Active; p = p->_prev) {
        pWk = p->_next;
        DELETE_IMPOSSIBLE_NULL(pWk);
    }
    DELETE_IMPOSSIBLE_NULL(pLast);
}

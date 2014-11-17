#include "jp/ggaf/lib/util/VirtualButton.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/lib/util/VBReplayRecorder.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

std::map<std::string, int> VirtualButton::_mapStr2Dik;
std::map<std::string, int> VirtualButton::_mapStr2JoyBtn;
std::map<int, std::string> VirtualButton::_mapDik2Str;
std::map<int, std::string> VirtualButton::_mapJoyBtn2Str;
std::map<int, VirtualButton::funcVJBtn> VirtualButton::_mapVJoyBtn2Func;

bool VirtualButton::_is_init = false;

//�g�ݍ��ݕW���L�[�{�[�h���蓖��
VirtualButton::KEYBOARDMAP VirtualButton::_keyboardmap = {
                              DIK_Z,      // BUTTON1
                              DIK_X,      // BUTTON2
                              DIK_C,      // BUTTON3
                              DIK_A,      // BUTTON4
                              DIK_S,      // BUTTON5
                              DIK_D,      // BUTTON6
                              DIK_V,      // BUTTON7
                              DIK_B,      // BUTTON8
                              DIK_N,      // BUTTON9
                              DIK_M,      // BUTTON10
                              0xFF,      // BUTTON11
                              0xFF,      // BUTTON12
                              0xFF,      // BUTTON13
                              0xFF,      // BUTTON14
                              0xFF,      // BUTTON15
                              0xFF,      // BUTTON16
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

VirtualButton::JOYSTICKMAP VirtualButton::_joystickmap = {
                              0x00, // BUTTON1
                              0x01, // BUTTON2
                              0x02, // BUTTON3
                              0x03, // BUTTON4
                              0x04, // BUTTON5
                              0x05, // BUTTON6
                              0x06, // BUTTON7
                              0x07, // BUTTON8
                              0x08, // BUTTON9
                              0x09, // BUTTON10
                              0x0A, // BUTTON11
                              0x0B, // BUTTON12
                              0x0C, // BUTTON13
                              0x0D, // BUTTON14
                              0x0E, // BUTTON15
                              0x0F, // BUTTON16
                              0x07, // PAUSE
                              0x80, // UP
                              0x81, // DOWN
                              0x82, // LEFT
                              0x83, // RIGHT
                              0x80, // UI_UP
                              0x81, // UI_DOWN
                              0x82, // UI_LEFT
                              0x83, // UI_RIGHT
                              0,    // UI_EXECUTE
                              1     // UI_CANCEL
                              //, 0xFF  // UI_DEBUG
                           };

VirtualButton::VirtualButton(const char* prm_replay_file) : GgafObject() {
    //��o�����A�����X�g�\�z
    _pVBRecord_active = NEW VBRecord();
    VirtualButton::VBRecord* pVBRecord_temp = _pVBRecord_active;
    for (int i = 1; i < VB_MAP_BUFFER - 1; i++) {
        VirtualButton::VBRecord* pVBRecordWork = NEW VirtualButton::VBRecord();
        pVBRecordWork->_next = pVBRecord_temp;
        pVBRecord_temp->_prev = pVBRecordWork;
        pVBRecord_temp = pVBRecordWork;
    }
    VirtualButton::VBRecord* pVBRecord_oldest = NEW VirtualButton::VBRecord();
    pVBRecord_temp->_prev = pVBRecord_oldest;
    pVBRecord_oldest->_next = pVBRecord_temp;
    pVBRecord_oldest->_prev = _pVBRecord_active;
    _pVBRecord_active->_next = pVBRecord_oldest;
    _is_auto_repeat = false;

    _pRpy = NEW VBReplayRecorder();
    if (_pRpy->importFile(prm_replay_file) ) {
        //�ǂݍ��߂��ꍇ���v���C���[�h
        _TRACE_("VirtualButton("<<prm_replay_file<<") ���v���C���[�h�ł��B");
        _is_replaying = true;
    } else {
        //�ǂݍ��߂Ȃ��ꍇ�͒ʏ�L�^���[�h
        _is_replaying = false;
        _TRACE_("VirtualButton("<<prm_replay_file<<") �ʏ�L�^���[�h�B");
    }
    if (!_is_init) {
        init();
    }
    _was_replay_done = false;
    _with_pov = true;
}

void VirtualButton::init() {
    _mapStr2Dik["DIK_ESCAPE"]       = 0x01;
    _mapStr2Dik["DIK_1"]            = 0x02;
    _mapStr2Dik["DIK_2"]            = 0x03;
    _mapStr2Dik["DIK_3"]            = 0x04;
    _mapStr2Dik["DIK_4"]            = 0x05;
    _mapStr2Dik["DIK_5"]            = 0x06;
    _mapStr2Dik["DIK_6"]            = 0x07;
    _mapStr2Dik["DIK_7"]            = 0x08;
    _mapStr2Dik["DIK_8"]            = 0x09;
    _mapStr2Dik["DIK_9"]            = 0x0A;
    _mapStr2Dik["DIK_0"]            = 0x0B;
    _mapStr2Dik["DIK_MINUS"]        = 0x0C;
    _mapStr2Dik["DIK_EQUALS"]       = 0x0D;
    _mapStr2Dik["DIK_BACK"]         = 0x0E;
    _mapStr2Dik["DIK_TAB"]          = 0x0F;
    _mapStr2Dik["DIK_Q"]            = 0x10;
    _mapStr2Dik["DIK_W"]            = 0x11;
    _mapStr2Dik["DIK_E"]            = 0x12;
    _mapStr2Dik["DIK_R"]            = 0x13;
    _mapStr2Dik["DIK_T"]            = 0x14;
    _mapStr2Dik["DIK_Y"]            = 0x15;
    _mapStr2Dik["DIK_U"]            = 0x16;
    _mapStr2Dik["DIK_I"]            = 0x17;
    _mapStr2Dik["DIK_O"]            = 0x18;
    _mapStr2Dik["DIK_P"]            = 0x19;
    _mapStr2Dik["DIK_LBRACKET"]     = 0x1A;
    _mapStr2Dik["DIK_RBRACKET"]     = 0x1B;
    _mapStr2Dik["DIK_RETURN"]       = 0x1C;
    _mapStr2Dik["DIK_LCONTROL"]     = 0x1D;
    _mapStr2Dik["DIK_A"]            = 0x1E;
    _mapStr2Dik["DIK_S"]            = 0x1F;
    _mapStr2Dik["DIK_D"]            = 0x20;
    _mapStr2Dik["DIK_F"]            = 0x21;
    _mapStr2Dik["DIK_G"]            = 0x22;
    _mapStr2Dik["DIK_H"]            = 0x23;
    _mapStr2Dik["DIK_J"]            = 0x24;
    _mapStr2Dik["DIK_K"]            = 0x25;
    _mapStr2Dik["DIK_L"]            = 0x26;
    _mapStr2Dik["DIK_SEMICOLON"]    = 0x27;
    _mapStr2Dik["DIK_APOSTROPHE"]   = 0x28;
    _mapStr2Dik["DIK_GRAVE"]        = 0x29;
    _mapStr2Dik["DIK_LSHIFT"]       = 0x2A;
    _mapStr2Dik["DIK_BACKSLASH"]    = 0x2B;
    _mapStr2Dik["DIK_Z"]            = 0x2C;
    _mapStr2Dik["DIK_X"]            = 0x2D;
    _mapStr2Dik["DIK_C"]            = 0x2E;
    _mapStr2Dik["DIK_V"]            = 0x2F;
    _mapStr2Dik["DIK_B"]            = 0x30;
    _mapStr2Dik["DIK_N"]            = 0x31;
    _mapStr2Dik["DIK_M"]            = 0x32;
    _mapStr2Dik["DIK_COMMA"]        = 0x33;
    _mapStr2Dik["DIK_PERIOD"]       = 0x34;
    _mapStr2Dik["DIK_SLASH"]        = 0x35;
    _mapStr2Dik["DIK_RSHIFT"]       = 0x36;
    _mapStr2Dik["DIK_MULTIPLY"]     = 0x37;
    _mapStr2Dik["DIK_LMENU"]        = 0x38;
    _mapStr2Dik["DIK_SPACE"]        = 0x39;
    _mapStr2Dik["DIK_CAPITAL"]      = 0x3A;
    _mapStr2Dik["DIK_F1"]           = 0x3B;
    _mapStr2Dik["DIK_F2"]           = 0x3C;
    _mapStr2Dik["DIK_F3"]           = 0x3D;
    _mapStr2Dik["DIK_F4"]           = 0x3E;
    _mapStr2Dik["DIK_F5"]           = 0x3F;
    _mapStr2Dik["DIK_F6"]           = 0x40;
    _mapStr2Dik["DIK_F7"]           = 0x41;
    _mapStr2Dik["DIK_F8"]           = 0x42;
    _mapStr2Dik["DIK_F9"]           = 0x43;
    _mapStr2Dik["DIK_F10"]          = 0x44;
    _mapStr2Dik["DIK_NUMLOCK"]      = 0x45;
    _mapStr2Dik["DIK_SCROLL"]       = 0x46;
    _mapStr2Dik["DIK_NUMPAD7"]      = 0x47;
    _mapStr2Dik["DIK_NUMPAD8"]      = 0x48;
    _mapStr2Dik["DIK_NUMPAD9"]      = 0x49;
    _mapStr2Dik["DIK_SUBTRACT"]     = 0x4A;
    _mapStr2Dik["DIK_NUMPAD4"]      = 0x4B;
    _mapStr2Dik["DIK_NUMPAD5"]      = 0x4C;
    _mapStr2Dik["DIK_NUMPAD6"]      = 0x4D;
    _mapStr2Dik["DIK_ADD"]          = 0x4E;
    _mapStr2Dik["DIK_NUMPAD1"]      = 0x4F;
    _mapStr2Dik["DIK_NUMPAD2"]      = 0x50;
    _mapStr2Dik["DIK_NUMPAD3"]      = 0x51;
    _mapStr2Dik["DIK_NUMPAD0"]      = 0x52;
    _mapStr2Dik["DIK_DECIMAL"]      = 0x53;
    _mapStr2Dik["DIK_OEM_102"]      = 0x56;
    _mapStr2Dik["DIK_F11"]          = 0x57;
    _mapStr2Dik["DIK_F12"]          = 0x58;
    _mapStr2Dik["DIK_F13"]          = 0x64;
    _mapStr2Dik["DIK_F14"]          = 0x65;
    _mapStr2Dik["DIK_F15"]          = 0x66;
    _mapStr2Dik["DIK_KANA"]         = 0x70;
    _mapStr2Dik["DIK_ABNT_C1"]      = 0x73;
    _mapStr2Dik["DIK_CONVERT"]      = 0x79;
    _mapStr2Dik["DIK_NOCONVERT"]    = 0x7B;
    _mapStr2Dik["DIK_YEN"]          = 0x7D;
    _mapStr2Dik["DIK_ABNT_C2"]      = 0x7E;
    _mapStr2Dik["DIK_NUMPADEQUALS"] = 0x8D;
    _mapStr2Dik["DIK_PREVTRACK"]    = 0x90;
    _mapStr2Dik["DIK_AT"]           = 0x91;
    _mapStr2Dik["DIK_COLON"]        = 0x92;
    _mapStr2Dik["DIK_UNDERLINE"]    = 0x93;
    _mapStr2Dik["DIK_KANJI"]        = 0x94;
    _mapStr2Dik["DIK_STOP"]         = 0x95;
    _mapStr2Dik["DIK_AX"]           = 0x96;
    _mapStr2Dik["DIK_UNLABELED"]    = 0x97;
    _mapStr2Dik["DIK_NEXTTRACK"]    = 0x99;
    _mapStr2Dik["DIK_NUMPADENTER"]  = 0x9C;
    _mapStr2Dik["DIK_RCONTROL"]     = 0x9D;
    _mapStr2Dik["DIK_MUTE"]         = 0xA0;
    _mapStr2Dik["DIK_CALCULATOR"]   = 0xA1;
    _mapStr2Dik["DIK_PLAYPAUSE"]    = 0xA2;
    _mapStr2Dik["DIK_MEDIASTOP"]    = 0xA4;
    _mapStr2Dik["DIK_VOLUMEDOWN"]   = 0xAE;
    _mapStr2Dik["DIK_VOLUMEUP"]     = 0xB0;
    _mapStr2Dik["DIK_WEBHOME"]      = 0xB2;
    _mapStr2Dik["DIK_NUMPADCOMMA"]  = 0xB3;
    _mapStr2Dik["DIK_DIVIDE"]       = 0xB5;
    _mapStr2Dik["DIK_SYSRQ"]        = 0xB7;
    _mapStr2Dik["DIK_RMENU"]        = 0xB8;
    _mapStr2Dik["DIK_PAUSE"]        = 0xC5;
    _mapStr2Dik["DIK_HOME"]         = 0xC7;
    _mapStr2Dik["DIK_UP"]           = 0xC8;
    _mapStr2Dik["DIK_PRIOR"]        = 0xC9;
    _mapStr2Dik["DIK_LEFT"]         = 0xCB;
    _mapStr2Dik["DIK_RIGHT"]        = 0xCD;
    _mapStr2Dik["DIK_END"]          = 0xCF;
    _mapStr2Dik["DIK_DOWN"]         = 0xD0;
    _mapStr2Dik["DIK_NEXT"]         = 0xD1;
    _mapStr2Dik["DIK_INSERT"]       = 0xD2;
    _mapStr2Dik["DIK_DELETE"]       = 0xD3;
    _mapStr2Dik["DIK_LWIN"]         = 0xDB;
    _mapStr2Dik["DIK_RWIN"]         = 0xDC;
    _mapStr2Dik["DIK_APPS"]         = 0xDD;
    _mapStr2Dik["DIK_POWER"]        = 0xDE;
    _mapStr2Dik["DIK_SLEEP"]        = 0xDF;
    _mapStr2Dik["DIK_WAKE"]         = 0xE3;
    _mapStr2Dik["DIK_WEBSEARCH"]    = 0xE5;
    _mapStr2Dik["DIK_WEBFAVORITES"] = 0xE6;
    _mapStr2Dik["DIK_WEBREFRESH"]   = 0xE7;
    _mapStr2Dik["DIK_WEBSTOP"]      = 0xE8;
    _mapStr2Dik["DIK_WEBFORWARD"]   = 0xE9;
    _mapStr2Dik["DIK_WEBBACK"]      = 0xEA;
    _mapStr2Dik["DIK_MYCOMPUTER"]   = 0xEB;
    _mapStr2Dik["DIK_MAIL"]         = 0xEC;
    _mapStr2Dik["DIK_MEDIASELECT"]  = 0xED;
    _mapStr2Dik["DIK_BACKSPACE"]    = 0x0E;
    _mapStr2Dik["DIK_NUMPADSTAR"]   = 0x37;
    _mapStr2Dik["DIK_LALT"]         = 0x38;
    _mapStr2Dik["DIK_CAPSLOCK"]     = 0x3A;
    _mapStr2Dik["DIK_NUMPADMINUS"]  = 0x4A;
    _mapStr2Dik["DIK_NUMPADPLUS"]   = 0x4E;
    _mapStr2Dik["DIK_NUMPADPERIOD"] = 0x53;
    _mapStr2Dik["DIK_NUMPADSLASH"]  = 0xB5;
    _mapStr2Dik["DIK_RALT"]         = 0xB8;
    _mapStr2Dik["DIK_UPARROW"]      = 0xC8;
    _mapStr2Dik["DIK_PGUP"]         = 0xC9;
    _mapStr2Dik["DIK_LEFTARROW"]    = 0xCB;
    _mapStr2Dik["DIK_RIGHTARROW"]   = 0xCD;
    _mapStr2Dik["DIK_DOWNARROW"]    = 0xD0;
    _mapStr2Dik["DIK_PGDN"]         = 0xD1;

    _mapStr2JoyBtn["JOY_BUTTON_00"] = 0x00;
    _mapStr2JoyBtn["JOY_BUTTON_01"] = 0x01;
    _mapStr2JoyBtn["JOY_BUTTON_02"] = 0x02;
    _mapStr2JoyBtn["JOY_BUTTON_03"] = 0x03;
    _mapStr2JoyBtn["JOY_BUTTON_04"] = 0x04;
    _mapStr2JoyBtn["JOY_BUTTON_05"] = 0x05;
    _mapStr2JoyBtn["JOY_BUTTON_06"] = 0x06;
    _mapStr2JoyBtn["JOY_BUTTON_07"] = 0x07;
    _mapStr2JoyBtn["JOY_BUTTON_08"] = 0x08;
    _mapStr2JoyBtn["JOY_BUTTON_09"] = 0x09;
    _mapStr2JoyBtn["JOY_BUTTON_10"] = 0x0A;
    _mapStr2JoyBtn["JOY_BUTTON_11"] = 0x0B;
    _mapStr2JoyBtn["JOY_BUTTON_12"] = 0x0C;
    _mapStr2JoyBtn["JOY_BUTTON_13"] = 0x0D;
    _mapStr2JoyBtn["JOY_BUTTON_14"] = 0x0E;
    _mapStr2JoyBtn["JOY_BUTTON_15"] = 0x0F;
    _mapStr2JoyBtn["JOY_UP"]        = 0x80;
    _mapStr2JoyBtn["JOY_DOWN"]      = 0x81;
    _mapStr2JoyBtn["JOY_LEFT"]      = 0x82;
    _mapStr2JoyBtn["JOY_RIGHT"]     = 0x83;
    _mapStr2JoyBtn["JOY_POV_UP"]    = 0x90;
    _mapStr2JoyBtn["JOY_POV_DOWN"]  = 0x91;
    _mapStr2JoyBtn["JOY_POV_LEFT"]  = 0x92;
    _mapStr2JoyBtn["JOY_POV_RIGHT"] = 0x93;

    _mapDik2Str[0x01] = "DIK_ESCAPE";
    _mapDik2Str[0x02] = "DIK_1";
    _mapDik2Str[0x03] = "DIK_2";
    _mapDik2Str[0x04] = "DIK_3";
    _mapDik2Str[0x05] = "DIK_4";
    _mapDik2Str[0x06] = "DIK_5";
    _mapDik2Str[0x07] = "DIK_6";
    _mapDik2Str[0x08] = "DIK_7";
    _mapDik2Str[0x09] = "DIK_8";
    _mapDik2Str[0x0A] = "DIK_9";
    _mapDik2Str[0x0B] = "DIK_0";
    _mapDik2Str[0x0C] = "DIK_MINUS";
    _mapDik2Str[0x0D] = "DIK_EQUALS";
    _mapDik2Str[0x0E] = "DIK_BACK";
    _mapDik2Str[0x0F] = "DIK_TAB";
    _mapDik2Str[0x10] = "DIK_Q";
    _mapDik2Str[0x11] = "DIK_W";
    _mapDik2Str[0x12] = "DIK_E";
    _mapDik2Str[0x13] = "DIK_R";
    _mapDik2Str[0x14] = "DIK_T";
    _mapDik2Str[0x15] = "DIK_Y";
    _mapDik2Str[0x16] = "DIK_U";
    _mapDik2Str[0x17] = "DIK_I";
    _mapDik2Str[0x18] = "DIK_O";
    _mapDik2Str[0x19] = "DIK_P";
    _mapDik2Str[0x1A] = "DIK_LBRACKET";
    _mapDik2Str[0x1B] = "DIK_RBRACKET";
    _mapDik2Str[0x1C] = "DIK_RETURN";
    _mapDik2Str[0x1D] = "DIK_LCONTROL";
    _mapDik2Str[0x1E] = "DIK_A";
    _mapDik2Str[0x1F] = "DIK_S";
    _mapDik2Str[0x20] = "DIK_D";
    _mapDik2Str[0x21] = "DIK_F";
    _mapDik2Str[0x22] = "DIK_G";
    _mapDik2Str[0x23] = "DIK_H";
    _mapDik2Str[0x24] = "DIK_J";
    _mapDik2Str[0x25] = "DIK_K";
    _mapDik2Str[0x26] = "DIK_L";
    _mapDik2Str[0x27] = "DIK_SEMICOLON";
    _mapDik2Str[0x28] = "DIK_APOSTROPHE";
    _mapDik2Str[0x29] = "DIK_GRAVE";
    _mapDik2Str[0x2A] = "DIK_LSHIFT";
    _mapDik2Str[0x2B] = "DIK_BACKSLASH";
    _mapDik2Str[0x2C] = "DIK_Z";
    _mapDik2Str[0x2D] = "DIK_X";
    _mapDik2Str[0x2E] = "DIK_C";
    _mapDik2Str[0x2F] = "DIK_V";
    _mapDik2Str[0x30] = "DIK_B";
    _mapDik2Str[0x31] = "DIK_N";
    _mapDik2Str[0x32] = "DIK_M";
    _mapDik2Str[0x33] = "DIK_COMMA";
    _mapDik2Str[0x34] = "DIK_PERIOD";
    _mapDik2Str[0x35] = "DIK_SLASH";
    _mapDik2Str[0x36] = "DIK_RSHIFT";
    _mapDik2Str[0x37] = "DIK_MULTIPLY";
    _mapDik2Str[0x38] = "DIK_LMENU";
    _mapDik2Str[0x39] = "DIK_SPACE";
    _mapDik2Str[0x3A] = "DIK_CAPITAL";
    _mapDik2Str[0x3B] = "DIK_F1";
    _mapDik2Str[0x3C] = "DIK_F2";
    _mapDik2Str[0x3D] = "DIK_F3";
    _mapDik2Str[0x3E] = "DIK_F4";
    _mapDik2Str[0x3F] = "DIK_F5";
    _mapDik2Str[0x40] = "DIK_F6";
    _mapDik2Str[0x41] = "DIK_F7";
    _mapDik2Str[0x42] = "DIK_F8";
    _mapDik2Str[0x43] = "DIK_F9";
    _mapDik2Str[0x44] = "DIK_F10";
    _mapDik2Str[0x45] = "DIK_NUMLOCK";
    _mapDik2Str[0x46] = "DIK_SCROLL";
    _mapDik2Str[0x47] = "DIK_NUMPAD7";
    _mapDik2Str[0x48] = "DIK_NUMPAD8";
    _mapDik2Str[0x49] = "DIK_NUMPAD9";
    _mapDik2Str[0x4A] = "DIK_SUBTRACT";
    _mapDik2Str[0x4B] = "DIK_NUMPAD4";
    _mapDik2Str[0x4C] = "DIK_NUMPAD5";
    _mapDik2Str[0x4D] = "DIK_NUMPAD6";
    _mapDik2Str[0x4E] = "DIK_ADD";
    _mapDik2Str[0x4F] = "DIK_NUMPAD1";
    _mapDik2Str[0x50] = "DIK_NUMPAD2";
    _mapDik2Str[0x51] = "DIK_NUMPAD3";
    _mapDik2Str[0x52] = "DIK_NUMPAD0";
    _mapDik2Str[0x53] = "DIK_DECIMAL";
    _mapDik2Str[0x56] = "DIK_OEM_102";
    _mapDik2Str[0x57] = "DIK_F11";
    _mapDik2Str[0x58] = "DIK_F12";
    _mapDik2Str[0x64] = "DIK_F13";
    _mapDik2Str[0x65] = "DIK_F14";
    _mapDik2Str[0x66] = "DIK_F15";
    _mapDik2Str[0x70] = "DIK_KANA";
    _mapDik2Str[0x73] = "DIK_ABNT_C1";
    _mapDik2Str[0x79] = "DIK_CONVERT";
    _mapDik2Str[0x7B] = "DIK_NOCONVERT";
    _mapDik2Str[0x7D] = "DIK_YEN";
    _mapDik2Str[0x7E] = "DIK_ABNT_C2";
    _mapDik2Str[0x8D] = "DIK_NUMPADEQUALS";
    _mapDik2Str[0x90] = "DIK_PREVTRACK";
    _mapDik2Str[0x91] = "DIK_AT";
    _mapDik2Str[0x92] = "DIK_COLON";
    _mapDik2Str[0x93] = "DIK_UNDERLINE";
    _mapDik2Str[0x94] = "DIK_KANJI";
    _mapDik2Str[0x95] = "DIK_STOP";
    _mapDik2Str[0x96] = "DIK_AX";
    _mapDik2Str[0x97] = "DIK_UNLABELED";
    _mapDik2Str[0x99] = "DIK_NEXTTRACK";
    _mapDik2Str[0x9C] = "DIK_NUMPADENTER";
    _mapDik2Str[0x9D] = "DIK_RCONTROL";
    _mapDik2Str[0xA0] = "DIK_MUTE";
    _mapDik2Str[0xA1] = "DIK_CALCULATOR";
    _mapDik2Str[0xA2] = "DIK_PLAYPAUSE";
    _mapDik2Str[0xA4] = "DIK_MEDIASTOP";
    _mapDik2Str[0xAE] = "DIK_VOLUMEDOWN";
    _mapDik2Str[0xB0] = "DIK_VOLUMEUP";
    _mapDik2Str[0xB2] = "DIK_WEBHOME";
    _mapDik2Str[0xB3] = "DIK_NUMPADCOMMA";
    _mapDik2Str[0xB5] = "DIK_DIVIDE";
    _mapDik2Str[0xB7] = "DIK_SYSRQ";
    _mapDik2Str[0xB8] = "DIK_RMENU";
    _mapDik2Str[0xC5] = "DIK_PAUSE";
    _mapDik2Str[0xC7] = "DIK_HOME";
    _mapDik2Str[0xC8] = "DIK_UP";
    _mapDik2Str[0xC9] = "DIK_PRIOR";
    _mapDik2Str[0xCB] = "DIK_LEFT";
    _mapDik2Str[0xCD] = "DIK_RIGHT";
    _mapDik2Str[0xCF] = "DIK_END";
    _mapDik2Str[0xD0] = "DIK_DOWN";
    _mapDik2Str[0xD1] = "DIK_NEXT";
    _mapDik2Str[0xD2] = "DIK_INSERT";
    _mapDik2Str[0xD3] = "DIK_DELETE";
    _mapDik2Str[0xDB] = "DIK_LWIN";
    _mapDik2Str[0xDC] = "DIK_RWIN";
    _mapDik2Str[0xDD] = "DIK_APPS";
    _mapDik2Str[0xDE] = "DIK_POWER";
    _mapDik2Str[0xDF] = "DIK_SLEEP";
    _mapDik2Str[0xE3] = "DIK_WAKE";
    _mapDik2Str[0xE5] = "DIK_WEBSEARCH";
    _mapDik2Str[0xE6] = "DIK_WEBFAVORITES";
    _mapDik2Str[0xE7] = "DIK_WEBREFRESH";
    _mapDik2Str[0xE8] = "DIK_WEBSTOP";
    _mapDik2Str[0xE9] = "DIK_WEBFORWARD";
    _mapDik2Str[0xEA] = "DIK_WEBBACK";
    _mapDik2Str[0xEB] = "DIK_MYCOMPUTER";
    _mapDik2Str[0xEC] = "DIK_MAIL";
    _mapDik2Str[0xED] = "DIK_MEDIASELECT";
//    _mapDik2Str[0x0E] = "DIK_BACKSPACE";
//    _mapDik2Str[0x37] = "DIK_NUMPADSTAR";
//    _mapDik2Str[0x38] = "DIK_LALT";
//    _mapDik2Str[0x3A] = "DIK_CAPSLOCK";
//    _mapDik2Str[0x4A] = "DIK_NUMPADMINUS";
//    _mapDik2Str[0x4E] = "DIK_NUMPADPLUS";
//    _mapDik2Str[0x53] = "DIK_NUMPADPERIOD";
//    _mapDik2Str[0xB5] = "DIK_NUMPADSLASH";
//    _mapDik2Str[0xB8] = "DIK_RALT";
//    _mapDik2Str[0xC8] = "DIK_UPARROW";
//    _mapDik2Str[0xC9] = "DIK_PGUP";
//    _mapDik2Str[0xCB] = "DIK_LEFTARROW";
//    _mapDik2Str[0xCD] = "DIK_RIGHTARROW";
//    _mapDik2Str[0xD0] = "DIK_DOWNARROW";
//    _mapDik2Str[0xD1] = "DIK_PGDN";

    _mapJoyBtn2Str[0x00] = "JOY_BUTTON_00";
    _mapJoyBtn2Str[0x01] = "JOY_BUTTON_01";
    _mapJoyBtn2Str[0x02] = "JOY_BUTTON_02";
    _mapJoyBtn2Str[0x03] = "JOY_BUTTON_03";
    _mapJoyBtn2Str[0x04] = "JOY_BUTTON_04";
    _mapJoyBtn2Str[0x05] = "JOY_BUTTON_05";
    _mapJoyBtn2Str[0x06] = "JOY_BUTTON_06";
    _mapJoyBtn2Str[0x07] = "JOY_BUTTON_07";
    _mapJoyBtn2Str[0x08] = "JOY_BUTTON_08";
    _mapJoyBtn2Str[0x09] = "JOY_BUTTON_09";
    _mapJoyBtn2Str[0x0A] = "JOY_BUTTON_10";
    _mapJoyBtn2Str[0x0B] = "JOY_BUTTON_11";
    _mapJoyBtn2Str[0x0C] = "JOY_BUTTON_12";
    _mapJoyBtn2Str[0x0D] = "JOY_BUTTON_13";
    _mapJoyBtn2Str[0x0E] = "JOY_BUTTON_14";
    _mapJoyBtn2Str[0x0F] = "JOY_BUTTON_15";
    _mapJoyBtn2Str[0x80] = "JOY_UP";
    _mapJoyBtn2Str[0x81] = "JOY_DOWN";
    _mapJoyBtn2Str[0x82] = "JOY_LEFT";
    _mapJoyBtn2Str[0x83] = "JOY_RIGHT";
    _mapJoyBtn2Str[0x90] = "JOY_POV_UP";
    _mapJoyBtn2Str[0x91] = "JOY_POV_DOWN";
    _mapJoyBtn2Str[0x92] = "JOY_POV_LEFT";
    _mapJoyBtn2Str[0x93] = "JOY_POV_RIGHT";


    _mapVJoyBtn2Func[0x80] = GgafDxCore::GgafDxInput::isBeingPressedJoyUp;
    _mapVJoyBtn2Func[0x81] = GgafDxCore::GgafDxInput::isBeingPressedJoyDown;
    _mapVJoyBtn2Func[0x82] = GgafDxCore::GgafDxInput::isBeingPressedJoyLeft;
    _mapVJoyBtn2Func[0x83] = GgafDxCore::GgafDxInput::isBeingPressedJoyRight;
    _mapVJoyBtn2Func[0x90] = GgafDxCore::GgafDxInput::isBeingPressedPovUp;
    _mapVJoyBtn2Func[0x91] = GgafDxCore::GgafDxInput::isBeingPressedPovDown;
    _mapVJoyBtn2Func[0x92] = GgafDxCore::GgafDxInput::isBeingPressedPovLeft;
    _mapVJoyBtn2Func[0x93] = GgafDxCore::GgafDxInput::isBeingPressedPovRight;
}

VirtualButton::VBRecord* VirtualButton::getPastVBRecord(frame prm_frame_ago) {
    VirtualButton::VBRecord* pVBRecord_temp = _pVBRecord_active;
    for (frame i = 0; i < prm_frame_ago; i++) {
        pVBRecord_temp = pVBRecord_temp->_prev;
    }
    return pVBRecord_temp;
}

vbsta VirtualButton::isAutoRepeat(vbsta prm_VB, frame prm_begin_repeat, frame prm_while_repeat) {
    vbsta sta = (_pVBRecord_active->_state & prm_VB);
    if (sta) {
        _is_auto_repeat = true;
        if (sta == (_pVBRecord_active->_prev->_state & prm_VB)) {
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
            //�L�[�C�����ɂ܂�����
            return sta;
        } else if (_auto_repeat_counter[prm_VB] > prm_begin_repeat && _auto_repeat_counter[prm_VB] % prm_while_repeat == 0) {
            //�I�[�g���s�[�g������(�f�t�H���g�ł́A20�t���[����ȍ~��5�t���[�����ɐ���)
            return sta;
        }
    }
    return false;
}



vbsta VirtualButton::wasBeingPressed(vbsta prm_VB, frame prm_frame_ago) {
    VirtualButton::VBRecord* pVBRecord_temp = getPastVBRecord(prm_frame_ago);
    return (pVBRecord_temp->_state & prm_VB);
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

vbsta VirtualButton::isDoublePushedDown(vbsta prm_VB, frame prm_frame_push, frame prm_frame_delay) {
    //-------oooo-----o
    //       <--><--->
    //         |    `-- prm_frame_delay
    //         `-- prm_frame_push
    //�ߋ��ɑk��Ȃ��猟��
    VirtualButton::VBRecord* pVBRecord;
    pVBRecord = _pVBRecord_active;
    if (pVBRecord->_state & prm_VB) {
        //OK
    } else {
        return false;
    }
    pVBRecord = pVBRecord->_prev;
    //���O�͕K��������Ă��Ă͑ʖ�
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



////������������Ă��Ȃ���������
//bool VirtualButton::isNonAfterPushedDown(int prm_VB) {
//	if (_pVBRecord_active->_state[prm_VB]) {
//		for (int i = 0; i < VB_NUM; i++) {
//			if (_pVBRecord_active->_prev->_state[i]) {
//				return false;
//			}
//		}
//		return true;
//	} else {
//		return false;
//	}
//}

vbsta VirtualButton::arePushedDownAtOnce(vbsta prm_aVB[], int prm_num_button) {

    //���݂͑S�ĉ�����Ă��Ȃ���΂Ȃ�Ȃ�
    for (int i = 0; i < prm_num_button; i++) {
        if (isBeingPressed(prm_aVB[i]) == false) {
            return false;
        }
    }

    //�R�t���[���]�T������
    //�S�{�^���ɂ��āA���ꂼ�ꂪ�ȉ��̂��Âꂩ�̓���ɂȂ��Ă��邩�`�F�b�N�B
    // �� > �H > �H > ��
    //       or
    // �H > �� > �H > ��
    //       or
    // �H > �H > �� > ��
    bool prev1Flg, prev2Flg, prev3Flg;
    for (int i = 0; i < prm_num_button; i++) {
        prev1Flg = wasNotBeingPressed(prm_aVB[i], 1);
        prev2Flg = wasNotBeingPressed(prm_aVB[i], 2);
        prev3Flg = wasNotBeingPressed(prm_aVB[i], 3);
        if (prev1Flg) { //�� > �� > �� >
            continue;
        } else if (prev2Flg) { //�� > �� > �� >
            continue;
        } else if (prev3Flg) { //�� > �� > �� >
            continue;
        } else {
            return false;
        }
    }

    //�A��1�O�̃t���[���ŁA�S�ĉ�����Ă��Ă͐������Ȃ��B
    //���̏�������Ȃ��ƁA�u�����������������ςȂ��v�̏ꍇ�A�ő�R�t���[���A���Ő������Ă��܂��ꍇ������B
    for (int i = 0; i < prm_num_button; i++) {
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
    if ((_pVBRecord_active->_prev->_state & prm_VB) && !(_pVBRecord_active->_state & prm_VB)) {
        return true;
    } else {
        return false;
    }
}

vbsta VirtualButton::isPushedUp(vbsta prm_VB, frame prm_frame_push) {
    //���ߋ�      ����
    //            ��
    //---------ooo-
    //       <--->
    //         |
    //         `-- prm_frame_push

    //�ߋ��ɑk��Ȃ��猟��
    VirtualButton::VBRecord* pVBRecord;
    pVBRecord = _pVBRecord_active;
    //���݂͉�����Ă��Ă͑ʖ�
    if (pVBRecord->_state & prm_VB) {
        return false;
    } else {
        //OK
    }
    pVBRecord = pVBRecord->_prev;
    //���O�͉�����Ă��Ȃ���΂����Ȃ�
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
            //prm_frame_push���ԓ��ɗ����Ă����OK
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


bool VirtualButton::isScrewPushDown(vbsta prm_VB, frame prm_frame_delay) {
    if (isPushedDown(prm_VB)) {
        VirtualButton::VBRecord* pVBRecord;
        pVBRecord = _pVBRecord_active;
        bool up    = false;
        bool down  = false;
        bool left  = false;
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
        return (up && down && left && right) ? true : false;
    } else {
        return false;
    }
}



//vbsta VirtualButton::getPushedDownStickWith(vbsta prm_VB) {
//    if (isBeingPressed(prm_VB)) {
//        static bool prev1Flg, prev2Flg, prev3Flg;
//        //�{�^���ɉ�����Ă��Ȃ����Ԃ����O�ɂ�������
//        prev1Flg = wasNotBeingPressed(prm_VB, 1);
//        prev2Flg = wasNotBeingPressed(prm_VB, 2);
//        prev3Flg = wasNotBeingPressed(prm_VB, 3);
//        if (prev1Flg) { //�� > �� > �� >
//            //OK
//        } else if (prev2Flg) { //�� > �� > �� >
//            //OK
//        } else if (prev3Flg) { //�� > �� > �� >
//            //OK
//        } else {
//            //NG
//            return 0;
//        }
//
//        //�X�e�B�b�N�ɉ�����Ă��Ȃ����Ԃ����O�ɂ�������
//        static bool prev1N_Flg, prev2N_Flg, prev3N_Flg;
//        prev1N_Flg = wasBeingPressed(VB_NEUTRAL_STC, 1);
//        prev2N_Flg = wasBeingPressed(VB_NEUTRAL_STC, 2);
//        prev3N_Flg = wasBeingPressed(VB_NEUTRAL_STC, 3);
//        if (prev1N_Flg) { //�� > �� > �m >
//            //OK
//        } else if (prev2N_Flg) { //�� > �m > �� >
//            //OK
//        } else if (prev3N_Flg) { //�m > �� > �� >
//            //OK
//        } else {
//            //NG
//            return 0;
//        }
//
//        for (int i = VB_UP_RIGHT_STC; i <= VB_LEFT_STC; i++) {
//            //���͉����Ă���
//            if (isBeingPressed(i)) {
//
//                //�A��1�O�̃t���[���ŁA����������Ă��Ă͐������Ȃ��B
//                //�i���̏�������Ȃ��ƁA�u�����������������ςȂ��v�̏ꍇ�A���t���[���A���Ő������Ă��܂��j
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
    return _pVBRecord_active->_state;
}

void VirtualButton::update() {
#ifdef MY_DEBUG
    if (_pVBRecord_active == nullptr) {
        throwGgafCriticalException("VirtualButton::update() ���p�O�Ɉ�x init() ���Ăяo���ĉ������B");
    }
#endif
    GgafDxInput::updateKeyboardState();
    GgafDxInput::updateJoystickState();

    if (_is_replaying && _was_replay_done == false) {
        //���v���C���[�h��
        _pVBRecord_active = _pVBRecord_active->_next;
        _pVBRecord_active->_state = _pRpy->read();
        if (_pVBRecord_active->_state == 0) {
            _was_replay_done = true;
        }
        return;

    } else {

        //�ʏ푀�쎞
        _pVBRecord_active = _pVBRecord_active->_next;

        vbsta state = 0;
        KEYBOARDMAP& kmap = _keyboardmap;
        JOYSTICKMAP& jmap = _joystickmap;

        state |= (VB_BUTTON1  * GgafDxInput::isBeingPressedKey(kmap.BUTTON1));
        state |= (VB_BUTTON2  * GgafDxInput::isBeingPressedKey(kmap.BUTTON2));
        state |= (VB_BUTTON3  * GgafDxInput::isBeingPressedKey(kmap.BUTTON3));
        state |= (VB_BUTTON4  * GgafDxInput::isBeingPressedKey(kmap.BUTTON4));
        state |= (VB_BUTTON5  * GgafDxInput::isBeingPressedKey(kmap.BUTTON5));
        state |= (VB_BUTTON6  * GgafDxInput::isBeingPressedKey(kmap.BUTTON6));
        state |= (VB_BUTTON7  * GgafDxInput::isBeingPressedKey(kmap.BUTTON7));
        state |= (VB_BUTTON8  * GgafDxInput::isBeingPressedKey(kmap.BUTTON8));
        state |= (VB_BUTTON9  * GgafDxInput::isBeingPressedKey(kmap.BUTTON9));
        state |= (VB_BUTTON10 * GgafDxInput::isBeingPressedKey(kmap.BUTTON10));
        state |= (VB_BUTTON11 * GgafDxInput::isBeingPressedKey(kmap.BUTTON11));
        state |= (VB_BUTTON12 * GgafDxInput::isBeingPressedKey(kmap.BUTTON12));
        state |= (VB_BUTTON13 * GgafDxInput::isBeingPressedKey(kmap.BUTTON13));
        state |= (VB_BUTTON14 * GgafDxInput::isBeingPressedKey(kmap.BUTTON14));
        state |= (VB_BUTTON15 * GgafDxInput::isBeingPressedKey(kmap.BUTTON15));
        state |= (VB_BUTTON16 * GgafDxInput::isBeingPressedKey(kmap.BUTTON16));
        state |= (VB_PAUSE   * GgafDxInput::isBeingPressedKey(kmap.PAUSE));
        state |= (VB_UP    * GgafDxInput::isBeingPressedKey(kmap.UP));
        state |= (VB_DOWN  * GgafDxInput::isBeingPressedKey(kmap.DOWN));
        state |= (VB_LEFT  * GgafDxInput::isBeingPressedKey(kmap.LEFT));
        state |= (VB_RIGHT * GgafDxInput::isBeingPressedKey(kmap.RIGHT));
        state |= (VB_UI_UP    * GgafDxInput::isBeingPressedKey(kmap.UI_UP));
        state |= (VB_UI_DOWN  * GgafDxInput::isBeingPressedKey(kmap.UI_DOWN));
        state |= (VB_UI_LEFT  * GgafDxInput::isBeingPressedKey(kmap.UI_LEFT));
        state |= (VB_UI_RIGHT * GgafDxInput::isBeingPressedKey(kmap.UI_RIGHT));
        state |= (VB_UI_EXECUTE * GgafDxInput::isBeingPressedKey(kmap.UI_EXECUTE));
        state |= (VB_UI_CANCEL * GgafDxInput::isBeingPressedKey(kmap.UI_CANCEL));
        state |= (VB_UI_DEBUG * GgafDxInput::isBeingPressedKey(kmap.UI_DEBUG));

        if (GgafDxInput::_pJoystickInputDevice) {
            state |= (VB_BUTTON1  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON1));
            state |= (VB_BUTTON2  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON2));
            state |= (VB_BUTTON3  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON3));
            state |= (VB_BUTTON4  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON4));
            state |= (VB_BUTTON5  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON5));
            state |= (VB_BUTTON6  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON6));
            state |= (VB_BUTTON7  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON7));
            state |= (VB_BUTTON8  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON8));
            state |= (VB_BUTTON9  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON9));
            state |= (VB_BUTTON10 * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON10));
            state |= (VB_BUTTON11 * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON11));
            state |= (VB_BUTTON12 * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON12));
            state |= (VB_BUTTON13 * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON13));
            state |= (VB_BUTTON14 * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON14));
            state |= (VB_BUTTON15 * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON15));
            state |= (VB_BUTTON16 * VirtualButton::isBeingPressedVirtualJoyButton(jmap.BUTTON16));
            state |= (VB_PAUSE * VirtualButton::isBeingPressedVirtualJoyButton(jmap.PAUSE));
            state |= (VB_UP    * VirtualButton::isBeingPressedVirtualJoyButton(jmap.UP)    );
            state |= (VB_DOWN  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.DOWN)  );
            state |= (VB_LEFT  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.LEFT)  );
            state |= (VB_RIGHT * VirtualButton::isBeingPressedVirtualJoyButton(jmap.RIGHT) );
            if (_with_pov) {
                state |= (VB_UI_UP    * (VirtualButton::isBeingPressedVirtualJoyButton(jmap.UI_UP)    ||  GgafDxInput::isBeingPressedPovUp()    ));
                state |= (VB_UI_DOWN  * (VirtualButton::isBeingPressedVirtualJoyButton(jmap.UI_DOWN)  ||  GgafDxInput::isBeingPressedPovDown()  ));
                state |= (VB_UI_LEFT  * (VirtualButton::isBeingPressedVirtualJoyButton(jmap.UI_LEFT)  ||  GgafDxInput::isBeingPressedPovLeft()  ));
                state |= (VB_UI_RIGHT * (VirtualButton::isBeingPressedVirtualJoyButton(jmap.UI_RIGHT) ||  GgafDxInput::isBeingPressedPovRight() ));
            } else {
                state |= (VB_UI_UP    * VirtualButton::isBeingPressedVirtualJoyButton(jmap.UI_UP)   );
                state |= (VB_UI_DOWN  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.UI_DOWN) );
                state |= (VB_UI_LEFT  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.UI_LEFT) );
                state |= (VB_UI_RIGHT * VirtualButton::isBeingPressedVirtualJoyButton(jmap.UI_RIGHT));

            }
            state |= (VB_UI_EXECUTE * VirtualButton::isBeingPressedVirtualJoyButton(jmap.UI_EXECUTE));
            state |= (VB_UI_CANCEL * VirtualButton::isBeingPressedVirtualJoyButton(jmap.UI_CANCEL));
            //state |= (VB_UI_DEBUG * VirtualButton::isBeingPressedVirtualJoyButton(jmap.UI_DEBUG)); //JoyStick�ɂ�DEBUG�{�^���͖����d�l
        }
        _pVBRecord_active->_state = state;
    }
    _pRpy->write(_pVBRecord_active->_state); //���v���C���L�^
}


void VirtualButton::clear() {
    VirtualButton::VBRecord* pVBRecord = _pVBRecord_active;
    for (int i = 0; i < VB_MAP_BUFFER; i++) {
        pVBRecord->_state = 0;
        pVBRecord = pVBRecord->_next;
    }
}


 bool VirtualButton::isBeingPressedVirtualJoyButton(int prm_virtual_joy_button_no) {
    if (0 <= prm_virtual_joy_button_no && prm_virtual_joy_button_no <= 0x0F) {
        return GgafDxCore::GgafDxInput::isBeingPressedJoyButton(prm_virtual_joy_button_no);
    } else {
        if ( ( 0x80 <= prm_virtual_joy_button_no && prm_virtual_joy_button_no <= 0x83 ) ||
             ( 0x90 <= prm_virtual_joy_button_no && prm_virtual_joy_button_no <= 0x93 )   )
        {
            return (_mapVJoyBtn2Func[prm_virtual_joy_button_no])();
        } else {
            return -1;
        }
    }
}
int VirtualButton::getPushedDownVirtualJoyButton() {
    int JOY_pushed = GgafDxInput::getPushedDownJoyRgbButton();
    if (JOY_pushed == -1) {
        if (GgafDxInput::isBeingPressedJoyUp()) {
            return 0x80;
        } else if (GgafDxInput::isBeingPressedJoyDown()) {
            return 0x81;
        } else if (GgafDxInput::isBeingPressedJoyLeft()) {
            return 0x82;
        } else if (GgafDxInput::isBeingPressedJoyRight()) {
            return 0x83;
        } else if (GgafDxInput::isBeingPressedPovUp()) {
            return 0x90;
        } else if (GgafDxInput::isBeingPressedPovDown()) {
            return 0x91;
        } else if (GgafDxInput::isBeingPressedPovLeft()) {
            return 0x92;
        } else if (GgafDxInput::isBeingPressedPovRight()) {
            return 0x93;
        } else {
            return -1;
        }
     } else {
         return JOY_pushed;
     }
}

VirtualButton::~VirtualButton() {
    GGAF_DELETE(_pRpy);
    VirtualButton::VBRecord* pLast = _pVBRecord_active->_next;
    VirtualButton::VBRecord* pWk;
    for (VirtualButton::VBRecord* p = _pVBRecord_active->_prev; p != _pVBRecord_active; p = p->_prev) {
        pWk = p->_next;
        GGAF_DELETE(pWk);
    }
    GGAF_DELETE(pLast);
}

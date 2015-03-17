#include "jp/ggaf/lib/util/VirtualButton.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/lib/util/VBReplayRecorder.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

VirtualButton::VirtualButton(const char* prm_replay_file) : GgafObject() {
    _keyboardmap.BUTTON1     = VBK_Z;
    _keyboardmap.BUTTON2     = VBK_X;
    _keyboardmap.BUTTON3     = VBK_C;
    _keyboardmap.BUTTON4     = VBK_A;
    _keyboardmap.BUTTON5     = VBK_S;
    _keyboardmap.BUTTON6     = VBK_D;
    _keyboardmap.BUTTON7     = VBK_V;
    _keyboardmap.BUTTON8     = VBK_B;
    _keyboardmap.BUTTON9     = VBK_N;
    _keyboardmap.BUTTON10    = VBK_M;
    _keyboardmap.BUTTON11    = 0xFF;
    _keyboardmap.BUTTON12    = 0xFF;
    _keyboardmap.BUTTON13    = 0xFF;
    _keyboardmap.BUTTON14    = 0xFF;
    _keyboardmap.BUTTON15    = 0xFF;
    _keyboardmap.BUTTON16    = 0xFF;
    _keyboardmap.PAUSE       = VBK_ESCAPE;
    _keyboardmap.UP          = VBK_UP;
    _keyboardmap.DOWN        = VBK_DOWN;
    _keyboardmap.LEFT        = VBK_LEFT;
    _keyboardmap.RIGHT       = VBK_RIGHT;
    _keyboardmap.S1_UP       = 0xFF;
    _keyboardmap.S1_DOWN     = 0xFF;
    _keyboardmap.S1_LEFT     = 0xFF;
    _keyboardmap.S1_RIGHT    = 0xFF;
    _keyboardmap.S2_UP       = 0xFF;
    _keyboardmap.S2_DOWN     = 0xFF;
    _keyboardmap.S2_LEFT     = 0xFF;
    _keyboardmap.S2_RIGHT    = 0xFF;
    _keyboardmap.UI_UP       = VBK_UP;
    _keyboardmap.UI_DOWN     = VBK_DOWN;
    _keyboardmap.UI_LEFT     = VBK_LEFT;
    _keyboardmap.UI_RIGHT    = VBK_RIGHT;
    _keyboardmap.UI_EXECUTE  = VBK_RETURN;
    _keyboardmap.UI_CANCEL   = VBK_ESCAPE;
    _keyboardmap.UI_DEBUG    = VBK_Q;

    _joystickmap.BUTTON1     = VBJ_BUTTON_01;
    _joystickmap.BUTTON2     = VBJ_BUTTON_02;
    _joystickmap.BUTTON3     = VBJ_BUTTON_03;
    _joystickmap.BUTTON4     = VBJ_BUTTON_04;
    _joystickmap.BUTTON5     = VBJ_BUTTON_05;
    _joystickmap.BUTTON6     = VBJ_BUTTON_06;
    _joystickmap.BUTTON7     = VBJ_BUTTON_07;
    _joystickmap.BUTTON8     = VBJ_BUTTON_08;
    _joystickmap.BUTTON9     = VBJ_BUTTON_09;
    _joystickmap.BUTTON10    = VBJ_BUTTON_10;
    _joystickmap.BUTTON11    = VBJ_BUTTON_11;
    _joystickmap.BUTTON12    = VBJ_BUTTON_12;
    _joystickmap.BUTTON13    = VBJ_BUTTON_13;
    _joystickmap.BUTTON14    = VBJ_BUTTON_14;
    _joystickmap.BUTTON15    = VBJ_BUTTON_15;
    _joystickmap.BUTTON16    = VBJ_BUTTON_16;
    _joystickmap.PAUSE       = VBJ_BUTTON_08;
    _joystickmap.UP          = VBJ_Y_POS_MINUS;
    _joystickmap.DOWN        = VBJ_Y_POS_PLUS ;
    _joystickmap.LEFT        = VBJ_X_POS_MINUS;
    _joystickmap.RIGHT       = VBJ_X_POS_PLUS ;
    _joystickmap.S1_UP       = 0xFF;
    _joystickmap.S1_DOWN     = 0xFF;
    _joystickmap.S1_LEFT     = 0xFF;
    _joystickmap.S1_RIGHT    = 0xFF;
    _joystickmap.S2_UP       = 0xFF;
    _joystickmap.S2_DOWN     = 0xFF;
    _joystickmap.S2_LEFT     = 0xFF;
    _joystickmap.S2_RIGHT    = 0xFF;
    _joystickmap.UI_UP       = VBJ_Y_POS_MINUS;
    _joystickmap.UI_DOWN     = VBJ_Y_POS_PLUS ;
    _joystickmap.UI_LEFT     = VBJ_X_POS_MINUS;
    _joystickmap.UI_RIGHT    = VBJ_X_POS_PLUS ;
    _joystickmap.UI_EXECUTE  = VBJ_BUTTON_01;
    _joystickmap.UI_CANCEL   = VBJ_BUTTON_02;
    //_joystickmap.UI_DEBUG    = //; 0xFF


    //環状双方向連結リスト構築
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
        //読み込めた場合リプレイモード
        _TRACE_("VirtualButton("<<prm_replay_file<<") リプレイモードです。");
        _is_replaying = true;
    } else {
        //読み込めない場合は通常記録モード
        _is_replaying = false;
        _TRACE_("VirtualButton("<<prm_replay_file<<") 通常記録モード。");
    }

    _was_replay_done = false;
    _with_pov = true;

    static bool is_init = VirtualButton::initStatic(); //静的メンバ初期化
}

std::map<std::string, int> VirtualButton::_mapStr2VBK;
std::map<std::string, int> VirtualButton::_mapStr2VBJ;
std::map<int, std::string> VirtualButton::_mapVBK2Str;
std::map<int, std::string> VirtualButton::_mapVBJ2Str;
std::map<int, VirtualButton::funcVJBtn> VirtualButton::_mapVBJ2Func;
bool VirtualButton::initStatic() {
    VirtualButton::_mapStr2VBK["VBK_ESCAPE"]       = VBK_ESCAPE      ;
    VirtualButton::_mapStr2VBK["VBK_1"]            = VBK_1           ;
    VirtualButton::_mapStr2VBK["VBK_2"]            = VBK_2           ;
    VirtualButton::_mapStr2VBK["VBK_3"]            = VBK_3           ;
    VirtualButton::_mapStr2VBK["VBK_4"]            = VBK_4           ;
    VirtualButton::_mapStr2VBK["VBK_5"]            = VBK_5           ;
    VirtualButton::_mapStr2VBK["VBK_6"]            = VBK_6           ;
    VirtualButton::_mapStr2VBK["VBK_7"]            = VBK_7           ;
    VirtualButton::_mapStr2VBK["VBK_8"]            = VBK_8           ;
    VirtualButton::_mapStr2VBK["VBK_9"]            = VBK_9           ;
    VirtualButton::_mapStr2VBK["VBK_0"]            = VBK_0           ;
    VirtualButton::_mapStr2VBK["VBK_MINUS"]        = VBK_MINUS       ;
    VirtualButton::_mapStr2VBK["VBK_EQUALS"]       = VBK_EQUALS      ;
    VirtualButton::_mapStr2VBK["VBK_BACK"]         = VBK_BACK        ;
    VirtualButton::_mapStr2VBK["VBK_TAB"]          = VBK_TAB         ;
    VirtualButton::_mapStr2VBK["VBK_Q"]            = VBK_Q           ;
    VirtualButton::_mapStr2VBK["VBK_W"]            = VBK_W           ;
    VirtualButton::_mapStr2VBK["VBK_E"]            = VBK_E           ;
    VirtualButton::_mapStr2VBK["VBK_R"]            = VBK_R           ;
    VirtualButton::_mapStr2VBK["VBK_T"]            = VBK_T           ;
    VirtualButton::_mapStr2VBK["VBK_Y"]            = VBK_Y           ;
    VirtualButton::_mapStr2VBK["VBK_U"]            = VBK_U           ;
    VirtualButton::_mapStr2VBK["VBK_I"]            = VBK_I           ;
    VirtualButton::_mapStr2VBK["VBK_O"]            = VBK_O           ;
    VirtualButton::_mapStr2VBK["VBK_P"]            = VBK_P           ;
    VirtualButton::_mapStr2VBK["VBK_LBRACKET"]     = VBK_LBRACKET    ;
    VirtualButton::_mapStr2VBK["VBK_RBRACKET"]     = VBK_RBRACKET    ;
    VirtualButton::_mapStr2VBK["VBK_RETURN"]       = VBK_RETURN      ;
    VirtualButton::_mapStr2VBK["VBK_LCONTROL"]     = VBK_LCONTROL    ;
    VirtualButton::_mapStr2VBK["VBK_A"]            = VBK_A           ;
    VirtualButton::_mapStr2VBK["VBK_S"]            = VBK_S           ;
    VirtualButton::_mapStr2VBK["VBK_D"]            = VBK_D           ;
    VirtualButton::_mapStr2VBK["VBK_F"]            = VBK_F           ;
    VirtualButton::_mapStr2VBK["VBK_G"]            = VBK_G           ;
    VirtualButton::_mapStr2VBK["VBK_H"]            = VBK_H           ;
    VirtualButton::_mapStr2VBK["VBK_J"]            = VBK_J           ;
    VirtualButton::_mapStr2VBK["VBK_K"]            = VBK_K           ;
    VirtualButton::_mapStr2VBK["VBK_L"]            = VBK_L           ;
    VirtualButton::_mapStr2VBK["VBK_SEMICOLON"]    = VBK_SEMICOLON   ;
    VirtualButton::_mapStr2VBK["VBK_APOSTROPHE"]   = VBK_APOSTROPHE  ;
    VirtualButton::_mapStr2VBK["VBK_GRAVE"]        = VBK_GRAVE       ;
    VirtualButton::_mapStr2VBK["VBK_LSHIFT"]       = VBK_LSHIFT      ;
    VirtualButton::_mapStr2VBK["VBK_BACKSLASH"]    = VBK_BACKSLASH   ;
    VirtualButton::_mapStr2VBK["VBK_Z"]            = VBK_Z           ;
    VirtualButton::_mapStr2VBK["VBK_X"]            = VBK_X           ;
    VirtualButton::_mapStr2VBK["VBK_C"]            = VBK_C           ;
    VirtualButton::_mapStr2VBK["VBK_V"]            = VBK_V           ;
    VirtualButton::_mapStr2VBK["VBK_B"]            = VBK_B           ;
    VirtualButton::_mapStr2VBK["VBK_N"]            = VBK_N           ;
    VirtualButton::_mapStr2VBK["VBK_M"]            = VBK_M           ;
    VirtualButton::_mapStr2VBK["VBK_COMMA"]        = VBK_COMMA       ;
    VirtualButton::_mapStr2VBK["VBK_PERIOD"]       = VBK_PERIOD      ;
    VirtualButton::_mapStr2VBK["VBK_SLASH"]        = VBK_SLASH       ;
    VirtualButton::_mapStr2VBK["VBK_RSHIFT"]       = VBK_RSHIFT      ;
    VirtualButton::_mapStr2VBK["VBK_MULTIPLY"]     = VBK_MULTIPLY    ;
    VirtualButton::_mapStr2VBK["VBK_LMENU"]        = VBK_LMENU       ;
    VirtualButton::_mapStr2VBK["VBK_SPACE"]        = VBK_SPACE       ;
    VirtualButton::_mapStr2VBK["VBK_CAPITAL"]      = VBK_CAPITAL     ;
    VirtualButton::_mapStr2VBK["VBK_F1"]           = VBK_F1          ;
    VirtualButton::_mapStr2VBK["VBK_F2"]           = VBK_F2          ;
    VirtualButton::_mapStr2VBK["VBK_F3"]           = VBK_F3          ;
    VirtualButton::_mapStr2VBK["VBK_F4"]           = VBK_F4          ;
    VirtualButton::_mapStr2VBK["VBK_F5"]           = VBK_F5          ;
    VirtualButton::_mapStr2VBK["VBK_F6"]           = VBK_F6          ;
    VirtualButton::_mapStr2VBK["VBK_F7"]           = VBK_F7          ;
    VirtualButton::_mapStr2VBK["VBK_F8"]           = VBK_F8          ;
    VirtualButton::_mapStr2VBK["VBK_F9"]           = VBK_F9          ;
    VirtualButton::_mapStr2VBK["VBK_F10"]          = VBK_F10         ;
    VirtualButton::_mapStr2VBK["VBK_NUMLOCK"]      = VBK_NUMLOCK     ;
    VirtualButton::_mapStr2VBK["VBK_SCROLL"]       = VBK_SCROLL      ;
    VirtualButton::_mapStr2VBK["VBK_NUMPAD7"]      = VBK_NUMPAD7     ;
    VirtualButton::_mapStr2VBK["VBK_NUMPAD8"]      = VBK_NUMPAD8     ;
    VirtualButton::_mapStr2VBK["VBK_NUMPAD9"]      = VBK_NUMPAD9     ;
    VirtualButton::_mapStr2VBK["VBK_SUBTRACT"]     = VBK_SUBTRACT    ;
    VirtualButton::_mapStr2VBK["VBK_NUMPAD4"]      = VBK_NUMPAD4     ;
    VirtualButton::_mapStr2VBK["VBK_NUMPAD5"]      = VBK_NUMPAD5     ;
    VirtualButton::_mapStr2VBK["VBK_NUMPAD6"]      = VBK_NUMPAD6     ;
    VirtualButton::_mapStr2VBK["VBK_ADD"]          = VBK_ADD         ;
    VirtualButton::_mapStr2VBK["VBK_NUMPAD1"]      = VBK_NUMPAD1     ;
    VirtualButton::_mapStr2VBK["VBK_NUMPAD2"]      = VBK_NUMPAD2     ;
    VirtualButton::_mapStr2VBK["VBK_NUMPAD3"]      = VBK_NUMPAD3     ;
    VirtualButton::_mapStr2VBK["VBK_NUMPAD0"]      = VBK_NUMPAD0     ;
    VirtualButton::_mapStr2VBK["VBK_DECIMAL"]      = VBK_DECIMAL     ;
    VirtualButton::_mapStr2VBK["VBK_OEM_102"]      = VBK_OEM_102     ;
    VirtualButton::_mapStr2VBK["VBK_F11"]          = VBK_F11         ;
    VirtualButton::_mapStr2VBK["VBK_F12"]          = VBK_F12         ;
    VirtualButton::_mapStr2VBK["VBK_F13"]          = VBK_F13         ;
    VirtualButton::_mapStr2VBK["VBK_F14"]          = VBK_F14         ;
    VirtualButton::_mapStr2VBK["VBK_F15"]          = VBK_F15         ;
    VirtualButton::_mapStr2VBK["VBK_KANA"]         = VBK_KANA        ;
    VirtualButton::_mapStr2VBK["VBK_ABNT_C1"]      = VBK_ABNT_C1     ;
    VirtualButton::_mapStr2VBK["VBK_CONVERT"]      = VBK_CONVERT     ;
    VirtualButton::_mapStr2VBK["VBK_NOCONVERT"]    = VBK_NOCONVERT   ;
    VirtualButton::_mapStr2VBK["VBK_YEN"]          = VBK_YEN         ;
    VirtualButton::_mapStr2VBK["VBK_ABNT_C2"]      = VBK_ABNT_C2     ;
    VirtualButton::_mapStr2VBK["VBK_NUMPADEQUALS"] = VBK_NUMPADEQUALS;
    VirtualButton::_mapStr2VBK["VBK_PREVTRACK"]    = VBK_PREVTRACK   ;
    VirtualButton::_mapStr2VBK["VBK_AT"]           = VBK_AT          ;
    VirtualButton::_mapStr2VBK["VBK_COLON"]        = VBK_COLON       ;
    VirtualButton::_mapStr2VBK["VBK_UNDERLINE"]    = VBK_UNDERLINE   ;
    VirtualButton::_mapStr2VBK["VBK_KANJI"]        = VBK_KANJI       ;
    VirtualButton::_mapStr2VBK["VBK_STOP"]         = VBK_STOP        ;
    VirtualButton::_mapStr2VBK["VBK_AX"]           = VBK_AX          ;
    VirtualButton::_mapStr2VBK["VBK_UNLABELED"]    = VBK_UNLABELED   ;
    VirtualButton::_mapStr2VBK["VBK_NEXTTRACK"]    = VBK_NEXTTRACK   ;
    VirtualButton::_mapStr2VBK["VBK_NUMPADENTER"]  = VBK_NUMPADENTER ;
    VirtualButton::_mapStr2VBK["VBK_RCONTROL"]     = VBK_RCONTROL    ;
    VirtualButton::_mapStr2VBK["VBK_MUTE"]         = VBK_MUTE        ;
    VirtualButton::_mapStr2VBK["VBK_CALCULATOR"]   = VBK_CALCULATOR  ;
    VirtualButton::_mapStr2VBK["VBK_PLAYPAUSE"]    = VBK_PLAYPAUSE   ;
    VirtualButton::_mapStr2VBK["VBK_MEDIASTOP"]    = VBK_MEDIASTOP   ;
    VirtualButton::_mapStr2VBK["VBK_VOLUMEDOWN"]   = VBK_VOLUMEDOWN  ;
    VirtualButton::_mapStr2VBK["VBK_VOLUMEUP"]     = VBK_VOLUMEUP    ;
    VirtualButton::_mapStr2VBK["VBK_WEBHOME"]      = VBK_WEBHOME     ;
    VirtualButton::_mapStr2VBK["VBK_NUMPADCOMMA"]  = VBK_NUMPADCOMMA ;
    VirtualButton::_mapStr2VBK["VBK_DIVIDE"]       = VBK_DIVIDE      ;
    VirtualButton::_mapStr2VBK["VBK_SYSRQ"]        = VBK_SYSRQ       ;
    VirtualButton::_mapStr2VBK["VBK_RMENU"]        = VBK_RMENU       ;
    VirtualButton::_mapStr2VBK["VBK_PAUSE"]        = VBK_PAUSE       ;
    VirtualButton::_mapStr2VBK["VBK_HOME"]         = VBK_HOME        ;
    VirtualButton::_mapStr2VBK["VBK_UP"]           = VBK_UP          ;
    VirtualButton::_mapStr2VBK["VBK_PRIOR"]        = VBK_PRIOR       ;
    VirtualButton::_mapStr2VBK["VBK_LEFT"]         = VBK_LEFT        ;
    VirtualButton::_mapStr2VBK["VBK_RIGHT"]        = VBK_RIGHT       ;
    VirtualButton::_mapStr2VBK["VBK_END"]          = VBK_END         ;
    VirtualButton::_mapStr2VBK["VBK_DOWN"]         = VBK_DOWN        ;
    VirtualButton::_mapStr2VBK["VBK_NEXT"]         = VBK_NEXT        ;
    VirtualButton::_mapStr2VBK["VBK_INSERT"]       = VBK_INSERT      ;
    VirtualButton::_mapStr2VBK["VBK_DELETE"]       = VBK_DELETE      ;
    VirtualButton::_mapStr2VBK["VBK_LWIN"]         = VBK_LWIN        ;
    VirtualButton::_mapStr2VBK["VBK_RWIN"]         = VBK_RWIN        ;
    VirtualButton::_mapStr2VBK["VBK_APPS"]         = VBK_APPS        ;
    VirtualButton::_mapStr2VBK["VBK_POWER"]        = VBK_POWER       ;
    VirtualButton::_mapStr2VBK["VBK_SLEEP"]        = VBK_SLEEP       ;
    VirtualButton::_mapStr2VBK["VBK_WAKE"]         = VBK_WAKE        ;
    VirtualButton::_mapStr2VBK["VBK_WEBSEARCH"]    = VBK_WEBSEARCH   ;
    VirtualButton::_mapStr2VBK["VBK_WEBFAVORITES"] = VBK_WEBFAVORITES;
    VirtualButton::_mapStr2VBK["VBK_WEBREFRESH"]   = VBK_WEBREFRESH  ;
    VirtualButton::_mapStr2VBK["VBK_WEBSTOP"]      = VBK_WEBSTOP     ;
    VirtualButton::_mapStr2VBK["VBK_WEBFORWARD"]   = VBK_WEBFORWARD  ;
    VirtualButton::_mapStr2VBK["VBK_WEBBACK"]      = VBK_WEBBACK     ;
    VirtualButton::_mapStr2VBK["VBK_MYCOMPUTER"]   = VBK_MYCOMPUTER  ;
    VirtualButton::_mapStr2VBK["VBK_MAIL"]         = VBK_MAIL        ;
    VirtualButton::_mapStr2VBK["VBK_MEDIASELECT"]  = VBK_MEDIASELECT ;

    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_01"]   = VBJ_BUTTON_01  ;
    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_02"]   = VBJ_BUTTON_02  ;
    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_03"]   = VBJ_BUTTON_03  ;
    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_04"]   = VBJ_BUTTON_04  ;
    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_05"]   = VBJ_BUTTON_05  ;
    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_06"]   = VBJ_BUTTON_06  ;
    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_07"]   = VBJ_BUTTON_07  ;
    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_08"]   = VBJ_BUTTON_08  ;
    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_09"]   = VBJ_BUTTON_09  ;
    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_10"]   = VBJ_BUTTON_10  ;
    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_11"]   = VBJ_BUTTON_11  ;
    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_12"]   = VBJ_BUTTON_12  ;
    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_13"]   = VBJ_BUTTON_13  ;
    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_14"]   = VBJ_BUTTON_14  ;
    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_15"]   = VBJ_BUTTON_15  ;
    VirtualButton::_mapStr2VBJ["VBJ_BUTTON_15"]   = VBJ_BUTTON_16  ;
    VirtualButton::_mapStr2VBJ["VBJ_X_POS_MINUS"] = VBJ_X_POS_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_X_POS_PLUS"]  = VBJ_X_POS_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_Y_POS_MINUS"] = VBJ_Y_POS_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_Y_POS_PLUS"]  = VBJ_Y_POS_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_Z_POS_MINUS"] = VBJ_Z_POS_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_Z_POS_PLUS"]  = VBJ_Z_POS_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_X_ROT_MINUS"] = VBJ_X_ROT_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_X_ROT_PLUS"]  = VBJ_X_ROT_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_Y_ROT_MINUS"] = VBJ_Y_ROT_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_Y_ROT_PLUS"]  = VBJ_Y_ROT_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_Z_ROT_MINUS"] = VBJ_Z_ROT_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_Z_ROT_PLUS"]  = VBJ_Z_ROT_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_POV_UP"]      = VBJ_POV_UP     ;
    VirtualButton::_mapStr2VBJ["VBJ_POV_DOWN"]    = VBJ_POV_DOWN   ;
    VirtualButton::_mapStr2VBJ["VBJ_POV_LEFT"]    = VBJ_POV_LEFT   ;
    VirtualButton::_mapStr2VBJ["VBJ_POV_RIGHT"]   = VBJ_POV_RIGHT  ;

    VirtualButton::_mapVBK2Str[VBK_ESCAPE      ] = "VBK_ESCAPE";
    VirtualButton::_mapVBK2Str[VBK_1           ] = "VBK_1";
    VirtualButton::_mapVBK2Str[VBK_2           ] = "VBK_2";
    VirtualButton::_mapVBK2Str[VBK_3           ] = "VBK_3";
    VirtualButton::_mapVBK2Str[VBK_4           ] = "VBK_4";
    VirtualButton::_mapVBK2Str[VBK_5           ] = "VBK_5";
    VirtualButton::_mapVBK2Str[VBK_6           ] = "VBK_6";
    VirtualButton::_mapVBK2Str[VBK_7           ] = "VBK_7";
    VirtualButton::_mapVBK2Str[VBK_8           ] = "VBK_8";
    VirtualButton::_mapVBK2Str[VBK_9           ] = "VBK_9";
    VirtualButton::_mapVBK2Str[VBK_0           ] = "VBK_0";
    VirtualButton::_mapVBK2Str[VBK_MINUS       ] = "VBK_MINUS";
    VirtualButton::_mapVBK2Str[VBK_EQUALS      ] = "VBK_EQUALS";
    VirtualButton::_mapVBK2Str[VBK_BACK        ] = "VBK_BACK";
    VirtualButton::_mapVBK2Str[VBK_TAB         ] = "VBK_TAB";
    VirtualButton::_mapVBK2Str[VBK_Q           ] = "VBK_Q";
    VirtualButton::_mapVBK2Str[VBK_W           ] = "VBK_W";
    VirtualButton::_mapVBK2Str[VBK_E           ] = "VBK_E";
    VirtualButton::_mapVBK2Str[VBK_R           ] = "VBK_R";
    VirtualButton::_mapVBK2Str[VBK_T           ] = "VBK_T";
    VirtualButton::_mapVBK2Str[VBK_Y           ] = "VBK_Y";
    VirtualButton::_mapVBK2Str[VBK_U           ] = "VBK_U";
    VirtualButton::_mapVBK2Str[VBK_I           ] = "VBK_I";
    VirtualButton::_mapVBK2Str[VBK_O           ] = "VBK_O";
    VirtualButton::_mapVBK2Str[VBK_P           ] = "VBK_P";
    VirtualButton::_mapVBK2Str[VBK_LBRACKET    ] = "VBK_LBRACKET";
    VirtualButton::_mapVBK2Str[VBK_RBRACKET    ] = "VBK_RBRACKET";
    VirtualButton::_mapVBK2Str[VBK_RETURN      ] = "VBK_RETURN";
    VirtualButton::_mapVBK2Str[VBK_LCONTROL    ] = "VBK_LCONTROL";
    VirtualButton::_mapVBK2Str[VBK_A           ] = "VBK_A";
    VirtualButton::_mapVBK2Str[VBK_S           ] = "VBK_S";
    VirtualButton::_mapVBK2Str[VBK_D           ] = "VBK_D";
    VirtualButton::_mapVBK2Str[VBK_F           ] = "VBK_F";
    VirtualButton::_mapVBK2Str[VBK_G           ] = "VBK_G";
    VirtualButton::_mapVBK2Str[VBK_H           ] = "VBK_H";
    VirtualButton::_mapVBK2Str[VBK_J           ] = "VBK_J";
    VirtualButton::_mapVBK2Str[VBK_K           ] = "VBK_K";
    VirtualButton::_mapVBK2Str[VBK_L           ] = "VBK_L";
    VirtualButton::_mapVBK2Str[VBK_SEMICOLON   ] = "VBK_SEMICOLON";
    VirtualButton::_mapVBK2Str[VBK_APOSTROPHE  ] = "VBK_APOSTROPHE";
    VirtualButton::_mapVBK2Str[VBK_GRAVE       ] = "VBK_GRAVE";
    VirtualButton::_mapVBK2Str[VBK_LSHIFT      ] = "VBK_LSHIFT";
    VirtualButton::_mapVBK2Str[VBK_BACKSLASH   ] = "VBK_BACKSLASH";
    VirtualButton::_mapVBK2Str[VBK_Z           ] = "VBK_Z";
    VirtualButton::_mapVBK2Str[VBK_X           ] = "VBK_X";
    VirtualButton::_mapVBK2Str[VBK_C           ] = "VBK_C";
    VirtualButton::_mapVBK2Str[VBK_V           ] = "VBK_V";
    VirtualButton::_mapVBK2Str[VBK_B           ] = "VBK_B";
    VirtualButton::_mapVBK2Str[VBK_N           ] = "VBK_N";
    VirtualButton::_mapVBK2Str[VBK_M           ] = "VBK_M";
    VirtualButton::_mapVBK2Str[VBK_COMMA       ] = "VBK_COMMA";
    VirtualButton::_mapVBK2Str[VBK_PERIOD      ] = "VBK_PERIOD";
    VirtualButton::_mapVBK2Str[VBK_SLASH       ] = "VBK_SLASH";
    VirtualButton::_mapVBK2Str[VBK_RSHIFT      ] = "VBK_RSHIFT";
    VirtualButton::_mapVBK2Str[VBK_MULTIPLY    ] = "VBK_MULTIPLY";
    VirtualButton::_mapVBK2Str[VBK_LMENU       ] = "VBK_LMENU";
    VirtualButton::_mapVBK2Str[VBK_SPACE       ] = "VBK_SPACE";
    VirtualButton::_mapVBK2Str[VBK_CAPITAL     ] = "VBK_CAPITAL";
    VirtualButton::_mapVBK2Str[VBK_F1          ] = "VBK_F1";
    VirtualButton::_mapVBK2Str[VBK_F2          ] = "VBK_F2";
    VirtualButton::_mapVBK2Str[VBK_F3          ] = "VBK_F3";
    VirtualButton::_mapVBK2Str[VBK_F4          ] = "VBK_F4";
    VirtualButton::_mapVBK2Str[VBK_F5          ] = "VBK_F5";
    VirtualButton::_mapVBK2Str[VBK_F6          ] = "VBK_F6";
    VirtualButton::_mapVBK2Str[VBK_F7          ] = "VBK_F7";
    VirtualButton::_mapVBK2Str[VBK_F8          ] = "VBK_F8";
    VirtualButton::_mapVBK2Str[VBK_F9          ] = "VBK_F9";
    VirtualButton::_mapVBK2Str[VBK_F10         ] = "VBK_F10";
    VirtualButton::_mapVBK2Str[VBK_NUMLOCK     ] = "VBK_NUMLOCK";
    VirtualButton::_mapVBK2Str[VBK_SCROLL      ] = "VBK_SCROLL";
    VirtualButton::_mapVBK2Str[VBK_NUMPAD7     ] = "VBK_NUMPAD7";
    VirtualButton::_mapVBK2Str[VBK_NUMPAD8     ] = "VBK_NUMPAD8";
    VirtualButton::_mapVBK2Str[VBK_NUMPAD9     ] = "VBK_NUMPAD9";
    VirtualButton::_mapVBK2Str[VBK_SUBTRACT    ] = "VBK_SUBTRACT";
    VirtualButton::_mapVBK2Str[VBK_NUMPAD4     ] = "VBK_NUMPAD4";
    VirtualButton::_mapVBK2Str[VBK_NUMPAD5     ] = "VBK_NUMPAD5";
    VirtualButton::_mapVBK2Str[VBK_NUMPAD6     ] = "VBK_NUMPAD6";
    VirtualButton::_mapVBK2Str[VBK_ADD         ] = "VBK_ADD";
    VirtualButton::_mapVBK2Str[VBK_NUMPAD1     ] = "VBK_NUMPAD1";
    VirtualButton::_mapVBK2Str[VBK_NUMPAD2     ] = "VBK_NUMPAD2";
    VirtualButton::_mapVBK2Str[VBK_NUMPAD3     ] = "VBK_NUMPAD3";
    VirtualButton::_mapVBK2Str[VBK_NUMPAD0     ] = "VBK_NUMPAD0";
    VirtualButton::_mapVBK2Str[VBK_DECIMAL     ] = "VBK_DECIMAL";
    VirtualButton::_mapVBK2Str[VBK_OEM_102     ] = "VBK_OEM_102";
    VirtualButton::_mapVBK2Str[VBK_F11         ] = "VBK_F11";
    VirtualButton::_mapVBK2Str[VBK_F12         ] = "VBK_F12";
    VirtualButton::_mapVBK2Str[VBK_F13         ] = "VBK_F13";
    VirtualButton::_mapVBK2Str[VBK_F14         ] = "VBK_F14";
    VirtualButton::_mapVBK2Str[VBK_F15         ] = "VBK_F15";
    VirtualButton::_mapVBK2Str[VBK_KANA        ] = "VBK_KANA";
    VirtualButton::_mapVBK2Str[VBK_ABNT_C1     ] = "VBK_ABNT_C1";
    VirtualButton::_mapVBK2Str[VBK_CONVERT     ] = "VBK_CONVERT";
    VirtualButton::_mapVBK2Str[VBK_NOCONVERT   ] = "VBK_NOCONVERT";
    VirtualButton::_mapVBK2Str[VBK_YEN         ] = "VBK_YEN";
    VirtualButton::_mapVBK2Str[VBK_ABNT_C2     ] = "VBK_ABNT_C2";
    VirtualButton::_mapVBK2Str[VBK_NUMPADEQUALS] = "VBK_NUMPADEQUALS";
    VirtualButton::_mapVBK2Str[VBK_PREVTRACK   ] = "VBK_PREVTRACK";
    VirtualButton::_mapVBK2Str[VBK_AT          ] = "VBK_AT";
    VirtualButton::_mapVBK2Str[VBK_COLON       ] = "VBK_COLON";
    VirtualButton::_mapVBK2Str[VBK_UNDERLINE   ] = "VBK_UNDERLINE";
    VirtualButton::_mapVBK2Str[VBK_KANJI       ] = "VBK_KANJI";
    VirtualButton::_mapVBK2Str[VBK_STOP        ] = "VBK_STOP";
    VirtualButton::_mapVBK2Str[VBK_AX          ] = "VBK_AX";
    VirtualButton::_mapVBK2Str[VBK_UNLABELED   ] = "VBK_UNLABELED";
    VirtualButton::_mapVBK2Str[VBK_NEXTTRACK   ] = "VBK_NEXTTRACK";
    VirtualButton::_mapVBK2Str[VBK_NUMPADENTER ] = "VBK_NUMPADENTER";
    VirtualButton::_mapVBK2Str[VBK_RCONTROL    ] = "VBK_RCONTROL";
    VirtualButton::_mapVBK2Str[VBK_MUTE        ] = "VBK_MUTE";
    VirtualButton::_mapVBK2Str[VBK_CALCULATOR  ] = "VBK_CALCULATOR";
    VirtualButton::_mapVBK2Str[VBK_PLAYPAUSE   ] = "VBK_PLAYPAUSE";
    VirtualButton::_mapVBK2Str[VBK_MEDIASTOP   ] = "VBK_MEDIASTOP";
    VirtualButton::_mapVBK2Str[VBK_VOLUMEDOWN  ] = "VBK_VOLUMEDOWN";
    VirtualButton::_mapVBK2Str[VBK_VOLUMEUP    ] = "VBK_VOLUMEUP";
    VirtualButton::_mapVBK2Str[VBK_WEBHOME     ] = "VBK_WEBHOME";
    VirtualButton::_mapVBK2Str[VBK_NUMPADCOMMA ] = "VBK_NUMPADCOMMA";
    VirtualButton::_mapVBK2Str[VBK_DIVIDE      ] = "VBK_DIVIDE";
    VirtualButton::_mapVBK2Str[VBK_SYSRQ       ] = "VBK_SYSRQ";
    VirtualButton::_mapVBK2Str[VBK_RMENU       ] = "VBK_RMENU";
    VirtualButton::_mapVBK2Str[VBK_PAUSE       ] = "VBK_PAUSE";
    VirtualButton::_mapVBK2Str[VBK_HOME        ] = "VBK_HOME";
    VirtualButton::_mapVBK2Str[VBK_UP          ] = "VBK_UP";
    VirtualButton::_mapVBK2Str[VBK_PRIOR       ] = "VBK_PRIOR";
    VirtualButton::_mapVBK2Str[VBK_LEFT        ] = "VBK_LEFT";
    VirtualButton::_mapVBK2Str[VBK_RIGHT       ] = "VBK_RIGHT";
    VirtualButton::_mapVBK2Str[VBK_END         ] = "VBK_END";
    VirtualButton::_mapVBK2Str[VBK_DOWN        ] = "VBK_DOWN";
    VirtualButton::_mapVBK2Str[VBK_NEXT        ] = "VBK_NEXT";
    VirtualButton::_mapVBK2Str[VBK_INSERT      ] = "VBK_INSERT";
    VirtualButton::_mapVBK2Str[VBK_DELETE      ] = "VBK_DELETE";
    VirtualButton::_mapVBK2Str[VBK_LWIN        ] = "VBK_LWIN";
    VirtualButton::_mapVBK2Str[VBK_RWIN        ] = "VBK_RWIN";
    VirtualButton::_mapVBK2Str[VBK_APPS        ] = "VBK_APPS";
    VirtualButton::_mapVBK2Str[VBK_POWER       ] = "VBK_POWER";
    VirtualButton::_mapVBK2Str[VBK_SLEEP       ] = "VBK_SLEEP";
    VirtualButton::_mapVBK2Str[VBK_WAKE        ] = "VBK_WAKE";
    VirtualButton::_mapVBK2Str[VBK_WEBSEARCH   ] = "VBK_WEBSEARCH";
    VirtualButton::_mapVBK2Str[VBK_WEBFAVORITES] = "VBK_WEBFAVORITES";
    VirtualButton::_mapVBK2Str[VBK_WEBREFRESH  ] = "VBK_WEBREFRESH";
    VirtualButton::_mapVBK2Str[VBK_WEBSTOP     ] = "VBK_WEBSTOP";
    VirtualButton::_mapVBK2Str[VBK_WEBFORWARD  ] = "VBK_WEBFORWARD";
    VirtualButton::_mapVBK2Str[VBK_WEBBACK     ] = "VBK_WEBBACK";
    VirtualButton::_mapVBK2Str[VBK_MYCOMPUTER  ] = "VBK_MYCOMPUTER";
    VirtualButton::_mapVBK2Str[VBK_MAIL        ] = "VBK_MAIL";
    VirtualButton::_mapVBK2Str[VBK_MEDIASELECT ] = "VBK_MEDIASELECT";

    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_01  ] = "VBJ_BUTTON_01";
    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_02  ] = "VBJ_BUTTON_02";
    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_03  ] = "VBJ_BUTTON_03";
    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_04  ] = "VBJ_BUTTON_04";
    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_05  ] = "VBJ_BUTTON_05";
    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_06  ] = "VBJ_BUTTON_06";
    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_07  ] = "VBJ_BUTTON_07";
    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_08  ] = "VBJ_BUTTON_08";
    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_09  ] = "VBJ_BUTTON_09";
    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_10  ] = "VBJ_BUTTON_10";
    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_11  ] = "VBJ_BUTTON_11";
    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_12  ] = "VBJ_BUTTON_12";
    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_13  ] = "VBJ_BUTTON_13";
    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_14  ] = "VBJ_BUTTON_14";
    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_15  ] = "VBJ_BUTTON_15";
    VirtualButton::_mapVBJ2Str[VBJ_BUTTON_16  ] = "VBJ_BUTTON_16";
    VirtualButton::_mapVBJ2Str[VBJ_X_POS_MINUS] = "VBJ_X_POS_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_X_POS_PLUS ] = "VBJ_X_POS_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_Y_POS_MINUS] = "VBJ_Y_POS_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_Y_POS_PLUS ] = "VBJ_Y_POS_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_Z_POS_MINUS] = "VBJ_Z_POS_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_Z_POS_PLUS ] = "VBJ_Z_POS_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_X_ROT_MINUS] = "VBJ_X_ROT_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_X_ROT_PLUS ] = "VBJ_X_ROT_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_Y_ROT_MINUS] = "VBJ_Y_ROT_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_Y_ROT_PLUS ] = "VBJ_Y_ROT_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_Z_ROT_MINUS] = "VBJ_Z_ROT_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_Z_ROT_PLUS ] = "VBJ_Z_ROT_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_POV_UP     ] = "VBJ_POV_UP";
    VirtualButton::_mapVBJ2Str[VBJ_POV_DOWN   ] = "VBJ_POV_DOWN";
    VirtualButton::_mapVBJ2Str[VBJ_POV_LEFT   ] = "VBJ_POV_LEFT";
    VirtualButton::_mapVBJ2Str[VBJ_POV_RIGHT  ] = "VBJ_POV_RIGHT";

    VirtualButton::_mapVBJ2Func[VBJ_X_POS_MINUS] = GgafDxCore::GgafDxInput::isBeingPressedJoyXAxisMinus;
    VirtualButton::_mapVBJ2Func[VBJ_X_POS_PLUS ] = GgafDxCore::GgafDxInput::isBeingPressedJoyXAxisPlus;
    VirtualButton::_mapVBJ2Func[VBJ_Y_POS_MINUS] = GgafDxCore::GgafDxInput::isBeingPressedJoyYAxisMinus;
    VirtualButton::_mapVBJ2Func[VBJ_Y_POS_PLUS ] = GgafDxCore::GgafDxInput::isBeingPressedJoyYAxisPlus;
    VirtualButton::_mapVBJ2Func[VBJ_Z_POS_MINUS] = GgafDxCore::GgafDxInput::isBeingPressedJoyZAxisMinus;
    VirtualButton::_mapVBJ2Func[VBJ_Z_POS_PLUS ] = GgafDxCore::GgafDxInput::isBeingPressedJoyZAxisPlus;
    VirtualButton::_mapVBJ2Func[VBJ_X_ROT_MINUS] = GgafDxCore::GgafDxInput::isBeingPressedJoyRxMinus;
    VirtualButton::_mapVBJ2Func[VBJ_X_ROT_PLUS ] = GgafDxCore::GgafDxInput::isBeingPressedJoyRxPlus;
    VirtualButton::_mapVBJ2Func[VBJ_Y_ROT_MINUS] = GgafDxCore::GgafDxInput::isBeingPressedJoyRyMinus;
    VirtualButton::_mapVBJ2Func[VBJ_Y_ROT_PLUS ] = GgafDxCore::GgafDxInput::isBeingPressedJoyRyPlus;
    VirtualButton::_mapVBJ2Func[VBJ_Z_ROT_MINUS] = GgafDxCore::GgafDxInput::isBeingPressedJoyRzMinus;
    VirtualButton::_mapVBJ2Func[VBJ_Z_ROT_PLUS ] = GgafDxCore::GgafDxInput::isBeingPressedJoyRzPlus;
    VirtualButton::_mapVBJ2Func[VBJ_POV_UP     ] = GgafDxCore::GgafDxInput::isBeingPressedPovUp;
    VirtualButton::_mapVBJ2Func[VBJ_POV_DOWN   ] = GgafDxCore::GgafDxInput::isBeingPressedPovDown;
    VirtualButton::_mapVBJ2Func[VBJ_POV_LEFT   ] = GgafDxCore::GgafDxInput::isBeingPressedPovLeft;
    VirtualButton::_mapVBJ2Func[VBJ_POV_RIGHT  ] = GgafDxCore::GgafDxInput::isBeingPressedPovRight;
    return true;
}

VirtualButton::VBRecord* VirtualButton::getPastVBRecord(frame prm_frame_ago) const {
    VirtualButton::VBRecord* pVBRecord_temp = _pVBRecord_active;
    for (frame i = 0; i < prm_frame_ago; i++) {
        pVBRecord_temp = pVBRecord_temp->_prev;
    }
    return pVBRecord_temp;
}

vb_sta VirtualButton::isAutoRepeat(vb_sta prm_VB, frame prm_begin_repeat, frame prm_while_repeat) {
    vb_sta sta = (_pVBRecord_active->_state & prm_VB);
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
            //キーイン時にまず成立
            return sta;
        } else if (_auto_repeat_counter[prm_VB] > prm_begin_repeat && _auto_repeat_counter[prm_VB] % prm_while_repeat == 0) {
            //オートリピート時成立(デフォルトでは、20フレーム後以降は5フレーム毎に成立)
            return sta;
        }
    }
    return false;
}

vb_sta VirtualButton::wasBeingPressed(vb_sta prm_VB, frame prm_frame_ago) const {
    VirtualButton::VBRecord* pVBRecord_temp = getPastVBRecord(prm_frame_ago);
    return (pVBRecord_temp->_state & prm_VB);
}

vb_sta VirtualButton::isNotBeingPressed(vb_sta prm_VB) const {
    if (isBeingPressed(prm_VB)) {
        return false;
    } else {
        return true;
    }
}

vb_sta VirtualButton::wasNotBeingPressed(vb_sta prm_VB, frame prm_frame_ago) const {
    if (wasBeingPressed(prm_VB, prm_frame_ago)) {
        return false;
    } else {
        return true;
    }
}

vb_sta VirtualButton::isDoublePushedDown(vb_sta prm_VB, frame prm_frame_push, frame prm_frame_delay) const {
    //-------oooo-----o
    //       <--><--->
    //         |    `-- prm_frame_delay
    //         `-- prm_frame_push
    //過去に遡りながら検証
    VirtualButton::VBRecord* pVBRecord;
    pVBRecord = _pVBRecord_active;
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

vb_sta VirtualButton::arePushedDownAtOnce(vb_sta prm_aVB[], int prm_num_button) const {

    //現在は全て押されていなければならない
    for (int i = 0; i < prm_num_button; i++) {
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
    bool prev1Flg, prev2Flg, prev3Flg;
    for (int i = 0; i < prm_num_button; i++) {
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
    for (int i = 0; i < prm_num_button; i++) {
        if (wasNotBeingPressed(prm_aVB[i], 1)) {
            return true;
        }
    }
    return false;
}

vb_sta VirtualButton::wasPushedDown(vb_sta prm_VB, frame prm_frame_ago) const {
    if (wasBeingPressed(prm_VB, prm_frame_ago) && wasNotBeingPressed(prm_VB, prm_frame_ago + 1)) {
        return true;
    } else {
        return false;
    }
}

vb_sta VirtualButton::isReleasedUp(vb_sta prm_VB) const {
    if ((_pVBRecord_active->_prev->_state & prm_VB) && !(_pVBRecord_active->_state & prm_VB)) {
        return true;
    } else {
        return false;
    }
}

vb_sta VirtualButton::isPushedUp(vb_sta prm_VB, frame prm_frame_push) const {
    //←過去      現在
    //            ↓
    //---------ooo-
    //       <--->
    //         |
    //         `-- prm_frame_push

    //過去に遡りながら検証
    VirtualButton::VBRecord* pVBRecord;
    pVBRecord = _pVBRecord_active;
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


vb_sta VirtualButton::wasReleasedUp(vb_sta prm_VB, frame prm_frame_ago) const {
    if (wasNotBeingPressed(prm_VB, prm_frame_ago) && wasBeingPressed(prm_VB, prm_frame_ago + 1)) {
        return true;
    } else {
        return false;
    }
}


bool VirtualButton::isScrewPushDown(vb_sta prm_VB, frame prm_frame_delay) const {
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


//vb_sta VirtualButton::getPushedDownStickWith(vb_sta prm_VB) {
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

vb_sta VirtualButton::getState() const {
    return _pVBRecord_active->_state;
}

void VirtualButton::update() {
#ifdef MY_DEBUG
    if (_pVBRecord_active == nullptr) {
        throwGgafCriticalException("VirtualButton::update() 利用前に一度 init() を呼び出して下さい。");
    }
#endif
    GgafDxInput::updateKeyboardState();
    GgafDxInput::updateJoystickState();
    GgafDxInput::updateMouseState();

    if (_is_replaying && _was_replay_done == false) {
        //リプレイモード時
        _pVBRecord_active = _pVBRecord_active->_next;
        _pVBRecord_active->_state = _pRpy->read();
        if (_pVBRecord_active->_state == 0) {
            _was_replay_done = true;
        }
        return;

    } else {

        //通常操作時
        _pVBRecord_active = _pVBRecord_active->_next;

        vb_sta state = 0;
        const KEYBOARDMAP& kmap = _keyboardmap;
        const JOYSTICKMAP& jmap = _joystickmap;

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
        state |= (VB_PAUSE    * GgafDxInput::isBeingPressedKey(kmap.PAUSE));
        state |= (VB_UP       * GgafDxInput::isBeingPressedKey(kmap.UP));
        state |= (VB_DOWN     * GgafDxInput::isBeingPressedKey(kmap.DOWN));
        state |= (VB_LEFT     * GgafDxInput::isBeingPressedKey(kmap.LEFT));
        state |= (VB_RIGHT    * GgafDxInput::isBeingPressedKey(kmap.RIGHT));
        state |= (VB_S1_UP    * GgafDxInput::isBeingPressedKey(kmap.S1_UP));
        state |= (VB_S1_DOWN  * GgafDxInput::isBeingPressedKey(kmap.S1_DOWN));
        state |= (VB_S1_LEFT  * GgafDxInput::isBeingPressedKey(kmap.S1_LEFT));
        state |= (VB_S1_RIGHT * GgafDxInput::isBeingPressedKey(kmap.S1_RIGHT));
        state |= (VB_S2_UP    * GgafDxInput::isBeingPressedKey(kmap.S2_UP));
        state |= (VB_S2_DOWN  * GgafDxInput::isBeingPressedKey(kmap.S2_DOWN));
        state |= (VB_S2_LEFT  * GgafDxInput::isBeingPressedKey(kmap.S2_LEFT));
        state |= (VB_S2_RIGHT * GgafDxInput::isBeingPressedKey(kmap.S2_RIGHT));
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
            state |= (VB_PAUSE    * VirtualButton::isBeingPressedVirtualJoyButton(jmap.PAUSE));
            state |= (VB_UP       * VirtualButton::isBeingPressedVirtualJoyButton(jmap.UP));
            state |= (VB_DOWN     * VirtualButton::isBeingPressedVirtualJoyButton(jmap.DOWN));
            state |= (VB_LEFT     * VirtualButton::isBeingPressedVirtualJoyButton(jmap.LEFT));
            state |= (VB_RIGHT    * VirtualButton::isBeingPressedVirtualJoyButton(jmap.RIGHT));
            state |= (VB_S1_UP    * VirtualButton::isBeingPressedVirtualJoyButton(jmap.S1_UP));
            state |= (VB_S1_DOWN  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.S1_DOWN));
            state |= (VB_S1_LEFT  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.S1_LEFT));
            state |= (VB_S1_RIGHT * VirtualButton::isBeingPressedVirtualJoyButton(jmap.S1_RIGHT));
            state |= (VB_S2_UP    * VirtualButton::isBeingPressedVirtualJoyButton(jmap.S2_UP));
            state |= (VB_S2_DOWN  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.S2_DOWN));
            state |= (VB_S2_LEFT  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.S2_LEFT));
            state |= (VB_S2_RIGHT * VirtualButton::isBeingPressedVirtualJoyButton(jmap.S2_RIGHT));
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
            state |= (VB_UI_CANCEL  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.UI_CANCEL));
            //state |= (VB_UI_DEBUG * VirtualButton::isBeingPressedVirtualJoyButton(jmap.UI_DEBUG)); //JoyStickにはDEBUGボタンは無い仕様
        }
        _pVBRecord_active->_state = state;
    }
    _pRpy->write(_pVBRecord_active->_state); //リプレイ情報記録
}


void VirtualButton::clear() {
    VirtualButton::VBRecord* pVBRecord = _pVBRecord_active;
    for (int i = 0; i < VB_MAP_BUFFER; i++) {
        pVBRecord->_state = 0;
        pVBRecord = pVBRecord->_next;
    }
}


 bool VirtualButton::isBeingPressedVirtualJoyButton(int prm_VBJ) {
    if (0 <= prm_VBJ && prm_VBJ <= 0x0F) {
        return GgafDxCore::GgafDxInput::isBeingPressedJoyButton(prm_VBJ);
    } else {
        if ( ( 0x80 <= prm_VBJ && prm_VBJ <= 0x8B ) ||
             ( 0x90 <= prm_VBJ && prm_VBJ <= 0x93 )   )
        {
            //XYZ軸上下か、XYZ軸回転＋ーか、POVの方向の場合
            return (VirtualButton::_mapVBJ2Func[prm_VBJ])();
        } else {
            return -1;
        }
    }
}

int VirtualButton::getPushedDownVirtualJoyButton() {
    int VBJ_pushed = GgafDxInput::getPushedDownJoyRgbButton();
    if (VBJ_pushed == -1) {
        if (GgafDxInput::isBeingPressedJoyXAxisMinus()) {
            return VBJ_X_POS_MINUS;
        } else if (GgafDxInput::isBeingPressedJoyXAxisPlus()) {
            return VBJ_X_POS_PLUS;
        } else if (GgafDxInput::isBeingPressedJoyYAxisMinus()) {
            return VBJ_Y_POS_MINUS;
        } else if (GgafDxInput::isBeingPressedJoyYAxisPlus()) {
            return VBJ_Y_POS_PLUS;
        } else if (GgafDxInput::isBeingPressedJoyZAxisMinus()) {
            return VBJ_Z_POS_MINUS;
        } else if (GgafDxInput::isBeingPressedJoyZAxisPlus()) {
            return VBJ_Z_POS_PLUS;
        } else if (GgafDxInput::isBeingPressedJoyRxMinus()) {
            return VBJ_X_ROT_MINUS;
        } else if (GgafDxInput::isBeingPressedJoyRxPlus()) {
            return VBJ_X_ROT_PLUS;
        } else if (GgafDxInput::isBeingPressedJoyRyMinus()) {
            return VBJ_Y_ROT_MINUS;
        } else if (GgafDxInput::isBeingPressedJoyRyPlus()) {
            return VBJ_Y_ROT_PLUS;
        } else if (GgafDxInput::isBeingPressedJoyRzMinus()) {
            return VBJ_Z_ROT_MINUS;
        } else if (GgafDxInput::isBeingPressedJoyRzPlus()) {
            return VBJ_Z_ROT_PLUS;
        } else if (GgafDxInput::isBeingPressedPovUp()) {
            return VBJ_POV_UP;
        } else if (GgafDxInput::isBeingPressedPovDown()) {
            return VBJ_POV_DOWN;
        } else if (GgafDxInput::isBeingPressedPovLeft()) {
            return VBJ_POV_LEFT;
        } else if (GgafDxInput::isBeingPressedPovRight()) {
            return VBJ_POV_RIGHT;
        } else {
            return -1;
        }
     } else {
         return VBJ_pushed;
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

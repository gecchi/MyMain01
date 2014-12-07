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

//組み込み標準キーボード割り当て
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
                              0xFF,       // BUTTON11
                              0xFF,       // BUTTON12
                              0xFF,       // BUTTON13
                              0xFF,       // BUTTON14
                              0xFF,       // BUTTON15
                              0xFF,       // BUTTON16
                              DIK_ESCAPE, // PAUSE
                              DIK_UP,     // UP
                              DIK_DOWN,   // DOWN
                              DIK_LEFT,   // LEFT
                              DIK_RIGHT,  // RIGHT
                              DIK_UP,     // UI_UP
                              DIK_DOWN,   // UI_DOWN
                              DIK_LEFT,   // UI_LEFT
                              DIK_RIGHT,  // UI_RIGHT
                              0xFF,       // UI_S1_UP
                              0xFF,       // UI_S1_DOWN
                              0xFF,       // UI_S1_LEFT
                              0xFF,       // UI_S1_RIGHT
                              DIK_RETURN, // UI_EXECUTE
                              DIK_ESCAPE, // UI_CANCEL
                              DIK_Q       // UI_DEBUG
                           };

VirtualButton::JOYSTICKMAP VirtualButton::_joystickmap = {
                              VBJ_BUTTON_00,   // BUTTON1
                              VBJ_BUTTON_01,   // BUTTON2
                              VBJ_BUTTON_02,   // BUTTON3
                              VBJ_BUTTON_03,   // BUTTON4
                              VBJ_BUTTON_04,   // BUTTON5
                              VBJ_BUTTON_05,   // BUTTON6
                              VBJ_BUTTON_06,   // BUTTON7
                              VBJ_BUTTON_07,   // BUTTON8
                              VBJ_BUTTON_08,   // BUTTON9
                              VBJ_BUTTON_09,   // BUTTON10
                              VBJ_BUTTON_10,   // BUTTON11
                              VBJ_BUTTON_11,   // BUTTON12
                              VBJ_BUTTON_12,   // BUTTON13
                              VBJ_BUTTON_13,   // BUTTON14
                              VBJ_BUTTON_14,   // BUTTON15
                              VBJ_BUTTON_15,   // BUTTON16
                              VBJ_BUTTON_07,   // PAUSE
                              VBJ_Y_POS_MINUS, // UP
                              VBJ_Y_POS_PLUS , // DOWN
                              VBJ_X_POS_MINUS, // LEFT
                              VBJ_X_POS_PLUS , // RIGHT
                              0xFF, // S1_UP
                              0xFF, // S1_DOWN
                              0xFF, // S1_LEFT
                              0xFF, // S1_RIGHT
                              VBJ_Y_POS_MINUS, // UI_UP
                              VBJ_Y_POS_PLUS , // UI_DOWN
                              VBJ_X_POS_MINUS, // UI_LEFT
                              VBJ_X_POS_PLUS , // UI_RIGHT
                              VBJ_BUTTON_00, // UI_EXECUTE
                              VBJ_BUTTON_01  // UI_CANCEL
                              //, 0xFF  // UI_DEBUG
                           };

VirtualButton::VirtualButton(const char* prm_replay_file) : GgafObject() {
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
    if (!VirtualButton::_is_init) {
        init();//初回new時だけ実行。
        VirtualButton::_is_init = true;
    }
    _was_replay_done = false;
    _with_pov = true;
}

void VirtualButton::init() {
    _mapStr2Dik["DIK_ESCAPE"]       = DIK_ESCAPE      ;
    _mapStr2Dik["DIK_1"]            = DIK_1           ;
    _mapStr2Dik["DIK_2"]            = DIK_2           ;
    _mapStr2Dik["DIK_3"]            = DIK_3           ;
    _mapStr2Dik["DIK_4"]            = DIK_4           ;
    _mapStr2Dik["DIK_5"]            = DIK_5           ;
    _mapStr2Dik["DIK_6"]            = DIK_6           ;
    _mapStr2Dik["DIK_7"]            = DIK_7           ;
    _mapStr2Dik["DIK_8"]            = DIK_8           ;
    _mapStr2Dik["DIK_9"]            = DIK_9           ;
    _mapStr2Dik["DIK_0"]            = DIK_0           ;
    _mapStr2Dik["DIK_MINUS"]        = DIK_MINUS       ;
    _mapStr2Dik["DIK_EQUALS"]       = DIK_EQUALS      ;
    _mapStr2Dik["DIK_BACK"]         = DIK_BACK        ;
    _mapStr2Dik["DIK_TAB"]          = DIK_TAB         ;
    _mapStr2Dik["DIK_Q"]            = DIK_Q           ;
    _mapStr2Dik["DIK_W"]            = DIK_W           ;
    _mapStr2Dik["DIK_E"]            = DIK_E           ;
    _mapStr2Dik["DIK_R"]            = DIK_R           ;
    _mapStr2Dik["DIK_T"]            = DIK_T           ;
    _mapStr2Dik["DIK_Y"]            = DIK_Y           ;
    _mapStr2Dik["DIK_U"]            = DIK_U           ;
    _mapStr2Dik["DIK_I"]            = DIK_I           ;
    _mapStr2Dik["DIK_O"]            = DIK_O           ;
    _mapStr2Dik["DIK_P"]            = DIK_P           ;
    _mapStr2Dik["DIK_LBRACKET"]     = DIK_LBRACKET    ;
    _mapStr2Dik["DIK_RBRACKET"]     = DIK_RBRACKET    ;
    _mapStr2Dik["DIK_RETURN"]       = DIK_RETURN      ;
    _mapStr2Dik["DIK_LCONTROL"]     = DIK_LCONTROL    ;
    _mapStr2Dik["DIK_A"]            = DIK_A           ;
    _mapStr2Dik["DIK_S"]            = DIK_S           ;
    _mapStr2Dik["DIK_D"]            = DIK_D           ;
    _mapStr2Dik["DIK_F"]            = DIK_F           ;
    _mapStr2Dik["DIK_G"]            = DIK_G           ;
    _mapStr2Dik["DIK_H"]            = DIK_H           ;
    _mapStr2Dik["DIK_J"]            = DIK_J           ;
    _mapStr2Dik["DIK_K"]            = DIK_K           ;
    _mapStr2Dik["DIK_L"]            = DIK_L           ;
    _mapStr2Dik["DIK_SEMICOLON"]    = DIK_SEMICOLON   ;
    _mapStr2Dik["DIK_APOSTROPHE"]   = DIK_APOSTROPHE  ;
    _mapStr2Dik["DIK_GRAVE"]        = DIK_GRAVE       ;
    _mapStr2Dik["DIK_LSHIFT"]       = DIK_LSHIFT      ;
    _mapStr2Dik["DIK_BACKSLASH"]    = DIK_BACKSLASH   ;
    _mapStr2Dik["DIK_Z"]            = DIK_Z           ;
    _mapStr2Dik["DIK_X"]            = DIK_X           ;
    _mapStr2Dik["DIK_C"]            = DIK_C           ;
    _mapStr2Dik["DIK_V"]            = DIK_V           ;
    _mapStr2Dik["DIK_B"]            = DIK_B           ;
    _mapStr2Dik["DIK_N"]            = DIK_N           ;
    _mapStr2Dik["DIK_M"]            = DIK_M           ;
    _mapStr2Dik["DIK_COMMA"]        = DIK_COMMA       ;
    _mapStr2Dik["DIK_PERIOD"]       = DIK_PERIOD      ;
    _mapStr2Dik["DIK_SLASH"]        = DIK_SLASH       ;
    _mapStr2Dik["DIK_RSHIFT"]       = DIK_RSHIFT      ;
    _mapStr2Dik["DIK_MULTIPLY"]     = DIK_MULTIPLY    ;
    _mapStr2Dik["DIK_LMENU"]        = DIK_LMENU       ;
    _mapStr2Dik["DIK_SPACE"]        = DIK_SPACE       ;
    _mapStr2Dik["DIK_CAPITAL"]      = DIK_CAPITAL     ;
    _mapStr2Dik["DIK_F1"]           = DIK_F1          ;
    _mapStr2Dik["DIK_F2"]           = DIK_F2          ;
    _mapStr2Dik["DIK_F3"]           = DIK_F3          ;
    _mapStr2Dik["DIK_F4"]           = DIK_F4          ;
    _mapStr2Dik["DIK_F5"]           = DIK_F5          ;
    _mapStr2Dik["DIK_F6"]           = DIK_F6          ;
    _mapStr2Dik["DIK_F7"]           = DIK_F7          ;
    _mapStr2Dik["DIK_F8"]           = DIK_F8          ;
    _mapStr2Dik["DIK_F9"]           = DIK_F9          ;
    _mapStr2Dik["DIK_F10"]          = DIK_F10         ;
    _mapStr2Dik["DIK_NUMLOCK"]      = DIK_NUMLOCK     ;
    _mapStr2Dik["DIK_SCROLL"]       = DIK_SCROLL      ;
    _mapStr2Dik["DIK_NUMPAD7"]      = DIK_NUMPAD7     ;
    _mapStr2Dik["DIK_NUMPAD8"]      = DIK_NUMPAD8     ;
    _mapStr2Dik["DIK_NUMPAD9"]      = DIK_NUMPAD9     ;
    _mapStr2Dik["DIK_SUBTRACT"]     = DIK_SUBTRACT    ;
    _mapStr2Dik["DIK_NUMPAD4"]      = DIK_NUMPAD4     ;
    _mapStr2Dik["DIK_NUMPAD5"]      = DIK_NUMPAD5     ;
    _mapStr2Dik["DIK_NUMPAD6"]      = DIK_NUMPAD6     ;
    _mapStr2Dik["DIK_ADD"]          = DIK_ADD         ;
    _mapStr2Dik["DIK_NUMPAD1"]      = DIK_NUMPAD1     ;
    _mapStr2Dik["DIK_NUMPAD2"]      = DIK_NUMPAD2     ;
    _mapStr2Dik["DIK_NUMPAD3"]      = DIK_NUMPAD3     ;
    _mapStr2Dik["DIK_NUMPAD0"]      = DIK_NUMPAD0     ;
    _mapStr2Dik["DIK_DECIMAL"]      = DIK_DECIMAL     ;
    _mapStr2Dik["DIK_OEM_102"]      = DIK_OEM_102     ;
    _mapStr2Dik["DIK_F11"]          = DIK_F11         ;
    _mapStr2Dik["DIK_F12"]          = DIK_F12         ;
    _mapStr2Dik["DIK_F13"]          = DIK_F13         ;
    _mapStr2Dik["DIK_F14"]          = DIK_F14         ;
    _mapStr2Dik["DIK_F15"]          = DIK_F15         ;
    _mapStr2Dik["DIK_KANA"]         = DIK_KANA        ;
    _mapStr2Dik["DIK_ABNT_C1"]      = DIK_ABNT_C1     ;
    _mapStr2Dik["DIK_CONVERT"]      = DIK_CONVERT     ;
    _mapStr2Dik["DIK_NOCONVERT"]    = DIK_NOCONVERT   ;
    _mapStr2Dik["DIK_YEN"]          = DIK_YEN         ;
    _mapStr2Dik["DIK_ABNT_C2"]      = DIK_ABNT_C2     ;
    _mapStr2Dik["DIK_NUMPADEQUALS"] = DIK_NUMPADEQUALS;
    _mapStr2Dik["DIK_PREVTRACK"]    = DIK_PREVTRACK   ;
    _mapStr2Dik["DIK_AT"]           = DIK_AT          ;
    _mapStr2Dik["DIK_COLON"]        = DIK_COLON       ;
    _mapStr2Dik["DIK_UNDERLINE"]    = DIK_UNDERLINE   ;
    _mapStr2Dik["DIK_KANJI"]        = DIK_KANJI       ;
    _mapStr2Dik["DIK_STOP"]         = DIK_STOP        ;
    _mapStr2Dik["DIK_AX"]           = DIK_AX          ;
    _mapStr2Dik["DIK_UNLABELED"]    = DIK_UNLABELED   ;
    _mapStr2Dik["DIK_NEXTTRACK"]    = DIK_NEXTTRACK   ;
    _mapStr2Dik["DIK_NUMPADENTER"]  = DIK_NUMPADENTER ;
    _mapStr2Dik["DIK_RCONTROL"]     = DIK_RCONTROL    ;
    _mapStr2Dik["DIK_MUTE"]         = DIK_MUTE        ;
    _mapStr2Dik["DIK_CALCULATOR"]   = DIK_CALCULATOR  ;
    _mapStr2Dik["DIK_PLAYPAUSE"]    = DIK_PLAYPAUSE   ;
    _mapStr2Dik["DIK_MEDIASTOP"]    = DIK_MEDIASTOP   ;
    _mapStr2Dik["DIK_VOLUMEDOWN"]   = DIK_VOLUMEDOWN  ;
    _mapStr2Dik["DIK_VOLUMEUP"]     = DIK_VOLUMEUP    ;
    _mapStr2Dik["DIK_WEBHOME"]      = DIK_WEBHOME     ;
    _mapStr2Dik["DIK_NUMPADCOMMA"]  = DIK_NUMPADCOMMA ;
    _mapStr2Dik["DIK_DIVIDE"]       = DIK_DIVIDE      ;
    _mapStr2Dik["DIK_SYSRQ"]        = DIK_SYSRQ       ;
    _mapStr2Dik["DIK_RMENU"]        = DIK_RMENU       ;
    _mapStr2Dik["DIK_PAUSE"]        = DIK_PAUSE       ;
    _mapStr2Dik["DIK_HOME"]         = DIK_HOME        ;
    _mapStr2Dik["DIK_UP"]           = DIK_UP          ;
    _mapStr2Dik["DIK_PRIOR"]        = DIK_PRIOR       ;
    _mapStr2Dik["DIK_LEFT"]         = DIK_LEFT        ;
    _mapStr2Dik["DIK_RIGHT"]        = DIK_RIGHT       ;
    _mapStr2Dik["DIK_END"]          = DIK_END         ;
    _mapStr2Dik["DIK_DOWN"]         = DIK_DOWN        ;
    _mapStr2Dik["DIK_NEXT"]         = DIK_NEXT        ;
    _mapStr2Dik["DIK_INSERT"]       = DIK_INSERT      ;
    _mapStr2Dik["DIK_DELETE"]       = DIK_DELETE      ;
    _mapStr2Dik["DIK_LWIN"]         = DIK_LWIN        ;
    _mapStr2Dik["DIK_RWIN"]         = DIK_RWIN        ;
    _mapStr2Dik["DIK_APPS"]         = DIK_APPS        ;
    _mapStr2Dik["DIK_POWER"]        = DIK_POWER       ;
    _mapStr2Dik["DIK_SLEEP"]        = DIK_SLEEP       ;
    _mapStr2Dik["DIK_WAKE"]         = DIK_WAKE        ;
    _mapStr2Dik["DIK_WEBSEARCH"]    = DIK_WEBSEARCH   ;
    _mapStr2Dik["DIK_WEBFAVORITES"] = DIK_WEBFAVORITES;
    _mapStr2Dik["DIK_WEBREFRESH"]   = DIK_WEBREFRESH  ;
    _mapStr2Dik["DIK_WEBSTOP"]      = DIK_WEBSTOP     ;
    _mapStr2Dik["DIK_WEBFORWARD"]   = DIK_WEBFORWARD  ;
    _mapStr2Dik["DIK_WEBBACK"]      = DIK_WEBBACK     ;
    _mapStr2Dik["DIK_MYCOMPUTER"]   = DIK_MYCOMPUTER  ;
    _mapStr2Dik["DIK_MAIL"]         = DIK_MAIL        ;
    _mapStr2Dik["DIK_MEDIASELECT"]  = DIK_MEDIASELECT ;
//    _mapStr2Dik["DIK_BACKSPACE"]    = ;
//    _mapStr2Dik["DIK_NUMPADSTAR"]   = ;
//    _mapStr2Dik["DIK_LALT"]         = ;
//    _mapStr2Dik["DIK_CAPSLOCK"]     = ;
//    _mapStr2Dik["DIK_NUMPADMINUS"]  = ;
//    _mapStr2Dik["DIK_NUMPADPLUS"]   = ;
//    _mapStr2Dik["DIK_NUMPADPERIOD"] = ;
//    _mapStr2Dik["DIK_NUMPADSLASH"]  = ;
//    _mapStr2Dik["DIK_RALT"]         = ;
//    _mapStr2Dik["DIK_UPARROW"]      = ;
//    _mapStr2Dik["DIK_PGUP"]         = ;
//    _mapStr2Dik["DIK_LEFTARROW"]    = ;
//    _mapStr2Dik["DIK_RIGHTARROW"]   = ;
//    _mapStr2Dik["DIK_DOWNARROW"]    = ;
//    _mapStr2Dik["DIK_PGDN"]         = ;

    _mapStr2JoyBtn["VBJ_BUTTON_00"]   = VBJ_BUTTON_00  ;
    _mapStr2JoyBtn["VBJ_BUTTON_01"]   = VBJ_BUTTON_01  ;
    _mapStr2JoyBtn["VBJ_BUTTON_02"]   = VBJ_BUTTON_02  ;
    _mapStr2JoyBtn["VBJ_BUTTON_03"]   = VBJ_BUTTON_03  ;
    _mapStr2JoyBtn["VBJ_BUTTON_04"]   = VBJ_BUTTON_04  ;
    _mapStr2JoyBtn["VBJ_BUTTON_05"]   = VBJ_BUTTON_05  ;
    _mapStr2JoyBtn["VBJ_BUTTON_06"]   = VBJ_BUTTON_06  ;
    _mapStr2JoyBtn["VBJ_BUTTON_07"]   = VBJ_BUTTON_07  ;
    _mapStr2JoyBtn["VBJ_BUTTON_08"]   = VBJ_BUTTON_08  ;
    _mapStr2JoyBtn["VBJ_BUTTON_09"]   = VBJ_BUTTON_09  ;
    _mapStr2JoyBtn["VBJ_BUTTON_10"]   = VBJ_BUTTON_10  ;
    _mapStr2JoyBtn["VBJ_BUTTON_11"]   = VBJ_BUTTON_11  ;
    _mapStr2JoyBtn["VBJ_BUTTON_12"]   = VBJ_BUTTON_12  ;
    _mapStr2JoyBtn["VBJ_BUTTON_13"]   = VBJ_BUTTON_13  ;
    _mapStr2JoyBtn["VBJ_BUTTON_14"]   = VBJ_BUTTON_14  ;
    _mapStr2JoyBtn["VBJ_BUTTON_15"]   = VBJ_BUTTON_15  ;
    _mapStr2JoyBtn["VBJ_X_POS_MINUS"] = VBJ_X_POS_MINUS;
    _mapStr2JoyBtn["VBJ_X_POS_PLUS"]  = VBJ_X_POS_PLUS ;
    _mapStr2JoyBtn["VBJ_Y_POS_MINUS"] = VBJ_Y_POS_MINUS;
    _mapStr2JoyBtn["VBJ_Y_POS_PLUS"]  = VBJ_Y_POS_PLUS ;
    _mapStr2JoyBtn["VBJ_Z_POS_MINUS"] = VBJ_Z_POS_MINUS;
    _mapStr2JoyBtn["VBJ_Z_POS_PLUS"]  = VBJ_Z_POS_PLUS ;
    _mapStr2JoyBtn["VBJ_X_ROT_MINUS"] = VBJ_X_ROT_MINUS;
    _mapStr2JoyBtn["VBJ_X_ROT_PLUS"]  = VBJ_X_ROT_PLUS ;
    _mapStr2JoyBtn["VBJ_Y_ROT_MINUS"] = VBJ_Y_ROT_MINUS;
    _mapStr2JoyBtn["VBJ_Y_ROT_PLUS"]  = VBJ_Y_ROT_PLUS ;
    _mapStr2JoyBtn["VBJ_Z_ROT_MINUS"] = VBJ_Z_ROT_MINUS;
    _mapStr2JoyBtn["VBJ_Z_ROT_PLUS"]  = VBJ_Z_ROT_PLUS ;
    _mapStr2JoyBtn["VBJ_POV_UP"]      = VBJ_POV_UP     ;
    _mapStr2JoyBtn["VBJ_POV_DOWN"]    = VBJ_POV_DOWN   ;
    _mapStr2JoyBtn["VBJ_POV_LEFT"]    = VBJ_POV_LEFT   ;
    _mapStr2JoyBtn["VBJ_POV_RIGHT"]   = VBJ_POV_RIGHT  ;

    _mapDik2Str[DIK_ESCAPE      ]  = "DIK_ESCAPE";
    _mapDik2Str[DIK_1           ]  = "DIK_1";
    _mapDik2Str[DIK_2           ]  = "DIK_2";
    _mapDik2Str[DIK_3           ]  = "DIK_3";
    _mapDik2Str[DIK_4           ]  = "DIK_4";
    _mapDik2Str[DIK_5           ]  = "DIK_5";
    _mapDik2Str[DIK_6           ]  = "DIK_6";
    _mapDik2Str[DIK_7           ]  = "DIK_7";
    _mapDik2Str[DIK_8           ]  = "DIK_8";
    _mapDik2Str[DIK_9           ]  = "DIK_9";
    _mapDik2Str[DIK_0           ]  = "DIK_0";
    _mapDik2Str[DIK_MINUS       ]  = "DIK_MINUS";
    _mapDik2Str[DIK_EQUALS      ]  = "DIK_EQUALS";
    _mapDik2Str[DIK_BACK        ]  = "DIK_BACK";
    _mapDik2Str[DIK_TAB         ]  = "DIK_TAB";
    _mapDik2Str[DIK_Q           ]  = "DIK_Q";
    _mapDik2Str[DIK_W           ]  = "DIK_W";
    _mapDik2Str[DIK_E           ]  = "DIK_E";
    _mapDik2Str[DIK_R           ]  = "DIK_R";
    _mapDik2Str[DIK_T           ]  = "DIK_T";
    _mapDik2Str[DIK_Y           ]  = "DIK_Y";
    _mapDik2Str[DIK_U           ]  = "DIK_U";
    _mapDik2Str[DIK_I           ]  = "DIK_I";
    _mapDik2Str[DIK_O           ]  = "DIK_O";
    _mapDik2Str[DIK_P           ]  = "DIK_P";
    _mapDik2Str[DIK_LBRACKET    ]  = "DIK_LBRACKET";
    _mapDik2Str[DIK_RBRACKET    ]  = "DIK_RBRACKET";
    _mapDik2Str[DIK_RETURN      ]  = "DIK_RETURN";
    _mapDik2Str[DIK_LCONTROL    ]  = "DIK_LCONTROL";
    _mapDik2Str[DIK_A           ]  = "DIK_A";
    _mapDik2Str[DIK_S           ]  = "DIK_S";
    _mapDik2Str[DIK_D           ]  = "DIK_D";
    _mapDik2Str[DIK_F           ]  = "DIK_F";
    _mapDik2Str[DIK_G           ]  = "DIK_G";
    _mapDik2Str[DIK_H           ]  = "DIK_H";
    _mapDik2Str[DIK_J           ]  = "DIK_J";
    _mapDik2Str[DIK_K           ]  = "DIK_K";
    _mapDik2Str[DIK_L           ]  = "DIK_L";
    _mapDik2Str[DIK_SEMICOLON   ]  = "DIK_SEMICOLON";
    _mapDik2Str[DIK_APOSTROPHE  ]  = "DIK_APOSTROPHE";
    _mapDik2Str[DIK_GRAVE       ]  = "DIK_GRAVE";
    _mapDik2Str[DIK_LSHIFT      ]  = "DIK_LSHIFT";
    _mapDik2Str[DIK_BACKSLASH   ]  = "DIK_BACKSLASH";
    _mapDik2Str[DIK_Z           ]  = "DIK_Z";
    _mapDik2Str[DIK_X           ]  = "DIK_X";
    _mapDik2Str[DIK_C           ]  = "DIK_C";
    _mapDik2Str[DIK_V           ]  = "DIK_V";
    _mapDik2Str[DIK_B           ]  = "DIK_B";
    _mapDik2Str[DIK_N           ]  = "DIK_N";
    _mapDik2Str[DIK_M           ]  = "DIK_M";
    _mapDik2Str[DIK_COMMA       ]  = "DIK_COMMA";
    _mapDik2Str[DIK_PERIOD      ]  = "DIK_PERIOD";
    _mapDik2Str[DIK_SLASH       ]  = "DIK_SLASH";
    _mapDik2Str[DIK_RSHIFT      ]  = "DIK_RSHIFT";
    _mapDik2Str[DIK_MULTIPLY    ]  = "DIK_MULTIPLY";
    _mapDik2Str[DIK_LMENU       ]  = "DIK_LMENU";
    _mapDik2Str[DIK_SPACE       ]  = "DIK_SPACE";
    _mapDik2Str[DIK_CAPITAL     ]  = "DIK_CAPITAL";
    _mapDik2Str[DIK_F1          ]  = "DIK_F1";
    _mapDik2Str[DIK_F2          ]  = "DIK_F2";
    _mapDik2Str[DIK_F3          ]  = "DIK_F3";
    _mapDik2Str[DIK_F4          ]  = "DIK_F4";
    _mapDik2Str[DIK_F5          ]  = "DIK_F5";
    _mapDik2Str[DIK_F6          ]  = "DIK_F6";
    _mapDik2Str[DIK_F7          ]  = "DIK_F7";
    _mapDik2Str[DIK_F8          ]  = "DIK_F8";
    _mapDik2Str[DIK_F9          ]  = "DIK_F9";
    _mapDik2Str[DIK_F10         ]  = "DIK_F10";
    _mapDik2Str[DIK_NUMLOCK     ]  = "DIK_NUMLOCK";
    _mapDik2Str[DIK_SCROLL      ]  = "DIK_SCROLL";
    _mapDik2Str[DIK_NUMPAD7     ]  = "DIK_NUMPAD7";
    _mapDik2Str[DIK_NUMPAD8     ]  = "DIK_NUMPAD8";
    _mapDik2Str[DIK_NUMPAD9     ]  = "DIK_NUMPAD9";
    _mapDik2Str[DIK_SUBTRACT    ]  = "DIK_SUBTRACT";
    _mapDik2Str[DIK_NUMPAD4     ]  = "DIK_NUMPAD4";
    _mapDik2Str[DIK_NUMPAD5     ]  = "DIK_NUMPAD5";
    _mapDik2Str[DIK_NUMPAD6     ]  = "DIK_NUMPAD6";
    _mapDik2Str[DIK_ADD         ]  = "DIK_ADD";
    _mapDik2Str[DIK_NUMPAD1     ]  = "DIK_NUMPAD1";
    _mapDik2Str[DIK_NUMPAD2     ]  = "DIK_NUMPAD2";
    _mapDik2Str[DIK_NUMPAD3     ]  = "DIK_NUMPAD3";
    _mapDik2Str[DIK_NUMPAD0     ]  = "DIK_NUMPAD0";
    _mapDik2Str[DIK_DECIMAL     ]  = "DIK_DECIMAL";
    _mapDik2Str[DIK_OEM_102     ]  = "DIK_OEM_102";
    _mapDik2Str[DIK_F11         ]  = "DIK_F11";
    _mapDik2Str[DIK_F12         ]  = "DIK_F12";
    _mapDik2Str[DIK_F13         ]  = "DIK_F13";
    _mapDik2Str[DIK_F14         ]  = "DIK_F14";
    _mapDik2Str[DIK_F15         ]  = "DIK_F15";
    _mapDik2Str[DIK_KANA        ]  = "DIK_KANA";
    _mapDik2Str[DIK_ABNT_C1     ]  = "DIK_ABNT_C1";
    _mapDik2Str[DIK_CONVERT     ]  = "DIK_CONVERT";
    _mapDik2Str[DIK_NOCONVERT   ]  = "DIK_NOCONVERT";
    _mapDik2Str[DIK_YEN         ]  = "DIK_YEN";
    _mapDik2Str[DIK_ABNT_C2     ]  = "DIK_ABNT_C2";
    _mapDik2Str[DIK_NUMPADEQUALS]  = "DIK_NUMPADEQUALS";
    _mapDik2Str[DIK_PREVTRACK   ]  = "DIK_PREVTRACK";
    _mapDik2Str[DIK_AT          ]  = "DIK_AT";
    _mapDik2Str[DIK_COLON       ]  = "DIK_COLON";
    _mapDik2Str[DIK_UNDERLINE   ]  = "DIK_UNDERLINE";
    _mapDik2Str[DIK_KANJI       ]  = "DIK_KANJI";
    _mapDik2Str[DIK_STOP        ]  = "DIK_STOP";
    _mapDik2Str[DIK_AX          ]  = "DIK_AX";
    _mapDik2Str[DIK_UNLABELED   ]  = "DIK_UNLABELED";
    _mapDik2Str[DIK_NEXTTRACK   ]  = "DIK_NEXTTRACK";
    _mapDik2Str[DIK_NUMPADENTER ]  = "DIK_NUMPADENTER";
    _mapDik2Str[DIK_RCONTROL    ]  = "DIK_RCONTROL";
    _mapDik2Str[DIK_MUTE        ]  = "DIK_MUTE";
    _mapDik2Str[DIK_CALCULATOR  ]  = "DIK_CALCULATOR";
    _mapDik2Str[DIK_PLAYPAUSE   ]  = "DIK_PLAYPAUSE";
    _mapDik2Str[DIK_MEDIASTOP   ]  = "DIK_MEDIASTOP";
    _mapDik2Str[DIK_VOLUMEDOWN  ]  = "DIK_VOLUMEDOWN";
    _mapDik2Str[DIK_VOLUMEUP    ]  = "DIK_VOLUMEUP";
    _mapDik2Str[DIK_WEBHOME     ]  = "DIK_WEBHOME";
    _mapDik2Str[DIK_NUMPADCOMMA ]  = "DIK_NUMPADCOMMA";
    _mapDik2Str[DIK_DIVIDE      ]  = "DIK_DIVIDE";
    _mapDik2Str[DIK_SYSRQ       ]  = "DIK_SYSRQ";
    _mapDik2Str[DIK_RMENU       ]  = "DIK_RMENU";
    _mapDik2Str[DIK_PAUSE       ]  = "DIK_PAUSE";
    _mapDik2Str[DIK_HOME        ]  = "DIK_HOME";
    _mapDik2Str[DIK_UP          ]  = "DIK_UP";
    _mapDik2Str[DIK_PRIOR       ]  = "DIK_PRIOR";
    _mapDik2Str[DIK_LEFT        ]  = "DIK_LEFT";
    _mapDik2Str[DIK_RIGHT       ]  = "DIK_RIGHT";
    _mapDik2Str[DIK_END         ]  = "DIK_END";
    _mapDik2Str[DIK_DOWN        ]  = "DIK_DOWN";
    _mapDik2Str[DIK_NEXT        ]  = "DIK_NEXT";
    _mapDik2Str[DIK_INSERT      ]  = "DIK_INSERT";
    _mapDik2Str[DIK_DELETE      ]  = "DIK_DELETE";
    _mapDik2Str[DIK_LWIN        ]  = "DIK_LWIN";
    _mapDik2Str[DIK_RWIN        ]  = "DIK_RWIN";
    _mapDik2Str[DIK_APPS        ]  = "DIK_APPS";
    _mapDik2Str[DIK_POWER       ]  = "DIK_POWER";
    _mapDik2Str[DIK_SLEEP       ]  = "DIK_SLEEP";
    _mapDik2Str[DIK_WAKE        ]  = "DIK_WAKE";
    _mapDik2Str[DIK_WEBSEARCH   ]  = "DIK_WEBSEARCH";
    _mapDik2Str[DIK_WEBFAVORITES]  = "DIK_WEBFAVORITES";
    _mapDik2Str[DIK_WEBREFRESH  ]  = "DIK_WEBREFRESH";
    _mapDik2Str[DIK_WEBSTOP     ]  = "DIK_WEBSTOP";
    _mapDik2Str[DIK_WEBFORWARD  ]  = "DIK_WEBFORWARD";
    _mapDik2Str[DIK_WEBBACK     ]  = "DIK_WEBBACK";
    _mapDik2Str[DIK_MYCOMPUTER  ]  = "DIK_MYCOMPUTER";
    _mapDik2Str[DIK_MAIL        ]  = "DIK_MAIL";
    _mapDik2Str[DIK_MEDIASELECT ]  = "DIK_MEDIASELECT";
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

    _mapJoyBtn2Str[VBJ_BUTTON_00  ] = "VBJ_BUTTON_00";
    _mapJoyBtn2Str[VBJ_BUTTON_01  ] = "VBJ_BUTTON_01";
    _mapJoyBtn2Str[VBJ_BUTTON_02  ] = "VBJ_BUTTON_02";
    _mapJoyBtn2Str[VBJ_BUTTON_03  ] = "VBJ_BUTTON_03";
    _mapJoyBtn2Str[VBJ_BUTTON_04  ] = "VBJ_BUTTON_04";
    _mapJoyBtn2Str[VBJ_BUTTON_05  ] = "VBJ_BUTTON_05";
    _mapJoyBtn2Str[VBJ_BUTTON_06  ] = "VBJ_BUTTON_06";
    _mapJoyBtn2Str[VBJ_BUTTON_07  ] = "VBJ_BUTTON_07";
    _mapJoyBtn2Str[VBJ_BUTTON_08  ] = "VBJ_BUTTON_08";
    _mapJoyBtn2Str[VBJ_BUTTON_09  ] = "VBJ_BUTTON_09";
    _mapJoyBtn2Str[VBJ_BUTTON_10  ] = "VBJ_BUTTON_10";
    _mapJoyBtn2Str[VBJ_BUTTON_11  ] = "VBJ_BUTTON_11";
    _mapJoyBtn2Str[VBJ_BUTTON_12  ] = "VBJ_BUTTON_12";
    _mapJoyBtn2Str[VBJ_BUTTON_13  ] = "VBJ_BUTTON_13";
    _mapJoyBtn2Str[VBJ_BUTTON_14  ] = "VBJ_BUTTON_14";
    _mapJoyBtn2Str[VBJ_BUTTON_15  ] = "VBJ_BUTTON_15";
    _mapJoyBtn2Str[VBJ_X_POS_MINUS] = "VBJ_X_POS_MINUS";
    _mapJoyBtn2Str[VBJ_X_POS_PLUS ] = "VBJ_X_POS_PLUS";
    _mapJoyBtn2Str[VBJ_Y_POS_MINUS] = "VBJ_Y_POS_MINUS";
    _mapJoyBtn2Str[VBJ_Y_POS_PLUS ] = "VBJ_Y_POS_PLUS";
    _mapJoyBtn2Str[VBJ_Z_POS_MINUS] = "VBJ_Z_POS_MINUS";
    _mapJoyBtn2Str[VBJ_Z_POS_PLUS ] = "VBJ_Z_POS_PLUS";
    _mapJoyBtn2Str[VBJ_X_ROT_MINUS] = "VBJ_X_ROT_MINUS";
    _mapJoyBtn2Str[VBJ_X_ROT_PLUS ] = "VBJ_X_ROT_PLUS";
    _mapJoyBtn2Str[VBJ_Y_ROT_MINUS] = "VBJ_Y_ROT_MINUS";
    _mapJoyBtn2Str[VBJ_Y_ROT_PLUS ] = "VBJ_Y_ROT_PLUS";
    _mapJoyBtn2Str[VBJ_Z_ROT_MINUS] = "VBJ_Z_ROT_MINUS";
    _mapJoyBtn2Str[VBJ_Z_ROT_PLUS ] = "VBJ_Z_ROT_PLUS";
    _mapJoyBtn2Str[VBJ_POV_UP     ] = "VBJ_POV_UP";
    _mapJoyBtn2Str[VBJ_POV_DOWN   ] = "VBJ_POV_DOWN";
    _mapJoyBtn2Str[VBJ_POV_LEFT   ] = "VBJ_POV_LEFT";
    _mapJoyBtn2Str[VBJ_POV_RIGHT  ] = "VBJ_POV_RIGHT";

    _mapVJoyBtn2Func[VBJ_X_POS_MINUS] = GgafDxCore::GgafDxInput::isBeingPressedJoyXAxisMinus;
    _mapVJoyBtn2Func[VBJ_X_POS_PLUS ] = GgafDxCore::GgafDxInput::isBeingPressedJoyXAxisPlus;
    _mapVJoyBtn2Func[VBJ_Y_POS_MINUS] = GgafDxCore::GgafDxInput::isBeingPressedJoyYAxisMinus;
    _mapVJoyBtn2Func[VBJ_Y_POS_PLUS ] = GgafDxCore::GgafDxInput::isBeingPressedJoyYAxisPlus;
    _mapVJoyBtn2Func[VBJ_Z_POS_MINUS] = GgafDxCore::GgafDxInput::isBeingPressedJoyZAxisMinus;
    _mapVJoyBtn2Func[VBJ_Z_POS_PLUS ] = GgafDxCore::GgafDxInput::isBeingPressedJoyZAxisPlus;
    _mapVJoyBtn2Func[VBJ_X_ROT_MINUS] = GgafDxCore::GgafDxInput::isBeingPressedJoyRxMinus;
    _mapVJoyBtn2Func[VBJ_X_ROT_PLUS ] = GgafDxCore::GgafDxInput::isBeingPressedJoyRxPlus;
    _mapVJoyBtn2Func[VBJ_Y_ROT_MINUS] = GgafDxCore::GgafDxInput::isBeingPressedJoyRyMinus;
    _mapVJoyBtn2Func[VBJ_Y_ROT_PLUS ] = GgafDxCore::GgafDxInput::isBeingPressedJoyRyPlus;
    _mapVJoyBtn2Func[VBJ_Z_ROT_MINUS] = GgafDxCore::GgafDxInput::isBeingPressedJoyRzMinus;
    _mapVJoyBtn2Func[VBJ_Z_ROT_PLUS ] = GgafDxCore::GgafDxInput::isBeingPressedJoyRzPlus;
    _mapVJoyBtn2Func[VBJ_POV_UP     ] = GgafDxCore::GgafDxInput::isBeingPressedPovUp;
    _mapVJoyBtn2Func[VBJ_POV_DOWN   ] = GgafDxCore::GgafDxInput::isBeingPressedPovDown;
    _mapVJoyBtn2Func[VBJ_POV_LEFT   ] = GgafDxCore::GgafDxInput::isBeingPressedPovLeft;
    _mapVJoyBtn2Func[VBJ_POV_RIGHT  ] = GgafDxCore::GgafDxInput::isBeingPressedPovRight;
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

vbsta VirtualButton::arePushedDownAtOnce(vbsta prm_aVB[], int prm_num_button) {

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
        state |= (VB_S1_UP    * GgafDxInput::isBeingPressedKey(kmap.S1_UP));
        state |= (VB_S1_DOWN  * GgafDxInput::isBeingPressedKey(kmap.S1_DOWN));
        state |= (VB_S1_LEFT  * GgafDxInput::isBeingPressedKey(kmap.S1_LEFT));
        state |= (VB_S1_RIGHT * GgafDxInput::isBeingPressedKey(kmap.S1_RIGHT));
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
            state |= (VB_S1_UP    * VirtualButton::isBeingPressedVirtualJoyButton(jmap.S1_UP)    );
            state |= (VB_S1_DOWN  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.S1_DOWN)  );
            state |= (VB_S1_LEFT  * VirtualButton::isBeingPressedVirtualJoyButton(jmap.S1_LEFT)  );
            state |= (VB_S1_RIGHT * VirtualButton::isBeingPressedVirtualJoyButton(jmap.S1_RIGHT) );
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


 bool VirtualButton::isBeingPressedVirtualJoyButton(int prm_virtual_joy_button_no) {
    if (0 <= prm_virtual_joy_button_no && prm_virtual_joy_button_no <= 0x0F) {
        return GgafDxCore::GgafDxInput::isBeingPressedJoyButton(prm_virtual_joy_button_no);
    } else {
        if ( ( 0x80 <= prm_virtual_joy_button_no && prm_virtual_joy_button_no <= 0x8B ) ||
             ( 0x90 <= prm_virtual_joy_button_no && prm_virtual_joy_button_no <= 0x93 )   )
        {
            //XYZ軸上下か、XYZ軸回転＋ーか、POVの方向の場合
            return (_mapVJoyBtn2Func[prm_virtual_joy_button_no])();
        } else {
            return -1;
        }
    }
}
int VirtualButton::getPushedDownVirtualJoyButton() {
    int VBJ_pushed = GgafDxInput::getPushedDownJoyRgbButton();
    if (VBJ_pushed == -1) {
        if (GgafDxInput::isBeingPressedJoyXAxisMinus()) {
            return 0x80;
        } else if (GgafDxInput::isBeingPressedJoyXAxisPlus()) {
            return 0x81;
        } else if (GgafDxInput::isBeingPressedJoyYAxisMinus()) {
            return 0x82;
        } else if (GgafDxInput::isBeingPressedJoyYAxisPlus()) {
            return 0x83;
        } else if (GgafDxInput::isBeingPressedJoyZAxisMinus()) {
            return 0x84;
        } else if (GgafDxInput::isBeingPressedJoyZAxisPlus()) {
            return 0x85;
        } else if (GgafDxInput::isBeingPressedJoyRxMinus()) {
            return 0x86;
        } else if (GgafDxInput::isBeingPressedJoyRxPlus()) {
            return 0x87;
        } else if (GgafDxInput::isBeingPressedJoyRyMinus()) {
            return 0x88;
        } else if (GgafDxInput::isBeingPressedJoyRyPlus()) {
            return 0x89;
        } else if (GgafDxInput::isBeingPressedJoyRzMinus()) {
            return 0x8A;
        } else if (GgafDxInput::isBeingPressedJoyRzPlus()) {
            return 0x8B;
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

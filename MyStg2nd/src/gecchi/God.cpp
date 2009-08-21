#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

God::God(HINSTANCE prm_hInstance, HWND _hWnd) : DefaultGod(prm_hInstance, _hWnd) {
    VirtualButton::init();

    VirtualButton::_tagKeymap.BUTTON1    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_SHOT1) ];
    VirtualButton::_tagKeymap.BUTTON2    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_SHOT2) ];
    VirtualButton::_tagKeymap.BUTTON3    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_OPTION) ];
    VirtualButton::_tagKeymap.BUTTON4    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_ZMOVE) ];
    VirtualButton::_tagKeymap.BUTTON5    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_BUTTON5) ];
    VirtualButton::_tagKeymap.BUTTON6    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_BUTTON6) ];
    VirtualButton::_tagKeymap.PAUSE      = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_PAUSE) ];
    VirtualButton::_tagKeymap.UP         = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UP) ];
    VirtualButton::_tagKeymap.DOWN       = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_DOWN) ];
    VirtualButton::_tagKeymap.LEFT       = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_LEFT) ];
    VirtualButton::_tagKeymap.RIGHT      = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_RIGHT) ];
    VirtualButton::_tagKeymap.UI_UP      = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UI_UP) ];
    VirtualButton::_tagKeymap.UI_DOWN    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UI_DOWN) ];
    VirtualButton::_tagKeymap.UI_LEFT    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UI_LEFT) ];
    VirtualButton::_tagKeymap.UI_RIGHT   = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UI_RIGHT) ];
    VirtualButton::_tagKeymap.UI_EXECUTE = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UI_EXECUT) ];
    VirtualButton::_tagKeymap.UI_CANCEL  = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UI_CANCEL) ];
    VirtualButton::_tagKeymap.UI_DEBUG   = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UI_DEBUG) ];
    VirtualButton::_tagJoymap.BUTTON1    = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_SHOT1) ];
    VirtualButton::_tagJoymap.BUTTON2    = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_SHOT2) ];
    VirtualButton::_tagJoymap.BUTTON3    = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_OPTION) ];
    VirtualButton::_tagJoymap.BUTTON4    = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_ZMOVE) ];
    VirtualButton::_tagJoymap.BUTTON5    = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_BUTTON5) ];
    VirtualButton::_tagJoymap.BUTTON6    = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_BUTTON6) ];
    VirtualButton::_tagJoymap.PAUSE      = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_PAUSE) ];
    VirtualButton::_tagJoymap.UI_EXECUTE = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_UI_EXECUT) ];
    VirtualButton::_tagJoymap.UI_CANCEL  = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_UI_CANCEL) ];
//    VirtualButton::_tagKeymap = {
//                                  DIK_Z,      // BUTTON1
//                                  DIK_X,      // BUTTON2
//                                  DIK_A,      // BUTTON3
//                                  DIK_Q,      // BUTTON4
//                                  DIK_C,      // BUTTON5
//                                  DIK_V,      // BUTTON6
//                                  DIK_ESCAPE, // PAUSE
//                                  DIK_UP,     // UP
//                                  DIK_DOWN,   // DOWN
//                                  DIK_LEFT,   // LEFT
//                                  DIK_RIGHT,  // RIGHT
//                                  DIK_UP,     // UI_UP
//                                  DIK_DOWN,   // UI_DOWN
//                                  DIK_LEFT,   // UI_LEFT
//                                  DIK_RIGHT,  // UI_RIGHT
//                                  DIK_RETURN, // UI_EXECUTE
//                                  DIK_ESCAPE, // UI_CANCEL
//                                  DIK_D       // UI_DEBUG
//                               };

//    VirtualButton::_tagJoymap = {
//                                  0, // BUTTON1
//                                  7, // BUTTON2
//                                  8, // BUTTON3
//                                  1, // BUTTON4
//                                  2, // BUTTON5
//                                  3, // BUTTON6
//                                  6, // PAUSE
//                                  0, // UI_EXECUTE
//                                  4  // UI_CANCEL
//                               };


}

GgafUniverse* God::createUniverse() {
    Universe* pUniverse = NEW Universe("MYUNIVERSE");
    return (GgafUniverse*)pUniverse;
}

God::~God() {
    VirtualButton::clear();
    _pUniverse->dump();
}

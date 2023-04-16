#include "jp/ggaf/lib/util/VirtualButton.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/lib/util/VBReplayRecorder.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafLib;

VirtualButton::VirtualButton(const char* prm_replay_file) : GgafCore::Object() {
    _vbk_keyboardmap.P1_BUTTON1     = VBK_Z;
    _vbk_keyboardmap.P1_BUTTON2     = VBK_X;
    _vbk_keyboardmap.P1_BUTTON3     = VBK_C;
    _vbk_keyboardmap.P1_BUTTON4     = VBK_A;
    _vbk_keyboardmap.P1_BUTTON5     = VBK_S;
    _vbk_keyboardmap.P1_BUTTON6     = VBK_D;
    _vbk_keyboardmap.P1_BUTTON7     = VBK_V;
    _vbk_keyboardmap.P1_BUTTON8     = VBK_B;
    _vbk_keyboardmap.P1_BUTTON9     = VBK_N;
    _vbk_keyboardmap.P1_BUTTON10    = VBK_M;
    _vbk_keyboardmap.P1_BUTTON11    = 0xFF;
    _vbk_keyboardmap.P1_BUTTON12    = 0xFF;
    _vbk_keyboardmap.P1_BUTTON13    = 0xFF;
    _vbk_keyboardmap.P1_BUTTON14    = 0xFF;
    _vbk_keyboardmap.P1_BUTTON15    = 0xFF;
    _vbk_keyboardmap.P1_BUTTON16    = 0xFF;
    _vbk_keyboardmap.P1_PAUSE       = VBK_ESCAPE;
    _vbk_keyboardmap.P1_UP          = VBK_UP;
    _vbk_keyboardmap.P1_DOWN        = VBK_DOWN;
    _vbk_keyboardmap.P1_LEFT        = VBK_LEFT;
    _vbk_keyboardmap.P1_RIGHT       = VBK_RIGHT;
    _vbk_keyboardmap.P1_S1_UP       = 0xFF;
    _vbk_keyboardmap.P1_S1_DOWN     = 0xFF;
    _vbk_keyboardmap.P1_S1_LEFT     = 0xFF;
    _vbk_keyboardmap.P1_S1_RIGHT    = 0xFF;
    _vbk_keyboardmap.P1_S2_UP       = 0xFF;
    _vbk_keyboardmap.P1_S2_DOWN     = 0xFF;
    _vbk_keyboardmap.P1_S2_LEFT     = 0xFF;
    _vbk_keyboardmap.P1_S2_RIGHT    = 0xFF;
    _vbk_keyboardmap.P1_UI_UP       = VBK_UP;
    _vbk_keyboardmap.P1_UI_DOWN     = VBK_DOWN;
    _vbk_keyboardmap.P1_UI_LEFT     = VBK_LEFT;
    _vbk_keyboardmap.P1_UI_RIGHT    = VBK_RIGHT;
    _vbk_keyboardmap.P1_UI_EXECUTE  = VBK_RETURN;
    _vbk_keyboardmap.P1_UI_CANCEL   = VBK_ESCAPE;
    _vbk_keyboardmap.P1_UI_DEBUG    = VBK_Q;
    _vbk_keyboardmap.P1_UI_START    = VBK_1;
    _vbk_keyboardmap.P1_UI_COIN     = VBK_5;
    _vbk_keyboardmap.P1_UI_SERVICE  = 0xFF;
    _vbk_keyboardmap.P1_UI_TEST     = 0xFF;

    _vbk_keyboardmap.P2_BUTTON1     = 0xFF;
    _vbk_keyboardmap.P2_BUTTON2     = 0xFF;
    _vbk_keyboardmap.P2_BUTTON3     = 0xFF;
    _vbk_keyboardmap.P2_BUTTON4     = 0xFF;
    _vbk_keyboardmap.P2_BUTTON5     = 0xFF;
    _vbk_keyboardmap.P2_BUTTON6     = 0xFF;
    _vbk_keyboardmap.P2_BUTTON7     = 0xFF;
    _vbk_keyboardmap.P2_BUTTON8     = 0xFF;
    _vbk_keyboardmap.P2_BUTTON9     = 0xFF;
    _vbk_keyboardmap.P2_BUTTON10    = 0xFF;
    _vbk_keyboardmap.P2_BUTTON11    = 0xFF;
    _vbk_keyboardmap.P2_BUTTON12    = 0xFF;
    _vbk_keyboardmap.P2_BUTTON13    = 0xFF;
    _vbk_keyboardmap.P2_BUTTON14    = 0xFF;
    _vbk_keyboardmap.P2_BUTTON15    = 0xFF;
    _vbk_keyboardmap.P2_BUTTON16    = 0xFF;
    _vbk_keyboardmap.P2_PAUSE       = 0xFF;
    _vbk_keyboardmap.P2_UP          = 0xFF;
    _vbk_keyboardmap.P2_DOWN        = 0xFF;
    _vbk_keyboardmap.P2_LEFT        = 0xFF;
    _vbk_keyboardmap.P2_RIGHT       = 0xFF;
    _vbk_keyboardmap.P2_S1_UP       = 0xFF;
    _vbk_keyboardmap.P2_S1_DOWN     = 0xFF;
    _vbk_keyboardmap.P2_S1_LEFT     = 0xFF;
    _vbk_keyboardmap.P2_S1_RIGHT    = 0xFF;
    _vbk_keyboardmap.P2_S2_UP       = 0xFF;
    _vbk_keyboardmap.P2_S2_DOWN     = 0xFF;
    _vbk_keyboardmap.P2_S2_LEFT     = 0xFF;
    _vbk_keyboardmap.P2_S2_RIGHT    = 0xFF;
    _vbk_keyboardmap.P2_UI_UP       = 0xFF;
    _vbk_keyboardmap.P2_UI_DOWN     = 0xFF;
    _vbk_keyboardmap.P2_UI_LEFT     = 0xFF;
    _vbk_keyboardmap.P2_UI_RIGHT    = 0xFF;
    _vbk_keyboardmap.P2_UI_EXECUTE  = 0xFF;
    _vbk_keyboardmap.P2_UI_CANCEL   = 0xFF;
    _vbk_keyboardmap.P2_UI_DEBUG    = 0xFF;
    _vbk_keyboardmap.P2_UI_START    = 0xFF;
    _vbk_keyboardmap.P2_UI_COIN     = 0xFF;
    _vbk_keyboardmap.P2_UI_SERVICE  = 0xFF;
    _vbk_keyboardmap.P2_UI_TEST     = 0xFF;

    _vbj_joystickmap[P1_JOY_STICK].BUTTON1     = VBJ_P1_BUTTON_01;
    _vbj_joystickmap[P1_JOY_STICK].BUTTON2     = VBJ_P1_BUTTON_02;
    _vbj_joystickmap[P1_JOY_STICK].BUTTON3     = VBJ_P1_BUTTON_03;
    _vbj_joystickmap[P1_JOY_STICK].BUTTON4     = VBJ_P1_BUTTON_04;
    _vbj_joystickmap[P1_JOY_STICK].BUTTON5     = VBJ_P1_BUTTON_05;
    _vbj_joystickmap[P1_JOY_STICK].BUTTON6     = VBJ_P1_BUTTON_06;
    _vbj_joystickmap[P1_JOY_STICK].BUTTON7     = VBJ_P1_BUTTON_07;
    _vbj_joystickmap[P1_JOY_STICK].BUTTON8     = VBJ_P1_BUTTON_08;
    _vbj_joystickmap[P1_JOY_STICK].BUTTON9     = VBJ_P1_BUTTON_09;
    _vbj_joystickmap[P1_JOY_STICK].BUTTON10    = VBJ_P1_BUTTON_10;
    _vbj_joystickmap[P1_JOY_STICK].BUTTON11    = VBJ_P1_BUTTON_11;
    _vbj_joystickmap[P1_JOY_STICK].BUTTON12    = VBJ_P1_BUTTON_12;
    _vbj_joystickmap[P1_JOY_STICK].BUTTON13    = VBJ_P1_BUTTON_13;
    _vbj_joystickmap[P1_JOY_STICK].BUTTON14    = VBJ_P1_BUTTON_14;
    _vbj_joystickmap[P1_JOY_STICK].BUTTON15    = VBJ_P1_BUTTON_15;
    _vbj_joystickmap[P1_JOY_STICK].BUTTON16    = VBJ_P1_BUTTON_16;
    _vbj_joystickmap[P1_JOY_STICK].PAUSE       = VBJ_P1_BUTTON_08;
    _vbj_joystickmap[P1_JOY_STICK].UP          = VBJ_P1_Y_POS_MINUS;
    _vbj_joystickmap[P1_JOY_STICK].DOWN        = VBJ_P1_Y_POS_PLUS ;
    _vbj_joystickmap[P1_JOY_STICK].LEFT        = VBJ_P1_X_POS_MINUS;
    _vbj_joystickmap[P1_JOY_STICK].RIGHT       = VBJ_P1_X_POS_PLUS ;
    _vbj_joystickmap[P1_JOY_STICK].S1_UP       = 0xFF;
    _vbj_joystickmap[P1_JOY_STICK].S1_DOWN     = 0xFF;
    _vbj_joystickmap[P1_JOY_STICK].S1_LEFT     = 0xFF;
    _vbj_joystickmap[P1_JOY_STICK].S1_RIGHT    = 0xFF;
    _vbj_joystickmap[P1_JOY_STICK].S2_UP       = 0xFF;
    _vbj_joystickmap[P1_JOY_STICK].S2_DOWN     = 0xFF;
    _vbj_joystickmap[P1_JOY_STICK].S2_LEFT     = 0xFF;
    _vbj_joystickmap[P1_JOY_STICK].S2_RIGHT    = 0xFF;
    _vbj_joystickmap[P1_JOY_STICK].UI_UP       = VBJ_P1_Y_POS_MINUS;
    _vbj_joystickmap[P1_JOY_STICK].UI_DOWN     = VBJ_P1_Y_POS_PLUS ;
    _vbj_joystickmap[P1_JOY_STICK].UI_LEFT     = VBJ_P1_X_POS_MINUS;
    _vbj_joystickmap[P1_JOY_STICK].UI_RIGHT    = VBJ_P1_X_POS_PLUS ;
    _vbj_joystickmap[P1_JOY_STICK].UI_EXECUTE  = VBJ_P1_BUTTON_01;
    _vbj_joystickmap[P1_JOY_STICK].UI_CANCEL   = VBJ_P1_BUTTON_02;
    _vbj_joystickmap[P1_JOY_STICK].UI_DEBUG    = 0xFF;
    _vbj_joystickmap[P1_JOY_STICK].UI_START    = 0xFF;
    _vbj_joystickmap[P1_JOY_STICK].UI_COIN     = 0xFF;
    _vbj_joystickmap[P1_JOY_STICK].UI_SERVICE  = 0xFF;
    _vbj_joystickmap[P1_JOY_STICK].UI_TEST     = 0xFF;

    //_vbj_joystickmap.UI_DEBUG    = //; 0xFF
    _vbj_joystickmap[P2_JOY_STICK].BUTTON1     = VBJ_P2_BUTTON_01;
    _vbj_joystickmap[P2_JOY_STICK].BUTTON2     = VBJ_P2_BUTTON_02;
    _vbj_joystickmap[P2_JOY_STICK].BUTTON3     = VBJ_P2_BUTTON_03;
    _vbj_joystickmap[P2_JOY_STICK].BUTTON4     = VBJ_P2_BUTTON_04;
    _vbj_joystickmap[P2_JOY_STICK].BUTTON5     = VBJ_P2_BUTTON_05;
    _vbj_joystickmap[P2_JOY_STICK].BUTTON6     = VBJ_P2_BUTTON_06;
    _vbj_joystickmap[P2_JOY_STICK].BUTTON7     = VBJ_P2_BUTTON_07;
    _vbj_joystickmap[P2_JOY_STICK].BUTTON8     = VBJ_P2_BUTTON_08;
    _vbj_joystickmap[P2_JOY_STICK].BUTTON9     = VBJ_P2_BUTTON_09;
    _vbj_joystickmap[P2_JOY_STICK].BUTTON10    = VBJ_P2_BUTTON_10;
    _vbj_joystickmap[P2_JOY_STICK].BUTTON11    = VBJ_P2_BUTTON_11;
    _vbj_joystickmap[P2_JOY_STICK].BUTTON12    = VBJ_P2_BUTTON_12;
    _vbj_joystickmap[P2_JOY_STICK].BUTTON13    = VBJ_P2_BUTTON_13;
    _vbj_joystickmap[P2_JOY_STICK].BUTTON14    = VBJ_P2_BUTTON_14;
    _vbj_joystickmap[P2_JOY_STICK].BUTTON15    = VBJ_P2_BUTTON_15;
    _vbj_joystickmap[P2_JOY_STICK].BUTTON16    = VBJ_P2_BUTTON_16;
    _vbj_joystickmap[P2_JOY_STICK].PAUSE       = VBJ_P2_BUTTON_08;
    _vbj_joystickmap[P2_JOY_STICK].UP          = VBJ_P2_Y_POS_MINUS;
    _vbj_joystickmap[P2_JOY_STICK].DOWN        = VBJ_P2_Y_POS_PLUS ;
    _vbj_joystickmap[P2_JOY_STICK].LEFT        = VBJ_P2_X_POS_MINUS;
    _vbj_joystickmap[P2_JOY_STICK].RIGHT       = VBJ_P2_X_POS_PLUS ;
    _vbj_joystickmap[P2_JOY_STICK].S1_UP       = 0xFF;
    _vbj_joystickmap[P2_JOY_STICK].S1_DOWN     = 0xFF;
    _vbj_joystickmap[P2_JOY_STICK].S1_LEFT     = 0xFF;
    _vbj_joystickmap[P2_JOY_STICK].S1_RIGHT    = 0xFF;
    _vbj_joystickmap[P2_JOY_STICK].S2_UP       = 0xFF;
    _vbj_joystickmap[P2_JOY_STICK].S2_DOWN     = 0xFF;
    _vbj_joystickmap[P2_JOY_STICK].S2_LEFT     = 0xFF;
    _vbj_joystickmap[P2_JOY_STICK].S2_RIGHT    = 0xFF;
    _vbj_joystickmap[P2_JOY_STICK].UI_UP       = VBJ_P2_Y_POS_MINUS;
    _vbj_joystickmap[P2_JOY_STICK].UI_DOWN     = VBJ_P2_Y_POS_PLUS ;
    _vbj_joystickmap[P2_JOY_STICK].UI_LEFT     = VBJ_P2_X_POS_MINUS;
    _vbj_joystickmap[P2_JOY_STICK].UI_RIGHT    = VBJ_P2_X_POS_PLUS ;
    _vbj_joystickmap[P2_JOY_STICK].UI_EXECUTE  = VBJ_P2_BUTTON_01;
    _vbj_joystickmap[P2_JOY_STICK].UI_CANCEL   = VBJ_P2_BUTTON_02;
    _vbj_joystickmap[P2_JOY_STICK].UI_DEBUG    = 0xFF;
    _vbj_joystickmap[P2_JOY_STICK].UI_START    = 0xFF;
    _vbj_joystickmap[P2_JOY_STICK].UI_COIN     = 0xFF;
    _vbj_joystickmap[P2_JOY_STICK].UI_SERVICE  = 0xFF;
    _vbj_joystickmap[P2_JOY_STICK].UI_TEST     = 0xFF;

    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON1   ] = &(_vbk_keyboardmap.P1_BUTTON1   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON2   ] = &(_vbk_keyboardmap.P1_BUTTON2   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON3   ] = &(_vbk_keyboardmap.P1_BUTTON3   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON4   ] = &(_vbk_keyboardmap.P1_BUTTON4   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON5   ] = &(_vbk_keyboardmap.P1_BUTTON5   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON6   ] = &(_vbk_keyboardmap.P1_BUTTON6   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON7   ] = &(_vbk_keyboardmap.P1_BUTTON7   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON8   ] = &(_vbk_keyboardmap.P1_BUTTON8   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON9   ] = &(_vbk_keyboardmap.P1_BUTTON9   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON10  ] = &(_vbk_keyboardmap.P1_BUTTON10  );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON11  ] = &(_vbk_keyboardmap.P1_BUTTON11  );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON12  ] = &(_vbk_keyboardmap.P1_BUTTON12  );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON13  ] = &(_vbk_keyboardmap.P1_BUTTON13  );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON14  ] = &(_vbk_keyboardmap.P1_BUTTON14  );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON15  ] = &(_vbk_keyboardmap.P1_BUTTON15  );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_BUTTON16  ] = &(_vbk_keyboardmap.P1_BUTTON16  );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_PAUSE     ] = &(_vbk_keyboardmap.P1_PAUSE     );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_UP        ] = &(_vbk_keyboardmap.P1_UP        );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_DOWN      ] = &(_vbk_keyboardmap.P1_DOWN      );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_LEFT      ] = &(_vbk_keyboardmap.P1_LEFT      );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_RIGHT     ] = &(_vbk_keyboardmap.P1_RIGHT     );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_S1_UP     ] = &(_vbk_keyboardmap.P1_S1_UP     );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_S1_DOWN   ] = &(_vbk_keyboardmap.P1_S1_DOWN   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_S1_LEFT   ] = &(_vbk_keyboardmap.P1_S1_LEFT   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_S1_RIGHT  ] = &(_vbk_keyboardmap.P1_S1_RIGHT  );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_S2_UP     ] = &(_vbk_keyboardmap.P1_S2_UP     );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_S2_DOWN   ] = &(_vbk_keyboardmap.P1_S2_DOWN   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_S2_LEFT   ] = &(_vbk_keyboardmap.P1_S2_LEFT   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_S2_RIGHT  ] = &(_vbk_keyboardmap.P1_S2_RIGHT  );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_UI_UP     ] = &(_vbk_keyboardmap.P1_UI_UP     );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_UI_DOWN   ] = &(_vbk_keyboardmap.P1_UI_DOWN   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_UI_LEFT   ] = &(_vbk_keyboardmap.P1_UI_LEFT   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_UI_RIGHT  ] = &(_vbk_keyboardmap.P1_UI_RIGHT  );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_UI_EXECUTE] = &(_vbk_keyboardmap.P1_UI_EXECUTE);
    _mapVB2keyboardmap[P1_JOY_STICK][VB_UI_CANCEL ] = &(_vbk_keyboardmap.P1_UI_CANCEL );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_UI_DEBUG  ] = &(_vbk_keyboardmap.P1_UI_DEBUG  );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_UI_START  ] = &(_vbk_keyboardmap.P1_UI_START  );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_UI_COIN   ] = &(_vbk_keyboardmap.P1_UI_COIN   );
    _mapVB2keyboardmap[P1_JOY_STICK][VB_UI_SERVICE] = &(_vbk_keyboardmap.P1_UI_SERVICE);
    _mapVB2keyboardmap[P1_JOY_STICK][VB_UI_TEST   ] = &(_vbk_keyboardmap.P1_UI_TEST   );

    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON1   ] = &(_vbk_keyboardmap.P2_BUTTON1   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON2   ] = &(_vbk_keyboardmap.P2_BUTTON2   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON3   ] = &(_vbk_keyboardmap.P2_BUTTON3   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON4   ] = &(_vbk_keyboardmap.P2_BUTTON4   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON5   ] = &(_vbk_keyboardmap.P2_BUTTON5   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON6   ] = &(_vbk_keyboardmap.P2_BUTTON6   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON7   ] = &(_vbk_keyboardmap.P2_BUTTON7   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON8   ] = &(_vbk_keyboardmap.P2_BUTTON8   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON9   ] = &(_vbk_keyboardmap.P2_BUTTON9   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON10  ] = &(_vbk_keyboardmap.P2_BUTTON10  );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON11  ] = &(_vbk_keyboardmap.P2_BUTTON11  );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON12  ] = &(_vbk_keyboardmap.P2_BUTTON12  );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON13  ] = &(_vbk_keyboardmap.P2_BUTTON13  );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON14  ] = &(_vbk_keyboardmap.P2_BUTTON14  );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON15  ] = &(_vbk_keyboardmap.P2_BUTTON15  );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_BUTTON16  ] = &(_vbk_keyboardmap.P2_BUTTON16  );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_PAUSE     ] = &(_vbk_keyboardmap.P2_PAUSE     );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_UP        ] = &(_vbk_keyboardmap.P2_UP        );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_DOWN      ] = &(_vbk_keyboardmap.P2_DOWN      );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_LEFT      ] = &(_vbk_keyboardmap.P2_LEFT      );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_RIGHT     ] = &(_vbk_keyboardmap.P2_RIGHT     );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_S1_UP     ] = &(_vbk_keyboardmap.P2_S1_UP     );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_S1_DOWN   ] = &(_vbk_keyboardmap.P2_S1_DOWN   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_S1_LEFT   ] = &(_vbk_keyboardmap.P2_S1_LEFT   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_S1_RIGHT  ] = &(_vbk_keyboardmap.P2_S1_RIGHT  );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_S2_UP     ] = &(_vbk_keyboardmap.P2_S2_UP     );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_S2_DOWN   ] = &(_vbk_keyboardmap.P2_S2_DOWN   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_S2_LEFT   ] = &(_vbk_keyboardmap.P2_S2_LEFT   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_S2_RIGHT  ] = &(_vbk_keyboardmap.P2_S2_RIGHT  );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_UI_UP     ] = &(_vbk_keyboardmap.P2_UI_UP     );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_UI_DOWN   ] = &(_vbk_keyboardmap.P2_UI_DOWN   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_UI_LEFT   ] = &(_vbk_keyboardmap.P2_UI_LEFT   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_UI_RIGHT  ] = &(_vbk_keyboardmap.P2_UI_RIGHT  );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_UI_EXECUTE] = &(_vbk_keyboardmap.P2_UI_EXECUTE);
    _mapVB2keyboardmap[P2_JOY_STICK][VB_UI_CANCEL ] = &(_vbk_keyboardmap.P2_UI_CANCEL );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_UI_DEBUG  ] = &(_vbk_keyboardmap.P2_UI_DEBUG  );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_UI_START  ] = &(_vbk_keyboardmap.P2_UI_START  );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_UI_COIN   ] = &(_vbk_keyboardmap.P2_UI_COIN   );
    _mapVB2keyboardmap[P2_JOY_STICK][VB_UI_SERVICE] = &(_vbk_keyboardmap.P2_UI_SERVICE);
    _mapVB2keyboardmap[P2_JOY_STICK][VB_UI_TEST   ] = &(_vbk_keyboardmap.P2_UI_TEST   );

    for (int p = 0; p < MAX_JOY_STICK_NUM; p++) {
        _mapVB2joystickmap[p][VB_BUTTON1   ] = &(_vbj_joystickmap[p].BUTTON1   );
        _mapVB2joystickmap[p][VB_BUTTON2   ] = &(_vbj_joystickmap[p].BUTTON2   );
        _mapVB2joystickmap[p][VB_BUTTON3   ] = &(_vbj_joystickmap[p].BUTTON3   );
        _mapVB2joystickmap[p][VB_BUTTON4   ] = &(_vbj_joystickmap[p].BUTTON4   );
        _mapVB2joystickmap[p][VB_BUTTON5   ] = &(_vbj_joystickmap[p].BUTTON5   );
        _mapVB2joystickmap[p][VB_BUTTON6   ] = &(_vbj_joystickmap[p].BUTTON6   );
        _mapVB2joystickmap[p][VB_BUTTON7   ] = &(_vbj_joystickmap[p].BUTTON7   );
        _mapVB2joystickmap[p][VB_BUTTON8   ] = &(_vbj_joystickmap[p].BUTTON8   );
        _mapVB2joystickmap[p][VB_BUTTON9   ] = &(_vbj_joystickmap[p].BUTTON9   );
        _mapVB2joystickmap[p][VB_BUTTON10  ] = &(_vbj_joystickmap[p].BUTTON10  );
        _mapVB2joystickmap[p][VB_BUTTON11  ] = &(_vbj_joystickmap[p].BUTTON11  );
        _mapVB2joystickmap[p][VB_BUTTON12  ] = &(_vbj_joystickmap[p].BUTTON12  );
        _mapVB2joystickmap[p][VB_BUTTON13  ] = &(_vbj_joystickmap[p].BUTTON13  );
        _mapVB2joystickmap[p][VB_BUTTON14  ] = &(_vbj_joystickmap[p].BUTTON14  );
        _mapVB2joystickmap[p][VB_BUTTON15  ] = &(_vbj_joystickmap[p].BUTTON15  );
        _mapVB2joystickmap[p][VB_BUTTON16  ] = &(_vbj_joystickmap[p].BUTTON16  );
        _mapVB2joystickmap[p][VB_PAUSE     ] = &(_vbj_joystickmap[p].PAUSE     );
        _mapVB2joystickmap[p][VB_UP        ] = &(_vbj_joystickmap[p].UP        );
        _mapVB2joystickmap[p][VB_DOWN      ] = &(_vbj_joystickmap[p].DOWN      );
        _mapVB2joystickmap[p][VB_LEFT      ] = &(_vbj_joystickmap[p].LEFT      );
        _mapVB2joystickmap[p][VB_RIGHT     ] = &(_vbj_joystickmap[p].RIGHT     );
        _mapVB2joystickmap[p][VB_S1_UP     ] = &(_vbj_joystickmap[p].S1_UP     );
        _mapVB2joystickmap[p][VB_S1_DOWN   ] = &(_vbj_joystickmap[p].S1_DOWN   );
        _mapVB2joystickmap[p][VB_S1_LEFT   ] = &(_vbj_joystickmap[p].S1_LEFT   );
        _mapVB2joystickmap[p][VB_S1_RIGHT  ] = &(_vbj_joystickmap[p].S1_RIGHT  );
        _mapVB2joystickmap[p][VB_S2_UP     ] = &(_vbj_joystickmap[p].S2_UP     );
        _mapVB2joystickmap[p][VB_S2_DOWN   ] = &(_vbj_joystickmap[p].S2_DOWN   );
        _mapVB2joystickmap[p][VB_S2_LEFT   ] = &(_vbj_joystickmap[p].S2_LEFT   );
        _mapVB2joystickmap[p][VB_S2_RIGHT  ] = &(_vbj_joystickmap[p].S2_RIGHT  );
        _mapVB2joystickmap[p][VB_UI_UP     ] = &(_vbj_joystickmap[p].UI_UP     );
        _mapVB2joystickmap[p][VB_UI_DOWN   ] = &(_vbj_joystickmap[p].UI_DOWN   );
        _mapVB2joystickmap[p][VB_UI_LEFT   ] = &(_vbj_joystickmap[p].UI_LEFT   );
        _mapVB2joystickmap[p][VB_UI_RIGHT  ] = &(_vbj_joystickmap[p].UI_RIGHT  );
        _mapVB2joystickmap[p][VB_UI_EXECUTE] = &(_vbj_joystickmap[p].UI_EXECUTE);
        _mapVB2joystickmap[p][VB_UI_CANCEL ] = &(_vbj_joystickmap[p].UI_CANCEL );
        _mapVB2joystickmap[p][VB_UI_DEBUG  ] = &(_vbj_joystickmap[p].UI_DEBUG  );
        _mapVB2joystickmap[p][VB_UI_START  ] = &(_vbj_joystickmap[p].UI_START  );
        _mapVB2joystickmap[p][VB_UI_COIN   ] = &(_vbj_joystickmap[p].UI_COIN   );
        _mapVB2joystickmap[p][VB_UI_SERVICE] = &(_vbj_joystickmap[p].UI_SERVICE);
        _mapVB2joystickmap[p][VB_UI_TEST   ] = &(_vbj_joystickmap[p].UI_TEST   );
    }


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

    _with_pov = true;

    static volatile bool is_init = VirtualButton::initStatic(); //静的メンバ初期化
}

std::map<std::string, vbk> VirtualButton::_mapStr2VBK;
std::map<std::string, vbj> VirtualButton::_mapStr2VBJ;
std::map<vbk, std::string> VirtualButton::_mapVBK2Str;
std::map<vbj, std::string> VirtualButton::_mapVBJ2Str;
std::map<vbj_base, VirtualButton::funcVJBtn> VirtualButton::_mapVbjBase2Func;
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

    VirtualButton::_mapStr2VBK["VBK_BACKSPACE"]    = VBK_BACKSPACE   ;
    VirtualButton::_mapStr2VBK["VBK_NUMPADSTAR"]   = VBK_NUMPADSTAR  ;
    VirtualButton::_mapStr2VBK["VBK_LALT"]         = VBK_LALT        ;
    VirtualButton::_mapStr2VBK["VBK_CAPSLOCK"]     = VBK_CAPSLOCK    ;
    VirtualButton::_mapStr2VBK["VBK_NUMPADMINUS"]  = VBK_NUMPADMINUS ;
    VirtualButton::_mapStr2VBK["VBK_NUMPADPLUS"]   = VBK_NUMPADPLUS  ;
    VirtualButton::_mapStr2VBK["VBK_NUMPADPERIOD"] = VBK_NUMPADPERIOD;
    VirtualButton::_mapStr2VBK["VBK_NUMPADSLASH"]  = VBK_NUMPADSLASH ;
    VirtualButton::_mapStr2VBK["VBK_RALT"]         = VBK_RALT        ;
    VirtualButton::_mapStr2VBK["VBK_UPARROW"]      = VBK_UPARROW     ;
    VirtualButton::_mapStr2VBK["VBK_PGUP"]         = VBK_PGUP        ;
    VirtualButton::_mapStr2VBK["VBK_LEFTARROW"]    = VBK_LEFTARROW   ;
    VirtualButton::_mapStr2VBK["VBK_RIGHTARROW"]   = VBK_RIGHTARROW  ;
    VirtualButton::_mapStr2VBK["VBK_DOWNARROW"]    = VBK_DOWNARROW   ;
    VirtualButton::_mapStr2VBK["VBK_PGDN"]         = VBK_PGDN        ;


    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_01"]   = VBJ_P1_BUTTON_01  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_02"]   = VBJ_P1_BUTTON_02  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_03"]   = VBJ_P1_BUTTON_03  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_04"]   = VBJ_P1_BUTTON_04  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_05"]   = VBJ_P1_BUTTON_05  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_06"]   = VBJ_P1_BUTTON_06  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_07"]   = VBJ_P1_BUTTON_07  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_08"]   = VBJ_P1_BUTTON_08  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_09"]   = VBJ_P1_BUTTON_09  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_10"]   = VBJ_P1_BUTTON_10  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_11"]   = VBJ_P1_BUTTON_11  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_12"]   = VBJ_P1_BUTTON_12  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_13"]   = VBJ_P1_BUTTON_13  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_14"]   = VBJ_P1_BUTTON_14  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_15"]   = VBJ_P1_BUTTON_15  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_BUTTON_15"]   = VBJ_P1_BUTTON_16  ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_X_POS_MINUS"] = VBJ_P1_X_POS_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_P1_X_POS_PLUS"]  = VBJ_P1_X_POS_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_Y_POS_MINUS"] = VBJ_P1_Y_POS_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_P1_Y_POS_PLUS"]  = VBJ_P1_Y_POS_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_Z_POS_MINUS"] = VBJ_P1_Z_POS_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_P1_Z_POS_PLUS"]  = VBJ_P1_Z_POS_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_X_ROT_MINUS"] = VBJ_P1_X_ROT_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_P1_X_ROT_PLUS"]  = VBJ_P1_X_ROT_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_Y_ROT_MINUS"] = VBJ_P1_Y_ROT_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_P1_Y_ROT_PLUS"]  = VBJ_P1_Y_ROT_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_Z_ROT_MINUS"] = VBJ_P1_Z_ROT_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_P1_Z_ROT_PLUS"]  = VBJ_P1_Z_ROT_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_POV_UP"]      = VBJ_P1_POV_UP     ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_POV_DOWN"]    = VBJ_P1_POV_DOWN   ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_POV_LEFT"]    = VBJ_P1_POV_LEFT   ;
    VirtualButton::_mapStr2VBJ["VBJ_P1_POV_RIGHT"]   = VBJ_P1_POV_RIGHT  ;

    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_01"]   = VBJ_P2_BUTTON_01  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_02"]   = VBJ_P2_BUTTON_02  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_03"]   = VBJ_P2_BUTTON_03  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_04"]   = VBJ_P2_BUTTON_04  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_05"]   = VBJ_P2_BUTTON_05  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_06"]   = VBJ_P2_BUTTON_06  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_07"]   = VBJ_P2_BUTTON_07  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_08"]   = VBJ_P2_BUTTON_08  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_09"]   = VBJ_P2_BUTTON_09  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_10"]   = VBJ_P2_BUTTON_10  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_11"]   = VBJ_P2_BUTTON_11  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_12"]   = VBJ_P2_BUTTON_12  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_13"]   = VBJ_P2_BUTTON_13  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_14"]   = VBJ_P2_BUTTON_14  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_15"]   = VBJ_P2_BUTTON_15  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_BUTTON_15"]   = VBJ_P2_BUTTON_16  ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_X_POS_MINUS"] = VBJ_P2_X_POS_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_P2_X_POS_PLUS"]  = VBJ_P2_X_POS_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_Y_POS_MINUS"] = VBJ_P2_Y_POS_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_P2_Y_POS_PLUS"]  = VBJ_P2_Y_POS_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_Z_POS_MINUS"] = VBJ_P2_Z_POS_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_P2_Z_POS_PLUS"]  = VBJ_P2_Z_POS_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_X_ROT_MINUS"] = VBJ_P2_X_ROT_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_P2_X_ROT_PLUS"]  = VBJ_P2_X_ROT_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_Y_ROT_MINUS"] = VBJ_P2_Y_ROT_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_P2_Y_ROT_PLUS"]  = VBJ_P2_Y_ROT_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_Z_ROT_MINUS"] = VBJ_P2_Z_ROT_MINUS;
    VirtualButton::_mapStr2VBJ["VBJ_P2_Z_ROT_PLUS"]  = VBJ_P2_Z_ROT_PLUS ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_POV_UP"]      = VBJ_P2_POV_UP     ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_POV_DOWN"]    = VBJ_P2_POV_DOWN   ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_POV_LEFT"]    = VBJ_P2_POV_LEFT   ;
    VirtualButton::_mapStr2VBJ["VBJ_P2_POV_RIGHT"]   = VBJ_P2_POV_RIGHT  ;

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

    VirtualButton::_mapVBK2Str[VBK_BACKSPACE   ] = "VBK_BACKSPACE";
    VirtualButton::_mapVBK2Str[VBK_NUMPADSTAR  ] = "VBK_NUMPADSTAR";
    VirtualButton::_mapVBK2Str[VBK_LALT        ] = "VBK_LALT";
    VirtualButton::_mapVBK2Str[VBK_CAPSLOCK    ] = "VBK_CAPSLOCK";
    VirtualButton::_mapVBK2Str[VBK_NUMPADMINUS ] = "VBK_NUMPADMINUS";
    VirtualButton::_mapVBK2Str[VBK_NUMPADPLUS  ] = "VBK_NUMPADPLUS";
    VirtualButton::_mapVBK2Str[VBK_NUMPADPERIOD] = "VBK_NUMPADPERIOD";
    VirtualButton::_mapVBK2Str[VBK_NUMPADSLASH ] = "VBK_NUMPADSLASH";
    VirtualButton::_mapVBK2Str[VBK_RALT        ] = "VBK_RALT";
    VirtualButton::_mapVBK2Str[VBK_UPARROW     ] = "VBK_UPARROW";
    VirtualButton::_mapVBK2Str[VBK_PGUP        ] = "VBK_PGUP";
    VirtualButton::_mapVBK2Str[VBK_LEFTARROW   ] = "VBK_LEFTARROW";
    VirtualButton::_mapVBK2Str[VBK_RIGHTARROW  ] = "VBK_RIGHTARROW";
    VirtualButton::_mapVBK2Str[VBK_DOWNARROW   ] = "VBK_DOWNARROW";
    VirtualButton::_mapVBK2Str[VBK_PGDN        ] = "VBK_PGDN";

    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_01  ] = "VBJ_P1_BUTTON_01";
    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_02  ] = "VBJ_P1_BUTTON_02";
    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_03  ] = "VBJ_P1_BUTTON_03";
    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_04  ] = "VBJ_P1_BUTTON_04";
    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_05  ] = "VBJ_P1_BUTTON_05";
    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_06  ] = "VBJ_P1_BUTTON_06";
    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_07  ] = "VBJ_P1_BUTTON_07";
    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_08  ] = "VBJ_P1_BUTTON_08";
    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_09  ] = "VBJ_P1_BUTTON_09";
    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_10  ] = "VBJ_P1_BUTTON_10";
    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_11  ] = "VBJ_P1_BUTTON_11";
    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_12  ] = "VBJ_P1_BUTTON_12";
    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_13  ] = "VBJ_P1_BUTTON_13";
    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_14  ] = "VBJ_P1_BUTTON_14";
    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_15  ] = "VBJ_P1_BUTTON_15";
    VirtualButton::_mapVBJ2Str[VBJ_P1_BUTTON_16  ] = "VBJ_P1_BUTTON_16";
    VirtualButton::_mapVBJ2Str[VBJ_P1_X_POS_MINUS] = "VBJ_P1_X_POS_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_P1_X_POS_PLUS ] = "VBJ_P1_X_POS_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_P1_Y_POS_MINUS] = "VBJ_P1_Y_POS_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_P1_Y_POS_PLUS ] = "VBJ_P1_Y_POS_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_P1_Z_POS_MINUS] = "VBJ_P1_Z_POS_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_P1_Z_POS_PLUS ] = "VBJ_P1_Z_POS_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_P1_X_ROT_MINUS] = "VBJ_P1_X_ROT_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_P1_X_ROT_PLUS ] = "VBJ_P1_X_ROT_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_P1_Y_ROT_MINUS] = "VBJ_P1_Y_ROT_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_P1_Y_ROT_PLUS ] = "VBJ_P1_Y_ROT_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_P1_Z_ROT_MINUS] = "VBJ_P1_Z_ROT_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_P1_Z_ROT_PLUS ] = "VBJ_P1_Z_ROT_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_P1_POV_UP     ] = "VBJ_P1_POV_UP";
    VirtualButton::_mapVBJ2Str[VBJ_P1_POV_DOWN   ] = "VBJ_P1_POV_DOWN";
    VirtualButton::_mapVBJ2Str[VBJ_P1_POV_LEFT   ] = "VBJ_P1_POV_LEFT";
    VirtualButton::_mapVBJ2Str[VBJ_P1_POV_RIGHT  ] = "VBJ_P1_POV_RIGHT";

    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_01  ] = "VBJ_P2_BUTTON_01";
    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_02  ] = "VBJ_P2_BUTTON_02";
    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_03  ] = "VBJ_P2_BUTTON_03";
    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_04  ] = "VBJ_P2_BUTTON_04";
    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_05  ] = "VBJ_P2_BUTTON_05";
    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_06  ] = "VBJ_P2_BUTTON_06";
    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_07  ] = "VBJ_P2_BUTTON_07";
    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_08  ] = "VBJ_P2_BUTTON_08";
    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_09  ] = "VBJ_P2_BUTTON_09";
    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_10  ] = "VBJ_P2_BUTTON_10";
    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_11  ] = "VBJ_P2_BUTTON_11";
    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_12  ] = "VBJ_P2_BUTTON_12";
    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_13  ] = "VBJ_P2_BUTTON_13";
    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_14  ] = "VBJ_P2_BUTTON_14";
    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_15  ] = "VBJ_P2_BUTTON_15";
    VirtualButton::_mapVBJ2Str[VBJ_P2_BUTTON_16  ] = "VBJ_P2_BUTTON_16";
    VirtualButton::_mapVBJ2Str[VBJ_P2_X_POS_MINUS] = "VBJ_P2_X_POS_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_P2_X_POS_PLUS ] = "VBJ_P2_X_POS_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_P2_Y_POS_MINUS] = "VBJ_P2_Y_POS_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_P2_Y_POS_PLUS ] = "VBJ_P2_Y_POS_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_P2_Z_POS_MINUS] = "VBJ_P2_Z_POS_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_P2_Z_POS_PLUS ] = "VBJ_P2_Z_POS_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_P2_X_ROT_MINUS] = "VBJ_P2_X_ROT_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_P2_X_ROT_PLUS ] = "VBJ_P2_X_ROT_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_P2_Y_ROT_MINUS] = "VBJ_P2_Y_ROT_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_P2_Y_ROT_PLUS ] = "VBJ_P2_Y_ROT_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_P2_Z_ROT_MINUS] = "VBJ_P2_Z_ROT_MINUS";
    VirtualButton::_mapVBJ2Str[VBJ_P2_Z_ROT_PLUS ] = "VBJ_P2_Z_ROT_PLUS";
    VirtualButton::_mapVBJ2Str[VBJ_P2_POV_UP     ] = "VBJ_P2_POV_UP";
    VirtualButton::_mapVBJ2Str[VBJ_P2_POV_DOWN   ] = "VBJ_P2_POV_DOWN";
    VirtualButton::_mapVBJ2Str[VBJ_P2_POV_LEFT   ] = "VBJ_P2_POV_LEFT";
    VirtualButton::_mapVBJ2Str[VBJ_P2_POV_RIGHT  ] = "VBJ_P2_POV_RIGHT";

    VirtualButton::_mapVbjBase2Func[VBJ_BASE_X_POS_MINUS] = GgafDx::Input::isPressedJoyXAxisMinus;
    VirtualButton::_mapVbjBase2Func[VBJ_BASE_X_POS_PLUS ] = GgafDx::Input::isPressedJoyXAxisPlus;
    VirtualButton::_mapVbjBase2Func[VBJ_BASE_Y_POS_MINUS] = GgafDx::Input::isPressedJoyYAxisMinus;
    VirtualButton::_mapVbjBase2Func[VBJ_BASE_Y_POS_PLUS ] = GgafDx::Input::isPressedJoyYAxisPlus;
    VirtualButton::_mapVbjBase2Func[VBJ_BASE_Z_POS_MINUS] = GgafDx::Input::isPressedJoyZAxisMinus;
    VirtualButton::_mapVbjBase2Func[VBJ_BASE_Z_POS_PLUS ] = GgafDx::Input::isPressedJoyZAxisPlus;
    VirtualButton::_mapVbjBase2Func[VBJ_BASE_X_ROT_MINUS] = GgafDx::Input::isPressedJoyRxMinus;
    VirtualButton::_mapVbjBase2Func[VBJ_BASE_X_ROT_PLUS ] = GgafDx::Input::isPressedJoyRxPlus;
    VirtualButton::_mapVbjBase2Func[VBJ_BASE_Y_ROT_MINUS] = GgafDx::Input::isPressedJoyRyMinus;
    VirtualButton::_mapVbjBase2Func[VBJ_BASE_Y_ROT_PLUS ] = GgafDx::Input::isPressedJoyRyPlus;
    VirtualButton::_mapVbjBase2Func[VBJ_BASE_Z_ROT_MINUS] = GgafDx::Input::isPressedJoyRzMinus;
    VirtualButton::_mapVbjBase2Func[VBJ_BASE_Z_ROT_PLUS ] = GgafDx::Input::isPressedJoyRzPlus;
    VirtualButton::_mapVbjBase2Func[VBJ_BASE_POV_UP     ] = GgafDx::Input::isPressedPovUp;
    VirtualButton::_mapVbjBase2Func[VBJ_BASE_POV_DOWN   ] = GgafDx::Input::isPressedPovDown;
    VirtualButton::_mapVbjBase2Func[VBJ_BASE_POV_LEFT   ] = GgafDx::Input::isPressedPovLeft;
    VirtualButton::_mapVbjBase2Func[VBJ_BASE_POV_RIGHT  ] = GgafDx::Input::isPressedPovRight;
    return true;
}

void VirtualButton::remap(int prm_player_no, vb_sta prm_VB, vbk prm_VBK, vbj prm_VBJ) {
    if (_mapVB2keyboardmap[prm_player_no].count(prm_VB) == 0) {
        throwCriticalException("VirtualButton::remap _mapVB2keyboardmapに、キーが存在しません。prm_VB="<<prm_VB);
    }
    if (prm_VBK == 0) {
        throwCriticalException("VirtualButton::remap prm_VB="<<prm_VB<<"に、割り当てる値が不正です。prm_VBK="<<prm_VBK);
    }
    if (_mapVB2joystickmap[prm_player_no].count(prm_VB) == 0) {
        throwCriticalException("VirtualButton::remap _mapVB2joystickmap、キーが存在しません。prm_VB="<<prm_VB);
    }
    if (prm_VBJ == 0) {
        throwCriticalException("VirtualButton::remap prm_VB="<<prm_VB<<"に、割り当てる値が不正です。prm_VBJ="<<prm_VBJ);
    }

    *_mapVB2keyboardmap[prm_player_no][prm_VB] = prm_VBK;
    *_mapVB2joystickmap[prm_player_no][prm_VB] = prm_VBJ;
}

void VirtualButton::remapK(int prm_player_no, vb_sta prm_VB, vbk prm_VBK)  {
    if (_mapVB2keyboardmap[prm_player_no].count(prm_VB) == 0) {
        throwCriticalException("VirtualButton::remap _mapVB2keyboardmapに、キーが存在しません。prm_VB="<<prm_VB);
    }
    if (prm_VBK == 0) {
        throwCriticalException("VirtualButton::remap prm_VB="<<prm_VB<<"に、割り当てる値が不正です。prm_VBK="<<prm_VBK);
    }
    *_mapVB2keyboardmap[prm_player_no][prm_VB] = prm_VBK;
}

void VirtualButton::remapJ(int prm_player_no, vb_sta prm_VB, vbj prm_VBJ)  {
    if (_mapVB2joystickmap[prm_player_no].count(prm_VB) == 0) {
        throwCriticalException("VirtualButton::remap _mapVB2joystickmap、キーが存在しません。prm_VB="<<prm_VB);
    }
    if (prm_VBJ == 0) {
        throwCriticalException("VirtualButton::remap prm_VB="<<prm_VB<<"に、割り当てる値が不正です。prm_VBJ="<<prm_VBJ);
    }
    *_mapVB2joystickmap[prm_player_no][prm_VB] = prm_VBJ;
}

VirtualButton::VBRecord* VirtualButton::getPastVBRecord(frame prm_frame_ago) const {
    VirtualButton::VBRecord* pVBRecord_temp = _pVBRecord_active;
    for (frame i = 0; i < prm_frame_ago; i++) {
        pVBRecord_temp = pVBRecord_temp->_prev;
    }
    return pVBRecord_temp;
}

bool VirtualButton::isAutoRepeat(int prm_player_no, vb_sta prm_VB, frame prm_begin_repeat, frame prm_while_repeat) {
    vb_sta sta = (_pVBRecord_active->_vb_state[prm_player_no] & prm_VB);
    if (sta) {
        _is_auto_repeat = true;
        if (sta == (_pVBRecord_active->_prev->_vb_state[prm_player_no] & prm_VB)) {
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
            return true;
        } else if (_auto_repeat_counter[prm_VB] > prm_begin_repeat && _auto_repeat_counter[prm_VB] % prm_while_repeat == 0) {
            //オートリピート時成立(デフォルトでは、20フレーム後以降は5フレーム毎に成立)
            return true;
        }
    }
    return false;
}

vb_sta VirtualButton::wasPressed(int prm_player_no, vb_sta prm_VB, frame prm_frame_ago) const {
    VirtualButton::VBRecord* pVBRecord_temp = getPastVBRecord(prm_frame_ago);
    return (pVBRecord_temp->_vb_state[prm_player_no] & prm_VB);
}

vb_sta VirtualButton::hasBeenPressed(int prm_player_no, vb_sta prm_VB, frame prm_frame_ago) const {
    VirtualButton::VBRecord* pVBRecord_temp = _pVBRecord_active;
    vb_sta vb_state;
    for (frame i = 0; i < prm_frame_ago+1; i++) {
        vb_state = pVBRecord_temp->_vb_state[prm_player_no] & prm_VB;
        if (!vb_state) {
            //押されていない瞬間あり
            return false;
        }
        pVBRecord_temp = pVBRecord_temp->_prev;
    }
    //過去 prm_frame_ago フレームずっと押されっぱなしは成立
    return true;
}


//vb_sta VirtualButton::wasPressedAtLeastOnce(vb_sta prm_VB, frame prm_frame_ago) const {
//    VirtualButton::VBRecord* pVBRecord_temp = _pVBRecord_active;
//    vb_sta vb_state[0] = pVBRecord_temp->_vb_state[0] & prm_VB;
//    if (vb_state[0]) {
//        return vb_state[0];
//    }
//    for (frame i = 0; i < prm_frame_ago; i++) {
//        pVBRecord_temp = pVBRecord_temp->_prev;
//        vb_state[0] = pVBRecord_temp->_vb_state[0] & prm_VB;
//        if (vb_state[0]) {
//            return vb_state[0];
//        }
//    }
//    return false;
//}
//vb_sta VirtualButton::wasReleasedUpAtLeastOnce(vb_sta prm_VB, frame prm_frame_ago) const {
//    VirtualButton::VBRecord* pVBRecord_temp = _pVBRecord_active;
//
//    if ((pVBRecord_temp->_prev->_vb_state[0] & prm_VB) && !(pVBRecord_temp->_vb_state[0] & prm_VB)) {
//        return true;
//    } else {
//        return false;
//    }
//
//    for (frame i = 0; i < prm_frame_ago; i++) {
//        pVBRecord_temp = pVBRecord_temp->_prev;
//        if ((pVBRecord_temp->_prev->_vb_state[0] & prm_VB) && !(pVBRecord_temp->_vb_state[0] & prm_VB)) {
//            return true;
//        } else {
//            return false;
//        }
//    }
//    return false;
//}


bool VirtualButton::isDoublePushedDown(int prm_player_no, vb_sta prm_VB, frame prm_frame_push, frame prm_frame_delay) const {
    //-------oooo-----o
    //       <--><--->
    //         |    `-- prm_frame_delay
    //         `-- prm_frame_push
    //過去に遡りながら検証
    VirtualButton::VBRecord* pVBRecord;
    pVBRecord = _pVBRecord_active;
    if (pVBRecord->_vb_state[prm_player_no] & prm_VB) {
        //OK
    } else {
        return false;
    }
    pVBRecord = pVBRecord->_prev;
    //直前は必ず押されていては駄目
    if (pVBRecord->_vb_state[prm_player_no] & prm_VB) {
        return false;
    }
    bool ok = false;
    for (frame i = 0; i < prm_frame_delay; i++) {
        pVBRecord = pVBRecord->_prev;
        if (pVBRecord->_vb_state[prm_player_no] & prm_VB) {
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
        if (pVBRecord->_vb_state[prm_player_no] & prm_VB) {

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
//	if (_pVBRecord_active->_vb_state[0][prm_VB]) {
//		for (int i = 0; i < VB_NUM; i++) {
//			if (_pVBRecord_active->_prev->_vb_state[0][i]) {
//				return false;
//			}
//		}
//		return true;
//	} else {
//		return false;
//	}
//}

bool VirtualButton::arePushedDownAtOnce(int prm_player_no, vb_sta prm_aVB[], int prm_num_button, int delay) const {

    //現在は全て押されていなければならない
    for (int i = 0; i < prm_num_button; i++) {
        if (isPressed(prm_player_no, prm_aVB[i]) == false) {
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
//    for (int i = 0; i < prm_num_button; i++) {
//        if (!wasReleasedUpAtLeastOnce(prm_aVB[i], delay)) {
//            return false;
//        }
//    }

    //delay フレーム余裕を見る
    //全ボタンについて、それぞれが以下のいづれかの動作になっているかチェック。
    // ↑ > ？ > ？ > ↓
    //       or
    // ？ > ↑ > ？ > ↓
    //       or
    // ？ > ？ > ↑ > ↓
    for (int i = 0; i < prm_num_button; i++) {
        //各ボタンについてループ
        if (hasBeenPressed(prm_player_no, prm_aVB[i], delay)) {
            //過去 delay フレームずっと押されっぱなしは非成立
            return false;
        }
    }


//    bool prev1Flg, prev2Flg, prev3Flg;
//    for (int i = 0; i < prm_num_button; i++) {
//        prev1Flg = wasNotPressed(prm_aVB[i], 1);
//        prev2Flg = wasNotPressed(prm_aVB[i], 2);
//        prev3Flg = wasNotPressed(prm_aVB[i], 3);
//        if (prev1Flg) {        //＊ > ＊ > ↑ >
//            continue;
//        } else if (prev2Flg) { //＊ > ↑ > ＊ >
//            continue;
//        } else if (prev3Flg) { //↑ > ＊ > ＊ >
//            continue;
//        } else {
//            return false;
//        }
//    }

    //但し1つ前のフレームで、全て押されていては成立しない。
    //この条件入れないと、「同時押し→押しっぱなし」の場合、最大３フレーム連続で成立してしまう場合がある。
    for (int i = 0; i < prm_num_button; i++) {
        if (wasNotPressed(prm_player_no, prm_aVB[i], 1)) {
            return true;
        }
    }
    return false;
}

bool VirtualButton::wasPushedDown(int prm_player_no, vb_sta prm_VB, frame prm_frame_ago) const {
    if (wasPressed(prm_player_no, prm_VB, prm_frame_ago) && wasNotPressed(prm_player_no, prm_VB, prm_frame_ago + 1)) {
        return true;
    } else {
        return false;
    }
}

bool VirtualButton::isReleasedUp(int prm_player_no, vb_sta prm_VB) const {
    if ((_pVBRecord_active->_prev->_vb_state[prm_player_no] & prm_VB) && !(_pVBRecord_active->_vb_state[prm_player_no] & prm_VB)) {
        return true;
    } else {
        return false;
    }
}

bool VirtualButton::isPushedUp(int prm_player_no, vb_sta prm_VB, frame prm_frame_push) const {
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
    if (pVBRecord->_vb_state[prm_player_no] & prm_VB) {
        return false;
    } else {
        //OK
    }
    pVBRecord = pVBRecord->_prev;
    //直前は押されていなければいけない
    if (pVBRecord->_vb_state[prm_player_no] & prm_VB) {
        //OK
    } else {
        return false;
    }
    pVBRecord = pVBRecord->_prev;
    bool ok = false;
    for (frame i = 0; i < prm_frame_push; i++) {
        pVBRecord = pVBRecord->_prev;
        if (pVBRecord->_vb_state[prm_player_no] & prm_VB) {

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

bool VirtualButton::wasReleasedUp(int prm_player_no, vb_sta prm_VB, frame prm_frame_ago) const {
    if (wasNotPressed(prm_player_no, prm_VB, prm_frame_ago) && wasPressed(prm_player_no, prm_VB, prm_frame_ago + 1)) {
        return true;
    } else {
        return false;
    }
}

bool VirtualButton::isScrewPushDown(int prm_player_no, vb_sta prm_VB, frame prm_frame_delay) const {
    if (isPushedDown(prm_player_no, prm_VB)) {
        VirtualButton::VBRecord* pVBRecord;
        pVBRecord = _pVBRecord_active;
        bool up    = false;
        bool down  = false;
        bool left  = false;
        bool right = false;
        for (frame i = 0; i < prm_frame_delay; i++) {
            pVBRecord = pVBRecord->_prev;
            if (pVBRecord->_vb_state[prm_player_no] & VB_UP) {
                up = true;
                continue;
            }
            if (pVBRecord->_vb_state[prm_player_no] & VB_RIGHT) {
                right = true;
                continue;
            }
            if (pVBRecord->_vb_state[prm_player_no] & VB_DOWN) {
                down = true;
                continue;
            }
            if (pVBRecord->_vb_state[0] & VB_LEFT) {
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
//    if (isPressed(prm_VB)) {
//        static bool prev1Flg, prev2Flg, prev3Flg;
//        //ボタンに押されていない期間が直前にあったか
//        prev1Flg = wasNotPressed(prm_VB, 1);
//        prev2Flg = wasNotPressed(prm_VB, 2);
//        prev3Flg = wasNotPressed(prm_VB, 3);
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
//        prev1N_Flg = wasPressed(VB_NEUTRAL_STC, 1);
//        prev2N_Flg = wasPressed(VB_NEUTRAL_STC, 2);
//        prev3N_Flg = wasPressed(VB_NEUTRAL_STC, 3);
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
//            if (isPressed(i)) {
//
//                //但し1つ前のフレームで、両方押されていては成立しない。
//                //（この条件入れないと、「同時押し→押しっぱなし」の場合、数フレーム連続で成立してしまう）
//                if (wasPressed(prm_VB, 1) && wasPressed(i, 1)) {
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
    if (_pVBRecord_active == nullptr) {
        throwCriticalException("利用前に一度 init() を呼び出して下さい。");
    }
#endif
    GgafDx::Input::updateKeyboardState();
    GgafDx::Input::updateAllJoystickState();
    GgafDx::Input::updateMouseState();

    _pVBRecord_active = _pVBRecord_active->_next;
    if (_is_replaying) {
        if (_pRpy->hasNextRecord()) {
            //リプレイ継続時
//            _pVBRecord_active->_vb_state[0] = _pRpy->readNextFrameStatus();
            _pRpy->readNextFrameStatus(_pVBRecord_active->_vb_state);

            return;
        } else {
            //リプレイ終了
            _is_replaying = false;
        }
    }
    //通常操作時
    vb_sta vb_state[MAX_JOY_STICK_NUM];
    vb_state[0] = 0;
    vb_state[1] = 0;
    const VbkKeyboard& kmap = _vbk_keyboardmap;

    BYTE* kst = GgafDx::Input::_keyboard_state[GgafDx::Input::_flip_ks];
    vb_state[0] |= ( VB_BUTTON1    *  ((kst[kmap.P1_BUTTON1] & 0x80)    == 0x80) );
    vb_state[0] |= ( VB_BUTTON2    *  ((kst[kmap.P1_BUTTON2] & 0x80)    == 0x80) );
    vb_state[0] |= ( VB_BUTTON3    *  ((kst[kmap.P1_BUTTON3] & 0x80)    == 0x80) );
    vb_state[0] |= ( VB_BUTTON4    *  ((kst[kmap.P1_BUTTON4] & 0x80)    == 0x80) );
    vb_state[0] |= ( VB_BUTTON5    *  ((kst[kmap.P1_BUTTON5] & 0x80)    == 0x80) );
    vb_state[0] |= ( VB_BUTTON6    *  ((kst[kmap.P1_BUTTON6] & 0x80)    == 0x80) );
    vb_state[0] |= ( VB_BUTTON7    *  ((kst[kmap.P1_BUTTON7] & 0x80)    == 0x80) );
    vb_state[0] |= ( VB_BUTTON8    *  ((kst[kmap.P1_BUTTON8] & 0x80)    == 0x80) );
    vb_state[0] |= ( VB_BUTTON9    *  ((kst[kmap.P1_BUTTON9] & 0x80)    == 0x80) );
    vb_state[0] |= ( VB_BUTTON10   *  ((kst[kmap.P1_BUTTON10] & 0x80)   == 0x80) );
    vb_state[0] |= ( VB_BUTTON11   *  ((kst[kmap.P1_BUTTON11] & 0x80)   == 0x80) );
    vb_state[0] |= ( VB_BUTTON12   *  ((kst[kmap.P1_BUTTON12] & 0x80)   == 0x80) );
    vb_state[0] |= ( VB_BUTTON13   *  ((kst[kmap.P1_BUTTON13] & 0x80)   == 0x80) );
    vb_state[0] |= ( VB_BUTTON14   *  ((kst[kmap.P1_BUTTON14] & 0x80)   == 0x80) );
    vb_state[0] |= ( VB_BUTTON15   *  ((kst[kmap.P1_BUTTON15] & 0x80)   == 0x80) );
    vb_state[0] |= ( VB_BUTTON16   *  ((kst[kmap.P1_BUTTON16] & 0x80)   == 0x80) );
    vb_state[0] |= ( VB_PAUSE      *  ((kst[kmap.P1_PAUSE] & 0x80)      == 0x80) );
    vb_state[0] |= ( VB_UP         *  ((kst[kmap.P1_UP] & 0x80)         == 0x80) );
    vb_state[0] |= ( VB_DOWN       *  ((kst[kmap.P1_DOWN] & 0x80)       == 0x80) );
    vb_state[0] |= ( VB_LEFT       *  ((kst[kmap.P1_LEFT] & 0x80)       == 0x80) );
    vb_state[0] |= ( VB_RIGHT      *  ((kst[kmap.P1_RIGHT] & 0x80)      == 0x80) );
    vb_state[0] |= ( VB_S1_UP      *  ((kst[kmap.P1_S1_UP] & 0x80)      == 0x80) );
    vb_state[0] |= ( VB_S1_DOWN    *  ((kst[kmap.P1_S1_DOWN] & 0x80)    == 0x80) );
    vb_state[0] |= ( VB_S1_LEFT    *  ((kst[kmap.P1_S1_LEFT] & 0x80)    == 0x80) );
    vb_state[0] |= ( VB_S1_RIGHT   *  ((kst[kmap.P1_S1_RIGHT] & 0x80)   == 0x80) );
    vb_state[0] |= ( VB_S2_UP      *  ((kst[kmap.P1_S2_UP] & 0x80)      == 0x80) );
    vb_state[0] |= ( VB_S2_DOWN    *  ((kst[kmap.P1_S2_DOWN] & 0x80)    == 0x80) );
    vb_state[0] |= ( VB_S2_LEFT    *  ((kst[kmap.P1_S2_LEFT] & 0x80)    == 0x80) );
    vb_state[0] |= ( VB_S2_RIGHT   *  ((kst[kmap.P1_S2_RIGHT] & 0x80)   == 0x80) );
    vb_state[0] |= ( VB_UI_UP      *  ((kst[kmap.P1_UI_UP] & 0x80)      == 0x80) );
    vb_state[0] |= ( VB_UI_DOWN    *  ((kst[kmap.P1_UI_DOWN] & 0x80)    == 0x80) );
    vb_state[0] |= ( VB_UI_LEFT    *  ((kst[kmap.P1_UI_LEFT] & 0x80)    == 0x80) );
    vb_state[0] |= ( VB_UI_RIGHT   *  ((kst[kmap.P1_UI_RIGHT] & 0x80)   == 0x80) );
    vb_state[0] |= ( VB_UI_EXECUTE *  ((kst[kmap.P1_UI_EXECUTE] & 0x80) == 0x80) );
    vb_state[0] |= ( VB_UI_CANCEL  *  ((kst[kmap.P1_UI_CANCEL] & 0x80)  == 0x80) );
    vb_state[0] |= ( VB_UI_DEBUG   *  ((kst[kmap.P1_UI_DEBUG] & 0x80)   == 0x80) );
    vb_state[0] |= ( VB_UI_START   *  ((kst[kmap.P1_UI_START  ] & 0x80) == 0x80) );
    vb_state[0] |= ( VB_UI_COIN    *  ((kst[kmap.P1_UI_COIN   ] & 0x80) == 0x80) );
    vb_state[0] |= ( VB_UI_SERVICE *  ((kst[kmap.P1_UI_SERVICE] & 0x80) == 0x80) );
    vb_state[0] |= ( VB_UI_TEST    *  ((kst[kmap.P1_UI_TEST   ] & 0x80) == 0x80) );

    vb_state[1] |= ( VB_BUTTON1    *  ((kst[kmap.P2_BUTTON1] & 0x80)    == 0x80) );
    vb_state[1] |= ( VB_BUTTON2    *  ((kst[kmap.P2_BUTTON2] & 0x80)    == 0x80) );
    vb_state[1] |= ( VB_BUTTON3    *  ((kst[kmap.P2_BUTTON3] & 0x80)    == 0x80) );
    vb_state[1] |= ( VB_BUTTON4    *  ((kst[kmap.P2_BUTTON4] & 0x80)    == 0x80) );
    vb_state[1] |= ( VB_BUTTON5    *  ((kst[kmap.P2_BUTTON5] & 0x80)    == 0x80) );
    vb_state[1] |= ( VB_BUTTON6    *  ((kst[kmap.P2_BUTTON6] & 0x80)    == 0x80) );
    vb_state[1] |= ( VB_BUTTON7    *  ((kst[kmap.P2_BUTTON7] & 0x80)    == 0x80) );
    vb_state[1] |= ( VB_BUTTON8    *  ((kst[kmap.P2_BUTTON8] & 0x80)    == 0x80) );
    vb_state[1] |= ( VB_BUTTON9    *  ((kst[kmap.P2_BUTTON9] & 0x80)    == 0x80) );
    vb_state[1] |= ( VB_BUTTON10   *  ((kst[kmap.P2_BUTTON10] & 0x80)   == 0x80) );
    vb_state[1] |= ( VB_BUTTON11   *  ((kst[kmap.P2_BUTTON11] & 0x80)   == 0x80) );
    vb_state[1] |= ( VB_BUTTON12   *  ((kst[kmap.P2_BUTTON12] & 0x80)   == 0x80) );
    vb_state[1] |= ( VB_BUTTON13   *  ((kst[kmap.P2_BUTTON13] & 0x80)   == 0x80) );
    vb_state[1] |= ( VB_BUTTON14   *  ((kst[kmap.P2_BUTTON14] & 0x80)   == 0x80) );
    vb_state[1] |= ( VB_BUTTON15   *  ((kst[kmap.P2_BUTTON15] & 0x80)   == 0x80) );
    vb_state[1] |= ( VB_BUTTON16   *  ((kst[kmap.P2_BUTTON16] & 0x80)   == 0x80) );
    vb_state[1] |= ( VB_PAUSE      *  ((kst[kmap.P2_PAUSE] & 0x80)      == 0x80) );
    vb_state[1] |= ( VB_UP         *  ((kst[kmap.P2_UP] & 0x80)         == 0x80) );
    vb_state[1] |= ( VB_DOWN       *  ((kst[kmap.P2_DOWN] & 0x80)       == 0x80) );
    vb_state[1] |= ( VB_LEFT       *  ((kst[kmap.P2_LEFT] & 0x80)       == 0x80) );
    vb_state[1] |= ( VB_RIGHT      *  ((kst[kmap.P2_RIGHT] & 0x80)      == 0x80) );
    vb_state[1] |= ( VB_S1_UP      *  ((kst[kmap.P2_S1_UP] & 0x80)      == 0x80) );
    vb_state[1] |= ( VB_S1_DOWN    *  ((kst[kmap.P2_S1_DOWN] & 0x80)    == 0x80) );
    vb_state[1] |= ( VB_S1_LEFT    *  ((kst[kmap.P2_S1_LEFT] & 0x80)    == 0x80) );
    vb_state[1] |= ( VB_S1_RIGHT   *  ((kst[kmap.P2_S1_RIGHT] & 0x80)   == 0x80) );
    vb_state[1] |= ( VB_S2_UP      *  ((kst[kmap.P2_S2_UP] & 0x80)      == 0x80) );
    vb_state[1] |= ( VB_S2_DOWN    *  ((kst[kmap.P2_S2_DOWN] & 0x80)    == 0x80) );
    vb_state[1] |= ( VB_S2_LEFT    *  ((kst[kmap.P2_S2_LEFT] & 0x80)    == 0x80) );
    vb_state[1] |= ( VB_S2_RIGHT   *  ((kst[kmap.P2_S2_RIGHT] & 0x80)   == 0x80) );
    vb_state[1] |= ( VB_UI_UP      *  ((kst[kmap.P2_UI_UP] & 0x80)      == 0x80) );
    vb_state[1] |= ( VB_UI_DOWN    *  ((kst[kmap.P2_UI_DOWN] & 0x80)    == 0x80) );
    vb_state[1] |= ( VB_UI_LEFT    *  ((kst[kmap.P2_UI_LEFT] & 0x80)    == 0x80) );
    vb_state[1] |= ( VB_UI_RIGHT   *  ((kst[kmap.P2_UI_RIGHT] & 0x80)   == 0x80) );
    vb_state[1] |= ( VB_UI_EXECUTE *  ((kst[kmap.P2_UI_EXECUTE] & 0x80) == 0x80) );
    vb_state[1] |= ( VB_UI_CANCEL  *  ((kst[kmap.P2_UI_CANCEL] & 0x80)  == 0x80) );
    vb_state[1] |= ( VB_UI_DEBUG   *  ((kst[kmap.P2_UI_DEBUG] & 0x80)   == 0x80) );
    vb_state[1] |= ( VB_UI_START   *  ((kst[kmap.P2_UI_START  ] & 0x80) == 0x80) );
    vb_state[1] |= ( VB_UI_COIN    *  ((kst[kmap.P2_UI_COIN   ] & 0x80) == 0x80) );
    vb_state[1] |= ( VB_UI_SERVICE *  ((kst[kmap.P2_UI_SERVICE] & 0x80) == 0x80) );
    vb_state[1] |= ( VB_UI_TEST    *  ((kst[kmap.P2_UI_TEST   ] & 0x80) == 0x80) );

    for (int p = 0; p < MAX_JOY_STICK_NUM; p++) {
        if (GgafDx::Input::_apJoystickInputDevice[p]) {
            const VbjJoystick& jmap = _vbj_joystickmap[p];
            vb_state[p] |= (VB_BUTTON1  * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON1));
            vb_state[p] |= (VB_BUTTON2  * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON2));
            vb_state[p] |= (VB_BUTTON3  * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON3));
            vb_state[p] |= (VB_BUTTON4  * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON4));
            vb_state[p] |= (VB_BUTTON5  * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON5));
            vb_state[p] |= (VB_BUTTON6  * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON6));
            vb_state[p] |= (VB_BUTTON7  * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON7));
            vb_state[p] |= (VB_BUTTON8  * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON8));
            vb_state[p] |= (VB_BUTTON9  * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON9));
            vb_state[p] |= (VB_BUTTON10 * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON10));
            vb_state[p] |= (VB_BUTTON11 * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON11));
            vb_state[p] |= (VB_BUTTON12 * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON12));
            vb_state[p] |= (VB_BUTTON13 * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON13));
            vb_state[p] |= (VB_BUTTON14 * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON14));
            vb_state[p] |= (VB_BUTTON15 * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON15));
            vb_state[p] |= (VB_BUTTON16 * VirtualButton::isPressedVirtualJoyButton(jmap.BUTTON16));
            vb_state[p] |= (VB_PAUSE    * VirtualButton::isPressedVirtualJoyButton(jmap.PAUSE));

            vb_state[p] |= (VB_UP       * VirtualButton::isPressedVirtualJoyButton(jmap.UP));
            vb_state[p] |= (VB_DOWN     * VirtualButton::isPressedVirtualJoyButton(jmap.DOWN));
            vb_state[p] |= (VB_LEFT     * VirtualButton::isPressedVirtualJoyButton(jmap.LEFT));
            vb_state[p] |= (VB_RIGHT    * VirtualButton::isPressedVirtualJoyButton(jmap.RIGHT));

            vb_state[p] |= (VB_S1_UP    * VirtualButton::isPressedVirtualJoyButton(jmap.S1_UP));
            vb_state[p] |= (VB_S1_DOWN  * VirtualButton::isPressedVirtualJoyButton(jmap.S1_DOWN));
            vb_state[p] |= (VB_S1_LEFT  * VirtualButton::isPressedVirtualJoyButton(jmap.S1_LEFT));
            vb_state[p] |= (VB_S1_RIGHT * VirtualButton::isPressedVirtualJoyButton(jmap.S1_RIGHT));
            vb_state[p] |= (VB_S2_UP    * VirtualButton::isPressedVirtualJoyButton(jmap.S2_UP));
            vb_state[p] |= (VB_S2_DOWN  * VirtualButton::isPressedVirtualJoyButton(jmap.S2_DOWN));
            vb_state[p] |= (VB_S2_LEFT  * VirtualButton::isPressedVirtualJoyButton(jmap.S2_LEFT));
            vb_state[p] |= (VB_S2_RIGHT * VirtualButton::isPressedVirtualJoyButton(jmap.S2_RIGHT));
            if (_with_pov) {
//                _TRACE_("VirtualButton::isPressedVirtualJoyButton=" <<
//                    VirtualButton::isPressedVirtualJoyButton(jmap.UI_UP) <<
//                    VirtualButton::isPressedVirtualJoyButton(jmap.UI_DOWN) <<
//                    VirtualButton::isPressedVirtualJoyButton(jmap.UI_LEFT) <<
//                    VirtualButton::isPressedVirtualJoyButton(jmap.UI_RIGHT) );
//
//                _TRACE_("GgafDx::Input::isPressedPovUp=" <<
//                    GgafDx::Input::isPressedPovUp(p) <<
//                    GgafDx::Input::isPressedPovDown(p) <<
//                    GgafDx::Input::isPressedPovLeft(p) <<
//                    GgafDx::Input::isPressedPovRight(p));
                vb_state[p] |= (VB_UI_UP    * (VirtualButton::isPressedVirtualJoyButton(jmap.UI_UP)    ||  GgafDx::Input::isPressedPovUp(p)    ));
                vb_state[p] |= (VB_UI_DOWN  * (VirtualButton::isPressedVirtualJoyButton(jmap.UI_DOWN)  ||  GgafDx::Input::isPressedPovDown(p)  ));
                vb_state[p] |= (VB_UI_LEFT  * (VirtualButton::isPressedVirtualJoyButton(jmap.UI_LEFT)  ||  GgafDx::Input::isPressedPovLeft(p)  ));
                vb_state[p] |= (VB_UI_RIGHT * (VirtualButton::isPressedVirtualJoyButton(jmap.UI_RIGHT) ||  GgafDx::Input::isPressedPovRight(p) ));
            } else {
                vb_state[p] |= (VB_UI_UP    * VirtualButton::isPressedVirtualJoyButton(jmap.UI_UP)   );
                vb_state[p] |= (VB_UI_DOWN  * VirtualButton::isPressedVirtualJoyButton(jmap.UI_DOWN) );
                vb_state[p] |= (VB_UI_LEFT  * VirtualButton::isPressedVirtualJoyButton(jmap.UI_LEFT) );
                vb_state[p] |= (VB_UI_RIGHT * VirtualButton::isPressedVirtualJoyButton(jmap.UI_RIGHT));
            }
            vb_state[p] |= (VB_UI_EXECUTE * VirtualButton::isPressedVirtualJoyButton(jmap.UI_EXECUTE));
            vb_state[p] |= (VB_UI_CANCEL  * VirtualButton::isPressedVirtualJoyButton(jmap.UI_CANCEL));
            vb_state[p] |= (VB_UI_DEBUG * VirtualButton::isPressedVirtualJoyButton(jmap.UI_DEBUG));
            vb_state[p] |= (VB_UI_START   * VirtualButton::isPressedVirtualJoyButton(jmap.UI_START  ));
            vb_state[p] |= (VB_UI_COIN    * VirtualButton::isPressedVirtualJoyButton(jmap.UI_COIN   ));
            vb_state[p] |= (VB_UI_SERVICE * VirtualButton::isPressedVirtualJoyButton(jmap.UI_SERVICE));
            vb_state[p] |= (VB_UI_TEST    * VirtualButton::isPressedVirtualJoyButton(jmap.UI_TEST   ));
        }
    }
    for (int p = 0; p < MAX_JOY_STICK_NUM; p++) {
        _pVBRecord_active->_vb_state[p] = vb_state[p];
    }
    _pRpy->write(_pVBRecord_active->_vb_state); //リプレイ情報記録
    //TODO:DEBUG
    //printDebugState();

}

void VirtualButton::printDebugState() {
    const int bitnum = 32;
    char aChar_strbit_0[bitnum+1];
    char aChar_strbit_1[bitnum+1];
    UTIL::dec2bin(_pVBRecord_active->_vb_state[0], aChar_strbit_0, bitnum);
    UTIL::dec2bin(_pVBRecord_active->_vb_state[1], aChar_strbit_1, bitnum);
    _TRACE_("_vb_state("<<aChar_strbit_0<<","<<aChar_strbit_1<<")");
}
void VirtualButton::clear() {
    VirtualButton::VBRecord* pVBRecord = _pVBRecord_active;
    for (int i = 0; i < VB_MAP_BUFFER; i++) {
        for (int p = 0; p < MAX_JOY_STICK_NUM; p++) {
            pVBRecord->_vb_state[p] = 0;
        }
        pVBRecord = pVBRecord->_next;
    }
}

bool VirtualButton::isPressedVirtualJoyButton(vbj prm_VBJ) {
    int player_no = VBJ_TO_P_N(prm_VBJ);
    vbj_base vbj_base_prm = VBJ_TO_BASE(prm_VBJ);
    if (VBJ_BASE_BUTTON_01 <= vbj_base_prm && vbj_base_prm <= VBJ_BASE_BUTTON_MAX) {
        return GgafDx::Input::isPressedJoyButton(player_no, vbj_base_prm); //rgb_buttonの場合
    } else if ( VBJ_BASE_X_POS_MINUS <= vbj_base_prm && vbj_base_prm <= VBJ_BASE_POV_RIGHT ) {
        return (VirtualButton::_mapVbjBase2Func[vbj_base_prm])(player_no); //XYZ軸上下か、XYZ軸回転＋ーか、POVの方向の場合
    } else {
        return false;
    }
}
vbj VirtualButton::getFirstPushedDownVirtualJoyButton(int prm_player_no) {
    vbj_base VBJ_BASE_pushed_button_no = GgafDx::Input::getFirstPushedDownJoyRgbButton(prm_player_no);
    //0～15 => VBJ_BASE_BUTTON_01 ～VBJ_BASE_BUTTON_15 / -1:何も押されていない
    if (VBJ_BASE_pushed_button_no == -1) {
        if (GgafDx::Input::isPressedJoyXAxisMinus(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_X_POS_MINUS);
        } else if (GgafDx::Input::isPressedJoyXAxisPlus(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_X_POS_PLUS);
        } else if (GgafDx::Input::isPressedJoyYAxisMinus(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_Y_POS_MINUS);
        } else if (GgafDx::Input::isPressedJoyYAxisPlus(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_Y_POS_PLUS);
        } else if (GgafDx::Input::isPressedJoyZAxisMinus(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_Z_POS_MINUS);
        } else if (GgafDx::Input::isPressedJoyZAxisPlus(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_Z_POS_PLUS);
        } else if (GgafDx::Input::isPressedJoyRxMinus(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_X_ROT_MINUS);
        } else if (GgafDx::Input::isPressedJoyRxPlus(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_X_ROT_PLUS);
        } else if (GgafDx::Input::isPressedJoyRyMinus(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_Y_ROT_MINUS);
        } else if (GgafDx::Input::isPressedJoyRyPlus(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_Y_ROT_PLUS);
        } else if (GgafDx::Input::isPressedJoyRzMinus(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_Z_ROT_MINUS);
        } else if (GgafDx::Input::isPressedJoyRzPlus(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_Z_ROT_PLUS);
        } else if (GgafDx::Input::isPressedPovUp(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_POV_UP);
        } else if (GgafDx::Input::isPressedPovDown(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_POV_DOWN);
        } else if (GgafDx::Input::isPressedPovLeft(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_POV_LEFT);
        } else if (GgafDx::Input::isPressedPovRight(prm_player_no)) {
            return BASE_TO_VBJ(prm_player_no, VBJ_BASE_POV_RIGHT);
        } else {
            return -1;
        }
    } else {
        return BASE_TO_VBJ(prm_player_no, VBJ_BASE_pushed_button_no);
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

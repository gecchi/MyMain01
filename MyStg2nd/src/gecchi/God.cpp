#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


VirtualButton* God::_pVbtn_PLAY = NULL;
VirtualButton* God::_pVbtn_UI = NULL;
VirtualButton* God::_pVbtn_Active = NULL;
VirtualButton* God::_pVbtn_Active_next_frame = NULL;

God::God(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary) : DefaultGod(prm_hInstance, prm_pHWndPrimary, prm_pHWndSecondary) {
    _pDispatcherManager = NEW DispatcherManager("DispatcherManager");
    _pSpline3DManager = NEW Spline3DManager("Spline3DManager");
    _pSplineManager = NEW SplineManager("SplineManager");

    God::_pVbtn_PLAY = NEW VirtualButton("VB_PLAY.rep");
    God::_pVbtn_UI   = NEW VirtualButton("VB_UI.rep");
    God::_pVbtn_Active = God::_pVbtn_UI;
    God::_pVbtn_Active_next_frame = God::_pVbtn_UI;

    //仮想ボタンを本ゲーム用に上書きして再定義
    VirtualButton::_tagKeymap.BUTTON1    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_SHOT1)      ];
    VirtualButton::_tagKeymap.BUTTON2    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_SHOT2)      ];
    VirtualButton::_tagKeymap.BUTTON3    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_OPTION)     ];
    VirtualButton::_tagKeymap.BUTTON4    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_VIEW)       ];
    VirtualButton::_tagKeymap.BUTTON5    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_TURBO)      ];
    VirtualButton::_tagKeymap.BUTTON6    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_POWERUP)    ];
    VirtualButton::_tagKeymap.BUTTON7    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_BUTTON7)    ];
    VirtualButton::_tagKeymap.BUTTON8    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_BUTTON8)    ];
    VirtualButton::_tagKeymap.PAUSE      = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_PAUSE)      ];
    VirtualButton::_tagKeymap.UP         = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_UP)         ];
    VirtualButton::_tagKeymap.DOWN       = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_DOWN)       ];
    VirtualButton::_tagKeymap.LEFT       = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_LEFT)       ];
    VirtualButton::_tagKeymap.RIGHT      = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_RIGHT)      ];
    VirtualButton::_tagKeymap.UI_UP      = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_UI_UP)      ];
    VirtualButton::_tagKeymap.UI_DOWN    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_UI_DOWN)    ];
    VirtualButton::_tagKeymap.UI_LEFT    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_UI_LEFT)    ];
    VirtualButton::_tagKeymap.UI_RIGHT   = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_UI_RIGHT)   ];
    VirtualButton::_tagKeymap.UI_EXECUTE = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_UI_EXECUTE) ];
    VirtualButton::_tagKeymap.UI_CANCEL  = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_UI_CANCEL)  ];
    VirtualButton::_tagKeymap.UI_DEBUG   = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_KEY_UI_DEBUG)   ];

    VirtualButton::_tagJoymap.BUTTON1    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_JOY_SHOT1)      ];
    VirtualButton::_tagJoymap.BUTTON2    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_JOY_SHOT2)      ];
    VirtualButton::_tagJoymap.BUTTON3    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_JOY_OPTION)     ];
    VirtualButton::_tagJoymap.BUTTON4    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_JOY_VIEW)       ];
    VirtualButton::_tagJoymap.BUTTON5    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_JOY_TURBO)      ];
    VirtualButton::_tagJoymap.BUTTON6    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_JOY_POWERUP)    ];
    VirtualButton::_tagJoymap.BUTTON7    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_JOY_BUTTON7)    ];
    VirtualButton::_tagJoymap.BUTTON8    = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_JOY_BUTTON8)    ];
    VirtualButton::_tagJoymap.PAUSE      = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_JOY_PAUSE)      ];
    VirtualButton::_tagJoymap.UI_EXECUTE = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_JOY_UI_EXECUTE) ];
    VirtualButton::_tagJoymap.UI_CANCEL  = VirtualButton::_mapDIK[ CFG_PROPERTY(MY_JOY_UI_CANCEL)  ];
}

GgafUniverse* God::createUniverse() {
    Camera* pCamera = NEW Camera("CAMERA");    //FovX視野角80度、深さ×GAME_SPACE_DEPTH

    Universe* pUniverse = NEW Universe("MYUNIVERSE", pCamera);
    return (GgafUniverse*)pUniverse;
}

void God::clean() {
    if (!_was_cleaned) {

        if (!VB_PLAY->_is_replaying) {
            _TRACE_("write VB_PLAY_LAST.rep");
            VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST.rep");
        }
        if (!VB_UI->_is_replaying) {
            _TRACE_("write VB_UI_LAST.rep");
            VB_UI->_pRpy->outputFile("VB_UI_LAST.rep");
        }
        _TRACE_("God::clean() begin");
        DefaultGod::clean();
        DELETE_IMPOSSIBLE_NULL(_pVbtn_PLAY);
        DELETE_IMPOSSIBLE_NULL(_pVbtn_UI);
        DELETE_IMPOSSIBLE_NULL(_pDispatcherManager);
        DELETE_IMPOSSIBLE_NULL(_pSpline3DManager);
        DELETE_IMPOSSIBLE_NULL(_pSplineManager);
        _TRACE_("God::clean() end");
    }
}

void God::oops() {
    VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_Oops.rep");
    VB_UI->_pRpy->outputFile("VB_UI_LASTT_Oops.rep");
    DefaultGod::oops(); //上位のしまったへ
}

God::~God() {
    clean();
    _was_cleaned = true;
}

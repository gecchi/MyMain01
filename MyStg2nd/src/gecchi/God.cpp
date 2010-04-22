#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


DispatcherManager God::_dispatcherManager = DispatcherManager("DispatcherManager");
VirtualButton* God::_pVbtn_PLAY = NULL;
VirtualButton* God::_pVbtn_UI = NULL;
God::God(HINSTANCE prm_hInstance, HWND _hWnd) : DefaultGod(prm_hInstance, _hWnd) {
    God::_pVbtn_PLAY = NEW VirtualButton();
    God::_pVbtn_UI   = NEW VirtualButton();


    //‰¼‘zƒ{ƒ^ƒ“‚ğ–{AƒQ[ƒ€—p‚Éã‘‚«‚µ‚ÄÄ’è‹`
    VirtualButton::_tagKeymap.BUTTON1    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_SHOT1)      ];
    VirtualButton::_tagKeymap.BUTTON2    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_SHOT2)      ];
    VirtualButton::_tagKeymap.BUTTON3    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_OPTION)     ];
    VirtualButton::_tagKeymap.BUTTON4    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_ZMOVE)      ];
    VirtualButton::_tagKeymap.BUTTON5    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_TURBO)      ];
    VirtualButton::_tagKeymap.BUTTON6    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_BUTTON6)    ];
    VirtualButton::_tagKeymap.PAUSE      = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_PAUSE)      ];
    VirtualButton::_tagKeymap.UP         = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UP)         ];
    VirtualButton::_tagKeymap.DOWN       = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_DOWN)       ];
    VirtualButton::_tagKeymap.LEFT       = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_LEFT)       ];
    VirtualButton::_tagKeymap.RIGHT      = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_RIGHT)      ];
    VirtualButton::_tagKeymap.UI_UP      = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UI_UP)      ];
    VirtualButton::_tagKeymap.UI_DOWN    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UI_DOWN)    ];
    VirtualButton::_tagKeymap.UI_LEFT    = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UI_LEFT)    ];
    VirtualButton::_tagKeymap.UI_RIGHT   = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UI_RIGHT)   ];
    VirtualButton::_tagKeymap.UI_EXECUTE = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UI_EXECUTE) ];
    VirtualButton::_tagKeymap.UI_CANCEL  = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UI_CANCEL)  ];
    VirtualButton::_tagKeymap.UI_DEBUG   = VirtualButton::_mapDIK[ PROPERTY(MY_KEY_UI_DEBUG)   ];

    VirtualButton::_tagJoymap.BUTTON1    = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_SHOT1)      ];
    VirtualButton::_tagJoymap.BUTTON2    = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_SHOT2)      ];
    VirtualButton::_tagJoymap.BUTTON3    = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_OPTION)     ];
    VirtualButton::_tagJoymap.BUTTON4    = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_ZMOVE)      ];
    VirtualButton::_tagJoymap.BUTTON5    = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_TURBO)      ];
    VirtualButton::_tagJoymap.BUTTON6    = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_BUTTON6)    ];
    VirtualButton::_tagJoymap.PAUSE      = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_PAUSE)      ];
    VirtualButton::_tagJoymap.UI_EXECUTE = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_UI_EXECUTE) ];
    VirtualButton::_tagJoymap.UI_CANCEL  = VirtualButton::_mapDIK[ PROPERTY(MY_JOY_UI_CANCEL)  ];
}

GgafUniverse* God::createUniverse() {
    Universe* pUniverse = NEW Universe("MYUNIVERSE");
    return (GgafUniverse*)pUniverse;
}

God::~God() {
    DELETE_IMPOSSIBLE_NULL(_pVbtn_PLAY);
    DELETE_IMPOSSIBLE_NULL(_pVbtn_UI);

    GgafFactory::_is_working_flg = false;
    for (int i = 0; GgafFactory::_was_finished_flg == false; i++) {
        Sleep(60); //Hê‚ª—‚¿’…‚­‚Ü‚Å‘Ò‚Â
        _TRACE_("God::~God() Hê‰Ò“®’â~‘Ò‚¿");
        if (i > 2000) {
            _TRACE_("God::~God() ‚Q•ª‘Ò‹@‚µ‚Ü‚µ‚½‚ªAHê‚©‚ç”½‰‚ª‚ ‚è‚Ü‚¹‚ñBbreak‚µ‚Ü‚·B—v’²¸");
        }
    }
    _TRACE_("God::~God() Hê’â~");


    _pUniverse->dump();
}

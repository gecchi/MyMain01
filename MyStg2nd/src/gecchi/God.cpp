#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

God::God(HINSTANCE prm_hInstance, HWND _hWnd) : DefaultGod(prm_hInstance, _hWnd) {
    VB::init();

    //仮想ボタン再定義
    VB::_tagKeymap.BUTTON1    = VB::_mapDIK[ PROPERTY(MY_KEY_SHOT1)      ];
    VB::_tagKeymap.BUTTON2    = VB::_mapDIK[ PROPERTY(MY_KEY_SHOT2)      ];
    VB::_tagKeymap.BUTTON3    = VB::_mapDIK[ PROPERTY(MY_KEY_OPTION)     ];
    VB::_tagKeymap.BUTTON4    = VB::_mapDIK[ PROPERTY(MY_KEY_ZMOVE)      ];
    VB::_tagKeymap.BUTTON5    = VB::_mapDIK[ PROPERTY(MY_KEY_BUTTON5)    ];
    VB::_tagKeymap.BUTTON6    = VB::_mapDIK[ PROPERTY(MY_KEY_BUTTON6)    ];
    VB::_tagKeymap.PAUSE      = VB::_mapDIK[ PROPERTY(MY_KEY_PAUSE)      ];
    VB::_tagKeymap.UP         = VB::_mapDIK[ PROPERTY(MY_KEY_UP)         ];
    VB::_tagKeymap.DOWN       = VB::_mapDIK[ PROPERTY(MY_KEY_DOWN)       ];
    VB::_tagKeymap.LEFT       = VB::_mapDIK[ PROPERTY(MY_KEY_LEFT)       ];
    VB::_tagKeymap.RIGHT      = VB::_mapDIK[ PROPERTY(MY_KEY_RIGHT)      ];
    VB::_tagKeymap.UI_UP      = VB::_mapDIK[ PROPERTY(MY_KEY_UI_UP)      ];
    VB::_tagKeymap.UI_DOWN    = VB::_mapDIK[ PROPERTY(MY_KEY_UI_DOWN)    ];
    VB::_tagKeymap.UI_LEFT    = VB::_mapDIK[ PROPERTY(MY_KEY_UI_LEFT)    ];
    VB::_tagKeymap.UI_RIGHT   = VB::_mapDIK[ PROPERTY(MY_KEY_UI_RIGHT)   ];
    VB::_tagKeymap.UI_EXECUTE = VB::_mapDIK[ PROPERTY(MY_KEY_UI_EXECUTE) ];
    VB::_tagKeymap.UI_CANCEL  = VB::_mapDIK[ PROPERTY(MY_KEY_UI_CANCEL)  ];
    VB::_tagKeymap.UI_DEBUG   = VB::_mapDIK[ PROPERTY(MY_KEY_UI_DEBUG)   ];

    VB::_tagJoymap.BUTTON1    = VB::_mapDIK[ PROPERTY(MY_JOY_SHOT1)      ];
    VB::_tagJoymap.BUTTON2    = VB::_mapDIK[ PROPERTY(MY_JOY_SHOT2)      ];
    VB::_tagJoymap.BUTTON3    = VB::_mapDIK[ PROPERTY(MY_JOY_OPTION)     ];
    VB::_tagJoymap.BUTTON4    = VB::_mapDIK[ PROPERTY(MY_JOY_ZMOVE)      ];
    VB::_tagJoymap.BUTTON5    = VB::_mapDIK[ PROPERTY(MY_JOY_BUTTON5)    ];
    VB::_tagJoymap.BUTTON6    = VB::_mapDIK[ PROPERTY(MY_JOY_BUTTON6)    ];
    VB::_tagJoymap.PAUSE      = VB::_mapDIK[ PROPERTY(MY_JOY_PAUSE)      ];
    VB::_tagJoymap.UI_EXECUTE = VB::_mapDIK[ PROPERTY(MY_JOY_UI_EXECUTE) ];
    VB::_tagJoymap.UI_CANCEL  = VB::_mapDIK[ PROPERTY(MY_JOY_UI_CANCEL)  ];

}

GgafUniverse* God::createUniverse() {
    Universe* pUniverse = NEW Universe("MYUNIVERSE");
    return (GgafUniverse*)pUniverse;
}

God::~God() {
    VB::clear();
    _pUniverse->dump();
}

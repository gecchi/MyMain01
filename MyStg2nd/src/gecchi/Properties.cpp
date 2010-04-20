#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

string* Properties::MY_KEY_SHOT1 = NULL;
string* Properties::MY_KEY_SHOT2 = NULL;
string* Properties::MY_KEY_OPTION = NULL;
string* Properties::MY_KEY_ZMOVE = NULL;
string* Properties::MY_KEY_TURBO = NULL;
string* Properties::MY_KEY_BUTTON6 = NULL;
string* Properties::MY_KEY_PAUSE = NULL;
string* Properties::MY_KEY_UP = NULL;
string* Properties::MY_KEY_DOWN = NULL;
string* Properties::MY_KEY_LEFT = NULL;
string* Properties::MY_KEY_RIGHT = NULL;
string* Properties::MY_KEY_UI_UP = NULL;
string* Properties::MY_KEY_UI_DOWN = NULL;
string* Properties::MY_KEY_UI_LEFT = NULL;
string* Properties::MY_KEY_UI_RIGHT = NULL;
string* Properties::MY_KEY_UI_EXECUTE = NULL;
string* Properties::MY_KEY_UI_CANCEL = NULL;
string* Properties::MY_KEY_UI_DEBUG = NULL;
string* Properties::MY_JOY_SHOT1 = NULL;
string* Properties::MY_JOY_SHOT2 = NULL;
string* Properties::MY_JOY_OPTION = NULL;
string* Properties::MY_JOY_ZMOVE = NULL;
string* Properties::MY_JOY_TURBO = NULL;
string* Properties::MY_JOY_BUTTON6 = NULL;
string* Properties::MY_JOY_PAUSE = NULL;
string* Properties::MY_JOY_UI_EXECUTE = NULL;
string* Properties::MY_JOY_UI_CANCEL = NULL;


void Properties::load(string prm_ini_filename) {
    GgafDx9Properties::load(prm_ini_filename);
    MY_KEY_SHOT1      = getStr("MY_KEY_SHOT1");
    MY_KEY_SHOT2      = getStr("MY_KEY_SHOT2");
    MY_KEY_OPTION     = getStr("MY_KEY_OPTION");
    MY_KEY_ZMOVE      = getStr("MY_KEY_ZMOVE");
    MY_KEY_TURBO    = getStr("MY_KEY_TURBO");
    MY_KEY_BUTTON6    = getStr("MY_KEY_BUTTON6");
    MY_KEY_PAUSE      = getStr("MY_KEY_PAUSE");
    MY_KEY_UP         = getStr("MY_KEY_UP");
    MY_KEY_DOWN       = getStr("MY_KEY_DOWN");
    MY_KEY_LEFT       = getStr("MY_KEY_LEFT");
    MY_KEY_RIGHT      = getStr("MY_KEY_RIGHT");
    MY_KEY_UI_UP      = getStr("MY_KEY_UI_UP");
    MY_KEY_UI_DOWN    = getStr("MY_KEY_UI_DOWN");
    MY_KEY_UI_LEFT    = getStr("MY_KEY_UI_LEFT");
    MY_KEY_UI_RIGHT   = getStr("MY_KEY_UI_RIGHT");
    MY_KEY_UI_EXECUTE = getStr("MY_KEY_UI_EXECUTE");
    MY_KEY_UI_CANCEL  = getStr("MY_KEY_UI_CANCEL");
    MY_KEY_UI_DEBUG   = getStr("MY_KEY_UI_DEBUG");
    MY_JOY_SHOT1      = getStr("MY_JOY_SHOT1");
    MY_JOY_SHOT2      = getStr("MY_JOY_SHOT2");
    MY_JOY_OPTION     = getStr("MY_JOY_OPTION");
    MY_JOY_ZMOVE      = getStr("MY_JOY_ZMOVE");
    MY_JOY_TURBO    = getStr("MY_JOY_TURBO");
    MY_JOY_BUTTON6    = getStr("MY_JOY_BUTTON6");
    MY_JOY_PAUSE      = getStr("MY_JOY_PAUSE");
    MY_JOY_UI_EXECUTE = getStr("MY_JOY_UI_EXECUTE");
    MY_JOY_UI_CANCEL  = getStr("MY_JOY_UI_CANCEL");


    _TRACE_("PROPERTY(MY_KEY_SHOT1)="<<PROPERTY(MY_KEY_SHOT1));
    _TRACE_("PROPERTY(MY_KEY_SHOT2)="<<PROPERTY(MY_KEY_SHOT2));
    _TRACE_("PROPERTY(MY_KEY_OPTION)="<<PROPERTY(MY_KEY_OPTION));
    _TRACE_("PROPERTY(MY_KEY_ZMOVE)="<<PROPERTY(MY_KEY_ZMOVE));
    _TRACE_("PROPERTY(MY_KEY_TURBO)="<<PROPERTY(MY_KEY_TURBO));
    _TRACE_("PROPERTY(MY_KEY_BUTTON6)="<<PROPERTY(MY_KEY_BUTTON6));
    _TRACE_("PROPERTY(MY_KEY_PAUSE)="<<PROPERTY(MY_KEY_PAUSE));
    _TRACE_("PROPERTY(MY_KEY_UP)="<<PROPERTY(MY_KEY_UP));
    _TRACE_("PROPERTY(MY_KEY_DOWN)="<<PROPERTY(MY_KEY_DOWN));
    _TRACE_("PROPERTY(MY_KEY_LEFT)="<<PROPERTY(MY_KEY_LEFT));
    _TRACE_("PROPERTY(MY_KEY_RIGHT)="<<PROPERTY(MY_KEY_RIGHT));
    _TRACE_("PROPERTY(MY_KEY_UI_UP)="<<PROPERTY(MY_KEY_UI_UP));
    _TRACE_("PROPERTY(MY_KEY_UI_DOWN)="<<PROPERTY(MY_KEY_UI_DOWN));
    _TRACE_("PROPERTY(MY_KEY_UI_LEFT)="<<PROPERTY(MY_KEY_UI_LEFT));
    _TRACE_("PROPERTY(MY_KEY_UI_RIGHT)="<<PROPERTY(MY_KEY_UI_RIGHT));
    _TRACE_("PROPERTY(MY_KEY_UI_EXECUTE)="<<PROPERTY(MY_KEY_UI_EXECUTE));
    _TRACE_("PROPERTY(MY_KEY_UI_CANCEL)="<<PROPERTY(MY_KEY_UI_CANCEL));
    _TRACE_("PROPERTY(MY_KEY_UI_DEBUG)="<<PROPERTY(MY_KEY_UI_DEBUG));
    _TRACE_("PROPERTY(MY_JOY_SHOT1)="<<PROPERTY(MY_JOY_SHOT1));
    _TRACE_("PROPERTY(MY_JOY_SHOT2)="<<PROPERTY(MY_JOY_SHOT2));
    _TRACE_("PROPERTY(MY_JOY_OPTION)="<<PROPERTY(MY_JOY_OPTION));
    _TRACE_("PROPERTY(MY_JOY_ZMOVE)="<<PROPERTY(MY_JOY_ZMOVE));
    _TRACE_("PROPERTY(MY_JOY_TURBO)="<<PROPERTY(MY_JOY_TURBO));
    _TRACE_("PROPERTY(MY_JOY_BUTTON6)="<<PROPERTY(MY_JOY_BUTTON6));
    _TRACE_("PROPERTY(MY_JOY_PAUSE)="<<PROPERTY(MY_JOY_PAUSE));
    _TRACE_("PROPERTY(MY_JOY_UI_EXECUTE)="<<PROPERTY(MY_JOY_UI_EXECUTE));
    _TRACE_("PROPERTY(MY_JOY_UI_CANCEL)="<<PROPERTY(MY_JOY_UI_CANCEL));
}

void Properties::clean() {
    GgafDx9Properties::clean();
    DELETE_IMPOSSIBLE_NULL(MY_KEY_SHOT1);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_SHOT2);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_OPTION);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_ZMOVE);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_TURBO);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_BUTTON6);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_PAUSE);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_UP);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_DOWN);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_LEFT);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_RIGHT);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_UI_UP);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_UI_DOWN);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_UI_LEFT);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_UI_RIGHT);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_UI_EXECUTE);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_UI_CANCEL);
    DELETE_IMPOSSIBLE_NULL(MY_KEY_UI_DEBUG);
    DELETE_IMPOSSIBLE_NULL(MY_JOY_SHOT1);
    DELETE_IMPOSSIBLE_NULL(MY_JOY_SHOT2);
    DELETE_IMPOSSIBLE_NULL(MY_JOY_OPTION);
    DELETE_IMPOSSIBLE_NULL(MY_JOY_ZMOVE);
    DELETE_IMPOSSIBLE_NULL(MY_JOY_TURBO);
    DELETE_IMPOSSIBLE_NULL(MY_JOY_BUTTON6);
    DELETE_IMPOSSIBLE_NULL(MY_JOY_PAUSE);
    DELETE_IMPOSSIBLE_NULL(MY_JOY_UI_EXECUTE);
    DELETE_IMPOSSIBLE_NULL(MY_JOY_UI_CANCEL);
}

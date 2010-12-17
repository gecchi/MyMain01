#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

string Properties::MY_KEY_SHOT1 = "";
string Properties::MY_KEY_SHOT2 = "";
string Properties::MY_KEY_OPTION = "";
string Properties::MY_KEY_VIEW = "";
string Properties::MY_KEY_TURBO = "";
string Properties::MY_KEY_POWERUP = "";
string Properties::MY_KEY_BUTTON7 = "";
string Properties::MY_KEY_BUTTON8 = "";
string Properties::MY_KEY_PAUSE = "";
string Properties::MY_KEY_UP = "";
string Properties::MY_KEY_DOWN = "";
string Properties::MY_KEY_LEFT = "";
string Properties::MY_KEY_RIGHT = "";
string Properties::MY_KEY_UI_UP = "";
string Properties::MY_KEY_UI_DOWN = "";
string Properties::MY_KEY_UI_LEFT = "";
string Properties::MY_KEY_UI_RIGHT = "";
string Properties::MY_KEY_UI_EXECUTE = "";
string Properties::MY_KEY_UI_CANCEL = "";
string Properties::MY_KEY_UI_DEBUG = "";
string Properties::MY_JOY_SHOT1 = "";
string Properties::MY_JOY_SHOT2 = "";
string Properties::MY_JOY_OPTION = "";
string Properties::MY_JOY_VIEW = "";
string Properties::MY_JOY_TURBO = "";
string Properties::MY_JOY_POWERUP = "";
string Properties::MY_JOY_BUTTON7 = "";
string Properties::MY_JOY_BUTTON8 = "";
string Properties::MY_JOY_PAUSE = "";
string Properties::MY_JOY_UI_EXECUTE = "";
string Properties::MY_JOY_UI_CANCEL = "";


void Properties::load(string prm_ini_filename) {
    StgProperties::load(prm_ini_filename);
    Properties::MY_KEY_SHOT1      = getStr("MY_KEY_SHOT1");
    Properties::MY_KEY_SHOT2      = getStr("MY_KEY_SHOT2");
    Properties::MY_KEY_OPTION     = getStr("MY_KEY_OPTION");
    Properties::MY_KEY_VIEW       = getStr("MY_KEY_VIEW");
    Properties::MY_KEY_TURBO      = getStr("MY_KEY_TURBO");
    Properties::MY_KEY_POWERUP    = getStr("MY_KEY_POWERUP");
    Properties::MY_KEY_BUTTON7    = getStr("MY_KEY_BUTTON7");
    Properties::MY_KEY_BUTTON8    = getStr("MY_KEY_BUTTON8");
    Properties::MY_KEY_PAUSE      = getStr("MY_KEY_PAUSE");
    Properties::MY_KEY_UP         = getStr("MY_KEY_UP");
    Properties::MY_KEY_DOWN       = getStr("MY_KEY_DOWN");
    Properties::MY_KEY_LEFT       = getStr("MY_KEY_LEFT");
    Properties::MY_KEY_RIGHT      = getStr("MY_KEY_RIGHT");
    Properties::MY_KEY_UI_UP      = getStr("MY_KEY_UI_UP");
    Properties::MY_KEY_UI_DOWN    = getStr("MY_KEY_UI_DOWN");
    Properties::MY_KEY_UI_LEFT    = getStr("MY_KEY_UI_LEFT");
    Properties::MY_KEY_UI_RIGHT   = getStr("MY_KEY_UI_RIGHT");
    Properties::MY_KEY_UI_EXECUTE = getStr("MY_KEY_UI_EXECUTE");
    Properties::MY_KEY_UI_CANCEL  = getStr("MY_KEY_UI_CANCEL");
    Properties::MY_KEY_UI_DEBUG   = getStr("MY_KEY_UI_DEBUG");
    Properties::MY_JOY_SHOT1      = getStr("MY_JOY_SHOT1");
    Properties::MY_JOY_SHOT2      = getStr("MY_JOY_SHOT2");
    Properties::MY_JOY_OPTION     = getStr("MY_JOY_OPTION");
    Properties::MY_JOY_VIEW       = getStr("MY_JOY_VIEW");
    Properties::MY_JOY_TURBO      = getStr("MY_JOY_TURBO");
    Properties::MY_JOY_POWERUP    = getStr("MY_JOY_POWERUP");
    Properties::MY_JOY_BUTTON7    = getStr("MY_JOY_BUTTON7");
    Properties::MY_JOY_BUTTON8    = getStr("MY_JOY_BUTTON8");
    Properties::MY_JOY_PAUSE      = getStr("MY_JOY_PAUSE");
    Properties::MY_JOY_UI_EXECUTE = getStr("MY_JOY_UI_EXECUTE");
    Properties::MY_JOY_UI_CANCEL  = getStr("MY_JOY_UI_CANCEL");

    _TRACE_("Properties::MY_KEY_SHOT1="<<Properties::MY_KEY_SHOT1);
    _TRACE_("Properties::MY_KEY_SHOT2="<<Properties::MY_KEY_SHOT2);
    _TRACE_("Properties::MY_KEY_OPTION="<<Properties::MY_KEY_OPTION);
    _TRACE_("Properties::MY_KEY_VIEW="<<Properties::MY_KEY_VIEW);
    _TRACE_("Properties::MY_KEY_TURBO="<<Properties::MY_KEY_TURBO);
    _TRACE_("Properties::MY_KEY_POWERUP="<<Properties::MY_KEY_POWERUP);
    _TRACE_("Properties::MY_KEY_BUTTON7="<<Properties::MY_KEY_BUTTON7);
    _TRACE_("Properties::MY_KEY_BUTTON8="<<Properties::MY_KEY_BUTTON8);
    _TRACE_("Properties::MY_KEY_PAUSE="<<Properties::MY_KEY_PAUSE);
    _TRACE_("Properties::MY_KEY_UP="<<Properties::MY_KEY_UP);
    _TRACE_("Properties::MY_KEY_DOWN="<<Properties::MY_KEY_DOWN);
    _TRACE_("Properties::MY_KEY_LEFT="<<Properties::MY_KEY_LEFT);
    _TRACE_("Properties::MY_KEY_RIGHT="<<Properties::MY_KEY_RIGHT);
    _TRACE_("Properties::MY_KEY_UI_UP="<<Properties::MY_KEY_UI_UP);
    _TRACE_("Properties::MY_KEY_UI_DOWN="<<Properties::MY_KEY_UI_DOWN);
    _TRACE_("Properties::MY_KEY_UI_LEFT="<<Properties::MY_KEY_UI_LEFT);
    _TRACE_("Properties::MY_KEY_UI_RIGHT="<<Properties::MY_KEY_UI_RIGHT);
    _TRACE_("Properties::MY_KEY_UI_EXECUTE="<<Properties::MY_KEY_UI_EXECUTE);
    _TRACE_("Properties::MY_KEY_UI_CANCEL="<<Properties::MY_KEY_UI_CANCEL);
    _TRACE_("Properties::MY_KEY_UI_DEBUG="<<Properties::MY_KEY_UI_DEBUG);
    _TRACE_("Properties::MY_JOY_SHOT1="<<Properties::MY_JOY_SHOT1);
    _TRACE_("Properties::MY_JOY_SHOT2="<<Properties::MY_JOY_SHOT2);
    _TRACE_("Properties::MY_JOY_OPTION="<<Properties::MY_JOY_OPTION);
    _TRACE_("Properties::MY_JOY_VIEW="<<Properties::MY_JOY_VIEW);
    _TRACE_("Properties::MY_JOY_TURBO="<<Properties::MY_JOY_TURBO);
    _TRACE_("Properties::MY_JOY_POWERUP="<<Properties::MY_JOY_POWERUP);
    _TRACE_("Properties::MY_JOY_BUTTON7="<<Properties::MY_JOY_BUTTON7);
    _TRACE_("Properties::MY_JOY_BUTTON8="<<Properties::MY_JOY_BUTTON8);
    _TRACE_("Properties::MY_JOY_PAUSE="<<Properties::MY_JOY_PAUSE);
    _TRACE_("Properties::MY_JOY_UI_EXECUTE="<<Properties::MY_JOY_UI_EXECUTE);
    _TRACE_("Properties::MY_JOY_UI_CANCEL="<<Properties::MY_JOY_UI_CANCEL);}

void Properties::clean() {
    StgProperties::clean();
}

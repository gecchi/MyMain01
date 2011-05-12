#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

bool GgafDx9Properties::FULL_SCREEN = 0;
bool GgafDx9Properties::DUAL_DISPLAY = 0;
int GgafDx9Properties::GAME_BUFFER_WIDTH = 0;
int GgafDx9Properties::GAME_BUFFER_HEIGHT = 0;
float GgafDx9Properties::GAME_SPACE_DEPTH = 0;

int GgafDx9Properties::SINGLE_DISPLAY_WINDOW_WIDTH = 0;
int GgafDx9Properties::SINGLE_DISPLAY_WINDOW_HEIGHT = 0;
int GgafDx9Properties::DUAL_DISPLAY_WINDOW1_WIDTH = 0;
int GgafDx9Properties::DUAL_DISPLAY_WINDOW1_HEIGHT = 0;
int GgafDx9Properties::DUAL_DISPLAY_WINDOW2_WIDTH = 0;
int GgafDx9Properties::DUAL_DISPLAY_WINDOW2_HEIGHT = 0;
int GgafDx9Properties::SINGLE_DISPLAY_FULL_SCREEN_WIDTH = 0;
int GgafDx9Properties::SINGLE_DISPLAY_FULL_SCREEN_HEIGHT = 0;
int GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN1_WIDTH = 0;
int GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN1_HEIGHT = 0;
int GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN2_WIDTH = 0;
int GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN2_HEIGHT = 0;

bool GgafDx9Properties::FIXED_VIEW_ASPECT = false;
bool GgafDx9Properties::SWAP_DISPLAY = false;

int GgafDx9Properties::MASTER_VOLUME;
int GgafDx9Properties::BGM_VOLUME;
int GgafDx9Properties::SE_VOLUME;
string GgafDx9Properties::DIR_MESH_MODEL = "";
string GgafDx9Properties::DIR_SPRITE_MODEL = "";
string GgafDx9Properties::DIR_TEXTURE = "";
string GgafDx9Properties::DIR_EFFECT = "";
string GgafDx9Properties::DIR_OGG = "";
string GgafDx9Properties::DIR_WAVE = "";

void GgafDx9Properties::load(string prm_ini_filename) {
    GgafProperties::load(prm_ini_filename);

    GgafDx9Properties::FULL_SCREEN = getBool("FULL_SCREEN");
    GgafDx9Properties::DUAL_DISPLAY = getBool("DUAL_DISPLAY");
    GgafDx9Properties::GAME_BUFFER_WIDTH = getInt("GAME_BUFFER_WIDTH");
    GgafDx9Properties::GAME_BUFFER_HEIGHT = getInt("GAME_BUFFER_HEIGHT");
    GgafDx9Properties::GAME_SPACE_DEPTH = getFloat("GAME_SPACE_DEPTH");

    GgafDx9Properties::SINGLE_DISPLAY_WINDOW_WIDTH       = getInt("SINGLE_DISPLAY_WINDOW_WIDTH");
    GgafDx9Properties::SINGLE_DISPLAY_WINDOW_HEIGHT      = getInt("SINGLE_DISPLAY_WINDOW_HEIGHT");
    GgafDx9Properties::DUAL_DISPLAY_WINDOW1_WIDTH        = getInt("DUAL_DISPLAY_WINDOW1_WIDTH");
    GgafDx9Properties::DUAL_DISPLAY_WINDOW1_HEIGHT       = getInt("DUAL_DISPLAY_WINDOW1_HEIGHT");
    GgafDx9Properties::DUAL_DISPLAY_WINDOW2_WIDTH        = getInt("DUAL_DISPLAY_WINDOW2_WIDTH");
    GgafDx9Properties::DUAL_DISPLAY_WINDOW2_HEIGHT       = getInt("DUAL_DISPLAY_WINDOW2_HEIGHT");
    GgafDx9Properties::SINGLE_DISPLAY_FULL_SCREEN_WIDTH  = getInt("SINGLE_DISPLAY_FULL_SCREEN_WIDTH");
    GgafDx9Properties::SINGLE_DISPLAY_FULL_SCREEN_HEIGHT = getInt("SINGLE_DISPLAY_FULL_SCREEN_HEIGHT");
    GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN1_WIDTH   = getInt("DUAL_DISPLAY_FULL_SCREEN1_WIDTH");
    GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN1_HEIGHT  = getInt("DUAL_DISPLAY_FULL_SCREEN1_HEIGHT");
    GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN2_WIDTH   = getInt("DUAL_DISPLAY_FULL_SCREEN2_WIDTH");
    GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN2_HEIGHT  = getInt("DUAL_DISPLAY_FULL_SCREEN2_HEIGHT");


    GgafDx9Properties::FIXED_VIEW_ASPECT = getBool("FIXED_VIEW_ASPECT");
    GgafDx9Properties::SWAP_DISPLAY = getBool("SWAP_DISPLAY");
    GgafDx9Properties::MASTER_VOLUME = getInt("MASTER_VOLUME");
    GgafDx9Properties::BGM_VOLUME = getInt("BGM_VOLUME");
    GgafDx9Properties::SE_VOLUME = getInt("SE_VOLUME");

    GgafDx9Properties::DIR_MESH_MODEL = getStr("DIR_MESH_MODEL");
    GgafDx9Properties::DIR_SPRITE_MODEL = getStr("DIR_SPRITE_MODEL");
    GgafDx9Properties::DIR_TEXTURE = getStr("DIR_TEXTURE");
    GgafDx9Properties::DIR_EFFECT = getStr("DIR_EFFECT");
    GgafDx9Properties::DIR_OGG = getStr("DIR_OGG");
    GgafDx9Properties::DIR_WAVE = getStr("DIR_WAVE");

    _TRACE_("GgafDx9Properties::FULL_SCREEN="<<GgafDx9Properties::FULL_SCREEN);
    _TRACE_("GgafDx9Properties::DUAL_DISPLAY="<<GgafDx9Properties::DUAL_DISPLAY);
    _TRACE_("GgafDx9Properties::GAME_BUFFER_WIDTH="<<GgafDx9Properties::GAME_BUFFER_WIDTH);
    _TRACE_("GgafDx9Properties::GAME_SPACE_DEPTH="<<GgafDx9Properties::GAME_SPACE_DEPTH);
    _TRACE_("GgafDx9Properties::GAME_BUFFER_HEIGHT="<<GgafDx9Properties::GAME_BUFFER_HEIGHT);

    _TRACE_("GgafDx9Properties::SINGLE_DISPLAY_WINDOW_WIDTH="<<GgafDx9Properties::SINGLE_DISPLAY_WINDOW_WIDTH);
    _TRACE_("GgafDx9Properties::SINGLE_DISPLAY_WINDOW_HEIGHT="<<GgafDx9Properties::SINGLE_DISPLAY_WINDOW_HEIGHT);
    _TRACE_("GgafDx9Properties::DUAL_DISPLAY_WINDOW1_WIDTH="<<GgafDx9Properties::DUAL_DISPLAY_WINDOW1_WIDTH);
    _TRACE_("GgafDx9Properties::DUAL_DISPLAY_WINDOW1_HEIGHT="<<GgafDx9Properties::DUAL_DISPLAY_WINDOW1_HEIGHT);
    _TRACE_("GgafDx9Properties::DUAL_DISPLAY_WINDOW2_WIDTH="<<GgafDx9Properties::DUAL_DISPLAY_WINDOW2_WIDTH);
    _TRACE_("GgafDx9Properties::DUAL_DISPLAY_WINDOW2_HEIGHT="<<GgafDx9Properties::DUAL_DISPLAY_WINDOW2_HEIGHT);
    _TRACE_("GgafDx9Properties::SINGLE_DISPLAY_FULL_SCREEN_WIDTH="<<GgafDx9Properties::SINGLE_DISPLAY_FULL_SCREEN_WIDTH);
    _TRACE_("GgafDx9Properties::SINGLE_DISPLAY_FULL_SCREEN_HEIGHT="<<GgafDx9Properties::SINGLE_DISPLAY_FULL_SCREEN_HEIGHT);
    _TRACE_("GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN1_WIDTH="<<GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN1_WIDTH);
    _TRACE_("GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN1_HEIGHT="<<GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN1_HEIGHT);
    _TRACE_("GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN2_WIDTH="<<GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN2_WIDTH);
    _TRACE_("GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN2_HEIGHT="<<GgafDx9Properties::DUAL_DISPLAY_FULL_SCREEN2_HEIGHT);
    _TRACE_("GgafDx9Properties::FIXED_VIEW_ASPECT="<<GgafDx9Properties::FIXED_VIEW_ASPECT);
    _TRACE_("GgafDx9Properties::SWAP_DISPLAY="<<GgafDx9Properties::SWAP_DISPLAY);

    _TRACE_("GgafDx9Properties::MASTER_VOLUME="<<GgafDx9Properties::MASTER_VOLUME);
    _TRACE_("GgafDx9Properties::BGM_VOLUME="<<GgafDx9Properties::BGM_VOLUME);
    _TRACE_("GgafDx9Properties::SE_VOLUME="<<GgafDx9Properties::SE_VOLUME);

    _TRACE_("GgafDx9Properties::DIR_MESH_MODEL="<<GgafDx9Properties::DIR_MESH_MODEL);
    _TRACE_("GgafDx9Properties::DIR_SPRITE_MODEL="<<GgafDx9Properties::DIR_SPRITE_MODEL);
    _TRACE_("GgafDx9Properties::DIR_TEXTURE="<<GgafDx9Properties::DIR_TEXTURE);
    _TRACE_("GgafDx9Properties::DIR_EFFECT="<<GgafDx9Properties::DIR_EFFECT);
    _TRACE_("GgafDx9Properties::DIR_OGG="<<GgafDx9Properties::DIR_OGG);
    _TRACE_("GgafDx9Properties::DIR_WAVE="<<GgafDx9Properties::DIR_WAVE);
    //����
}

void GgafDx9Properties::clean() {
    GgafProperties::clean();
}

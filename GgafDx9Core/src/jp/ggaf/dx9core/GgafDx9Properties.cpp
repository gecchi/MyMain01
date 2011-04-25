#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

bool GgafDx9Properties::FULL_SCREEN = 0;
bool GgafDx9Properties::MULTI_SCREEN = 0;
int GgafDx9Properties::GAME_BUFFER_WIDTH = 0;
int GgafDx9Properties::GAME_BUFFER_HEIGHT = 0;
float GgafDx9Properties::GAME_SPACE_DEPTH = 0;
int GgafDx9Properties::VIEW_SCREEN_WIDTH = 0;
int GgafDx9Properties::VIEW_SCREEN_HEIGHT = 0;
bool GgafDx9Properties::FIXED_VIEW_ASPECT = 0;
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
    GgafDx9Properties::MULTI_SCREEN = getBool("MULTI_SCREEN");
    GgafDx9Properties::GAME_BUFFER_WIDTH = getInt("GAME_BUFFER_WIDTH");
    GgafDx9Properties::GAME_BUFFER_HEIGHT = getInt("GAME_BUFFER_HEIGHT");
    GgafDx9Properties::GAME_SPACE_DEPTH = getFloat("GAME_SPACE_DEPTH");
    GgafDx9Properties::VIEW_SCREEN_WIDTH = getInt("VIEW_SCREEN_WIDTH");
    GgafDx9Properties::VIEW_SCREEN_HEIGHT = getInt("VIEW_SCREEN_HEIGHT");
    GgafDx9Properties::FIXED_VIEW_ASPECT = getBool("FIXED_VIEW_ASPECT");
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
    _TRACE_("GgafDx9Properties::MULTI_SCREEN="<<GgafDx9Properties::MULTI_SCREEN);
    _TRACE_("GgafDx9Properties::GAME_BUFFER_WIDTH="<<GgafDx9Properties::GAME_BUFFER_WIDTH);
    _TRACE_("GgafDx9Properties::GAME_SPACE_DEPTH="<<GgafDx9Properties::GAME_SPACE_DEPTH);
    _TRACE_("GgafDx9Properties::GAME_BUFFER_HEIGHT="<<GgafDx9Properties::GAME_BUFFER_HEIGHT);
    _TRACE_("GgafDx9Properties::VIEW_SCREEN_WIDTH="<<GgafDx9Properties::VIEW_SCREEN_WIDTH);
    _TRACE_("GgafDx9Properties::VIEW_SCREEN_HEIGHT="<<GgafDx9Properties::VIEW_SCREEN_HEIGHT);
    _TRACE_("GgafDx9Properties::FIXED_VIEW_ASPECT="<<GgafDx9Properties::FIXED_VIEW_ASPECT);
    _TRACE_("GgafDx9Properties::MASTER_VOLUME="<<GgafDx9Properties::MASTER_VOLUME);
    _TRACE_("GgafDx9Properties::BGM_VOLUME="<<GgafDx9Properties::BGM_VOLUME);
    _TRACE_("GgafDx9Properties::SE_VOLUME="<<GgafDx9Properties::SE_VOLUME);

    _TRACE_("GgafDx9Properties::DIR_MESH_MODEL="<<GgafDx9Properties::DIR_MESH_MODEL);
    _TRACE_("GgafDx9Properties::DIR_SPRITE_MODEL="<<GgafDx9Properties::DIR_SPRITE_MODEL);
    _TRACE_("GgafDx9Properties::DIR_TEXTURE="<<GgafDx9Properties::DIR_TEXTURE);
    _TRACE_("GgafDx9Properties::DIR_EFFECT="<<GgafDx9Properties::DIR_EFFECT);
    _TRACE_("GgafDx9Properties::DIR_OGG="<<GgafDx9Properties::DIR_OGG);
    _TRACE_("GgafDx9Properties::DIR_WAVE="<<GgafDx9Properties::DIR_WAVE);
    //‘±‚«
}

void GgafDx9Properties::clean() {
    GgafProperties::clean();
}

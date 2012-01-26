#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

bool GgafDxProperties::FULL_SCREEN = false;
bool GgafDxProperties::DUAL_VIEW = false;

pixcoord GgafDxProperties::GAME_BUFFER_WIDTH = 1440;
pixcoord GgafDxProperties::GAME_BUFFER_HEIGHT = 450;
float GgafDxProperties::GAME_SPACE_DEPTH = 15.0;
pixcoord GgafDxProperties::RENDER_TARGET_BUFFER_WIDTH = 1440;
pixcoord GgafDxProperties::RENDER_TARGET_BUFFER_HEIGHT = 450;

pixcoord GgafDxProperties::SINGLE_VIEW_WINDOW_WIDTH = 1440;
pixcoord GgafDxProperties::SINGLE_VIEW_WINDOW_HEIGHT = 450;
pixcoord GgafDxProperties::DUAL_VIEW_WINDOW1_WIDTH = 720;
pixcoord GgafDxProperties::DUAL_VIEW_WINDOW1_HEIGHT = 450;
pixcoord GgafDxProperties::DUAL_VIEW_WINDOW2_WIDTH = 720;
pixcoord GgafDxProperties::DUAL_VIEW_WINDOW2_HEIGHT = 450;
pixcoord GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_WIDTH = 1440;
pixcoord GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_HEIGHT = 900;
pixcoord GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_WIDTH = 1440;
pixcoord GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_HEIGHT = 900;
pixcoord GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_WIDTH = 1440;
pixcoord GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_HEIGHT = 900;
pixcoord GgafDxProperties::DUAL_VIEW_FULL_SCREEN_WIDTH = 1440;
pixcoord GgafDxProperties::DUAL_VIEW_FULL_SCREEN_HEIGHT = 900;

bool GgafDxProperties::FIXED_GAME_VIEW_ASPECT = false;
bool GgafDxProperties::SWAP_GAME_VIEW = false;
int GgafDxProperties::SINGLE_VIEW_DRAW_POSITION = 5;
int GgafDxProperties::DUAL_VIEW_DRAW_POSITION1 = 6;
int GgafDxProperties::DUAL_VIEW_DRAW_POSITION2 = 4;

string GgafDxProperties::BG_COLOR = "#222222";

int GgafDxProperties::MASTER_VOLUME = 80;
int GgafDxProperties::BGM_VOLUME = 80;
int GgafDxProperties::SE_VOLUME = 80;
string GgafDxProperties::DIR_MESH_MODEL = ".\\model\\mesh\\";
string GgafDxProperties::DIR_SPRITE_MODEL = ".\\model\\sprite\\";
string GgafDxProperties::DIR_TEXTURE = ".\\model\\texture\\";
string GgafDxProperties::DIR_EFFECT = ".\\model\\effect\\";
string GgafDxProperties::DIR_OGG = ".\\sound\\bgm\\";
string GgafDxProperties::DIR_WAVE = ".\\sound\\se\\";
bool GgafDxProperties::REALTIME_EFFECT_COMPILE = false;

void GgafDxProperties::load(string prm_ini_filename) {
    GgafProperties::load(prm_ini_filename);

    if (GgafProperties::isExistKey("FULL_SCREEN")) {
        GgafDxProperties::FULL_SCREEN                    = getBool("FULL_SCREEN");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW")) {
        GgafDxProperties::DUAL_VIEW                      = getBool("DUAL_VIEW");
    }
    if (GgafProperties::isExistKey("GAME_BUFFER_WIDTH")) {
        GgafDxProperties::GAME_BUFFER_WIDTH              = getInt("GAME_BUFFER_WIDTH");
    }
    if (GgafProperties::isExistKey("GAME_BUFFER_HEIGHT")) {
        GgafDxProperties::GAME_BUFFER_HEIGHT             = getInt("GAME_BUFFER_HEIGHT");
    }
    if (GgafProperties::isExistKey("GAME_SPACE_DEPTH")) {
        GgafDxProperties::GAME_SPACE_DEPTH               = getFloat("GAME_SPACE_DEPTH");
    }
    if (GgafProperties::isExistKey("RENDER_TARGET_BUFFER_WIDTH")) {
        GgafDxProperties::RENDER_TARGET_BUFFER_WIDTH     = getInt("RENDER_TARGET_BUFFER_WIDTH");
    }
    if (GgafProperties::isExistKey("RENDER_TARGET_BUFFER_HEIGHT")) {
        GgafDxProperties::RENDER_TARGET_BUFFER_HEIGHT    = getInt("RENDER_TARGET_BUFFER_HEIGHT");
    }
    if (GgafProperties::isExistKey("SINGLE_VIEW_WINDOW_WIDTH")) {
        GgafDxProperties::SINGLE_VIEW_WINDOW_WIDTH       = getInt("SINGLE_VIEW_WINDOW_WIDTH");
    }
    if (GgafProperties::isExistKey("SINGLE_VIEW_WINDOW_HEIGHT")) {
        GgafDxProperties::SINGLE_VIEW_WINDOW_HEIGHT      = getInt("SINGLE_VIEW_WINDOW_HEIGHT");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_WINDOW1_WIDTH")) {
        GgafDxProperties::DUAL_VIEW_WINDOW1_WIDTH        = getInt("DUAL_VIEW_WINDOW1_WIDTH");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_WINDOW1_HEIGHT")) {
        GgafDxProperties::DUAL_VIEW_WINDOW1_HEIGHT       = getInt("DUAL_VIEW_WINDOW1_HEIGHT");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_WINDOW2_WIDTH")) {
        GgafDxProperties::DUAL_VIEW_WINDOW2_WIDTH        = getInt("DUAL_VIEW_WINDOW2_WIDTH");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_WINDOW2_HEIGHT")) {
        GgafDxProperties::DUAL_VIEW_WINDOW2_HEIGHT       = getInt("DUAL_VIEW_WINDOW2_HEIGHT");
    }
    if (GgafProperties::isExistKey("SINGLE_VIEW_FULL_SCREEN_WIDTH")) {
        GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_WIDTH  = getInt("SINGLE_VIEW_FULL_SCREEN_WIDTH");
    }
    if (GgafProperties::isExistKey("SINGLE_VIEW_FULL_SCREEN_HEIGHT")) {
        GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_HEIGHT = getInt("SINGLE_VIEW_FULL_SCREEN_HEIGHT");
    }
//    if (GgafProperties::isExistKey("DUAL_VIEW_FULL_SCREEN_WIDTH")) {
//        GgafDxProperties::DUAL_VIEW_FULL_SCREEN_WIDTH    = getInt("DUAL_VIEW_FULL_SCREEN_WIDTH");
//    }
//    if (GgafProperties::isExistKey("DUAL_VIEW_FULL_SCREEN_HEIGHT")) {
//        GgafDxProperties::DUAL_VIEW_FULL_SCREEN_HEIGHT   = getInt("DUAL_VIEW_FULL_SCREEN_HEIGHT");
//    }
//    GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_WIDTH   = DUAL_VIEW_FULL_SCREEN_WIDTH ;
//    GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_HEIGHT  = DUAL_VIEW_FULL_SCREEN_HEIGHT;
//    GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_WIDTH   = DUAL_VIEW_FULL_SCREEN_WIDTH ;
//    GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_HEIGHT  = DUAL_VIEW_FULL_SCREEN_HEIGHT;


    if (GgafProperties::isExistKey("DUAL_VIEW_FULL_SCREEN1_WIDTH")) {
        GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_WIDTH    = getInt("DUAL_VIEW_FULL_SCREEN1_WIDTH");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_FULL_SCREEN1_HEIGHT")) {
        GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_HEIGHT    = getInt("DUAL_VIEW_FULL_SCREEN1_HEIGHT");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_FULL_SCREEN2_WIDTH")) {
        GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_WIDTH    = getInt("DUAL_VIEW_FULL_SCREEN2_WIDTH");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_FULL_SCREEN2_HEIGHT")) {
        GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_HEIGHT    = getInt("DUAL_VIEW_FULL_SCREEN2_HEIGHT");
    }

    if (GgafProperties::isExistKey("FIXED_GAME_VIEW_ASPECT")) {
        GgafDxProperties::FIXED_GAME_VIEW_ASPECT         = getBool("FIXED_GAME_VIEW_ASPECT");
    }
    if (GgafProperties::isExistKey("SWAP_GAME_VIEW")) {
        GgafDxProperties::SWAP_GAME_VIEW                 = getBool("SWAP_GAME_VIEW");
    }
    if (GgafProperties::isExistKey("SINGLE_VIEW_DRAW_POSITION")) {
        GgafDxProperties::SINGLE_VIEW_DRAW_POSITION      = getInt("SINGLE_VIEW_DRAW_POSITION");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_DRAW_POSITION1")) {
        GgafDxProperties::DUAL_VIEW_DRAW_POSITION1       = getInt("DUAL_VIEW_DRAW_POSITION1");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_DRAW_POSITION2")) {
        GgafDxProperties::DUAL_VIEW_DRAW_POSITION2       = getInt("DUAL_VIEW_DRAW_POSITION2");
    }
    if (GgafProperties::isExistKey("BG_COLOR")) {
        GgafDxProperties::BG_COLOR                       = getStr("BG_COLOR");
    }

    if (GgafProperties::isExistKey("MASTER_VOLUME")) {
        GgafDxProperties::MASTER_VOLUME                  = getInt("MASTER_VOLUME");
    }
    if (GgafProperties::isExistKey("BGM_VOLUME")) {
        GgafDxProperties::BGM_VOLUME                     = getInt("BGM_VOLUME");
    }
    if (GgafProperties::isExistKey("SE_VOLUME")) {
        GgafDxProperties::SE_VOLUME                      = getInt("SE_VOLUME");
    }
    if (GgafProperties::isExistKey("DIR_MESH_MODEL")) {
        GgafDxProperties::DIR_MESH_MODEL                 = getStr("DIR_MESH_MODEL");
    }
    if (GgafProperties::isExistKey("DIR_SPRITE_MODEL")) {
        GgafDxProperties::DIR_SPRITE_MODEL               = getStr("DIR_SPRITE_MODEL");
    }
    if (GgafProperties::isExistKey("DIR_TEXTURE")) {
        GgafDxProperties::DIR_TEXTURE                    = getStr("DIR_TEXTURE");
    }
    if (GgafProperties::isExistKey("DIR_EFFECT")) {
        GgafDxProperties::DIR_EFFECT                     = getStr("DIR_EFFECT");
    }
    if (GgafProperties::isExistKey("DIR_OGG")) {
        GgafDxProperties::DIR_OGG                        = getStr("DIR_OGG");
    }
    if (GgafProperties::isExistKey("DIR_WAVE")) {
        GgafDxProperties::DIR_WAVE                       = getStr("DIR_WAVE");
    }
    if (GgafProperties::isExistKey("REALTIME_EFFECT_COMPILE")) {
        GgafDxProperties::REALTIME_EFFECT_COMPILE        = getBool("REALTIME_EFFECT_COMPILE");
    }

    _TRACE_("GgafDxProperties::FULL_SCREEN="<<GgafDxProperties::FULL_SCREEN);
    _TRACE_("GgafDxProperties::DUAL_VIEW="<<GgafDxProperties::DUAL_VIEW);
    _TRACE_("GgafDxProperties::GAME_BUFFER_WIDTH="<<GgafDxProperties::GAME_BUFFER_WIDTH);
    _TRACE_("GgafDxProperties::GAME_BUFFER_HEIGHT="<<GgafDxProperties::GAME_BUFFER_HEIGHT);
    _TRACE_("GgafDxProperties::GAME_SPACE_DEPTH="<<GgafDxProperties::GAME_SPACE_DEPTH);
    _TRACE_("GgafDxProperties::RENDER_TARGET_BUFFER_WIDTH="<<GgafDxProperties::RENDER_TARGET_BUFFER_WIDTH);
    _TRACE_("GgafDxProperties::RENDER_TARGET_BUFFER_HEIGHT="<<GgafDxProperties::RENDER_TARGET_BUFFER_HEIGHT);
    _TRACE_("GgafDxProperties::SINGLE_VIEW_WINDOW_WIDTH="<<GgafDxProperties::SINGLE_VIEW_WINDOW_WIDTH);
    _TRACE_("GgafDxProperties::SINGLE_VIEW_WINDOW_HEIGHT="<<GgafDxProperties::SINGLE_VIEW_WINDOW_HEIGHT);
    _TRACE_("GgafDxProperties::DUAL_VIEW_WINDOW1_WIDTH="<<GgafDxProperties::DUAL_VIEW_WINDOW1_WIDTH);
    _TRACE_("GgafDxProperties::DUAL_VIEW_WINDOW1_HEIGHT="<<GgafDxProperties::DUAL_VIEW_WINDOW1_HEIGHT);
    _TRACE_("GgafDxProperties::DUAL_VIEW_WINDOW2_WIDTH="<<GgafDxProperties::DUAL_VIEW_WINDOW2_WIDTH);
    _TRACE_("GgafDxProperties::DUAL_VIEW_WINDOW2_HEIGHT="<<GgafDxProperties::DUAL_VIEW_WINDOW2_HEIGHT);
    _TRACE_("GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_WIDTH="<<GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_WIDTH);
    _TRACE_("GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_HEIGHT="<<GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_HEIGHT);
    _TRACE_("GgafDxProperties::DUAL_VIEW_FULL_SCREEN_WIDTH="<<GgafDxProperties::DUAL_VIEW_FULL_SCREEN_WIDTH);
    _TRACE_("GgafDxProperties::DUAL_VIEW_FULL_SCREEN_HEIGHT="<<GgafDxProperties::DUAL_VIEW_FULL_SCREEN_HEIGHT);
    _TRACE_("GgafDxProperties::FIXED_GAME_VIEW_ASPECT="<<GgafDxProperties::FIXED_GAME_VIEW_ASPECT);
    _TRACE_("GgafDxProperties::SWAP_GAME_VIEW="<<GgafDxProperties::SWAP_GAME_VIEW);
    _TRACE_("GgafDxProperties::SINGLE_VIEW_DRAW_POSITION="<<GgafDxProperties::SINGLE_VIEW_DRAW_POSITION);
    _TRACE_("GgafDxProperties::DUAL_VIEW_DRAW_POSITION1="<<GgafDxProperties::DUAL_VIEW_DRAW_POSITION1);
    _TRACE_("GgafDxProperties::DUAL_VIEW_DRAW_POSITION2="<<GgafDxProperties::DUAL_VIEW_DRAW_POSITION2);
    _TRACE_("GgafDxProperties::BG_COLOR="<<GgafDxProperties::BG_COLOR);

    _TRACE_("GgafDxProperties::MASTER_VOLUME="<<GgafDxProperties::MASTER_VOLUME);
    _TRACE_("GgafDxProperties::BGM_VOLUME="<<GgafDxProperties::BGM_VOLUME);
    _TRACE_("GgafDxProperties::SE_VOLUME="<<GgafDxProperties::SE_VOLUME);

    _TRACE_("GgafDxProperties::DIR_MESH_MODEL="<<GgafDxProperties::DIR_MESH_MODEL);
    _TRACE_("GgafDxProperties::DIR_SPRITE_MODEL="<<GgafDxProperties::DIR_SPRITE_MODEL);
    _TRACE_("GgafDxProperties::DIR_TEXTURE="<<GgafDxProperties::DIR_TEXTURE);
    _TRACE_("GgafDxProperties::DIR_EFFECT="<<GgafDxProperties::DIR_EFFECT);
    _TRACE_("GgafDxProperties::DIR_OGG="<<GgafDxProperties::DIR_OGG);
    _TRACE_("GgafDxProperties::DIR_WAVE="<<GgafDxProperties::DIR_WAVE);

    _TRACE_("GgafDxProperties::REALTIME_EFFECT_COMPILE="<<GgafDxProperties::REALTIME_EFFECT_COMPILE);

}

void GgafDxProperties::clean() {
    GgafProperties::clean();
}

﻿#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

bool* GgafDx9Properties::FULL_SCREEN = NULL;
int* GgafDx9Properties::GAME_SCREEN_WIDTH = NULL;
int* GgafDx9Properties::GAME_SCREEN_HEIGHT = NULL;
float* GgafDx9Properties::GAME_SPACE_DEPTH = NULL;
int* GgafDx9Properties::VIEW_SCREEN_WIDTH = NULL;
int* GgafDx9Properties::VIEW_SCREEN_HEIGHT = NULL;
bool* GgafDx9Properties::FIXED_VIEW_ASPECT = NULL;
int* GgafDx9Properties::MASTER_VOLUME;
int* GgafDx9Properties::BGM_VOLUME;
int* GgafDx9Properties::SE_VOLUME;
string* GgafDx9Properties::DIR_MESH_MODEL = NULL;
string* GgafDx9Properties::DIR_SPRITE_MODEL = NULL;
string* GgafDx9Properties::DIR_TEXTURE = NULL;
string* GgafDx9Properties::DIR_EFFECT = NULL;
string* GgafDx9Properties::DIR_OGG = NULL;
string* GgafDx9Properties::DIR_WAVE = NULL;

void GgafDx9Properties::load(string prm_ini_filename) {
    GgafProperties::load(prm_ini_filename);

    FULL_SCREEN = getBool("FULL_SCREEN");
    GAME_SCREEN_WIDTH = getInt("GAME_SCREEN_WIDTH");
    GAME_SCREEN_HEIGHT = getInt("GAME_SCREEN_HEIGHT");
    GAME_SPACE_DEPTH = getFloat("GAME_SPACE_DEPTH");
    VIEW_SCREEN_WIDTH = getInt("VIEW_SCREEN_WIDTH");
    VIEW_SCREEN_HEIGHT = getInt("VIEW_SCREEN_HEIGHT");
    FIXED_VIEW_ASPECT = getBool("FIXED_VIEW_ASPECT");
    MASTER_VOLUME = getInt("MASTER_VOLUME");
    BGM_VOLUME = getInt("BGM_VOLUME");
    SE_VOLUME = getInt("SE_VOLUME");

    DIR_MESH_MODEL = getStr("DIR_MESH_MODEL");
    DIR_SPRITE_MODEL = getStr("DIR_SPRITE_MODEL");
    DIR_TEXTURE = getStr("DIR_TEXTURE");
    DIR_EFFECT = getStr("DIR_EFFECT");
    DIR_OGG = getStr("DIR_OGG");
    DIR_WAVE = getStr("DIR_WAVE");

    _TRACE_("GGAFDX9_PROPERTY(FULL_SCREEN)="<<GGAFDX9_PROPERTY(FULL_SCREEN));
    _TRACE_("GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)="<<GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH));
    _TRACE_("GGAFDX9_PROPERTY(GAME_SPACE_DEPTH)="<<GGAFDX9_PROPERTY(GAME_SPACE_DEPTH));
    _TRACE_("GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)="<<GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT));
    _TRACE_("GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH)="<<GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH));
    _TRACE_("GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT)="<<GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT));
    _TRACE_("GGAFDX9_PROPERTY(FIXED_VIEW_ASPECT)="<<GGAFDX9_PROPERTY(FIXED_VIEW_ASPECT));
    _TRACE_("GGAFDX9_PROPERTY(MASTER_VOLUME)="<<GGAFDX9_PROPERTY(MASTER_VOLUME));
    _TRACE_("GGAFDX9_PROPERTY(BGM_VOLUME)="<<GGAFDX9_PROPERTY(BGM_VOLUME));
    _TRACE_("GGAFDX9_PROPERTY(SE_VOLUME)="<<GGAFDX9_PROPERTY(SE_VOLUME));

    _TRACE_("GGAFDX9_PROPERTY(DIR_MESH_MODEL)="<<GGAFDX9_PROPERTY(DIR_MESH_MODEL));
    _TRACE_("GGAFDX9_PROPERTY(DIR_SPRITE_MODEL)="<<GGAFDX9_PROPERTY(DIR_SPRITE_MODEL));
    _TRACE_("GGAFDX9_PROPERTY(DIR_TEXTURE)="<<GGAFDX9_PROPERTY(DIR_TEXTURE));
    _TRACE_("GGAFDX9_PROPERTY(DIR_EFFECT)="<<GGAFDX9_PROPERTY(DIR_EFFECT));
    _TRACE_("GGAFDX9_PROPERTY(DIR_OGG)="<<GGAFDX9_PROPERTY(DIR_OGG));
    _TRACE_("GGAFDX9_PROPERTY(DIR_WAVE)="<<GGAFDX9_PROPERTY(DIR_WAVE));
    //続き
}

void GgafDx9Properties::clean() {
    GgafProperties::clean();

    DELETE_IMPOSSIBLE_NULL(DIR_MESH_MODEL);
    DELETE_IMPOSSIBLE_NULL(DIR_SPRITE_MODEL);
    DELETE_IMPOSSIBLE_NULL(DIR_TEXTURE);
    DELETE_IMPOSSIBLE_NULL(DIR_EFFECT);
    DELETE_IMPOSSIBLE_NULL(DIR_OGG);
    DELETE_IMPOSSIBLE_NULL(DIR_WAVE);
    DELETE_IMPOSSIBLE_NULL(FULL_SCREEN);
    DELETE_IMPOSSIBLE_NULL(GAME_SCREEN_WIDTH);
    DELETE_IMPOSSIBLE_NULL(GAME_SCREEN_HEIGHT);
    DELETE_IMPOSSIBLE_NULL(GAME_SPACE_DEPTH);
    DELETE_IMPOSSIBLE_NULL(VIEW_SCREEN_WIDTH);
    DELETE_IMPOSSIBLE_NULL(VIEW_SCREEN_HEIGHT);
    DELETE_IMPOSSIBLE_NULL(FIXED_VIEW_ASPECT);
    DELETE_IMPOSSIBLE_NULL(MASTER_VOLUME);
    DELETE_IMPOSSIBLE_NULL(BGM_VOLUME);
    DELETE_IMPOSSIBLE_NULL(SE_VOLUME);
}

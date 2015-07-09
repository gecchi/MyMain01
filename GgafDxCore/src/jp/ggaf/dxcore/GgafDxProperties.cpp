#include "jp/ggaf/dxcore/GgafDxProperties.h"

#include <Shlwapi.h>

using namespace GgafCore;
using namespace GgafDxCore;

bool GgafDxProperties::FULL_SCREEN = false;
bool GgafDxProperties::DUAL_VIEW = false;

pixcoord GgafDxProperties::GAME_BUFFER_WIDTH = 1600;
pixcoord GgafDxProperties::GAME_BUFFER_HEIGHT = 450;
double GgafDxProperties::GAME_SPACE_DEPTH = 15.0;
int GgafDxProperties::RENDER_DEPTH_INDEXS_NUM = 256;
double GgafDxProperties::RENDER_DEPTH_STAGE_RATIO = 0.6;
bool GgafDxProperties::PRJ_2D_MODE = false;
pixcoord GgafDxProperties::RENDER_TARGET_BUFFER_WIDTH = 1600;
pixcoord GgafDxProperties::RENDER_TARGET_BUFFER_HEIGHT = 450;

pixcoord GgafDxProperties::SINGLE_VIEW_WINDOW_WIDTH = 1600;
pixcoord GgafDxProperties::SINGLE_VIEW_WINDOW_HEIGHT = 450;
pixcoord GgafDxProperties::DUAL_VIEW_WINDOW1_WIDTH = 800;
pixcoord GgafDxProperties::DUAL_VIEW_WINDOW1_HEIGHT = 450;
pixcoord GgafDxProperties::DUAL_VIEW_WINDOW2_WIDTH = 800;
pixcoord GgafDxProperties::DUAL_VIEW_WINDOW2_HEIGHT = 450;
pixcoord GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_WIDTH = 1600;
pixcoord GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_HEIGHT = 900;
pixcoord GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_WIDTH = 1600;
pixcoord GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_HEIGHT = 900;
pixcoord GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_WIDTH = 1600;
pixcoord GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_HEIGHT = 900;

pixcoord GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_WIDTH_BK  = GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_WIDTH;
pixcoord GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_HEIGHT_BK = GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_HEIGHT;
pixcoord GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_WIDTH_BK   = GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_WIDTH;
pixcoord GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_HEIGHT_BK  = GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_HEIGHT;
pixcoord GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_WIDTH_BK   = GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_WIDTH;
pixcoord GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_HEIGHT_BK  = GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_HEIGHT;


bool GgafDxProperties::FIXED_GAME_VIEW_ASPECT = false;
bool GgafDxProperties::VIEW_AS_RENDER_TARGET_BUFFER_SIZE = false;
bool GgafDxProperties::SWAP_GAME_VIEW = false;
int GgafDxProperties::SINGLE_VIEW_DRAW_POSITION = 5;
int GgafDxProperties::DUAL_VIEW_DRAW_POSITION1 = 6;
int GgafDxProperties::DUAL_VIEW_DRAW_POSITION2 = 4;

double GgafDxProperties::VIEW1_WIDTH_RATIO = 1.0;
double GgafDxProperties::VIEW1_HEIGHT_RATIO = 1.0;
double GgafDxProperties::VIEW2_WIDTH_RATIO = 1.0;
double GgafDxProperties::VIEW2_HEIGHT_RATIO = 1.0;

std::string GgafDxProperties::BORDER_COLOR = "#222222";
std::string GgafDxProperties::BG_COLOR = "#000000";

int GgafDxProperties::MASTER_VOLUME = 800;
int GgafDxProperties::BGM_VOLUME = 800;
int GgafDxProperties::SE_VOLUME = 800;
int GgafDxProperties::MAX_SE_AT_ONCE = 16;
int GgafDxProperties::MAX_SE_DELAY = 240;

std::string GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_MESH = "mesh";
std::string GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_SPRITE = "sprite";
std::string GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE = "texture";
std::string GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_EFFECT = "effect";
std::string GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_OGG = "ogg";
std::string GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_WAVE = "wave";

std::string GgafDxProperties::DIR_MESH_MODEL[] = {
                GgafProperties::DIR_SKIN_KIND[0] + "/" + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_MESH,
                GgafProperties::DIR_SKIN_KIND[1] + "/" + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_MESH,
                GgafProperties::DIR_SKIN_KIND[2] + "/"
            };
std::string GgafDxProperties::DIR_SPRITE_MODEL[] = {
                GgafProperties::DIR_SKIN_KIND[0] + "/" + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_SPRITE + "/",
                GgafProperties::DIR_SKIN_KIND[1] + "/" + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_SPRITE + "/",
                GgafProperties::DIR_SKIN_KIND[2] + "/"
            };
std::string GgafDxProperties::DIR_TEXTURE[] = {
                GgafProperties::DIR_SKIN_KIND[0] + "/" + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/",
                GgafProperties::DIR_SKIN_KIND[1] + "/" + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/",
                GgafProperties::DIR_SKIN_KIND[2]
            };
std::string GgafDxProperties::DIR_EFFECT[] = {
                GgafProperties::DIR_SKIN_KIND[0] + "/" + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_EFFECT + "/",
                GgafProperties::DIR_SKIN_KIND[1] + "/" + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_EFFECT + "/",
                GgafProperties::DIR_SKIN_KIND[2]
            };
std::string GgafDxProperties::DIR_OGG[] = {
                GgafProperties::DIR_SKIN_KIND[0] + "/" + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_OGG + "/",
                GgafProperties::DIR_SKIN_KIND[1] + "/" + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_OGG + "/",
                GgafProperties::DIR_SKIN_KIND[2]
            };
std::string GgafDxProperties::DIR_WAVE[] = {
                GgafProperties::DIR_SKIN_KIND[0] + "/" + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_WAVE + "/",
                GgafProperties::DIR_SKIN_KIND[1] + "/" + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_WAVE + "/",
                GgafProperties::DIR_SKIN_KIND[2]
            };

bool GgafDxProperties::REALTIME_EFFECT_COMPILE = false;

std::string GgafDxProperties::ILLIGAL_TEXTURE = "GgafDxIlligalTexture.dds";
std::string GgafDxProperties::ILLIGAL_CUBEMAP_TEXTURE = "GgafDxIlligalCubeMapTexture.dds";
std::string GgafDxProperties::WHITE_TEXTURE = "GgafDxWhite.dds";
std::string GgafDxProperties::COLI_AAB_MODEL = "GgafDxAAB";
std::string GgafDxProperties::COLI_AAPRISM_MODEL = "GgafDxAAPrism";
std::string GgafDxProperties::COLI_SPHERE_MODEL = "GgafDxSphere";


void GgafDxProperties::load(std::string prm_properties_filename) {
    GgafProperties::load(prm_properties_filename);

    if (GgafProperties::isExistKey("FULL_SCREEN")) {
        GgafDxProperties::FULL_SCREEN = getBool("FULL_SCREEN");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW")) {
        GgafDxProperties::DUAL_VIEW = getBool("DUAL_VIEW");
    }
    if (GgafProperties::isExistKey("GAME_BUFFER_WIDTH")) {
        GgafDxProperties::GAME_BUFFER_WIDTH = getInt("GAME_BUFFER_WIDTH");
    }
    if (GgafProperties::isExistKey("GAME_BUFFER_HEIGHT")) {
        GgafDxProperties::GAME_BUFFER_HEIGHT = getInt("GAME_BUFFER_HEIGHT");
    }
    if (GgafProperties::isExistKey("GAME_SPACE_DEPTH")) {
        GgafDxProperties::GAME_SPACE_DEPTH = getDouble("GAME_SPACE_DEPTH");
    }
    if (GgafProperties::isExistKey("RENDER_DEPTH_INDEXS_NUM")) {
        GgafDxProperties::RENDER_DEPTH_INDEXS_NUM = getInt("RENDER_DEPTH_INDEXS_NUM");
    }
    if (GgafProperties::isExistKey("RENDER_DEPTH_STAGE_RATIO")) {
        GgafDxProperties::RENDER_DEPTH_STAGE_RATIO = getDouble("RENDER_DEPTH_STAGE_RATIO");
    }
    if (GgafProperties::isExistKey("PRJ_2D_MODE")) {
        GgafDxProperties::PRJ_2D_MODE = getBool("PRJ_2D_MODE");
    }
    if (GgafProperties::isExistKey("RENDER_TARGET_BUFFER_WIDTH")) {
        GgafDxProperties::RENDER_TARGET_BUFFER_WIDTH = getInt("RENDER_TARGET_BUFFER_WIDTH");
    }
    if (GgafProperties::isExistKey("RENDER_TARGET_BUFFER_HEIGHT")) {
        GgafDxProperties::RENDER_TARGET_BUFFER_HEIGHT = getInt("RENDER_TARGET_BUFFER_HEIGHT");
    }
    if (GgafProperties::isExistKey("SINGLE_VIEW_WINDOW_WIDTH")) {
        GgafDxProperties::SINGLE_VIEW_WINDOW_WIDTH = getInt("SINGLE_VIEW_WINDOW_WIDTH");
    }
    if (GgafProperties::isExistKey("SINGLE_VIEW_WINDOW_HEIGHT")) {
        GgafDxProperties::SINGLE_VIEW_WINDOW_HEIGHT = getInt("SINGLE_VIEW_WINDOW_HEIGHT");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_WINDOW1_WIDTH")) {
        GgafDxProperties::DUAL_VIEW_WINDOW1_WIDTH = getInt("DUAL_VIEW_WINDOW1_WIDTH");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_WINDOW1_HEIGHT")) {
        GgafDxProperties::DUAL_VIEW_WINDOW1_HEIGHT = getInt("DUAL_VIEW_WINDOW1_HEIGHT");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_WINDOW2_WIDTH")) {
        GgafDxProperties::DUAL_VIEW_WINDOW2_WIDTH = getInt("DUAL_VIEW_WINDOW2_WIDTH");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_WINDOW2_HEIGHT")) {
        GgafDxProperties::DUAL_VIEW_WINDOW2_HEIGHT = getInt("DUAL_VIEW_WINDOW2_HEIGHT");
    }

    if (GgafProperties::isExistKey("SINGLE_VIEW_FULL_SCREEN_WIDTH")) {
        GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_WIDTH = getInt("SINGLE_VIEW_FULL_SCREEN_WIDTH");
        GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_WIDTH_BK  = GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_WIDTH;
    }
    if (GgafProperties::isExistKey("SINGLE_VIEW_FULL_SCREEN_HEIGHT")) {
        GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_HEIGHT = getInt("SINGLE_VIEW_FULL_SCREEN_HEIGHT");
        GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_HEIGHT_BK = GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_HEIGHT;
    }

    if (GgafProperties::isExistKey("DUAL_VIEW_FULL_SCREEN1_WIDTH")) {
        GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_WIDTH = getInt("DUAL_VIEW_FULL_SCREEN1_WIDTH");
        GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_WIDTH_BK   = GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_WIDTH;
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_FULL_SCREEN1_HEIGHT")) {
        GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_HEIGHT = getInt("DUAL_VIEW_FULL_SCREEN1_HEIGHT");
        GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_HEIGHT_BK  = GgafDxProperties::DUAL_VIEW_FULL_SCREEN1_HEIGHT;
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_FULL_SCREEN2_WIDTH")) {
        GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_WIDTH = getInt("DUAL_VIEW_FULL_SCREEN2_WIDTH");
        GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_WIDTH_BK   = GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_WIDTH;
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_FULL_SCREEN2_HEIGHT")) {
        GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_HEIGHT = getInt("DUAL_VIEW_FULL_SCREEN2_HEIGHT");
        GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_HEIGHT_BK  = GgafDxProperties::DUAL_VIEW_FULL_SCREEN2_HEIGHT;
    }

    if (GgafProperties::isExistKey("FIXED_GAME_VIEW_ASPECT")) {
        GgafDxProperties::FIXED_GAME_VIEW_ASPECT = getBool("FIXED_GAME_VIEW_ASPECT");
    }
    if (GgafProperties::isExistKey("VIEW_AS_RENDER_TARGET_BUFFER_SIZE")) {
        GgafDxProperties::VIEW_AS_RENDER_TARGET_BUFFER_SIZE = getBool("VIEW_AS_RENDER_TARGET_BUFFER_SIZE");
    }

    if (GgafProperties::isExistKey("SWAP_GAME_VIEW")) {
        GgafDxProperties::SWAP_GAME_VIEW = getBool("SWAP_GAME_VIEW");
    }
    if (GgafProperties::isExistKey("SINGLE_VIEW_DRAW_POSITION")) {
        GgafDxProperties::SINGLE_VIEW_DRAW_POSITION = getInt("SINGLE_VIEW_DRAW_POSITION");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_DRAW_POSITION1")) {
        GgafDxProperties::DUAL_VIEW_DRAW_POSITION1 = getInt("DUAL_VIEW_DRAW_POSITION1");
    }
    if (GgafProperties::isExistKey("DUAL_VIEW_DRAW_POSITION2")) {
        GgafDxProperties::DUAL_VIEW_DRAW_POSITION2 = getInt("DUAL_VIEW_DRAW_POSITION2");
    }

    if (GgafProperties::isExistKey("VIEW1_WIDTH_RATIO")) {
        GgafDxProperties::VIEW1_WIDTH_RATIO = getDouble("VIEW1_WIDTH_RATIO");
    }
    if (GgafProperties::isExistKey("VIEW1_HEIGHT_RATIO")) {
        GgafDxProperties::VIEW1_HEIGHT_RATIO = getDouble("VIEW1_HEIGHT_RATIO");
    }
    if (GgafProperties::isExistKey("VIEW2_WIDTH_RATIO")) {
        GgafDxProperties::VIEW2_WIDTH_RATIO = getDouble("VIEW2_WIDTH_RATIO");
    }
    if (GgafProperties::isExistKey("VIEW1_HEIGHT_RATIO")) {
        GgafDxProperties::VIEW2_HEIGHT_RATIO = getDouble("VIEW2_HEIGHT_RATIO");
    }

    if (GgafProperties::isExistKey("BORDER_COLOR")) {
        GgafDxProperties::BORDER_COLOR = getStr("BORDER_COLOR");
    }
    if (GgafProperties::isExistKey("BG_COLOR")) {
        GgafDxProperties::BG_COLOR = getStr("BG_COLOR");
    }
    if (GgafProperties::isExistKey("MASTER_VOLUME")) {
        GgafDxProperties::MASTER_VOLUME = getInt("MASTER_VOLUME");
    }
    if (GgafProperties::isExistKey("BGM_VOLUME")) {
        GgafDxProperties::BGM_VOLUME = getInt("BGM_VOLUME");
    }
    if (GgafProperties::isExistKey("SE_VOLUME")) {
        GgafDxProperties::SE_VOLUME = getInt("SE_VOLUME");
    }
    if (GgafProperties::isExistKey("MAX_SE_AT_ONCE")) {
        GgafDxProperties::MAX_SE_AT_ONCE = getInt("MAX_SE_AT_ONCE");
    }
    if (GgafProperties::isExistKey("MAX_SE_DELAY")) {
        GgafDxProperties::MAX_SE_DELAY = getInt("MAX_SE_DELAY");
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SKIN_XXX_MESH")) {
        GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_MESH = getStr("DIRNAME_RESOURCE_SKIN_XXX_MESH");
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SKIN_XXX_SPRITE")) {
        GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_SPRITE = getStr("DIRNAME_RESOURCE_SKIN_XXX_SPRITE");
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SKIN_XXX_TEXTURE")) {
        GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE = getStr("DIRNAME_RESOURCE_SKIN_XXX_TEXTURE");
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SKIN_XXX_EFFECT")) {
        GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_EFFECT = getStr("DIRNAME_RESOURCE_SKIN_XXX_EFFECT");
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SKIN_XXX_OGG")) {
        GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_OGG = getStr("DIRNAME_RESOURCE_SKIN_XXX_OGG");
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SKIN_XXX_WAVE")) {
        GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_WAVE = getStr("DIRNAME_RESOURCE_SKIN_XXX_WAVE");
    }
    if (GgafProperties::isExistKey("REALTIME_EFFECT_COMPILE")) {
        GgafDxProperties::REALTIME_EFFECT_COMPILE = getBool("REALTIME_EFFECT_COMPILE");
    }


    if (GgafProperties::isExistKey("ILLIGAL_TEXTURE")) {
        GgafDxProperties::ILLIGAL_TEXTURE = getStr("ILLIGAL_TEXTURE");
    }
    if (GgafProperties::isExistKey("ILLIGAL_CUBEMAP_TEXTURE")) {
        GgafDxProperties::ILLIGAL_CUBEMAP_TEXTURE = getStr("ILLIGAL_CUBEMAP_TEXTURE");
    }
    if (GgafProperties::isExistKey("WHITE_TEXTURE")) {
        GgafDxProperties::WHITE_TEXTURE = getStr("WHITE_TEXTURE");
    }
    if (GgafProperties::isExistKey("COLI_AAB_MODEL")) {
        GgafDxProperties::COLI_AAB_MODEL = getStr("COLI_AAB_MODEL");
    }
    if (GgafProperties::isExistKey("COLI_AAPRISM_MODEL")) {
        GgafDxProperties::COLI_AAPRISM_MODEL = getStr("COLI_AAPRISM_MODEL");
    }
    if (GgafProperties::isExistKey("COLI_SPHERE_MODEL")) {
        GgafDxProperties::COLI_SPHERE_MODEL = getStr("COLI_SPHERE_MODEL");
    }


    GgafDxProperties::DIR_MESH_MODEL[0] = GgafProperties::DIR_SKIN_KIND[0] + "/"
            + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_MESH + "/";
    GgafDxProperties::DIR_SPRITE_MODEL[0] = GgafProperties::DIR_SKIN_KIND[0] + "/"
            + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_SPRITE + "/";
    GgafDxProperties::DIR_TEXTURE[0] = GgafProperties::DIR_SKIN_KIND[0] + "/"
            + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
    GgafDxProperties::DIR_EFFECT[0] = GgafProperties::DIR_SKIN_KIND[0] + "/"
            + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_EFFECT + "/";
    GgafDxProperties::DIR_OGG[0] = GgafProperties::DIR_SKIN_KIND[0] + "/"
            + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_OGG + "/";
    GgafDxProperties::DIR_WAVE[0] = GgafProperties::DIR_SKIN_KIND[0] + "/"
            + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_WAVE + "/";

    GgafDxProperties::DIR_MESH_MODEL[1] = GgafProperties::DIR_SKIN_KIND[1] + "/"
            + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_MESH + "/";
    GgafDxProperties::DIR_SPRITE_MODEL[1] = GgafProperties::DIR_SKIN_KIND[1] + "/"
            + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_SPRITE + "/";
    GgafDxProperties::DIR_TEXTURE[1] = GgafProperties::DIR_SKIN_KIND[1] + "/"
            + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
    GgafDxProperties::DIR_EFFECT[1] = GgafProperties::DIR_SKIN_KIND[1] + "/"
            + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_EFFECT + "/";
    GgafDxProperties::DIR_OGG[1] = GgafProperties::DIR_SKIN_KIND[1] + "/"
            + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_OGG + "/";
    GgafDxProperties::DIR_WAVE[1] = GgafProperties::DIR_SKIN_KIND[1] + "/"
            + GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_WAVE + "/";

    GgafDxProperties::DIR_MESH_MODEL[2] = GgafProperties::DIR_SKIN_KIND[2] + "/";
    GgafDxProperties::DIR_SPRITE_MODEL[2] = GgafProperties::DIR_SKIN_KIND[2] + "/";
    GgafDxProperties::DIR_TEXTURE[2] = GgafProperties::DIR_SKIN_KIND[2] + "/";
    GgafDxProperties::DIR_EFFECT[2] = GgafProperties::DIR_SKIN_KIND[2] + "/";
    GgafDxProperties::DIR_OGG[2] = GgafProperties::DIR_SKIN_KIND[2] + "/";
    GgafDxProperties::DIR_WAVE[2] = GgafProperties::DIR_SKIN_KIND[2] + "/";


    UTIL::strReplace(GgafDxProperties::DIR_MESH_MODEL[0]    , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_SPRITE_MODEL[0]  , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_TEXTURE[0]       , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_EFFECT[0]        , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_OGG[0]           , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_WAVE[0]          , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_MESH_MODEL[1]    , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_SPRITE_MODEL[1]  , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_TEXTURE[1]       , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_EFFECT[1]        , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_OGG[1]           , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_WAVE[1]          , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_MESH_MODEL[2]    , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_SPRITE_MODEL[2]  , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_TEXTURE[2]       , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_EFFECT[2]        , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_OGG[2]           , "//", "/");
    UTIL::strReplace(GgafDxProperties::DIR_WAVE[2]          , "//", "/");

    //リソースディレクトリ名指定があるのならば、デフォルトのスキンディレクトリのリソースディレクトリ存在チェック
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SKIN_XXX_MESH")) {
        if (!PathFileExists(GgafDxProperties::DIR_MESH_MODEL[0].c_str()) ) {
            throwGgafCriticalException("GgafProperties::load("<<prm_properties_filename<<") DIR_MESH_MODEL[0]("<<GgafDxProperties::DIR_MESH_MODEL[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SKIN_XXX_SPRITE")) {
        if (!PathFileExists(GgafDxProperties::DIR_SPRITE_MODEL[0].c_str()) ) {
            throwGgafCriticalException("GgafProperties::load("<<prm_properties_filename<<") DIR_SPRITE_MODEL[0]("<<GgafDxProperties::DIR_SPRITE_MODEL[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SKIN_XXX_TEXTURE")) {
        if (!PathFileExists(GgafDxProperties::DIR_TEXTURE[0].c_str()) ) {
            throwGgafCriticalException("GgafProperties::load("<<prm_properties_filename<<") DIR_TEXTURE[0]("<<GgafDxProperties::DIR_TEXTURE[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SKIN_XXX_EFFECT")) {
        if (!PathFileExists(GgafDxProperties::DIR_EFFECT[0].c_str()) ) {
            throwGgafCriticalException("GgafProperties::load("<<prm_properties_filename<<") DIR_EFFECT[0]("<<GgafDxProperties::DIR_EFFECT[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SKIN_XXX_OGG")) {
        if (!PathFileExists(GgafDxProperties::DIR_OGG[0].c_str()) ) {
            throwGgafCriticalException("GgafProperties::load("<<prm_properties_filename<<") DIR_OGG[0]("<<GgafDxProperties::DIR_OGG[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SKIN_XXX_WAVE")) {
        if (!PathFileExists(GgafDxProperties::DIR_WAVE[0].c_str()) ) {
            throwGgafCriticalException("GgafProperties::load("<<prm_properties_filename<<") DIR_WAVE[0]("<<GgafDxProperties::DIR_WAVE[0]<<") のディレクトリが見つかりません。");
        }
    }

    _TRACE_("GgafDxProperties::FULL_SCREEN=" << GgafDxProperties::FULL_SCREEN);
    _TRACE_("GgafDxProperties::DUAL_VIEW=" << GgafDxProperties::DUAL_VIEW);
    _TRACE_("GgafDxProperties::GAME_BUFFER_WIDTH=" << GgafDxProperties::GAME_BUFFER_WIDTH);
    _TRACE_("GgafDxProperties::GAME_BUFFER_HEIGHT=" << GgafDxProperties::GAME_BUFFER_HEIGHT);
    _TRACE_("GgafDxProperties::GAME_SPACE_DEPTH=" << GgafDxProperties::GAME_SPACE_DEPTH);
    _TRACE_("GgafDxProperties::RENDER_DEPTH_INDEXS_NUM=" << GgafDxProperties::RENDER_DEPTH_INDEXS_NUM);
    _TRACE_("GgafDxProperties::RENDER_DEPTH_STAGE_RATIO=" << GgafDxProperties::RENDER_DEPTH_STAGE_RATIO);
    _TRACE_("GgafDxProperties::PRJ_2D_MODE=" << GgafDxProperties::PRJ_2D_MODE);
    _TRACE_("GgafDxProperties::RENDER_TARGET_BUFFER_WIDTH=" << GgafDxProperties::RENDER_TARGET_BUFFER_WIDTH);
    _TRACE_("GgafDxProperties::RENDER_TARGET_BUFFER_HEIGHT=" << GgafDxProperties::RENDER_TARGET_BUFFER_HEIGHT);
    _TRACE_("GgafDxProperties::SINGLE_VIEW_WINDOW_WIDTH=" << GgafDxProperties::SINGLE_VIEW_WINDOW_WIDTH);
    _TRACE_("GgafDxProperties::SINGLE_VIEW_WINDOW_HEIGHT=" << GgafDxProperties::SINGLE_VIEW_WINDOW_HEIGHT);
    _TRACE_("GgafDxProperties::DUAL_VIEW_WINDOW1_WIDTH=" << GgafDxProperties::DUAL_VIEW_WINDOW1_WIDTH);
    _TRACE_("GgafDxProperties::DUAL_VIEW_WINDOW1_HEIGHT=" << GgafDxProperties::DUAL_VIEW_WINDOW1_HEIGHT);
    _TRACE_("GgafDxProperties::DUAL_VIEW_WINDOW2_WIDTH=" << GgafDxProperties::DUAL_VIEW_WINDOW2_WIDTH);
    _TRACE_("GgafDxProperties::DUAL_VIEW_WINDOW2_HEIGHT=" << GgafDxProperties::DUAL_VIEW_WINDOW2_HEIGHT);
    _TRACE_("GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_WIDTH=" << GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_WIDTH);
    _TRACE_("GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_HEIGHT=" << GgafDxProperties::SINGLE_VIEW_FULL_SCREEN_HEIGHT);
    _TRACE_("GgafDxProperties::FIXED_GAME_VIEW_ASPECT=" << GgafDxProperties::FIXED_GAME_VIEW_ASPECT);
    _TRACE_("GgafDxProperties::FIXED_GAME_VIEW_ASPECT=" << GgafDxProperties::VIEW_AS_RENDER_TARGET_BUFFER_SIZE);
    _TRACE_("GgafDxProperties::SWAP_GAME_VIEW=" << GgafDxProperties::SWAP_GAME_VIEW);
    _TRACE_("GgafDxProperties::SINGLE_VIEW_DRAW_POSITION=" << GgafDxProperties::SINGLE_VIEW_DRAW_POSITION);
    _TRACE_("GgafDxProperties::DUAL_VIEW_DRAW_POSITION1=" << GgafDxProperties::DUAL_VIEW_DRAW_POSITION1);
    _TRACE_("GgafDxProperties::DUAL_VIEW_DRAW_POSITION2=" << GgafDxProperties::DUAL_VIEW_DRAW_POSITION2);
    _TRACE_("GgafDxProperties::VIEW1_WIDTH_RATIO=" << GgafDxProperties::VIEW1_WIDTH_RATIO);
    _TRACE_("GgafDxProperties::VIEW1_HEIGHT_RATIO=" << GgafDxProperties::VIEW1_HEIGHT_RATIO);
    _TRACE_("GgafDxProperties::VIEW2_WIDTH_RATIO=" << GgafDxProperties::VIEW2_WIDTH_RATIO);
    _TRACE_("GgafDxProperties::VIEW2_HEIGHT_RATIO=" << GgafDxProperties::VIEW2_HEIGHT_RATIO);
    _TRACE_("GgafDxProperties::BORDER_COLOR=" << GgafDxProperties::BORDER_COLOR);
    _TRACE_("GgafDxProperties::BG_COLOR=" << GgafDxProperties::BG_COLOR);
    _TRACE_("GgafDxProperties::MASTER_VOLUME=" << GgafDxProperties::MASTER_VOLUME);
    _TRACE_("GgafDxProperties::BGM_VOLUME=" << GgafDxProperties::BGM_VOLUME);
    _TRACE_("GgafDxProperties::SE_VOLUME=" << GgafDxProperties::SE_VOLUME);
    _TRACE_("GgafDxProperties::MAX_SE_AT_ONCE=" << GgafDxProperties::MAX_SE_AT_ONCE);
    _TRACE_("GgafDxProperties::MAX_SE_DELAY=" << GgafDxProperties::MAX_SE_DELAY);
    _TRACE_("GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_MESH=" << GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_MESH);
    _TRACE_("GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_SPRITE=" << GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_SPRITE);
    _TRACE_("GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE=" << GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE);
    _TRACE_("GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_EFFECT=" << GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_EFFECT);
    _TRACE_("GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_OGG=" << GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_OGG);
    _TRACE_("GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_WAVE=" << GgafDxProperties::DIRNAME_RESOURCE_SKIN_XXX_WAVE);

    _TRACE_("GgafDxProperties::DIR_MESH_MODEL[0]=" << GgafDxProperties::DIR_MESH_MODEL[0]);
    _TRACE_("GgafDxProperties::DIR_SPRITE_MODEL[0]=" << GgafDxProperties::DIR_SPRITE_MODEL[0]);
    _TRACE_("GgafDxProperties::DIR_TEXTURE[0]=" << GgafDxProperties::DIR_TEXTURE[0]);
    _TRACE_("GgafDxProperties::DIR_EFFECT[0]=" << GgafDxProperties::DIR_EFFECT[0]);
    _TRACE_("GgafDxProperties::DIR_OGG[0]=" << GgafDxProperties::DIR_OGG[0]);
    _TRACE_("GgafDxProperties::DIR_WAVE[0]=" << GgafDxProperties::DIR_WAVE[0]);

    _TRACE_("GgafDxProperties::DIR_MESH_MODEL[1]=" << GgafDxProperties::DIR_MESH_MODEL[1]);
    _TRACE_("GgafDxProperties::DIR_SPRITE_MODEL[1]=" << GgafDxProperties::DIR_SPRITE_MODEL[1]);
    _TRACE_("GgafDxProperties::DIR_TEXTURE[1]=" << GgafDxProperties::DIR_TEXTURE[1]);
    _TRACE_("GgafDxProperties::DIR_EFFECT[1]=" << GgafDxProperties::DIR_EFFECT[1]);
    _TRACE_("GgafDxProperties::DIR_OGG[1]=" << GgafDxProperties::DIR_OGG[1]);
    _TRACE_("GgafDxProperties::DIR_WAVE[1]=" << GgafDxProperties::DIR_WAVE[1]);

    _TRACE_("GgafDxProperties::DIR_MESH_MODEL[2]=" << GgafDxProperties::DIR_MESH_MODEL[2]);
    _TRACE_("GgafDxProperties::DIR_SPRITE_MODEL[2]=" << GgafDxProperties::DIR_SPRITE_MODEL[2]);
    _TRACE_("GgafDxProperties::DIR_TEXTURE[2]=" << GgafDxProperties::DIR_TEXTURE[2]);
    _TRACE_("GgafDxProperties::DIR_EFFECT[2]=" << GgafDxProperties::DIR_EFFECT[2]);
    _TRACE_("GgafDxProperties::DIR_OGG[2]=" << GgafDxProperties::DIR_OGG[2]);
    _TRACE_("GgafDxProperties::DIR_WAVE[2]=" << GgafDxProperties::DIR_WAVE[2]);
    _TRACE_("GgafDxProperties::REALTIME_EFFECT_COMPILE="<<GgafDxProperties::REALTIME_EFFECT_COMPILE);

}


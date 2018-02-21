#include "jp/ggaf/dxcore/GgafDxConfig.h"

#include <Shlwapi.h>

using namespace GgafCore;
using namespace GgafDxCore;

bool GgafDxConfig::FULL_SCREEN = false;
bool GgafDxConfig::DUAL_VIEW = false;

pixcoord GgafDxConfig::GAME_BUFFER_WIDTH = 1600;
pixcoord GgafDxConfig::GAME_BUFFER_HEIGHT = 450;
double GgafDxConfig::GAME_SPACE_DEPTH = 15.0;
int GgafDxConfig::RENDER_DEPTH_INDEXS_NUM = 256;
double GgafDxConfig::RENDER_DEPTH_STAGE_RATIO = 0.6;
bool GgafDxConfig::PRJ_2D_MODE = false;
pixcoord GgafDxConfig::RENDER_TARGET_BUFFER_WIDTH = 1600;
pixcoord GgafDxConfig::RENDER_TARGET_BUFFER_HEIGHT = 450;

pixcoord GgafDxConfig::VIEW_SOURCE_BUFFER_WIDTH = GgafDxConfig::RENDER_TARGET_BUFFER_WIDTH;
pixcoord GgafDxConfig::VIEW_SOURCE_BUFFER_HEIGHT = GgafDxConfig::RENDER_TARGET_BUFFER_HEIGHT;

pixcoord GgafDxConfig::SINGLE_VIEW_WINDOW_WIDTH = 1600;
pixcoord GgafDxConfig::SINGLE_VIEW_WINDOW_HEIGHT = 450;
pixcoord GgafDxConfig::DUAL_VIEW_WINDOW1_WIDTH = 800;
pixcoord GgafDxConfig::DUAL_VIEW_WINDOW1_HEIGHT = 450;
pixcoord GgafDxConfig::DUAL_VIEW_WINDOW2_WIDTH = 800;
pixcoord GgafDxConfig::DUAL_VIEW_WINDOW2_HEIGHT = 450;
pixcoord GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_WIDTH = 1600;
pixcoord GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_HEIGHT = 900;
pixcoord GgafDxConfig::DUAL_VIEW_FULL_SCREEN1_WIDTH = 1600;
pixcoord GgafDxConfig::DUAL_VIEW_FULL_SCREEN1_HEIGHT = 900;
pixcoord GgafDxConfig::DUAL_VIEW_FULL_SCREEN2_WIDTH = 1600;
pixcoord GgafDxConfig::DUAL_VIEW_FULL_SCREEN2_HEIGHT = 900;

pixcoord GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_WIDTH_BK  = GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_WIDTH;
pixcoord GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_HEIGHT_BK = GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_HEIGHT;
pixcoord GgafDxConfig::DUAL_VIEW_FULL_SCREEN1_WIDTH_BK   = GgafDxConfig::DUAL_VIEW_FULL_SCREEN1_WIDTH;
pixcoord GgafDxConfig::DUAL_VIEW_FULL_SCREEN1_HEIGHT_BK  = GgafDxConfig::DUAL_VIEW_FULL_SCREEN1_HEIGHT;
pixcoord GgafDxConfig::DUAL_VIEW_FULL_SCREEN2_WIDTH_BK   = GgafDxConfig::DUAL_VIEW_FULL_SCREEN2_WIDTH;
pixcoord GgafDxConfig::DUAL_VIEW_FULL_SCREEN2_HEIGHT_BK  = GgafDxConfig::DUAL_VIEW_FULL_SCREEN2_HEIGHT;


bool GgafDxConfig::FIXED_GAME_VIEW_ASPECT = false;
int GgafDxConfig::PRIMARY_ADAPTER_NO = 0;
int GgafDxConfig::SECONDARY_ADAPTER_NO = 1;

bool GgafDxConfig::SWAP_GAME_VIEW = false;
int GgafDxConfig::SINGLE_VIEW_DRAW_POSITION = 5;
int GgafDxConfig::DUAL_VIEW_DRAW_POSITION1 = 6;
int GgafDxConfig::DUAL_VIEW_DRAW_POSITION2 = 4;

double GgafDxConfig::VIEW1_WIDTH_RATIO = 1.0;
double GgafDxConfig::VIEW1_HEIGHT_RATIO = 1.0;
double GgafDxConfig::VIEW2_WIDTH_RATIO = 1.0;
double GgafDxConfig::VIEW2_HEIGHT_RATIO = 1.0;

std::string GgafDxConfig::BORDER_COLOR = "#222222";
std::string GgafDxConfig::BG_COLOR = "#000000";

int GgafDxConfig::MASTER_VOLUME = 800;
int GgafDxConfig::BGM_VOLUME = 800;
int GgafDxConfig::SE_VOLUME = 800;
int GgafDxConfig::MAX_SE_AT_ONCE = 16;
int GgafDxConfig::MAX_SE_DELAY = 240;

std::string GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_MESH = "mesh";
std::string GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_SPRITE = "sprite";
std::string GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE = "texture";
std::string GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_EFFECT = "effect";
std::string GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_OGG = "ogg";
std::string GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_WAVE = "wave";

std::string GgafDxConfig::DIR_MESH_MODEL[] = {
                GgafConfig::DIR_SKIN_KIND[0] + "/" + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_MESH,
                GgafConfig::DIR_SKIN_KIND[1] + "/" + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_MESH,
                GgafConfig::DIR_SKIN_KIND[2] + "/"
            };
std::string GgafDxConfig::DIR_SPRITE_MODEL[] = {
                GgafConfig::DIR_SKIN_KIND[0] + "/" + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_SPRITE + "/",
                GgafConfig::DIR_SKIN_KIND[1] + "/" + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_SPRITE + "/",
                GgafConfig::DIR_SKIN_KIND[2] + "/"
            };
std::string GgafDxConfig::DIR_TEXTURE[] = {
                GgafConfig::DIR_SKIN_KIND[0] + "/" + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/",
                GgafConfig::DIR_SKIN_KIND[1] + "/" + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/",
                GgafConfig::DIR_SKIN_KIND[2]
            };
std::string GgafDxConfig::DIR_EFFECT[] = {
                GgafConfig::DIR_SKIN_KIND[0] + "/" + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_EFFECT + "/",
                GgafConfig::DIR_SKIN_KIND[1] + "/" + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_EFFECT + "/",
                GgafConfig::DIR_SKIN_KIND[2]
            };
std::string GgafDxConfig::DIR_OGG[] = {
                GgafConfig::DIR_SKIN_KIND[0] + "/" + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_OGG + "/",
                GgafConfig::DIR_SKIN_KIND[1] + "/" + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_OGG + "/",
                GgafConfig::DIR_SKIN_KIND[2]
            };
std::string GgafDxConfig::DIR_WAVE[] = {
                GgafConfig::DIR_SKIN_KIND[0] + "/" + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_WAVE + "/",
                GgafConfig::DIR_SKIN_KIND[1] + "/" + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_WAVE + "/",
                GgafConfig::DIR_SKIN_KIND[2]
            };

bool GgafDxConfig::REALTIME_EFFECT_COMPILE = false;

std::string GgafDxConfig::ILLIGAL_TEXTURE = "GgafDxIlligalTexture.dds";
std::string GgafDxConfig::ILLIGAL_CUBEMAP_TEXTURE = "GgafDxIlligalCubeMapTexture.dds";
std::string GgafDxConfig::WHITE_TEXTURE = "GgafDxWhite.dds";
std::string GgafDxConfig::COLI_AABOX_MODEL = "GgafDxAAB";
std::string GgafDxConfig::COLI_AAPRISM_MODEL = "GgafDxAAPrism";
std::string GgafDxConfig::COLI_AAPYRAMID_MODEL = "GgafDxAAPyramid";
std::string GgafDxConfig::COLI_SPHERE_MODEL = "GgafDxSphere";


void GgafDxConfig::loadProperties(std::string prm_properties_filename) {
    GgafConfig::loadProperties(prm_properties_filename);

    if (GgafConfig::_properties.isExistKey("FULL_SCREEN")) {
        GgafDxConfig::FULL_SCREEN = GgafConfig::_properties.getBool("FULL_SCREEN");
    }
    if (GgafConfig::_properties.isExistKey("DUAL_VIEW")) {
        GgafDxConfig::DUAL_VIEW = GgafConfig::_properties.getBool("DUAL_VIEW");
    }
    if (GgafConfig::_properties.isExistKey("GAME_BUFFER_WIDTH")) {
        GgafDxConfig::GAME_BUFFER_WIDTH = GgafConfig::_properties.getInt("GAME_BUFFER_WIDTH");
    }
    if (GgafConfig::_properties.isExistKey("GAME_BUFFER_HEIGHT")) {
        GgafDxConfig::GAME_BUFFER_HEIGHT = GgafConfig::_properties.getInt("GAME_BUFFER_HEIGHT");
    }
    if (GgafConfig::_properties.isExistKey("GAME_SPACE_DEPTH")) {
        GgafDxConfig::GAME_SPACE_DEPTH = GgafConfig::_properties.getDouble("GAME_SPACE_DEPTH");
    }
    if (GgafConfig::_properties.isExistKey("RENDER_DEPTH_INDEXS_NUM")) {
        GgafDxConfig::RENDER_DEPTH_INDEXS_NUM = GgafConfig::_properties.getInt("RENDER_DEPTH_INDEXS_NUM");
    }
    if (GgafConfig::_properties.isExistKey("RENDER_DEPTH_STAGE_RATIO")) {
        GgafDxConfig::RENDER_DEPTH_STAGE_RATIO = GgafConfig::_properties.getDouble("RENDER_DEPTH_STAGE_RATIO");
    }
    if (GgafConfig::_properties.isExistKey("PRJ_2D_MODE")) {
        GgafDxConfig::PRJ_2D_MODE = GgafConfig::_properties.getBool("PRJ_2D_MODE");
    }
    if (GgafConfig::_properties.isExistKey("RENDER_TARGET_BUFFER_WIDTH")) {
        GgafDxConfig::RENDER_TARGET_BUFFER_WIDTH = GgafConfig::_properties.getInt("RENDER_TARGET_BUFFER_WIDTH");
    }
    if (GgafConfig::_properties.isExistKey("RENDER_TARGET_BUFFER_HEIGHT")) {
        GgafDxConfig::RENDER_TARGET_BUFFER_HEIGHT = GgafConfig::_properties.getInt("RENDER_TARGET_BUFFER_HEIGHT");
    }
    if (GgafConfig::_properties.isExistKey("VIEW_SOURCE_BUFFER_WIDTH")) {
        GgafDxConfig::VIEW_SOURCE_BUFFER_WIDTH = GgafConfig::_properties.getInt("VIEW_SOURCE_BUFFER_WIDTH");
    } else {
        GgafDxConfig::VIEW_SOURCE_BUFFER_WIDTH = GgafDxConfig::RENDER_TARGET_BUFFER_WIDTH;
    }
    if (GgafConfig::_properties.isExistKey("VIEW_SOURCE_BUFFER_HEIGHT")) {
        GgafDxConfig::VIEW_SOURCE_BUFFER_HEIGHT = GgafConfig::_properties.getInt("VIEW_SOURCE_BUFFER_HEIGHT");
    } else {
        GgafDxConfig::VIEW_SOURCE_BUFFER_HEIGHT = GgafDxConfig::RENDER_TARGET_BUFFER_HEIGHT;
    }
    if (GgafConfig::_properties.isExistKey("SINGLE_VIEW_WINDOW_WIDTH")) {
        GgafDxConfig::SINGLE_VIEW_WINDOW_WIDTH = GgafConfig::_properties.getInt("SINGLE_VIEW_WINDOW_WIDTH");
    }
    if (GgafConfig::_properties.isExistKey("SINGLE_VIEW_WINDOW_HEIGHT")) {
        GgafDxConfig::SINGLE_VIEW_WINDOW_HEIGHT = GgafConfig::_properties.getInt("SINGLE_VIEW_WINDOW_HEIGHT");
    }
    if (GgafConfig::_properties.isExistKey("DUAL_VIEW_WINDOW1_WIDTH")) {
        GgafDxConfig::DUAL_VIEW_WINDOW1_WIDTH = GgafConfig::_properties.getInt("DUAL_VIEW_WINDOW1_WIDTH");
    }
    if (GgafConfig::_properties.isExistKey("DUAL_VIEW_WINDOW1_HEIGHT")) {
        GgafDxConfig::DUAL_VIEW_WINDOW1_HEIGHT = GgafConfig::_properties.getInt("DUAL_VIEW_WINDOW1_HEIGHT");
    }
    if (GgafConfig::_properties.isExistKey("DUAL_VIEW_WINDOW2_WIDTH")) {
        GgafDxConfig::DUAL_VIEW_WINDOW2_WIDTH = GgafConfig::_properties.getInt("DUAL_VIEW_WINDOW2_WIDTH");
    }
    if (GgafConfig::_properties.isExistKey("DUAL_VIEW_WINDOW2_HEIGHT")) {
        GgafDxConfig::DUAL_VIEW_WINDOW2_HEIGHT = GgafConfig::_properties.getInt("DUAL_VIEW_WINDOW2_HEIGHT");
    }

    if (GgafConfig::_properties.isExistKey("SINGLE_VIEW_FULL_SCREEN_WIDTH")) {
        GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_WIDTH = GgafConfig::_properties.getInt("SINGLE_VIEW_FULL_SCREEN_WIDTH");
        GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_WIDTH_BK  = GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_WIDTH;
    }
    if (GgafConfig::_properties.isExistKey("SINGLE_VIEW_FULL_SCREEN_HEIGHT")) {
        GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_HEIGHT = GgafConfig::_properties.getInt("SINGLE_VIEW_FULL_SCREEN_HEIGHT");
        GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_HEIGHT_BK = GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_HEIGHT;
    }

    if (GgafConfig::_properties.isExistKey("DUAL_VIEW_FULL_SCREEN1_WIDTH")) {
        GgafDxConfig::DUAL_VIEW_FULL_SCREEN1_WIDTH = GgafConfig::_properties.getInt("DUAL_VIEW_FULL_SCREEN1_WIDTH");
        GgafDxConfig::DUAL_VIEW_FULL_SCREEN1_WIDTH_BK   = GgafDxConfig::DUAL_VIEW_FULL_SCREEN1_WIDTH;
    }
    if (GgafConfig::_properties.isExistKey("DUAL_VIEW_FULL_SCREEN1_HEIGHT")) {
        GgafDxConfig::DUAL_VIEW_FULL_SCREEN1_HEIGHT = GgafConfig::_properties.getInt("DUAL_VIEW_FULL_SCREEN1_HEIGHT");
        GgafDxConfig::DUAL_VIEW_FULL_SCREEN1_HEIGHT_BK  = GgafDxConfig::DUAL_VIEW_FULL_SCREEN1_HEIGHT;
    }
    if (GgafConfig::_properties.isExistKey("DUAL_VIEW_FULL_SCREEN2_WIDTH")) {
        GgafDxConfig::DUAL_VIEW_FULL_SCREEN2_WIDTH = GgafConfig::_properties.getInt("DUAL_VIEW_FULL_SCREEN2_WIDTH");
        GgafDxConfig::DUAL_VIEW_FULL_SCREEN2_WIDTH_BK   = GgafDxConfig::DUAL_VIEW_FULL_SCREEN2_WIDTH;
    }
    if (GgafConfig::_properties.isExistKey("DUAL_VIEW_FULL_SCREEN2_HEIGHT")) {
        GgafDxConfig::DUAL_VIEW_FULL_SCREEN2_HEIGHT = GgafConfig::_properties.getInt("DUAL_VIEW_FULL_SCREEN2_HEIGHT");
        GgafDxConfig::DUAL_VIEW_FULL_SCREEN2_HEIGHT_BK  = GgafDxConfig::DUAL_VIEW_FULL_SCREEN2_HEIGHT;
    }

    if (GgafConfig::_properties.isExistKey("FIXED_GAME_VIEW_ASPECT")) {
        GgafDxConfig::FIXED_GAME_VIEW_ASPECT = GgafConfig::_properties.getBool("FIXED_GAME_VIEW_ASPECT");
    }

    if (GgafConfig::_properties.isExistKey("PRIMARY_ADAPTER_NO")) {
        GgafDxConfig::PRIMARY_ADAPTER_NO = GgafConfig::_properties.getInt("PRIMARY_ADAPTER_NO");
    }
    if (GgafConfig::_properties.isExistKey("SECONDARY_ADAPTER_NO")) {
        GgafDxConfig::SECONDARY_ADAPTER_NO = GgafConfig::_properties.getInt("SECONDARY_ADAPTER_NO");
    }
    if (GgafConfig::_properties.isExistKey("SWAP_GAME_VIEW")) {
        GgafDxConfig::SWAP_GAME_VIEW = GgafConfig::_properties.getBool("SWAP_GAME_VIEW");
    }
    if (GgafConfig::_properties.isExistKey("SINGLE_VIEW_DRAW_POSITION")) {
        GgafDxConfig::SINGLE_VIEW_DRAW_POSITION = GgafConfig::_properties.getInt("SINGLE_VIEW_DRAW_POSITION");
    }
    if (GgafConfig::_properties.isExistKey("DUAL_VIEW_DRAW_POSITION1")) {
        GgafDxConfig::DUAL_VIEW_DRAW_POSITION1 = GgafConfig::_properties.getInt("DUAL_VIEW_DRAW_POSITION1");
    }
    if (GgafConfig::_properties.isExistKey("DUAL_VIEW_DRAW_POSITION2")) {
        GgafDxConfig::DUAL_VIEW_DRAW_POSITION2 = GgafConfig::_properties.getInt("DUAL_VIEW_DRAW_POSITION2");
    }

    if (GgafConfig::_properties.isExistKey("VIEW1_WIDTH_RATIO")) {
        GgafDxConfig::VIEW1_WIDTH_RATIO = GgafConfig::_properties.getDouble("VIEW1_WIDTH_RATIO");
    }
    if (GgafConfig::_properties.isExistKey("VIEW1_HEIGHT_RATIO")) {
        GgafDxConfig::VIEW1_HEIGHT_RATIO = GgafConfig::_properties.getDouble("VIEW1_HEIGHT_RATIO");
    }
    if (GgafConfig::_properties.isExistKey("VIEW2_WIDTH_RATIO")) {
        GgafDxConfig::VIEW2_WIDTH_RATIO = GgafConfig::_properties.getDouble("VIEW2_WIDTH_RATIO");
    }
    if (GgafConfig::_properties.isExistKey("VIEW1_HEIGHT_RATIO")) {
        GgafDxConfig::VIEW2_HEIGHT_RATIO = GgafConfig::_properties.getDouble("VIEW2_HEIGHT_RATIO");
    }

    if (GgafConfig::_properties.isExistKey("BORDER_COLOR")) {
        GgafDxConfig::BORDER_COLOR = GgafConfig::_properties.getStr("BORDER_COLOR");
    }
    if (GgafConfig::_properties.isExistKey("BG_COLOR")) {
        GgafDxConfig::BG_COLOR = GgafConfig::_properties.getStr("BG_COLOR");
    }
    if (GgafConfig::_properties.isExistKey("MASTER_VOLUME")) {
        GgafDxConfig::MASTER_VOLUME = GgafConfig::_properties.getInt("MASTER_VOLUME");
    }
    if (GgafConfig::_properties.isExistKey("BGM_VOLUME")) {
        GgafDxConfig::BGM_VOLUME = GgafConfig::_properties.getInt("BGM_VOLUME");
    }
    if (GgafConfig::_properties.isExistKey("SE_VOLUME")) {
        GgafDxConfig::SE_VOLUME = GgafConfig::_properties.getInt("SE_VOLUME");
    }
    if (GgafConfig::_properties.isExistKey("MAX_SE_AT_ONCE")) {
        GgafDxConfig::MAX_SE_AT_ONCE = GgafConfig::_properties.getInt("MAX_SE_AT_ONCE");
    }
    if (GgafConfig::_properties.isExistKey("MAX_SE_DELAY")) {
        GgafDxConfig::MAX_SE_DELAY = GgafConfig::_properties.getInt("MAX_SE_DELAY");
    }
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_MESH")) {
        GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_MESH = GgafConfig::_properties.getStr("DIRNAME_RESOURCE_SKIN_XXX_MESH");
    }
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_SPRITE")) {
        GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_SPRITE = GgafConfig::_properties.getStr("DIRNAME_RESOURCE_SKIN_XXX_SPRITE");
    }
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_TEXTURE")) {
        GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE = GgafConfig::_properties.getStr("DIRNAME_RESOURCE_SKIN_XXX_TEXTURE");
    }
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_EFFECT")) {
        GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_EFFECT = GgafConfig::_properties.getStr("DIRNAME_RESOURCE_SKIN_XXX_EFFECT");
    }
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_OGG")) {
        GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_OGG = GgafConfig::_properties.getStr("DIRNAME_RESOURCE_SKIN_XXX_OGG");
    }
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_WAVE")) {
        GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_WAVE = GgafConfig::_properties.getStr("DIRNAME_RESOURCE_SKIN_XXX_WAVE");
    }
    if (GgafConfig::_properties.isExistKey("REALTIME_EFFECT_COMPILE")) {
        GgafDxConfig::REALTIME_EFFECT_COMPILE = GgafConfig::_properties.getBool("REALTIME_EFFECT_COMPILE");
    }


    if (GgafConfig::_properties.isExistKey("ILLIGAL_TEXTURE")) {
        GgafDxConfig::ILLIGAL_TEXTURE = GgafConfig::_properties.getStr("ILLIGAL_TEXTURE");
    }
    if (GgafConfig::_properties.isExistKey("ILLIGAL_CUBEMAP_TEXTURE")) {
        GgafDxConfig::ILLIGAL_CUBEMAP_TEXTURE = GgafConfig::_properties.getStr("ILLIGAL_CUBEMAP_TEXTURE");
    }
    if (GgafConfig::_properties.isExistKey("WHITE_TEXTURE")) {
        GgafDxConfig::WHITE_TEXTURE = GgafConfig::_properties.getStr("WHITE_TEXTURE");
    }
    if (GgafConfig::_properties.isExistKey("COLI_AABOX_MODEL")) {
        GgafDxConfig::COLI_AABOX_MODEL = GgafConfig::_properties.getStr("COLI_AABOX_MODEL");
    }
    if (GgafConfig::_properties.isExistKey("COLI_AAPRISM_MODEL")) {
        GgafDxConfig::COLI_AAPRISM_MODEL = GgafConfig::_properties.getStr("COLI_AAPRISM_MODEL");
    }
    if (GgafConfig::_properties.isExistKey("COLI_AAPYRAMID_MODEL")) {
        GgafDxConfig::COLI_AAPYRAMID_MODEL = GgafConfig::_properties.getStr("COLI_AAPYRAMID_MODEL");
    }
    if (GgafConfig::_properties.isExistKey("COLI_SPHERE_MODEL")) {
        GgafDxConfig::COLI_SPHERE_MODEL = GgafConfig::_properties.getStr("COLI_SPHERE_MODEL");
    }


    GgafDxConfig::DIR_MESH_MODEL[0] = GgafConfig::DIR_SKIN_KIND[0] + "/"
            + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_MESH + "/";
    GgafDxConfig::DIR_SPRITE_MODEL[0] = GgafConfig::DIR_SKIN_KIND[0] + "/"
            + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_SPRITE + "/";
    GgafDxConfig::DIR_TEXTURE[0] = GgafConfig::DIR_SKIN_KIND[0] + "/"
            + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
    GgafDxConfig::DIR_EFFECT[0] = GgafConfig::DIR_SKIN_KIND[0] + "/"
            + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_EFFECT + "/";
    GgafDxConfig::DIR_OGG[0] = GgafConfig::DIR_SKIN_KIND[0] + "/"
            + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_OGG + "/";
    GgafDxConfig::DIR_WAVE[0] = GgafConfig::DIR_SKIN_KIND[0] + "/"
            + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_WAVE + "/";

    GgafDxConfig::DIR_MESH_MODEL[1] = GgafConfig::DIR_SKIN_KIND[1] + "/"
            + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_MESH + "/";
    GgafDxConfig::DIR_SPRITE_MODEL[1] = GgafConfig::DIR_SKIN_KIND[1] + "/"
            + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_SPRITE + "/";
    GgafDxConfig::DIR_TEXTURE[1] = GgafConfig::DIR_SKIN_KIND[1] + "/"
            + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
    GgafDxConfig::DIR_EFFECT[1] = GgafConfig::DIR_SKIN_KIND[1] + "/"
            + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_EFFECT + "/";
    GgafDxConfig::DIR_OGG[1] = GgafConfig::DIR_SKIN_KIND[1] + "/"
            + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_OGG + "/";
    GgafDxConfig::DIR_WAVE[1] = GgafConfig::DIR_SKIN_KIND[1] + "/"
            + GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_WAVE + "/";

    GgafDxConfig::DIR_MESH_MODEL[2] = GgafConfig::DIR_SKIN_KIND[2] + "/";
    GgafDxConfig::DIR_SPRITE_MODEL[2] = GgafConfig::DIR_SKIN_KIND[2] + "/";
    GgafDxConfig::DIR_TEXTURE[2] = GgafConfig::DIR_SKIN_KIND[2] + "/";
    GgafDxConfig::DIR_EFFECT[2] = GgafConfig::DIR_SKIN_KIND[2] + "/";
    GgafDxConfig::DIR_OGG[2] = GgafConfig::DIR_SKIN_KIND[2] + "/";
    GgafDxConfig::DIR_WAVE[2] = GgafConfig::DIR_SKIN_KIND[2] + "/";


    UTIL::strReplace(GgafDxConfig::DIR_MESH_MODEL[0]    , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_SPRITE_MODEL[0]  , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_TEXTURE[0]       , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_EFFECT[0]        , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_OGG[0]           , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_WAVE[0]          , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_MESH_MODEL[1]    , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_SPRITE_MODEL[1]  , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_TEXTURE[1]       , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_EFFECT[1]        , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_OGG[1]           , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_WAVE[1]          , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_MESH_MODEL[2]    , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_SPRITE_MODEL[2]  , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_TEXTURE[2]       , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_EFFECT[2]        , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_OGG[2]           , "//", "/");
    UTIL::strReplace(GgafDxConfig::DIR_WAVE[2]          , "//", "/");

    //リソースディレクトリ名指定があるのならば、デフォルトのスキンディレクトリのリソースディレクトリ存在チェック
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_MESH")) {
        if (!PathFileExists(GgafDxConfig::DIR_MESH_MODEL[0].c_str()) ) {
            throwGgafCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_MESH_MODEL[0]("<<GgafDxConfig::DIR_MESH_MODEL[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_SPRITE")) {
        if (!PathFileExists(GgafDxConfig::DIR_SPRITE_MODEL[0].c_str()) ) {
            throwGgafCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_SPRITE_MODEL[0]("<<GgafDxConfig::DIR_SPRITE_MODEL[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_TEXTURE")) {
        if (!PathFileExists(GgafDxConfig::DIR_TEXTURE[0].c_str()) ) {
            throwGgafCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_TEXTURE[0]("<<GgafDxConfig::DIR_TEXTURE[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_EFFECT")) {
        if (!PathFileExists(GgafDxConfig::DIR_EFFECT[0].c_str()) ) {
            throwGgafCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_EFFECT[0]("<<GgafDxConfig::DIR_EFFECT[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_OGG")) {
        if (!PathFileExists(GgafDxConfig::DIR_OGG[0].c_str()) ) {
            throwGgafCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_OGG[0]("<<GgafDxConfig::DIR_OGG[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_WAVE")) {
        if (!PathFileExists(GgafDxConfig::DIR_WAVE[0].c_str()) ) {
            throwGgafCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_WAVE[0]("<<GgafDxConfig::DIR_WAVE[0]<<") のディレクトリが見つかりません。");
        }
    }

    _TRACE_("GgafDxConfig::FULL_SCREEN=" << GgafDxConfig::FULL_SCREEN);
    _TRACE_("GgafDxConfig::DUAL_VIEW=" << GgafDxConfig::DUAL_VIEW);
    _TRACE_("GgafDxConfig::GAME_BUFFER_WIDTH=" << GgafDxConfig::GAME_BUFFER_WIDTH);
    _TRACE_("GgafDxConfig::GAME_BUFFER_HEIGHT=" << GgafDxConfig::GAME_BUFFER_HEIGHT);
    _TRACE_("GgafDxConfig::GAME_SPACE_DEPTH=" << GgafDxConfig::GAME_SPACE_DEPTH);
    _TRACE_("GgafDxConfig::RENDER_DEPTH_INDEXS_NUM=" << GgafDxConfig::RENDER_DEPTH_INDEXS_NUM);
    _TRACE_("GgafDxConfig::RENDER_DEPTH_STAGE_RATIO=" << GgafDxConfig::RENDER_DEPTH_STAGE_RATIO);
    _TRACE_("GgafDxConfig::PRJ_2D_MODE=" << GgafDxConfig::PRJ_2D_MODE);
    _TRACE_("GgafDxConfig::RENDER_TARGET_BUFFER_WIDTH=" << GgafDxConfig::RENDER_TARGET_BUFFER_WIDTH);
    _TRACE_("GgafDxConfig::RENDER_TARGET_BUFFER_HEIGHT=" << GgafDxConfig::RENDER_TARGET_BUFFER_HEIGHT);
    _TRACE_("GgafDxConfig::VIEW_SOURCE_BUFFER_WIDTH=" << GgafDxConfig::VIEW_SOURCE_BUFFER_WIDTH);
    _TRACE_("GgafDxConfig::VIEW_SOURCE_BUFFER_HEIGHT=" << GgafDxConfig::VIEW_SOURCE_BUFFER_HEIGHT);
    _TRACE_("GgafDxConfig::SINGLE_VIEW_WINDOW_WIDTH=" << GgafDxConfig::SINGLE_VIEW_WINDOW_WIDTH);
    _TRACE_("GgafDxConfig::SINGLE_VIEW_WINDOW_HEIGHT=" << GgafDxConfig::SINGLE_VIEW_WINDOW_HEIGHT);
    _TRACE_("GgafDxConfig::DUAL_VIEW_WINDOW1_WIDTH=" << GgafDxConfig::DUAL_VIEW_WINDOW1_WIDTH);
    _TRACE_("GgafDxConfig::DUAL_VIEW_WINDOW1_HEIGHT=" << GgafDxConfig::DUAL_VIEW_WINDOW1_HEIGHT);
    _TRACE_("GgafDxConfig::DUAL_VIEW_WINDOW2_WIDTH=" << GgafDxConfig::DUAL_VIEW_WINDOW2_WIDTH);
    _TRACE_("GgafDxConfig::DUAL_VIEW_WINDOW2_HEIGHT=" << GgafDxConfig::DUAL_VIEW_WINDOW2_HEIGHT);
    _TRACE_("GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_WIDTH=" << GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_WIDTH);
    _TRACE_("GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_HEIGHT=" << GgafDxConfig::SINGLE_VIEW_FULL_SCREEN_HEIGHT);
    _TRACE_("GgafDxConfig::FIXED_GAME_VIEW_ASPECT=" << GgafDxConfig::FIXED_GAME_VIEW_ASPECT);

    _TRACE_("GgafDxConfig::PRIMARY_ADAPTER_NO=" << GgafDxConfig::PRIMARY_ADAPTER_NO);
    _TRACE_("GgafDxConfig::SECONDARY_ADAPTER_NO=" << GgafDxConfig::SECONDARY_ADAPTER_NO);
    _TRACE_("GgafDxConfig::SWAP_GAME_VIEW=" << GgafDxConfig::SWAP_GAME_VIEW);
    _TRACE_("GgafDxConfig::SINGLE_VIEW_DRAW_POSITION=" << GgafDxConfig::SINGLE_VIEW_DRAW_POSITION);
    _TRACE_("GgafDxConfig::DUAL_VIEW_DRAW_POSITION1=" << GgafDxConfig::DUAL_VIEW_DRAW_POSITION1);
    _TRACE_("GgafDxConfig::DUAL_VIEW_DRAW_POSITION2=" << GgafDxConfig::DUAL_VIEW_DRAW_POSITION2);
    _TRACE_("GgafDxConfig::VIEW1_WIDTH_RATIO=" << GgafDxConfig::VIEW1_WIDTH_RATIO);
    _TRACE_("GgafDxConfig::VIEW1_HEIGHT_RATIO=" << GgafDxConfig::VIEW1_HEIGHT_RATIO);
    _TRACE_("GgafDxConfig::VIEW2_WIDTH_RATIO=" << GgafDxConfig::VIEW2_WIDTH_RATIO);
    _TRACE_("GgafDxConfig::VIEW2_HEIGHT_RATIO=" << GgafDxConfig::VIEW2_HEIGHT_RATIO);
    _TRACE_("GgafDxConfig::BORDER_COLOR=" << GgafDxConfig::BORDER_COLOR);
    _TRACE_("GgafDxConfig::BG_COLOR=" << GgafDxConfig::BG_COLOR);
    _TRACE_("GgafDxConfig::MASTER_VOLUME=" << GgafDxConfig::MASTER_VOLUME);
    _TRACE_("GgafDxConfig::BGM_VOLUME=" << GgafDxConfig::BGM_VOLUME);
    _TRACE_("GgafDxConfig::SE_VOLUME=" << GgafDxConfig::SE_VOLUME);
    _TRACE_("GgafDxConfig::MAX_SE_AT_ONCE=" << GgafDxConfig::MAX_SE_AT_ONCE);
    _TRACE_("GgafDxConfig::MAX_SE_DELAY=" << GgafDxConfig::MAX_SE_DELAY);
    _TRACE_("GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_MESH=" << GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_MESH);
    _TRACE_("GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_SPRITE=" << GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_SPRITE);
    _TRACE_("GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE=" << GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE);
    _TRACE_("GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_EFFECT=" << GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_EFFECT);
    _TRACE_("GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_OGG=" << GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_OGG);
    _TRACE_("GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_WAVE=" << GgafDxConfig::DIRNAME_RESOURCE_SKIN_XXX_WAVE);

    _TRACE_("GgafDxConfig::DIR_MESH_MODEL[0]=" << GgafDxConfig::DIR_MESH_MODEL[0]);
    _TRACE_("GgafDxConfig::DIR_SPRITE_MODEL[0]=" << GgafDxConfig::DIR_SPRITE_MODEL[0]);
    _TRACE_("GgafDxConfig::DIR_TEXTURE[0]=" << GgafDxConfig::DIR_TEXTURE[0]);
    _TRACE_("GgafDxConfig::DIR_EFFECT[0]=" << GgafDxConfig::DIR_EFFECT[0]);
    _TRACE_("GgafDxConfig::DIR_OGG[0]=" << GgafDxConfig::DIR_OGG[0]);
    _TRACE_("GgafDxConfig::DIR_WAVE[0]=" << GgafDxConfig::DIR_WAVE[0]);

    _TRACE_("GgafDxConfig::DIR_MESH_MODEL[1]=" << GgafDxConfig::DIR_MESH_MODEL[1]);
    _TRACE_("GgafDxConfig::DIR_SPRITE_MODEL[1]=" << GgafDxConfig::DIR_SPRITE_MODEL[1]);
    _TRACE_("GgafDxConfig::DIR_TEXTURE[1]=" << GgafDxConfig::DIR_TEXTURE[1]);
    _TRACE_("GgafDxConfig::DIR_EFFECT[1]=" << GgafDxConfig::DIR_EFFECT[1]);
    _TRACE_("GgafDxConfig::DIR_OGG[1]=" << GgafDxConfig::DIR_OGG[1]);
    _TRACE_("GgafDxConfig::DIR_WAVE[1]=" << GgafDxConfig::DIR_WAVE[1]);

    _TRACE_("GgafDxConfig::DIR_MESH_MODEL[2]=" << GgafDxConfig::DIR_MESH_MODEL[2]);
    _TRACE_("GgafDxConfig::DIR_SPRITE_MODEL[2]=" << GgafDxConfig::DIR_SPRITE_MODEL[2]);
    _TRACE_("GgafDxConfig::DIR_TEXTURE[2]=" << GgafDxConfig::DIR_TEXTURE[2]);
    _TRACE_("GgafDxConfig::DIR_EFFECT[2]=" << GgafDxConfig::DIR_EFFECT[2]);
    _TRACE_("GgafDxConfig::DIR_OGG[2]=" << GgafDxConfig::DIR_OGG[2]);
    _TRACE_("GgafDxConfig::DIR_WAVE[2]=" << GgafDxConfig::DIR_WAVE[2]);
    _TRACE_("GgafDxConfig::REALTIME_EFFECT_COMPILE="<<GgafDxConfig::REALTIME_EFFECT_COMPILE);

}


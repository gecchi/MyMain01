#include "jp/ggaf/dx/Config.h"

#include <Shlwapi.h>


using namespace GgafDx;

bool Config::FULL_SCREEN = false;
bool Config::DUAL_VIEW = false;

pixcoord Config::GAME_BUFFER_WIDTH = 1600;
pixcoord Config::GAME_BUFFER_HEIGHT = 450;
double Config::GAME_SPACE_DEPTH = 15.0;
int Config::RENDER_DEPTH_INDEXS_NUM = 256;
int Config::RENDER_DEPTH_INDEXS_NUM_EX_NEAR = 10;
int Config::RENDER_DEPTH_INDEXS_NUM_EX_FAR = 10;
double Config::RENDER_DEPTH_STAGE_RATIO = 0.6;
bool Config::PRJ_2D_MODE = false;

pixcoord Config::RENDER_TARGET_BUFFER_WIDTH = Config::GAME_BUFFER_WIDTH;
pixcoord Config::RENDER_TARGET_BUFFER_HEIGHT = Config::GAME_BUFFER_HEIGHT;

int Config::PRIMARY_DISPLAY_NO = 0;
int Config::SECONDARY_DISPLAY_NO = 1;

pixcoord Config::PRIMARY_RENDER_BUFFER_SOURCE_LEFT   = 0;
pixcoord Config::PRIMARY_RENDER_BUFFER_SOURCE_TOP    = 0;
pixcoord Config::PRIMARY_RENDER_BUFFER_SOURCE_WIDTH  = Config::RENDER_TARGET_BUFFER_WIDTH;
pixcoord Config::PRIMARY_RENDER_BUFFER_SOURCE_HEIGHT = Config::RENDER_TARGET_BUFFER_HEIGHT;

pixcoord Config::SECONDARY_RENDER_BUFFER_SOURCE_LEFT   = Config::RENDER_TARGET_BUFFER_WIDTH/2;
pixcoord Config::SECONDARY_RENDER_BUFFER_SOURCE_TOP    = 0;
pixcoord Config::SECONDARY_RENDER_BUFFER_SOURCE_WIDTH  = Config::RENDER_TARGET_BUFFER_WIDTH/2;
pixcoord Config::SECONDARY_RENDER_BUFFER_SOURCE_HEIGHT = Config::RENDER_TARGET_BUFFER_HEIGHT;

pixcoord Config::PRIMARY_WINDOW_WIDTH = 1600;
pixcoord Config::PRIMARY_WINDOW_HEIGHT = 450;
pixcoord Config::SECONDARY_WINDOW_WIDTH = 800;
pixcoord Config::SECONDARY_WINDOW_HEIGHT = 450;
//0の場合現在の解像度でフルスクリーン
pixcoord Config::PRIMARY_FULL_SCREEN_WIDTH = 0;
pixcoord Config::PRIMARY_FULL_SCREEN_HEIGHT = 0;
pixcoord Config::SECONDARY_FULL_SCREEN_WIDTH = 0;
pixcoord Config::SECONDARY_FULL_SCREEN_HEIGHT = 0;

pixcoord Config::PRIMARY_FULL_SCREEN_WIDTH_BK   = Config::PRIMARY_FULL_SCREEN_WIDTH;
pixcoord Config::PRIMARY_FULL_SCREEN_HEIGHT_BK  = Config::PRIMARY_FULL_SCREEN_HEIGHT;
pixcoord Config::SECONDARY_FULL_SCREEN_WIDTH_BK   = Config::SECONDARY_FULL_SCREEN_WIDTH;
pixcoord Config::SECONDARY_FULL_SCREEN_HEIGHT_BK  = Config::SECONDARY_FULL_SCREEN_HEIGHT;


bool Config::FIXED_GAME_VIEW_ASPECT = false;

bool Config::SWAP_GAME_VIEW = false;
int Config::PRIMARY_PRESENT_POSITION = 6;
int Config::SECONDARY_PRESENT_POSITION = 4;

double Config::PRIMARY_VIEW_WIDTH_RATIO = 1.0;
double Config::PRIMARY_VIEW_HEIGHT_RATIO = 1.0;
double Config::SECONDARY_VIEW_WIDTH_RATIO = 1.0;
double Config::SECONDARY_VIEW_HEIGHT_RATIO = 1.0;

std::string Config::BORDER_COLOR = "#222222";
std::string Config::BG_COLOR = "#000000";

int Config::MASTER_VOLUME = 800;
int Config::BGM_VOLUME = 800;
int Config::SE_VOLUME = 800;
int Config::MAX_SE_AT_ONCE = 16;
int Config::SE_DELAY_MSEC_MAX_DEPTH = 3000;
double Config::SE_VOLUME_RATE_MAX_DEPTH=0.2;

std::string Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL = "model";
std::string Config::DIRNAME_RESOURCE_SKIN_XXX_MESH = "mesh";
std::string Config::DIRNAME_RESOURCE_SKIN_XXX_POINT_SPRITE3D = "psprite3d";
std::string Config::DIRNAME_RESOURCE_SKIN_XXX_SPRITE = "sprite";
std::string Config::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE = "texture";
std::string Config::DIRNAME_RESOURCE_SKIN_XXX_EFFECT = "effect";
std::string Config::DIRNAME_RESOURCE_SKIN_XXX_BGM = "bgm";
std::string Config::DIRNAME_RESOURCE_SKIN_XXX_SE = "se";

std::string Config::DIR_MODEL[] = {
                GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL + "/",
                GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL + "/",
                GgafCore::Config::DIR_SKIN_KIND[2] + "/"
            };

std::string Config::DIR_MESH[] = {
                Config::DIR_MODEL[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_MESH + "/",
                Config::DIR_MODEL[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_MESH + "/",
                Config::DIR_MODEL[2] + "/"
            };
std::string Config::DIR_POINT_SPRITE3D[] = {
                Config::DIR_MODEL[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_POINT_SPRITE3D + "/",
                Config::DIR_MODEL[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_POINT_SPRITE3D + "/",
                Config::DIR_MODEL[2] + "/"
            };

std::string Config::DIR_SPRITE[] = {
                Config::DIR_MODEL[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_SPRITE + "/",
                Config::DIR_MODEL[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_SPRITE + "/",
                Config::DIR_MODEL[2] + "/"
            };

std::string Config::DIR_TEXTURE[] = {
                GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/",
                GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/",
                GgafCore::Config::DIR_SKIN_KIND[2]
            };
std::string Config::DIR_EFFECT[] = {
                GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_EFFECT + "/",
                GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_EFFECT + "/",
                GgafCore::Config::DIR_SKIN_KIND[2]
            };
std::string Config::DIR_BGM[] = {
                GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_BGM + "/",
                GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_BGM + "/",
                GgafCore::Config::DIR_SKIN_KIND[2]
            };
std::string Config::DIR_SE[] = {
                GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_SE + "/",
                GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_SE + "/",
                GgafCore::Config::DIR_SKIN_KIND[2]
            };

std::string Config::DIRNAME_RESOURCE_CURVE = "curve";
std::string Config::DIR_CURVE = GgafCore::Config::DIR_RESOURCE + "/" + Config::DIRNAME_RESOURCE_CURVE + "/" ;


bool Config::REALTIME_EFFECT_COMPILE = false;

std::string Config::ILLIGAL_TEXTURE = "GgafDxIlligalTexture.dds";
std::string Config::ILLIGAL_CUBEMAP_TEXTURE = "GgafDxIlligalCubeMapTexture.dds";
std::string Config::WHITE_TEXTURE = "GgafDxWhite.dds";
std::string Config::COLI_AABOX_MODEL = "GgafDxAAB";
std::string Config::COLI_AAPRISM_MODEL = "GgafDxAAPrism";
std::string Config::COLI_AAPYRAMID_MODEL = "GgafDxAAPyramid";
std::string Config::COLI_SPHERE_MODEL = "GgafDxSphere";
std::string Config::COLI_AABOARDRECT_MODEL = "GgafDxAABoardRect";


int Config::WORLD_HIT_CHECK_OCTREE_LEVEL = 2;
int Config::WORLD_HIT_CHECK_QUADTREE_LEVEL = 2;
int Config::VIEW_HIT_CHECK_QUADTREE_LEVEL = 2;
bool Config::ENABLE_WORLD_HIT_CHECK_2D = false;

void Config::loadProperties(std::string prm_properties_filename) {
    GgafCore::Config::loadProperties(prm_properties_filename);

    if (GgafCore::Config::_properties.isExistKey("FULL_SCREEN")) {
        Config::FULL_SCREEN = GgafCore::Config::_properties.getBool("FULL_SCREEN");
    }
    if (GgafCore::Config::_properties.isExistKey("DUAL_VIEW")) {
        Config::DUAL_VIEW = GgafCore::Config::_properties.getBool("DUAL_VIEW");
    }
    if (GgafCore::Config::_properties.isExistKey("GAME_BUFFER_WIDTH")) {
        Config::GAME_BUFFER_WIDTH = GgafCore::Config::_properties.getInt("GAME_BUFFER_WIDTH");
    }
    if (GgafCore::Config::_properties.isExistKey("GAME_BUFFER_HEIGHT")) {
        Config::GAME_BUFFER_HEIGHT = GgafCore::Config::_properties.getInt("GAME_BUFFER_HEIGHT");
    }
    if (GgafCore::Config::_properties.isExistKey("GAME_SPACE_DEPTH")) {
        Config::GAME_SPACE_DEPTH = GgafCore::Config::_properties.getDouble("GAME_SPACE_DEPTH");
    }
    if (GgafCore::Config::_properties.isExistKey("RENDER_DEPTH_INDEXS_NUM")) {
        Config::RENDER_DEPTH_INDEXS_NUM = GgafCore::Config::_properties.getInt("RENDER_DEPTH_INDEXS_NUM");
    }
    if (GgafCore::Config::_properties.isExistKey("RENDER_DEPTH_INDEXS_NUM_EX_NEAR")) {
        Config::RENDER_DEPTH_INDEXS_NUM_EX_NEAR = GgafCore::Config::_properties.getInt("RENDER_DEPTH_INDEXS_NUM_EX_NEAR");
    }
    if (Config::RENDER_DEPTH_INDEXS_NUM_EX_NEAR < 1) {
        throwCriticalException("Config::RENDER_DEPTH_INDEXS_NUM_EX_NEAR("<<Config::RENDER_DEPTH_INDEXS_NUM_EX_NEAR<<")は、1 以上で設定が必要です");
    }

    if (GgafCore::Config::_properties.isExistKey("RENDER_DEPTH_INDEXS_NUM_EX_FAR")) {
        Config::RENDER_DEPTH_INDEXS_NUM_EX_FAR = GgafCore::Config::_properties.getInt("RENDER_DEPTH_INDEXS_NUM_EX_FAR");
    }

    if (Config::RENDER_DEPTH_INDEXS_NUM_EX_FAR < 1) {
        throwCriticalException("Config::RENDER_DEPTH_INDEXS_NUM_EX_FAR("<<Config::RENDER_DEPTH_INDEXS_NUM_EX_FAR<<")は、1 以上で設定が必要です");
    }


    if (GgafCore::Config::_properties.isExistKey("RENDER_DEPTH_STAGE_RATIO")) {
        Config::RENDER_DEPTH_STAGE_RATIO = GgafCore::Config::_properties.getDouble("RENDER_DEPTH_STAGE_RATIO");
    }
    if (GgafCore::Config::_properties.isExistKey("PRJ_2D_MODE")) {
        Config::PRJ_2D_MODE = GgafCore::Config::_properties.getBool("PRJ_2D_MODE");
    }

    Config::RENDER_TARGET_BUFFER_WIDTH = Config::GAME_BUFFER_WIDTH;
    Config::RENDER_TARGET_BUFFER_HEIGHT = Config::GAME_BUFFER_HEIGHT;
    if (GgafCore::Config::_properties.isExistKey("RENDER_TARGET_BUFFER_WIDTH")) {
        Config::RENDER_TARGET_BUFFER_WIDTH = GgafCore::Config::_properties.getInt("RENDER_TARGET_BUFFER_WIDTH");
    }
    if (GgafCore::Config::_properties.isExistKey("RENDER_TARGET_BUFFER_HEIGHT")) {
        Config::RENDER_TARGET_BUFFER_HEIGHT = GgafCore::Config::_properties.getInt("RENDER_TARGET_BUFFER_HEIGHT");
    }

    if (GgafCore::Config::_properties.isExistKey("PRIMARY_DISPLAY_NO")) {
        Config::PRIMARY_DISPLAY_NO = GgafCore::Config::_properties.getInt("PRIMARY_DISPLAY_NO");
    }
    if (GgafCore::Config::_properties.isExistKey("SECONDARY_DISPLAY_NO")) {
        Config::SECONDARY_DISPLAY_NO = GgafCore::Config::_properties.getInt("SECONDARY_DISPLAY_NO");
    }

    if (Config::DUAL_VIEW) {
        Config::PRIMARY_RENDER_BUFFER_SOURCE_LEFT   = 0;
        Config::PRIMARY_RENDER_BUFFER_SOURCE_TOP    = 0;
        Config::PRIMARY_RENDER_BUFFER_SOURCE_WIDTH  = Config::RENDER_TARGET_BUFFER_WIDTH/2;
        Config::PRIMARY_RENDER_BUFFER_SOURCE_HEIGHT = Config::RENDER_TARGET_BUFFER_HEIGHT;

        Config::SECONDARY_RENDER_BUFFER_SOURCE_LEFT   = Config::RENDER_TARGET_BUFFER_WIDTH/2;
        Config::SECONDARY_RENDER_BUFFER_SOURCE_TOP    = 0;
        Config::SECONDARY_RENDER_BUFFER_SOURCE_WIDTH  = Config::RENDER_TARGET_BUFFER_WIDTH/2;
        Config::SECONDARY_RENDER_BUFFER_SOURCE_HEIGHT = Config::RENDER_TARGET_BUFFER_HEIGHT;
    } else {
        Config::PRIMARY_RENDER_BUFFER_SOURCE_LEFT   = 0;
        Config::PRIMARY_RENDER_BUFFER_SOURCE_TOP    = 0;
        Config::PRIMARY_RENDER_BUFFER_SOURCE_WIDTH  = Config::RENDER_TARGET_BUFFER_WIDTH;
        Config::PRIMARY_RENDER_BUFFER_SOURCE_HEIGHT = Config::RENDER_TARGET_BUFFER_HEIGHT;
    }
    if (GgafCore::Config::_properties.isExistKey("PRIMARY_RENDER_BUFFER_SOURCE_LEFT")) {
        Config::PRIMARY_RENDER_BUFFER_SOURCE_LEFT = GgafCore::Config::_properties.getInt("PRIMARY_RENDER_BUFFER_SOURCE_LEFT");
    }
    if (GgafCore::Config::_properties.isExistKey("PRIMARY_RENDER_BUFFER_SOURCE_TOP")) {
        Config::PRIMARY_RENDER_BUFFER_SOURCE_TOP = GgafCore::Config::_properties.getInt("PRIMARY_RENDER_BUFFER_SOURCE_TOP");
    }
    if (GgafCore::Config::_properties.isExistKey("PRIMARY_RENDER_BUFFER_SOURCE_WIDTH")) {
        Config::PRIMARY_RENDER_BUFFER_SOURCE_WIDTH = GgafCore::Config::_properties.getInt("PRIMARY_RENDER_BUFFER_SOURCE_WIDTH");
    }
    if (GgafCore::Config::_properties.isExistKey("PRIMARY_RENDER_BUFFER_SOURCE_HEIGHT")) {
        Config::PRIMARY_RENDER_BUFFER_SOURCE_HEIGHT = GgafCore::Config::_properties.getInt("PRIMARY_RENDER_BUFFER_SOURCE_HEIGHT");
    }
    if (GgafCore::Config::_properties.isExistKey("SECONDARY_RENDER_BUFFER_SOURCE_LEFT")) {
        Config::SECONDARY_RENDER_BUFFER_SOURCE_LEFT = GgafCore::Config::_properties.getInt("SECONDARY_RENDER_BUFFER_SOURCE_LEFT");
    }
    if (GgafCore::Config::_properties.isExistKey("SECONDARY_RENDER_BUFFER_SOURCE_TOP")) {
        Config::SECONDARY_RENDER_BUFFER_SOURCE_TOP = GgafCore::Config::_properties.getInt("SECONDARY_RENDER_BUFFER_SOURCE_TOP");
    }
    if (GgafCore::Config::_properties.isExistKey("SECONDARY_RENDER_BUFFER_SOURCE_WIDTH")) {
        Config::SECONDARY_RENDER_BUFFER_SOURCE_WIDTH = GgafCore::Config::_properties.getInt("SECONDARY_RENDER_BUFFER_SOURCE_WIDTH");
    }
    if (GgafCore::Config::_properties.isExistKey("SECONDARY_RENDER_BUFFER_SOURCE_HEIGHT")) {
        Config::SECONDARY_RENDER_BUFFER_SOURCE_HEIGHT = GgafCore::Config::_properties.getInt("SECONDARY_RENDER_BUFFER_SOURCE_HEIGHT");
    }

    Config::PRIMARY_WINDOW_WIDTH = PRIMARY_RENDER_BUFFER_SOURCE_WIDTH;
    Config::PRIMARY_WINDOW_HEIGHT = PRIMARY_RENDER_BUFFER_SOURCE_HEIGHT;
    Config::SECONDARY_WINDOW_WIDTH = SECONDARY_RENDER_BUFFER_SOURCE_WIDTH;
    Config::SECONDARY_WINDOW_HEIGHT = SECONDARY_RENDER_BUFFER_SOURCE_HEIGHT;
    if (GgafCore::Config::_properties.isExistKey("PRIMARY_WINDOW_WIDTH")) {
        Config::PRIMARY_WINDOW_WIDTH = GgafCore::Config::_properties.getInt("PRIMARY_WINDOW_WIDTH");
    }
    if (GgafCore::Config::_properties.isExistKey("PRIMARY_WINDOW_HEIGHT")) {
        Config::PRIMARY_WINDOW_HEIGHT = GgafCore::Config::_properties.getInt("PRIMARY_WINDOW_HEIGHT");
    }
    if (GgafCore::Config::_properties.isExistKey("SECONDARY_WINDOW_WIDTH")) {
        Config::SECONDARY_WINDOW_WIDTH = GgafCore::Config::_properties.getInt("SECONDARY_WINDOW_WIDTH");
    }
    if (GgafCore::Config::_properties.isExistKey("SECONDARY_WINDOW_HEIGHT")) {
        Config::SECONDARY_WINDOW_HEIGHT = GgafCore::Config::_properties.getInt("SECONDARY_WINDOW_HEIGHT");
    }


    Config::PRIMARY_FULL_SCREEN_WIDTH = PRIMARY_RENDER_BUFFER_SOURCE_WIDTH;
    Config::PRIMARY_FULL_SCREEN_HEIGHT = PRIMARY_RENDER_BUFFER_SOURCE_HEIGHT;
    Config::SECONDARY_FULL_SCREEN_WIDTH = SECONDARY_RENDER_BUFFER_SOURCE_WIDTH;
    Config::SECONDARY_FULL_SCREEN_HEIGHT = SECONDARY_RENDER_BUFFER_SOURCE_HEIGHT;
    Config::PRIMARY_FULL_SCREEN_WIDTH_BK   = Config::PRIMARY_FULL_SCREEN_WIDTH;
    Config::PRIMARY_FULL_SCREEN_HEIGHT_BK  = Config::PRIMARY_FULL_SCREEN_HEIGHT;
    Config::SECONDARY_FULL_SCREEN_WIDTH_BK   = Config::SECONDARY_FULL_SCREEN_WIDTH;
    Config::SECONDARY_FULL_SCREEN_HEIGHT_BK  = Config::SECONDARY_FULL_SCREEN_HEIGHT;
    if (GgafCore::Config::_properties.isExistKey("PRIMARY_FULL_SCREEN_WIDTH")) {
        Config::PRIMARY_FULL_SCREEN_WIDTH = GgafCore::Config::_properties.getInt("PRIMARY_FULL_SCREEN_WIDTH");
        Config::PRIMARY_FULL_SCREEN_WIDTH_BK   = Config::PRIMARY_FULL_SCREEN_WIDTH;
    }
    if (GgafCore::Config::_properties.isExistKey("PRIMARY_FULL_SCREEN_HEIGHT")) {
        Config::PRIMARY_FULL_SCREEN_HEIGHT = GgafCore::Config::_properties.getInt("PRIMARY_FULL_SCREEN_HEIGHT");
        Config::PRIMARY_FULL_SCREEN_HEIGHT_BK  = Config::PRIMARY_FULL_SCREEN_HEIGHT;
    }
    if (GgafCore::Config::_properties.isExistKey("SECONDARY_FULL_SCREEN_WIDTH")) {
        Config::SECONDARY_FULL_SCREEN_WIDTH = GgafCore::Config::_properties.getInt("SECONDARY_FULL_SCREEN_WIDTH");
        Config::SECONDARY_FULL_SCREEN_WIDTH_BK   = Config::SECONDARY_FULL_SCREEN_WIDTH;
    }
    if (GgafCore::Config::_properties.isExistKey("SECONDARY_FULL_SCREEN_HEIGHT")) {
        Config::SECONDARY_FULL_SCREEN_HEIGHT = GgafCore::Config::_properties.getInt("SECONDARY_FULL_SCREEN_HEIGHT");
        Config::SECONDARY_FULL_SCREEN_HEIGHT_BK  = Config::SECONDARY_FULL_SCREEN_HEIGHT;
    }

    if (GgafCore::Config::_properties.isExistKey("FIXED_GAME_VIEW_ASPECT")) {
        Config::FIXED_GAME_VIEW_ASPECT = GgafCore::Config::_properties.getBool("FIXED_GAME_VIEW_ASPECT");
    }
    if (GgafCore::Config::_properties.isExistKey("SWAP_GAME_VIEW")) {
        Config::SWAP_GAME_VIEW = GgafCore::Config::_properties.getBool("SWAP_GAME_VIEW");
    }

    if (Config::DUAL_VIEW) {
        Config::PRIMARY_PRESENT_POSITION = 6;
        Config::SECONDARY_PRESENT_POSITION = 4;
    } else {
        Config::PRIMARY_PRESENT_POSITION = 5;
    }
    if (GgafCore::Config::_properties.isExistKey("PRIMARY_PRESENT_POSITION")) {
        Config::PRIMARY_PRESENT_POSITION = GgafCore::Config::_properties.getInt("PRIMARY_PRESENT_POSITION");
    }
    if (GgafCore::Config::_properties.isExistKey("SECONDARY_PRESENT_POSITION")) {
        Config::SECONDARY_PRESENT_POSITION = GgafCore::Config::_properties.getInt("SECONDARY_PRESENT_POSITION");
    }

    if (GgafCore::Config::_properties.isExistKey("PRIMARY_VIEW_WIDTH_RATIO")) {
        Config::PRIMARY_VIEW_WIDTH_RATIO = GgafCore::Config::_properties.getDouble("PRIMARY_VIEW_WIDTH_RATIO");
    }
    if (GgafCore::Config::_properties.isExistKey("PRIMARY_VIEW_HEIGHT_RATIO")) {
        Config::PRIMARY_VIEW_HEIGHT_RATIO = GgafCore::Config::_properties.getDouble("PRIMARY_VIEW_HEIGHT_RATIO");
    }
    if (GgafCore::Config::_properties.isExistKey("SECONDARY_VIEW_WIDTH_RATIO")) {
        Config::SECONDARY_VIEW_WIDTH_RATIO = GgafCore::Config::_properties.getDouble("SECONDARY_VIEW_WIDTH_RATIO");
    }
    if (GgafCore::Config::_properties.isExistKey("PRIMARY_VIEW_HEIGHT_RATIO")) {
        Config::SECONDARY_VIEW_HEIGHT_RATIO = GgafCore::Config::_properties.getDouble("SECONDARY_VIEW_HEIGHT_RATIO");
    }

    if (GgafCore::Config::_properties.isExistKey("BORDER_COLOR")) {
        Config::BORDER_COLOR = GgafCore::Config::_properties.getStr("BORDER_COLOR");
    }
    if (GgafCore::Config::_properties.isExistKey("BG_COLOR")) {
        Config::BG_COLOR = GgafCore::Config::_properties.getStr("BG_COLOR");
    }
    if (GgafCore::Config::_properties.isExistKey("MASTER_VOLUME")) {
        Config::MASTER_VOLUME = GgafCore::Config::_properties.getInt("MASTER_VOLUME");
    }
    if (GgafCore::Config::_properties.isExistKey("BGM_VOLUME")) {
        Config::BGM_VOLUME = GgafCore::Config::_properties.getInt("BGM_VOLUME");
    }
    if (GgafCore::Config::_properties.isExistKey("SE_VOLUME")) {
        Config::SE_VOLUME = GgafCore::Config::_properties.getInt("SE_VOLUME");
    }
    if (GgafCore::Config::_properties.isExistKey("MAX_SE_AT_ONCE")) {
        Config::MAX_SE_AT_ONCE = GgafCore::Config::_properties.getInt("MAX_SE_AT_ONCE");
    }
    if (GgafCore::Config::_properties.isExistKey("SE_DELAY_MSEC_MAX_DEPTH")) {
        Config::SE_DELAY_MSEC_MAX_DEPTH = GgafCore::Config::_properties.getInt("SE_DELAY_MSEC_MAX_DEPTH");
    }

    if (Config::SE_DELAY_MSEC_MAX_DEPTH*2 > GGAF_END_DELAY*1000) {
        throwCriticalException("Config::SE_DELAY_MSEC_MAX_DEPTH("<<Config::SE_DELAY_MSEC_MAX_DEPTH<<")は、GGAF_END_DELAY*1000("<<(GGAF_END_DELAY*1000)<<")の半分以下である必要があります。\n"<<
                "SE_DELAY_MSEC_MAX_DEPTH の設定値をもっと下げてください。");
    }

    if (GgafCore::Config::_properties.isExistKey("SE_VOLUME_RATE_MAX_DEPTH")) {
        Config::SE_VOLUME_RATE_MAX_DEPTH = GgafCore::Config::_properties.getDouble("SE_VOLUME_RATE_MAX_DEPTH");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_MODEL")) {
        Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKIN_XXX_MODEL");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_MESH")) {
        Config::DIRNAME_RESOURCE_SKIN_XXX_MESH = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKIN_XXX_MESH");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_SPRITE")) {
        Config::DIRNAME_RESOURCE_SKIN_XXX_SPRITE = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKIN_XXX_SPRITE");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_TEXTURE")) {
        Config::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKIN_XXX_TEXTURE");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_EFFECT")) {
        Config::DIRNAME_RESOURCE_SKIN_XXX_EFFECT = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKIN_XXX_EFFECT");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_BGM")) {
        Config::DIRNAME_RESOURCE_SKIN_XXX_BGM = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKIN_XXX_BGM");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_SE")) {
        Config::DIRNAME_RESOURCE_SKIN_XXX_SE = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKIN_XXX_SE");
    }

    if (Config::_properties.isExistKey("DIRNAME_RESOURCE_CURVE")) {
        Config::DIRNAME_RESOURCE_CURVE  = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_CURVE");
    }

    if (GgafCore::Config::_properties.isExistKey("REALTIME_EFFECT_COMPILE")) {
        Config::REALTIME_EFFECT_COMPILE = GgafCore::Config::_properties.getBool("REALTIME_EFFECT_COMPILE");
    }

    if (GgafCore::Config::_properties.isExistKey("ILLIGAL_TEXTURE")) {
        Config::ILLIGAL_TEXTURE = GgafCore::Config::_properties.getStr("ILLIGAL_TEXTURE");
    }
    if (GgafCore::Config::_properties.isExistKey("ILLIGAL_CUBEMAP_TEXTURE")) {
        Config::ILLIGAL_CUBEMAP_TEXTURE = GgafCore::Config::_properties.getStr("ILLIGAL_CUBEMAP_TEXTURE");
    }
    if (GgafCore::Config::_properties.isExistKey("WHITE_TEXTURE")) {
        Config::WHITE_TEXTURE = GgafCore::Config::_properties.getStr("WHITE_TEXTURE");
    }
    if (GgafCore::Config::_properties.isExistKey("COLI_AABOX_MODEL")) {
        Config::COLI_AABOX_MODEL = GgafCore::Config::_properties.getStr("COLI_AABOX_MODEL");
    }
    if (GgafCore::Config::_properties.isExistKey("COLI_AAPRISM_MODEL")) {
        Config::COLI_AAPRISM_MODEL = GgafCore::Config::_properties.getStr("COLI_AAPRISM_MODEL");
    }
    if (GgafCore::Config::_properties.isExistKey("COLI_AAPYRAMID_MODEL")) {
        Config::COLI_AAPYRAMID_MODEL = GgafCore::Config::_properties.getStr("COLI_AAPYRAMID_MODEL");
    }
    if (GgafCore::Config::_properties.isExistKey("COLI_SPHERE_MODEL")) {
        Config::COLI_SPHERE_MODEL = GgafCore::Config::_properties.getStr("COLI_SPHERE_MODEL");
    }
    if (GgafCore::Config::_properties.isExistKey("COLI_AABOARDRECT_MODEL")) {
        Config::COLI_AABOARDRECT_MODEL = GgafCore::Config::_properties.getStr("COLI_AABOARDRECT_MODEL");
    }

    Config::DIR_MODEL[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL + "/";
      Config::DIR_MESH[0] = Config::DIR_MODEL[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_MESH + "/";
      Config::DIR_POINT_SPRITE3D[0] = Config::DIR_MODEL[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_POINT_SPRITE3D + "/";
      Config::DIR_SPRITE[0] = Config::DIR_MODEL[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_SPRITE + "/";
    Config::DIR_TEXTURE[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
    Config::DIR_EFFECT[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_EFFECT + "/";
    Config::DIR_BGM[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_BGM + "/";
    Config::DIR_SE[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_SE + "/";

    Config::DIR_MODEL[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL + "/";
      Config::DIR_MESH[1] = Config::DIR_MODEL[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_MESH + "/";
      Config::DIR_POINT_SPRITE3D[1] = Config::DIR_MODEL[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_POINT_SPRITE3D + "/";
      Config::DIR_SPRITE[1] = Config::DIR_MODEL[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_SPRITE + "/";
    Config::DIR_TEXTURE[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
    Config::DIR_EFFECT[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_EFFECT + "/";
    Config::DIR_BGM[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_BGM + "/";
    Config::DIR_SE[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_SE + "/";


    Config::DIR_MODEL[2] = GgafCore::Config::DIR_SKIN_KIND[2] + "/";
      Config::DIR_MESH[2] = Config::DIR_MODEL[2] + "/";
      Config::DIR_POINT_SPRITE3D[2] = Config::DIR_MODEL[2] + "/";
      Config::DIR_SPRITE[2] = Config::DIR_MODEL[2] + "/";
    Config::DIR_TEXTURE[2] = GgafCore::Config::DIR_SKIN_KIND[2] + "/";
    Config::DIR_EFFECT[2] = GgafCore::Config::DIR_SKIN_KIND[2] + "/";
    Config::DIR_BGM[2] = GgafCore::Config::DIR_SKIN_KIND[2] + "/";
    Config::DIR_SE[2] = GgafCore::Config::DIR_SKIN_KIND[2] + "/";

    Config::DIR_CURVE = GgafCore::Config::DIR_RESOURCE + "/" + Config::DIRNAME_RESOURCE_CURVE + "/";

    for (int n = 0; n < 2; n++) { //何回かして重複削除
        UTIL::strReplace(Config::DIR_CURVE     , "//", "/");
        for (int i = 0; i < 3; i++) {
            UTIL::strReplace(Config::DIR_MODEL[i]  , "//", "/");
            UTIL::strReplace(Config::DIR_MESH[i]  , "//", "/");
            UTIL::strReplace(Config::DIR_SPRITE[i]  , "//", "/");
            UTIL::strReplace(Config::DIR_TEXTURE[i], "//", "/");
            UTIL::strReplace(Config::DIR_EFFECT[i] , "//", "/");
            UTIL::strReplace(Config::DIR_BGM[i]    , "//", "/");
            UTIL::strReplace(Config::DIR_SE[i]     , "//", "/");
        }
    }

    //リソースディレクトリ名指定があるのならば、デフォルトのスキンディレクトリのリソースディレクトリ存在チェック
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_MODEL")) {
        if (!PathFileExists(Config::DIR_MODEL[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_MODEL[0]("<<Config::DIR_MODEL[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_MESH")) {
        if (!PathFileExists(Config::DIR_MESH[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_MESH[0]("<<Config::DIR_MESH[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_POINT_SPRITE3D")) {
        if (!PathFileExists(Config::DIR_POINT_SPRITE3D[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_POINT_SPRITE3D[0]("<<Config::DIR_POINT_SPRITE3D[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_SPRITE")) {
        if (!PathFileExists(Config::DIR_SPRITE[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_SPRITE[0]("<<Config::DIR_SPRITE[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_TEXTURE")) {
        if (!PathFileExists(Config::DIR_TEXTURE[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_TEXTURE[0]("<<Config::DIR_TEXTURE[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_EFFECT")) {
        if (!PathFileExists(Config::DIR_EFFECT[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_EFFECT[0]("<<Config::DIR_EFFECT[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_BGM")) {
        if (!PathFileExists(Config::DIR_BGM[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_BGM[0]("<<Config::DIR_BGM[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_SE")) {
        if (!PathFileExists(Config::DIR_SE[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_SE[0]("<<Config::DIR_SE[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_CURVE")) {
        if (!PathFileExists(Config::DIR_CURVE.c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_CURVE("<<Config::DIR_CURVE<<") のディレクトリが見つかりません。");
        }
    }


    if (GgafCore::Config::_properties.isExistKey("ENABLE_WORLD_HIT_CHECK_2D")) {
        Config::ENABLE_WORLD_HIT_CHECK_2D = GgafCore::Config::_properties.getBool("ENABLE_WORLD_HIT_CHECK_2D");
    }
    if (Config::ENABLE_WORLD_HIT_CHECK_2D) {
        if (GgafCore::Config::_properties.isExistKey("WORLD_HIT_CHECK_QUADTREE_LEVEL")) {
            Config::WORLD_HIT_CHECK_QUADTREE_LEVEL  = GgafCore::Config::_properties.getInt("WORLD_HIT_CHECK_QUADTREE_LEVEL");
        }
        if (GgafCore::Config::_properties.isExistKey("WORLD_HIT_CHECK_OCTREE_LEVEL")) {
            throwCriticalException("ENABLE_WORLD_HIT_CHECK_2D が ture の場合、WORLD_HIT_CHECK_OCTREE_LEVEL は設定できません。(WORLD_HIT_CHECK_QUADTREE_LEVEL を設定してください。)");
        }
    } else {
        if (GgafCore::Config::_properties.isExistKey("WORLD_HIT_CHECK_QUADTREE_LEVEL")) {
            throwCriticalException("ENABLE_WORLD_HIT_CHECK_2D が false の場合、WORLD_HIT_CHECK_QUADTREE_LEVEL は設定できません。(WORLD_HIT_CHECK_OCTREE_LEVEL を設定してください。)");
        }
        if (GgafCore::Config::_properties.isExistKey("WORLD_HIT_CHECK_OCTREE_LEVEL")) {
            Config::WORLD_HIT_CHECK_OCTREE_LEVEL  = GgafCore::Config::_properties.getInt("WORLD_HIT_CHECK_OCTREE_LEVEL");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("VIEW_HIT_CHECK_QUADTREE_LEVEL")) {
        Config::VIEW_HIT_CHECK_QUADTREE_LEVEL  = GgafCore::Config::_properties.getInt("VIEW_HIT_CHECK_QUADTREE_LEVEL");
    }


    _TRACE_("Config::FULL_SCREEN=" << Config::FULL_SCREEN);
    _TRACE_("Config::DUAL_VIEW=" << Config::DUAL_VIEW);
    _TRACE_("Config::GAME_BUFFER_WIDTH=" << Config::GAME_BUFFER_WIDTH);
    _TRACE_("Config::GAME_BUFFER_HEIGHT=" << Config::GAME_BUFFER_HEIGHT);
    _TRACE_("Config::GAME_SPACE_DEPTH=" << Config::GAME_SPACE_DEPTH);
    _TRACE_("Config::RENDER_DEPTH_INDEXS_NUM=" << Config::RENDER_DEPTH_INDEXS_NUM);
    _TRACE_("Config::RENDER_DEPTH_INDEXS_NUM_EX_NEAR=" << Config::RENDER_DEPTH_INDEXS_NUM_EX_NEAR);
    _TRACE_("Config::RENDER_DEPTH_INDEXS_NUM_EX_FAR=" << Config::RENDER_DEPTH_INDEXS_NUM_EX_FAR);
    _TRACE_("Config::RENDER_DEPTH_STAGE_RATIO=" << Config::RENDER_DEPTH_STAGE_RATIO);
    _TRACE_("Config::PRJ_2D_MODE=" << Config::PRJ_2D_MODE);
    _TRACE_("Config::RENDER_TARGET_BUFFER_WIDTH=" << Config::RENDER_TARGET_BUFFER_WIDTH);
    _TRACE_("Config::RENDER_TARGET_BUFFER_HEIGHT=" << Config::RENDER_TARGET_BUFFER_HEIGHT);

    _TRACE_("Config::PRIMARY_RENDER_BUFFER_SOURCE_LEFT=" << Config::PRIMARY_RENDER_BUFFER_SOURCE_LEFT   );
    _TRACE_("Config::PRIMARY_RENDER_BUFFER_SOURCE_TOP=" << Config::PRIMARY_RENDER_BUFFER_SOURCE_TOP    );
    _TRACE_("Config::PRIMARY_RENDER_BUFFER_SOURCE_WIDTH=" << Config::PRIMARY_RENDER_BUFFER_SOURCE_WIDTH  );
    _TRACE_("Config::PRIMARY_RENDER_BUFFER_SOURCE_HEIGHT=" << Config::PRIMARY_RENDER_BUFFER_SOURCE_HEIGHT );
    _TRACE_("Config::SECONDARY_RENDER_BUFFER_SOURCE_LEFT=" << Config::SECONDARY_RENDER_BUFFER_SOURCE_LEFT   );
    _TRACE_("Config::SECONDARY_RENDER_BUFFER_SOURCE_TOP=" << Config::SECONDARY_RENDER_BUFFER_SOURCE_TOP    );
    _TRACE_("Config::SECONDARY_RENDER_BUFFER_SOURCE_WIDTH=" << Config::SECONDARY_RENDER_BUFFER_SOURCE_WIDTH  );
    _TRACE_("Config::SECONDARY_RENDER_BUFFER_SOURCE_HEIGHT=" << Config::SECONDARY_RENDER_BUFFER_SOURCE_HEIGHT );

    _TRACE_("Config::PRIMARY_WINDOW_WIDTH=" << Config::PRIMARY_WINDOW_WIDTH);
    _TRACE_("Config::PRIMARY_WINDOW_HEIGHT=" << Config::PRIMARY_WINDOW_HEIGHT);
    _TRACE_("Config::SECONDARY_WINDOW_WIDTH=" << Config::SECONDARY_WINDOW_WIDTH);
    _TRACE_("Config::SECONDARY_WINDOW_HEIGHT=" << Config::SECONDARY_WINDOW_HEIGHT);
    _TRACE_("Config::FIXED_GAME_VIEW_ASPECT=" << Config::FIXED_GAME_VIEW_ASPECT);
    _TRACE_("Config::PRIMARY_DISPLAY_NO=" << Config::PRIMARY_DISPLAY_NO);
    _TRACE_("Config::SECONDARY_DISPLAY_NO=" << Config::SECONDARY_DISPLAY_NO);
    _TRACE_("Config::SWAP_GAME_VIEW=" << Config::SWAP_GAME_VIEW);
    _TRACE_("Config::PRIMARY_PRESENT_POSITION=" << Config::PRIMARY_PRESENT_POSITION);
    _TRACE_("Config::SECONDARY_PRESENT_POSITION=" << Config::SECONDARY_PRESENT_POSITION);
    _TRACE_("Config::PRIMARY_VIEW_WIDTH_RATIO=" << Config::PRIMARY_VIEW_WIDTH_RATIO);
    _TRACE_("Config::PRIMARY_VIEW_HEIGHT_RATIO=" << Config::PRIMARY_VIEW_HEIGHT_RATIO);
    _TRACE_("Config::SECONDARY_VIEW_WIDTH_RATIO=" << Config::SECONDARY_VIEW_WIDTH_RATIO);
    _TRACE_("Config::SECONDARY_VIEW_HEIGHT_RATIO=" << Config::SECONDARY_VIEW_HEIGHT_RATIO);
    _TRACE_("Config::BORDER_COLOR=" << Config::BORDER_COLOR);
    _TRACE_("Config::BG_COLOR=" << Config::BG_COLOR);
    _TRACE_("Config::MASTER_VOLUME=" << Config::MASTER_VOLUME);
    _TRACE_("Config::BGM_VOLUME=" << Config::BGM_VOLUME);
    _TRACE_("Config::SE_VOLUME=" << Config::SE_VOLUME);
    _TRACE_("Config::MAX_SE_AT_ONCE=" << Config::MAX_SE_AT_ONCE);
    _TRACE_("Config::SE_DELAY_MSEC_MAX_DEPTH=" << Config::SE_DELAY_MSEC_MAX_DEPTH);
    _TRACE_("Config::SE_VOLUME_RATE_MAX_DEPTH=" << Config::SE_VOLUME_RATE_MAX_DEPTH);

    _TRACE_("Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL=" << Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL);
    _TRACE_("Config::DIRNAME_RESOURCE_SKIN_XXX_MESH=" << Config::DIRNAME_RESOURCE_SKIN_XXX_MESH);
    _TRACE_("Config::DIRNAME_RESOURCE_SKIN_XXX_SPRITE=" << Config::DIRNAME_RESOURCE_SKIN_XXX_SPRITE);
    _TRACE_("Config::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE=" << Config::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE);
    _TRACE_("Config::DIRNAME_RESOURCE_SKIN_XXX_EFFECT=" << Config::DIRNAME_RESOURCE_SKIN_XXX_EFFECT);
    _TRACE_("Config::DIRNAME_RESOURCE_SKIN_XXX_BGM=" << Config::DIRNAME_RESOURCE_SKIN_XXX_BGM);
    _TRACE_("Config::DIRNAME_RESOURCE_SKIN_XXX_SE=" << Config::DIRNAME_RESOURCE_SKIN_XXX_SE);
    _TRACE_("Config::DIRNAME_RESOURCE_CURVE=" << Config::DIRNAME_RESOURCE_CURVE);
    for (int i = 0; i < 3; i++) {
        _TRACE_("Config::DIR_MODEL["<<i<<"]=" << Config::DIR_MODEL[i]);
        _TRACE_("Config::DIR_MESH["<<i<<"]=" << Config::DIR_MESH[i]);
        _TRACE_("Config::DIR_SPRITE["<<i<<"]=" << Config::DIR_SPRITE[i]);
        _TRACE_("Config::DIR_TEXTURE["<<i<<"]=" << Config::DIR_TEXTURE[i]);
        _TRACE_("Config::DIR_EFFECT["<<i<<"]=" << Config::DIR_EFFECT[i]);
        _TRACE_("Config::DIR_BGM["<<i<<"]=" << Config::DIR_BGM[i]);
        _TRACE_("Config::DIR_SE["<<i<<"]=" << Config::DIR_SE[i]);
    }
    _TRACE_("Config::DIR_CURVE=" << Config::DIR_CURVE);
    _TRACE_("Config::REALTIME_EFFECT_COMPILE="<<Config::REALTIME_EFFECT_COMPILE);
    _TRACE_("Config::ENABLE_WORLD_HIT_CHECK_2D=" << Config::ENABLE_WORLD_HIT_CHECK_2D);
    _TRACE_("Config::WORLD_HIT_CHECK_OCTREE_LEVEL=" << Config::WORLD_HIT_CHECK_OCTREE_LEVEL);
    _TRACE_("Config::WORLD_HIT_CHECK_QUADTREE_LEVEL=" << Config::WORLD_HIT_CHECK_QUADTREE_LEVEL);
}


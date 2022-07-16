#include "jp/ggaf/dx/Config.h"

#include <Shlwapi.h>


using namespace GgafDx;

bool Config::FULL_SCREEN = false;
bool Config::DUAL_VIEW = false;

pixcoord Config::GAME_BUFFER_WIDTH = 1600;
pixcoord Config::GAME_BUFFER_HEIGHT = 450;
double Config::GAME_SPACE_DEPTH = 15.0;
int Config::RENDER_DEPTH_INDEXS_NUM = 256;
double Config::RENDER_DEPTH_STAGE_RATIO = 0.6;
bool Config::PRJ_2D_MODE = false;
pixcoord Config::RENDER_TARGET_BUFFER_WIDTH = 1600;
pixcoord Config::RENDER_TARGET_BUFFER_HEIGHT = 450;

pixcoord Config::VIEW_SOURCE_BUFFER_WIDTH = Config::RENDER_TARGET_BUFFER_WIDTH;
pixcoord Config::VIEW_SOURCE_BUFFER_HEIGHT = Config::RENDER_TARGET_BUFFER_HEIGHT;

pixcoord Config::SINGLE_VIEW_WINDOW_WIDTH = 1600;
pixcoord Config::SINGLE_VIEW_WINDOW_HEIGHT = 450;
pixcoord Config::DUAL_VIEW_WINDOW1_WIDTH = 800;
pixcoord Config::DUAL_VIEW_WINDOW1_HEIGHT = 450;
pixcoord Config::DUAL_VIEW_WINDOW2_WIDTH = 800;
pixcoord Config::DUAL_VIEW_WINDOW2_HEIGHT = 450;
//0の場合現在の解像度でフルスクリーン
pixcoord Config::SINGLE_VIEW_FULL_SCREEN_WIDTH = 0;
pixcoord Config::SINGLE_VIEW_FULL_SCREEN_HEIGHT = 0;
pixcoord Config::DUAL_VIEW_FULL_SCREEN1_WIDTH = 0;
pixcoord Config::DUAL_VIEW_FULL_SCREEN1_HEIGHT = 0;
pixcoord Config::DUAL_VIEW_FULL_SCREEN2_WIDTH = 0;
pixcoord Config::DUAL_VIEW_FULL_SCREEN2_HEIGHT = 0;

pixcoord Config::SINGLE_VIEW_FULL_SCREEN_WIDTH_BK  = Config::SINGLE_VIEW_FULL_SCREEN_WIDTH;
pixcoord Config::SINGLE_VIEW_FULL_SCREEN_HEIGHT_BK = Config::SINGLE_VIEW_FULL_SCREEN_HEIGHT;
pixcoord Config::DUAL_VIEW_FULL_SCREEN1_WIDTH_BK   = Config::DUAL_VIEW_FULL_SCREEN1_WIDTH;
pixcoord Config::DUAL_VIEW_FULL_SCREEN1_HEIGHT_BK  = Config::DUAL_VIEW_FULL_SCREEN1_HEIGHT;
pixcoord Config::DUAL_VIEW_FULL_SCREEN2_WIDTH_BK   = Config::DUAL_VIEW_FULL_SCREEN2_WIDTH;
pixcoord Config::DUAL_VIEW_FULL_SCREEN2_HEIGHT_BK  = Config::DUAL_VIEW_FULL_SCREEN2_HEIGHT;


bool Config::FIXED_GAME_VIEW_ASPECT = false;
int Config::PRIMARY_ADAPTER_NO = 0;
int Config::SECONDARY_ADAPTER_NO = 1;

bool Config::SWAP_GAME_VIEW = false;
int Config::SINGLE_VIEW_DRAW_POSITION = 5;
int Config::DUAL_VIEW_DRAW_POSITION1 = 6;
int Config::DUAL_VIEW_DRAW_POSITION2 = 4;

double Config::VIEW1_WIDTH_RATIO = 1.0;
double Config::VIEW1_HEIGHT_RATIO = 1.0;
double Config::VIEW2_WIDTH_RATIO = 1.0;
double Config::VIEW2_HEIGHT_RATIO = 1.0;

std::string Config::BORDER_COLOR = "#222222";
std::string Config::BG_COLOR = "#000000";

int Config::MASTER_VOLUME = 800;
int Config::BGM_VOLUME = 800;
int Config::SE_VOLUME = 800;
int Config::MAX_SE_AT_ONCE = 16;
int Config::SE_DELAY_MAX_DEPTH = 180;
double Config::SE_VOLUME_RATE_MAX_DEPTH=0.2;

std::string Config::DIRNAME_RESOURCE_SKIN_XXX_MESH = "mesh";
std::string Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL = "model";
std::string Config::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE = "texture";
std::string Config::DIRNAME_RESOURCE_SKIN_XXX_EFFECT = "effect";
std::string Config::DIRNAME_RESOURCE_SKIN_XXX_BGM = "bgm";
std::string Config::DIRNAME_RESOURCE_SKIN_XXX_SE = "se";

std::string Config::DIR_MESH[] = {
                GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_MESH,
                GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_MESH,
                GgafCore::Config::DIR_SKIN_KIND[2] + "/"
            };
std::string Config::DIR_MODEL[] = {
                GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL + "/",
                GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL + "/",
                GgafCore::Config::DIR_SKIN_KIND[2] + "/"
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
    if (GgafCore::Config::_properties.isExistKey("RENDER_DEPTH_STAGE_RATIO")) {
        Config::RENDER_DEPTH_STAGE_RATIO = GgafCore::Config::_properties.getDouble("RENDER_DEPTH_STAGE_RATIO");
    }
    if (GgafCore::Config::_properties.isExistKey("PRJ_2D_MODE")) {
        Config::PRJ_2D_MODE = GgafCore::Config::_properties.getBool("PRJ_2D_MODE");
    }
    if (GgafCore::Config::_properties.isExistKey("RENDER_TARGET_BUFFER_WIDTH")) {
        Config::RENDER_TARGET_BUFFER_WIDTH = GgafCore::Config::_properties.getInt("RENDER_TARGET_BUFFER_WIDTH");
    }
    if (GgafCore::Config::_properties.isExistKey("RENDER_TARGET_BUFFER_HEIGHT")) {
        Config::RENDER_TARGET_BUFFER_HEIGHT = GgafCore::Config::_properties.getInt("RENDER_TARGET_BUFFER_HEIGHT");
    }
    if (GgafCore::Config::_properties.isExistKey("VIEW_SOURCE_BUFFER_WIDTH")) {
        Config::VIEW_SOURCE_BUFFER_WIDTH = GgafCore::Config::_properties.getInt("VIEW_SOURCE_BUFFER_WIDTH");
    } else {
        Config::VIEW_SOURCE_BUFFER_WIDTH = Config::RENDER_TARGET_BUFFER_WIDTH;
    }
    if (GgafCore::Config::_properties.isExistKey("VIEW_SOURCE_BUFFER_HEIGHT")) {
        Config::VIEW_SOURCE_BUFFER_HEIGHT = GgafCore::Config::_properties.getInt("VIEW_SOURCE_BUFFER_HEIGHT");
    } else {
        Config::VIEW_SOURCE_BUFFER_HEIGHT = Config::RENDER_TARGET_BUFFER_HEIGHT;
    }
    if (GgafCore::Config::_properties.isExistKey("SINGLE_VIEW_WINDOW_WIDTH")) {
        Config::SINGLE_VIEW_WINDOW_WIDTH = GgafCore::Config::_properties.getInt("SINGLE_VIEW_WINDOW_WIDTH");
    }
    if (GgafCore::Config::_properties.isExistKey("SINGLE_VIEW_WINDOW_HEIGHT")) {
        Config::SINGLE_VIEW_WINDOW_HEIGHT = GgafCore::Config::_properties.getInt("SINGLE_VIEW_WINDOW_HEIGHT");
    }
    if (GgafCore::Config::_properties.isExistKey("DUAL_VIEW_WINDOW1_WIDTH")) {
        Config::DUAL_VIEW_WINDOW1_WIDTH = GgafCore::Config::_properties.getInt("DUAL_VIEW_WINDOW1_WIDTH");
    }
    if (GgafCore::Config::_properties.isExistKey("DUAL_VIEW_WINDOW1_HEIGHT")) {
        Config::DUAL_VIEW_WINDOW1_HEIGHT = GgafCore::Config::_properties.getInt("DUAL_VIEW_WINDOW1_HEIGHT");
    }
    if (GgafCore::Config::_properties.isExistKey("DUAL_VIEW_WINDOW2_WIDTH")) {
        Config::DUAL_VIEW_WINDOW2_WIDTH = GgafCore::Config::_properties.getInt("DUAL_VIEW_WINDOW2_WIDTH");
    }
    if (GgafCore::Config::_properties.isExistKey("DUAL_VIEW_WINDOW2_HEIGHT")) {
        Config::DUAL_VIEW_WINDOW2_HEIGHT = GgafCore::Config::_properties.getInt("DUAL_VIEW_WINDOW2_HEIGHT");
    }

    if (GgafCore::Config::_properties.isExistKey("SINGLE_VIEW_FULL_SCREEN_WIDTH")) {
        Config::SINGLE_VIEW_FULL_SCREEN_WIDTH = GgafCore::Config::_properties.getInt("SINGLE_VIEW_FULL_SCREEN_WIDTH");
        Config::SINGLE_VIEW_FULL_SCREEN_WIDTH_BK  = Config::SINGLE_VIEW_FULL_SCREEN_WIDTH;
    }
    if (GgafCore::Config::_properties.isExistKey("SINGLE_VIEW_FULL_SCREEN_HEIGHT")) {
        Config::SINGLE_VIEW_FULL_SCREEN_HEIGHT = GgafCore::Config::_properties.getInt("SINGLE_VIEW_FULL_SCREEN_HEIGHT");
        Config::SINGLE_VIEW_FULL_SCREEN_HEIGHT_BK = Config::SINGLE_VIEW_FULL_SCREEN_HEIGHT;
    }

    if (GgafCore::Config::_properties.isExistKey("DUAL_VIEW_FULL_SCREEN1_WIDTH")) {
        Config::DUAL_VIEW_FULL_SCREEN1_WIDTH = GgafCore::Config::_properties.getInt("DUAL_VIEW_FULL_SCREEN1_WIDTH");
        Config::DUAL_VIEW_FULL_SCREEN1_WIDTH_BK   = Config::DUAL_VIEW_FULL_SCREEN1_WIDTH;
    }
    if (GgafCore::Config::_properties.isExistKey("DUAL_VIEW_FULL_SCREEN1_HEIGHT")) {
        Config::DUAL_VIEW_FULL_SCREEN1_HEIGHT = GgafCore::Config::_properties.getInt("DUAL_VIEW_FULL_SCREEN1_HEIGHT");
        Config::DUAL_VIEW_FULL_SCREEN1_HEIGHT_BK  = Config::DUAL_VIEW_FULL_SCREEN1_HEIGHT;
    }
    if (GgafCore::Config::_properties.isExistKey("DUAL_VIEW_FULL_SCREEN2_WIDTH")) {
        Config::DUAL_VIEW_FULL_SCREEN2_WIDTH = GgafCore::Config::_properties.getInt("DUAL_VIEW_FULL_SCREEN2_WIDTH");
        Config::DUAL_VIEW_FULL_SCREEN2_WIDTH_BK   = Config::DUAL_VIEW_FULL_SCREEN2_WIDTH;
    }
    if (GgafCore::Config::_properties.isExistKey("DUAL_VIEW_FULL_SCREEN2_HEIGHT")) {
        Config::DUAL_VIEW_FULL_SCREEN2_HEIGHT = GgafCore::Config::_properties.getInt("DUAL_VIEW_FULL_SCREEN2_HEIGHT");
        Config::DUAL_VIEW_FULL_SCREEN2_HEIGHT_BK  = Config::DUAL_VIEW_FULL_SCREEN2_HEIGHT;
    }

    if (GgafCore::Config::_properties.isExistKey("FIXED_GAME_VIEW_ASPECT")) {
        Config::FIXED_GAME_VIEW_ASPECT = GgafCore::Config::_properties.getBool("FIXED_GAME_VIEW_ASPECT");
    }

    if (GgafCore::Config::_properties.isExistKey("PRIMARY_ADAPTER_NO")) {
        Config::PRIMARY_ADAPTER_NO = GgafCore::Config::_properties.getInt("PRIMARY_ADAPTER_NO");
    }
    if (GgafCore::Config::_properties.isExistKey("SECONDARY_ADAPTER_NO")) {
        Config::SECONDARY_ADAPTER_NO = GgafCore::Config::_properties.getInt("SECONDARY_ADAPTER_NO");
    }
    if (GgafCore::Config::_properties.isExistKey("SWAP_GAME_VIEW")) {
        Config::SWAP_GAME_VIEW = GgafCore::Config::_properties.getBool("SWAP_GAME_VIEW");
    }
    if (GgafCore::Config::_properties.isExistKey("SINGLE_VIEW_DRAW_POSITION")) {
        Config::SINGLE_VIEW_DRAW_POSITION = GgafCore::Config::_properties.getInt("SINGLE_VIEW_DRAW_POSITION");
    }
    if (GgafCore::Config::_properties.isExistKey("DUAL_VIEW_DRAW_POSITION1")) {
        Config::DUAL_VIEW_DRAW_POSITION1 = GgafCore::Config::_properties.getInt("DUAL_VIEW_DRAW_POSITION1");
    }
    if (GgafCore::Config::_properties.isExistKey("DUAL_VIEW_DRAW_POSITION2")) {
        Config::DUAL_VIEW_DRAW_POSITION2 = GgafCore::Config::_properties.getInt("DUAL_VIEW_DRAW_POSITION2");
    }

    if (GgafCore::Config::_properties.isExistKey("VIEW1_WIDTH_RATIO")) {
        Config::VIEW1_WIDTH_RATIO = GgafCore::Config::_properties.getDouble("VIEW1_WIDTH_RATIO");
    }
    if (GgafCore::Config::_properties.isExistKey("VIEW1_HEIGHT_RATIO")) {
        Config::VIEW1_HEIGHT_RATIO = GgafCore::Config::_properties.getDouble("VIEW1_HEIGHT_RATIO");
    }
    if (GgafCore::Config::_properties.isExistKey("VIEW2_WIDTH_RATIO")) {
        Config::VIEW2_WIDTH_RATIO = GgafCore::Config::_properties.getDouble("VIEW2_WIDTH_RATIO");
    }
    if (GgafCore::Config::_properties.isExistKey("VIEW1_HEIGHT_RATIO")) {
        Config::VIEW2_HEIGHT_RATIO = GgafCore::Config::_properties.getDouble("VIEW2_HEIGHT_RATIO");
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
    if (GgafCore::Config::_properties.isExistKey("SE_DELAY_MAX_DEPTH")) {
        Config::SE_DELAY_MAX_DEPTH = GgafCore::Config::_properties.getInt("SE_DELAY_MAX_DEPTH");
    }

    if (Config::SE_DELAY_MAX_DEPTH*2 > GGAF_END_DELAY) {
        throwCriticalException("Config::SE_DELAY_MAX_DEPTH("<<Config::SE_DELAY_MAX_DEPTH<<")は、GGAF_END_DELAY("<<GGAF_END_DELAY<<")の半分以下である必要があります。\n"<<
                "SE_DELAY_MAX_DEPTH の設定値をもっと下げてください。");
    }

    if (GgafCore::Config::_properties.isExistKey("SE_VOLUME_RATE_MAX_DEPTH")) {
        Config::SE_VOLUME_RATE_MAX_DEPTH = GgafCore::Config::_properties.getDouble("SE_VOLUME_RATE_MAX_DEPTH");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_MESH")) {
        Config::DIRNAME_RESOURCE_SKIN_XXX_MESH = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKIN_XXX_MESH");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_MODEL")) {
        Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKIN_XXX_MODEL");
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


    Config::DIR_MESH[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/"
            + Config::DIRNAME_RESOURCE_SKIN_XXX_MESH + "/";
    Config::DIR_MODEL[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/"
            + Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL + "/";
    Config::DIR_TEXTURE[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/"
            + Config::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
    Config::DIR_EFFECT[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/"
            + Config::DIRNAME_RESOURCE_SKIN_XXX_EFFECT + "/";
    Config::DIR_BGM[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/"
            + Config::DIRNAME_RESOURCE_SKIN_XXX_BGM + "/";
    Config::DIR_SE[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/"
            + Config::DIRNAME_RESOURCE_SKIN_XXX_SE + "/";

    Config::DIR_MESH[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/"
            + Config::DIRNAME_RESOURCE_SKIN_XXX_MESH + "/";
    Config::DIR_MODEL[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/"
            + Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL + "/";
    Config::DIR_TEXTURE[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/"
            + Config::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
    Config::DIR_EFFECT[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/"
            + Config::DIRNAME_RESOURCE_SKIN_XXX_EFFECT + "/";
    Config::DIR_BGM[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/"
            + Config::DIRNAME_RESOURCE_SKIN_XXX_BGM + "/";
    Config::DIR_SE[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/"
            + Config::DIRNAME_RESOURCE_SKIN_XXX_SE + "/";

    Config::DIR_MESH[2] = GgafCore::Config::DIR_SKIN_KIND[2] + "/";
    Config::DIR_MODEL[2] = GgafCore::Config::DIR_SKIN_KIND[2] + "/";
    Config::DIR_TEXTURE[2] = GgafCore::Config::DIR_SKIN_KIND[2] + "/";
    Config::DIR_EFFECT[2] = GgafCore::Config::DIR_SKIN_KIND[2] + "/";
    Config::DIR_BGM[2] = GgafCore::Config::DIR_SKIN_KIND[2] + "/";
    Config::DIR_SE[2] = GgafCore::Config::DIR_SKIN_KIND[2] + "/";


    Config::DIR_CURVE = GgafCore::Config::DIR_RESOURCE + "/" + Config::DIRNAME_RESOURCE_CURVE + "/";


    UTIL::strReplace(Config::DIR_MESH[0]  , "//", "/");
    UTIL::strReplace(Config::DIR_MODEL[0]  , "//", "/");
    UTIL::strReplace(Config::DIR_TEXTURE[0], "//", "/");
    UTIL::strReplace(Config::DIR_EFFECT[0] , "//", "/");
    UTIL::strReplace(Config::DIR_BGM[0]    , "//", "/");
    UTIL::strReplace(Config::DIR_SE[0]     , "//", "/");
    UTIL::strReplace(Config::DIR_MESH[1]  , "//", "/");
    UTIL::strReplace(Config::DIR_MODEL[1]  , "//", "/");
    UTIL::strReplace(Config::DIR_TEXTURE[1], "//", "/");
    UTIL::strReplace(Config::DIR_EFFECT[1] , "//", "/");
    UTIL::strReplace(Config::DIR_BGM[1]    , "//", "/");
    UTIL::strReplace(Config::DIR_SE[1]     , "//", "/");
    UTIL::strReplace(Config::DIR_MESH[2]  , "//", "/");
    UTIL::strReplace(Config::DIR_MODEL[2]  , "//", "/");
    UTIL::strReplace(Config::DIR_TEXTURE[2], "//", "/");
    UTIL::strReplace(Config::DIR_EFFECT[2] , "//", "/");
    UTIL::strReplace(Config::DIR_BGM[2]    , "//", "/");
    UTIL::strReplace(Config::DIR_SE[2]     , "//", "/");

    UTIL::strReplace(Config::DIR_CURVE     , "//", "/");

    //リソースディレクトリ名指定があるのならば、デフォルトのスキンディレクトリのリソースディレクトリ存在チェック
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_MESH")) {
        if (!PathFileExists(Config::DIR_MESH[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_MESH[0]("<<Config::DIR_MESH[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKIN_XXX_MODEL")) {
        if (!PathFileExists(Config::DIR_MODEL[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_MODEL[0]("<<Config::DIR_MODEL[0]<<") のディレクトリが見つかりません。");
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
    _TRACE_("Config::FULL_SCREEN=" << Config::FULL_SCREEN);
    _TRACE_("Config::DUAL_VIEW=" << Config::DUAL_VIEW);
    _TRACE_("Config::GAME_BUFFER_WIDTH=" << Config::GAME_BUFFER_WIDTH);
    _TRACE_("Config::GAME_BUFFER_HEIGHT=" << Config::GAME_BUFFER_HEIGHT);
    _TRACE_("Config::GAME_SPACE_DEPTH=" << Config::GAME_SPACE_DEPTH);
    _TRACE_("Config::RENDER_DEPTH_INDEXS_NUM=" << Config::RENDER_DEPTH_INDEXS_NUM);
    _TRACE_("Config::RENDER_DEPTH_STAGE_RATIO=" << Config::RENDER_DEPTH_STAGE_RATIO);
    _TRACE_("Config::PRJ_2D_MODE=" << Config::PRJ_2D_MODE);
    _TRACE_("Config::RENDER_TARGET_BUFFER_WIDTH=" << Config::RENDER_TARGET_BUFFER_WIDTH);
    _TRACE_("Config::RENDER_TARGET_BUFFER_HEIGHT=" << Config::RENDER_TARGET_BUFFER_HEIGHT);
    _TRACE_("Config::VIEW_SOURCE_BUFFER_WIDTH=" << Config::VIEW_SOURCE_BUFFER_WIDTH);
    _TRACE_("Config::VIEW_SOURCE_BUFFER_HEIGHT=" << Config::VIEW_SOURCE_BUFFER_HEIGHT);
    _TRACE_("Config::SINGLE_VIEW_WINDOW_WIDTH=" << Config::SINGLE_VIEW_WINDOW_WIDTH);
    _TRACE_("Config::SINGLE_VIEW_WINDOW_HEIGHT=" << Config::SINGLE_VIEW_WINDOW_HEIGHT);
    _TRACE_("Config::DUAL_VIEW_WINDOW1_WIDTH=" << Config::DUAL_VIEW_WINDOW1_WIDTH);
    _TRACE_("Config::DUAL_VIEW_WINDOW1_HEIGHT=" << Config::DUAL_VIEW_WINDOW1_HEIGHT);
    _TRACE_("Config::DUAL_VIEW_WINDOW2_WIDTH=" << Config::DUAL_VIEW_WINDOW2_WIDTH);
    _TRACE_("Config::DUAL_VIEW_WINDOW2_HEIGHT=" << Config::DUAL_VIEW_WINDOW2_HEIGHT);
    _TRACE_("Config::SINGLE_VIEW_FULL_SCREEN_WIDTH=" << Config::SINGLE_VIEW_FULL_SCREEN_WIDTH);
    _TRACE_("Config::SINGLE_VIEW_FULL_SCREEN_HEIGHT=" << Config::SINGLE_VIEW_FULL_SCREEN_HEIGHT);
    _TRACE_("Config::FIXED_GAME_VIEW_ASPECT=" << Config::FIXED_GAME_VIEW_ASPECT);

    _TRACE_("Config::PRIMARY_ADAPTER_NO=" << Config::PRIMARY_ADAPTER_NO);
    _TRACE_("Config::SECONDARY_ADAPTER_NO=" << Config::SECONDARY_ADAPTER_NO);
    _TRACE_("Config::SWAP_GAME_VIEW=" << Config::SWAP_GAME_VIEW);
    _TRACE_("Config::SINGLE_VIEW_DRAW_POSITION=" << Config::SINGLE_VIEW_DRAW_POSITION);
    _TRACE_("Config::DUAL_VIEW_DRAW_POSITION1=" << Config::DUAL_VIEW_DRAW_POSITION1);
    _TRACE_("Config::DUAL_VIEW_DRAW_POSITION2=" << Config::DUAL_VIEW_DRAW_POSITION2);
    _TRACE_("Config::VIEW1_WIDTH_RATIO=" << Config::VIEW1_WIDTH_RATIO);
    _TRACE_("Config::VIEW1_HEIGHT_RATIO=" << Config::VIEW1_HEIGHT_RATIO);
    _TRACE_("Config::VIEW2_WIDTH_RATIO=" << Config::VIEW2_WIDTH_RATIO);
    _TRACE_("Config::VIEW2_HEIGHT_RATIO=" << Config::VIEW2_HEIGHT_RATIO);
    _TRACE_("Config::BORDER_COLOR=" << Config::BORDER_COLOR);
    _TRACE_("Config::BG_COLOR=" << Config::BG_COLOR);
    _TRACE_("Config::MASTER_VOLUME=" << Config::MASTER_VOLUME);
    _TRACE_("Config::BGM_VOLUME=" << Config::BGM_VOLUME);
    _TRACE_("Config::SE_VOLUME=" << Config::SE_VOLUME);
    _TRACE_("Config::MAX_SE_AT_ONCE=" << Config::MAX_SE_AT_ONCE);
    _TRACE_("Config::SE_DELAY_MAX_DEPTH=" << Config::SE_DELAY_MAX_DEPTH);
    _TRACE_("Config::SE_VOLUME_RATE_MAX_DEPTH=" << Config::SE_VOLUME_RATE_MAX_DEPTH);

    _TRACE_("Config::DIRNAME_RESOURCE_SKIN_XXX_MESH=" << Config::DIRNAME_RESOURCE_SKIN_XXX_MESH);
    _TRACE_("Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL=" << Config::DIRNAME_RESOURCE_SKIN_XXX_MODEL);
    _TRACE_("Config::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE=" << Config::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE);
    _TRACE_("Config::DIRNAME_RESOURCE_SKIN_XXX_EFFECT=" << Config::DIRNAME_RESOURCE_SKIN_XXX_EFFECT);
    _TRACE_("Config::DIRNAME_RESOURCE_SKIN_XXX_BGM=" << Config::DIRNAME_RESOURCE_SKIN_XXX_BGM);
    _TRACE_("Config::DIRNAME_RESOURCE_SKIN_XXX_SE=" << Config::DIRNAME_RESOURCE_SKIN_XXX_SE);
    _TRACE_("Config::DIRNAME_RESOURCE_CURVE=" << Config::DIRNAME_RESOURCE_CURVE);

    _TRACE_("Config::DIR_MESH[0]=" << Config::DIR_MESH[0]);
    _TRACE_("Config::DIR_MODEL[0]=" << Config::DIR_MODEL[0]);
    _TRACE_("Config::DIR_TEXTURE[0]=" << Config::DIR_TEXTURE[0]);
    _TRACE_("Config::DIR_EFFECT[0]=" << Config::DIR_EFFECT[0]);
    _TRACE_("Config::DIR_BGM[0]=" << Config::DIR_BGM[0]);
    _TRACE_("Config::DIR_SE[0]=" << Config::DIR_SE[0]);

    _TRACE_("Config::DIR_MESH[1]=" << Config::DIR_MESH[1]);
    _TRACE_("Config::DIR_MODEL[1]=" << Config::DIR_MODEL[1]);
    _TRACE_("Config::DIR_TEXTURE[1]=" << Config::DIR_TEXTURE[1]);
    _TRACE_("Config::DIR_EFFECT[1]=" << Config::DIR_EFFECT[1]);
    _TRACE_("Config::DIR_BGM[1]=" << Config::DIR_BGM[1]);
    _TRACE_("Config::DIR_SE[1]=" << Config::DIR_SE[1]);

    _TRACE_("Config::DIR_MESH[2]=" << Config::DIR_MESH[2]);
    _TRACE_("Config::DIR_MODEL[2]=" << Config::DIR_MODEL[2]);
    _TRACE_("Config::DIR_TEXTURE[2]=" << Config::DIR_TEXTURE[2]);
    _TRACE_("Config::DIR_EFFECT[2]=" << Config::DIR_EFFECT[2]);
    _TRACE_("Config::DIR_BGM[2]=" << Config::DIR_BGM[2]);
    _TRACE_("Config::DIR_SE[2]=" << Config::DIR_SE[2]);

    _TRACE_("Config::DIR_CURVE=" << Config::DIR_CURVE);

    _TRACE_("Config::REALTIME_EFFECT_COMPILE="<<Config::REALTIME_EFFECT_COMPILE);

}


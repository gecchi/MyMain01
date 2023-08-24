#include "jp/ggaf/dx/Config.h"

#include <Shlwapi.h>

using namespace GgafDx;

bool Config::FULL_SCREEN = false;
int Config::NUMBER_OF_SCREENS_USED = 1;

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

int Config::SCREEN_DISPLAY_NO[MAX_SCREENS];

Config::GGAFRECT<pixcoord> Config::SCREEN_RENDER_BUFFER_SOURCE[MAX_SCREENS];
Config::GGAFSIZE<pixcoord> Config::SCREEN_WINDOW[MAX_SCREENS];
Config::GGAFSIZE<pixcoord> Config::SCREEN_FULL_SCREEN[MAX_SCREENS]; //0の場合現在の解像度でフルスクリーン
Config::GGAFSIZE<pixcoord> Config::SCREEN_FULL_SCREEN_BK[MAX_SCREENS];
bool Config::SCREEN_ASPECT_RATIO_FIXED[MAX_SCREENS];
int Config::SCREEN_PRESENT_POSITION[MAX_SCREENS];
Config::GGAFSIZE<double> Config::SCREEN_RATIO[MAX_SCREENS];

std::string Config::BORDER_COLOR = "#222222";
std::string Config::BG_COLOR = "#000000";

int Config::MASTER_VOLUME = 800;
int Config::BGM_VOLUME = 800;
int Config::SE_VOLUME = 800;
int Config::MAX_SE_AT_ONCE = 16;
uint32_t Config::MILLISEC_OF_SE_DELAY_MAX_DEPTH = 3000;
double Config::SE_VOLUME_RATE_MAX_DEPTH=0.2;

std::string Config::DIRNAME_RESOURCE_SKINXXX_MODEL = "model";
std::string Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_MESH = "mesh";
std::string Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_POINT_SPRITE3D = "psprite3d";
std::string Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_SPRITE = "sprite";
std::string Config::DIRNAME_RESOURCE_SKINXXX_TEXTURE = "texture";
std::string Config::DIRNAME_RESOURCE_SKINXXX_EFFECT = "effect";
std::string Config::DIRNAME_RESOURCE_SKINXXX_BGM = "bgm";
std::string Config::DIRNAME_RESOURCE_SKINXXX_SE = "se";

std::string Config::DIR_MODEL[] = {
                GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODEL + "/",
                GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODEL + "/",
                GgafCore::Config::DIR_SKIN_KIND[2] + "/"
            };

std::string Config::DIR_MESH[] = {
                Config::DIR_MODEL[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_MESH + "/",
                Config::DIR_MODEL[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_MESH + "/",
                Config::DIR_MODEL[2] + "/"
            };
std::string Config::DIR_POINT_SPRITE3D[] = {
                Config::DIR_MODEL[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_POINT_SPRITE3D + "/",
                Config::DIR_MODEL[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_POINT_SPRITE3D + "/",
                Config::DIR_MODEL[2] + "/"
            };

std::string Config::DIR_SPRITE[] = {
                Config::DIR_MODEL[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_SPRITE + "/",
                Config::DIR_MODEL[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_SPRITE + "/",
                Config::DIR_MODEL[2] + "/"
            };

std::string Config::DIR_TEXTURE[] = {
                GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/",
                GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/",
                GgafCore::Config::DIR_SKIN_KIND[2]
            };
std::string Config::DIR_EFFECT[] = {
                GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_EFFECT + "/",
                GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_EFFECT + "/",
                GgafCore::Config::DIR_SKIN_KIND[2]
            };
std::string Config::DIR_BGM[] = {
                GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_BGM + "/",
                GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_BGM + "/",
                GgafCore::Config::DIR_SKIN_KIND[2]
            };
std::string Config::DIR_SE[] = {
                GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_SE + "/",
                GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_SE + "/",
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

int Config::P1_JOY_STICK_DEVICE_NO = 0;
int Config::P2_JOY_STICK_DEVICE_NO = 1;

double Config::DEFAULT_DRAW_FAR_RATE = 0.7;

void Config::loadProperties(std::string prm_properties_filename) {
    GgafCore::Config::loadProperties(prm_properties_filename);

    if (GgafCore::Config::_properties.isExistKey("FULL_SCREEN")) {
        Config::FULL_SCREEN = GgafCore::Config::_properties.getBool("FULL_SCREEN");
    }
    if (GgafCore::Config::_properties.isExistKey("NUMBER_OF_SCREENS_USED")) {
        Config::NUMBER_OF_SCREENS_USED = GgafCore::Config::_properties.getInt("NUMBER_OF_SCREENS_USED");
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

    //デフォルト値
    for (int pry = 0; pry < MAX_SCREENS; pry++) {
        Config::SCREEN_DISPLAY_NO[pry] = pry;
    }
    //個別設定値があれば上書き
    for (int pry = 0; pry < MAX_SCREENS; pry++) {
        std::string key = "SCREEN"+ ZPAD(pry+1, 2) + "_DISPLAY_NO"; //SCREEN01_DISPLAY_NO～SCREEN16_DISPLAY_NO
        if (GgafCore::Config::_properties.isExistKey(key)) {
            Config::SCREEN_DISPLAY_NO[pry] = GgafCore::Config::_properties.getInt(key) - 1;

            if (Config::SCREEN_DISPLAY_NO[pry] < 0 || MAX_SCREENS <= Config::SCREEN_DISPLAY_NO[pry]) {
                throwCriticalException(key << "=" << GgafCore::Config::_properties.getInt(key) <<" は範囲外です。\n"<<
                                       "スクリーン番号は 1～"<<MAX_SCREENS<<" の範囲で設定してください。");
            }

        }
    }

    //デフォルト値
    for (int pry = 0; pry < MAX_SCREENS; pry++) {
        Config::SCREEN_RENDER_BUFFER_SOURCE[pry].LEFT   = 0;
        Config::SCREEN_RENDER_BUFFER_SOURCE[pry].TOP    = 0;
        Config::SCREEN_RENDER_BUFFER_SOURCE[pry].WIDTH  = Config::RENDER_TARGET_BUFFER_WIDTH;
        Config::SCREEN_RENDER_BUFFER_SOURCE[pry].HEIGHT = Config::RENDER_TARGET_BUFFER_HEIGHT;
    }
    if (Config::NUMBER_OF_SCREENS_USED == 0) {
        throwCriticalException("NUMBER_OF_SCREENS_USED が、0です。使用モニタ数は 1 以上を指定してください。");
    }

    int a_width = Config::RENDER_TARGET_BUFFER_WIDTH / Config::NUMBER_OF_SCREENS_USED;
    int a_width_add = 0;
    for (int pry = 0; pry < Config::NUMBER_OF_SCREENS_USED; pry++) {
        if (!(pry == (Config::NUMBER_OF_SCREENS_USED-1))) {
            //最後以外
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].LEFT   = a_width_add;
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].TOP    = 0;
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].WIDTH  = a_width;
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].HEIGHT = Config::RENDER_TARGET_BUFFER_HEIGHT;
        } else {
            //最後
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].LEFT   = a_width_add;
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].TOP    = 0;
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].WIDTH  = Config::RENDER_TARGET_BUFFER_WIDTH - a_width_add;
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].HEIGHT = Config::RENDER_TARGET_BUFFER_HEIGHT;
        }
        a_width_add += a_width;
    }
    //共通設定値があれば上書き
    if (GgafCore::Config::_properties.isExistKey("SCREEN_RENDER_BUFFER_SOURCE_LEFT")) {
        for (int pry = 0; pry < MAX_SCREENS; pry++) {
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].LEFT = GgafCore::Config::_properties.getInt("SCREEN_RENDER_BUFFER_SOURCE_LEFT");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("SCREEN_RENDER_BUFFER_SOURCE_TOP")) {
        for (int pry = 0; pry < MAX_SCREENS; pry++) {
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].TOP = GgafCore::Config::_properties.getInt("SCREEN_RENDER_BUFFER_SOURCE_TOP");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("SCREEN_RENDER_BUFFER_SOURCE_WIDTH")) {
        for (int pry = 0; pry < MAX_SCREENS; pry++) {
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].WIDTH = GgafCore::Config::_properties.getInt("SCREEN_RENDER_BUFFER_SOURCE_WIDTH");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("SCREEN_RENDER_BUFFER_SOURCE_HEIGHT")) {
        for (int pry = 0; pry < MAX_SCREENS; pry++) {
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].HEIGHT = GgafCore::Config::_properties.getInt("SCREEN_RENDER_BUFFER_SOURCE_HEIGHT");
        }
    }
    //個別設定値があれば上書き
    for (int pry = 0; pry < MAX_SCREENS; pry++) {
        std::string key = "SCREEN"+ ZPAD(pry+1, 2) + "_RENDER_BUFFER_SOURCE_LEFT"; //SCREEN01_RENDER_BUFFER_SOURCE_LEFT～SCREEN16_RENDER_BUFFER_SOURCE_LEFT
        if (GgafCore::Config::_properties.isExistKey(key)) {
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].LEFT = GgafCore::Config::_properties.getInt(key);
        }
        key = "SCREEN"+ ZPAD(pry+1, 2) + "_RENDER_BUFFER_SOURCE_TOP"; //SCREEN01_RENDER_BUFFER_SOURCE_TOP～SCREEN16_RENDER_BUFFER_SOURCE_TOP
        if (GgafCore::Config::_properties.isExistKey(key)) {
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].TOP = GgafCore::Config::_properties.getInt(key);
        }
        key = "SCREEN"+ ZPAD(pry+1, 2) + "_RENDER_BUFFER_SOURCE_WIDTH"; //SCREEN01_RENDER_BUFFER_SOURCE_WIDTH～SCREEN16_RENDER_BUFFER_SOURCE_WIDTH
        if (GgafCore::Config::_properties.isExistKey(key)) {
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].WIDTH = GgafCore::Config::_properties.getInt(key);
        }
        key = "SCREEN"+ ZPAD(pry+1, 2) + "_RENDER_BUFFER_SOURCE_HEIGHT"; //SCREEN01_RENDER_BUFFER_SOURCE_HEIGHT～SCREEN16_RENDER_BUFFER_SOURCE_HEIGHT
        if (GgafCore::Config::_properties.isExistKey(key)) {
            Config::SCREEN_RENDER_BUFFER_SOURCE[pry].HEIGHT = GgafCore::Config::_properties.getInt(key);
        }
    }

    //デフォルト値
    for (int pry = 0; pry < MAX_SCREENS; pry++) {
        Config::SCREEN_WINDOW[pry].WIDTH = SCREEN_RENDER_BUFFER_SOURCE[pry].WIDTH;
        Config::SCREEN_WINDOW[pry].HEIGHT = SCREEN_RENDER_BUFFER_SOURCE[pry].HEIGHT;
    }
    //共通設定値があれば上書き
    if (GgafCore::Config::_properties.isExistKey("SCREEN_WINDOW_WIDTH")) {
        for (int pry = 0; pry < MAX_SCREENS; pry++) {
            Config::SCREEN_WINDOW[pry].WIDTH = GgafCore::Config::_properties.getInt("SCREEN_WINDOW_WIDTH");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("SCREEN_WINDOW_HEIGHT")) {
        for (int pry = 0; pry < MAX_SCREENS; pry++) {
            Config::SCREEN_WINDOW[pry].HEIGHT = GgafCore::Config::_properties.getInt("SCREEN_WINDOW_HEIGHT");
        }
    }
    //個別設定値があれば上書き
    for (int pry = 0; pry < MAX_SCREENS; pry++) {
        std::string key = "SCREEN"+ ZPAD(pry+1, 2) + "_WINDOW_WIDTH"; //SCREEN01_WINDOW_WIDTH～SCREEN16_WINDOW_WIDTH
        if (GgafCore::Config::_properties.isExistKey(key)) {
            Config::SCREEN_WINDOW[pry].WIDTH = GgafCore::Config::_properties.getInt(key);
        }
        key = "SCREEN"+ ZPAD(pry+1, 2) + "_WINDOW_HEIGHT"; //SCREEN01_WINDOW_HEIGHT～SCREEN16_WINDOW_HEIGHT
        if (GgafCore::Config::_properties.isExistKey(key)) {
            Config::SCREEN_WINDOW[pry].HEIGHT = GgafCore::Config::_properties.getInt(key);
        }
    }

    //デフォルト値（0の場合現在の解像度でフルスクリーン）
    for (int pry = 0; pry < MAX_SCREENS; pry++) {
        Config::SCREEN_FULL_SCREEN[pry].WIDTH = 0;
        Config::SCREEN_FULL_SCREEN[pry].HEIGHT = 0;
        Config::SCREEN_FULL_SCREEN_BK[pry].WIDTH  = Config::SCREEN_FULL_SCREEN[pry].WIDTH;
        Config::SCREEN_FULL_SCREEN_BK[pry].HEIGHT = Config::SCREEN_FULL_SCREEN[pry].HEIGHT;
    }
    //共通設定値があれば上書き
    if (GgafCore::Config::_properties.isExistKey("SCREEN_WINDOW_WIDTH")) {
        for (int pry = 0; pry < MAX_SCREENS; pry++) {
            Config::SCREEN_FULL_SCREEN[pry].WIDTH = GgafCore::Config::_properties.getInt("SCREEN_WINDOW_WIDTH");
            Config::SCREEN_FULL_SCREEN_BK[pry].WIDTH = Config::SCREEN_FULL_SCREEN[pry].WIDTH;
        }
    }
    if (GgafCore::Config::_properties.isExistKey("SCREEN_WINDOW_HEIGHT")) {
        for (int pry = 0; pry < MAX_SCREENS; pry++) {
            Config::SCREEN_FULL_SCREEN[pry].HEIGHT = GgafCore::Config::_properties.getInt("SCREEN_WINDOW_HEIGHT");
            Config::SCREEN_FULL_SCREEN_BK[pry].HEIGHT = Config::SCREEN_FULL_SCREEN[pry].HEIGHT;
        }
    }
    //設定値があれば上書き（指定解像度でフルスクリーン）
    for (int pry = 0; pry < MAX_SCREENS; pry++) {
        std::string key = "SCREEN"+ ZPAD(pry+1, 2) + "_FULL_SCREEN_WIDTH"; //SCREEN01_WINDOW_WIDTH～SCREEN16_WINDOW_WIDTH
        if (GgafCore::Config::_properties.isExistKey(key)) {
            Config::SCREEN_FULL_SCREEN[pry].WIDTH = GgafCore::Config::_properties.getInt(key);
            Config::SCREEN_FULL_SCREEN_BK[pry].WIDTH = Config::SCREEN_FULL_SCREEN[pry].WIDTH;
        }
        key = "SCREEN"+ ZPAD(pry+1, 2) + "_FULL_SCREEN_HEIGHT"; //SCREEN01_WINDOW_HEIGHT～SCREEN16_WINDOW_HEIGHT
        if (GgafCore::Config::_properties.isExistKey(key)) {
            Config::SCREEN_FULL_SCREEN[pry].HEIGHT = GgafCore::Config::_properties.getInt(key);
            Config::SCREEN_FULL_SCREEN_BK[pry].HEIGHT = Config::SCREEN_FULL_SCREEN[pry].HEIGHT;
        }
    }

    //デフォルト値
    for (int pry = 0; pry < MAX_SCREENS; pry++) {
        Config::SCREEN_ASPECT_RATIO_FIXED[pry] = true;
    }
    //共通設定値があれば上書き
    if (GgafCore::Config::_properties.isExistKey("SCREEN_ASPECT_RATIO_FIXED")) {
        for (int pry = 0; pry < MAX_SCREENS; pry++) {
            Config::SCREEN_ASPECT_RATIO_FIXED[pry] = GgafCore::Config::_properties.getBool("SCREEN_ASPECT_RATIO_FIXED");
        }
    }
    //設定値があれば上書き
    for (int pry = 0; pry < MAX_SCREENS; pry++) {
        std::string key = "SCREEN"+ ZPAD(pry+1, 2) + "_ASPECT_RATIO_FIXED"; //SCREEN01_ASPECT_RATIO_FIXED～SCREEN16_ASPECT_RATIO_FIXED
        if (GgafCore::Config::_properties.isExistKey(key)) {
            Config::SCREEN_ASPECT_RATIO_FIXED[pry] = GgafCore::Config::_properties.getBool(key);
        }
    }

    //デフォルト値
    for (int pry = 0; pry < MAX_SCREENS; pry++) {
        Config::SCREEN_PRESENT_POSITION[pry] = 5;
    }
    //共通設定値があれば上書き
    if (GgafCore::Config::_properties.isExistKey("SCREEN_PRESENT_POSITION")) {
        for (int pry = 0; pry < MAX_SCREENS; pry++) {
            Config::SCREEN_PRESENT_POSITION[pry] = GgafCore::Config::_properties.getInt("SCREEN_PRESENT_POSITION");
        }
    }
    //設定値があれば上書き
    for (int pry = 0; pry < MAX_SCREENS; pry++) {
        std::string key = "SCREEN"+ ZPAD(pry+1, 2) + "_PRESENT_POSITION"; //SCREEN01_PRESENT_POSITION～SCREEN16_PRESENT_POSITION
        if (GgafCore::Config::_properties.isExistKey(key)) {
            Config::SCREEN_PRESENT_POSITION[pry] = GgafCore::Config::_properties.getInt(key);
        }
    }

    //デフォルト値
    for (int pry = 0; pry < MAX_SCREENS; pry++) {
        Config::SCREEN_RATIO[pry].WIDTH = 1.0;
        Config::SCREEN_RATIO[pry].HEIGHT = 1.0;
    }
    //共通設定値があれば上書き
    if (GgafCore::Config::_properties.isExistKey("SCREEN_WIDTH_RATIO")) {
        for (int pry = 0; pry < MAX_SCREENS; pry++) {
            Config::SCREEN_RATIO[pry].WIDTH  = GgafCore::Config::_properties.getDouble("SCREEN_WIDTH_RATIO");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("SCREEN_HEIGHT_RATIO")) {
        for (int pry = 0; pry < MAX_SCREENS; pry++) {
            Config::SCREEN_RATIO[pry].HEIGHT  = GgafCore::Config::_properties.getDouble("SCREEN_HEIGHT_RATIO");
        }
    }
    //設定値で上書き
    for (int pry = 0; pry < MAX_SCREENS; pry++) {
        std::string key = "SCREEN"+ ZPAD(pry+1, 2) + "_WIDTH_RATIO"; //SCREEN01_WIDTH_RATIO～SCREEN16_WIDTH_RATIO
        if (GgafCore::Config::_properties.isExistKey(key)) {
            Config::SCREEN_RATIO[pry].WIDTH = GgafCore::Config::_properties.getDouble(key);
        }
        key = "SCREEN"+ ZPAD(pry+1, 2) + "_HEIGHT_RATIO"; //SCREEN01_HEIGHT_RATIO～SCREEN16_HEIGHT_RATIO
        if (GgafCore::Config::_properties.isExistKey(key)) {
            Config::SCREEN_RATIO[pry].HEIGHT = GgafCore::Config::_properties.getDouble(key);
        }
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
    if (GgafCore::Config::_properties.isExistKey("MILLISEC_OF_SE_DELAY_MAX_DEPTH")) {
        Config::MILLISEC_OF_SE_DELAY_MAX_DEPTH = GgafCore::Config::_properties.getUInt("MILLISEC_OF_SE_DELAY_MAX_DEPTH");
    }

    if (MSEC_F(Config::MILLISEC_OF_SE_DELAY_MAX_DEPTH)*2 > GgafCore::Config::END_DELAY_FRAME) {
        throwCriticalException("Config::MILLISEC_OF_SE_DELAY_MAX_DEPTH("<<Config::MILLISEC_OF_SE_DELAY_MAX_DEPTH<<")＝"<<MSEC_F(Config::MILLISEC_OF_SE_DELAY_MAX_DEPTH)<<"frameは、END_DELAY_FRAME("<<(GgafCore::Config::END_DELAY_FRAME)<<")フレームの半分以下の時間である必要があります。\n"<<
                "MILLISEC_OF_SE_DELAY_MAX_DEPTH の設定値をもっと下げてください。");
    }

    if (GgafCore::Config::_properties.isExistKey("SE_VOLUME_RATE_MAX_DEPTH")) {
        Config::SE_VOLUME_RATE_MAX_DEPTH = GgafCore::Config::_properties.getDouble("SE_VOLUME_RATE_MAX_DEPTH");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKINXXX_MODEL")) {
        Config::DIRNAME_RESOURCE_SKINXXX_MODEL = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKINXXX_MODEL");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKINXXX_MODELXXX_MESH")) {
        Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_MESH = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKINXXX_MODELXXX_MESH");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKINXXX_MODELXXX_SPRITE")) {
        Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_SPRITE = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKINXXX_MODELXXX_SPRITE");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKINXXX_TEXTURE")) {
        Config::DIRNAME_RESOURCE_SKINXXX_TEXTURE = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKINXXX_TEXTURE");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKINXXX_EFFECT")) {
        Config::DIRNAME_RESOURCE_SKINXXX_EFFECT = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKINXXX_EFFECT");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKINXXX_BGM")) {
        Config::DIRNAME_RESOURCE_SKINXXX_BGM = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKINXXX_BGM");
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKINXXX_SE")) {
        Config::DIRNAME_RESOURCE_SKINXXX_SE = GgafCore::Config::_properties.getStr("DIRNAME_RESOURCE_SKINXXX_SE");
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

    Config::DIR_MODEL[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODEL + "/";
      Config::DIR_MESH[0] = Config::DIR_MODEL[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_MESH + "/";
      Config::DIR_POINT_SPRITE3D[0] = Config::DIR_MODEL[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_POINT_SPRITE3D + "/";
      Config::DIR_SPRITE[0] = Config::DIR_MODEL[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_SPRITE + "/";
    Config::DIR_TEXTURE[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
    Config::DIR_EFFECT[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_EFFECT + "/";
    Config::DIR_BGM[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_BGM + "/";
    Config::DIR_SE[0] = GgafCore::Config::DIR_SKIN_KIND[0] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_SE + "/";

    Config::DIR_MODEL[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODEL + "/";
      Config::DIR_MESH[1] = Config::DIR_MODEL[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_MESH + "/";
      Config::DIR_POINT_SPRITE3D[1] = Config::DIR_MODEL[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_POINT_SPRITE3D + "/";
      Config::DIR_SPRITE[1] = Config::DIR_MODEL[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_SPRITE + "/";
    Config::DIR_TEXTURE[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
    Config::DIR_EFFECT[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_EFFECT + "/";
    Config::DIR_BGM[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_BGM + "/";
    Config::DIR_SE[1] = GgafCore::Config::DIR_SKIN_KIND[1] + "/" + Config::DIRNAME_RESOURCE_SKINXXX_SE + "/";


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
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKINXXX_MODEL")) {
        if (!PathFileExists(Config::DIR_MODEL[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_MODEL[0]("<<Config::DIR_MODEL[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKINXXX_MODELXXX_MESH")) {
        if (!PathFileExists(Config::DIR_MESH[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_MESH[0]("<<Config::DIR_MESH[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKINXXX_MODELXXX_POINT_SPRITE3D")) {
        if (!PathFileExists(Config::DIR_POINT_SPRITE3D[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_POINT_SPRITE3D[0]("<<Config::DIR_POINT_SPRITE3D[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKINXXX_MODELXXX_SPRITE")) {
        if (!PathFileExists(Config::DIR_SPRITE[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_SPRITE[0]("<<Config::DIR_SPRITE[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKINXXX_TEXTURE")) {
        if (!PathFileExists(Config::DIR_TEXTURE[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_TEXTURE[0]("<<Config::DIR_TEXTURE[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKINXXX_EFFECT")) {
        if (!PathFileExists(Config::DIR_EFFECT[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_EFFECT[0]("<<Config::DIR_EFFECT[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKINXXX_BGM")) {
        if (!PathFileExists(Config::DIR_BGM[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_BGM[0]("<<Config::DIR_BGM[0]<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafCore::Config::_properties.isExistKey("DIRNAME_RESOURCE_SKINXXX_SE")) {
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

    if (GgafCore::Config::_properties.isExistKey("P1_JOY_STICK_DEVICE_NO")) {
        Config::P1_JOY_STICK_DEVICE_NO  = GgafCore::Config::_properties.getInt("P1_JOY_STICK_DEVICE_NO");
    }
    if (GgafCore::Config::_properties.isExistKey("P2_JOY_STICK_DEVICE_NO")) {
        Config::P2_JOY_STICK_DEVICE_NO  = GgafCore::Config::_properties.getInt("P2_JOY_STICK_DEVICE_NO");
    }

    if (GgafCore::Config::_properties.isExistKey("DEFAULT_DRAW_FAR_RATE")) {
        Config::DEFAULT_DRAW_FAR_RATE = GgafCore::Config::_properties.getDouble("DEFAULT_DRAW_FAR_RATE");
    }

    _TRACE_("Config::FULL_SCREEN=" << Config::FULL_SCREEN);
    _TRACE_("Config::NUMBER_OF_SCREENS_USED=" << Config::NUMBER_OF_SCREENS_USED);
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

    for (int pry = 0; pry < Config::NUMBER_OF_SCREENS_USED; pry++) {
        _TRACE_("Config::SCREEN_RENDER_BUFFER_SOURCE["<<pry<<"].LEFT="   << Config::SCREEN_RENDER_BUFFER_SOURCE[pry].LEFT   );
        _TRACE_("Config::SCREEN_RENDER_BUFFER_SOURCE["<<pry<<"].TOP="    << Config::SCREEN_RENDER_BUFFER_SOURCE[pry].TOP    );
        _TRACE_("Config::SCREEN_RENDER_BUFFER_SOURCE["<<pry<<"].WIDTH="  << Config::SCREEN_RENDER_BUFFER_SOURCE[pry].WIDTH  );
        _TRACE_("Config::SCREEN_RENDER_BUFFER_SOURCE["<<pry<<"].HEIGHT=" << Config::SCREEN_RENDER_BUFFER_SOURCE[pry].HEIGHT );
        _TRACE_("Config::SCREEN_WINDOW["<<pry<<"].WIDTH="  << Config::SCREEN_WINDOW[pry].WIDTH);
        _TRACE_("Config::SCREEN_WINDOW["<<pry<<"].HEIGHT=" << Config::SCREEN_WINDOW[pry].HEIGHT);
        _TRACE_("Config::SCREEN_ASPECT_RATIO_FIXED["<<pry<<"]=" << Config::SCREEN_ASPECT_RATIO_FIXED[pry]);
        _TRACE_("Config::SCREEN_DISPLAY_NO["<<pry<<"]=" << Config::SCREEN_DISPLAY_NO[pry]);
        _TRACE_("Config::SCREEN_PRESENT_POSITION["<<pry<<"]=" << Config::SCREEN_PRESENT_POSITION[pry]);
        _TRACE_("Config::SCREEN_RATIO["<<pry<<"].WIDTH=" << Config::SCREEN_RATIO[pry].WIDTH);
        _TRACE_("Config::SCREEN_RATIO["<<pry<<"].HEIGHT=" << Config::SCREEN_RATIO[pry].HEIGHT);
    }
    _TRACE_("Config::BORDER_COLOR=" << Config::BORDER_COLOR);
    _TRACE_("Config::BG_COLOR=" << Config::BG_COLOR);
    _TRACE_("Config::MASTER_VOLUME=" << Config::MASTER_VOLUME);
    _TRACE_("Config::BGM_VOLUME=" << Config::BGM_VOLUME);
    _TRACE_("Config::SE_VOLUME=" << Config::SE_VOLUME);
    _TRACE_("Config::MAX_SE_AT_ONCE=" << Config::MAX_SE_AT_ONCE);
    _TRACE_("Config::MILLISEC_OF_SE_DELAY_MAX_DEPTH=" << Config::MILLISEC_OF_SE_DELAY_MAX_DEPTH);
    _TRACE_("Config::SE_VOLUME_RATE_MAX_DEPTH=" << Config::SE_VOLUME_RATE_MAX_DEPTH);

    _TRACE_("Config::DIRNAME_RESOURCE_SKINXXX_MODEL=" << Config::DIRNAME_RESOURCE_SKINXXX_MODEL);
    _TRACE_("Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_MESH=" << Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_MESH);
    _TRACE_("Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_SPRITE=" << Config::DIRNAME_RESOURCE_SKINXXX_MODELXXX_SPRITE);
    _TRACE_("Config::DIRNAME_RESOURCE_SKINXXX_TEXTURE=" << Config::DIRNAME_RESOURCE_SKINXXX_TEXTURE);
    _TRACE_("Config::DIRNAME_RESOURCE_SKINXXX_EFFECT=" << Config::DIRNAME_RESOURCE_SKINXXX_EFFECT);
    _TRACE_("Config::DIRNAME_RESOURCE_SKINXXX_BGM=" << Config::DIRNAME_RESOURCE_SKINXXX_BGM);
    _TRACE_("Config::DIRNAME_RESOURCE_SKINXXX_SE=" << Config::DIRNAME_RESOURCE_SKINXXX_SE);
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

    _TRACE_("Config::P1_JOY_STICK_DEVICE_NO=" << Config::P1_JOY_STICK_DEVICE_NO);
    _TRACE_("Config::P2_JOY_STICK_DEVICE_NO=" << Config::P2_JOY_STICK_DEVICE_NO);

    _TRACE_("Config::DEFAULT_DRAW_FAR_RATE=" << Config::DEFAULT_DRAW_FAR_RATE);
}


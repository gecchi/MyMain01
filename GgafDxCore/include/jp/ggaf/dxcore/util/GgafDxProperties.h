#ifndef GGAFDXPROPERTIES_H_
#define GGAFDXPROPERTIES_H_

#ifdef CFG_PROPERTY
    #undef CFG_PROPERTY
#endif
#define CFG_PROPERTY(X) (GgafDxCore::GgafDxProperties::X)

namespace GgafDxCore {

class GgafDxProperties: public GgafCore::GgafProperties {
public:
    static bool FULL_SCREEN;
    static bool DUAL_VIEW;
    static pixcoord GAME_BUFFER_WIDTH;
    static pixcoord GAME_BUFFER_HEIGHT;
    static float GAME_SPACE_DEPTH;
    static pixcoord RENDER_TARGET_BUFFER_WIDTH;
    static pixcoord RENDER_TARGET_BUFFER_HEIGHT;

    static pixcoord SINGLE_VIEW_WINDOW_WIDTH;
    static pixcoord SINGLE_VIEW_WINDOW_HEIGHT;
    static pixcoord DUAL_VIEW_WINDOW1_WIDTH;
    static pixcoord DUAL_VIEW_WINDOW1_HEIGHT;
    static pixcoord DUAL_VIEW_WINDOW2_WIDTH;
    static pixcoord DUAL_VIEW_WINDOW2_HEIGHT;

    static pixcoord SINGLE_VIEW_FULL_SCREEN_WIDTH;
    static pixcoord SINGLE_VIEW_FULL_SCREEN_HEIGHT;
    static pixcoord DUAL_VIEW_FULL_SCREEN1_WIDTH;
    static pixcoord DUAL_VIEW_FULL_SCREEN1_HEIGHT;
    static pixcoord DUAL_VIEW_FULL_SCREEN2_WIDTH;
    static pixcoord DUAL_VIEW_FULL_SCREEN2_HEIGHT;
    static pixcoord DUAL_VIEW_FULL_SCREEN_WIDTH;
    static pixcoord DUAL_VIEW_FULL_SCREEN_HEIGHT;
    static bool FIXED_GAME_VIEW_ASPECT;
    static bool SWAP_GAME_VIEW;
    static int SINGLE_VIEW_DRAW_POSITION;
    static int DUAL_VIEW_DRAW_POSITION1;
    static int DUAL_VIEW_DRAW_POSITION2;
    static std::string BG_COLOR;

    static int MASTER_VOLUME;
    static int BGM_VOLUME;
    static int SE_VOLUME;
    static std::string DIR_MESH_MODEL;
    static std::string DIR_SPRITE_MODEL;
    static std::string DIR_TEXTURE;
    static std::string DIR_EFFECT;
    static std::string DIR_OGG;
    static std::string DIR_WAVE;

    static bool REALTIME_EFFECT_COMPILE;

    static void load(std::string prm_ini_filename); //shadows
    static void clean();                            //shadows
};

}
#endif /*GGAFDXPROPERTIES_H_*/


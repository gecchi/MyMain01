#ifndef GGAFDX9PROPERTIES_H_
#define GGAFDX9PROPERTIES_H_

#define GGAFDX9_PROPERTY(X) (*GgafDx9Core::GgafDx9Properties::X)

namespace GgafDx9Core {

class GgafDx9Properties: public GgafCore::GgafProperties {
public:
    static bool* FULL_SCREEN;
    static int* GAME_BUFFER_WIDTH;
    static int* GAME_BUFFER_HEIGHT;
    static float* GAME_SPACE_DEPTH;
    static int* VIEW_SCREEN_WIDTH;
    static int* VIEW_SCREEN_HEIGHT;
    static bool* FIXED_VIEW_ASPECT;
    static int* MASTER_VOLUME;
    static int* BGM_VOLUME;
    static int* SE_VOLUME;
    static std::string* DIR_MESH_MODEL;
    static std::string* DIR_SPRITE_MODEL;
    static std::string* DIR_TEXTURE;
    static std::string* DIR_EFFECT;
    static std::string* DIR_OGG;
    static std::string* DIR_WAVE;

    static void load(std::string prm_ini_filename);
    static void clean();
};

}
#endif /*GGAFDX9PROPERTIES_H_*/


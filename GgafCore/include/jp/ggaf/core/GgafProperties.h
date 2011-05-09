#ifndef GGAFPROPERTIES
#define GGAFPROPERTIES


#ifdef  PROPERTY
    #undef PROPERTY
#endif
#define PROPERTY(X) (GgafCore::GgafProperties::X)

namespace GgafCore {

/**
 * プロパティクラス .
 * 外部ファイルから読み込こみ、アプリの環境変数を保持します。
 * @version 1.00
 * @since 2008/07/22
 * @author Masatoshi Tsuge
 */
class GgafProperties {

public:
    static UINT32 MAX_SKIP_FRAME;
    static int DRAWNUM_TO_SLOWDOWN1;
    static int DRAWNUM_TO_SLOWDOWN2;
    static float FPS_TO_CLEAN_GARBAGE_BOX;
    static void load(std::string prm_properties_filename);
    static void clean();

    static std::_MAP_<std::string, std::string>* _pMapProperties;

    static int read(std::string prm_properties_filename);
    static void parse(char* p);
    static bool isExistKey(std::string prm_key);
    static std::string getStr(std::string prm_key);
    static bool getBool(std::string prm_key);
    static float getFloat(std::string prm_key);
    static int getInt(std::string prm_key);
    static UINT32 getUInt(std::string prm_key);
    static double getDouble(std::string prm_key);
};

}
#endif /*GGAFPROPERTIES*/


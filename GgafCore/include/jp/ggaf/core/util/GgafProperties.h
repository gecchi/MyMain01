#ifndef GGAFPROPERTIES
#define GGAFPROPERTIES

#define GGAF_PROPERTY(X) (*GgafCore::GgafProperties::X)

/**
 * プロパティクラス .
 * 外部ファイルから読み込こみ、アプリの環境変数を保持します。
 * @version 1.00
 * @since 2009/08/21
 * @author Masatoshi Tsuge
 */
namespace GgafCore {

class GgafProperties {

public:
    static DWORD* MAX_SKIP_FRAME;

    static void load(std::string prm_properties_filename);
    static void clean();

    static std::map<std::string, std::string>* _pMapProperties;

    static int read(std::string prm_properties_filename);
    static void parse(char* p);
    static bool isExistKey(std::string prm_key);
    static std::string* getStr(std::string prm_key);
    static bool* getBool(std::string prm_key);
    static int* getInt(std::string prm_key);
    static DWORD* getDWORD(std::string prm_key);
    static double* getDouble(std::string prm_key);
};

}
#endif /*GGAFPROPERTIES*/


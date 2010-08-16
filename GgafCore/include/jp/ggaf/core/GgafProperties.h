#ifndef GGAFPROPERTIES
#define GGAFPROPERTIES

#define GGAF_PROPERTY(X) (*GgafCore::GgafProperties::X)


namespace GgafCore {

/**
 * �v���p�e�B�N���X .
 * �O���t�@�C������ǂݍ����݁A�A�v���̊��ϐ���ێ����܂��B
 * @version 1.00
 * @since 2008/07/22
 * @author Masatoshi Tsuge
 */
class GgafProperties {

public:
    static UINT32* MAX_SKIP_FRAME;

    static void load(std::string prm_properties_filename);
    static void clean();

    static std::map<std::string, std::string>* _pMapProperties;

    static int read(std::string prm_properties_filename);
    static void parse(char* p);
    static bool isExistKey(std::string prm_key);
    static std::string* getStr(std::string prm_key);
    static bool* getBool(std::string prm_key);
    static float* getFloat(std::string prm_key);
    static int* getInt(std::string prm_key);
    static UINT32* getUInt(std::string prm_key);
    static double* getDouble(std::string prm_key);
};

}
#endif /*GGAFPROPERTIES*/


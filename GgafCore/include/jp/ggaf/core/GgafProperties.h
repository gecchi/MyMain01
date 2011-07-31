#ifndef GGAFPROPERTIES_H_
#define GGAFPROPERTIES_H_


#ifdef CFG_PROPERTY
    #undef CFG_PROPERTY
#endif
#define CFG_PROPERTY(X) (GgafCore::GgafProperties::X)

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
    static UINT32 MAX_SKIP_FRAME;
    static int DRAWNUM_TO_SLOWDOWN1;
    static int DRAWNUM_TO_SLOWDOWN2;
    static float FPS_TO_CLEAN_GARBAGE_BOX;

    static void load(std::string prm_properties_filename);
    static void clean();



//    static int read(std::string prm_properties_filename);
//    static void parse(char* p);

    typedef std::map<std::string, std::string> PropertyMapT;
    typedef PropertyMapT::value_type           value_type;
    typedef PropertyMapT::iterator             iteratorP;



    static PropertyMapT* _pMapProperties;

    static void read(std::string filename, PropertyMapT* pMap);
    static void read(std::istream &is, PropertyMapT* pMap);
    static void write(const char *filename, PropertyMapT* pMap, const char *header = NULL);
    static void write(std::ostream &os, PropertyMapT* pMap, const char *header = NULL);
    static void print(std::ostream &os, PropertyMapT* pMap);
    static inline char m_hex(int nibble)
    {
        static const char *digits = "0123456789ABCDEF";
        return digits[nibble & 0xf];
    }



    static bool isExistKey(std::string prm_key);
    static std::string getStr(std::string prm_key);
    static bool getBool(std::string prm_key);
    static float getFloat(std::string prm_key);
    static int getInt(std::string prm_key);
    static UINT32 getUInt(std::string prm_key);
    static double getDouble(std::string prm_key);
    static GgafRgb getRGB(std::string prm_key);

};

}
#endif /*GGAFPROPERTIES_H_*/


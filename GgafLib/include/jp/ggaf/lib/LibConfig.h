#ifndef GGAFLIBCONFIGH_
#define GGAFLIBCONFIGH_
#include "jp/ggaf/dx/Config.h"

#ifdef CONFIG
    #undef CONFIG
#endif
#define CONFIG GgafLib::LibConfig

namespace GgafLib {

class LibConfig: public GgafDx::Config {
public:
    /** [r] シーン地形データファイル(datファイル)格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_WALL;

    ////// 以下は、上記プロパティから生成される読み出し専用プロパティ ////////

    /** [r] シーン地形データファイル(datファイル)格納ディレクトリ */
    static std::string DIR_WALL;

public:
    static void loadProperties(std::string prm_properties_filename); //shadows
};

}
#endif /*GGAFLIBCONFIGH_*/


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
    /** [r] 八分木空間レベル数 */
    static int OCTREE_LEVEL;
    /** [r] 四分木空間レベル数 */
    static int QUADTREE_LEVEL;
    /** [r] ヒットチェックに使用する空間分割は八分木場合true／それ以外はfalse */
    static bool IS_HIT_CHECK_3D;
    /** [r] ヒットチェックに使用する空間分割は四分木場合true／それ以外はfalse */
    static bool IS_HIT_CHECK_2D;

    ////// 以下は、上記プロパティから生成される読み出し専用プロパティ ////////

    /** [r] シーン地形データファイル(datファイル)格納ディレクトリ */
    static std::string DIR_WALL;



public:
    static void loadProperties(std::string prm_properties_filename); //shadows
};

}
#endif /*GGAFLIBCONFIGH_*/


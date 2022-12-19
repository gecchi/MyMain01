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
    /** [r] ワールドヒットチェックの八分木空間レベル数 */
    static int WORLD_HIT_CHECK_OCTREE_LEVEL;
    /** [r] ワールドヒットチェックの四分木空間レベル数 */
    static int WORLD_HIT_CHECK_QUADTREE_LEVEL;
    /** [r] ビューヒットチェックの四分木空間レベル数 */
    static int VIEW_HIT_CHECK_QUADTREE_LEVEL;
    /** [r] ヒットチェックに使用する空間分割、true：四分木場合／false：八分木（デフォルト） */
    static bool ENABLE_WORLD_HIT_CHECK_2D;

    ////// 以下は、上記プロパティから生成される読み出し専用プロパティ ////////

    /** [r] シーン地形データファイル(datファイル)格納ディレクトリ */
    static std::string DIR_WALL;

public:
    static void loadProperties(std::string prm_properties_filename); //shadows
};

}
#endif /*GGAFLIBCONFIGH_*/


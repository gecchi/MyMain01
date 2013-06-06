#ifndef GGAFLIBPROPERTIESH_
#define GGAFLIBPROPERTIESH_
#include "jp/ggaf/dxcore/GgafDxProperties.h"

#include <Shlwapi.h>

#ifdef PROPERTY
    #undef PROPERTY
#endif
#define PROPERTY GgafLib::GgafLibProperties

namespace GgafLib {

class GgafLibProperties: public GgafDxCore::GgafDxProperties {
public:
    /** [r] シーン地形データファイル(datファイル)格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_WALL;
    /** [r] スプライン曲線座標情報ファイル(datファイル)格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SPLINE;
    /** [r] ８分木空間レベル数 */
    static int OCTREE_LEVEL;

    ////// 以下は、上記プロパティから生成される読み出し専用プロパティ ////////

    /** [r] シーン地形データファイル(datファイル)格納ディレクトリ */
    static std::string DIR_WALL;
    /** [r] スプライン曲線座標情報ファイル(datファイル)格納ディレクトリ */
    static std::string DIR_SPLINE;


public:
    static void load(std::string prm_properties_filename); //shadows
    static void clean();                            //shadows
};

}
#endif /*GGAFLIBPROPERTIESH_*/


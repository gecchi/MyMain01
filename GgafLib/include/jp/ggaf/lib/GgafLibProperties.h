#ifndef GGAFLIBPROPERTIESH_
#define GGAFLIBPROPERTIESH_

#ifdef GGAF_PROPERTY
    #undef GGAF_PROPERTY
#endif
#define GGAF_PROPERTY(X) (GgafLib::GgafLibProperties::X)

namespace GgafLib {

class GgafLibProperties: public GgafDxCore::GgafDxProperties {
public:
    /** [r] シーン地形データファイル(datファイル)格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_WALL;
    /** [r] スプライン曲線座標情報ファイル(datファイル)格納ディレクトリ名 */
    static std::string DIRNAME_RESOURCE_SPLINE;

    /** [r] シーン地形データファイル(datファイル)格納ディレクトリ(0:default/1:ユーザー) */
    static std::string DIR_WALL;
    /** [r] スプライン曲線座標情報ファイル(datファイル)格納ディレクトリ(0:default/1:ユーザー) */
    static std::string DIR_SPLINE;

    /** [r] ８分木空間レベル数 */
    static int OCTREE_LEVEL;

    static void load(std::string prm_properties_filename); //shadows
    static void clean();                            //shadows
};

}
#endif /*GGAFLIBPROPERTIESH_*/


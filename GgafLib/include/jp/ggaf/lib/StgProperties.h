#ifndef STGPROPERTIES_H_
#define STGPROPERTIES_H_

#ifdef CFG_PROPERTY
    #undef CFG_PROPERTY
#endif
#define CFG_PROPERTY(X) (GgafLib::StgProperties::X)

namespace GgafLib {

class StgProperties: public GgafDxCore::GgafDxProperties {
public:
    /** [r] シーン地形データファイル(datファイル)格納ディレクトリ */
    static std::string DIR_SCENE_DATA;
    /** [r] スプライン曲線座標情報ファイル(datファイル)格納ディレクトリ */
    static std::string DIR_SPLINE_DATA;

    static void load(std::string prm_ini_filename); //shadows
    static void clean();                            //shadows
};

}
#endif /*STGPROPERTIES_H_*/


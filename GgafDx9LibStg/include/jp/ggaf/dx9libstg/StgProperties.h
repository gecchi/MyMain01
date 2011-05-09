#ifndef STGPROPERTIES_H_
#define STGPROPERTIES_H_

#ifdef  PROPERTY
    #undef PROPERTY
#endif
#define PROPERTY(X) (GgafDx9LibStg::StgProperties::X)

namespace GgafDx9LibStg {

class StgProperties: public GgafDx9Core::GgafDx9Properties {
public:
    static std::string DIR_SCENE_DATA;
    static std::string DIR_SPLINE_DATA;

    static void load(std::string prm_ini_filename);
    static void clean();
};

}
#endif /*STGPROPERTIES_H_*/


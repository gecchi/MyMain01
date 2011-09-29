#ifndef STGPROPERTIES_H_
#define STGPROPERTIES_H_

#ifdef CFG_PROPERTY
    #undef CFG_PROPERTY
#endif
#define CFG_PROPERTY(X) (GgafLib::StgProperties::X)

namespace GgafLib {

class StgProperties: public GgafDxCore::GgafDxProperties {
public:
    static std::string DIR_SCENE_DATA;
    static std::string DIR_SPLINE_DATA;

    static void load(std::string prm_ini_filename);
    static void clean();
};

}
#endif /*STGPROPERTIES_H_*/


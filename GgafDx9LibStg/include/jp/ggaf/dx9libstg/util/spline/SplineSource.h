#ifndef SPLINESOURCE_H_
#define SPLINESOURCE_H_
namespace GgafDx9LibStg {

/**
 * Spline�I�u�W�F�N�g�\�[�X .
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineSource : public GgafCore::GgafObject {

public:
    Spline3D* _pSp;
    double _accuracy;
    std::string _classname;

    SplineSource(char* prm_idstr);

    virtual ~SplineSource();
};

}
#endif /*SPLINESOURCE_H_*/

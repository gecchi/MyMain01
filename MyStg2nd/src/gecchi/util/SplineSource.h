#ifndef SPLINESOURCE_H_
#define SPLINESOURCE_H_
namespace MyStg2nd {

class SplineSource : public GgafCore::GgafObject {

public:
    GgafDx9Core::GgafDx9Spline3D* _pSp;
    double _accuracy;
    frame _spent_frame;
    angvelo _angveloRzRyMv;
    std::string _classname;

    SplineSource(char* prm_idstr);


    GgafDx9Core::GgafDx9SplineProgram* makeSplineProgram(GgafDx9Core::GgafDx9GeometricActor* prm_pActor);


    virtual ~SplineSource();
};

}
#endif /*SPLINESOURCE_H_*/

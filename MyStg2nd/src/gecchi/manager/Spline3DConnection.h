#ifndef SPLINE3DCONNECTION_H_
#define SPLINE3DCONNECTION_H_
namespace MyStg2nd {

/**
 * GgafDx9Spline3D資源コネクション.
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class Spline3DConnection : public GgafCore::GgafResourceConnection<GgafDx9Core::GgafDx9Spline3D> {

public:

    double _accuracy;
    frame _spent_frame;
    angvelo _angveloRzRyMv;
    std::string _classname;


    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pSpline3D GgafDx9Spline3Dオブジェクト
     */
    Spline3DConnection(char* prm_idstr, GgafDx9Core::GgafDx9Spline3D* prm_pSpline3D);

    void processReleaseResource(GgafDx9Core::GgafDx9Spline3D* prm_pResource);

    GgafDx9Core::GgafDx9SplineProgram* makeSplineProgram();

    virtual ~Spline3DConnection() {
    }
};

}
#endif /*SPLINE3DCONNECTION_H_*/

#ifndef SPLINELINECONNECTION_H_
#define SPLINELINECONNECTION_H_
namespace MyStg2nd {

/**
 * SplineLine資源コネクション.
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class SplineLineConnection : public GgafCore::GgafResourceConnection<GgafDx9LibStg::SplineLine> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pSpl3D SplineLineオブジェクト
     */
    SplineLineConnection(char* prm_idstr, GgafDx9LibStg::SplineLine* prm_pSpl3D);

    void processReleaseResource(GgafDx9LibStg::SplineLine* prm_pResource);

    virtual ~SplineLineConnection() {
    }
};

}
#endif /*SPLINE3DCONNECTION_H_*/

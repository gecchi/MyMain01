#ifndef SPLINEPROGRAMCONNECTION_H_
#define SPLINEPROGRAMCONNECTION_H_
namespace GgafDx9LibStg {

/**
 * SplineSource資源コネクション.
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineConnection : public GgafCore::GgafResourceConnection<SplineSource> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pSplineProgram SplineSourceオブジェクト
     */
    SplineConnection(char* prm_idstr, SplineSource* prm_pSplineProgram);

    void processReleaseResource(SplineSource* prm_pResource);

    virtual ~SplineConnection() {
    }
};

}
#endif /*SPLINEPROGRAMCONNECTION_H_*/

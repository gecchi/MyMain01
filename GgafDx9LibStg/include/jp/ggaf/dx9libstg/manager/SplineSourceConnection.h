#ifndef SPLINEPROGRAMCONNECTION_H_
#define SPLINEPROGRAMCONNECTION_H_
namespace GgafDx9LibStg {

/**
 * SplineSource資源コネクション.
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineSourceConnection : public GgafCore::GgafResourceConnection<SplineSource> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pSplSeqram SplineSourceオブジェクト
     */
    SplineSourceConnection(char* prm_idstr, SplineSource* prm_pSplSeqram);

    void processReleaseResource(SplineSource* prm_pResource);

    virtual ~SplineSourceConnection() {
    }
};

}
#endif /*SPLINEPROGRAMCONNECTION_H_*/

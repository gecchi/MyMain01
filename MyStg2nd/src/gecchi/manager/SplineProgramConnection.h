#ifndef SPLINEPROGRAMCONNECTION_H_
#define SPLINEPROGRAMCONNECTION_H_
namespace MyStg2nd {

/**
 * GgafDx9SplineProgram資源コネクション.
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class SplineProgramConnection : public GgafCore::GgafResourceConnection<GgafDx9Core::GgafDx9SplineProgram> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pSplineProgram GgafDx9SplineProgramオブジェクト
     */
    SplineProgramConnection(char* prm_idstr, GgafDx9Core::GgafDx9SplineProgram* prm_pSplineProgram);

    void processReleaseResource(GgafDx9Core::GgafDx9SplineProgram* prm_pResource);

    virtual ~SplineProgramConnection() {
    }
};

}
#endif /*SPLINEPROGRAMCONNECTION_H_*/

#ifndef DEFINITESPLINECONNECTION_H_
#define DEFINITESPLINECONNECTION_H_
namespace MyStg2nd {

/**
 * DefiniteSplineコネクション.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class DefiniteSplineConnection : public GgafCore::GgafResourceConnection<GgafDx9Core::GgafDx9Spline3D> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pDefiniteSpline ディスパッチャー
     */
    DefiniteSplineConnection(char* prm_idstr, GgafDx9Core::GgafDx9Spline3D* prm_pDefiniteSpline);

    void processReleaseResource(GgafDx9Core::GgafDx9Spline3D* prm_pResource);

    virtual ~DefiniteSplineConnection() {
    }
};

}
#endif /*DEFINITESPLINECONNECTION_H_*/

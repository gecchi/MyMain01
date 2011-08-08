#ifndef SPLINE3DCONNECTION_H_
#define SPLINE3DCONNECTION_H_
namespace MyStg2nd {

/**
 * Spline3D資源コネクション.
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class Spline3DConnection : public GgafCore::GgafResourceConnection<GgafDx9LibStg::Spline3D> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pSpl3D Spline3Dオブジェクト
     */
    Spline3DConnection(char* prm_idstr, GgafDx9LibStg::Spline3D* prm_pSpl3D);

    void processReleaseResource(GgafDx9LibStg::Spline3D* prm_pResource);

    virtual ~Spline3DConnection() {
    }
};

}
#endif /*SPLINE3DCONNECTION_H_*/

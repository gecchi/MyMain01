#ifndef SPLINEMANUFACTURECONNECTION_H_
#define SPLINEMANUFACTURECONNECTION_H_
namespace GgafLib {

/**
 * SplineManufacture資源コネクション.
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineManufactureConnection : public GgafCore::GgafResourceConnection<SplineManufacture> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pResource SplineManufactureオブジェクト
     */
    SplineManufactureConnection(char* prm_idstr, SplineManufacture* prm_pResource);

    void processReleaseResource(SplineManufacture* prm_pResource);

    virtual ~SplineManufactureConnection() {
    }
};

}
#endif /*SPLINEMANUFACTURECONNECTION_H_*/

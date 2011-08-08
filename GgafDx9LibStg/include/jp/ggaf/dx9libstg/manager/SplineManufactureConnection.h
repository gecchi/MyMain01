#ifndef SPLINEMANUFACTURECONNECTION_H_
#define SPLINEMANUFACTURECONNECTION_H_
namespace GgafDx9LibStg {

/**
 * SplineManufacture�����R�l�N�V����.
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineManufactureConnection : public GgafCore::GgafResourceConnection<SplineManufacture> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pSplProgram SplineManufacture�I�u�W�F�N�g
     */
    SplineManufactureConnection(char* prm_idstr, SplineManufacture* prm_pSplProgram);

    void processReleaseResource(SplineManufacture* prm_pResource);

    virtual ~SplineManufactureConnection() {
    }
};

}
#endif /*SPLINEMANUFACTURECONNECTION_H_*/

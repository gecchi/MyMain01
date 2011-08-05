#ifndef SPLINEPROGRAMCONNECTION_H_
#define SPLINEPROGRAMCONNECTION_H_
namespace GgafDx9LibStg {

/**
 * SplineSource�����R�l�N�V����.
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineSourceConnection : public GgafCore::GgafResourceConnection<SplineSource> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pSplineProgram SplineSource�I�u�W�F�N�g
     */
    SplineSourceConnection(char* prm_idstr, SplineSource* prm_pSplineProgram);

    void processReleaseResource(SplineSource* prm_pResource);

    virtual ~SplineSourceConnection() {
    }
};

}
#endif /*SPLINEPROGRAMCONNECTION_H_*/
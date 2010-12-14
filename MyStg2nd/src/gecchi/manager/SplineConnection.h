#ifndef SPLINEPROGRAMCONNECTION_H_
#define SPLINEPROGRAMCONNECTION_H_
namespace MyStg2nd {

/**
 * SplineSource�����R�l�N�V����.
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class SplineConnection : public GgafCore::GgafResourceConnection<SplineSource> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pSplineProgram SplineSource�I�u�W�F�N�g
     */
    SplineConnection(char* prm_idstr, SplineSource* prm_pSplineProgram);

    void processReleaseResource(SplineSource* prm_pResource);

    virtual ~SplineConnection() {
    }
};

}
#endif /*SPLINEPROGRAMCONNECTION_H_*/

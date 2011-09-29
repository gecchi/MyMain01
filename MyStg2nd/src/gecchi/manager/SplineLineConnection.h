#ifndef SPLINELINECONNECTION_H_
#define SPLINELINECONNECTION_H_
namespace MyStg2nd {

/**
 * SplineLine�����R�l�N�V����.
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class SplineLineConnection : public GgafCore::GgafResourceConnection<GgafLib::SplineLine> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pSpl3D SplineLine�I�u�W�F�N�g
     */
    SplineLineConnection(char* prm_idstr, GgafLib::SplineLine* prm_pSpl3D);

    void processReleaseResource(GgafLib::SplineLine* prm_pResource);

    virtual ~SplineLineConnection() {
    }
};

}
#endif /*SPLINE3DCONNECTION_H_*/

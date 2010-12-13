#ifndef SPLINEPROGRAMCONNECTION_H_
#define SPLINEPROGRAMCONNECTION_H_
namespace MyStg2nd {

/**
 * GgafDx9SplineProgram�����R�l�N�V����.
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class SplineProgramConnection : public GgafCore::GgafResourceConnection<GgafDx9Core::GgafDx9SplineProgram> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pSplineProgram GgafDx9SplineProgram�I�u�W�F�N�g
     */
    SplineProgramConnection(char* prm_idstr, GgafDx9Core::GgafDx9SplineProgram* prm_pSplineProgram);

    void processReleaseResource(GgafDx9Core::GgafDx9SplineProgram* prm_pResource);

    virtual ~SplineProgramConnection() {
    }
};

}
#endif /*SPLINEPROGRAMCONNECTION_H_*/

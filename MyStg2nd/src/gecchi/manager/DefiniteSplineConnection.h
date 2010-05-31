#ifndef DEFINITESPLINECONNECTION_H_
#define DEFINITESPLINECONNECTION_H_
namespace MyStg2nd {

/**
 * DefiniteSpline�R�l�N�V����.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class DefiniteSplineConnection : public GgafCore::GgafResourceConnection<GgafDx9Core::GgafDx9Spline3D> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pDefiniteSpline �f�B�X�p�b�`���[
     */
    DefiniteSplineConnection(char* prm_idstr, GgafDx9Core::GgafDx9Spline3D* prm_pDefiniteSpline);

    void processReleaseResource(GgafDx9Core::GgafDx9Spline3D* prm_pResource);

    virtual ~DefiniteSplineConnection() {
    }
};

}
#endif /*DEFINITESPLINECONNECTION_H_*/

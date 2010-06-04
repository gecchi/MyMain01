#ifndef DEFINITESPLINECONNECTION_H_
#define DEFINITESPLINECONNECTION_H_
namespace MyStg2nd {

/**
 * GgafDx9Spline3D�����R�l�N�V����.
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class Spline3DConnection : public GgafCore::GgafResourceConnection<GgafDx9Core::GgafDx9Spline3D> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pSpline3D GgafDx9Spline3D�I�u�W�F�N�g
     */
    Spline3DConnection(char* prm_idstr, GgafDx9Core::GgafDx9Spline3D* prm_pSpline3D);

    void processReleaseResource(GgafDx9Core::GgafDx9Spline3D* prm_pResource);

    virtual ~Spline3DConnection() {
    }
};

}
#endif /*DEFINITESPLINECONNECTION_H_*/
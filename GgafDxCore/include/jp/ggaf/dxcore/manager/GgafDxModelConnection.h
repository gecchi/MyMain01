#ifndef GGAFDXMODELCONNECTION_H_
#define GGAFDXMODELCONNECTION_H_
namespace GgafDxCore {

/**
 * ���f�������̃R�l�N�V����.
 * @version 1.00
 * @since 2009/02/01
 * @author Masatoshi Tsuge
 */
class GgafDxModelConnection : public GgafCore::GgafResourceConnection<GgafDxModel> {
public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���f�����ʖ�
     * @param prm_pModel ���\�[�X�ƂȂ郂�f��
     */
    GgafDxModelConnection(char* prm_idstr, GgafDxModel* prm_pModel);

    void processReleaseResource(GgafDxModel* prm_pResource);

    virtual ~GgafDxModelConnection() {
    }
};

}
#endif /*GGAFDXMODELCONNECTION_H_*/
#ifndef GGAFDXEFFECTCONNECTION_H_
#define GGAFDXEFFECTCONNECTION_H_
namespace GgafDxCore {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxEffectConnection : public GgafCore::GgafResourceConnection<GgafDxEffect> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr �G�t�F�N�g���ʖ�(���t�@�C����)
     * @param prm_pEffect �G�t�F�N�g
     */
    GgafDxEffectConnection(char* prm_idstr, GgafDxEffect* prm_pEffect);

    /**
     * �I�[�o�[���C�h
     */
    void processReleaseResource(GgafDxEffect* prm_pResource);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDxEffectConnection() {
    }
};

}
#endif /*GGAFDXEFFECTCONNECTION_H_*/

#ifndef GGAFDX9EFFECTCONNECTION_H_
#define GGAFDX9EFFECTCONNECTION_H_
namespace GgafDx9Core {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDx9EffectConnection : public GgafCore::GgafResourceConnection<GgafDx9Effect> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr �G�t�F�N�g���ʖ�(���t�@�C����)
     * @param prm_pEffect �G�t�F�N�g
     */
    GgafDx9EffectConnection(char* prm_idstr, GgafDx9Effect* prm_pEffect);

    /**
     * �I�[�o�[���C�h
     */
    void processReleaseResource(GgafDx9Effect* prm_pResource);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDx9EffectConnection() {
    }
};

}
#endif /*GGAFDX9EFFECTCONNECTION_H_*/

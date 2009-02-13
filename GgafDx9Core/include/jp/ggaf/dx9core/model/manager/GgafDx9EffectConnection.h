#ifndef GGAFDX9EFFECTCONNECTION_H_
#define GGAFDX9EFFECTCONNECTION_H_
namespace GgafDx9Core {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 */
class GgafDx9EffectConnection : public GgafCore::GgafResourceConnection<ID3DXEffect> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_texture_file_name �e�N�X�`�����ʖ�(���t�@�C����)
     * @param prm_pID3DXEffect �e�N�X�`��
     */
    GgafDx9EffectConnection(char* prm_idstr, ID3DXEffect* prm_pID3DXEffect);

    /**
     * �I�[�o�[���C�h
     */
    void processReleaseResource(ID3DXEffect* prm_pResource);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDx9EffectConnection() {
    }
};

}
#endif /*GGAFDX9EFFECTCONNECTION_H_*/

#ifndef GGAFDX9EFFECTLEAD_H_
#define GGAFDX9EFFECTLEAD_H_
namespace GgafDx9Core {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 */
class GgafDx9EffectLead : public GgafCore::GgafResourceLead<ID3DXEffect> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_texture_file_name �e�N�X�`�����ʖ�(���t�@�C����)
     * @param prm_pID3DXEffect �e�N�X�`��
     */
    GgafDx9EffectLead(char* prm_idstr, ID3DXEffect* prm_pID3DXEffect);

    /**
     * �I�[�o�[���C�h
     */
    void processReleaseResource(ID3DXEffect* prm_pResource);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDx9EffectLead() {
    }
};

}
#endif /*GGAFDX9EFFECTLEAD_H_*/

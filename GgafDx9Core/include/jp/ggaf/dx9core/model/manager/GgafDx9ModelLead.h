#ifndef GGAFDX9MODELLEAD_H_
#define GGAFDX9MODELLEAD_H_
namespace GgafDx9Core {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 */
class GgafDx9ModelLead : public GgafCore::GgafResourceLead<GgafDx9Model> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_texture_file_name �e�N�X�`�����ʖ�(���t�@�C����)
     * @param prm_pModel ���\�[�X�ƂȂ郂�f��
     */
    GgafDx9ModelLead(char* prm_idstr, GgafDx9Model* prm_pModel);

    void processReleaseResource(GgafDx9Model* prm_pResource);

    virtual ~GgafDx9ModelLead() {
    }
};

}
#endif /*GGAFDX9MODELLEAD_H_*/

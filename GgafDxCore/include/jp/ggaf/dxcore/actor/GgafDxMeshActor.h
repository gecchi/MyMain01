#ifndef GGAFDXMESHACTOR_H_
#define GGAFDXMESHACTOR_H_
namespace GgafDxCore {

/**
 * ���b�V���A�N�^�[.
 * GgafDxDrawableActor ���p�����A�Ǝ���X�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł��B<BR>
 * @version 1.00
 * @since 2009/02/26
 * @author Masatoshi Tsuge
 */
class GgafDxMeshActor : public GgafDxDrawableActor, public GgafDxIBumpMapActor {

public:
    /** [r]���f������ */
    GgafDxMeshModel* _pMeshModel;
    /** [r]�G�t�F�N�g���� */
    GgafDxMeshEffect* _pMeshEffect;

    float _far_rate;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name ���f�����́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���B������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� nullptr�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     */
    GgafDxMeshActor(const char* prm_name,
                    const char* prm_model_id,
                    const char* prm_effect_id,
                    const char* prm_technique,
                    GgafCore::GgafStatus* prm_pStat,
                    GgafDxChecker* prm_pChecker );

    /**
     * ���ʌp���p�R���X�g���N�^
     * @param prm_name �A�N�^�[���́i�C�Ӂj
     * @param prm_model_id ���f����`��
     * @param prm_model_type ���f���^�C�v
     * @param prm_effect_id �G�t�F�N�g��`��
     * @param prm_effect_type �G�t�F�N�g�^�C�v
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� nullptr�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    GgafDxMeshActor(const char* prm_name,
                    const char* prm_model_id,
                    const char* prm_model_type,
                    const char* prm_effect_id,
                    const char* prm_effect_type,
                    const char* prm_technique,
                    GgafCore::GgafStatus* prm_pStat,
                    GgafDxChecker* prm_pChecker);

    virtual void processDraw() override;

    /**
     * �����̍��W�ł������\�� .
     * @param prm_b
     */
    void drawAnyFar(bool prm_b) {
        if (prm_b) {
            _far_rate = 0.999f;
        } else {
            _far_rate = -1.0f;
        }
    }

    /**
     * ���ݒ�.
     * @param prm_alpha
     */
    virtual void setAlpha(float prm_alpha) override;

    /**
     * �����Z .
     * @param prm_alpha
     */
    virtual void addAlpha(float prm_alpha) override;

    void effectBumpMapping(const char* prm_cubemap_tex, frame prm_frame = MAX_FRAME);

    virtual ~GgafDxMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXMESHACTOR_H_*/

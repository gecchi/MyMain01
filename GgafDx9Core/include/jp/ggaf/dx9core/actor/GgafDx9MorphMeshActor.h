#ifndef GGAFDX9MORPHMESHACTOR_H_
#define GGAFDX9MORPHMESHACTOR_H_
namespace GgafDx9Core {

/**
 * ���[�t���b�V���A�N�^�[.
 * GgafDx9DrawableActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\�y��<BR>
 * ���[�t�A�j���[�V�����@�\��������A�N�^�[<BR>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class GgafDx9MorphMeshActor : public GgafDx9DrawableActor {
private:

public:
    /** ���f������ */
    GgafDx9MorphMeshModel* _pMorphMeshModel;
    /** �G�t�F�N�g���� */
    GgafDx9MorphMeshEffect* _pMorphMeshEffect;
    /** ���[�t�^�[�Q�b�g�̏d��(0.0 �` 1.0) */
    float _weight[MAX_MORPH_TARGET+1]; //[0]�͖��g�p�A[1]�`[6]�����[�t�^�[�Q�b�g1�`6�̏d��

    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     * @return
     */
    GgafDx9MorphMeshActor(const char* prm_name,
                          const char* prm_model_id,
                          const char* prm_effect_id,
                          const char* prm_technique,
                          GgafDx9Checker* prm_pChecker );

    /**
     * ���ʌp���p�R���X�g���N�^
     * @param prm_name �A�N�^�[���́i�C�Ӂj
     * @param prm_model_id ���f����`��
     * @param prm_model_type ���f���^�C�v
     * @param prm_effect_id �G�t�F�N�g��`��
     * @param prm_effect_type �G�t�F�N�g�^�C�v
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     * @return
     */
    GgafDx9MorphMeshActor(const char* prm_name,
                          const char* prm_model_id,
                          const char* prm_model_type,
                          const char* prm_effect_id,
                          const char* prm_effect_type,
                          const char* prm_technique,
                          GgafDx9Checker* prm_pChecker);

    virtual void processDraw() override;

    /**
     * ���[�t�^�[�Q�b�g���b�V�����擾
     * @return ���[�t�^�[�Q�b�g���b�V����
     */
    int getMorphTergetNum();

    /**
     * ���ݒ�.
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha) override;

    /**
     * �����Z .
     * @param prm_fAlpha
     */
    void addAlpha(float prm_fAlpha) override;


    virtual ~GgafDx9MorphMeshActor (); //�f�X�g���N�^
};

}
#endif /*GGAFDX9MORPHMESHACTOR_H_*/

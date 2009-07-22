#ifndef GGAFDX9MORPHMESHACTOR_H_
#define GGAFDX9MORPHMESHACTOR_H_
namespace GgafDx9Core {

/**
 * ���[�t���b�V���A�N�^�[.
 * GgafDx9DrawableActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\�y��<BR>
 * ���[�t�A�j���[�V�����@�\��������A�N�^�[<BR>
 */
class GgafDx9MorphMeshActor : public GgafDx9DrawableActor {
private:

public:
    /** ���f������ */
    GgafDx9MorphMeshModel* _pMorphMeshModel;
    /** �G�t�F�N�g���� */
    GgafDx9MorphMeshEffect* _pMorphMeshEffect;
    /** ���[�t�^�[�Q�b�g�̏d��(0.0 �` 1.0) */
    float _weight[10]; //[0]�͖��g�p�A[1]�`[9]�����[�t�^�[�Q�b�g1�`9�̏d��

    /**
     * �R���X�g���N�^
     * @param prm_name  ���f�����́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model ���f����`���BGgafDx9MorphMeshModel �̐����Q�ƁB
     * @param prm_technique �G�t�F�N�g(GgafDx9MeshEffect.fx) �̃e�N�j�b�N�B
     * @param prm_pChecker   �l�X�Ȕ�����s�Ȃ��`�F�b�J�[�N���X�̃C���X�^���X��n��
     */
    GgafDx9MorphMeshActor(const char* prm_name,
                          const char* prm_model_id,
                          const char* prm_effect_id,
                          const char* prm_technique,
                          GgafDx9Checker* prm_pChecker );

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processDrawMain();

    /**
     * ���[�t�^�[�Q�b�g���b�V�����擾
     * @return ���[�t�^�[�Q�b�g���b�V����
     */
    int getMorphTergetNum();

    /**
     * ���ݒ�.
     * ���I�[�o�[���C�g��
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha);

    virtual ~GgafDx9MorphMeshActor (); //�f�X�g���N�^
};

}
#endif /*GGAFDX9MORPHMESHACTOR_H_*/

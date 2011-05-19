#ifndef GGAFDX9CUBEMAPMORPHMESHACTOR_H_
#define GGAFDX9CUBEMAPMORPHMESHACTOR_H_
namespace GgafDx9Core {

/**
 * ���}�b�v���[�t���b�V���A�N�^�[.
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMorphMeshActor : public GgafDx9MorphMeshActor {
private:

public:
    /** ���f������ */
    GgafDx9CubeMapMorphMeshModel* _pCubeMapMorphMeshModel;
    /** �G�t�F�N�g���� */
    GgafDx9CubeMapMorphMeshEffect* _pCubeMapMorphMeshEffect;

    /** ���}�b�v�e�N�X�`������ */
    GgafDx9TextureConnection* _pCubeMapTextureCon;

    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     * @return
     */
    GgafDx9CubeMapMorphMeshActor(const char* prm_name,
                          const char* prm_model_id,
                          const char* prm_effect_id,
                          const char* prm_technique,
                          GgafDx9Checker* prm_pChecker );

    void setCubeMapTexture(const char* prm_cubemap_tex);

    virtual void processDraw() override;

    virtual ~GgafDx9CubeMapMorphMeshActor (); //�f�X�g���N�^
};

}
#endif /*GGAFDX9CUBEMAPMORPHMESHACTOR_H_*/

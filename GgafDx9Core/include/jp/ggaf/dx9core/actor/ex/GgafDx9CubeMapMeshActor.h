#ifndef GGAFDX9CUBEMAPMESHACTOR_H_
#define GGAFDX9CUBEMAPMESHACTOR_H_
namespace GgafDx9Core {

/**
 * ���}�b�v���b�V���A�N�^�[.
 * GgafDx9MeshActor ���p�����A���}�b�v�e�N�X�`�������������A�N�^�[�ł��B<BR>
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMeshActor : public GgafDx9MeshActor {

public:

    /** ���f������ */
    GgafDx9CubeMapMeshModel* _pCubeMapMeshModel;
    /** �G�t�F�N�g���� */
    GgafDx9CubeMapMeshEffect* _pCubeMapMeshEffect;

    /** ���}�b�v�e�N�X�`������ */
    GgafDx9TextureConnection* _pCubeMapTextureCon;
    /** ���}�b�v�e�N�X�`�� */
    IDirect3DBaseTexture9* _pCubeMapTexture;
    /** ���}�b�v�e�N�X�`���f�肱�ݗ� */
    float _reflectance;
    /**
     * �R���X�g���N�^
     * @param prm_name ���f�����́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���B������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     */
    GgafDx9CubeMapMeshActor(const char* prm_name,
                       const char* prm_model_id,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       GgafDx9Checker* prm_pChecker );

    /**
     * ���}�b�s���O����e�N�X�`�����w�肷��B
     * @param prm_cubemap_tex �e�N�X�`���t�@�C����
     * @param prm_reflectance ���}�b�v�e�N�X�`���̉f�荞�݋(0.0�`1.0)�B
     *                        prm_cubemap_tex�̐F�Ɉ����̗����悶���A���n�̃}�e���A���F�ɉ��Z����܂��B
     *                        0.0:�f�荞�ݖ����A0.3:�嗝�΂��炢�A1.0:����
     */
    void setCubeMapTexture(const char* prm_cubemap_tex, float prm_reflectance);

    virtual void processDraw() override;

    virtual ~GgafDx9CubeMapMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9CUBEMAPMESHACTOR_H_*/

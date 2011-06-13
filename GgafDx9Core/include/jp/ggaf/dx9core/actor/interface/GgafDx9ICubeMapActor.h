#ifndef GGAFDX9ICUBEMAPACTOR_H_
#define GGAFDX9ICUBEMAPACTOR_H_
namespace GgafDx9Core {

/**
 * �L���[�u���}�b�v�I�u�W�F�N�g�p�C���^�[�t�F�C�X�B
 * @version 1.00
 * @since 2011/05/27
 * @author Masatoshi Tsuge
 */
class GgafDx9ICubeMapActor {

public:
    /** ���}�b�v�e�N�X�`������ */
    GgafDx9TextureConnection* _pCubeMapTextureCon;
    /** ���}�b�v�e�N�X�`�� */
    IDirect3DBaseTexture9* _pCubeMapTexture;
    /** ���}�b�v�e�N�X�`���f�肱�ݗ� */
    float _reflectance;

    GgafDx9ICubeMapActor();

    /**
     * ���}�b�s���O����e�N�X�`�����w�肷��B
     * @param prm_cubemap_tex �e�N�X�`���t�@�C����
     * @param prm_reflectance ���}�b�v�e�N�X�`���̉f�荞�݋(0.0�`1.0)�B
     *                        prm_cubemap_tex�̐F�Ɉ����̗����悶���A���n�̃}�e���A���F�ɉ��Z����܂��B
     *                        0.0:�f�荞�ݖ����A0.3:�嗝�΂��炢�A1.0:����
     */
    void setCubeMapTexture(const char* prm_cubemap_tex, float prm_reflectance = 1.0);

    IDirect3DBaseTexture9* getCubeMapTexture();

    float getCubeMapReflectance() {
        return _reflectance;
    }

    virtual ~GgafDx9ICubeMapActor(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9ICUBEMAPACTOR_H_*/
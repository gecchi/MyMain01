#ifndef GGAFDXIBUMPMAPACTOR_H_
#define GGAFDXIBUMPMAPACTOR_H_
namespace GgafDxCore {

/**
 * �o���v�}�b�v�I�u�W�F�N�g�p�C���^�[�t�F�C�X�B
 * @version 1.00
 * @since 2012/07/06
 * @author Masatoshi Tsuge
 */
class GgafDxIBumpMapActor {

public:
    /** ���}�b�v�e�N�X�`������ */
    GgafDxTextureConnection* _pBumpMapTextureCon;

    const char* _cubemap_tex;

    GgafDxIBumpMapActor();


    /**
     * ���}�b�s���O����e�N�X�`���Ɖf�荞�݋���w�肷��B .
     * �R���X�g���N�^�ȊO�Ŏ��s����ƁA�e�N�X�`���r���̊֌W�ŏ������x���ł��B
     * @param prm_cubemap_tex �e�N�X�`���t�@�C����
     * @param prm_reflectance ���}�b�v�e�N�X�`���̉f�荞�݋(0.0�`1.0)�B
     *                        prm_cubemap_tex�̐F�Ɉ����̗����悶���A���n�̃}�e���A���F�ɉ��Z����܂��B
     *                        0.0:�f�荞�ݖ����A0.3:�嗝�΂��炢�A1.0:����
     */
//    void setBumpMap(const char* prm_cubemap_tex, float prm_reflectance);

    /**
     * ���}�b�s���O����e�N�X�`�����w�肷��B .
     * �R���X�g���N�^�ȊO�Ŏ��s����ƁA�e�N�X�`���r���̊֌W�ŏ������x���ł��B
     * @param prm_cubemap_tex ���}�b�b�v�e�N�X�`���t�@�C����
     */
    void setBumpMapTexture(const char* prm_cubemap_tex);

    /**
     * ���}�b�v�̉f�荞�݋ .
     * @param prm_reflectance ���}�b�v�e�N�X�`���̉f�荞�݋(0.0�`1.0)�B
     *                        prm_cubemap_tex�̐F�Ɉ����̗����悶���A���n�̃}�e���A���F�ɉ��Z����܂��B
     *                        0.0:�f�荞�ݖ����A0.3:�嗝�΂��炢�A1.0:����
     */
//    void setBumpMapReflectance(float prm_reflectance);

    IDirect3DBaseTexture9* getBumpMapTexture();

//    float getBumpMapReflectance() {
//        return _reflectance;
//    }

//    void releaseBumpMapTex();
//
//    void restoreBumpMapTex();

    virtual ~GgafDxIBumpMapActor(); //�f�X�g���N�^

};

}
#endif /*GGAFDXICUBEMAPACTOR_H_*/
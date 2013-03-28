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
    GgafDxTextureConnection* _pBumpMapTextureConnection;

    const char* _bumpmap_tex;

public:
    GgafDxIBumpMapActor();

    /**
     * �o���v�}�b�s���O����e�N�X�`�����w�肷��B .
     * �R���X�g���N�^�ȊO�Ŏ��s����ƁA�e�N�X�`���r���̊֌W�ŏ������x���ł��B
     * @param prm_cubemap_tex ���}�b�b�v�e�N�X�`���t�@�C����
     */
    void setBumpMapTexture(const char* prm_bumpmap_tex);


    IDirect3DBaseTexture9* getBumpMapTexture();

    virtual ~GgafDxIBumpMapActor();

};

}
#endif /*GGAFDXICUBEMAPACTOR_H_*/

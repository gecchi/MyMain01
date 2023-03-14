#ifndef GGAF_DX_IBUMPMAPACTOR_H_
#define GGAF_DX_IBUMPMAPACTOR_H_
#include "GgafDxCommonHeader.h"

#include <d3d9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

namespace GgafDx {

/**
 * �o���v�}�b�v�I�u�W�F�N�g�p�C���^�[�t�F�C�X�B
 * @version 1.00
 * @since 2012/07/06
 * @author Masatoshi Tsuge
 */
class IBumpMapActor {

public:
    /** ���}�b�v�e�N�X�`������ */
    TextureConnection* _pBumpMapTextureConnection;

    char* _bumpmap_tex;

public:
    IBumpMapActor();

    /**
     * �o���v�}�b�s���O����e�N�X�`�����w�肷��B .
     * �R���X�g���N�^�ȊO�Ŏ��s����ƁA�e�N�X�`���r���̊֌W�ŏ������x���ł��B
     * @param prm_cubemap_tex ���}�b�b�v�e�N�X�`���t�@�C����
     */
    void setBumpMapTexture(const char* prm_bumpmap_tex);


    IDirect3DBaseTexture9* getBumpMapTexture();

    virtual ~IBumpMapActor();

};

}
#endif /*GGAF_DX_ICUBEMAPACTOR_H_*/

#ifndef GGAF_DX_ICUBEMAPACTOR_H_
#define GGAF_DX_ICUBEMAPACTOR_H_
#include "GgafDxCommonHeader.h"

#include <d3d9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

namespace GgafDx {

/**
 * �L���[�u���}�b�v�I�u�W�F�N�g�p�C���^�[�t�F�C�X�B
 * @version 1.00
 * @since 2011/05/27
 * @author Masatoshi Tsuge
 */
class ICubeMapActor {

public:
    /** ���}�b�v�e�N�X�`������ */
    TextureConnection* _pCubeMapTextureConnection;
    /** ���}�b�v�e�N�X�`���f�肱�ݗ� */
    float _reflectance;

    const char* _cubemap_tex;

public:
    ICubeMapActor();

    /**
     * ���}�b�s���O����e�N�X�`���Ɖf�荞�݋���w�肷��B .
     * �R���X�g���N�^�ȊO�Ŏ��s����ƁA�e�N�X�`���r���̊֌W�ŏ������x���ł��B
     * @param prm_cubemap_tex �e�N�X�`���t�@�C����
     * @param prm_reflectance ���}�b�v�e�N�X�`���̉f�荞�݋(0.0�`1.0)�B
     *                        prm_cubemap_tex�̐F�Ɉ����̗����悶���A���n�̃}�e���A���F�ɉ��Z����܂��B
     *                        0.0:�f�荞�ݖ����A0.3:�嗝�΂��炢�A1.0:����
     */
    void setCubeMap(const char* prm_cubemap_tex, float prm_reflectance);

    /**
     * ���}�b�s���O����e�N�X�`�����w�肷��B .
     * �R���X�g���N�^�ȊO�Ŏ��s����ƁA�e�N�X�`���r���̊֌W�ŏ������x���ł��B
     * @param prm_cubemap_tex ���}�b�b�v�e�N�X�`���t�@�C����
     */
    void setCubeMapTexture(const char* prm_cubemap_tex);

    /**
     * ���}�b�v�̉f�荞�݋ .
     * @param prm_reflectance ���}�b�v�e�N�X�`���̉f�荞�݋(0.0�`1.0)�B
     *                        prm_cubemap_tex�̐F�Ɉ����̗����悶���A���n�̃}�e���A���F�ɉ��Z����܂��B
     *                        0.0:�f�荞�ݖ����A0.3:�嗝�΂��炢�A1.0:����
     */
    void setCubeMapReflectance(float prm_reflectance);

    IDirect3DBaseTexture9* getCubeMapTexture();

    float getCubeMapReflectance() {
        return _reflectance;
    }

    virtual ~ICubeMapActor(); //�f�X�g���N�^

};

}
#endif /*GGAF_DX_ICUBEMAPACTOR_H_*/
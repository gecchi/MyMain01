#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxICubeMapActor::GgafDxICubeMapActor()  {
    _pCubeMapTextureCon = NULL;
    _reflectance = 0.0f;
    _cubemap_tex = "alpha_zero_cubemap.dds";
}

void GgafDxICubeMapActor::setCubeMap(const char* prm_cubemap_tex, float prm_reflectance) {
    setCubeMapTexture(prm_cubemap_tex);
    setCubeMapReflectance(prm_reflectance);
}

void GgafDxICubeMapActor::setCubeMapTexture(const char* prm_cubemap_tex) {
    _cubemap_tex = prm_cubemap_tex;
    if (_pCubeMapTextureCon) {
        _pCubeMapTextureCon->close();
    }
    _pCubeMapTextureCon = (GgafDxTextureConnection*)(GgafDxGod::_pCubeMapTextureManager->connect(prm_cubemap_tex));
//    _pCubeMapTexture = _pCubeMapTextureCon->fetch()->_pIDirect3DBaseTexture9;
}
void GgafDxICubeMapActor::setCubeMapReflectance(float prm_reflectance) {
    _reflectance = prm_reflectance;
}

IDirect3DBaseTexture9* GgafDxICubeMapActor::getCubeMapTexture() {
    if (!_pCubeMapTextureCon) {
        _pCubeMapTextureCon = (GgafDxTextureConnection*)(GgafDxGod::_pCubeMapTextureManager->connect("alpha_zero_cubemap.dds"));
    }
    return _pCubeMapTextureCon->fetch()->_pIDirect3DBaseTexture9;;
//    } else {
//        _pCubeMapTexture = _pCubeMapTextureCon->fetch()->_pIDirect3DBaseTexture9;
//        return _pCubeMapTexture;
//    }
}

//void GgafDxICubeMapActor::releaseCubeMapTex() {
//    //�e�N�X�`�������
//    _TRACE_("�f�o�C�X���X�g�L���[�u�}�b�v��� GgafDxICubeMapActor::releaseCubeMapTex() begin "<<_pCubeMapTextureCon->getIdStr()<<"<-"<<_pCubeMapTextureCon->getNumConnection()<<"connection");
//    if (_pCubeMapTextureCon) {
//        _TRACE_("�f�o�C�X���X�g�L���[�u�}�b�v��� GgafDxICubeMapActor::releaseCubeMapTex()->close() !");
//        _pCubeMapTextureCon->close();
//    }
//    //_TRACE_("�f�o�C�X���X�g�L���[�u�}�b�v��� GgafDxICubeMapActor::releaseCubeMapTex() end "<<_pCubeMapTextureCon->getIdStr()<<"<-"<<_pCubeMapTextureCon->getNumConnection()<<"connection");
//    _pCubeMapTextureCon = NULL;
//    _pCubeMapTexture = NULL;
//}
//
//void GgafDxICubeMapActor::restoreCubeMapTex() {
//    _pCubeMapTextureCon = (GgafDxTextureConnection*)(GgafDxGod::_pCubeMapTextureManager->connect(_cubemap_tex));
//    _pCubeMapTexture = _pCubeMapTextureCon->fetch()->_pIDirect3DBaseTexture9;
//}


GgafDxICubeMapActor::~GgafDxICubeMapActor() {

    //�����擾�� connet() �̓��C���X���b�h�ł���B
    //������ close() �i�f�X�g���N�^�j�͍H��X���b�h�Ŏ��s�B
    //�{���͔�����ׂ������AGgafResourceConnection����close()�����ǂ��A
    //�ʃX���b�h�����close()�ɂ��Ή������BTODO:�v�e�X�g
    if (_pCubeMapTextureCon) {
        _pCubeMapTextureCon->close();
    }
}

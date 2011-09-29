#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxICubeMapActor::GgafDxICubeMapActor()  {
    _pCubeMapTextureCon = NULL;
    //_pCubeMapTexture = NULL;
    _reflectance = 0.5f;
    _cubemap_tex = "uffizi_cross_cubemap.dds";
}

void GgafDxICubeMapActor::setCubeMapTexture(const char* prm_cubemap_tex, float prm_reflectance) {
    _reflectance = prm_reflectance;
    _cubemap_tex = prm_cubemap_tex;
    if (_pCubeMapTextureCon) {
        _pCubeMapTextureCon->close();
    }
    _pCubeMapTextureCon = (GgafDxTextureConnection*)(GgafDxGod::_pCubeMapTextureManager->connect(prm_cubemap_tex));
//    _pCubeMapTexture = _pCubeMapTextureCon->use()->_pIDirect3DBaseTexture9;
}


IDirect3DBaseTexture9* GgafDxICubeMapActor::getCubeMapTexture() {
    if (!_pCubeMapTextureCon) {
        _pCubeMapTextureCon = (GgafDxTextureConnection*)(GgafDxGod::_pCubeMapTextureManager->connect("uffizi_cross_cubemap.dds"));
    }
    return _pCubeMapTextureCon->use()->_pIDirect3DBaseTexture9;;
//    } else {
//        _pCubeMapTexture = _pCubeMapTextureCon->use()->_pIDirect3DBaseTexture9;
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
//    _pCubeMapTexture = _pCubeMapTextureCon->use()->_pIDirect3DBaseTexture9;
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

#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxIBumpMapActor::GgafDxIBumpMapActor()  {
    _pBumpMapTextureCon = nullptr;
    _cubemap_tex = "alpha_zero_cubemap.dds";
}

//void GgafDxIBumpMapActor::setBumpMap(const char* prm_cubemap_tex, float prm_reflectance) {
//    setBumpMapTexture(prm_cubemap_tex);
//    setBumpMapReflectance(prm_reflectance);
//}

void GgafDxIBumpMapActor::setBumpMapTexture(const char* prm_cubemap_tex) {
    _cubemap_tex = prm_cubemap_tex;
    if (_pBumpMapTextureCon) {
        _pBumpMapTextureCon->close();
    }
    _pBumpMapTextureCon = (GgafDxTextureConnection*)(GgafDxGod::_pBumpMapTextureManager->connect(prm_cubemap_tex));
}
//void GgafDxIBumpMapActor::setBumpMapReflectance(float prm_reflectance) {
//    _reflectance = prm_reflectance;
//}

IDirect3DBaseTexture9* GgafDxIBumpMapActor::getBumpMapTexture() {
    if (!_pBumpMapTextureCon) {
        _pBumpMapTextureCon = (GgafDxTextureConnection*)(GgafDxGod::_pBumpMapTextureManager->connect("alpha_zero_cubemap.dds"));
    }
    return _pBumpMapTextureCon->fetch()->_pIDirect3DBaseTexture9;;
}

GgafDxIBumpMapActor::~GgafDxIBumpMapActor() {

    //�����擾�� connet() �̓��C���X���b�h�ł���B
    //������ close() �i�f�X�g���N�^�j�͍H��X���b�h�Ŏ��s�B
    //�{���͔�����ׂ������AGgafResourceConnection����close()�����ǂ��A
    //�ʃX���b�h�����close()�ɂ��Ή������BTODO:�v�e�X�g
    if (_pBumpMapTextureCon) {
        _pBumpMapTextureCon->close();
    }
}

#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxIBumpMapActor::GgafDxIBumpMapActor()  {
    _pBumpMapTextureCon = nullptr;
    _bumpmap_tex = "alpha_zero_cubemap.dds";
}

void GgafDxIBumpMapActor::setBumpMapTexture(const char* prm_bumpmap_tex) {
    _bumpmap_tex = prm_bumpmap_tex;
    if (_pBumpMapTextureCon) {
        _pBumpMapTextureCon->close();
    }
    _pBumpMapTextureCon = (GgafDxTextureConnection*)(GgafDxGod::_pBumpMapTextureManager->connect(_bumpmap_tex));
}

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

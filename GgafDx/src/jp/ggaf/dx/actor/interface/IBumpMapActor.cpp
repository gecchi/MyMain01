#include "jp/ggaf/dx/actor/interface/IBumpMapActor.h"

#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/God.h"

using namespace GgafDx;

IBumpMapActor::IBumpMapActor()  {
    _pBumpMapTextureConnection = nullptr;
    _bumpmap_tex = "alpha_zero_cubemap.dds";
}

void IBumpMapActor::setBumpMapTexture(const char* prm_bumpmap_tex) {
    _bumpmap_tex = prm_bumpmap_tex;
    if (_pBumpMapTextureConnection) {
        _pBumpMapTextureConnection->close();
    }
    _pBumpMapTextureConnection = (TextureConnection*)(pGOD->_pBumpMapTextureManager->connect(_bumpmap_tex,this));
}

IDirect3DBaseTexture9* IBumpMapActor::getBumpMapTexture() {
    if (!_pBumpMapTextureConnection) {
        _pBumpMapTextureConnection = (TextureConnection*)(pGOD->_pBumpMapTextureManager->connect("alpha_zero_cubemap.dds",this));
    }
    return _pBumpMapTextureConnection->peek()->_pIDirect3DBaseTexture9;
}

IBumpMapActor::~IBumpMapActor() {
    //�����擾�� connet() �̓��C���X���b�h�ł���B
    //������ close() �i�f�X�g���N�^�j�͈��X���b�h�Ŏ��s�B
    //�{���͔�����ׂ������AGgafCore::ResourceConnection����close()�����ǂ��A
    //�ʃX���b�h�����close()�ɂ��Ή������BTODO:�v�e�X�g
    if (_pBumpMapTextureConnection) {
        _pBumpMapTextureConnection->close();
    }
}

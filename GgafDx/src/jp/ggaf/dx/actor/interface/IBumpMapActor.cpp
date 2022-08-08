#include "jp/ggaf/dx/actor/interface/IBumpMapActor.h"

#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/Caretaker.h"

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
    _pBumpMapTextureConnection = (TextureConnection*)(pCARETAKER->_pBumpMapTextureManager->connect(_bumpmap_tex,this));
}

IDirect3DBaseTexture9* IBumpMapActor::getBumpMapTexture() {
    if (!_pBumpMapTextureConnection) {
        _pBumpMapTextureConnection = (TextureConnection*)(pCARETAKER->_pBumpMapTextureManager->connect("alpha_zero_cubemap.dds",this));
    }
    return _pBumpMapTextureConnection->peek()->_pIDirect3DBaseTexture9;
}

IBumpMapActor::~IBumpMapActor() {
    //資源取得の connet() はメインスレッドである。
    //しかし close() （デストラクタ）は愛スレッドで実行。
    //本当は避けるべきだが、GgafCore::ResourceConnection側のclose()を改良し、
    //別スレッドからのclose()にも対応した。TODO:要テスト
    if (_pBumpMapTextureConnection) {
        _pBumpMapTextureConnection->close();
    }
}

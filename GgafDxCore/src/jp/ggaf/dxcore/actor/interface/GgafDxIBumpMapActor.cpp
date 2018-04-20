#include "jp/ggaf/dxcore/actor/interface/GgafDxIBumpMapActor.h"

#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"

using namespace GgafDxCore;

GgafDxIBumpMapActor::GgafDxIBumpMapActor()  {
    _pBumpMapTextureConnection = nullptr;
    _bumpmap_tex = "alpha_zero_cubemap.dds";
}

void GgafDxIBumpMapActor::setBumpMapTexture(const char* prm_bumpmap_tex) {
    _bumpmap_tex = prm_bumpmap_tex;
    if (_pBumpMapTextureConnection) {
        _pBumpMapTextureConnection->close();
    }
    _pBumpMapTextureConnection = (GgafDxTextureConnection*)(GgafDxGod::_pBumpMapTextureManager->connect(_bumpmap_tex,this));
}

IDirect3DBaseTexture9* GgafDxIBumpMapActor::getBumpMapTexture() {
    if (!_pBumpMapTextureConnection) {
        _pBumpMapTextureConnection = (GgafDxTextureConnection*)(GgafDxGod::_pBumpMapTextureManager->connect("alpha_zero_cubemap.dds",this));
    }
    return _pBumpMapTextureConnection->peek()->_pIDirect3DBaseTexture9;
}

GgafDxIBumpMapActor::~GgafDxIBumpMapActor() {
    //資源取得の connet() はメインスレッドである。
    //しかし close() （デストラクタ）は愛スレッドで実行。
    //本当は避けるべきだが、GgafResourceConnection側のclose()を改良し、
    //別スレッドからのclose()にも対応した。TODO:要テスト
    if (_pBumpMapTextureConnection) {
        _pBumpMapTextureConnection->close();
    }
}

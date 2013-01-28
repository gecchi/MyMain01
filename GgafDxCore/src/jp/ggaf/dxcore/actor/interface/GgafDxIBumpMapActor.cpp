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
    //資源取得の connet() はメインスレッドである。
    //しかし close() （デストラクタ）は工場スレッドで実行。
    //本当は避けるべきだが、GgafResourceConnection側のclose()を改良し、
    //別スレッドからのclose()にも対応した。TODO:要テスト
    if (_pBumpMapTextureCon) {
        _pBumpMapTextureCon->close();
    }
}

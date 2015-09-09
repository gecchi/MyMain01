#include "jp/ggaf/dxcore/actor/interface/GgafDxICubeMapActor.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxICubeMapActor::GgafDxICubeMapActor() {
    _pCubeMapTextureConnection = nullptr;
    _reflectance = 0.0f;
    _cubemap_tex = "alpha_zero_cubemap.dds";
}

void GgafDxICubeMapActor::setCubeMap(const char* prm_cubemap_tex, float prm_reflectance) {
    setCubeMapTexture(prm_cubemap_tex);
    setCubeMapReflectance(prm_reflectance);
}

void GgafDxICubeMapActor::setCubeMapTexture(const char* prm_cubemap_tex) {
    _cubemap_tex = prm_cubemap_tex;
    if (_pCubeMapTextureConnection) {
        _pCubeMapTextureConnection->close();
    }
    _pCubeMapTextureConnection = (GgafDxTextureConnection*)(GgafDxGod::_pCubeMapTextureManager->connect(prm_cubemap_tex,this));
}
void GgafDxICubeMapActor::setCubeMapReflectance(float prm_reflectance) {
    _reflectance = prm_reflectance;
}

IDirect3DBaseTexture9* GgafDxICubeMapActor::getCubeMapTexture() {
    if (!_pCubeMapTextureConnection) {
        _pCubeMapTextureConnection = (GgafDxTextureConnection*)(GgafDxGod::_pCubeMapTextureManager->connect("alpha_zero_cubemap.dds",this));
    }
    return _pCubeMapTextureConnection->peek()->_pIDirect3DBaseTexture9;
}

GgafDxICubeMapActor::~GgafDxICubeMapActor() {
    //資源取得の connet() はメインスレッドである。
    //しかし close() （デストラクタ）は工場スレッドで実行。
    //本当は避けるべきだが、GgafResourceConnection側のclose()を改良し、
    //別スレッドからのclose()にも対応した。TODO:要テスト
    if (_pCubeMapTextureConnection) {
        _pCubeMapTextureConnection->close();
    }
}

#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxICubeMapActor::GgafDxICubeMapActor()  {
    _pCubeMapTextureCon = nullptr;
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
}
void GgafDxICubeMapActor::setCubeMapReflectance(float prm_reflectance) {
    _reflectance = prm_reflectance;
}

IDirect3DBaseTexture9* GgafDxICubeMapActor::getCubeMapTexture() {
    if (!_pCubeMapTextureCon) {
        _pCubeMapTextureCon = (GgafDxTextureConnection*)(GgafDxGod::_pCubeMapTextureManager->connect("alpha_zero_cubemap.dds"));
    }
    return _pCubeMapTextureCon->fetch()->_pIDirect3DBaseTexture9;;
}

GgafDxICubeMapActor::~GgafDxICubeMapActor() {

    //資源取得の connet() はメインスレッドである。
    //しかし close() （デストラクタ）は工場スレッドで実行。
    //本当は避けるべきだが、GgafResourceConnection側のclose()を改良し、
    //別スレッドからのclose()にも対応した。TODO:要テスト
    if (_pCubeMapTextureCon) {
        _pCubeMapTextureCon->close();
    }
}

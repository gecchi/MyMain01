#include "jp/ggaf/dx/actor/interface/ICubeMapActor.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"


using namespace GgafDx;

ICubeMapActor::ICubeMapActor() {
    _pCubeMapTextureConnection = nullptr;
    _reflectance = 0.0f;
    _cubemap_tex = NEW char[2];
    strcpy(_cubemap_tex, "?");
}

void ICubeMapActor::setCubeMap(const char* prm_cubemap_tex, float prm_reflectance) {
    setCubeMapTexture(prm_cubemap_tex);
    setCubeMapReflectance(prm_reflectance);
}

void ICubeMapActor::setCubeMapTexture(const char* prm_cubemap_tex) {
    int len = (int)strlen(prm_cubemap_tex);
    GGAF_DELETEARR_NULLABLE(_cubemap_tex);
    _cubemap_tex = NEW char[len+1];
    strcpy(_cubemap_tex, prm_cubemap_tex);
    if (_pCubeMapTextureConnection) {
        _pCubeMapTextureConnection->close();
    }
    _pCubeMapTextureConnection = (TextureConnection*)(pCARETAKER->_pCubeMapTextureManager->connect(prm_cubemap_tex,this));
}
void ICubeMapActor::setCubeMapReflectance(float prm_reflectance) {
    _reflectance = prm_reflectance;
}

IDirect3DBaseTexture9* ICubeMapActor::getCubeMapTexture() {
    if (!_pCubeMapTextureConnection) {
        _pCubeMapTextureConnection = (TextureConnection*)(pCARETAKER->_pCubeMapTextureManager->connect("alpha_zero_cubemap.dds",this));
    }
    return _pCubeMapTextureConnection->peek()->_pIDirect3DBaseTexture9;
}

ICubeMapActor::~ICubeMapActor() {
    GGAF_DELETEARR_NULLABLE(_cubemap_tex);
    //資源取得の connet() はメインスレッドである。
    //しかし close() （デストラクタ）は愛スレッドで実行。
    //本当は避けるべきだが、GgafCore::ResourceConnection側のclose()を改良し、
    //別スレッドからのclose()にも対応した。TODO:要テスト
    if (_pCubeMapTextureConnection) {
        _pCubeMapTextureConnection->close();
    }
}

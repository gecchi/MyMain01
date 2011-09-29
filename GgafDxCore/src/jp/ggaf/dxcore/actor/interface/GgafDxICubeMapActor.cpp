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
//    //テクスチャを解放
//    _TRACE_("デバイスロストキューブマップ解放 GgafDxICubeMapActor::releaseCubeMapTex() begin "<<_pCubeMapTextureCon->getIdStr()<<"<-"<<_pCubeMapTextureCon->getNumConnection()<<"connection");
//    if (_pCubeMapTextureCon) {
//        _TRACE_("デバイスロストキューブマップ解放 GgafDxICubeMapActor::releaseCubeMapTex()->close() !");
//        _pCubeMapTextureCon->close();
//    }
//    //_TRACE_("デバイスロストキューブマップ解放 GgafDxICubeMapActor::releaseCubeMapTex() end "<<_pCubeMapTextureCon->getIdStr()<<"<-"<<_pCubeMapTextureCon->getNumConnection()<<"connection");
//    _pCubeMapTextureCon = NULL;
//    _pCubeMapTexture = NULL;
//}
//
//void GgafDxICubeMapActor::restoreCubeMapTex() {
//    _pCubeMapTextureCon = (GgafDxTextureConnection*)(GgafDxGod::_pCubeMapTextureManager->connect(_cubemap_tex));
//    _pCubeMapTexture = _pCubeMapTextureCon->use()->_pIDirect3DBaseTexture9;
//}


GgafDxICubeMapActor::~GgafDxICubeMapActor() {

    //資源取得の connet() はメインスレッドである。
    //しかし close() （デストラクタ）は工場スレッドで実行。
    //本当は避けるべきだが、GgafResourceConnection側のclose()を改良し、
    //別スレッドからのclose()にも対応した。TODO:要テスト
    if (_pCubeMapTextureCon) {
        _pCubeMapTextureCon->close();
    }
}

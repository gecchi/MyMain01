#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9ICubeMapActor::GgafDx9ICubeMapActor()  {
    _pCubeMapTextureCon = NULL;
    _pCubeMapTexture = NULL;
    _reflectance = 0.5f;
    _cubemap_tex = "uffizi_cross_cubemap.dds";
}

void GgafDx9ICubeMapActor::setCubeMapTexture(const char* prm_cubemap_tex, float prm_reflectance) {
    _reflectance = prm_reflectance;
    _cubemap_tex = prm_cubemap_tex;
    if (_pCubeMapTextureCon) {
        _pCubeMapTextureCon->close();
    }
    _pCubeMapTextureCon = (GgafDx9TextureConnection*)(GgafDx9God::_pCubeMapTextureManager->connect(prm_cubemap_tex));
    _pCubeMapTexture = _pCubeMapTextureCon->use()->_pIDirect3DBaseTexture9;
}


IDirect3DBaseTexture9* GgafDx9ICubeMapActor::getCubeMapTexture() {
    if (_pCubeMapTextureCon) {
        return _pCubeMapTexture;
    } else {
        _pCubeMapTextureCon = (GgafDx9TextureConnection*)(GgafDx9God::_pCubeMapTextureManager->connect("uffizi_cross_cubemap.dds"));
        _pCubeMapTexture = _pCubeMapTextureCon->use()->_pIDirect3DBaseTexture9;
        return _pCubeMapTexture;
    }
}

void GgafDx9ICubeMapActor::releaseCubeMapTex() {
    //テクスチャを解放
    if (_pCubeMapTextureCon) {
        _pCubeMapTextureCon->close();
    }
    _pCubeMapTextureCon = NULL;
    _pCubeMapTexture = NULL;
}

void GgafDx9ICubeMapActor::restoreCubeMapTex() {
    _pCubeMapTextureCon = (GgafDx9TextureConnection*)(GgafDx9God::_pCubeMapTextureManager->connect(_cubemap_tex));
    _pCubeMapTexture = _pCubeMapTextureCon->use()->_pIDirect3DBaseTexture9;
}


GgafDx9ICubeMapActor::~GgafDx9ICubeMapActor() {

    //資源取得の connet() はメインスレッドである。
    //しかし close() （デストラクタ）は工場スレッドで実行。
    //本当は避けるべきだが、GgafResourceConnection側のclose()を改良し、
    //別スレッドからのclose()にも対応した。TODO:要テスト
    if (_pCubeMapTextureCon) {
        _pCubeMapTextureCon->close();
    }
}

#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9ICubeMapActor::GgafDx9ICubeMapActor()  {
    _pCubeMapTextureCon = NULL;
    _pCubeMapTexture = NULL;
    _reflectance = 0.5f;
}

void GgafDx9ICubeMapActor::setCubeMapTexture(const char* prm_cubemap_tex, float prm_reflectance) {
    _reflectance = prm_reflectance;
    if (_pCubeMapTextureCon) {
        _pCubeMapTextureCon->close();
    }
    _pCubeMapTextureCon = (GgafDx9TextureConnection*)(P_UNIVERSE->_pCubeMapTextureManager->getConnection(prm_cubemap_tex));
    _pCubeMapTexture = _pCubeMapTextureCon->refer()->_pIDirect3DBaseTexture9;
}


IDirect3DBaseTexture9* GgafDx9ICubeMapActor::getCubeMapTexture() {
    if (_pCubeMapTextureCon) {
        return _pCubeMapTexture;
    } else {
        _pCubeMapTextureCon = (GgafDx9TextureConnection*)(P_UNIVERSE->_pCubeMapTextureManager->getConnection("uffizi_cross_cubemap.dds"));
        _pCubeMapTexture = _pCubeMapTextureCon->refer()->_pIDirect3DBaseTexture9;
        return _pCubeMapTexture;
    }
}

GgafDx9ICubeMapActor::~GgafDx9ICubeMapActor() {
    if (_pCubeMapTextureCon) {
        _pCubeMapTextureCon->close();
    }
}

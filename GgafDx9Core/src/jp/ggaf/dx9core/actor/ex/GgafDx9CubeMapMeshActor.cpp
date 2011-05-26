#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9CubeMapMeshActor::GgafDx9CubeMapMeshActor(const char* prm_name,
                                   const char* prm_model_id,
                                   const char* prm_effect_id,
                                   const char* prm_technique,
                                   GgafDx9Checker* prm_pChecker) :

                                           GgafDx9MeshActor(prm_name,
                                                            prm_model_id,
                                                            "G",
                                                            prm_effect_id,
                                                            "G",
                                                            prm_technique,
                                                            prm_pChecker) {
    _obj_class |= Obj_GgafDx9CubeMapMeshActor;
    _class_name = "GgafDx9CubeMapMeshActor";
    _pCubeMapMeshModel = (GgafDx9CubeMapMeshModel*)_pGgafDx9Model;
    _pCubeMapMeshEffect = (GgafDx9CubeMapMeshEffect*)_pGgafDx9Effect;
//    _pFunc_calcRotMvWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
    _pCubeMapTextureCon = (GgafDx9TextureConnection*)(P_UNIVERSE->_pCubeMapTextureManager->getConnection("uffizi_cross_cubemap.dds"));
    _pCubeMapTexture = _pCubeMapTextureCon->refer()->_pIDirect3DBaseTexture9;
    _reflectance = 0.3f;
}
void GgafDx9CubeMapMeshActor::setCubeMapTexture(const char* prm_cubemap_tex, float prm_reflectance) {
    _reflectance = prm_reflectance;
    _pCubeMapTextureCon->close();
    _pCubeMapTextureCon = (GgafDx9TextureConnection*)(P_UNIVERSE->_pCubeMapTextureManager->getConnection(prm_cubemap_tex));
    _pCubeMapTexture = _pCubeMapTextureCon->refer()->_pIDirect3DBaseTexture9;
}

void GgafDx9CubeMapMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pCubeMapMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9CubeMapMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pCubeMapMeshEffect->_h_reflectance, _reflectance);
    checkDxException(hr, D3D_OK, "GgafDx9CubeMapMeshActor::processDraw() SetFloat(_h_reflectances) に失敗しました。");
    if (_pCubeMapTextureCon) {
        GgafDx9God::_pID3DDevice9->SetTexture(1, _pCubeMapTextureCon->refer()->_pIDirect3DBaseTexture9);
    } else {
        throwGgafCriticalException("GgafDx9CubeMapMeshActor::processDraw() 環境マップテクスチャがありません this="<<getName());
    }
    _pCubeMapMeshModel->draw(this);
}

GgafDx9CubeMapMeshActor::~GgafDx9CubeMapMeshActor() {
    if (_pCubeMapTextureCon) {
        _pCubeMapTextureCon->close();
    }
}

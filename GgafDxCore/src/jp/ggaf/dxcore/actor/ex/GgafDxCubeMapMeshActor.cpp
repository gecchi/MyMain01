#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxCubeMapMeshActor::GgafDxCubeMapMeshActor(const char* prm_name,
                                   const char* prm_model_id,
                                   const char* prm_effect_id,
                                   const char* prm_technique,
                                   GgafStatus* prm_pStat,
                                   GgafDxChecker* prm_pChecker) :
                                           GgafDxMeshActor(prm_name,
                                                            prm_model_id,
                                                            "G",
                                                            prm_effect_id,
                                                            "G",
                                                            prm_technique,
                                                            prm_pStat,
                                                            prm_pChecker) ,
                                            GgafDxICubeMapActor() {
    _obj_class |= Obj_GgafDxCubeMapMeshActor;
    _class_name = "GgafDxCubeMapMeshActor";
    _pCubeMapMeshModel = (GgafDxCubeMapMeshModel*)_pModel;
    _pCubeMapMeshEffect = (GgafDxCubeMapMeshEffect*)_pEffect;
//    _pFunc_calcRotMvWorldMatrix = GgafDxUtil::setWorldMatrix_RxRzRyMv;
//    _pCubeMapTextureCon = (GgafDxTextureConnection*)(P_UNIVERSE->_pCubeMapTextureManager->connect("uffizi_cross_cubemap.dds"));
//    _pCubeMapTexture = _pCubeMapTextureCon->use()->_pIDirect3DBaseTexture9;
//    _reflectance = 0.3f;
}
//void GgafDxCubeMapMeshActor::setCubeMapTexture(const char* prm_cubemap_tex, float prm_reflectance) {
//    _reflectance = prm_reflectance;
//    _pCubeMapTextureCon->close();
//    _pCubeMapTextureCon = (GgafDxTextureConnection*)(P_UNIVERSE->_pCubeMapTextureManager->connect(prm_cubemap_tex));
//    _pCubeMapTexture = _pCubeMapTextureCon->use()->_pIDirect3DBaseTexture9;
//}

void GgafDxCubeMapMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pCubeMapMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxCubeMapMeshActor::processDraw() SetMatrix(g_matWorld) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pCubeMapMeshEffect->_h_reflectance, getCubeMapReflectance());
    checkDxException(hr, D3D_OK, "GgafDxCubeMapMeshActor::processDraw() SetFloat(_h_reflectances) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    GgafDxGod::_pID3DDevice9->SetTexture(1, getCubeMapTexture());
    _pCubeMapMeshModel->draw(this);
}



GgafDxCubeMapMeshActor::~GgafDxCubeMapMeshActor() {
}

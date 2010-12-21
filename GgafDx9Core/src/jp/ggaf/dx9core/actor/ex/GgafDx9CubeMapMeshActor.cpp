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
}


void GgafDx9CubeMapMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pCubeMapMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9CubeMapMeshActor::processDraw() SetMatrix(g_matWorld) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    _pCubeMapMeshModel->draw(this);
}

GgafDx9CubeMapMeshActor::~GgafDx9CubeMapMeshActor() {
}

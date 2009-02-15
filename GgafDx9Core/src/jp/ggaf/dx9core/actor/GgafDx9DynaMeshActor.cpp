#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9DynaMeshActor::GgafDx9DynaMeshActor(const char* prm_name,
                                           const char* prm_meshmodel_name,
                                           GgafDx9GeometryMover* prm_pGeoMover,
                                           GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {
    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_meshmodel_name);
    _pMeshModel = (GgafDx9MeshModel*)_pModelCon->view();
    _class_name = "GgafDx9DynaMeshActor";
    //マテリアルをコピー
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pMeshModel->_dwNumMaterials];
	for (DWORD i = 0; i < _pMeshModel->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pMeshModel->_paD3DMaterial9_default[i];
    }
    _fAlpha = 1.0f;
}

void GgafDx9DynaMeshActor::processDrawMain() {
    GgafDx9UntransformedActor::setWorldTransformRxRzRyScMv(this);
    _pMeshModel->draw(this);
}

void GgafDx9DynaMeshActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //α設定
    for (DWORD i = 0; i < _pMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}
GgafDx9DynaMeshActor::~GgafDx9DynaMeshActor() {
    _pModelCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}

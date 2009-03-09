#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9D3DXMeshActor::GgafDx9D3DXMeshActor(const char* prm_name,
                                   const char* prm_model,
                                   GgafDx9GeometryMover* prm_pGeoMover,
                                   GgafDx9GeometryChecker* prm_pGeoChecker) :
    GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {
    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pD3DXMeshModel = (GgafDx9D3DXMeshModel*)_pModelCon->view();
    _class_name = "GgafDx9D3DXMeshActor";
    //マテリアルをコピー
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pD3DXMeshModel->_dwNumMaterials];
	for (DWORD i = 0; i < _pD3DXMeshModel->_dwNumMaterials; i++){
	    _paD3DMaterial9[i] = _pD3DXMeshModel->_paD3DMaterial9_default[i];
	}
}

void GgafDx9D3DXMeshActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //α設定
    for (DWORD i = 0; i < _pD3DXMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}

void GgafDx9D3DXMeshActor::processDrawMain() {
//    if (_pID3DXEffect == NULL) {
//        GgafDx9UntransformedActor::setWorldTransformRxRzRyScMv(this);
//    }
    GgafDx9UntransformedActor::setWorldTransformRxRzRyScMv(this);
    _pD3DXMeshModel->draw(this);
}

GgafDx9D3DXMeshActor::~GgafDx9D3DXMeshActor() {
    _pModelCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}

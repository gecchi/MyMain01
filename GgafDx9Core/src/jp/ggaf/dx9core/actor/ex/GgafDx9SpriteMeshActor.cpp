#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteMeshActor::GgafDx9SpriteMeshActor(const char* prm_name,
                                       const char* prm_model,
                                       GgafDx9Checker* prm_pChecker) :

                                        GgafDx9MeshActor(prm_name,
                                                         prm_model,
                                                         "SpriteMeshEffect",
                                                         "SpriteMeshTechnique",
                                                         prm_pChecker) {

    _class_name = "GgafDx9SpriteMeshActor";
    _pUvFlipper = NEW GgafDx9UvFlipper(this);
    _pUvFlipper->forceUvFlipPtnRange(0, 1);
    _pUvFlipper->setUvFlipPtnNo(0);
    _pUvFlipper->setUvFlipMethod(NOT_ANIMATED, 1);
}


void GgafDx9SpriteMeshActor::processDraw() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatView, &pCAM->_vMatrixView );
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(g_matView) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    (*_pFunc_calcWorldMatrix)(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(g_matWorld) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    float u = 0;
    float v = 0;
    _pUvFlipper->getUV(u, v);
    hr = pID3DXEffect->SetFloat(_pMeshEffect->_h_offset_u, u);
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_u) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pMeshEffect->_h_offset_v, v);
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_v) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    _pMeshModel->draw(this);

}


GgafDx9SpriteMeshActor::~GgafDx9SpriteMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}

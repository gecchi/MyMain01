#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteMeshActor::GgafDx9SpriteMeshActor(const char* prm_name,
                                               const char* prm_model,
                                               GgafStatus* prm_pStat,
                                               GgafDx9Checker* prm_pChecker) :

                                        GgafDx9MeshActor(prm_name,
                                                         prm_model,
                                                         "SpriteMeshEffect",
                                                         "SpriteMeshTechnique",
                                                         prm_pStat,
                                                         prm_pChecker) {

    _obj_class |= Obj_GgafDx9SpriteMeshActor;
    _class_name = "GgafDx9SpriteMeshActor";
    GgafDx9Texture* pTexture = _pMeshModel->_papTextureCon[0]->use();
    _pUvFlipper = NEW GgafDx9UvFlipper(pTexture);
    _pUvFlipper->setRotation(1, 1);
    _pUvFlipper->setActivePtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
}


void GgafDx9SpriteMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
    float u = 0;
    float v = 0;
    _pUvFlipper->getUV(u, v);
    hr = pID3DXEffect->SetFloat(_pMeshEffect->_h_offset_u, u);
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_u) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pMeshEffect->_h_offset_v, v);
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_v) �Ɏ��s���܂����B");
    _pMeshModel->draw(this);
}


GgafDx9SpriteMeshActor::~GgafDx9SpriteMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}

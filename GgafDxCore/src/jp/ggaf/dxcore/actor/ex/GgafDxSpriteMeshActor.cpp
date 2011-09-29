#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSpriteMeshActor::GgafDxSpriteMeshActor(const char* prm_name,
                                               const char* prm_model,
                                               GgafStatus* prm_pStat,
                                               GgafDxChecker* prm_pChecker) :

                                        GgafDxMeshActor(prm_name,
                                                         prm_model,
                                                         "SpriteMeshEffect",
                                                         "SpriteMeshTechnique",
                                                         prm_pStat,
                                                         prm_pChecker) {

    _obj_class |= Obj_GgafDxSpriteMeshActor;
    _class_name = "GgafDxSpriteMeshActor";
    GgafDxTexture* pTexture = _pMeshModel->_papTextureCon[0]->use();
    _pUvFlipper = NEW GgafDxUvFlipper(pTexture);
    _pUvFlipper->setRotation(1, 1);
    _pUvFlipper->setActivePtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
}


void GgafDxSpriteMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetMatrix(g_matWorld) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    float u = 0;
    float v = 0;
    _pUvFlipper->getUV(u, v);
    hr = pID3DXEffect->SetFloat(_pMeshEffect->_h_offset_u, u);
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetMatrix(_h_offset_u) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pMeshEffect->_h_offset_v, v);
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetMatrix(_h_offset_v) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    _pMeshModel->draw(this);
}


GgafDxSpriteMeshActor::~GgafDxSpriteMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}

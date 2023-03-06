#include "jp/ggaf/dx/actor/DynaD3DXMeshActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"
#include "jp/ggaf/dx/model/D3DXMeshModel.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

DWORD DynaD3DXMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

DynaD3DXMeshActor::DynaD3DXMeshActor(const char* prm_name,
                                     const char* prm_model,
                                     const char* prm_effect_id,
                                     const char* prm_technique,
                                     CollisionChecker* prm_pChecker) :

                                         FigureActor(prm_name,
                                                     prm_model,
                                                     TYPE_DYNAD3DXMESH_MODEL,
                                                     prm_effect_id,
                                                     TYPE_MESH_EFFECT,
                                                     prm_technique,
                                                     prm_pChecker) {
    _obj_class |= Obj_GgafDx_DynaD3DXMeshActor;
    _class_name = "DynaD3DXMeshActor";

    _pD3DXMeshModel = (D3DXMeshModel*)_pModel;
    _pMeshEffect = (MeshEffect*)_pEffect;
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //ƒfƒtƒHƒ‹ƒg‚Ì‰ñ“]~ˆÚ“®‚Ì•ÏŠ·s—ñ
}

void DynaD3DXMeshActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    _pD3DXMeshModel->draw(this);
}

void DynaD3DXMeshActor::changeModel(int prm_model_index) {
    FigureActor::changeModel(prm_model_index);
    _pD3DXMeshModel = (D3DXMeshModel*)_pModel;
}

DynaD3DXMeshActor::~DynaD3DXMeshActor() {
}

#include "jp/ggaf/dx/actor/D3DXMeshActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/D3DXMeshModel.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

DWORD D3DXMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
D3DXMeshActor::D3DXMeshActor(const char* prm_name,
                             const char* prm_model,
                             const char* prm_effect_id,
                             const char* prm_technique) :

                                 FigureActor(prm_name,
                                             prm_model,
                                             TYPE_D3DXMESH_MODEL,
                                             prm_effect_id,
                                             TYPE_MESH_EFFECT,
                                             prm_technique) {
    _obj_class |= Obj_GgafDx_D3DXMeshActor;
    _class_name = "D3DXMeshActor";
    _pD3DXMeshModel = (D3DXMeshModel*)_pModel;
    _pMeshEffect = (MeshEffect*)_pEffect;
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
}

void D3DXMeshActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) に失敗しました。");
    _pD3DXMeshModel->draw(this);
}

void D3DXMeshActor::changeModelByIndex(int prm_model_index) {
    FigureActor::changeModelByIndex(prm_model_index);
    _pD3DXMeshModel = (D3DXMeshModel*)_pModel;
}

D3DXMeshActor::~D3DXMeshActor() {
}

#include "jp/ggaf/dxcore/actor/GgafDxD3DXMeshActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/model/GgafDxD3DXMeshModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshEffect.h"

using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxD3DXMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
GgafDxD3DXMeshActor::GgafDxD3DXMeshActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char* prm_effect_id,
                                         const char* prm_technique,
                                         GgafStatus* prm_pStat,
                                         GgafDxChecker* prm_pChecker) :

                                             GgafDxFigureActor(prm_name,
                                                                 prm_model_id,
                                                                 "D",
                                                                 prm_effect_id,
                                                                 "X",
                                                                 prm_technique,
                                                                 prm_pStat,
                                                                 prm_pChecker) {
    _obj_class |= Obj_GgafDxD3DXMeshActor;
    _class_name = "GgafDxD3DXMeshActor";
    _pD3DXMeshModel = (GgafDxD3DXMeshModel*)_pModel;
    _pMeshEffect = (GgafDxMeshEffect*)_pEffect;
    _pFunc_calc_rot_mv_world_matrix = UTIL::setWorldMatrix_RxRzRyMv;
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
}

void GgafDxD3DXMeshActor::setAlpha(float prm_alpha) {
    _alpha = prm_alpha;
    //GgafDxD3DXMeshActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pD3DXMeshModel->_num_materials; i++) {
        _paMaterial[i].Ambient.a = _alpha;
        _paMaterial[i].Diffuse.a = _alpha;
    }
}

void GgafDxD3DXMeshActor::addAlpha(float prm_alpha) {
    _alpha += prm_alpha;
    //GgafDxD3DXMeshActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pD3DXMeshModel->_num_materials; i++) {
        _paMaterial[i].Ambient.a = _alpha;
        _paMaterial[i].Diffuse.a = _alpha;
    }
}

void GgafDxD3DXMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxD3DXMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
    _pD3DXMeshModel->draw(this);
}

GgafDxD3DXMeshActor::~GgafDxD3DXMeshActor() {
}

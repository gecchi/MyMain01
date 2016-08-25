#include <jp/ggaf/dxcore/util/GgafDxUtil.h>
#include "jp/ggaf/dxcore/actor/GgafDxD3DXMeshActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
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
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
}

void GgafDxD3DXMeshActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) に失敗しました。");
    _pD3DXMeshModel->draw(this);
}

GgafDxD3DXMeshActor::~GgafDxD3DXMeshActor() {
}

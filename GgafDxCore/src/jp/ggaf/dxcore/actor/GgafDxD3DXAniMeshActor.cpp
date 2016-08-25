#include <jp/ggaf/dxcore/util/GgafDxUtil.h>
#include "jp/ggaf/dxcore/actor/GgafDxD3DXAniMeshActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxPuppeteer.h"
#include "jp/ggaf/dxcore/model/GgafDxD3DXAniMeshModel.h"

using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxD3DXAniMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
GgafDxD3DXAniMeshActor::GgafDxD3DXAniMeshActor(const char* prm_name,
                                               const char* prm_model_id,
                                               const char* prm_effect_id,
                                               const char* prm_technique,
                                               GgafStatus* prm_pStat,
                                               GgafDxChecker* prm_pChecker) :

                                                   GgafDxFigureActor(prm_name,
                                                                       prm_model_id,
                                                                       "A",
                                                                       prm_effect_id,
                                                                       "A",
                                                                       prm_technique,
                                                                       prm_pStat,
                                                                       prm_pChecker) {
    _obj_class |= Obj_GgafDxD3DXAniMeshActor;
    _class_name = "GgafDxD3DXAniMeshActor";
    _pD3DXAniMeshModel = (GgafDxD3DXAniMeshModel*)_pModel;
    _pD3DXAniMeshEffect = (GgafDxD3DXAniMeshEffect*)_pEffect;
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    _pPuppeteer = NEW GgafDxPuppeteer(this);
}

void GgafDxD3DXAniMeshActor::processDraw() {
    _pD3DXAniMeshModel->draw(this);
}

GgafDxD3DXAniMeshActor::~GgafDxD3DXAniMeshActor() {
    GGAF_DELETE(_pPuppeteer);
}

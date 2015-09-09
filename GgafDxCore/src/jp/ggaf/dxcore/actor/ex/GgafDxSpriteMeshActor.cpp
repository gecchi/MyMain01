#include "jp/ggaf/dxcore/actor/ex/GgafDxSpriteMeshActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshEffect.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"

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
    GgafDxTexture* pTexture = getModel()->getDefaultTextureConnection()->peek();
    _pUvFlipper = NEW GgafDxUvFlipper(pTexture);
    _pUvFlipper->setRotation(1, 1);
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
}

void GgafDxSpriteMeshActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pMeshEffect->_pID3DXEffect;
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
    _pMeshModel->GgafDxMeshModel::draw(this);
}

GgafDxSpriteMeshActor::~GgafDxSpriteMeshActor() {
    GGAF_DELETE(_pUvFlipper);
}

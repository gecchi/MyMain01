#include "GroundMeshActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshModel.h"
#include "jp/ggaf/lib/actor/ColliAABActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

GroundMeshActor::GroundMeshActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxMeshActor(prm_name,
                     prm_model,
                     "GroundMeshEffect",
                     "GroundMeshTechnique",
                     prm_pStat,
                     NEW CollisionChecker3D(this) ) {

    _class_name = "GroundMeshActor";
    offset_frames_ = 0;
    _pColliChecker = (CollisionChecker3D*)_pChecker;

//    if (pMeshModel_->paVtxBuffer_org_[0].nx == 0 &&
//        pMeshModel_->paVtxBuffer_org_[0].ny == 0 &&
//        pMeshModel_->paVtxBuffer_org_[0].nz == 0)
//    {
//        strcpy(technique_, "GroundMeshTechnique2");
//    }
}

//void GroundMeshActor::processPreDraw() {
//    pNext_TheSameRenderDepthIndexLevel_ = nullptr;
//    if (is_active_flg_ && can_live_flg_) {
//        //背景なので背面で描画
//        GgafDxSpacetime::setRenderDepthIndexMaxLevel(this);
//    }
//}

void GroundMeshActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    UTIL::setWorldMatrix_RxRzRyMv(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");

    _pMeshModel->GgafDxMeshModel::draw(this);
}

void GroundMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

GroundMeshActor::~GroundMeshActor() {
    GGAF_DELETE(_pColliChecker);
}

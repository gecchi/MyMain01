#include "GroundMeshActor.h"

#include "jp/ggaf/dxcore/effect/GgafDxMeshEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshModel.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
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
                     UTIL::createChecker(this) ) {

    _class_name = "GroundMeshActor";
    offset_frames_ = 0;
    _pColliChecker = (CollisionChecker*)_pChecker;

//    if (pMeshModel_->paVtxBuffer_data_[0].nx == 0 &&
//        pMeshModel_->paVtxBuffer_data_[0].ny == 0 &&
//        pMeshModel_->paVtxBuffer_data_[0].nz == 0)
//    {
//        strcpy(technique_, "GroundMeshTechnique2");
//    }
}

//void GroundMeshActor::processPreDraw() {
//    pNext_TheSameRenderDepthIndexLevel_ = nullptr;
//    if (is_active_flg_ && can_live_flg_) {
//        //”wŒi‚È‚Ì‚Å”w–Ê‚Å•`‰æ
//        GgafDxSpacetime::setRenderDepthIndexMaxLevel(this);
//    }
//}

void GroundMeshActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    UTIL::setWorldMatrix_RxRzRyMv(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");

    _pMeshModel->GgafDxMeshModel::draw(this);
}

void GroundMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

GroundMeshActor::~GroundMeshActor() {
    GGAF_DELETE(_pColliChecker);
}

#include "GroundMeshActor.h"

#include "jp/ggaf/dx/effect/MeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/MeshModel.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

GroundMeshActor::GroundMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::MeshActor(prm_name,
                     prm_model,
                     "GroundMeshEffect",
                     "GroundMeshTechnique") {

    _class_name = "GroundMeshActor";
    offset_frames_ = 0;
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();

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
//        GgafDx::Spacetime::setRenderDepthIndexMaxLevel(this);
//    }
//}

void GroundMeshActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    UTIL::setWorldMatrix_RxRzRyMv(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");

    _pMeshModel->GgafDx::MeshModel::draw(this);
}

void GroundMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}
GgafDx::CollisionChecker* GroundMeshActor::createChecker() {
    return UTIL::createCollisionChecker(this);
}
GroundMeshActor::~GroundMeshActor() {
}

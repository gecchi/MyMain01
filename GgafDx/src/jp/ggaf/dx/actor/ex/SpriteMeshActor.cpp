#include "jp/ggaf/dx/actor/ex/SpriteMeshActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/model/MeshModel.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

SpriteMeshActor::SpriteMeshActor(const char* prm_name,
                                 const char* prm_model,
                                 CollisionChecker* prm_pChecker) :

                                     MeshActor(prm_name,
                                               prm_model,
                                               "SpriteMeshEffect",
                                               "SpriteMeshTechnique",
                                               prm_pChecker) {

    _obj_class |= Obj_GgafDx_SpriteMeshActor;
    _class_name = "SpriteMeshActor";
    _pUvFlipper = NEW UvFlipper();
}

void SpriteMeshActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    float u = 0;
    float v = 0;
    _pUvFlipper->getUV(u, v);
    hr = pID3DXEffect->SetFloat(_pMeshEffect->_h_offset_u, u);
    checkDxException(hr, D3D_OK, "SetMatrix(_h_offset_u) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pMeshEffect->_h_offset_v, v);
    checkDxException(hr, D3D_OK, "SetMatrix(_h_offset_v) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    _pMeshModel->MeshModel::draw(this);
}

SpriteMeshActor::~SpriteMeshActor() {
    GGAF_DELETE(_pUvFlipper);
}

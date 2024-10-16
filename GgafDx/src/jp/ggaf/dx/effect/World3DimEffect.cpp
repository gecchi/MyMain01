#include "jp/ggaf/dx/effect/World3DimEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


using namespace GgafDx;

World3DimEffect::World3DimEffect(const char* prm_effect_name) : Effect(prm_effect_name) {
    _obj_class |= Obj_GgafDx_World3DimEffect;
    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();

    HRESULT hr;
    hr = _pID3DXEffect->SetFloat("g_zf", pCam->getZFar());
    checkDxException(hr, D3D_OK, "SetFloat(g_zf) に失敗しました。");
    hr = _pID3DXEffect->SetFloat("g_cameraZ_org", pCam->getZOrigin());
    checkDxException(hr, D3D_OK, "SetFloat(g_cameraZ_org) に失敗しました。");

    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", pCam->getProjectionMatrix() );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matProj) に失敗しました。");

    _h_matView = _pID3DXEffect->GetParameterByName( nullptr, "g_matView" );
    _h_fog_starts_far_rate = _pID3DXEffect->GetParameterByName( nullptr, "g_fog_starts_far_rate" );
}
void World3DimEffect::setParamPerFrame() {
    Camera* pCam = pCARETAKER->getSpacetime()->getCamera();
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, pCam->getViewMatrix() );
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_matView) に失敗しました。");
}

World3DimEffect::~World3DimEffect() {
}


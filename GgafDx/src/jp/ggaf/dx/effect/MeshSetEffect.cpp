#include "jp/ggaf/dx/effect/MeshSetEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


using namespace GgafDx;

MeshSetEffect::MeshSetEffect(const char* prm_effect_name) : World3DimEffect(prm_effect_name) {
    _obj_class |= Obj_GgafDx_MeshSetEffect;
    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    D3DLIGHT9* pLight = &(pCARETAKER->_d3dlight9_default);
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    //ライト方向
    hr = _pID3DXEffect->SetValue("g_vecLightFrom_World", &(pLight->Direction), sizeof(D3DVECTOR) );
    checkDxException(hr, D3D_OK, "SetValue(g_vecLightFrom_World) に失敗しました。");
    //Diffuse反射
    hr = _pID3DXEffect->SetValue("g_colLightDiffuse", &(pLight->Diffuse), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "SetValue(g_colLightDiffuse) に失敗しました。");
    //Ambient反射
    hr = _pID3DXEffect->SetValue("g_colLightAmbient", &(pLight->Ambient), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "SetValue(g_colLightAmbient) に失敗しました。");

    //シェーダーハンドル
    _ah_matWorld[0]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld001" );
    _ah_matWorld[1]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld002" );
    _ah_matWorld[2]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld003" );
    _ah_matWorld[3]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld004" );
    _ah_matWorld[4]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld005" );
    _ah_matWorld[5]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld006" );
    _ah_matWorld[6]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld007" );
    _ah_matWorld[7]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld008" );
    _ah_matWorld[8]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld009" );
    _ah_matWorld[9]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld010" );
    _ah_matWorld[10]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld011" );
    _ah_matWorld[11]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld012" );
    _ah_matWorld[12]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld013" );
    _ah_matWorld[13]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld014" );
    _ah_matWorld[14]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld015" );
    _ah_matWorld[15]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld016" );
    _ah_matWorld[16]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld017" );
    _ah_matWorld[17]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld018" );
    _ah_matWorld[18]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld019" );
    _ah_matWorld[19]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld020" );
    _ah_matWorld[20]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld021" );
    _ah_matWorld[21]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld022" );
    _ah_matWorld[22]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld023" );
    _ah_matWorld[23]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld024" );
    _ah_matWorld[24]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld025" );
    _ah_matWorld[25]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld026" );
    _ah_matWorld[26]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld027" );
    _ah_matWorld[27]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld028" );
    _ah_matWorld[28]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld029" );
    _ah_matWorld[29]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld030" );
    _ah_matWorld[30]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld031" );
    _ah_matWorld[31]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld032" );


    _ah_materialDiffuse[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse001" );
    _ah_materialDiffuse[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse002" );
    _ah_materialDiffuse[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse003" );
    _ah_materialDiffuse[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse004" );
    _ah_materialDiffuse[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse005" );
    _ah_materialDiffuse[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse006" );
    _ah_materialDiffuse[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse007" );
    _ah_materialDiffuse[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse008" );
    _ah_materialDiffuse[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse009" );
    _ah_materialDiffuse[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse010" );
    _ah_materialDiffuse[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse011" );
    _ah_materialDiffuse[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse012" );
    _ah_materialDiffuse[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse013" );
    _ah_materialDiffuse[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse014" );
    _ah_materialDiffuse[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse015" );
    _ah_materialDiffuse[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse016" );
    _ah_materialDiffuse[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse017" );
    _ah_materialDiffuse[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse018" );
    _ah_materialDiffuse[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse019" );
    _ah_materialDiffuse[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse020" );
    _ah_materialDiffuse[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse021" );
    _ah_materialDiffuse[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse022" );
    _ah_materialDiffuse[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse023" );
    _ah_materialDiffuse[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse024" );
    _ah_materialDiffuse[24] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse025" );
    _ah_materialDiffuse[25] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse026" );
    _ah_materialDiffuse[26] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse027" );
    _ah_materialDiffuse[27] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse028" );
    _ah_materialDiffuse[28] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse029" );
    _ah_materialDiffuse[29] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse030" );
    _ah_materialDiffuse[30] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse031" );
    _ah_materialDiffuse[31] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse032" );


    _ah_offset_u[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u001" );
    _ah_offset_u[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u002" );
    _ah_offset_u[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u003" );
    _ah_offset_u[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u004" );
    _ah_offset_u[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u005" );
    _ah_offset_u[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u006" );
    _ah_offset_u[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u007" );
    _ah_offset_u[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u008" );
    _ah_offset_u[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u009" );
    _ah_offset_u[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u010" );
    _ah_offset_u[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u011" );
    _ah_offset_u[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u012" );
    _ah_offset_u[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u013" );
    _ah_offset_u[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u014" );
    _ah_offset_u[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u015" );
    _ah_offset_u[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u016" );
    _ah_offset_u[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u017" );
    _ah_offset_u[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u018" );
    _ah_offset_u[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u019" );
    _ah_offset_u[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u020" );
    _ah_offset_u[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u021" );
    _ah_offset_u[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u022" );
    _ah_offset_u[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u023" );
    _ah_offset_u[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u024" );
    _ah_offset_u[24] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u025" );
    _ah_offset_u[25] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u026" );
    _ah_offset_u[26] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u027" );
    _ah_offset_u[27] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u028" );
    _ah_offset_u[28] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u029" );
    _ah_offset_u[29] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u030" );
    _ah_offset_u[30] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u031" );
    _ah_offset_u[31] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u032" );

    _ah_offset_v[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v001" );
    _ah_offset_v[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v002" );
    _ah_offset_v[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v003" );
    _ah_offset_v[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v004" );
    _ah_offset_v[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v005" );
    _ah_offset_v[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v006" );
    _ah_offset_v[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v007" );
    _ah_offset_v[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v008" );
    _ah_offset_v[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v009" );
    _ah_offset_v[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v010" );
    _ah_offset_v[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v011" );
    _ah_offset_v[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v012" );
    _ah_offset_v[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v013" );
    _ah_offset_v[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v014" );
    _ah_offset_v[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v015" );
    _ah_offset_v[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v016" );
    _ah_offset_v[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v017" );
    _ah_offset_v[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v018" );
    _ah_offset_v[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v019" );
    _ah_offset_v[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v020" );
    _ah_offset_v[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v021" );
    _ah_offset_v[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v022" );
    _ah_offset_v[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v023" );
    _ah_offset_v[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v024" );
    _ah_offset_v[24] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v025" );
    _ah_offset_v[25] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v026" );
    _ah_offset_v[26] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v027" );
    _ah_offset_v[27] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v028" );
    _ah_offset_v[28] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v029" );
    _ah_offset_v[29] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v030" );
    _ah_offset_v[30] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v031" );
    _ah_offset_v[31] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v032" );

    _h_specular = _pID3DXEffect->GetParameterByName( nullptr, "g_specular" );
    _h_specular_power = _pID3DXEffect->GetParameterByName( nullptr, "g_specular_power" );
    _h_posCam = _pID3DXEffect->GetParameterByName( nullptr, "g_posCam_World" );
}

void MeshSetEffect::setParamPerFrame() {
    World3DimEffect::setParamPerFrame();
    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    HRESULT hr = _pID3DXEffect->SetValue(_h_posCam, pCam->getVecCamFromPoint(), sizeof(D3DXVECTOR3) );
    checkDxException(hr, D3D_OK, "SetValue(_h_posCam) に失敗しました。_effect_name="<<_effect_name);
}

MeshSetEffect::~MeshSetEffect() {
}


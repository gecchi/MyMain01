#include "jp/ggaf/dx/effect/SkinAniMeshEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"

using namespace GgafDx;

SkinAniMeshEffect::SkinAniMeshEffect(const char* prm_effect_name) : World3DimEffect(prm_effect_name) {
    _obj_class |= Obj_GgafDx_SkinAniMeshEffect;
    Camera* pCam = pCARETAKER->getSpacetime()->getCamera();
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
    _h_specular = _pID3DXEffect->GetParameterByName( nullptr, "g_specular" );
    _h_specular_power = _pID3DXEffect->GetParameterByName( nullptr, "g_specular_power" );
    _h_posCam = _pID3DXEffect->GetParameterByName( nullptr, "g_posCam_World" );
    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );

    _ah_matBone[0]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone001" );
    _ah_matBone[1]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone002" );
    _ah_matBone[2]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone003" );
    _ah_matBone[3]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone004" );
    _ah_matBone[4]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone005" );
    _ah_matBone[5]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone006" );
    _ah_matBone[6]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone007" );
    _ah_matBone[7]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone008" );
    _ah_matBone[8]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone009" );
    _ah_matBone[9]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone010" );
    _ah_matBone[10]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone011" );
    _ah_matBone[11]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone012" );
    _ah_matBone[12]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone013" );
    _ah_matBone[13]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone014" );
    _ah_matBone[14]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone015" );
    _ah_matBone[15]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone016" );
    _ah_matBone[16]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone017" );
    _ah_matBone[17]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone018" );
    _ah_matBone[18]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone019" );
    _ah_matBone[19]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone020" );
    _ah_matBone[20]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone021" );
    _ah_matBone[21]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone022" );
    _ah_matBone[22]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone023" );
    _ah_matBone[23]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone024" );
    _ah_matBone[24]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone025" );
    _ah_matBone[25]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone026" );
    _ah_matBone[26]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone027" );
    _ah_matBone[27]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone028" );
    _ah_matBone[28]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone029" );
    _ah_matBone[29]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone030" );
    _ah_matBone[30]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone031" );
    _ah_matBone[31]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone032" );
    _ah_matBone[32]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone033" );
    _ah_matBone[33]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone034" );
    _ah_matBone[34]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone035" );
    _ah_matBone[35]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone036" );
    _ah_matBone[36]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone037" );
    _ah_matBone[37]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone038" );
    _ah_matBone[38]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone039" );
    _ah_matBone[39]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone040" );
    _ah_matBone[40]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone041" );
    _ah_matBone[41]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone042" );
    _ah_matBone[42]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone043" );
    _ah_matBone[43]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone044" );
    _ah_matBone[44]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone045" );
    _ah_matBone[45]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone046" );
    _ah_matBone[46]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone047" );
    _ah_matBone[47]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone048" );
    _ah_matBone[48]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone049" );
    _ah_matBone[49]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBone050" );
//    _ah_matBoneOffset[0]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset001" );
//    _ah_matBoneOffset[1]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset002" );
//    _ah_matBoneOffset[2]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset003" );
//    _ah_matBoneOffset[3]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset004" );
//    _ah_matBoneOffset[4]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset005" );
//    _ah_matBoneOffset[5]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset006" );
//    _ah_matBoneOffset[6]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset007" );
//    _ah_matBoneOffset[7]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset008" );
//    _ah_matBoneOffset[8]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset009" );
//    _ah_matBoneOffset[9]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset010" );
//    _ah_matBoneOffset[10]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset011" );
//    _ah_matBoneOffset[11]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset012" );
//    _ah_matBoneOffset[12]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset013" );
//    _ah_matBoneOffset[13]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset014" );
//    _ah_matBoneOffset[14]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset015" );
//    _ah_matBoneOffset[15]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset016" );
//    _ah_matBoneOffset[16]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset017" );
//    _ah_matBoneOffset[17]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset018" );
//    _ah_matBoneOffset[18]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset019" );
//    _ah_matBoneOffset[19]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset020" );
//    _ah_matBoneOffset[20]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset021" );
//    _ah_matBoneOffset[21]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset022" );
//    _ah_matBoneOffset[22]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset023" );
//    _ah_matBoneOffset[23]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset024" );
//    _ah_matBoneOffset[24]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset025" );
//    _ah_matBoneOffset[25]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset026" );
//    _ah_matBoneOffset[26]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset027" );
//    _ah_matBoneOffset[27]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset028" );
//    _ah_matBoneOffset[28]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset029" );
//    _ah_matBoneOffset[29]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset030" );
//    _ah_matBoneOffset[30]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset031" );
//    _ah_matBoneOffset[31]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset032" );
//    _ah_matBoneOffset[32]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset033" );
//    _ah_matBoneOffset[33]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset034" );
//    _ah_matBoneOffset[34]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset035" );
//    _ah_matBoneOffset[35]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset036" );
//    _ah_matBoneOffset[36]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset037" );
//    _ah_matBoneOffset[37]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset038" );
//    _ah_matBoneOffset[38]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset039" );
//    _ah_matBoneOffset[39]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset040" );
//    _ah_matBoneOffset[40]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset041" );
//    _ah_matBoneOffset[41]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset042" );
//    _ah_matBoneOffset[42]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset043" );
//    _ah_matBoneOffset[43]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset044" );
//    _ah_matBoneOffset[44]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset045" );
//    _ah_matBoneOffset[45]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset046" );
//    _ah_matBoneOffset[46]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset047" );
//    _ah_matBoneOffset[47]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset048" );
//    _ah_matBoneOffset[48]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset049" );
//    _ah_matBoneOffset[49]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matBoneOffset050" );
}

void SkinAniMeshEffect::setParamPerFrame() {
    World3DimEffect::setParamPerFrame();
    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    HRESULT hr = _pID3DXEffect->SetValue(_h_posCam, pCam->getVecCamFromPoint(), sizeof(D3DXVECTOR3) );
    checkDxException(hr, D3D_OK, "SetValue(_h_posCam) に失敗しました。_effect_name="<<_effect_name);
}

SkinAniMeshEffect::~SkinAniMeshEffect() {
}


#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9PrimitiveActor::GgafDx9PrimitiveActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_technique,
                                   GgafDx9GeometryMover* prm_pGeoMover,
                                   GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {

    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pPrimitiveModel = (GgafDx9PrimitiveModel*)_pModelCon->view();
    _class_name = "GgafDx9PrimitiveActor";

    //エフェクト取得
    _pEffectConnection = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection("GgafDx9MashEffect");
    _pID3DXEffect = _pEffectConnection->view();
    //モデルのオリジナルマテリアルをコピーして保存
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pPrimitiveModel->_dwNumMaterials];
    for (DWORD i = 0; i < _pPrimitiveModel->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pPrimitiveModel->_paD3DMaterial9_default[i];
    }
    //シェーダー共通のグローバル変数設定
	HRESULT hr;
	hr = _pID3DXEffect->SetTechnique(prm_technique);
    whetherGgafDx9CriticalException(hr, S_OK, "GgafDx9PrimitiveActor::GgafDx9PrimitiveActor SetTechnique() に失敗しました。");
    //VIEW変換行列
    hr = _pID3DXEffect->SetMatrix( "g_matView", &GgafDx9God::_vMatrixView );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveActor::processDrawMain SetMatrix(g_matView) に失敗しました。");
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", &GgafDx9God::_vMatrixProjrction );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveActor::GgafDx9PrimitiveActor SetMatrix() に失敗しました。");
    //ライト方向
    hr = _pID3DXEffect->SetValue("g_LightDirection", &(GgafDx9God::_d3dlight9_default.Direction), sizeof(D3DVECTOR) );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveModel::draw SetValue(g_LightDirection) に失敗しました。");
    //Diffuse反射
    hr = _pID3DXEffect->SetValue("g_LightDiffuse", &(GgafDx9God::_d3dlight9_default.Diffuse), sizeof(D3DCOLORVALUE));
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveModel::draw SetValue(g_LightDiffuse) に失敗しました。");
    //Ambient反射
    hr = _pID3DXEffect->SetValue("g_LightAmbient", &(GgafDx9God::_d3dlight9_default.Ambient), sizeof(D3DCOLORVALUE));
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveModel::draw SetValue(g_LightAmbient) に失敗しました。");
    //シェーダーハンドル
    _hMatWorld = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld" );
    _hMaterialDiffuse = _pID3DXEffect->GetParameterByName( NULL, "g_MaterialDiffuse" );
}

void GgafDx9PrimitiveActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //α設定
    for (DWORD i = 0; i < _pPrimitiveModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}

void GgafDx9PrimitiveActor::processDrawMain() {
	HRESULT hr;
    static D3DXMATRIX matWorld; //WORLD変換行列
    GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(this, matWorld);
    hr = _pID3DXEffect->SetMatrix(_hMatWorld, &matWorld );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveActor::processDrawMain SetMatrix(g_matWorld) に失敗しました。");
    UINT numPass;
    hr = _pID3DXEffect->Begin( &numPass, 0 );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveActor::processDrawMain Begin() に失敗しました。");
    for (UINT pass = 0; pass < numPass; pass++) {
        hr = _pID3DXEffect->BeginPass(pass);
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveModel::draw BeginPass(0) に失敗しました。");
        _pPrimitiveModel->draw(this);
        hr = _pID3DXEffect->EndPass();
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveModel::draw EndPass() に失敗しました。");
    }
    hr = _pID3DXEffect->End();
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveActor::processDrawMain End() に失敗しました。");

}

GgafDx9PrimitiveActor::~GgafDx9PrimitiveActor() {
    _pModelCon->close();
    _pEffectConnection->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}

#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9PrimitiveActor::GgafDx9PrimitiveActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_effect,
                                   GgafDx9GeometryMover* prm_pGeoMover,
                                   GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {

    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pPrimitiveModel = (GgafDx9PrimitiveModel*)_pModelCon->view();
    _class_name = "GgafDx9PrimitiveActor";


    _pEffectConnection = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(prm_effect);
    _pID3DXEffect = _pEffectConnection->view();
    //マテリアルをコピー
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pPrimitiveModel->_dwNumMaterials];
    for (DWORD i = 0; i < _pPrimitiveModel->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pPrimitiveModel->_paD3DMaterial9_default[i];
    }
    //g_matProj(射影変換行列)は全シェーダー共通のグローバル変数とすることとする。
	HRESULT hr;
	hr = _pID3DXEffect->SetTechnique("DefaultTec");
    if (hr != S_OK ) {
        throwGgafDx9CriticalException("GgafDx9PrimitiveActor::GgafDx9PrimitiveActor SetTechnique() に失敗しました。", hr);
    }

    hr = _pID3DXEffect->SetMatrix("g_matProj", &GgafDx9God::_vMatrixProjrction );
    if (hr != D3D_OK) {
        throwGgafDx9CriticalException("GgafDx9PrimitiveActor::GgafDx9PrimitiveActor SetMatrix() に失敗しました。", hr);
    }

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
//    if (_pID3DXEffect == NULL) {
//        GgafDx9UntransformedActor::setWorldTransformRxRzRyScMv(this);
//    }
	HRESULT hr;
    D3DXMATRIX matWorld; //WORLD変換行列

    GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(this, matWorld);
    GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_WORLD, &matWorld);

    hr = _pID3DXEffect->SetMatrix( "g_matWorld", &matWorld );
    if (hr != D3D_OK) {
        throwGgafDx9CriticalException("GgafDx9PrimitiveActor::processDrawMain SetMatrix(g_matWorld) に失敗しました。", hr);
    }
    hr = _pID3DXEffect->SetMatrix( "g_matView", &GgafDx9God::_vMatrixView );
    if (hr != D3D_OK) {
        throwGgafDx9CriticalException("GgafDx9PrimitiveActor::processDrawMain SetMatrix(g_matView) に失敗しました。", hr);
    }

    UINT numPass;
    hr = _pID3DXEffect->Begin( &numPass, 0 );
    if (hr != D3D_OK) {
        throwGgafDx9CriticalException("GgafDx9PrimitiveActor::processDrawMain Begin() に失敗しました。", hr);
    }
    
    _pPrimitiveModel->draw(this);
    
    hr = _pID3DXEffect->End();
    if (hr != D3D_OK) {
        throwGgafDx9CriticalException("GgafDx9PrimitiveActor::processDrawMain End() に失敗しました。", hr);
    }

}

GgafDx9PrimitiveActor::~GgafDx9PrimitiveActor() {
    _pModelCon->close();
    _pEffectConnection->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}

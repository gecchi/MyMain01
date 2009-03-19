#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MeshActor::GgafDx9MeshActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_effect,
                                   const char* prm_technique,
                                   GgafDx9GeometryMover* prm_pGeoMover,
                                   GgafDx9GeometryChecker* prm_pGeoChecker) :
    GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker)
{
    _class_name = "GgafDx9MeshActor";
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
    //モデル取得
    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pMeshModel = (GgafDx9MeshModel*)_pModelCon->view();
    //エフェクト取得
    _pEffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(prm_effect);
    _pMeshEffect = (GgafDx9MeshEffect*)_pEffectCon->view();
    //モデルのオリジナルマテリアルをコピーして保存
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pMeshModel->_dwNumMaterials];
    for (DWORD i = 0; i < _pMeshModel->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pMeshModel->_paD3DMaterial9_default[i];
    }
}

void GgafDx9MeshActor::setAlpha(float prm_fAlpha) {
    GgafDx9UntransformedActor::setAlpha(prm_fAlpha);
    //α設定
    for (DWORD i = 0; i < _pMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}

void GgafDx9MeshActor::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    static D3DXMATRIX matWorld; //WORLD変換行列
    GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(this, matWorld);

	HRESULT hr;
	hr = pID3DXEffect->SetTechnique(_technique);
    whetherGgafDx9CriticalException(hr, S_OK, "GgafDx9MeshActor::processDrawMain() SetTechnique("<<_technique<<") に失敗しました。");

    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &matWorld );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() SetMatrix(g_matWorld) に失敗しました。");
    UINT numPass;
    hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE | D3DXFX_DONOTSAVESHADERSTATE );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() Begin() に失敗しました。");
    for (UINT pass = 0; pass < numPass; pass++) {
        hr = pID3DXEffect->BeginPass(pass);
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() BeginPass("<<pass<<") に失敗しました。");
        _pMeshModel->draw(this);
        hr = pID3DXEffect->EndPass();
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() EndPass() に失敗しました。");
    }
    hr = pID3DXEffect->End();
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() End() に失敗しました。");

}

GgafDx9MeshActor::~GgafDx9MeshActor() {
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    _pModelCon->close();
    _pEffectCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}

#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MeshSetActor::GgafDx9MeshSetActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char* prm_effect_id,
                                         const char* prm_technique,
                                         GgafDx9Checker* prm_pChecker) :
                                             GgafDx9DrawableActor(prm_name,
                                                                  prm_model_id,
                                                                  "x",
                                                                  prm_effect_id,
                                                                  "x",
                                                                  prm_technique,
                                                                  prm_pChecker) {
    _class_name = "GgafDx9MeshSetActor";
    _pMeshSetModel = (GgafDx9MeshSetModel*)_pGgafDx9Model;
    _pMeshSetEffect = (GgafDx9MeshSetEffect*)_pGgafDx9Effect;
    _pFunc_calcWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
}


void GgafDx9MeshSetActor::setAlpha(float prm_fAlpha) {
    GgafDx9DrawableActor::setAlpha(prm_fAlpha);
    //GgafDx9MeshSetActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pMeshSetModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}


void GgafDx9MeshSetActor::processDraw() {
    _draw_set_num = 1; //GgafDx9MeshSetActorの同じモデルが連続しているカウント数。同一描画深度は一度に描画する。
    GgafDx9DrawableActor* _pNextDrawActor;
    _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            if (_pNextDrawActor->_pGgafDx9Model == _pMeshSetModel && _pNextDrawActor->isActive()) {
                _draw_set_num++;
                if (_draw_set_num > _pMeshSetModel->_set_num) {
                    _draw_set_num = _pMeshSetModel->_set_num;
                    break;
                }
                _pNextDrawActor = _pNextDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;

    //VIEW変換行列
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_hMatView, &pCAM->_vMatrixView);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(_hMatView) に失敗しました。");
    //基本モデル頂点数
    hr = pID3DXEffect->SetInt(_pMeshSetEffect->_h_nVertexs, _pMeshSetModel->_nVertices);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetInt(_h_nVertexs) に失敗しました。2");

    GgafDx9DrawableActor *pDrawActor;
    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {
        //(*_pFunc_calcWorldMatrix)(pDrawActor, pDrawActor->_matWorld);
        //GgafDx9Util::setWorldMatrix_ScRxRzRyMv(pDrawActor, pDrawActor->_matWorld);
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ahMatWorld[i], &(pDrawActor->_matWorld));
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
        hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ahMaterialDiffuse[i], &(pDrawActor->_paD3DMaterial9[0].Diffuse), sizeof(D3DCOLORVALUE) );
        //【GgafDx9MeshSetActorのマテリアルカラーについて考え方】備忘録メモ
        //本来はマテリアル１オブジェクトに複数保持し、マテリアルリストのグループ毎に設定するものだが、実行速度最適化と使用レジスタ数削減の為、各セットの[0]のマテリアルを全体のマテリアルとする。
        //したがってGgafDx9MeshSetActorはマテリアル色は8セット全てそれぞれ１色しか不可能。
        //もともと本クラスは、同一モデル複数オブジェクトを、最大8セット同時に一回で描画しスピードアップを図ることを目的としたクラスで、たくさんマテリアルグループがあるオブジェクトには不向というか無意味である。
        //１枚テクスチャで頑張れば問題ない･･･という方針。マテリアル色で色分けしたい場合は GgafDx9MeshActor を使うしかない。
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() SetValue(g_MaterialDiffuse) に失敗しました。");
        pDrawActor = pDrawActor -> _pNext_TheSameDrawDepthLevel;
        if (i > 0) {
            //アクティブを進める
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    _pMeshSetModel->draw(this);
}

GgafDx9MeshSetActor::~GgafDx9MeshSetActor() {
}

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
    _obj_class |= Obj_GgafDx9MeshSetActor;
    _class_name = "GgafDx9MeshSetActor";
    _pMeshSetModel = (GgafDx9MeshSetModel*)_pGgafDx9Model;
    _pMeshSetEffect = (GgafDx9MeshSetEffect*)_pGgafDx9Effect;
    _pFunc_calcRotMvWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
}

GgafDx9MeshSetActor::GgafDx9MeshSetActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char* prm_model_type,
                                         const char* prm_effect_id,
                                         const char* prm_effect_type,
                                         const char* prm_technique,
                                         GgafDx9Checker* prm_pChecker) :

                                             GgafDx9DrawableActor(prm_name,
                                                                  prm_model_id,
                                                                  prm_model_type,
                                                                  prm_effect_id,
                                                                  prm_effect_type,
                                                                  prm_technique,
                                                                  prm_pChecker) {
    _obj_class |= Obj_GgafDx9MeshSetActor;
    _class_name = "GgafDx9MeshSetActor";
    _pMeshSetModel = (GgafDx9MeshSetModel*)_pGgafDx9Model;
    _pMeshSetEffect = (GgafDx9MeshSetEffect*)_pGgafDx9Effect;
    _pFunc_calcRotMvWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
}

void GgafDx9MeshSetActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //GgafDx9MeshSetActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pMeshSetModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}

void GgafDx9MeshSetActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //GgafDx9MeshSetActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pMeshSetModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}

void GgafDx9MeshSetActor::processDraw() {
    _draw_set_num = 0; //GgafDx9MeshSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    GgafDx9DrawableActor* pDrawActor = this;
    GgafDx9MeshSetActor* pMeshSetActor;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pGgafDx9Model == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pMeshSetActor = (GgafDx9MeshSetActor*)pDrawActor;
                //(*_pFunc_calcRotMvWorldMatrix)(pDrawActor, pDrawActor->_matWorld);
                //GgafDx9Util::setWorldMatrix_ScRxRzRyMv(pDrawActor, pDrawActor->_matWorld);
                hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[_draw_set_num], &(pMeshSetActor->_matWorld));
                checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
                hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[_draw_set_num], &(pMeshSetActor->_paD3DMaterial9[0].Diffuse), sizeof(D3DCOLORVALUE) );
                //【GgafDx9MeshSetActorのマテリアルカラーについて考え方】備忘録メモ
                //本来はマテリアル１オブジェクトに複数保持し、マテリアルリストのグループ毎に設定するものだが、実行速度最適化と使用レジスタ数削減の為、各セットの[0]のマテリアルを全体のマテリアルとする。
                //したがってGgafDx9MeshSetActorはマテリアル色は8セット全てそれぞれ１色しか不可能。
                //それぞれの１色を、マテリアル色としてオブジェクト別につるため頂点カラーで実現している。
                //もともと本クラスは、同一モデル複数オブジェクトを、最大8セット同時に一回で描画しスピードアップを図ることを目的としたクラスで、たくさんマテリアルグループがあるオブジェクトには不向というか無意味である。
                //１枚テクスチャで頑張れば問題ない・・・という方針。マテリアル色で色分けしたい場合は GgafDx9MeshActor を使うしかない。
                checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");
                _draw_set_num++;
                if (_draw_set_num >= _pMeshSetModel->_set_num) {
                    break;
                }
                pDrawActor = pDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    GgafDx9Universe::_pActor_DrawActive = pMeshSetActor; //描画セットの最後アクターをセット
    _pMeshSetModel->draw(this, _draw_set_num);
}

GgafDx9MeshSetActor::~GgafDx9MeshSetActor() {
}

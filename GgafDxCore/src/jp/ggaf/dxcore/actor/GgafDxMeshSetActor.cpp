#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMeshSetActor::GgafDxMeshSetActor(const char* prm_name,
                                       const char* prm_model_id,
                                       const char* prm_effect_id,
                                       const char* prm_technique,
                                       GgafStatus* prm_pStat,
                                       GgafDxChecker* prm_pChecker) :

                                           GgafDxDrawableActor(prm_name,
                                                                prm_model_id,
                                                                "x",
                                                                prm_effect_id,
                                                                "x",
                                                                prm_technique,
                                                                prm_pStat,
                                                                prm_pChecker) {
    _obj_class |= Obj_GgafDxMeshSetActor;
    _class_name = "GgafDxMeshSetActor";
    _pMeshSetModel = (GgafDxMeshSetModel*)_pModel;
    _pMeshSetEffect = (GgafDxMeshSetEffect*)_pEffect;
    _pFunc_calcRotMvWorldMatrix = GgafDxUtil::setWorldMatrix_RxRzRyMv;
}

GgafDxMeshSetActor::GgafDxMeshSetActor(const char* prm_name,
                                       const char* prm_model_id,
                                       const char* prm_model_type,
                                       const char* prm_effect_id,
                                       const char* prm_effect_type,
                                       const char* prm_technique,
                                       GgafStatus* prm_pStat,
                                       GgafDxChecker* prm_pChecker) :

                                           GgafDxDrawableActor(prm_name,
                                                                prm_model_id,
                                                                prm_model_type,
                                                                prm_effect_id,
                                                                prm_effect_type,
                                                                prm_technique,
                                                                prm_pStat,
                                                                prm_pChecker) {
    _obj_class |= Obj_GgafDxMeshSetActor;
    _class_name = "GgafDxMeshSetActor";
    _pMeshSetModel = (GgafDxMeshSetModel*)_pModel;
    _pMeshSetEffect = (GgafDxMeshSetEffect*)_pEffect;
    _pFunc_calcRotMvWorldMatrix = GgafDxUtil::setWorldMatrix_RxRzRyMv;
}

void GgafDxMeshSetActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //GgafDxMeshSetActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pMeshSetModel->_dwNumMaterials; i++) {
        _paMaterial[i].Ambient.a = _fAlpha;
        _paMaterial[i].Diffuse.a = _fAlpha;
    }
}

void GgafDxMeshSetActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //GgafDxMeshSetActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pMeshSetModel->_dwNumMaterials; i++) {
        _paMaterial[i].Ambient.a = _fAlpha;
        _paMaterial[i].Diffuse.a = _fAlpha;
    }
}

void GgafDxMeshSetActor::processDraw() {
    _draw_set_num = 0; //GgafDxMeshSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    GgafDxDrawableActor* pDrawActor = this;
    GgafDxMeshSetActor* pMeshSetActor = NULL;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pModel == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pMeshSetActor = (GgafDxMeshSetActor*)pDrawActor;
                hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[_draw_set_num], &(pMeshSetActor->_matWorld));
                checkDxException(hr, D3D_OK, "GgafDxMeshSetActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
                hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[_draw_set_num], &(pMeshSetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
                //【GgafDxMeshSetActorのマテリアルカラーについて考え方】備忘録メモ
                //本来はマテリアル１オブジェクトに複数保持し、マテリアルリストのグループ毎に設定するものだが、実行速度最適化と使用レジスタ数削減(ピクセルシェーダー2.0)の為、
                //各セットの[0]のマテリアルを全体のマテリアルとする。
                //したがってGgafDxMeshSetActorはマテリアル色は１色しか不可能。
                //それぞれの１色を、マテリアル色としてオブジェクト別につるため頂点カラーで実現している。
                //もともと本クラスは、同一モデル複数オブジェクトを、同時に一回で描画しスピードアップを図ることを目的としたクラスで、たくさんマテリアルグループがあるオブジェクトには不向というか無意味である。
                //１枚テクスチャで頑張れば問題ない・・・という方針。マテリアル色で色分けしたい場合は GgafDxMeshActor を使うしかない。
                checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");
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
    GgafDxUniverse::_pActor_DrawActive = pMeshSetActor; //描画セットの最後アクターをセット
    _pMeshSetModel->draw(this, _draw_set_num);
}

GgafDxMeshSetActor::~GgafDxMeshSetActor() {
}

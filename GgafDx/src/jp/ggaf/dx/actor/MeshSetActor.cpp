#include "jp/ggaf/dx/actor/MeshSetActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/effect/MeshSetEffect.h"
#include "jp/ggaf/dx/model/MeshSetModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

MeshSetActor::MeshSetActor(const char* prm_name,
                           const char* prm_model,
                           const char* prm_effect_id,
                           const char* prm_technique,
                           CollisionChecker* prm_pChecker) :

                               FigureActor(prm_name,
                                           prm_model,
                                           TYPE_MESHSET_MODEL,
                                           prm_effect_id,
                                           TYPE_MESHSET_EFFECT,
                                           prm_technique,
                                           prm_pChecker),
_pMeshSetModel((MeshSetModel*)_pModel),
_pMeshSetEffect((MeshSetEffect*)_pEffect)
{
    _obj_class |= Obj_GgafDx_MeshSetActor;
    _class_name = "MeshSetActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
}

MeshSetActor::MeshSetActor(const char* prm_name,
                           const char* prm_model,
                           const char prm_model_type,
                           const char* prm_effect_id,
                           const char prm_effect_type,
                           const char* prm_technique,
                           CollisionChecker* prm_pChecker) :

                               FigureActor(prm_name,
                                           prm_model,
                                           prm_model_type,
                                           prm_effect_id,
                                           prm_effect_type,
                                           prm_technique,
                                           prm_pChecker),
_pMeshSetModel((MeshSetModel*)_pModel),
_pMeshSetEffect((MeshSetEffect*)_pEffect) {

    _obj_class |= Obj_GgafDx_MeshSetActor;
    _class_name = "MeshSetActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
}

void MeshSetActor::processDraw() {
    int draw_set_num = 0; //MeshSetActorの同じモデルで同じテクニックが
                          //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* const pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    FigureActor* pDrawActor = this;
    MeshSetActor* pMeshSetActor = nullptr;
    const int model_draw_set_num = _pMeshSetModel->_draw_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pMeshSetActor = (MeshSetActor*)pDrawActor;
            hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[draw_set_num], &(pMeshSetActor->_matWorld));
            checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) に失敗しました。");
            hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[draw_set_num], &(pMeshSetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
            //【MeshSetActorのマテリアルカラーについて考え方】備忘録メモ
            //本来はマテリアル１オブジェクトに複数保持し、マテリアルリストのグループ毎に設定するものだが、実行速度最適化と使用レジスタ数削減(ピクセルシェーダー2.0)の為、
            //各セットの[0]のマテリアルを全体のマテリアルとする。
            //したがってMeshSetActorはマテリアル色は１色しか不可能。
            //それぞれの１色を、マテリアル色としてオブジェクト別につるため頂点カラーで実現している。
            //もともと本クラスは、同一モデル複数オブジェクトを、同時に一回で描画しスピードアップを図ることを目的としたクラスで、たくさんマテリアルグループがあるオブジェクトには不向というか無意味である。
            //１枚テクスチャで頑張れば問題ない・・・という方針。マテリアル色で色分けしたい場合は MeshActor を使うしかない。
            checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) に失敗しました。");

            pDrawActor = pDrawActor->_pNextRenderActor;
            draw_set_num++;
            if (draw_set_num >= model_draw_set_num) {
                break;
            }
        } else {
            break;
        }
    }
    ((MeshSetModel*)_pMeshSetModel)->MeshSetModel::draw(this, draw_set_num);
    _pNextRenderActor = pDrawActor;
}

void MeshSetActor::changeModelByIndex(int prm_model_index) {
    FigureActor::changeModelByIndex(prm_model_index);
    _pMeshSetModel = (MeshSetModel*)_pModel;
}


MeshSetActor::~MeshSetActor() {
}

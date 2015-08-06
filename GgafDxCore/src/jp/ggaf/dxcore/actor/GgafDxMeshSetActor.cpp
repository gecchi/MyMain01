#include "jp/ggaf/dxcore/actor/GgafDxMeshSetActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMeshSetActor::GgafDxMeshSetActor(const char* prm_name,
                                       const char* prm_model_id,
                                       const char* prm_effect_id,
                                       const char* prm_technique,
                                       GgafStatus* prm_pStat,
                                       GgafDxChecker* prm_pChecker) :

                                           GgafDxFigureActor(prm_name,
                                                               prm_model_id,
                                                               "x",
                                                               prm_effect_id,
                                                               "x",
                                                               prm_technique,
                                                               prm_pStat,
                                                               prm_pChecker),
_pMeshSetModel((GgafDxMeshSetModel*)_pModel),
_pMeshSetEffect((GgafDxMeshSetEffect*)_pEffect) {
    _obj_class |= Obj_GgafDxMeshSetActor;
    _class_name = "GgafDxMeshSetActor";
    _pFunc_calc_rot_mv_world_matrix = UTIL::setWorldMatrix_RxRzRyMv;
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
}

GgafDxMeshSetActor::GgafDxMeshSetActor(const char* prm_name,
                                       const char* prm_model_id,
                                       const char* prm_model_type,
                                       const char* prm_effect_id,
                                       const char* prm_effect_type,
                                       const char* prm_technique,
                                       GgafStatus* prm_pStat,
                                       GgafDxChecker* prm_pChecker) :

                                           GgafDxFigureActor(prm_name,
                                                               prm_model_id,
                                                               prm_model_type,
                                                               prm_effect_id,
                                                               prm_effect_type,
                                                               prm_technique,
                                                               prm_pStat,
                                                               prm_pChecker),
_pMeshSetModel((GgafDxMeshSetModel*)_pModel),
_pMeshSetEffect((GgafDxMeshSetEffect*)_pEffect) {

    _obj_class |= Obj_GgafDxMeshSetActor;
    _class_name = "GgafDxMeshSetActor";
    _pFunc_calc_rot_mv_world_matrix = UTIL::setWorldMatrix_RxRzRyMv;
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
}

void GgafDxMeshSetActor::processDraw() {
    int draw_set_num = 0; //GgafDxMeshSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* const pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    GgafDxFigureActor* pDrawActor = this;
    GgafDxMeshSetActor* pMeshSetActor = nullptr;
    const int model_set_num = _pMeshSetModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pMeshSetActor = (GgafDxMeshSetActor*)pDrawActor;
            hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[draw_set_num], &(pMeshSetActor->_matWorld));
            checkDxException(hr, D3D_OK, "GgafDxMeshSetActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
            hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[draw_set_num], &(pMeshSetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
            //【GgafDxMeshSetActorのマテリアルカラーについて考え方】備忘録メモ
            //本来はマテリアル１オブジェクトに複数保持し、マテリアルリストのグループ毎に設定するものだが、実行速度最適化と使用レジスタ数削減(ピクセルシェーダー2.0)の為、
            //各セットの[0]のマテリアルを全体のマテリアルとする。
            //したがってGgafDxMeshSetActorはマテリアル色は１色しか不可能。
            //それぞれの１色を、マテリアル色としてオブジェクト別につるため頂点カラーで実現している。
            //もともと本クラスは、同一モデル複数オブジェクトを、同時に一回で描画しスピードアップを図ることを目的としたクラスで、たくさんマテリアルグループがあるオブジェクトには不向というか無意味である。
            //１枚テクスチャで頑張れば問題ない・・・という方針。マテリアル色で色分けしたい場合は GgafDxMeshActor を使うしかない。
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");
            draw_set_num++;
            if (draw_set_num >= model_set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextActor_in_render_depth;
        } else {
            break;
        }
    }
    GgafDxSpacetime::_pActor_draw_active = pMeshSetActor; //描画セットの最後アクターをセット
    ((GgafDxMeshSetModel*)_pMeshSetModel)->GgafDxMeshSetModel::draw(this, draw_set_num);
}

GgafDxMeshSetActor::~GgafDxMeshSetActor() {
}

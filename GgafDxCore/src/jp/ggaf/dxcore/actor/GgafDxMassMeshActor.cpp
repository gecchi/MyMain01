#include "jp/ggaf/dxcore/actor/GgafDxMassMeshActor.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassMeshEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxMassMeshModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMassMeshActor::GgafDxMassMeshActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char* prm_effect_id,
                                         const char* prm_technique,
                                         GgafStatus* prm_pStat,
                                         GgafDxChecker* prm_pChecker) :

                                           GgafDxFigureActor(prm_name,
                                                             prm_model_id,
                                                             "t",
                                                             prm_effect_id,
                                                             "t",
                                                             prm_technique,
                                                             prm_pStat,
                                                             prm_pChecker),
_pMassMeshModel((GgafDxMassMeshModel*)_pModel),
_pMassMeshEffect((GgafDxMassMeshEffect*)_pEffect) {
    _obj_class |= Obj_GgafDxMassMeshActor;
    _class_name = "GgafDxMassMeshActor";
    _pFunc_calc_rot_mv_world_matrix = UTIL::setWorldMatrix_RxRzRyMv;
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
}

GgafDxMassMeshActor::GgafDxMassMeshActor(const char* prm_name,
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
_pMassMeshModel((GgafDxMassMeshModel*)_pModel),
_pMassMeshEffect((GgafDxMassMeshEffect*)_pEffect) {

    _obj_class |= Obj_GgafDxMassMeshActor;
    _class_name = "GgafDxMassMeshActor";
    _pFunc_calc_rot_mv_world_matrix = UTIL::setWorldMatrix_RxRzRyMv;
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
}

void GgafDxMassMeshActor::processDraw() {
    int draw_set_num = 0; //GgafDxMassMeshActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    GgafDxMassMeshModel* pMassMeshModel = _pMassMeshModel;
    const int model_max_set_num = pMassMeshModel->_set_num;
    const hashval hash_technique = _hash_technique;
    GgafDxMassMeshModel::VERTEX_instancedata* paInstancedata = pMassMeshModel->_aInstancedata;

    static const size_t SIZE_D3DXMATRIX = sizeof(D3DXMATRIX);
    static const size_t SIZE_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    GgafDxFigureActor* pDrawActor = this;
    while (pDrawActor) {
        if (pDrawActor->getModel() == pMassMeshModel && pDrawActor->_hash_technique == hash_technique) {
            memcpy(paInstancedata, &(pDrawActor->_matWorld), SIZE_D3DXMATRIX);
            memcpy(&(paInstancedata->r), &(pDrawActor->_paMaterial[0].Diffuse), SIZE_D3DCOLORVALUE);
//            (*(D3DXMATRIX*)(&(paInstancedata[draw_set_num]))) = pDrawActor->_matWorld;
//            (*(D3DCOLORVALUE *)(&(paInstancedata[draw_set_num].r))) = pDrawActor->_paMaterial[0].Diffuse;
            paInstancedata++;
            draw_set_num++;
            if (draw_set_num >= model_max_set_num) {
                break;
            }
            GgafDxSpacetime::_pActor_draw_active = pDrawActor; //描画セットの最後アクターをセット
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    ((GgafDxMassMeshModel*)_pMassMeshModel)->GgafDxMassMeshModel::draw(this, draw_set_num);
}

GgafDxMassMeshActor::~GgafDxMassMeshActor() {
}

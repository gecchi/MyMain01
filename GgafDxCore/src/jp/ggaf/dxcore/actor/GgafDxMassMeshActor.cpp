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
    GgafDxFigureActor* pDrawActor = this;
    GgafDxMassMeshActor* pMassMeshActor = nullptr;
    GgafDxMassMeshModel* pMassMeshModel = _pMassMeshModel;
    const int model_set_num = pMassMeshModel->_set_num;
    GgafDxMassMeshModel::VERTEX_instancedata* paInstancedata = pMassMeshModel->_aInstancedata;
    static const size_t size_D3DXMATRIX = sizeof(D3DXMATRIX);
    static const size_t size_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    while (pDrawActor) {
        if (pDrawActor->getModel() == pMassMeshModel && pDrawActor->_hash_technique == _hash_technique) {
            pMassMeshActor = (GgafDxMassMeshActor*)pDrawActor;
            memcpy(paInstancedata, &(pMassMeshActor->_matWorld), size_D3DXMATRIX);
            memcpy(&(paInstancedata->r), &(pMassMeshActor->_paMaterial[0].Diffuse), size_D3DCOLORVALUE);
//            (*(D3DXMATRIX*)(&(paInstancedata[draw_set_num]))) = pMassMeshActor->_matWorld;
//            (*(D3DCOLORVALUE *)(&(paInstancedata[draw_set_num].r))) = pMassMeshActor->_paMaterial[0].Diffuse;
            paInstancedata++;
            draw_set_num++;
            if (draw_set_num >= model_set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextActor_in_render_depth;
            if (pDrawActor == nullptr) {
                GgafDxSpacetime* pSpacetime =  P_GOD->getSpacetime();

                /////////////////////////////////
                //TODO:もっとスマートに！↓
                if (GgafDxSpacetime::render_depth_index_active > 0) {
                    GgafDxFigureActor* pNextDrawActor = pSpacetime->_papFirstActor_in_render_depth[GgafDxSpacetime::render_depth_index_active-1];
                    if (pNextDrawActor) {
                        if (pNextDrawActor->getModel() == pMassMeshModel && pNextDrawActor->_hash_technique == _hash_technique) {
                            pSpacetime->_papFirstActor_in_render_depth[GgafDxSpacetime::render_depth_index_active] = nullptr; //次回のためにリセット
                            pSpacetime->_papLastActor_in_render_depth[GgafDxSpacetime::render_depth_index_active] = nullptr;
                            GgafDxSpacetime::render_depth_index_active--;
                            pDrawActor = pNextDrawActor;
                        }
                    } else {
                        if (GgafDxSpacetime::render_depth_index_active > 1) {
                            GgafDxFigureActor* pNextNextDrawActor = pSpacetime->_papFirstActor_in_render_depth[GgafDxSpacetime::render_depth_index_active-2];
                            if (pNextNextDrawActor) {
                                if (pNextNextDrawActor->getModel() == pMassMeshModel && pNextNextDrawActor->_hash_technique == _hash_technique) {
                                    pSpacetime->_papFirstActor_in_render_depth[GgafDxSpacetime::render_depth_index_active] = nullptr; //次回のためにリセット
                                    pSpacetime->_papLastActor_in_render_depth[GgafDxSpacetime::render_depth_index_active] = nullptr;
                                    GgafDxSpacetime::render_depth_index_active--;
                                    pSpacetime->_papFirstActor_in_render_depth[GgafDxSpacetime::render_depth_index_active] = nullptr; //次回のためにリセット
                                    pSpacetime->_papLastActor_in_render_depth[GgafDxSpacetime::render_depth_index_active] = nullptr;
                                    GgafDxSpacetime::render_depth_index_active--;
                                    pDrawActor = pNextNextDrawActor;
                                }
                            }
                        }
                    }
                }
                /////////////////////////////////////

            }
        } else {
            break;
        }
    }
    GgafDxSpacetime::_pActor_draw_active = pMassMeshActor; //描画セットの最後アクターをセット
    ((GgafDxMassMeshModel*)_pMassMeshModel)->GgafDxMassMeshModel::draw(this, draw_set_num);
}

GgafDxMassMeshActor::~GgafDxMassMeshActor() {
}

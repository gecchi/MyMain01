#include "jp/ggaf/dxcore/actor/GgafDxMassMeshActor.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassMeshEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxMassMeshModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;


GgafDxMassMeshActor::VERTEX_instancedata GgafDxMassMeshActor::_aInstancedata[MAX_INSTACE];

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
    _pMassMeshModel->_pFunc_CreateVertexInstaceData = GgafDxMassMeshActor::createVertexInstaceData;
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

    _pMassMeshModel->_pFunc_CreateVertexInstaceData = GgafDxMassMeshActor::createVertexInstaceData;
}

void GgafDxMassMeshActor::processDraw() {
    int draw_set_num = 0; //GgafDxMassMeshActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    GgafDxMassMeshModel* pMassMeshModel = _pMassMeshModel;
    const int model_max_set_num = pMassMeshModel->_set_num;
    const hashval hash_technique = _hash_technique;
    VERTEX_instancedata* paInstancedata = GgafDxMassMeshActor::_aInstancedata;
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

void GgafDxMassMeshActor::createVertexInstaceData(D3DVERTEXELEMENT9** out_paVtxInstaceDataElement,
                                                    int* out_elem_num,
                                                    UINT* out_size_vertex_unit_instacedata,
                                                    void** out_pInstancedata) {
    *out_paVtxInstaceDataElement = NEW D3DVERTEXELEMENT9[5];
    *out_elem_num = 5;
    *out_size_vertex_unit_instacedata = sizeof(VERTEX_instancedata);
    *out_pInstancedata = GgafDxMassMeshActor::_aInstancedata;

    // Stream = 1 ---->
    WORD st1_offset_next = 0;
    //float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目
    (*out_paVtxInstaceDataElement)[0].Stream = 1;
    (*out_paVtxInstaceDataElement)[0].Offset = st1_offset_next;
    (*out_paVtxInstaceDataElement)[0].Type   = D3DDECLTYPE_FLOAT4;
    (*out_paVtxInstaceDataElement)[0].Method = D3DDECLMETHOD_DEFAULT;
    (*out_paVtxInstaceDataElement)[0].Usage  = D3DDECLUSAGE_TEXCOORD;
    (*out_paVtxInstaceDataElement)[0].UsageIndex = 1;
    st1_offset_next += sizeof(float)*4;
    //float _21, _22, _23, _24;  // : TEXCOORD2  World変換行列、２行目
    (*out_paVtxInstaceDataElement)[1].Stream = 1;
    (*out_paVtxInstaceDataElement)[1].Offset = st1_offset_next;
    (*out_paVtxInstaceDataElement)[1].Type   = D3DDECLTYPE_FLOAT4;
    (*out_paVtxInstaceDataElement)[1].Method = D3DDECLMETHOD_DEFAULT;
    (*out_paVtxInstaceDataElement)[1].Usage  = D3DDECLUSAGE_TEXCOORD;
    (*out_paVtxInstaceDataElement)[1].UsageIndex = 2;
    st1_offset_next += sizeof(float)*4;
    //float _31, _32, _33, _34;  // : TEXCOORD3  World変換行列、３行目
    (*out_paVtxInstaceDataElement)[2].Stream = 1;
    (*out_paVtxInstaceDataElement)[2].Offset = st1_offset_next;
    (*out_paVtxInstaceDataElement)[2].Type   = D3DDECLTYPE_FLOAT4;
    (*out_paVtxInstaceDataElement)[2].Method = D3DDECLMETHOD_DEFAULT;
    (*out_paVtxInstaceDataElement)[2].Usage  = D3DDECLUSAGE_TEXCOORD;
    (*out_paVtxInstaceDataElement)[2].UsageIndex = 3;
    st1_offset_next += sizeof(float)*4;
    //float _41, _42, _43, _44;  // : TEXCOORD4  World変換行列、４行目
    (*out_paVtxInstaceDataElement)[3].Stream = 1;
    (*out_paVtxInstaceDataElement)[3].Offset = st1_offset_next;
    (*out_paVtxInstaceDataElement)[3].Type   = D3DDECLTYPE_FLOAT4;
    (*out_paVtxInstaceDataElement)[3].Method = D3DDECLMETHOD_DEFAULT;
    (*out_paVtxInstaceDataElement)[3].Usage  = D3DDECLUSAGE_TEXCOORD;
    (*out_paVtxInstaceDataElement)[3].UsageIndex = 4;
    st1_offset_next += sizeof(float)*4;
    //float r, g, b, a;        // : TEXCOORD5  マテリアルカラー
    (*out_paVtxInstaceDataElement)[4].Stream = 1;
    (*out_paVtxInstaceDataElement)[4].Offset = st1_offset_next;
    (*out_paVtxInstaceDataElement)[4].Type   = D3DDECLTYPE_FLOAT4;
    (*out_paVtxInstaceDataElement)[4].Method = D3DDECLMETHOD_DEFAULT;
    (*out_paVtxInstaceDataElement)[4].Usage  = D3DDECLUSAGE_TEXCOORD;
    (*out_paVtxInstaceDataElement)[4].UsageIndex = 5;
    st1_offset_next += sizeof(float)*4;
    // <---- Stream = 1

}

GgafDxMassMeshActor::~GgafDxMassMeshActor() {
}

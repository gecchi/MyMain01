#include "jp/ggaf/lib/actor/DefaultMassBoardActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultMassBoardActor::VERTEX_instancedata DefaultMassBoardActor::_aInstancedata[GGAFDXMASS_MAX_INSTACE];

DefaultMassBoardActor::DefaultMassBoardActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxMassBoardActor(prm_name, prm_model, "DefaultMassBoardEffect", "DefaultMassBoardTechnique")
{
    _class_name = "DefaultMassBoardActor";
    _pMassBoardModel->registerCallback_VertexInstaceDataInfo(DefaultMassBoardActor::createVertexInstaceData);
}

void DefaultMassBoardActor::createVertexInstaceData(GgafDxMassModel::VertexInstaceDataInfo* out_info) {
    int element_num = 2;
    out_info->paElement = NEW D3DVERTEXELEMENT9[element_num];
    // Stream = 1 ---->
    WORD st1_offset_next = 0;
    //float transformed_x, transformed_y, depth_z;   // : TEXCOORD1
    out_info->paElement[0].Stream = 1;
    out_info->paElement[0].Offset = st1_offset_next;
    out_info->paElement[0].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[0].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[0].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[0].UsageIndex = 1;
    st1_offset_next += sizeof(float)*3;
    //float offset_u, offset_v, alpha;              // : TEXCOORD2
    out_info->paElement[1].Stream = 1;
    out_info->paElement[1].Offset = st1_offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[1].UsageIndex = 2;
    st1_offset_next += sizeof(float)*3;
    // <---- Stream = 1

    out_info->element_num = element_num;
    out_info->size_vertex_unit_instacedata = sizeof(DefaultMassBoardActor::VERTEX_instancedata);
    out_info->pInstancedata = DefaultMassBoardActor::_aInstancedata;
}
void DefaultMassBoardActor::processDraw() {
    int draw_set_num = 0; //GgafDxMassBoardActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    GgafDxMassBoardEffect* pMassBoardEffect = _pMassBoardEffect;
    HRESULT hr;
    GgafDxFigureActor* pDrawActor = this;
    DefaultMassBoardActor* pDefaultMassBoardActor = nullptr;
    int model_set_num = _pMassBoardModel->_set_num;
    float u,v;
    VERTEX_instancedata* paInstancedata = DefaultMassBoardActor::_aInstancedata;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMassBoardModel && pDrawActor->_hash_technique == _hash_technique) {
            pDefaultMassBoardActor = (DefaultMassBoardActor*)pDrawActor;

            GgafDxAlign align = pDefaultMassBoardActor->_align;
            GgafDxValign valign = pDefaultMassBoardActor->_valign;


            if (align == ALIGN_RIGHT) {
                paInstancedata->transformed_x = C_PX(pDefaultMassBoardActor->_x) - pDefaultMassBoardActor->_width_px;
            } else if (align == ALIGN_CENTER) {
                paInstancedata->transformed_x = C_PX(pDefaultMassBoardActor->_x) - pDefaultMassBoardActor->_harf_width_px;
            } else {
                //ALIGN_LEFT
                paInstancedata->transformed_x = C_PX(pDefaultMassBoardActor->_x);
            }
            if (valign == VALIGN_BOTTOM) {
                paInstancedata->transformed_y = C_PX(pDefaultMassBoardActor->_y) - pDefaultMassBoardActor->_height_px;
            } else if (valign == VALIGN_MIDDLE) {
                paInstancedata->transformed_y = C_PX(pDefaultMassBoardActor->_y) - pDefaultMassBoardActor->_harf_height_px;
            } else {
                //VALIGN_TOP
                paInstancedata->transformed_y = C_PX(pDefaultMassBoardActor->_y);
            }
            paInstancedata->depth_z = C_PX(pDefaultMassBoardActor->_z);

            pDefaultMassBoardActor->getUvFlipper()->getUV(u,v);
            paInstancedata->offset_u = u;
            paInstancedata->offset_v = v;
            paInstancedata->alpha = pDrawActor->_alpha;
            paInstancedata++;

            draw_set_num++;
            GgafDxSpacetime::_pActor_draw_active = pDrawActor; //描画セットの最後アクターをセット
            if (draw_set_num >= model_set_num) {
                break;
            } else {
                pDrawActor = pDrawActor->_pNextRenderActor;
            }
        } else {
            break;
        }
    }
    _pMassBoardModel->GgafDxMassBoardModel::draw(this, draw_set_num);
}

DefaultMassBoardActor::~DefaultMassBoardActor() {
}


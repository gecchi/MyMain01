#include "jp/ggaf/lib/actor/FontBoardActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassBoardEffect.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FontBoardActor::VERTEX_instancedata FontBoardActor::_aInstancedata[GGAFDXMASS_MAX_INSTANCE_NUM];

FontBoardActor::FontBoardActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
          GgafDxMassBoardActor(prm_name, prm_model, "FontBoardEffect", "FontBoardTechnique"),
          ICharacterChip<FontBoardActor>(this, (int)(_pMassBoardModel->_model_width_px), (int)(_pMassBoardModel->_model_height_px))
{
    _class_name = "FontBoardActor";
    _pMassBoardModel->registerCallback_VertexInstanceDataInfo(FontBoardActor::createVertexInstanceData);
}

void FontBoardActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    if (_align != prm_align || _valign != prm_valign) {
        _align = prm_align;
        _valign = prm_valign;
        prepare2();
    }
}

void FontBoardActor::setAlign(GgafDxAlign prm_align) {
    if (_align != prm_align) {
        _align = prm_align;
        prepare2();
    }
}

void FontBoardActor::setValign(GgafDxValign prm_valign) {
    if (_valign != prm_valign) {
        _valign = prm_valign;
        prepare2();
    }
}

void FontBoardActor::createVertexInstanceData(void* prm, GgafDxMassModel::VertexInstanceDataInfo* out_info) {
    int element_num = 2;
    out_info->paElement = NEW D3DVERTEXELEMENT9[element_num];
    // Stream = 1 ---->
    WORD st1_offset_next = 0;
    //float px_x, px_y, depth_z;   // : TEXCOORD1
    out_info->paElement[0].Stream = 1;
    out_info->paElement[0].Offset = st1_offset_next;
    out_info->paElement[0].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[0].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[0].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[0].UsageIndex = 1;
    st1_offset_next += sizeof(float)*3;
    //float offset_u, offset_v, alpha;   // : TEXCOORD2
    out_info->paElement[1].Stream = 1;
    out_info->paElement[1].Offset = st1_offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[1].UsageIndex = 2;
    st1_offset_next += sizeof(float)*3;
    // <---- Stream = 1

    out_info->element_num = element_num;
    out_info->size_vertex_unit_instancedata = sizeof(FontBoardActor::VERTEX_instancedata);
    out_info->pInstancedata = FontBoardActor::_aInstancedata;
}

void FontBoardActor::processDraw() {
    int draw_set_num = 0; //GgafDxMassBoardActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    VERTEX_instancedata* paInstancedata = FontBoardActor::_aInstancedata;
    GgafDxFigureActor* pDrawActor = this;
    FontBoardActor* pFontBoardActor = nullptr;
    int model_set_num = _pMassBoardModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == this->getModel() && pDrawActor->_hash_technique == this->_hash_technique) {
            pFontBoardActor = (FontBoardActor*)pDrawActor;
            int n = pFontBoardActor->_draw_chr_num;
            pixcoord x = C_PX(pFontBoardActor->_x);
            pixcoord y = C_PX(pFontBoardActor->_y);
            pixcoord z = C_PX(pFontBoardActor->_z);
            InstancePart* pInstancePart = pFontBoardActor->_paInstancePart;
            float alpha = pFontBoardActor->_alpha;
            GgafDxSpacetime::_pActor_draw_active = pDrawActor; //描画セットの最後アクターをセット

            for (int i = 0; i < n; i++) {
                paInstancedata->px_x = (float)(x + pInstancePart->px_local_x);
                paInstancedata->px_y = (float)(y + pInstancePart->px_local_y);
                paInstancedata->depth_z = (float)(z);
                paInstancedata->offset_u = pInstancePart->offset_u;
                paInstancedata->offset_v = pInstancePart->offset_v;
                paInstancedata->alpha    = alpha;
                ++pInstancePart;
                ++paInstancedata;

                draw_set_num++;
                if (draw_set_num >= model_set_num) {
                   _pMassBoardModel->GgafDxMassBoardModel::draw(this, draw_set_num);
                   paInstancedata = FontBoardActor::_aInstancedata;
                   draw_set_num = 0;
                }
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    if (draw_set_num > 0) {
        _pMassBoardModel->GgafDxMassBoardModel::draw(this, draw_set_num);
    }
}

FontBoardActor::~FontBoardActor() {
}



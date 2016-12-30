#include "jp/ggaf/lib/actor/DefaultMassBoardActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultMassBoardActor::VERTEX_instancedata DefaultMassBoardActor::_aInstancedata[GGAFDXMASS_MAX_INSTANCE_NUM];

DefaultMassBoardActor::DefaultMassBoardActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxMassBoardActor(prm_name, prm_model, "DefaultMassBoardEffect", "DefaultMassBoardTechnique")
{
    _class_name = "DefaultMassBoardActor";
    _pMassBoardModel->registerCallback_VertexInstanceDataInfo(DefaultMassBoardActor::createVertexInstanceData);
}

void DefaultMassBoardActor::createVertexInstanceData(void* prm, GgafDxMassModel::VertexInstanceDataInfo* out_info) {
    int element_num = 5;
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
    //float local_px_x, local_px_y;     // : TEXCOORD2
    out_info->paElement[1].Stream = 1;
    out_info->paElement[1].Offset = st1_offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT2;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[1].UsageIndex = 2;
    st1_offset_next += sizeof(float)*2;
    //float r_sx, r_sy, rad_rz;                     // : TEXCOORD3
    out_info->paElement[2].Stream = 1;
    out_info->paElement[2].Offset = st1_offset_next;
    out_info->paElement[2].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[2].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[2].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[2].UsageIndex = 3;
    st1_offset_next += sizeof(float)*3;
    //float offset_u, offset_v;                     // : TEXCOORD4
    out_info->paElement[3].Stream = 1;
    out_info->paElement[3].Offset = st1_offset_next;
    out_info->paElement[3].Type   = D3DDECLTYPE_FLOAT2;
    out_info->paElement[3].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[3].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[3].UsageIndex = 4;
    st1_offset_next += sizeof(float)*2;
    //float r, g, b, a;                              // : TEXCOORD5  �}�e���A���J���[
    out_info->paElement[4].Stream = 1;
    out_info->paElement[4].Offset = st1_offset_next;
    out_info->paElement[4].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[4].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[4].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[4].UsageIndex = 5;
    st1_offset_next += sizeof(float)*4;
    // <---- Stream = 1

    out_info->element_num = element_num;
    out_info->size_vertex_unit_instancedata = sizeof(DefaultMassBoardActor::VERTEX_instancedata);
    out_info->pInstancedata = DefaultMassBoardActor::_aInstancedata;
}
void DefaultMassBoardActor::processDraw() {
    int draw_set_num = 0; //GgafDxMassBoardActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    GgafDxFigureActor* pDrawActor = this;
    DefaultMassBoardActor* pDefaultMassBoardActor = nullptr;
    int model_set_num = _pMassBoardModel->_set_num;
    float u,v;
    VERTEX_instancedata* paInstancedata = DefaultMassBoardActor::_aInstancedata;
    static const size_t size_of_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMassBoardModel && pDrawActor->_hash_technique == _hash_technique) {
            pDefaultMassBoardActor = (DefaultMassBoardActor*)pDrawActor;

            GgafDxAlign align = pDefaultMassBoardActor->_align;
            GgafDxValign valign = pDefaultMassBoardActor->_valign;

            paInstancedata->px_x = C_PX(pDefaultMassBoardActor->_x);
            paInstancedata->px_y = C_PX(pDefaultMassBoardActor->_y);
            paInstancedata->depth_z = C_PX(pDefaultMassBoardActor->_z);
            if (align == ALIGN_RIGHT) {
                paInstancedata->local_px_x = -_pMassBoardModel->_model_width_px;
            } else if (align == ALIGN_CENTER) {
                paInstancedata->local_px_x = -_pMassBoardModel->_model_half_width_px;
            } else { //ALIGN_LEFT
                paInstancedata->local_px_x = 0.0f;
            }
            if (valign == VALIGN_BOTTOM) {
                paInstancedata->local_px_y = -_pMassBoardModel->_model_height_px;
            } else if (valign == VALIGN_MIDDLE) {
                paInstancedata->local_px_y = -_pMassBoardModel->_model_half_height_px;
            } else { //VALIGN_TOP
                paInstancedata->local_px_y = 0.0f;
            }
            paInstancedata->r_sx = SC_R(pDrawActor->_sx);
            paInstancedata->r_sy = SC_R(pDrawActor->_sy);
            paInstancedata->rad_rz = ANG_RAD(pDrawActor->_rz);
            pDefaultMassBoardActor->getUvFlipper()->getUV(u,v);
            paInstancedata->offset_u = u;
            paInstancedata->offset_v = v;
            memcpy(&(paInstancedata->r), &(pDefaultMassBoardActor->_paMaterial[0].Diffuse), size_of_D3DCOLORVALUE);
            ++paInstancedata;

            draw_set_num++;
            GgafDxSpacetime::_pActor_draw_active = pDrawActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
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


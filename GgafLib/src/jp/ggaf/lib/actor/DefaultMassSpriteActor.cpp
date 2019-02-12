#include "jp/ggaf/lib/actor/DefaultMassSpriteActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/scene/Spacetime.h"



using namespace GgafLib;

DefaultMassSpriteActor::VERTEX_instancedata DefaultMassSpriteActor::_aInstancedata[GGAFDXMASS_MAX_INSTANCE_NUM];

DefaultMassSpriteActor::DefaultMassSpriteActor(const char* prm_name, const char* prm_model_id, GgafCore::Status* prm_pStat) :
    GgafDx::MassSpriteActor(prm_name,
                          prm_model_id,
                          "DefaultMassSpriteEffect",
                          "DefaultMassSpriteTechnique",
                          prm_pStat,
                          UTIL::createChecker(this) ) {

    _class_name = "DefaultMassSpriteActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
    _pMassSpriteModel->registerCallback_VertexInstanceDataInfo(DefaultMassSpriteActor::createVertexInstanceData);
    setZWriteEnable(false);
}

void DefaultMassSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

void DefaultMassSpriteActor::createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info) {
    int element_num = 6;
    out_info->paElement = NEW D3DVERTEXELEMENT9[element_num];
    // Stream = 1 ---->
    WORD st1_offset_next = 0;
    //float _11, _12, _13, _14;   // : TEXCOORD1  World�ϊ��s��A�P�s��
    out_info->paElement[0].Stream = 1;
    out_info->paElement[0].Offset = st1_offset_next;
    out_info->paElement[0].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[0].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[0].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[0].UsageIndex = 1;
    st1_offset_next += sizeof(float)*4;
    //float _21, _22, _23, _24;  // : TEXCOORD2  World�ϊ��s��A�Q�s��
    out_info->paElement[1].Stream = 1;
    out_info->paElement[1].Offset = st1_offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[1].UsageIndex = 2;
    st1_offset_next += sizeof(float)*4;
    //float _31, _32, _33, _34;  // : TEXCOORD3  World�ϊ��s��A�R�s��
    out_info->paElement[2].Stream = 1;
    out_info->paElement[2].Offset = st1_offset_next;
    out_info->paElement[2].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[2].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[2].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[2].UsageIndex = 3;
    st1_offset_next += sizeof(float)*4;
    //float _41, _42, _43, _44;  // : TEXCOORD4  World�ϊ��s��A�S�s��
    out_info->paElement[3].Stream = 1;
    out_info->paElement[3].Offset = st1_offset_next;
    out_info->paElement[3].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[3].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[3].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[3].UsageIndex = 4;
    st1_offset_next += sizeof(float)*4;
    //float offset_u, offset_v;   // : TEXCOORD5  �e�N�X�`���I�t�Z�b�g
    out_info->paElement[4].Stream = 1;
    out_info->paElement[4].Offset = st1_offset_next;
    out_info->paElement[4].Type   = D3DDECLTYPE_FLOAT2;
    out_info->paElement[4].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[4].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[4].UsageIndex = 5;
    st1_offset_next += sizeof(float)*2;
    //float r, g, b, a;           // : TEXCOORD6  �}�e���A���J���[
    out_info->paElement[5].Stream = 1;
    out_info->paElement[5].Offset = st1_offset_next;
    out_info->paElement[5].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[5].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[5].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[5].UsageIndex = 6;
    st1_offset_next += sizeof(float)*4;
    // <---- Stream = 1

    out_info->element_num = element_num;
    out_info->size_vertex_unit_instancedata = sizeof(DefaultMassSpriteActor::VERTEX_instancedata);
    out_info->pInstancedata = DefaultMassSpriteActor::_aInstancedata;
}

void DefaultMassSpriteActor::processDraw() {
    int draw_set_num = 0; //MassSpriteActor�̓������f���œ����e�N�j�b�N��
                          //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    GgafDx::MassSpriteModel* pMassSpriteModel = _pMassSpriteModel;
    const int model_max_set_num = pMassSpriteModel->_set_num;
    const hashval hash_technique = _hash_technique;
    VERTEX_instancedata* paInstancedata = DefaultMassSpriteActor::_aInstancedata;
    GgafDx::FigureActor* pDrawActor = this;
    static const size_t size_of_D3DXMATRIX = sizeof(D3DXMATRIX);
    static const size_t size_of_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    static const dxcoord model_half_width = PX_DX(pMassSpriteModel->_model_half_width_px);
    static const dxcoord model_half_height = PX_DX(pMassSpriteModel->_model_half_height_px);
    float u,v;
    DefaultMassSpriteActor* pDefaultMassSpriteActor = nullptr;

    while (pDrawActor) {
        if (pDrawActor->getModel() == pMassSpriteModel && pDrawActor->_hash_technique == hash_technique) {
            pDefaultMassSpriteActor = (DefaultMassSpriteActor*)pDrawActor;
//            Align align = pDefaultMassSpriteActor->_align;
//            Valign valign = pDefaultMassSpriteActor->_valign;

            memcpy(paInstancedata, &(pDrawActor->_matWorld), size_of_D3DXMATRIX);
//            if (align == ALIGN_CENTER) {
//                paInstancedata->local_x = 0;
//            } else if (align == ALIGN_LEFT) {
//                paInstancedata->local_x = model_half_width;
//            } else { //ALIGN_RIGHT
//                paInstancedata->local_x = -model_half_width;
//            }
//            if (valign == VALIGN_MIDDLE) {
//                paInstancedata->local_y = 0;
//            } else if (valign == VALIGN_TOP) {
//                paInstancedata->local_y = -model_half_height;
//            } else {  //VALIGN_BOTTOM
//                paInstancedata->local_y = model_half_height;
//            }
            pDefaultMassSpriteActor->getUvFlipper()->getUV(u,v);
            paInstancedata->offset_u = u;
            paInstancedata->offset_v = v;
            memcpy(&(paInstancedata->r), &(pDefaultMassSpriteActor->_paMaterial[0].Diffuse), size_of_D3DCOLORVALUE);
            ++paInstancedata;

            draw_set_num++;
            GgafDx::Spacetime::_pActor_draw_active = pDrawActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
            if (draw_set_num >= model_max_set_num) {
                break;
            } else {
                pDrawActor = pDrawActor->_pNextRenderActor;
            }
        } else {
            break;
        }
    }
    pMassSpriteModel->GgafDx::MassSpriteModel::draw(this, draw_set_num);
}

DefaultMassSpriteActor::~DefaultMassSpriteActor() {
    GGAF_DELETE(_pColliChecker);
}

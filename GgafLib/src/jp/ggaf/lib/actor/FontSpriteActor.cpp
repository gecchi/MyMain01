#include "jp/ggaf/lib/actor/FontSpriteActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassSpriteEffect.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FontSpriteActor::VERTEX_instancedata FontSpriteActor::_aInstancedata[GGAFDXMASS_MAX_INSTACE_NUM];

FontSpriteActor::FontSpriteActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
            GgafDxMassSpriteActor(prm_name,
                                  prm_model_id,
                                  "FontSpriteEffect",
                                  "FontSpriteTechnique",
                                  prm_pStat,
                                  NEW CollisionChecker3D(this) ) ,
            ICharacterChip<FontSpriteActor>(this, (int)(_pMassSpriteModel->_model_width_px), (int)(_pMassSpriteModel->_model_height_px))
{
    _class_name = "FontSpriteActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _pMassSpriteModel->registerCallback_VertexInstaceDataInfo(FontSpriteActor::createVertexInstaceData);
}


void FontSpriteActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    if (_align != prm_align || _valign != prm_valign) {
        _align = prm_align;
        _valign = prm_valign;
        prepare2();
    }
}

void FontSpriteActor::setAlign(GgafDxAlign prm_align) {
    if (_align != prm_align) {
        _align = prm_align;
        prepare2();
    }
}

void FontSpriteActor::setValign(GgafDxValign prm_valign) {
    if (_valign != prm_valign) {
        _valign = prm_valign;
        prepare2();
    }
}


void FontSpriteActor::createVertexInstaceData(void* prm, GgafDxMassModel::VertexInstaceDataInfo* out_info) {
    int element_num = 7;
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
    //float local_x, local_y;     // : TEXCOORD5  ���[�J�����W�I�t�Z�b�g
    out_info->paElement[4].Stream = 1;
    out_info->paElement[4].Offset = st1_offset_next;
    out_info->paElement[4].Type   = D3DDECLTYPE_FLOAT2;
    out_info->paElement[4].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[4].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[4].UsageIndex = 5;
    st1_offset_next += sizeof(float)*2;
    //float offset_u, offset_v;   // : TEXCOORD6  �e�N�X�`���I�t�Z�b�g
    out_info->paElement[5].Stream = 1;
    out_info->paElement[5].Offset = st1_offset_next;
    out_info->paElement[5].Type   = D3DDECLTYPE_FLOAT2;
    out_info->paElement[5].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[5].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[5].UsageIndex = 6;
    st1_offset_next += sizeof(float)*2;
    //float r, g, b, a;           // : TEXCOORD7  �}�e���A���J���[
    out_info->paElement[6].Stream = 1;
    out_info->paElement[6].Offset = st1_offset_next;
    out_info->paElement[6].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[6].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[6].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[6].UsageIndex = 7;
    st1_offset_next += sizeof(float)*4;
    // <---- Stream = 1

    out_info->element_num = element_num;
    out_info->size_vertex_unit_instacedata = sizeof(FontSpriteActor::VERTEX_instancedata);
    out_info->pInstancedata = FontSpriteActor::_aInstancedata;

}

void FontSpriteActor::processDraw() {
    int draw_set_num = 0; //GgafDxMassSpriteActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    static const size_t size_of_D3DXMATRIX = sizeof(D3DXMATRIX);
    static const size_t size_of_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    GgafDxMassSpriteEffect* pMassSpriteEffect = _pMassSpriteEffect;
    GgafDxFigureActor* pDrawActor = this;
    FontSpriteActor* pFontSpriteActor = nullptr;
    int model_set_num = _pMassSpriteModel->_set_num;
    float u,v;
    VERTEX_instancedata* paInstancedata = FontSpriteActor::_aInstancedata;
    while (pDrawActor) {
        if (pDrawActor->getModel() == this->getModel() && pDrawActor->_hash_technique == this->_hash_technique) {
            pFontSpriteActor = (FontSpriteActor*)pDrawActor;
            int n = pFontSpriteActor->_draw_chr_num;
            InstacePart* pInstacePart = pFontSpriteActor->_paInstacePart;
            GgafDxSpacetime::_pActor_draw_active = pDrawActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g

            for (int i = 0; i < n; i++) {
                memcpy(paInstancedata, &(pFontSpriteActor->_matWorld), size_of_D3DXMATRIX);
                paInstancedata->local_x = PX_DX(  (pInstacePart->px_local_x ) + (pFontSpriteActor->_chr_base_width_px/2) );
                paInstancedata->local_y = PX_DX( ((pInstacePart->px_local_y ) + (pFontSpriteActor->_chr_base_height_px/2) ) * (-1) ) ; //-1�͍��W�n�̐��̌������t�̈�
                ((FontSpriteActor*)pDrawActor)->getUvFlipper()->getUV(u,v);
                paInstancedata->offset_u = pInstacePart->offset_u;
                paInstancedata->offset_v = pInstacePart->offset_v;
                memcpy(&(paInstancedata->r), &(pFontSpriteActor->_paMaterial[0].Diffuse), size_of_D3DCOLORVALUE);
                pInstacePart++;
                paInstancedata++;

                draw_set_num++;
                if (draw_set_num >= model_set_num) {
                   _pMassSpriteModel->GgafDxMassSpriteModel::draw(this, draw_set_num);
                   paInstancedata = FontSpriteActor::_aInstancedata;
                   draw_set_num = 0;
                }
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    if (draw_set_num > 0) {
        _pMassSpriteModel->GgafDxMassSpriteModel::draw(this, draw_set_num);
    }
}

FontSpriteActor::~FontSpriteActor() {
    GGAF_DELETE(_pColliChecker);
}



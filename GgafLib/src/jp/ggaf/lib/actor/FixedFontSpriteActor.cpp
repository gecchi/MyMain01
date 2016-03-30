#include "jp/ggaf/lib/actor/FixedFontSpriteActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassSpriteEffect.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FixedFontSpriteActor::VERTEX_instancedata FixedFontSpriteActor::_aInstancedata[GGAFDXMASS_MAX_INSTACE_NUM];

FixedFontSpriteActor::FixedFontSpriteActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
            GgafDxMassSpriteActor(prm_name,
                                  prm_model_id,
                                  "FontSpriteEffect",
                                  "FontSpriteTechnique",
                                  prm_pStat,
                                  NEW CollisionChecker3D(this) ) ,
            IFixedFont<FixedFontSpriteActor>(this, (int)(_pMassSpriteModel->_model_width_px), (int)(_pMassSpriteModel->_model_height_px))
{
    _class_name = "FixedFontSpriteActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _pMassSpriteModel->registerCallback_VertexInstaceDataInfo(FixedFontSpriteActor::createVertexInstaceData);
}


void FixedFontSpriteActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    if (_align != prm_align || _valign != prm_valign) {
        _align = prm_align;
        _valign = prm_valign;
        prepare2();
    }
}

void FixedFontSpriteActor::setAlign(GgafDxAlign prm_align) {
    if (_align != prm_align) {
        _align = prm_align;
        prepare2();
    }
}

void FixedFontSpriteActor::setValign(GgafDxValign prm_valign) {
    if (_valign != prm_valign) {
        _valign = prm_valign;
        prepare2();
    }
}


void FixedFontSpriteActor::createVertexInstaceData(void* prm, GgafDxMassModel::VertexInstaceDataInfo* out_info) {
    int element_num = 7;
    out_info->paElement = NEW D3DVERTEXELEMENT9[element_num];
    // Stream = 1 ---->
    WORD st1_offset_next = 0;
    //float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目
    out_info->paElement[0].Stream = 1;
    out_info->paElement[0].Offset = st1_offset_next;
    out_info->paElement[0].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[0].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[0].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[0].UsageIndex = 1;
    st1_offset_next += sizeof(float)*4;
    //float _21, _22, _23, _24;  // : TEXCOORD2  World変換行列、２行目
    out_info->paElement[1].Stream = 1;
    out_info->paElement[1].Offset = st1_offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[1].UsageIndex = 2;
    st1_offset_next += sizeof(float)*4;
    //float _31, _32, _33, _34;  // : TEXCOORD3  World変換行列、３行目
    out_info->paElement[2].Stream = 1;
    out_info->paElement[2].Offset = st1_offset_next;
    out_info->paElement[2].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[2].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[2].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[2].UsageIndex = 3;
    st1_offset_next += sizeof(float)*4;
    //float _41, _42, _43, _44;  // : TEXCOORD4  World変換行列、４行目
    out_info->paElement[3].Stream = 1;
    out_info->paElement[3].Offset = st1_offset_next;
    out_info->paElement[3].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[3].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[3].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[3].UsageIndex = 4;
    st1_offset_next += sizeof(float)*4;
    //float local_x, local_y;     // : TEXCOORD5  ローカル座標オフセット
    out_info->paElement[4].Stream = 1;
    out_info->paElement[4].Offset = st1_offset_next;
    out_info->paElement[4].Type   = D3DDECLTYPE_FLOAT2;
    out_info->paElement[4].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[4].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[4].UsageIndex = 5;
    st1_offset_next += sizeof(float)*2;
    //float offset_u, offset_v;   // : TEXCOORD6  テクスチャオフセット
    out_info->paElement[5].Stream = 1;
    out_info->paElement[5].Offset = st1_offset_next;
    out_info->paElement[5].Type   = D3DDECLTYPE_FLOAT2;
    out_info->paElement[5].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[5].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[5].UsageIndex = 6;
    st1_offset_next += sizeof(float)*2;
    //float r, g, b, a;           // : TEXCOORD7  マテリアルカラー
    out_info->paElement[6].Stream = 1;
    out_info->paElement[6].Offset = st1_offset_next;
    out_info->paElement[6].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[6].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[6].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[6].UsageIndex = 7;
    st1_offset_next += sizeof(float)*4;
    // <---- Stream = 1

    out_info->element_num = element_num;
    out_info->size_vertex_unit_instacedata = sizeof(FixedFontSpriteActor::VERTEX_instancedata);
    out_info->pInstancedata = FixedFontSpriteActor::_aInstancedata;

}

void FixedFontSpriteActor::processDraw() {
    int draw_set_num = 0; //GgafDxMassSpriteActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    static const size_t size_of_D3DXMATRIX = sizeof(D3DXMATRIX);
    static const size_t size_of_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    GgafDxMassSpriteEffect* pMassSpriteEffect = _pMassSpriteEffect;
    GgafDxFigureActor* pDrawActor = this;
    FixedFontSpriteActor* pFixedFontSpriteActor = nullptr;
    int model_set_num = _pMassSpriteModel->_set_num;
    float u,v;
    VERTEX_instancedata* paInstancedata = FixedFontSpriteActor::_aInstancedata;
    while (pDrawActor) {
        if (pDrawActor->getModel() == this->getModel() && pDrawActor->_hash_technique == this->_hash_technique) {
            pFixedFontSpriteActor = (FixedFontSpriteActor*)pDrawActor;
            int n = pFixedFontSpriteActor->_draw_chr_num;
            InstacePart* pInstacePart = pFixedFontSpriteActor->_paInstacePart;
            GgafDxSpacetime::_pActor_draw_active = pDrawActor; //描画セットの最後アクターをセット

            for (int i = 0; i < n; i++) {
                memcpy(paInstancedata, &(pFixedFontSpriteActor->_matWorld), size_of_D3DXMATRIX);
                paInstancedata->local_x = PX_DX(  (pInstacePart->px_local_x ) + (pFixedFontSpriteActor->_chr_width_px/2)           );
                paInstancedata->local_y = PX_DX( ((pInstacePart->px_local_y ) + (pFixedFontSpriteActor->_chr_height_px/2) ) * (-1) ) ;
                ((FixedFontSpriteActor*)pDrawActor)->getUvFlipper()->getUV(u,v);
                paInstancedata->offset_u = pInstacePart->offset_u;
                paInstancedata->offset_v = pInstacePart->offset_v;
                memcpy(&(paInstancedata->r), &(pFixedFontSpriteActor->_paMaterial[0].Diffuse), size_of_D3DCOLORVALUE);
                pInstacePart++;
                paInstancedata++;

                draw_set_num++;
                if (draw_set_num >= model_set_num) {
                   _pMassSpriteModel->GgafDxMassSpriteModel::draw(this, draw_set_num);
                   paInstancedata = FixedFontSpriteActor::_aInstancedata;
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

FixedFontSpriteActor::~FixedFontSpriteActor() {
    GGAF_DELETE(_pColliChecker);
    GGAF_DELETEARR(_buf);
    GGAF_DELETEARR(_paInstacePart);
}



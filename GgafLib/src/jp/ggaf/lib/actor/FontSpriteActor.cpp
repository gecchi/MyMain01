#include "jp/ggaf/lib/actor/FontSpriteActor.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/MassSpriteEffect.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

FontSpriteActor::VERTEX_instancedata FontSpriteActor::_aInstancedata[GGAFDXMASS_MAX_INSTANCE_NUM];

FontSpriteActor::FontSpriteActor(const char* prm_name, const char* prm_model) :
            GgafDx::MassSpriteActor(prm_name,
                                    prm_model,
                                    "FontSpriteEffect",
                                    "FontSpriteTechnique",
                                    UTIL::createCollisionChecker(this) ) ,
            ICharacterChip<FontSpriteActor, 256, 1024>(this, (int)(_pMassSpriteModel->_model_width_px), (int)(_pMassSpriteModel->_model_height_px))
{
    _class_name = "FontSpriteActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
    _align = ALIGN_CENTER;
    _valign = VALIGN_MIDDLE;
    _pMassSpriteModel->registerCallback_VertexInstanceDataInfo(FontSpriteActor::createVertexInstanceData);
}


void FontSpriteActor::setAlign(Align prm_align, Valign prm_valign) {
    if (_align != prm_align || _valign != prm_valign) {
        _align = prm_align;
        _valign = prm_valign;
        prepare2();
    }
}

void FontSpriteActor::setAlign(Align prm_align) {
    if (_align != prm_align) {
        _align = prm_align;
        prepare2();
    }
}

void FontSpriteActor::setValign(Valign prm_valign) {
    if (_valign != prm_valign) {
        _valign = prm_valign;
        prepare2();
    }
}


void FontSpriteActor::createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info) {
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
    out_info->size_vertex_unit_instancedata = sizeof(FontSpriteActor::VERTEX_instancedata);
    out_info->pInstancedata = FontSpriteActor::_aInstancedata;

}

void FontSpriteActor::processDraw() {
    int draw_set_num = 0; //MassSpriteActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    static const size_t size_of_D3DXMATRIX = sizeof(D3DXMATRIX);
    static const size_t size_of_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    GgafDx::FigureActor* pDrawActor = this;
    FontSpriteActor* pFontSpriteActor = nullptr;
    int model_draw_set_num = _pMassSpriteModel->_draw_set_num;
    float u,v;
    VERTEX_instancedata* paInstancedata = FontSpriteActor::_aInstancedata;
    while (pDrawActor) {
        if (pDrawActor->getModel() == this->getModel() && pDrawActor->_hash_technique == this->_hash_technique) {
            pFontSpriteActor = (FontSpriteActor*)pDrawActor;
            int n = pFontSpriteActor->_draw_chr_num;
            InstancePart* pInstancePart = pFontSpriteActor->_paInstancePart;
            for (int i = 0; i < n; i++) {
                memcpy(paInstancedata, &(pFontSpriteActor->_matWorld), size_of_D3DXMATRIX);
                paInstancedata->local_x = PX_DX(  (pInstancePart->px_local_x ) + (pFontSpriteActor->_chr_base_width_px /2) );
                paInstancedata->local_y = PX_DX( ((pInstancePart->px_local_y ) + (pFontSpriteActor->_chr_base_height_px/2) ) * (-1) ); //-1は座標系の正の向きが逆の為
                ((FontSpriteActor*)pDrawActor)->getUvFlipper()->getUV(u,v);
                paInstancedata->offset_u = pInstancePart->offset_u;
                paInstancedata->offset_v = pInstancePart->offset_v;
                memcpy(&(paInstancedata->r), &(pFontSpriteActor->_paMaterial[0].Diffuse), size_of_D3DCOLORVALUE);
                ++pInstancePart;
                ++paInstancedata;

                draw_set_num++;
                if (draw_set_num >= model_draw_set_num) {
                   _pMassSpriteModel->GgafDx::MassSpriteModel::draw(this, draw_set_num);
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
        _pMassSpriteModel->GgafDx::MassSpriteModel::draw(this, draw_set_num);
    }
    _pNextRenderActor = pDrawActor;
}


void FontSpriteActor::addModel(const char* prm_model) {
    MassSpriteActor::addModel(prm_model);
    GgafDx::MassSpriteModel* pModel = (GgafDx::MassSpriteModel*)_lstModel.back(); //今追加したモデル
    pModel->registerCallback_VertexInstanceDataInfo(FontSpriteActor::createVertexInstanceData);
}

FontSpriteActor::~FontSpriteActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}



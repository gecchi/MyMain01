#include "jp/ggaf/lib/actor/DefaultMassSpriteActor.h"

#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#ifdef MY_DEBUG
#include "jp/ggaf/lib/actor/ColliAABoxActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliAAPyramidActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#endif

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultMassSpriteActor::VERTEX_instancedata DefaultMassSpriteActor::_aInstancedata[GGAFDXMASS_MAX_INSTACE];

DefaultMassSpriteActor::DefaultMassSpriteActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
    GgafDxMassSpriteActor(prm_name,
                          prm_model_id,
                          "DefaultMassSpriteEffect",
                          "DefaultMassSpriteTechnique",
                          prm_pStat,
                          NEW CollisionChecker3D(this) ) {

    _class_name = "DefaultMassSpriteActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _pMassSpriteModel->registerCallback_VertexInstaceDataInfo(DefaultMassSpriteActor::createVertexInstaceData);
    setZWriteEnable(false);
}

void DefaultMassSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliAAPyramidActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
#endif
}

void DefaultMassSpriteActor::createVertexInstaceData(GgafDxMassModel::VertexInstaceDataInfo* out_info) {
    int element_num = 5;
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
    //float offset_u, offset_v, force_alpha;   // : TEXCOORD5  テクスチャオフセット、強制α
    out_info->paElement[4].Stream = 1;
    out_info->paElement[4].Offset = st1_offset_next;
    out_info->paElement[4].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[4].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[4].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[4].UsageIndex = 5;
    st1_offset_next += sizeof(float)*3;
    // <---- Stream = 1

    out_info->element_num = element_num;
    out_info->size_vertex_unit_instacedata = sizeof(DefaultMassSpriteActor::VERTEX_instancedata);
    out_info->pInstancedata = DefaultMassSpriteActor::_aInstancedata;
}

void DefaultMassSpriteActor::processDraw() {
    int draw_set_num = 0; //GgafDxMassSpriteActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    HRESULT hr;
    const int model_max_set_num = _pMassSpriteModel->_set_num;
    const hashval hash_technique = _hash_technique;
    VERTEX_instancedata* paInstancedata = DefaultMassSpriteActor::_aInstancedata;
    GgafDxFigureActor* pDrawActor = this;
    static const size_t SIZE_D3DXMATRIX = sizeof(D3DXMATRIX);
    static const size_t SIZE_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);

    float u,v;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMassSpriteModel && pDrawActor->_hash_technique == hash_technique) {
            if (_align == ALIGN_CENTER) {
                //do nothing
            } else if (_align == ALIGN_LEFT) {
                pDrawActor->_matWorld._41 += PX_C(_pMassSpriteModel->_model_width_px/2);
            } else {
                //ALIGN_RIGHT
                pDrawActor->_matWorld._41 -= PX_C(_pMassSpriteModel->_model_width_px/2);
            }
            if (_valign == VALIGN_MIDDLE) {
                //do nothing
            } else if (_valign == VALIGN_TOP) {
                pDrawActor->_matWorld._42 -= PX_C(_pMassSpriteModel->_model_height_px/2);
            } else {
                //VALIGN_BOTTOM
                pDrawActor->_matWorld._42 += PX_C(_pMassSpriteModel->_model_height_px/2);
            }

            memcpy(paInstancedata, &(pDrawActor->_matWorld), SIZE_D3DXMATRIX);
            ((DefaultMassSpriteActor*)pDrawActor)->getUvFlipper()->getUV(u,v);
            paInstancedata->offset_u = u;
            paInstancedata->offset_v = v;
            paInstancedata->alpha = pDrawActor->_alpha;
            paInstancedata++;

            draw_set_num++;
            GgafDxSpacetime::_pActor_draw_active = pDrawActor; //描画セットの最後アクターをセット
            if (draw_set_num >= model_max_set_num) {
                break;
            } else {
                pDrawActor = pDrawActor->_pNextRenderActor;
            }
        } else {
            break;
        }
    }
    _pMassSpriteModel->GgafDxMassSpriteModel::draw(this, draw_set_num);
}

DefaultMassSpriteActor::~DefaultMassSpriteActor() {
    GGAF_DELETE(_pColliChecker);
}

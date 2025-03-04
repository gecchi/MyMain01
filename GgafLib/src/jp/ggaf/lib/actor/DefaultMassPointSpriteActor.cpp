#include "jp/ggaf/lib/actor/DefaultMassPointSpriteActor.h"

#include "jp/ggaf/lib/DefaultCaretaker.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/exception/CriticalException.h"



using namespace GgafLib;


DefaultMassPointSpriteActor::VERTEX_instancedata DefaultMassPointSpriteActor::_aInstancedata[GGAFDXMASS_MAX_INSTANCE_NUM];

DefaultMassPointSpriteActor::DefaultMassPointSpriteActor(const char* prm_name, const char* prm_model) :
    GgafDx::MassPointSpriteActor(prm_name,
                        prm_model,
                        "DefaultMassPointSpriteEffect",
                        "DefaultMassPointSpriteTechnique") {
    _class_name = "DefaultMassPointSpriteActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
    _pMassPointSpriteModel->registerCallback_VertexInstanceDataInfo(DefaultMassPointSpriteActor::createVertexInstanceData);
}

void DefaultMassPointSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

void DefaultMassPointSpriteActor::createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info) {
    int element_num = 6;
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
    //float r, g, b, a;        // : TEXCOORD5  マテリアルカラー
    out_info->paElement[4].Stream = 1;
    out_info->paElement[4].Offset = st1_offset_next;
    out_info->paElement[4].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[4].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[4].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[4].UsageIndex = 5;
    st1_offset_next += sizeof(float)*4;
    //float pattno_uvflip_now;  // : TEXCOORD6
    out_info->paElement[5].Stream = 1;
    out_info->paElement[5].Offset = st1_offset_next;
    out_info->paElement[5].Type   = D3DDECLTYPE_FLOAT1;
    out_info->paElement[5].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[5].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[5].UsageIndex = 6;
    st1_offset_next += sizeof(float)*1;
    // <---- Stream = 1

    out_info->element_num = element_num;
    out_info->size_vertex_unit_instancedata = sizeof(DefaultMassPointSpriteActor::VERTEX_instancedata);
    out_info->pInstancedata = DefaultMassPointSpriteActor::_aInstancedata;
}


void DefaultMassPointSpriteActor::processDraw() {


    HRESULT hr = pCARETAKER->_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE); //ポイントスプライトON！
    checkDxException(hr, D3D_OK, " D3DRS_POINTSPRITEENABLE TRUE に失敗しました。");


    int draw_set_num = 0; //MassPointSpriteActorの同じモデルで同じテクニックが
                          //連続しているカウント数。同一描画深度は一度に描画する。
    GgafDx::MassPointSpriteModel* pMassPointSpriteModel = _pMassPointSpriteModel;
    const int model_max_draw_set_num = pMassPointSpriteModel->_draw_set_num;
    const hashval hash_technique = _hash_technique;

    static const size_t size_of_D3DXMATRIX = sizeof(D3DXMATRIX);
    static const size_t size_of_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    DefaultMassPointSpriteActor::VERTEX_instancedata* paInstancedata = DefaultMassPointSpriteActor::_aInstancedata;

    GgafDx::FigureActor* pDrawActor = this;
    while (pDrawActor) {
        if (pDrawActor->getModel() == pMassPointSpriteModel && pDrawActor->_hash_technique == hash_technique) {
            memcpy(paInstancedata, &(pDrawActor->_matWorld), size_of_D3DXMATRIX);
            memcpy(&(paInstancedata->r), &(pDrawActor->_paMaterial[0].Diffuse), size_of_D3DCOLORVALUE);
            paInstancedata->pattno_uvflip_now = ((DefaultMassPointSpriteActor*)pDrawActor)->getUvFlipper()->_pattno_uvflip_now;
            ++paInstancedata;

            pDrawActor = pDrawActor->_pNextRenderActor;
            draw_set_num++;
            if (draw_set_num >= model_max_draw_set_num) {
                break;
            }
        } else {
            break;
        }
    }
    ((GgafDx::MassPointSpriteModel*)_pMassPointSpriteModel)->GgafDx::MassPointSpriteModel::draw(this, draw_set_num);
    _pNextRenderActor = pDrawActor;
    hr = pCARETAKER->_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE); //ポイントスプライトOFF
    checkDxException(hr, D3D_OK, " D3DRS_POINTSPRITEENABLE FALSE に失敗しました。");
}

void DefaultMassPointSpriteActor::addModel(const char* prm_model) {
    MassPointSpriteActor::addModel(prm_model);
    GgafDx::MassPointSpriteModel* pModel = (GgafDx::MassPointSpriteModel*)_lstModel.back(); //今追加したモデル
    pModel->registerCallback_VertexInstanceDataInfo(DefaultMassPointSpriteActor::createVertexInstanceData);
}

GgafDx::CollisionChecker* DefaultMassPointSpriteActor::createChecker(kind_t prm_kind) {
    return UTIL::createCollisionChecker(this, prm_kind);
}

DefaultMassPointSpriteActor::~DefaultMassPointSpriteActor() {
}

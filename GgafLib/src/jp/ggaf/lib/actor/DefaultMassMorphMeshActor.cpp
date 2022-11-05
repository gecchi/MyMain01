#include "jp/ggaf/lib/actor/DefaultMassMorphMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/model/MassMorphMeshModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"



using namespace GgafLib;

DefaultMassMorphMeshActor::VERTEX_instancedata DefaultMassMorphMeshActor::_aInstancedata[GGAFDXMASS_MAX_INSTANCE_NUM];

DefaultMassMorphMeshActor::DefaultMassMorphMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::MassMorphMeshActor(prm_name,
                               prm_model,
                               "DefaultMassMorphMeshEffect",
                               "DefaultMassMorphMeshTechnique",
                               UTIL::createCollisionChecker(this) ) {
    _class_name = "DefaultMassMorphMeshActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
    _pMassMorphMeshModel->registerCallback_VertexInstanceDataInfo(DefaultMassMorphMeshActor::createVertexInstanceData);
}

void DefaultMassMorphMeshActor::createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info) {
    GgafDx::MassMorphMeshModel* pModel = (GgafDx::MassMorphMeshModel*)prm;
    int morph_target_num = pModel->_morph_target_num;
    int s = morph_target_num + 1;

    int element_num = 5;// + (morph_target_num+1);
    out_info->paElement = NEW D3DVERTEXELEMENT9[element_num];
    // Stream = 1 ---->
    WORD offset_next = 0;
    //float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目
    out_info->paElement[0].Stream = s;
    out_info->paElement[0].Offset = offset_next;
    out_info->paElement[0].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[0].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[0].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[0].UsageIndex = 1;
    offset_next += sizeof(float)*4;
    //float _21, _22, _23, _24;  // : TEXCOORD2  World変換行列、２行目
    out_info->paElement[1].Stream = s;
    out_info->paElement[1].Offset = offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[1].UsageIndex = 2;
    offset_next += sizeof(float)*4;
    //float _31, _32, _33, _34;  // : TEXCOORD3  World変換行列、３行目
    out_info->paElement[2].Stream = s;
    out_info->paElement[2].Offset = offset_next;
    out_info->paElement[2].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[2].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[2].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[2].UsageIndex = 3;
    offset_next += sizeof(float)*4;
    //float _41, _42, _43, _44;  // : TEXCOORD4  World変換行列、４行目
    out_info->paElement[3].Stream = s;
    out_info->paElement[3].Offset = offset_next;
    out_info->paElement[3].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[3].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[3].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[3].UsageIndex = 4;
    offset_next += sizeof(float)*4;
    //float r, g, b, a;        // : TEXCOORD5  マテリアルカラー
    out_info->paElement[4].Stream = s;
    out_info->paElement[4].Offset = offset_next;
    out_info->paElement[4].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[4].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[4].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[4].UsageIndex = 5;
    offset_next += sizeof(float)*4;

    out_info->element_num = element_num;
    out_info->pInstancedata = DefaultMassMorphMeshActor::_aInstancedata;
    out_info->size_vertex_unit_instancedata = sizeof(DefaultMassMorphMeshActor::VERTEX_instancedata);
}

void DefaultMassMorphMeshActor::processDraw() {
    int draw_set_num = 0; //MassMorphMeshActorの同じモデルで同じテクニックが
                          //連続しているカウント数。同一描画深度は一度に描画する。
    GgafDx::MassMorphMeshModel* pMassMorphMeshModel = _pMassMorphMeshModel;
    const int model_max_draw_set_num = pMassMorphMeshModel->_draw_set_num;
    const hashval hash_technique = _hash_technique;
    int morph_target_num = pMassMorphMeshModel->_morph_target_num;
    static const size_t size_of_D3DXMATRIX = sizeof(D3DXMATRIX);
    static const size_t size_of_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    VERTEX_instancedata* paInstancedata = DefaultMassMorphMeshActor::_aInstancedata;
    GgafDx::FigureActor* pDrawActor = this;
    while (pDrawActor) {
        if (pDrawActor->getModel() == pMassMorphMeshModel && pDrawActor->_hash_technique == hash_technique) {
            //_hash_techniqueが同じだと、モーフターゲット数も同じである
            DefaultMassMorphMeshActor* p = (DefaultMassMorphMeshActor*)pDrawActor;
            memcpy(paInstancedata, &(pDrawActor->_matWorld), size_of_D3DXMATRIX);
            //インスタンスデータのワールド変換行列の要素(_14 _24 _34 _44)に、
            //重みの値(_weight[1] ～_weight [4]) を埋め込んでシェーダー渡す。
            //入力レジスタ数が最大16である都合で、MAXモーフターゲットは4が限界
            if (morph_target_num >= 1) {
                paInstancedata->_14 = p->_weight[1];
                if (morph_target_num >= 2) {
                    paInstancedata->_24 = p->_weight[2];
                    if (morph_target_num >= 3) {
                        paInstancedata->_34 = p->_weight[3];
                        if (morph_target_num >= 4) {
                            paInstancedata->_44 = p->_weight[4];
                        }
                    }
                }
            }
            memcpy(&(paInstancedata->r), &(pDrawActor->_paMaterial[0].Diffuse), size_of_D3DCOLORVALUE);

            ++paInstancedata;
            draw_set_num++;
            GgafDx::Spacetime::_pActor_draw_active = pDrawActor; //描画セットの最後アクターをセット
            if (draw_set_num >= model_max_draw_set_num) {
                break;
            } else {
                pDrawActor = pDrawActor->_pNextRenderActor;
            }
        } else {
            break;
        }
    }
    ((GgafDx::MassMorphMeshModel*)_pMassMorphMeshModel)->GgafDx::MassMorphMeshModel::draw(this, draw_set_num);
}
void DefaultMassMorphMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

DefaultMassMorphMeshActor::~DefaultMassMorphMeshActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}

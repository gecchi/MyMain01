#include "jp/ggaf/lib/actor/DefaultMassPointSpriteActor.h"

#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/exception/CriticalException.h"



using namespace GgafLib;


DefaultMassPointSpriteActor::VERTEX_instancedata DefaultMassPointSpriteActor::_aInstancedata[GGAFDXMASS_MAX_INSTANCE_NUM];

DefaultMassPointSpriteActor::DefaultMassPointSpriteActor(const char* prm_name, const char* prm_model) :
    GgafDx::MassPointSpriteActor(prm_name,
                        prm_model,
                        "DefaultMassPointSpriteEffect",
                        "DefaultMassPointSpriteTechnique",
                        UTIL::createChecker(this) ) {
    _class_name = "DefaultMassPointSpriteActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
    _pMassPointSpriteModel->registerCallback_VertexInstanceDataInfo(DefaultMassPointSpriteActor::createVertexInstanceData);
}

void DefaultMassPointSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

void DefaultMassPointSpriteActor::createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info) {
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
    //float r, g, b, a;        // : TEXCOORD5  �}�e���A���J���[
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


    HRESULT hr = GgafDx::God::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE); //�|�C���g�X�v���C�gON�I
    checkDxException(hr, D3D_OK, " D3DRS_POINTSPRITEENABLE TRUE �Ɏ��s���܂����B");


    int draw_set_num = 0; //MassPointSpriteActor�̓������f���œ����e�N�j�b�N��
                          //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
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
            draw_set_num++;
            GgafDx::Spacetime::_pActor_draw_active = pDrawActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
            if (draw_set_num >= model_max_draw_set_num) {
                break;
            } else {
                pDrawActor = pDrawActor->_pNextRenderActor;
            }
        } else {
            break;
        }
    }

    ((GgafDx::MassPointSpriteModel*)_pMassPointSpriteModel)->GgafDx::MassPointSpriteModel::draw(this, draw_set_num);

    hr = GgafDx::God::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE); //�|�C���g�X�v���C�gOFF
    checkDxException(hr, D3D_OK, " D3DRS_POINTSPRITEENABLE FALSE �Ɏ��s���܂����B");
}

DefaultMassPointSpriteActor::~DefaultMassPointSpriteActor() {
    GGAF_DELETE(_pColliChecker);
}

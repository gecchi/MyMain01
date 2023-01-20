#include "jp/ggaf/lib/actor/wall/MassWallActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/scene/WallSectionScene.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"
#include "jp/ggaf/dx/effect/Effect.h"
#include "jp/ggaf/lib/effect/MassWallEffect.h"


using namespace GgafLib;


std::map<int, UINT> MassWallActor::_draw_face;
MassWallActor::VERTEX_instancedata MassWallActor::_aInstancedata[GGAFDXMASS_MAX_INSTANCE_NUM];

MassWallActor::MassWallActor(const char* prm_name,
                             const char* prm_model) :

                                 GgafDx::MassMeshActor(prm_name,
                                                     prm_model,
                                                     TYPE_MASSMESH_MODEL,
                                                     "MassWallEffect",
                                                     TYPE_MASSWALL_EFFECT,
                                                     "MassWallTechnique",
                                                     UTIL::createCollisionChecker(this))
{
    init();
}

MassWallActor::MassWallActor(const char* prm_name,
                             const char* prm_model,
                             const char* prm_effect,
                             const char* prm_technique) :

                                 GgafDx::MassMeshActor(prm_name,
                                                     prm_model,
                                                     TYPE_MASSMESH_MODEL,
                                                     prm_effect,
                                                     TYPE_MASSWALL_EFFECT,
                                                     prm_technique,
                                                     UTIL::createCollisionChecker(this))
{
    init();
}

void MassWallActor::init() {
    _class_name = "MassWallActor";
    _obj_class |= Obj_MassWallActor;
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
    _wall_draw_face = 0;
    _pos_info = 0;
    _pWallSectionScene = nullptr;

    _wall_dep = 0;
    _wall_width = 0;
    _wall_height = 0;
    setHitAble(true);

    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->createCollisionArea(3);
    pChecker->setColliAABox(0, 0,0,0, 0,0,0);
    pChecker->setColliAAPrism(1, 0,0,0, 0,0,0, 0);
    pChecker->setColliAAPyramid(2, 0,0,0, 0,0,0, POS_PYRAMID_NNN);
    _pMassMeshModel->registerCallback_VertexInstanceDataInfo(MassWallActor::createVertexInstanceData);

    static volatile bool is_init = MassWallActor::initStatic(this); //静的メンバ初期化
}

bool MassWallActor::initStatic(MassWallActor* prm_pMassWallActor) {
    //プリズム壁であるならば、形状により無条件で描画不要面がある、
    //    c
    // a b d f
    //      e
    //                 00abcdef
    //
    //    FACE_A_BIT = 32 = 0b100000
    //    FACE_B_BIT = 16 = 0b010000
    //    FACE_C_BIT = 8  = 0b001000
    //    FACE_D_BIT = 4  = 0b000100
    //    FACE_E_BIT = 2  = 0b000010
    //    FACE_F_BIT = 1  = 0b000001
    //
    //無条件で不要な面ビットを 0
    //特に条件がない場合、描画する面ビットを 1
    //に設定

    //XYプリズムの場合は +X -X面をつぶす
    MassWallActor::_draw_face[POS_PRISM_XY_NN] = ~FACE_F_BIT;
    MassWallActor::_draw_face[POS_PRISM_XY_NP] = ~FACE_F_BIT;
    MassWallActor::_draw_face[POS_PRISM_XY_PN] = ~FACE_B_BIT;
    MassWallActor::_draw_face[POS_PRISM_XY_PP] = ~FACE_B_BIT;

    //YZプリズムの場合も +Z -Z面をつぶす
    MassWallActor::_draw_face[POS_PRISM_YZ_NN] = ~FACE_C_BIT;
    MassWallActor::_draw_face[POS_PRISM_YZ_NP] = ~FACE_E_BIT;
    MassWallActor::_draw_face[POS_PRISM_YZ_PN] = ~FACE_C_BIT;
    MassWallActor::_draw_face[POS_PRISM_YZ_PP] = ~FACE_E_BIT;

    //ZXプリズムの場合も +X -X面をつぶす
    MassWallActor::_draw_face[POS_PRISM_ZX_NN] = ~FACE_F_BIT;
    MassWallActor::_draw_face[POS_PRISM_ZX_NP] = ~FACE_B_BIT;
    MassWallActor::_draw_face[POS_PRISM_ZX_PN] = ~FACE_F_BIT;
    MassWallActor::_draw_face[POS_PRISM_ZX_PP] = ~FACE_B_BIT;


    //ピラミッドであるならば、形状により無条件で描画不要面がある、
    //    c
    // a b d f
    //      e
    //                 00abcdef
    //
    //    FACE_A_BIT = 32 = 0b100000
    //    FACE_B_BIT = 16 = 0b010000
    //    FACE_C_BIT = 8  = 0b001000
    //    FACE_D_BIT = 4  = 0b000100
    //    FACE_E_BIT = 2  = 0b000010
    //    FACE_F_BIT = 1  = 0b000001
    //
    //無条件で不要な面ビットを 0
    //特に条件がない場合、描画する面ビットを 1
    //に設定
    MassWallActor::_draw_face[POS_PYRAMID_NNN] = ~(FACE_C_BIT | FACE_F_BIT);
    MassWallActor::_draw_face[POS_PYRAMID_NNP] = ~(FACE_E_BIT | FACE_F_BIT);
    MassWallActor::_draw_face[POS_PYRAMID_NPN] = ~(FACE_C_BIT | FACE_F_BIT);
    MassWallActor::_draw_face[POS_PYRAMID_NPP] = ~(FACE_E_BIT | FACE_F_BIT);
    MassWallActor::_draw_face[POS_PYRAMID_PNN] = ~(FACE_B_BIT | FACE_C_BIT);
    MassWallActor::_draw_face[POS_PYRAMID_PNP] = ~(FACE_B_BIT | FACE_E_BIT);
    MassWallActor::_draw_face[POS_PYRAMID_PPN] = ~(FACE_B_BIT | FACE_C_BIT);
    MassWallActor::_draw_face[POS_PYRAMID_PPP] = ~(FACE_B_BIT | FACE_E_BIT);

    return true;
}

void MassWallActor::createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info) {
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

    //float _wall_draw_face, _pos_info;  // : TEXCOORD6 壁ブロックプリズム位置情報, 壁ブロック表示面
    out_info->paElement[5].Stream = 1;
    out_info->paElement[5].Offset = st1_offset_next;
    out_info->paElement[5].Type   = D3DDECLTYPE_FLOAT2;
    out_info->paElement[5].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[5].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[5].UsageIndex = 6;
    st1_offset_next += sizeof(float)*2;
    // <---- Stream = 1

    out_info->element_num = element_num;
    out_info->size_vertex_unit_instancedata = sizeof(MassWallActor::VERTEX_instancedata);
    out_info->pInstancedata = MassWallActor::_aInstancedata;
}

void MassWallActor::executeHitChk_MeAnd(GgafCore::Actor* prm_pOtherActor) {
    if ((prm_pOtherActor->_obj_class & Obj_LaserChip) == Obj_LaserChip) {
        LaserChip* pLaserChip = (LaserChip*)prm_pOtherActor;
        if (pLaserChip->getInfrontChip() == nullptr) {
            //相手が先端チップだけ地形ブロックと判定
            GgafDx::FigureActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDx::FigureActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void MassWallActor::initialize() {
}

void MassWallActor::onActive() {
}

void MassWallActor::processBehavior() {
}

void MassWallActor::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void MassWallActor::processPreDraw() {
    if (_wall_draw_face > 0) {
        //描画面がある場合は表示対象にする
        GgafDx::FigureActor::processPreDraw();
    }
}

void MassWallActor::processDraw() {
    HRESULT hr;
    MassWallEffect* pMassWallEffect = (MassWallEffect*)_pMassMeshEffect;
    ID3DXEffect* pID3DXEffect = pMassWallEffect->_pID3DXEffect;
    dxcoord wall_dep    = C_DX(_wall_dep)/_rate_of_bounding_sphere_radius;
    dxcoord wall_height = C_DX(_wall_height)/_rate_of_bounding_sphere_radius;
    dxcoord wall_width  = C_DX(_wall_width)/_rate_of_bounding_sphere_radius;
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_wall_dep, wall_dep);
    checkDxException(hr, D3D_OK, "SetFloat(_h_wall_dep) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_wall_height, wall_height);
    checkDxException(hr, D3D_OK, "SetFloat(_h_wall_height) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_wall_width, wall_width);
    checkDxException(hr, D3D_OK, "SetFloat(_h_wall_width) に失敗しました。");
    if (_pWallSectionScene->_pActor_infront_alpha_target) {
        hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_distance_AlphaTarget, -(_pWallSectionScene->_pActor_infront_alpha_target->_dest_from_vppln_infront));
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    } else {
        hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_distance_AlphaTarget, PX_DX(1));
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    }
    //	ah = g_wall_width / g_wall_dep / 2.0; //傾き z/x （傾き x/z ではなくて）
    //	fh = g_wall_dep/2.0;                  //傾く軸
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_ah_POS_ZX, wall_width/wall_dep/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_ah_POS_ZX) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_fh_POS_ZX, wall_dep/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_fh_POS_ZX) に失敗しました。");
    //	ah = g_wall_height / g_wall_width / 2.0; //傾き y/z
    //	fh = g_wall_width/2.0;                   //傾く軸
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_ah_POS_YZ, wall_height/wall_width/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_ah_POS_YZ) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_fh_POS_YZ, wall_width/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_fh_POS_YZ) に失敗しました。");
    //	ah = g_wall_height / g_wall_dep / 2.0; //傾き y/x
    //	fh = g_wall_dep/2.0;                   //傾く軸
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_ah_POS_XY, wall_height/wall_dep/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_ah_POS_XY) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_fh_POS_XY, wall_dep/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_fh_POS_XY) に失敗しました。");

    int draw_set_num = 0; //MassMeshActorの同じモデルで同じテクニックが
                          //連続しているカウント数。同一描画深度は一度に描画する。
    GgafDx::MassMeshModel* pMassMeshModel = _pMassMeshModel;
    const int model_max_draw_set_num = pMassMeshModel->_draw_set_num;
    const hashval hash_technique = _hash_technique;

    static const size_t size_of_D3DXMATRIX = sizeof(D3DXMATRIX);
    static const size_t size_of_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    VERTEX_instancedata* paInstancedata = MassWallActor::_aInstancedata;
    MassWallActor* pMassWallActor = nullptr;
    GgafDx::FigureActor* pDrawActor = this;
    while (pDrawActor) {
        if (pDrawActor->getModel() == pMassMeshModel && pDrawActor->_hash_technique == hash_technique) {
            pMassWallActor = (MassWallActor*)pDrawActor;
            memcpy(paInstancedata, &(pDrawActor->_matWorld), size_of_D3DXMATRIX); //TEXCOORD1 ～ TEXCOORD4
            memcpy(&(paInstancedata->r), &(pDrawActor->_paMaterial[0].Diffuse), size_of_D3DCOLORVALUE); //TEXCOORD5
            paInstancedata->_wall_draw_face = pMassWallActor->_wall_draw_face; //TEXCOORD6
            paInstancedata->_pos_info =  pMassWallActor->_pos_info;            //TEXCOORD6
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
    ((GgafDx::MassMeshModel*)_pMassMeshModel)->GgafDx::MassMeshModel::draw(this, draw_set_num);
    _pNextRenderActor = pDrawActor;
}

bool MassWallActor::isOutOfSpacetime() const {
    GgafDx::Spacetime* pSpacetime =  pCARETAKER->getSpacetime();
    if (pSpacetime->_x_bound_left <= _x+_wall_dep) {
        return false;
    }
    return true;
}

int MassWallActor::isOutOfView() {
    if (_offscreen_kind == -1) {
        dxcoord bound = getModel()->_bounding_sphere_radius * _rate_of_bounding_sphere_radius*2.0f;//掛ける2は境界球を大きくして、画面境界のチラツキを抑える
        if (_dest_from_vppln_top < bound) {
            if (_dest_from_vppln_bottom < bound) {
                if (_dest_from_vppln_left < bound) {
                    if (_dest_from_vppln_right < bound) {
                        if (_dest_from_vppln_infront < bound) {
                            //if (_dest_from_vppln_back < bound) {
                            //    //Viewport範囲内
                            //    _offscreen_kind = 0;
                            //} else {
                            //    //奥平面より奥で範囲外
                            //    _offscreen_kind = 6;
                            //}

                            //奥平面判定は無し
                            _offscreen_kind = 0;
                        } else {
                            //手前平面より手前で範囲外
                            _offscreen_kind = 5;
                        }
                    } else {
                        //右平面より右で範囲外
                        _offscreen_kind = 4;
                    }
                } else {
                    //左平面より左で範囲外
                    _offscreen_kind = 3;
                }
            } else {
                //下平面より下で範囲外
                _offscreen_kind = 2;
            }
        } else {
            //上平面より上で範囲外
            _offscreen_kind = 1;
        }
    }
    return _offscreen_kind;
}


void MassWallActor::config(WallSectionScene* prm_pWallSectionScene, pos_t prm_pos_info, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    if (prm_pos_info == 0) {
        //BOX
        _wall_draw_face = prm_wall_draw_face;
    } else {
        //プリズムかピラミッドなので、無条件で描画不要面が一つ存在、それを追加
        _wall_draw_face = (prm_wall_draw_face & MassWallActor::_draw_face[prm_pos_info]);
    }
    _pWallSectionScene =prm_pWallSectionScene;
    _wall_dep = _pWallSectionScene->_wall_dep;
    _wall_width = _pWallSectionScene->_wall_width;
    _wall_height = _pWallSectionScene->_wall_height;
    _pos_info = prm_pos_info;

    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    if (prm_aColliBoxStretch[0] == 0) {
        pChecker->disable(0);
        pChecker->disable(1);
        pChecker->disable(2);
    } else {
        if (prm_pos_info == 0) {
            //BOX
            pChecker->setColliAABox(0, -(_wall_dep/2)    - (_wall_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1)),
                                       -(_wall_height/2) - (_wall_height * (prm_aColliBoxStretch[FACE_D_IDX]-1)),
                                       -(_wall_width/2)  - (_wall_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1)),
                                        (_wall_dep/2)    + (_wall_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1)),
                                        (_wall_height/2) + (_wall_height * (prm_aColliBoxStretch[FACE_A_IDX]-1)),
                                        (_wall_width/2)  + (_wall_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1))
                                 );
            pChecker->enable(0);
            pChecker->disable(1);
            pChecker->disable(2);
        } else if (POS_PRISM_XY_NN <= prm_pos_info && prm_pos_info <= POS_PRISM_ZX_PP) {
            //プリズム
            pChecker->setColliAAPrism(1, -(_wall_dep/2)    - (_wall_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1)),
                                         -(_wall_height/2) - (_wall_height * (prm_aColliBoxStretch[FACE_D_IDX]-1)),
                                         -(_wall_width/2)  - (_wall_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1)),
                                          (_wall_dep/2)    + (_wall_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1)),
                                          (_wall_height/2) + (_wall_height * (prm_aColliBoxStretch[FACE_A_IDX]-1)),
                                          (_wall_width/2)  + (_wall_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1)),
                                          _pos_info   );
            pChecker->enable(1);
            pChecker->disable(0);
            pChecker->disable(2);
        } else {
            //ピラミッド
            pChecker->setColliAAPyramid(2, -(_wall_dep/2)    - (_wall_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1)),
                                           -(_wall_height/2) - (_wall_height * (prm_aColliBoxStretch[FACE_D_IDX]-1)),
                                           -(_wall_width/2)  - (_wall_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1)),
                                            (_wall_dep/2)    + (_wall_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1)),
                                            (_wall_height/2) + (_wall_height * (prm_aColliBoxStretch[FACE_A_IDX]-1)),
                                            (_wall_width/2)  + (_wall_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1)),
                                            _pos_info   );
            pChecker->enable(2);
            pChecker->disable(0);
            pChecker->disable(1);
        }

    }
}

void MassWallActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

MassWallActor::~MassWallActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}

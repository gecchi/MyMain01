#include "jp/ggaf/lib/actor/wall/MassWallAABActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/model/GgafDxMassMeshModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassMeshEffect.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/scene/WalledSectionScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

MassWallAABActor::MassWallAABActor(const char* prm_name,
                           const char* prm_model,
                           GgafStatus* prm_pStat) :

                            MassWallActor(prm_name,
                                          std::string("16/" + std::string(prm_model)).c_str(),
                                          "WallAABEffect",
                                          "WallAABTechnique",
                                          prm_pStat) {

    _class_name = "MassWallAABActor";
    _pMassMeshModel->_set_num = 16; //MassWallAABActor最大セット数は16。
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1); //0:BOX用当たり判定、1:プリズム用当たり判定
    pChecker->setColliAABox(0, 0,0,0, 0,0,0);
    setZEnableDraw(true);   //描画時、Zバッファ値は考慮される
    setZWriteEnable(true);  //自身のZバッファを書き込みする

    static volatile bool is_init = MassWallAABActor::initStatic(this); //静的メンバ初期化
}

D3DXHANDLE MassWallAABActor::_h_distance_AlphaTarget;
D3DXHANDLE MassWallAABActor::_ah_wall_draw_face[16];
bool MassWallAABActor::initStatic(MassWallAABActor* prm_pMassWallAABActor) {
    ID3DXEffect* const pID3DXEffect = prm_pMassWallAABActor->getEffect()->_pID3DXEffect;
    MassWallAABActor::_h_distance_AlphaTarget = pID3DXEffect->GetParameterByName( nullptr, "g_distance_AlphaTarget" );
    MassWallAABActor::_ah_wall_draw_face[0]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face001" );
    MassWallAABActor::_ah_wall_draw_face[1]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face002" );
    MassWallAABActor::_ah_wall_draw_face[2]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face003" );
    MassWallAABActor::_ah_wall_draw_face[3]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face004" );
    MassWallAABActor::_ah_wall_draw_face[4]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face005" );
    MassWallAABActor::_ah_wall_draw_face[5]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face006" );
    MassWallAABActor::_ah_wall_draw_face[6]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face007" );
    MassWallAABActor::_ah_wall_draw_face[7]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face008" );
    MassWallAABActor::_ah_wall_draw_face[8]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face009" );
    MassWallAABActor::_ah_wall_draw_face[9]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face010" );
    MassWallAABActor::_ah_wall_draw_face[10]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face011" );
    MassWallAABActor::_ah_wall_draw_face[11]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face012" );
    MassWallAABActor::_ah_wall_draw_face[12]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face013" );
    MassWallAABActor::_ah_wall_draw_face[13]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face014" );
    MassWallAABActor::_ah_wall_draw_face[14]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face015" );
    MassWallAABActor::_ah_wall_draw_face[15]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face016" );
//    MassWallAABActor::_ah_wall_draw_face[16]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face017" );
//    MassWallAABActor::_ah_wall_draw_face[17]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face018" );
//    MassWallAABActor::_ah_wall_draw_face[18]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face019" );
    return true;
}
void MassWallAABActor::config(WalledSectionScene* prm_pWalledSectionScene, int prm_pos_info, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    MassWallActor::config(prm_pWalledSectionScene, prm_pos_info,  prm_wall_draw_face,  prm_aColliBoxStretch);
    CollisionChecker3D* pChecker = getCollisionChecker();
    if (prm_aColliBoxStretch[0] == 0) {
        pChecker->disable(0);
    } else {
        pChecker->setColliAABox(0, -(_wall_dep/2)    - (_wall_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1)),
                                 -(_wall_height/2) - (_wall_height * (prm_aColliBoxStretch[FACE_D_IDX]-1)),
                                 -(_wall_width/2)  - (_wall_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1)),
                                  (_wall_dep/2)    + (_wall_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1)),
                                  (_wall_height/2) + (_wall_height * (prm_aColliBoxStretch[FACE_A_IDX]-1)),
                                  (_wall_width/2)  + (_wall_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1))
                             );
         pChecker->enable(0);
    }
}

void MassWallAABActor::processDraw() {
    int draw_set_num = 0; //GgafDxMassMeshActorの同じモデルで同じテクニックが
                          //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* const pID3DXEffect = _pMassMeshEffect->_pID3DXEffect;
    HRESULT hr;
    if (_pWalledSectionScene->_pActor_infront_alpha_target) {
        hr = pID3DXEffect->SetFloat(MassWallAABActor::_h_distance_AlphaTarget, -(_pWalledSectionScene->_pActor_infront_alpha_target->_dest_from_vppln_infront));
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    } else {
        hr = pID3DXEffect->SetFloat(MassWallAABActor::_h_distance_AlphaTarget, -100.0f);
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    }
    GgafDxFigureActor* pDrawActor = this;
    MassWallActor* pMassWallActor = nullptr;
    int model_set_num = _pMassMeshModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMassMeshModel && pDrawActor->_hash_technique == _hash_technique) {
            pMassWallActor = (MassWallActor*)pDrawActor;
            hr = pID3DXEffect->SetInt(MassWallAABActor::_ah_wall_draw_face[draw_set_num], pMassWallActor->_wall_draw_face);
            checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) に失敗しました。");

//            hr = pID3DXEffect->SetMatrix(_pMassMeshEffect->_ah_matWorld[draw_set_num], &(pMassWallActor->_matWorld));
            checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) に失敗しました。");

            //_set_num 19を18に、あるいは２とか３に減らしてみたはどうか
            //FXをVS_2_0 に変えてみてはどうか
            //
//                D3DXMATRIX& mat = pMassWallActor->_matWorld;
//                _TRACE_(mat._11<<","<<mat._12<<","<<mat._13<<","<<mat._14);
//                _TRACE_(mat._21<<","<<mat._22<<","<<mat._23<<","<<mat._24);
//                _TRACE_(mat._31<<","<<mat._32<<","<<mat._33<<","<<mat._34);
//                _TRACE_(mat._41<<","<<mat._42<<","<<mat._43<<","<<mat._44);
//                _TRACE_("------------");

            draw_set_num++;
            if (draw_set_num >= model_set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    GgafDxSpacetime::_pActor_draw_active = pMassWallActor; //描画セットの最後アクターをセット
    _pMassMeshModel->GgafDxMassMeshModel::draw(this, draw_set_num);
}


MassWallAABActor::~MassWallAABActor() {
}

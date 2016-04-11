#include "jp/ggaf/lib/actor/WallAAPyramidActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/scene/WalledSectionScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WallAAPyramidActor::WallAAPyramidActor(const char* prm_name,
                                   const char* prm_model,
                                   GgafStatus* prm_pStat) :

                                      WallPartsActor(prm_name,
                                                     std::string("11/" + std::string(prm_model)).c_str(),
                                                     "WallAAPyramidEffect",
                                                     "WallAAPyramidTechnique",
                                                     prm_pStat) {

    _class_name = "WallAAPyramidActor";
    _pMeshSetModel->_set_num = 11; //WallAAPyramidActor最大セット数は11。

    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1); //0:BOX用当たり判定、1:ピラミッド用当たり判定
    pChecker->setColliAAPyramid(0, 0,0,0, 0,0,0, 0);
    setZEnableDraw(true);       //描画時、Zバッファ値は考慮される
    setZWriteEnable(true);  //自身のZバッファを書き込みする

    static volatile bool is_init = WallAAPyramidActor::initStatic(this); //静的メンバ初期化
}

D3DXHANDLE WallAAPyramidActor::_h_distance_AlphaTarget;
D3DXHANDLE WallAAPyramidActor::_h_wall_dep;
D3DXHANDLE WallAAPyramidActor::_h_wall_height;
D3DXHANDLE WallAAPyramidActor::_h_wall_width;
std::map<int, UINT> WallAAPyramidActor::_delface;
bool WallAAPyramidActor::initStatic(WallAAPyramidActor* prm_pWallAAPyramidActor) {
    ID3DXEffect* pID3DXEffect = prm_pWallAAPyramidActor->getEffect()->_pID3DXEffect;
    WallAAPyramidActor::_h_distance_AlphaTarget = pID3DXEffect->GetParameterByName( nullptr, "g_distance_AlphaTarget" );
    WallAAPyramidActor::_h_wall_dep    = pID3DXEffect->GetParameterByName( nullptr, "g_wall_dep" );
    WallAAPyramidActor::_h_wall_height = pID3DXEffect->GetParameterByName( nullptr, "g_wall_height" );
    WallAAPyramidActor::_h_wall_width  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_width" );

    //ピラミッド壁であるならば、形状により無条件で描画不要面がある、
    //    c
    // a b d f
    //      e
    //
    //                 00abcdef
    //
    //    FACE_A_BIT = 32 = 0b100000
    //    FACE_B_BIT = 16 = 0b010000
    //    FACE_C_BIT = 8  = 0b001000
    //    FACE_D_BIT = 4  = 0b000100
    //    FACE_E_BIT = 2  = 0b000010
    //    FACE_F_BIT = 1  = 0b000001
    //XYピラミッドの場合は +X -X面をつぶす
    //
    //無条件で不要な面ビットを 0
    //特に条件がない場合、描画する面ビットを 1
    //に設定
                                                                                           //斜面
    WallAAPyramidActor::_delface[POS_PYRAMID_nnn] = FACE_D_BIT | FACE_B_BIT | FACE_E_BIT | FACE_A_BIT;
    WallAAPyramidActor::_delface[POS_PYRAMID_nnp] = FACE_D_BIT | FACE_C_BIT | FACE_B_BIT | FACE_A_BIT;
    WallAAPyramidActor::_delface[POS_PYRAMID_npn] = FACE_A_BIT | FACE_B_BIT | FACE_E_BIT | FACE_D_BIT;
    WallAAPyramidActor::_delface[POS_PYRAMID_npp] = FACE_A_BIT | FACE_C_BIT | FACE_B_BIT | FACE_D_BIT;
    WallAAPyramidActor::_delface[POS_PYRAMID_pnn] = FACE_D_BIT | FACE_F_BIT | FACE_E_BIT | FACE_A_BIT;
    WallAAPyramidActor::_delface[POS_PYRAMID_pnp] = FACE_D_BIT | FACE_C_BIT | FACE_F_BIT | FACE_A_BIT;
    WallAAPyramidActor::_delface[POS_PYRAMID_ppn] = FACE_A_BIT | FACE_F_BIT | FACE_E_BIT | FACE_D_BIT;
    WallAAPyramidActor::_delface[POS_PYRAMID_ppp] = FACE_A_BIT | FACE_C_BIT | FACE_F_BIT | FACE_D_BIT;
    return true;
}

void WallAAPyramidActor::config(WalledSectionScene* prm_pWalledSectionScene, int prm_pos_pyramid, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    prm_wall_draw_face &= WallAAPyramidActor::_delface[prm_pos_pyramid]; //ピラミッド無条件描画不要面
    WallPartsActor::config(prm_pWalledSectionScene, prm_pos_pyramid,  prm_wall_draw_face,  prm_aColliBoxStretch);
    CollisionChecker3D* pChecker = getCollisionChecker();
    if (prm_aColliBoxStretch[0] == 0) {
        pChecker->disable(0);
    } else {
        pChecker->setColliAAPyramid(0, -(_wall_dep/2)    - (_wall_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1)),
                                       -(_wall_height/2) - (_wall_height * (prm_aColliBoxStretch[FACE_D_IDX]-1)),
                                       -(_wall_width/2)  - (_wall_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1)),
                                        (_wall_dep/2)    + (_wall_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1)),
                                        (_wall_height/2) + (_wall_height * (prm_aColliBoxStretch[FACE_A_IDX]-1)),
                                        (_wall_width/2)  + (_wall_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1)),
                                        _pos_info   );
         pChecker->enable(0);
    }
    HRESULT hr;
    ID3DXEffect* pID3DXEffect = getEffect()->_pID3DXEffect;
    hr = pID3DXEffect->SetFloat(WallAAPyramidActor::_h_wall_dep, C_DX(_wall_dep)/_rate_of_bounding_sphere_radius);
    checkDxException(hr, D3D_OK, "SetInt(_h_wall_dep) に失敗しました。");
    hr = pID3DXEffect->SetFloat(WallAAPyramidActor::_h_wall_height, C_DX(_wall_height)/_rate_of_bounding_sphere_radius);
    checkDxException(hr, D3D_OK, "SetInt(_h_wall_height) に失敗しました。");
    hr = pID3DXEffect->SetFloat(WallAAPyramidActor::_h_wall_width, C_DX(_wall_width)/_rate_of_bounding_sphere_radius);
    checkDxException(hr, D3D_OK, "SetInt(_h_wall_width) に失敗しました。");

}

void WallAAPyramidActor::processDraw() {
    int draw_set_num = 0; //GgafDxMeshSetActorの同じモデルで同じテクニックが
                          //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* const pID3DXEffect = getEffect()->_pID3DXEffect;
    HRESULT hr;
    if (_pWalledSectionScene->_pActor_infront_alpha_target) {
        hr = pID3DXEffect->SetFloat(WallAAPyramidActor::_h_distance_AlphaTarget, -(_pWalledSectionScene->_pActor_infront_alpha_target->_dest_from_vppln_infront));
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    } else {
        hr = pID3DXEffect->SetFloat(WallAAPyramidActor::_h_distance_AlphaTarget, -100.0f);
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    }
    GgafDxFigureActor* pDrawActor = this;
    WallPartsActor* pWallPartsActor = nullptr;
    int model_set_num = _pMeshSetModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pWallPartsActor = (WallPartsActor*)pDrawActor;
            pWallPartsActor->_matWorld._14 = pWallPartsActor->_wall_draw_face;  //描画面番号をワールド変換行列のmatWorld._14 に埋め込む
            pWallPartsActor->_matWorld._24 = pWallPartsActor->_pos_info;  //ピラミッド位置情報ををワールド変換行列のmatWorld._24 に埋め込む
            hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[draw_set_num], &(pWallPartsActor->_matWorld));
            checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) に失敗しました。");
            draw_set_num++;
            if (draw_set_num >= model_set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    GgafDxSpacetime::_pActor_draw_active = pWallPartsActor; //描画セットの最後アクターをセット
    _pMeshSetModel->GgafDxMeshSetModel::draw(this, draw_set_num);
}


WallAAPyramidActor::~WallAAPyramidActor() {
}

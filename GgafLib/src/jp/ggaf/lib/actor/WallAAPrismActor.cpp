#include "jp/ggaf/lib/actor/WallAAPrismActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/scene/WalledSectionScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WallAAPrismActor::WallAAPrismActor(const char* prm_name,
                                   const char* prm_model,
                                   GgafStatus* prm_pStat) :

                                      WallPartsActor(prm_name,
                                                     std::string("11/" + std::string(prm_model)).c_str(),
                                                     "WallAAPrismEffect",
                                                     "WallAAPrismTechnique",
                                                     prm_pStat) {

    _class_name = "WallAAPrismActor";
    _pMeshSetModel->_set_num = 11; //WallAAPrismActor最大セット数は11。

    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1); //0:BOX用当たり判定、1:プリズム用当たり判定
    pChecker->setColliAAPrism(0, 0,0,0, 0,0,0, 0);
    setZEnableDraw(true);       //描画時、Zバッファ値は考慮される
    setZWriteEnable(true);  //自身のZバッファを書き込みする
    if (isFirstEffectConnector()) {
        ID3DXEffect* pID3DXEffect = getEffect()->_pID3DXEffect;
        WallAAPrismActor::_h_distance_AlphaTarget = pID3DXEffect->GetParameterByName( nullptr, "g_distance_AlphaTarget" );
        WallAAPrismActor::_h_wall_dep    = pID3DXEffect->GetParameterByName( nullptr, "g_wall_dep" );
        WallAAPrismActor::_h_wall_height = pID3DXEffect->GetParameterByName( nullptr, "g_wall_height" );
        WallAAPrismActor::_h_wall_width  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_width" );
    }
    static volatile bool is_init = WallAAPrismActor::initStatic(this); //静的メンバ初期化
}

D3DXHANDLE WallAAPrismActor::_h_distance_AlphaTarget;
D3DXHANDLE WallAAPrismActor::_h_wall_dep;
D3DXHANDLE WallAAPrismActor::_h_wall_height;
D3DXHANDLE WallAAPrismActor::_h_wall_width;
std::map<int, UINT> WallAAPrismActor::_delface;

bool WallAAPrismActor::initStatic(WallAAPrismActor* prm_pWallAAPrismActor) {
    //プリズム壁であるならば、形状により無条件で描画不要面がある、
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
    //
    //無条件で不要な面ビットを 0
    //特に条件がない場合、描画する面ビットを 1
    //に設定

    //XYプリズムの場合は +X -X面をつぶす
    WallAAPrismActor::_delface[POS_PRISM_XY_NN] = ~FACE_F_BIT;
    WallAAPrismActor::_delface[POS_PRISM_XY_NP] = ~FACE_F_BIT;
    WallAAPrismActor::_delface[POS_PRISM_XY_PN] = ~FACE_B_BIT;
    WallAAPrismActor::_delface[POS_PRISM_XY_PP] = ~FACE_B_BIT;

    //YZプリズムの場合も +Z -Z面をつぶす
    WallAAPrismActor::_delface[POS_PRISM_YZ_NN] = ~FACE_C_BIT;
    WallAAPrismActor::_delface[POS_PRISM_YZ_NP] = ~FACE_E_BIT;
    WallAAPrismActor::_delface[POS_PRISM_YZ_PN] = ~FACE_C_BIT;
    WallAAPrismActor::_delface[POS_PRISM_YZ_PP] = ~FACE_E_BIT;

    //ZXプリズムの場合も +X -X面をつぶす
    WallAAPrismActor::_delface[POS_PRISM_ZX_NN] = ~FACE_F_BIT;
    WallAAPrismActor::_delface[POS_PRISM_ZX_NP] = ~FACE_B_BIT;
    WallAAPrismActor::_delface[POS_PRISM_ZX_PN] = ~FACE_F_BIT;
    WallAAPrismActor::_delface[POS_PRISM_ZX_PP] = ~FACE_B_BIT;
    return true;
}

void WallAAPrismActor::config(WalledSectionScene* prm_pWalledSectionScene, pos_t prm_pos_info, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    prm_wall_draw_face &= WallAAPrismActor::_delface[prm_pos_info]; //プリズム無条件描画不要面
    WallPartsActor::config(prm_pWalledSectionScene, prm_pos_info,  prm_wall_draw_face,  prm_aColliBoxStretch);
    CollisionChecker* pChecker = getCollisionChecker();
    if (prm_aColliBoxStretch[0] == 0) {
        pChecker->disable(0);
    } else {
        pChecker->setColliAAPrism(0, -(_wall_dep/2)    - (_wall_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1)),
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
    hr = pID3DXEffect->SetFloat(WallAAPrismActor::_h_wall_dep, C_DX(_wall_dep)/_rate_of_bounding_sphere_radius);
    checkDxException(hr, D3D_OK, "SetInt(_h_wall_dep) に失敗しました。");
    hr = pID3DXEffect->SetFloat(WallAAPrismActor::_h_wall_height, C_DX(_wall_height)/_rate_of_bounding_sphere_radius);
    checkDxException(hr, D3D_OK, "SetInt(_h_wall_height) に失敗しました。");
    hr = pID3DXEffect->SetFloat(WallAAPrismActor::_h_wall_width, C_DX(_wall_width)/_rate_of_bounding_sphere_radius);
    checkDxException(hr, D3D_OK, "SetInt(_h_wall_width) に失敗しました。");

}

void WallAAPrismActor::processDraw() {
    int draw_set_num = 0; //GgafDxMeshSetActorの同じモデルで同じテクニックが
                          //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* const pID3DXEffect = getEffect()->_pID3DXEffect;
    HRESULT hr;
    if (_pWalledSectionScene->_pActor_infront_alpha_target) {
        hr = pID3DXEffect->SetFloat(WallAAPrismActor::_h_distance_AlphaTarget, -(_pWalledSectionScene->_pActor_infront_alpha_target->_dest_from_vppln_infront));
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    } else {
        hr = pID3DXEffect->SetFloat(WallAAPrismActor::_h_distance_AlphaTarget, -100.0f);
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    }
    GgafDxFigureActor* pDrawActor = this;
    WallPartsActor* pWallPartsActor = nullptr;
    int model_set_num = _pMeshSetModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pWallPartsActor = (WallPartsActor*)pDrawActor;
            pWallPartsActor->_matWorld._14 = pWallPartsActor->_wall_draw_face;  //描画面番号をワールド変換行列のmatWorld._14 に埋め込む
            pWallPartsActor->_matWorld._24 = pWallPartsActor->_pos_info;  //プリズム位置情報ををワールド変換行列のmatWorld._24 に埋め込む
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


WallAAPrismActor::~WallAAPrismActor() {
}

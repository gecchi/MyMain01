#include "jp/ggaf/lib/actor/wall/MassWallAAPrismActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/model/GgafDxMassMeshModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassMeshEffect.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/scene/WalledSectionScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

MassWallAAPrismActor::MassWallAAPrismActor(const char* prm_name,
                                   const char* prm_model,
                                   GgafStatus* prm_pStat) :

                                       MassWallActor(prm_name,
                                                     std::string("11/" + std::string(prm_model)).c_str(),
                                                     "WallAAPrismEffect",
                                                     "WallAAPrismTechnique",
                                                     prm_pStat) {

    _class_name = "MassWallAAPrismActor";
    _pMassMeshModel->_set_num = 11; //MassWallAAPrismActor最大セット数は11。

    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1); //0:BOX用当たり判定、1:プリズム用当たり判定
    pChecker->setColliAAPrism(0, 0,0,0, 0,0,0, 0);
    setZEnableDraw(true);       //描画時、Zバッファ値は考慮される
    setZWriteEnable(true);  //自身のZバッファを書き込みする

    static volatile bool is_init = MassWallAAPrismActor::initStatic(this); //静的メンバ初期化
}

D3DXHANDLE MassWallAAPrismActor::_h_distance_AlphaTarget;
D3DXHANDLE MassWallAAPrismActor::_h_wall_dep;
D3DXHANDLE MassWallAAPrismActor::_h_wall_height;
D3DXHANDLE MassWallAAPrismActor::_h_wall_width;
std::map<int, UINT> MassWallAAPrismActor::_delface;
bool MassWallAAPrismActor::initStatic(MassWallAAPrismActor* prm_pMassWallAAPrismActor) {
    ID3DXEffect* pID3DXEffect = prm_pMassWallAAPrismActor->getEffect()->_pID3DXEffect;
    MassWallAAPrismActor::_h_distance_AlphaTarget = pID3DXEffect->GetParameterByName( nullptr, "g_distance_AlphaTarget" );
    MassWallAAPrismActor::_h_wall_dep    = pID3DXEffect->GetParameterByName( nullptr, "g_wall_dep" );
    MassWallAAPrismActor::_h_wall_height = pID3DXEffect->GetParameterByName( nullptr, "g_wall_height" );
    MassWallAAPrismActor::_h_wall_width  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_width" );

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
    MassWallAAPrismActor::_delface[POS_PRISM_XY_nn] = ~FACE_F_BIT;
    MassWallAAPrismActor::_delface[POS_PRISM_XY_np] = ~FACE_F_BIT;
    MassWallAAPrismActor::_delface[POS_PRISM_XY_pn] = ~FACE_B_BIT;
    MassWallAAPrismActor::_delface[POS_PRISM_XY_pp] = ~FACE_B_BIT;

    //YZプリズムの場合も +Z -Z面をつぶす
    MassWallAAPrismActor::_delface[POS_PRISM_YZ_nn] = ~FACE_C_BIT;
    MassWallAAPrismActor::_delface[POS_PRISM_YZ_np] = ~FACE_E_BIT;
    MassWallAAPrismActor::_delface[POS_PRISM_YZ_pn] = ~FACE_C_BIT;
    MassWallAAPrismActor::_delface[POS_PRISM_YZ_pp] = ~FACE_E_BIT;

    //ZXプリズムの場合も +X -X面をつぶす
    MassWallAAPrismActor::_delface[POS_PRISM_ZX_nn] = ~FACE_F_BIT;
    MassWallAAPrismActor::_delface[POS_PRISM_ZX_np] = ~FACE_B_BIT;
    MassWallAAPrismActor::_delface[POS_PRISM_ZX_pn] = ~FACE_F_BIT;
    MassWallAAPrismActor::_delface[POS_PRISM_ZX_pp] = ~FACE_B_BIT;
    return true;
}

void MassWallAAPrismActor::config(WalledSectionScene* prm_pWalledSectionScene, int prm_pos_info, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    prm_wall_draw_face &= MassWallAAPrismActor::_delface[prm_pos_info]; //プリズム無条件描画不要面
    MassWallActor::config(prm_pWalledSectionScene, prm_pos_info,  prm_wall_draw_face,  prm_aColliBoxStretch);
    CollisionChecker3D* pChecker = getCollisionChecker();
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
    hr = pID3DXEffect->SetFloat(MassWallAAPrismActor::_h_wall_dep, C_DX(_wall_dep)/_rate_of_bounding_sphere_radius);
    checkDxException(hr, D3D_OK, "SetInt(_h_wall_dep) に失敗しました。");
    hr = pID3DXEffect->SetFloat(MassWallAAPrismActor::_h_wall_height, C_DX(_wall_height)/_rate_of_bounding_sphere_radius);
    checkDxException(hr, D3D_OK, "SetInt(_h_wall_height) に失敗しました。");
    hr = pID3DXEffect->SetFloat(MassWallAAPrismActor::_h_wall_width, C_DX(_wall_width)/_rate_of_bounding_sphere_radius);
    checkDxException(hr, D3D_OK, "SetInt(_h_wall_width) に失敗しました。");

}

void MassWallAAPrismActor::processDraw() {
    int draw_set_num = 0; //GgafDxMassMeshActorの同じモデルで同じテクニックが
                          //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* const pID3DXEffect = getEffect()->_pID3DXEffect;
    HRESULT hr;
    if (_pWalledSectionScene->_pActor_infront_alpha_target) {
        hr = pID3DXEffect->SetFloat(MassWallAAPrismActor::_h_distance_AlphaTarget, -(_pWalledSectionScene->_pActor_infront_alpha_target->_dest_from_vppln_infront));
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    } else {
        hr = pID3DXEffect->SetFloat(MassWallAAPrismActor::_h_distance_AlphaTarget, -100.0f);
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    }
    GgafDxFigureActor* pDrawActor = this;
    MassWallActor* pMassWallActor = nullptr;
    int model_set_num = _pMassMeshModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMassMeshModel && pDrawActor->_hash_technique == _hash_technique) {
            pMassWallActor = (MassWallActor*)pDrawActor;
            pMassWallActor->_matWorld._14 = pMassWallActor->_wall_draw_face;  //描画面番号をワールド変換行列のmatWorld._14 に埋め込む
            pMassWallActor->_matWorld._24 = pMassWallActor->_pos_info;  //プリズム位置情報ををワールド変換行列のmatWorld._24 に埋め込む
//            hr = pID3DXEffect->SetMatrix(_pMassMeshEffect->_ah_matWorld[draw_set_num], &(pMassWallActor->_matWorld));
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
    GgafDxSpacetime::_pActor_draw_active = pMassWallActor; //描画セットの最後アクターをセット
    _pMassMeshModel->GgafDxMassMeshModel::draw(this, draw_set_num);
}


MassWallAAPrismActor::~MassWallAAPrismActor() {
}

#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WallAABActor::WallAABActor(const char* prm_name,
                           const char* prm_model,
                           GgafStatus* prm_pStat) :

                          WallPartsActor(prm_name,
                                        std::string("19/" + std::string(prm_model)).c_str(),
                                        "WallAABEffect",
                                        "WallAABTechnique",
                                        prm_pStat) {

    _class_name = "WallAABActor";
    _pMeshSetModel->_set_num = 19; //WallPartsActor最大セット数は20。
    _h_distance_AlphaTarget = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_distance_AlphaTarget" );
    _pColliChecker->makeCollision(1); //0:BOX用当たり判定、1:プリズム用当たり判定
    _pColliChecker->setColliAAB(0, 0,0,0, 0,0,0);
    setZEnable(true);       //Zバッファは考慮有り
    setZWriteEnable(true);  //Zバッファは書き込み有り
}


void WallAABActor::config(WalledSectionScene* prm_pWalledSectionScene, int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    WallPartsActor::config(prm_pWalledSectionScene, prm_pos_prism,  prm_wall_draw_face,  prm_aColliBoxStretch);

    if (prm_aColliBoxStretch[0] == 0) {
        _pColliChecker->disable(0);
    } else {
        _pColliChecker->setColliAAB(0, -(_wall_dep/2)    - (_wall_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1)),
                                           -(_wall_height/2) - (_wall_height * (prm_aColliBoxStretch[FACE_D_IDX]-1)),
                                           -(_wall_width/2)  - (_wall_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1)),
                                            (_wall_dep/2)    + (_wall_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1)),
                                            (_wall_height/2) + (_wall_height * (prm_aColliBoxStretch[FACE_A_IDX]-1)),
                                            (_wall_width/2)  + (_wall_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1))
                                       );
         _pColliChecker->enable(0);
    }
}

void WallAABActor::processDraw() {
    _draw_set_num = 0; //GgafDxMeshSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    if (_pWalledSectionScene->_pTarget_FrontAlpha) {
        hr = pID3DXEffect->SetFloat(_h_distance_AlphaTarget, -(_pWalledSectionScene->_pTarget_FrontAlpha->_dest_from_vppln_front));
        checkDxException(hr, D3D_OK, "GgafDxMeshSetActor::processDraw() SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    } else {
        hr = pID3DXEffect->SetFloat(_h_distance_AlphaTarget, -100.0f);
        checkDxException(hr, D3D_OK, "GgafDxMeshSetActor::processDraw() SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    }
    GgafDxDrawableActor* pDrawActor = this;
    WallPartsActor* pWallPartsActor = NULL;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pModel == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pWallPartsActor = (WallPartsActor*)pDrawActor;
                pWallPartsActor->_matWorld._14 = pWallPartsActor->_wall_draw_face;  //描画面番号をワールド変換行列のmatWorld._14 に埋め込む
                hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[_draw_set_num], &(pWallPartsActor->_matWorld));
                checkDxException(hr, D3D_OK, "WallPartsActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
                _draw_set_num++;
                if (_draw_set_num >= _pMeshSetModel->_set_num) {
                    break;
                }
                pDrawActor = pDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    GgafDxUniverse::_pActor_DrawActive = pWallPartsActor; //描画セットの最後アクターをセット
    _pMeshSetModel->draw(this, _draw_set_num);



//    WallPartsActor* pDrawActor;
//    pDrawActor = this;
//    for (int i = 0; i < _draw_set_num; i++) {
//        pDrawActor->_matWorld._14 = pDrawActor->_wall_draw_face;  //描画面番号をワールド変換行列のmatWorld._14 に埋め込む
//        //pDrawActor->_matWorld._24 = pDrawActor->_pos_prism;  //プリズム位置情報ををワールド変換行列のmatWorld._24 に埋め込む
//        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[i], &(pDrawActor->_matWorld));
//        checkDxException(hr, D3D_OK, "WallPartsActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
//        pDrawActor = (WallPartsActor*)(pDrawActor -> _pNext_TheSameDrawDepthLevel);
//        if (i > 0) {
//            //アクティブを進める
//            GgafDxUniverse::_pActor_DrawActive = GgafDxUniverse::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
//        }
//    }
//    _pMeshSetModel->draw(this, _draw_set_num);
}


WallAABActor::~WallAABActor() {
}

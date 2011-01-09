#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

boolean WallAAPrismActor::init = false;

_MAP_<int, UINT> WallAAPrismActor::_delface;

WallAAPrismActor::WallAAPrismActor(const char* prm_name,
                                   const char* prm_model) :

                                      WallActor(prm_name,
                                                string("17/" + string(prm_model)).c_str(),
                                                "WallAAPrismEffect",
                                                "WallAAPrismTechnique") {

    _class_name = "WallAAPrismActor";
    _pMeshSetModel->_set_num = 11; //WallActor最大セット数は20。


    _pCollisionChecker->makeCollision(1); //0:BOX用当たり判定、1:プリズム用当たり判定
    _pCollisionChecker->setColliAAPrism(0, 0,0,0, 0,0,0, 0);
    setZEnable(true);       //Zバッファは考慮有り
    setZWriteEnable(true);  //Zバッファは書き込み有り
    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    _h_distance_AlphaTarget = pID3DXEffect->GetParameterByName( NULL, "g_distance_AlphaTarget" );
    _h_wall_dep    = pID3DXEffect->GetParameterByName( NULL, "g_wall_dep" );
    _h_wall_height = pID3DXEffect->GetParameterByName( NULL, "g_wall_height" );
    _h_wall_width  = pID3DXEffect->GetParameterByName( NULL, "g_wall_width" );
    //_h_pos_prism = pID3DXEffect->GetParameterByName( NULL, "g_pos_prism" );
    if (init == false) {
        //プリズム壁であるならば、形状により無条件で描画不要面がある、
        //    c
        // a b d f
        //      e
        //
        //                 00abcdef
        //
        //    FACE_A_BIT = 0b100000 = 0
        //    FACE_B_BIT = 0b010000 = 9
        //    FACE_C_BIT = 0b001000 = 8
        //    FACE_D_BIT = 0b000100 = 4
        //    FACE_E_BIT = 0b000010 = 2
        //    FACE_F_BIT = 0b000001 = 1
        //XYプリズムの場合は +X -X面をつぶす
        _delface[POS_PRISM_XY_nn] = ~FACE_F_BIT;
        _delface[POS_PRISM_XY_np] = ~FACE_F_BIT;
        _delface[POS_PRISM_XY_pn] = ~FACE_B_BIT;
        _delface[POS_PRISM_XY_pp] = ~FACE_B_BIT;

        //YZプリズムの場合も +Z -Z面をつぶす
        _delface[POS_PRISM_YZ_nn] = ~FACE_C_BIT;
        _delface[POS_PRISM_YZ_np] = ~FACE_E_BIT;
        _delface[POS_PRISM_YZ_pn] = ~FACE_C_BIT;
        _delface[POS_PRISM_YZ_pp] = ~FACE_E_BIT;

        //ZXプリズムの場合も +X -X面をつぶす
        _delface[POS_PRISM_ZX_nn] = ~FACE_F_BIT;
        _delface[POS_PRISM_ZX_np] = ~FACE_B_BIT;
        _delface[POS_PRISM_ZX_pn] = ~FACE_F_BIT;
        _delface[POS_PRISM_ZX_pp] = ~FACE_B_BIT;
        init = true;
    }
}

void WallAAPrismActor::config(WalledSectionScene* prm_pWalledSectionScene, int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    prm_wall_draw_face &= _delface[prm_pos_prism]; //プリズム無条件描画不要面
    WallActor::config(prm_pWalledSectionScene, prm_pos_prism,  prm_wall_draw_face,  prm_aColliBoxStretch);

    if (prm_aColliBoxStretch[0] == 0) {
        _pCollisionChecker->disable(0);
    } else {
        _pCollisionChecker->setColliAAPrism(0, -(_wall_dep/2)    - (_wall_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1)),
                                               -(_wall_height/2) - (_wall_height * (prm_aColliBoxStretch[FACE_D_IDX]-1)),
                                               -(_wall_width/2)  - (_wall_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1)),
                                                (_wall_dep/2)    + (_wall_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1)),
                                                (_wall_height/2) + (_wall_height * (prm_aColliBoxStretch[FACE_A_IDX]-1)),
                                                (_wall_width/2)  + (_wall_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1)),
                                                _pos_prism
                                            );

         _pCollisionChecker->enable(0);
    }
	HRESULT hr;
	ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    hr = pID3DXEffect->SetFloat(_h_wall_dep, 1.0*_wall_dep/LEN_UNIT/PX_UNIT/_fRate_BoundingSphereRadius);
    checkDxException(hr, D3D_OK, "WallAAPrismActor::WallAAPrismActor() SetInt(_h_wall_dep) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_h_wall_height, 1.0*_wall_height/LEN_UNIT/PX_UNIT/_fRate_BoundingSphereRadius);
    checkDxException(hr, D3D_OK, "WallAAPrismActor::WallAAPrismActor() SetInt(_h_wall_height) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_h_wall_width, 1.0*_wall_width/LEN_UNIT/PX_UNIT/_fRate_BoundingSphereRadius);
    checkDxException(hr, D3D_OK, "WallAAPrismActor::WallAAPrismActor() SetInt(_h_wall_width) に失敗しました。");

}

void WallAAPrismActor::processDraw() {
    _draw_set_num = 1; //GgafDx9MeshSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    GgafDx9DrawableActor* _pNextDrawActor;
    _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            if (_pNextDrawActor->_pGgafDx9Model == _pMeshSetModel &&
                _pNextDrawActor->_hash_technique == _hash_technique &&
                _pNextDrawActor->isActive()
            ) {
                _draw_set_num++;
                if (_draw_set_num > _pMeshSetModel->_set_num) {
                    _draw_set_num = _pMeshSetModel->_set_num;
                    break;
                }
                _pNextDrawActor = _pNextDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;
    if (_pWalledSectionScene->_pTarget_FrontAlpha) {
        hr = pID3DXEffect->SetFloat(_h_distance_AlphaTarget, -(_pWalledSectionScene->_pTarget_FrontAlpha->_fDist_VpPlnFront));
        checkDxException(hr, D3D_OK, "WallAAPrismActor::processDraw() SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    } else {
        hr = pID3DXEffect->SetFloat(_h_distance_AlphaTarget, -100.0f);
        checkDxException(hr, D3D_OK, "WallAAPrismActor::processDraw() SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    }
    //VIEW変換行列
//    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_h_matView, &P_CAM->_vMatrixView);
//    checkDxException(hr, D3D_OK, "WallAAPrismActor::processDraw() SetMatrix(_h_matView) に失敗しました。");

    WallActor* pDrawActor;
    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {
        pDrawActor->_matWorld._14 = pDrawActor->_wall_draw_face;  //描画面番号をワールド変換行列のmatWorld._14 に埋め込む
        pDrawActor->_matWorld._24 = pDrawActor->_pos_prism;  //プリズム位置情報ををワールド変換行列のmatWorld._24 に埋め込む
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[i], &(pDrawActor->_matWorld));
        checkDxException(hr, D3D_OK, "WallAAPrismActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
//		hr = pID3DXEffect->SetInt(_h_pos_prism, pDrawActor->_pos_prism);
//		checkDxException(hr, D3D_OK, "WallAAPrismActor::processDraw() SetInt(_h_wall_dep) に失敗しました。");
        pDrawActor = (WallActor*)(pDrawActor -> _pNext_TheSameDrawDepthLevel);
        if (i > 0) {
            //アクティブを進める
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    _pMeshSetModel->draw(this);
}


WallAAPrismActor::~WallAAPrismActor() {
}

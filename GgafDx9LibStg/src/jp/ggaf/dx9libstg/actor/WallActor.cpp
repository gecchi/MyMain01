#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

WallActor::WallActor(const char* prm_name, const char* prm_model) :
    GgafDx9MeshSetActor(prm_name,
                        string(string("19/") + string(prm_model)).c_str(),
                         "WallEffect",
                         "WallTechnique",
                         NEW CollisionChecker(this) ) {
    _class_name = "WallActor";
    _obj_class |= Obj_WallActor;
    _pMeshSetModel->_set_num = 19; //WallActor最大セット数は20。
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pCollisionChecker->makeCollision(1);

    _pScaler = NEW GgafDx9GeometricScaler(this);
    _wall_draw_face = 0;

    _h_distance_AlphaTarget = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_distance_AlphaTarget" );
    _pWalledSectionScene = NULL;
    setZEnable(true);       //Zバッファは考慮有り
    setZWriteEnable(true);  //Zバッファは書き込み有り
}

void WallActor::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (prm_pOtherActor->_obj_class & Obj_LaserChip) {
        LaserChip* pLaserChip = (LaserChip*)prm_pOtherActor;
        if (pLaserChip->_chip_kind != 2 || pLaserChip->_can_chikei_hit) {
            GgafDx9DrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDx9DrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}



void WallActor::initialize() {
//    if (_pWalledSectionScene == NULL) {
//        _pWalledSectionScene = (WalledSectionScene*)getPlatformScene();
//        _TRACE_("ini getPlatformScene() = _pWalledSectionScene = "<<_pWalledSectionScene->getName());
//        _wall_dep = _pWalledSectionScene->_wall_dep;
//        _wall_width = _pWalledSectionScene->_wall_width;
//        _wall_height = _pWalledSectionScene->_wall_height;
//    }
    setHitAble(true);
}

void WallActor::onActive() {

}

void WallActor::processBehavior() {
}

void WallActor::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}
bool WallActor::isOutOfUniverse() {
    if (GgafDx9Universe::_X_goneLeft < _X) {
        return false;
    }
    return true;
}



void WallActor::processDraw() {
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

    ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;
    if (_pWalledSectionScene->_pTarget_FrontAlpha) {
        hr = pID3DXEffect->SetFloat(_h_distance_AlphaTarget, -(_pWalledSectionScene->_pTarget_FrontAlpha->_fDist_VpPlnFront));
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    } else {
        hr = pID3DXEffect->SetFloat(_h_distance_AlphaTarget, -100.0f);
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    }
    //VIEW変換行列
//    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_h_matView, &P_CAM->_vMatrixView);
//    checkDxException(hr, D3D_OK, "WallActor::processDraw() SetMatrix(_h_matView) に失敗しました。");

    WallActor* pDrawActor;
    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {
        pDrawActor->_matWorld._14 = pDrawActor->_wall_draw_face;  //描画面番号をワールド変換行列のmatWorld._14 に埋め込む
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[i], &(pDrawActor->_matWorld));
        checkDxException(hr, D3D_OK, "WallActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
        pDrawActor = (WallActor*)(pDrawActor -> _pNext_TheSameDrawDepthLevel);
        if (i > 0) {
            //アクティブを進める
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    _pMeshSetModel->draw(this);
}


void WallActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

void WallActor::config(WalledSectionScene* prm_pWalledSectionScene, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    _pWalledSectionScene =prm_pWalledSectionScene;
    _wall_dep = _pWalledSectionScene->_wall_dep;
    _wall_width = _pWalledSectionScene->_wall_width;
    _wall_height = _pWalledSectionScene->_wall_height;
    _wall_draw_face = prm_wall_draw_face;
    if (prm_aColliBoxStretch[0] == 0) {
        _pCollisionChecker->setColliAAB(0, 0,0,0, 0,0,0);
        _pCollisionChecker->disable(0);
    } else {

        _pCollisionChecker->setColliAAB(0, -(_wall_dep/2)    - (_wall_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1)),
                                           -(_wall_height/2) - (_wall_height * (prm_aColliBoxStretch[FACE_D_IDX]-1)),
                                           -(_wall_width/2)  - (_wall_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1)),
                                            (_wall_dep/2)    + (_wall_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1)),
                                            (_wall_height/2) + (_wall_height * (prm_aColliBoxStretch[FACE_A_IDX]-1)),
                                            (_wall_width/2)  + (_wall_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1))
                                       );
         _pCollisionChecker->enable(0);
    }
}

WallActor::~WallActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}

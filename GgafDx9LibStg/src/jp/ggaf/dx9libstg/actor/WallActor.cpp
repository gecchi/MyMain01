#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

WallActor::WallActor(const char* prm_name, const char* prm_model) :
    GgafDx9MeshSetActor(prm_name,
                        prm_model,
                         "WallEffect",
                         "WallTechnique",
                         NEW CollisionChecker(this) ) {
    _class_name = "WallActor";
    _pMeshSetModel->_set_num = 16; //WallActor最大セット数は16。
    _frame_offset = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pCollisionChecker->makeCollision(1);

    _pScaler = NEW GgafDx9GeometryScaler(this);
    _ground_speed = 0;
    _wall_draw_face = 0;

    _ahDrawFace[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face001" );
    _ahDrawFace[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face002" );
    _ahDrawFace[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face003" );
    _ahDrawFace[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face004" );
    _ahDrawFace[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face005" );
    _ahDrawFace[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face006" );
    _ahDrawFace[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face007" );
    _ahDrawFace[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face008" );
    _ahDrawFace[8]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face009" );
    _ahDrawFace[9]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face010" );
    _ahDrawFace[10] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face011" );
    _ahDrawFace[11] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face012" );
    _ahDrawFace[12] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face013" );
    _ahDrawFace[13] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face014" );
    _ahDrawFace[14] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face015" );
    _ahDrawFace[15] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face016" );
    _h_wall_dep = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_wall_dep" );
    _h_wall_width = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_wall_width" );
    _h_wall_height = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_wall_height" );
    _h_distance_AlphaTarget = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_distance_AlphaTarget" );
    _pWalledScene = NULL;
    _pTarget_FrontAlpha = NULL;
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(true);  //Zバッファは書き込み有り
}

void WallActor::initialize() {
    if (_pWalledScene == NULL) {
        _pWalledScene = (WalledScene*)getPlatformScene();
        _wall_dep = _pWalledScene->_wall_dep;
        _wall_width = _pWalledScene->_wall_width;
        _wall_height = _pWalledScene->_wall_height;
        _ground_speed = _pWalledScene->_ground_speed;
    }
}

void WallActor::onActive() {

}

void WallActor::processBehavior() {
    _X = _X - _ground_speed;
}

void WallActor::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
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

    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;
    if (_pTarget_FrontAlpha) {
        hr = pID3DXEffect->SetFloat(_h_distance_AlphaTarget, -(_pTarget_FrontAlpha->_fDist_VpPlnFront));
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    } else {
        hr = pID3DXEffect->SetFloat(_h_distance_AlphaTarget, -1.0f);
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(_h_distance_AlphaTarget) に失敗しました。");
    }
    //VIEW変換行列
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_h_matView, &pCAM->_vMatrixView);
    checkDxException(hr, D3D_OK, "WallActor::processDraw() SetMatrix(_h_matView) に失敗しました。");
    //基本モデル頂点数
    hr = pID3DXEffect->SetInt(_pMeshSetEffect->_h_vertexs_num, _pMeshSetModel->_nVertices);
    checkDxException(hr, D3D_OK, "WallActor::processDraw() SetInt(_h_vertexs_num) に失敗しました。2");

//    hr = pID3DXEffect->SetFloat(_h_wall_dep, 1.0*_wall_dep/LEN_UNIT/PX_UNIT);
//    checkDxException(hr, D3D_OK, "WallActor::processDraw() SetFloat(_h_wall_dep) に失敗しました。");
//    hr = pID3DXEffect->SetFloat(_h_wall_width, 1.0*_wall_width/LEN_UNIT/PX_UNIT);
//    checkDxException(hr, D3D_OK, "WallActor::processDraw() SetFloat(_h_wall_width) に失敗しました。");
//    hr = pID3DXEffect->SetFloat(_h_wall_height, 1.0*_wall_height/LEN_UNIT/PX_UNIT);
//    checkDxException(hr, D3D_OK, "WallActor::processDraw() SetFloat(_h_wall_height) に失敗しました。");


    WallActor* pDrawActor;
    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {
        //(*_pFunc_calcRotMvWorldMatrix)(pDrawActor, pDrawActor->_matWorld);
        //GgafDx9Util::setWorldMatrix_ScRxRzRyMv(pDrawActor, pDrawActor->_matWorld);
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[i], &(pDrawActor->_matWorld));
        checkDxException(hr, D3D_OK, "WallActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
        //hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[i], &(pDrawActor->_paD3DMaterial9[0].Diffuse), sizeof(D3DCOLORVALUE) );
        //【GgafDx9MeshSetActorのマテリアルカラーについて考え方】備忘録メモ
        //本来はマテリアル１オブジェクトに複数保持し、マテリアルリストのグループ毎に設定するものだが、実行速度最適化と使用レジスタ数削減の為、各セットの[0]のマテリアルを全体のマテリアルとする。
        //したがってGgafDx9MeshSetActorはマテリアル色は8セット全てそれぞれ１色しか不可能。
        //それぞれの１色を、マテリアル色としてオブジェクト別につるため頂点カラーで実現している。
        //もともと本クラスは、同一モデル複数オブジェクトを、最大8セット同時に一回で描画しスピードアップを図ることを目的としたクラスで、たくさんマテリアルグループがあるオブジェクトには不向というか無意味である。
        //１枚テクスチャで頑張れば問題ない・・・という方針。マテリアル色で色分けしたい場合は GgafDx9MeshActor を使うしかない。

        //checkDxException(hr, D3D_OK, "WallActor::processDraw() SetValue(_ah_materialDiffuse) に失敗しました。");

        //描画面番号
        hr = pID3DXEffect->SetInt(this->_ahDrawFace[i], pDrawActor->_wall_draw_face);
        checkDxException(hr, D3D_OK, "WallActor::processDraw() SetInt(_ahDrawFace) に失敗しました。");



        pDrawActor = (WallActor*)(pDrawActor -> _pNext_TheSameDrawDepthLevel);
        if (i > 0) {
            //アクティブを進める
            //このキャストは危険である。自身のオブジェクトモデルが唯一のモデルでなければ暴走してしまう。
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    _pMeshSetModel->draw(this);
}


void WallActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}

void WallActor::config(int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    if (_pWalledScene == NULL) {
        _pWalledScene = (WalledScene*)getPlatformScene();
        _wall_dep = _pWalledScene->_wall_dep;
        _wall_width = _pWalledScene->_wall_width;
        _wall_height = _pWalledScene->_wall_height;
        _ground_speed = _pWalledScene->_ground_speed;
    }


    _wall_draw_face = prm_wall_draw_face;

    _pCollisionChecker->setColliAAB(0, -(_wall_dep/2)    - (_wall_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1)),
                                       -(_wall_height/2) - (_wall_height * (prm_aColliBoxStretch[FACE_D_IDX]-1)),
                                       -(_wall_width/2)  - (_wall_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1)),
                                        (_wall_dep/2)    + (_wall_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1)),
                                        (_wall_height/2) + (_wall_height * (prm_aColliBoxStretch[FACE_A_IDX]-1)),
                                        (_wall_width/2)  + (_wall_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1))
                                   );

}

WallActor::~WallActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}

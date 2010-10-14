#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GroundBoxActor::GroundBoxActor(const char* prm_name, const char* prm_model, int prm_box_dep, int prm_box_width, int prm_box_height) :
    GgafDx9MeshSetActor(prm_name,
                        string(string("16/") + string(prm_model)).c_str(),
                         "GroundBoxEffect",
                         "GroundBoxTechnique",
                         NEW CollisionChecker(this) ) {
    _pMeshSetModel->_set_num = 16; //GroundBoxActor最大セット数は16。
    _class_name = "GroundBoxActor";
    setHitAble(true);
    _frame_offset = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometryScaler(this);
    _ground_speed = 0;
    _box_draw_face = 0;

    _box_dep = prm_box_dep;
    _box_width = prm_box_width;
    _box_height = prm_box_height;

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
    _h_box_dep = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_box_dep" );
    _h_box_width = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_box_width" );
    _h_box_height = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_box_height" );



    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(true);  //Zバッファは書き込み有り
}

//void GroundBoxActor::processPreDraw() {
//    _pNext_TheSameDrawDepthLevel = NULL;
//    if (_is_active_flg && _can_live_flg) {
//        //背景なので背面で描画
//        GgafDx9Universe::setDrawDepthMaxLevel(this);
//    }
//}

void GroundBoxActor::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -_box_dep/2, -_box_height/2, -_box_width/2,
                                        _box_dep/2,  _box_height/2,  _box_width/2);
    _SX=_SY=_SZ = 4000;
    setBoundingSphereRadiusRate(4.0);
}

void GroundBoxActor::onActive() {
    //_box_type



}



void GroundBoxActor::processBehavior() {
    _X = _X - _ground_speed;
}
void GroundBoxActor::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void GroundBoxActor::processDraw() {
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

    //VIEW変換行列
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_h_matView, &pCAM->_vMatrixView);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(_h_matView) に失敗しました。");
    //基本モデル頂点数
    hr = pID3DXEffect->SetInt(_pMeshSetEffect->_h_vertexs_num, _pMeshSetModel->_nVertices);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetInt(_h_vertexs_num) に失敗しました。2");

    hr = pID3DXEffect->SetFloat(_h_box_dep, 1.0*_box_dep/LEN_UNIT/PX_UNIT);
    checkDxException(hr, D3D_OK, "GroundBoxActor::processDraw() SetFloat(_h_box_dep) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_h_box_width, 1.0*_box_width/LEN_UNIT/PX_UNIT);
    checkDxException(hr, D3D_OK, "GroundBoxActor::processDraw() SetFloat(_h_box_width) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_h_box_height, 1.0*_box_height/LEN_UNIT/PX_UNIT);
    checkDxException(hr, D3D_OK, "GroundBoxActor::processDraw() SetFloat(_h_box_height) に失敗しました。");


    GroundBoxActor* pDrawActor;
    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {
        //(*_pFunc_calcRotMvWorldMatrix)(pDrawActor, pDrawActor->_matWorld);
        //GgafDx9Util::setWorldMatrix_ScRxRzRyMv(pDrawActor, pDrawActor->_matWorld);
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[i], &(pDrawActor->_matWorld));
        checkDxException(hr, D3D_OK, "GroundBoxActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
        //hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[i], &(pDrawActor->_paD3DMaterial9[0].Diffuse), sizeof(D3DCOLORVALUE) );
        //【GgafDx9MeshSetActorのマテリアルカラーについて考え方】備忘録メモ
        //本来はマテリアル１オブジェクトに複数保持し、マテリアルリストのグループ毎に設定するものだが、実行速度最適化と使用レジスタ数削減の為、各セットの[0]のマテリアルを全体のマテリアルとする。
        //したがってGgafDx9MeshSetActorはマテリアル色は8セット全てそれぞれ１色しか不可能。
        //それぞれの１色を、マテリアル色としてオブジェクト別につるため頂点カラーで実現している。
        //もともと本クラスは、同一モデル複数オブジェクトを、最大8セット同時に一回で描画しスピードアップを図ることを目的としたクラスで、たくさんマテリアルグループがあるオブジェクトには不向というか無意味である。
        //１枚テクスチャで頑張れば問題ない・・・という方針。マテリアル色で色分けしたい場合は GgafDx9MeshActor を使うしかない。

        //checkDxException(hr, D3D_OK, "GroundBoxActor::processDraw() SetValue(_ah_materialDiffuse) に失敗しました。");

        //描画面番号
        hr = pID3DXEffect->SetInt(this->_ahDrawFace[i], pDrawActor->_box_draw_face);
        checkDxException(hr, D3D_OK, "GroundBoxActor::processDraw() SetInt(_ahDrawFace) に失敗しました。");



        pDrawActor = (GroundBoxActor*)(pDrawActor -> _pNext_TheSameDrawDepthLevel);
        if (i > 0) {
            //アクティブを進める
            //このキャストは危険である。自身のオブジェクトモデルが唯一のモデルでなければ暴走してしまう。
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    _pMeshSetModel->draw(this);
}















//
//void GroundBoxActor::processDraw() {
//    static ID3DXEffect* pID3DXEffect;
//    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
//    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matView, &pCAM->_vMatrixView );
//    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(g_matView) に失敗しました。");
//    GgafDx9Util::setWorldMatrix_RxRzRyMv(this, _matWorld);
//    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
//    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
//
////    // Zバッファを無効に
////    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
////    // Zバッファ書き込み不可
////    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //カリングOFF
//    _pMeshModel->draw(this);
//
////    // Zバッファを有効に
////    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
////    // Zバッファ書き込み可
////    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
//
//}



void GroundBoxActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}

void GroundBoxActor::config(int prm_box_draw_face, int* prm_aColliBoxStretch) {
    _box_draw_face = prm_box_draw_face;

    _pCollisionChecker->setColliAAB(0, -(_box_dep/2)    - (_box_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1)),
                                       -(_box_height/2) - (_box_height * (prm_aColliBoxStretch[FACE_D_IDX]-1)),
                                       -(_box_width/2)  - (_box_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1)),
                                        (_box_dep/2)    + (_box_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1)),
                                        (_box_height/2) + (_box_height * (prm_aColliBoxStretch[FACE_A_IDX]-1)),
                                        (_box_width/2)  + (_box_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1))
                                   );




//                                        _box_dep/2,  _box_height/2,  _box_width/2);
//
//    GgafDx9CollisionPart* pColliPart = _pCollisionChecker->_pCollisionArea->_papColliPart[0];
//    //pColliPart->_aab_x1 -= _box_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1);
//    pColliPart->_aab_x2 += _box_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1);
//    //pColliPart->_aab_y1 -= _box_height * (prm_aColliBoxStretch[FACE_D_IDX]-1);
//    pColliPart->_aab_y2 += _box_height * (prm_aColliBoxStretch[FACE_A_IDX]-1);
//    //pColliPart->_aab_z1 -= _box_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1);
//    pColliPart->_aab_z2 += _box_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1);

}

GroundBoxActor::~GroundBoxActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}

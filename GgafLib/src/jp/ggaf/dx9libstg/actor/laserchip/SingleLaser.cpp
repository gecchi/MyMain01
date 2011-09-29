#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


SingleLaser::SingleLaser(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
             GgafDx9MeshSetActor(prm_name,
                                 string("27/" + string(prm_model_id)).c_str(),
                                 "SingleLaserEffect",
                                 "SingleLaserTechnique",
                                 prm_pStat,
                                 NEW CollisionChecker(this) ) {

    _pMeshSetModel->_set_num = 27; //現在のシングルレーザーの最大セット数は27。

    _class_name = "SingleLaser";
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _ah_matWorld[0]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld001" );
    _ah_matWorld[1]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld002" );
    _ah_matWorld[2]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld003" );
    _ah_matWorld[3]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld004" );
    _ah_matWorld[4]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld005" );
    _ah_matWorld[5]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld006" );
    _ah_matWorld[6]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld007" );
    _ah_matWorld[7]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld008" );
    _ah_matWorld[8]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld009" );
    _ah_matWorld[9]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld010" );
    _ah_matWorld[10]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld011" );
    _ah_matWorld[11]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld012" );
    _ah_matWorld[12]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld013" );
    _ah_matWorld[13]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld014" );
    _ah_matWorld[14]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld015" );
    _ah_matWorld[15]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld016" );
    _ah_matWorld[16]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld017" );
    _ah_matWorld[17]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld018" );
    _ah_matWorld[18]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld019" );
    _ah_matWorld[19]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld020" );
    _ah_matWorld[20]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld021" );
    _ah_matWorld[21]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld022" );
    _ah_matWorld[22]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld023" );
    _ah_matWorld[23]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld024" );
    _ah_matWorld[24]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld025" );
    _ah_matWorld[25]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld026" );
    _ah_matWorld[26]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld027" );
//    _ah_matWorld[27]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld028" );
//    _ah_matWorld[28]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld029" );
//    _ah_matWorld[29]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld030" );


    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し

}

//void SingleLaser::onCreateModel() {
//    _pMeshSetModel->_set_num = 27; //現在のSingleレーザーの最大セット数は27。
//    _TRACE_("SingleLaser::onCreateModel() "<<_pMeshSetModel->getName()<<" のセット数は "<< _pMeshSetModel->_set_num<<" 個に強制されました。");
//}

void SingleLaser::processDraw() {
    _draw_set_num = 0; //GgafDx9MeshSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    //基本モデル頂点数
    GgafDx9DrawableActor* pDrawActor = this;
    SingleLaser* pSingleLaserChip = NULL;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pModel == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pSingleLaserChip = (SingleLaser*)pDrawActor;

                hr = pID3DXEffect->SetMatrix(this->_ah_matWorld[_draw_set_num], &(pSingleLaserChip->_matWorld));
                checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(g_matWorld) _pMeshSetEffect="<<_pMeshSetEffect->getName() << " pDrawActor->_matWorld="<<pDrawActor->_matWorld<<" pDrawActor="<<pDrawActor->getName()<<" _draw_set_num="<<_draw_set_num<<" に失敗しました。");

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
    GgafDx9Universe::_pActor_DrawActive = pSingleLaserChip; //描画セットの最後アクターをセット
    _pMeshSetModel->draw(this, _draw_set_num);
}

void SingleLaser::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

SingleLaser::~SingleLaser() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
}

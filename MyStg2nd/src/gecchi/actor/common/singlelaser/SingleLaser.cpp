#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

SingleLaser::SingleLaser(const char* prm_name, const char* prm_model_id) :
             GgafDx9MeshSetActor(prm_name,
                                 prm_model_id,
                                 "SingleLaserEffect",
                                 "SingleLaserTechnique",
                                 NEW CollisionChecker(this) ) {
    _class_name = "SingleLaser";
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _ahMatWorld[0]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld001" );
    _ahMatWorld[1]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld002" );
    _ahMatWorld[2]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld003" );
    _ahMatWorld[3]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld004" );
    _ahMatWorld[4]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld005" );
    _ahMatWorld[5]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld006" );
    _ahMatWorld[6]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld007" );
    _ahMatWorld[7]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld008" );
    _ahMatWorld[8]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld009" );
    _ahMatWorld[9]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld010" );
    _ahMatWorld[10]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld011" );
    _ahMatWorld[11]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld012" );
    _ahMatWorld[12]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld013" );
    _ahMatWorld[13]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld014" );
    _ahMatWorld[14]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld015" );
    _ahMatWorld[15]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld016" );
    _ahMatWorld[16]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld017" );
    _ahMatWorld[17]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld018" );
    _ahMatWorld[18]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld019" );
    _ahMatWorld[19]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld020" );
    _ahMatWorld[20]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld021" );
    _ahMatWorld[21]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld022" );
    _ahMatWorld[22]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld023" );
    _ahMatWorld[23]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld024" );
    _ahMatWorld[24]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld025" );
    _ahMatWorld[25]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld026" );
    _ahMatWorld[26]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld027" );
//    _ahMatWorld[27]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld028" );
//    _ahMatWorld[28]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld029" );
//    _ahMatWorld[29]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld030" );
}

void SingleLaser::processDraw() {
    _draw_set_num = 1; //GgafDx9MeshSetActorの同じモデルが連続しているカウント数。同一描画深度は一度に描画する。
    GgafDx9DrawableActor* _pNextDrawActor;
    _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            if (_pNextDrawActor->_pGgafDx9Model == _pMeshSetModel && _pNextDrawActor->isActive()) {
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
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_hMatView, &pCAM->_vMatrixView);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(_hMatView) に失敗しました。");
    //基本モデル頂点数
    hr = pID3DXEffect->SetInt(_pMeshSetEffect->_h_nVertexs, _pMeshSetModel->_nVertices);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetInt(_h_nVertexs) に失敗しました。2");

    GgafDx9DrawableActor *pDrawActor;
    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {
        hr = pID3DXEffect->SetMatrix(this->_ahMatWorld[i], &(pDrawActor->_matWorld));
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(g_matWorld) _pMeshSetEffect="<<_pMeshSetEffect->getName() << " pDrawActor->_matWorld="<<pDrawActor->_matWorld<<" pDrawActor="<<pDrawActor->getName()<<" _draw_set_num="<<_draw_set_num<<" i="<<i<<" に失敗しました。");
        pDrawActor = pDrawActor -> _pNext_TheSameDrawDepthLevel;
        if (i > 0) {
            //アクティブを進める
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }

    //Zバッファは考慮して描画するが、Zバッファは書き込まない。
    // Zバッファを無効に
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    // Zバッファ書き込み不可
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
    _pMeshSetModel->draw(this);
    // Zバッファを有効に
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Zバッファ書き込み可
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void SingleLaser::drawHitArea() {
    CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}

SingleLaser::~SingleLaser() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
}

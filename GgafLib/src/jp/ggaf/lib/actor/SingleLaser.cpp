#include "jp/ggaf/lib/actor/SingleLaser.h"

#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/actor/ColliAABActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SingleLaser::SingleLaser(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
             GgafDxMeshSetActor(prm_name,
                                 std::string("26/" + std::string(prm_model_id)).c_str(),
                                 "SingleLaserEffect",
                                 "SingleLaserTechnique",
                                 prm_pStat,
                                 NEW CollisionChecker3D(this) ) {

    _pMeshSetModel->_set_num = 26; //現在のシングルレーザーの最大セット数強制上書き。

    _class_name = "SingleLaser";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _ah_matWorld[0]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld001" );
    _ah_matWorld[1]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld002" );
    _ah_matWorld[2]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld003" );
    _ah_matWorld[3]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld004" );
    _ah_matWorld[4]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld005" );
    _ah_matWorld[5]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld006" );
    _ah_matWorld[6]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld007" );
    _ah_matWorld[7]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld008" );
    _ah_matWorld[8]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld009" );
    _ah_matWorld[9]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld010" );
    _ah_matWorld[10]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld011" );
    _ah_matWorld[11]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld012" );
    _ah_matWorld[12]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld013" );
    _ah_matWorld[13]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld014" );
    _ah_matWorld[14]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld015" );
    _ah_matWorld[15]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld016" );
    _ah_matWorld[16]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld017" );
    _ah_matWorld[17]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld018" );
    _ah_matWorld[18]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld019" );
    _ah_matWorld[19]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld020" );
    _ah_matWorld[20]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld021" );
    _ah_matWorld[21]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld022" );
    _ah_matWorld[22]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld023" );
    _ah_matWorld[23]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld024" );
    _ah_matWorld[24]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld025" );
    _ah_matWorld[25]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld026" );
//    _ah_matWorld[26]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld027" );
//    _ah_matWorld[27]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld028" );
//    _ah_matWorld[28]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld029" );
//    _ah_matWorld[29]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld030" );


    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し

}

//void SingleLaser::onCreateModel() {
//    _pMeshSetModel->_set_num = 27; //現在のSingleレーザーの最大セット数は27。
//    _TRACE_("SingleLaser::onCreateModel() "<<_pMeshSetModel->getName()<<" のセット数は "<< _pMeshSetModel->_set_num<<" 個に強制されました。");
//}

void SingleLaser::processDraw() {
    int draw_set_num = 0; //GgafDxMeshSetActorの同じモデルで同じテクニックが
                          //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    //基本モデル頂点数
    GgafDxDrawableActor* pDrawActor = this;
    SingleLaser* pSingleLaserChip = nullptr;
    int model_Set_num = _pMeshSetModel->_set_num;

    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pSingleLaserChip = (SingleLaser*)pDrawActor;
            hr = pID3DXEffect->SetMatrix(this->_ah_matWorld[draw_set_num], &(pSingleLaserChip->_matWorld));
            checkDxException(hr, D3D_OK, "GgafDxMeshSetActor::processDraw() SetMatrix(g_matWorld) _pMeshSetEffect="<<_pMeshSetEffect->getName() << " pDrawActor->_matWorld="<<pDrawActor->_matWorld<<" pDrawActor="<<pDrawActor->getName()<<" draw_set_num="<<draw_set_num<<" に失敗しました。");
            draw_set_num++;
            if (draw_set_num >= model_Set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextActor_in_draw_depth_level;
        } else {
            break;
        }
    }
    GgafDxUniverse::_pActor_draw_active = pSingleLaserChip; //描画セットの最後アクターをセット
    _pMeshSetModel->GgafDxMeshSetModel::draw(this, draw_set_num);
}

void SingleLaser::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

SingleLaser::~SingleLaser() {
    GGAF_DELETE(_pColliChecker);
}

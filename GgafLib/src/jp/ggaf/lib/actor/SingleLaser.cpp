#include "jp/ggaf/lib/actor/SingleLaser.h"

#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#ifdef MY_DEBUG
#include "jp/ggaf/lib/actor/ColliAABoxActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliAAPyramidActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#endif

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


SingleLaser::SingleLaser(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
             GgafDxMeshSetActor(prm_name,
                                 std::string("26/" + std::string(prm_model_id)).c_str(),
                                 "SingleLaserEffect",
                                 "SingleLaserTechnique",
                                 prm_pStat,
                                 UTIL::createChecker(this) ) {

    _pMeshSetModel->_set_num = 26; //現在のシングルレーザーの最大セット数強制上書き。

    _class_name = "SingleLaser";
    _pColliChecker = (CollisionChecker3D*)_pChecker;

    setZEnableDraw(true);    //描画時、Zバッファ値は考慮される
    setZWriteEnable(false);  //自身のZバッファを書き込みしない

    static volatile bool is_init = SingleLaser::initStatic(this); //静的メンバ初期化
}

D3DXHANDLE SingleLaser::_ah_matWorld[26];
bool SingleLaser::initStatic(SingleLaser* prm_pSingleLaser) {
    ID3DXEffect* const pID3DXEffect = prm_pSingleLaser->getEffect()->_pID3DXEffect;
    SingleLaser::_ah_matWorld[0]   = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld001" );
    SingleLaser::_ah_matWorld[1]   = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld002" );
    SingleLaser::_ah_matWorld[2]   = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld003" );
    SingleLaser::_ah_matWorld[3]   = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld004" );
    SingleLaser::_ah_matWorld[4]   = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld005" );
    SingleLaser::_ah_matWorld[5]   = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld006" );
    SingleLaser::_ah_matWorld[6]   = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld007" );
    SingleLaser::_ah_matWorld[7]   = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld008" );
    SingleLaser::_ah_matWorld[8]   = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld009" );
    SingleLaser::_ah_matWorld[9]   = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld010" );
    SingleLaser::_ah_matWorld[10]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld011" );
    SingleLaser::_ah_matWorld[11]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld012" );
    SingleLaser::_ah_matWorld[12]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld013" );
    SingleLaser::_ah_matWorld[13]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld014" );
    SingleLaser::_ah_matWorld[14]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld015" );
    SingleLaser::_ah_matWorld[15]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld016" );
    SingleLaser::_ah_matWorld[16]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld017" );
    SingleLaser::_ah_matWorld[17]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld018" );
    SingleLaser::_ah_matWorld[18]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld019" );
    SingleLaser::_ah_matWorld[19]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld020" );
    SingleLaser::_ah_matWorld[20]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld021" );
    SingleLaser::_ah_matWorld[21]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld022" );
    SingleLaser::_ah_matWorld[22]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld023" );
    SingleLaser::_ah_matWorld[23]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld024" );
    SingleLaser::_ah_matWorld[24]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld025" );
    SingleLaser::_ah_matWorld[25]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld026" );
//    SingleLaser::_ah_matWorld[26]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld027" );
//    SingleLaser::_ah_matWorld[27]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld028" );
//    SingleLaser::_ah_matWorld[28]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld029" );
//    SingleLaser::_ah_matWorld[29]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld030" );
    return true;
}


void SingleLaser::processDraw() {
    int draw_set_num = 0; //GgafDxMeshSetActorの同じモデルで同じテクニックが
                          //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* const pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    //基本モデル頂点数
    GgafDxFigureActor* pDrawActor = this;
    SingleLaser* pSingleLaserChip = nullptr;
    int model_Set_num = _pMeshSetModel->_set_num;

    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pSingleLaserChip = (SingleLaser*)pDrawActor;
            hr = pID3DXEffect->SetMatrix(SingleLaser::_ah_matWorld[draw_set_num], &(pSingleLaserChip->_matWorld));
            checkDxException(hr, D3D_OK, "pDrawActor->_matWorld="<<pDrawActor->_matWorld<<" pDrawActor="<<pDrawActor->getName()<<" draw_set_num="<<draw_set_num<<" に失敗しました。");
            draw_set_num++;
            if (draw_set_num >= model_Set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    GgafDxSpacetime::_pActor_draw_active = pSingleLaserChip; //描画セットの最後アクターをセット
    _pMeshSetModel->GgafDxMeshSetModel::draw(this, draw_set_num);
}

void SingleLaser::drawHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliAAPyramidActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
#endif
}

SingleLaser::~SingleLaser() {
    GGAF_DELETE(_pColliChecker);
}

#include "jp/ggaf/lib/actor/SingleLaser.h"

#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/effect/SingleLaserEffect.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


SingleLaser::SingleLaser(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
             GgafDxMeshSetActor(prm_name,
                                 std::string("26/" + std::string(prm_model_id)).c_str(),
                                 TYPE_MESHSET_MODEL,
                                 "SingleLaserEffect",
                                 TYPE_SINGLELASER_EFFECT,
                                 "SingleLaserTechnique",
                                 prm_pStat,
                                 UTIL::createChecker(this) ) {

    _pMeshSetModel->_set_num = 26; //現在のシングルレーザーの最大セット数強制上書き。

    _class_name = "SingleLaser";
    _pColliChecker = (CollisionChecker*)_pChecker;

    setZEnableDraw(true);    //描画時、Zバッファ値は考慮される
    setZWriteEnable(false);  //自身のZバッファを書き込みしない
}

void SingleLaser::processDraw() {
    int draw_set_num = 0; //GgafDxMeshSetActorの同じモデルで同じテクニックが
                          //連続しているカウント数。同一描画深度は一度に描画する。
    SingleLaserEffect* pSingleLaserEffect = (SingleLaserEffect*)_pMeshSetEffect;
    ID3DXEffect* const pID3DXEffect = pSingleLaserEffect->_pID3DXEffect;
    HRESULT hr;
    //基本モデル頂点数
    GgafDxFigureActor* pDrawActor = this;
    SingleLaser* pSingleLaserChip = nullptr;
    int model_Set_num = _pMeshSetModel->_set_num;

    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pSingleLaserChip = (SingleLaser*)pDrawActor;
            hr = pID3DXEffect->SetMatrix(pSingleLaserEffect->_ah_matWorld[draw_set_num], &(pSingleLaserChip->_matWorld));
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
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

SingleLaser::~SingleLaser() {
    GGAF_DELETE(_pColliChecker);
}

#include "jp/ggaf/dxcore/actor/GgafDxPointSpriteActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxPointSpriteModel.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxPointSpriteActor::GgafDxPointSpriteActor(const char* prm_name,
                                               const char* prm_model_id,
                                               const char* prm_effect_id,
                                               const char* prm_technique,
                                               GgafStatus* prm_pStat,
                                               GgafDxChecker* prm_pChecker) :

                                                   GgafDxFigureActor(prm_name,
                                                                       prm_model_id,
                                                                       "P",
                                                                       prm_effect_id,
                                                                       "P",
                                                                       prm_technique,
                                                                       prm_pStat,
                                                                       prm_pChecker),
_pPointSpriteModel((GgafDxPointSpriteModel*)_pModel),
_pPointSpriteEffect((GgafDxPointSpriteEffect*)_pEffect),
_pUvFlipper(NEW GgafDxUvFlipper(_pPointSpriteModel->_papTextureConnection[0]->peek())) {

    _obj_class |= Obj_GgafDxPointSpriteActor;
    _class_name = "GgafDxPointSpriteActor";
    _pFunc_calc_rot_mv_world_matrix = UTIL::setWorldMatrix_RxRzRyMv;
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
    _pUvFlipper->setRotation(_pPointSpriteModel->_texture_split_rowcol,
                             _pPointSpriteModel->_texture_split_rowcol );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
    setZEnable(false);
    setZWriteEnable(false);
}

void GgafDxPointSpriteActor::setAlpha(float prm_alpha) {
    _alpha = prm_alpha;
    //GgafDxPointSpriteActorはメッシュαも設定（シェーダーで参照するため）
    _paMaterial[0].Ambient.a = _alpha;
    _paMaterial[0].Diffuse.a = _alpha;
}

void GgafDxPointSpriteActor::addAlpha(float prm_alpha) {
    _alpha += prm_alpha;
    //GgafDxPointSpriteActorはメッシュαも設定（シェーダーで参照するため）
    _paMaterial[0].Ambient.a = _alpha;
    _paMaterial[0].Diffuse.a = _alpha;
}

void GgafDxPointSpriteActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pPointSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pPointSpriteEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pPointSpriteEffect->_h_dist_VpInfrontPlane, -_dest_from_vppln_infront);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(g_h_dist_VpInfrontPlane) に失敗しました。");
    hr = pID3DXEffect->SetInt(_pPointSpriteEffect->_hUvFlipPtnNo, _pUvFlipper->_pattno_uvflip_now);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetInt(_hUvFlipPtnNo) に失敗しました。");
    //ポイントスプライトON
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
    //スケールはシェーダー内で独自計算
    _pPointSpriteModel->GgafDxPointSpriteModel::draw(this);
    //ポイントスプライトOFF
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
}

GgafDxPointSpriteActor::~GgafDxPointSpriteActor() {
    delete _pUvFlipper;
}

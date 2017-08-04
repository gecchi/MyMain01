#include "jp/ggaf/lib/actor/WallPartsActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/scene/WalledSectionScene.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/DefaultGod.h"
#ifdef MY_DEBUG
#include "jp/ggaf/lib/actor/ColliAABoxActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliAAPyramidActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#endif

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WallPartsActor::WallPartsActor(const char* prm_name,
                               const char* prm_model_id,
                               const char* prm_effect_id,
                               const char* prm_technique,
                               GgafStatus* prm_pStat) :

                        GgafDxMeshSetActor(prm_name,
                                           prm_model_id,
                                           prm_effect_id,
                                           prm_technique,
                                           prm_pStat,
                                           UTIL::createChecker(this) ) {
    _class_name = "WallPartsActor";
    _obj_class |= Obj_WallPartsActor;
    _pColliChecker = (CollisionChecker*)_pChecker;
    _wall_draw_face = 0;
    _pos_info = 0;
    _pWalledSectionScene = nullptr;

    _wall_dep = 0;
    _wall_width = 0;
    _wall_height = 0;
    setHitAble(true);
}

void WallPartsActor::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (prm_pOtherActor->instanceOf(Obj_LaserChip)) { //相手がレーザー
        LaserChip* pLaserChip = (LaserChip*)prm_pOtherActor;
        if (pLaserChip->getInfrontChip() == nullptr || pLaserChip->_can_chikei_hit) {
            //相手が先端チップか、1/16 の地形当たり判定有りチップ
            GgafDxFigureActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxFigureActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}



void WallPartsActor::initialize() {

}

void WallPartsActor::onActive() {

}

void WallPartsActor::processBehavior() {
}

void WallPartsActor::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void WallPartsActor::processPreDraw() {
    if (_wall_draw_face > 0) {
        //描画面がある場合は表示対象にする
        GgafDxFigureActor::processPreDraw();
    }
}

bool WallPartsActor::isOutOfSpacetime() const {
    GgafDxSpacetime* pSpacetime =  P_GOD->getSpacetime();
    if (pSpacetime->_x_bound_left <= _x+_wall_dep) {
        return false;
    }
    return true;
}

int WallPartsActor::isOutOfView() {
    if (_offscreen_kind == -1) {
        dxcoord bound = getModel()->_bounding_sphere_radius * _rate_of_bounding_sphere_radius*2.0f;//掛ける2は境界球を大きくして、画面境界のチラツキを抑える
        if (_dest_from_vppln_top < bound) {
            if (_dest_from_vppln_bottom < bound) {
                if (_dest_from_vppln_left < bound) {
                    if (_dest_from_vppln_right < bound) {
                        if (_dest_from_vppln_infront < bound) {
                            //if (_dest_from_vppln_back < bound) {
                            //    //Viewport範囲内
                            //    _offscreen_kind = 0;
                            //} else {
                            //    //奥平面より奥で範囲外
                            //    _offscreen_kind = 6;
                            //}

                            //奥平面判定は無し
                            _offscreen_kind = 0;
                        } else {
                            //手前平面より手前で範囲外
                            _offscreen_kind = 5;
                        }
                    } else {
                        //右平面より右で範囲外
                        _offscreen_kind = 4;
                    }
                } else {
                    //左平面より左で範囲外
                    _offscreen_kind = 3;
                }
            } else {
                //下平面より下で範囲外
                _offscreen_kind = 2;
            }
        } else {
            //上平面より上で範囲外
            _offscreen_kind = 1;
        }
    }
    return _offscreen_kind;
}


void WallPartsActor::config(WalledSectionScene* prm_pWalledSectionScene, int prm_pos_info, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    _pWalledSectionScene =prm_pWalledSectionScene;
    _wall_dep = _pWalledSectionScene->_wall_dep;
    _wall_width = _pWalledSectionScene->_wall_width;
    _wall_height = _pWalledSectionScene->_wall_height;
    _wall_draw_face = prm_wall_draw_face;
    _pos_info = prm_pos_info;
}

void WallPartsActor::drawHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliAAPyramidActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
#endif
}

WallPartsActor::~WallPartsActor() {
    GGAF_DELETE(_pColliChecker);
}

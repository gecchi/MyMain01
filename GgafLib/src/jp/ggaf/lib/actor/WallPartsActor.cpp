#include "stdafx.h"
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
                                            NEW CollisionChecker(this) ) {
    _class_name = "WallPartsActor";
    _obj_class |= Obj_WallPartsActor;
    _pColliChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);
    _wall_draw_face = 0;
    _pos_prism = 0;
    _pWalledSectionScene = NULL;

    _wall_dep = 0;
    _wall_width = 0;
    _wall_height = 0;
    setHitAble(true);

}

void WallPartsActor::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (prm_pOtherActor->instanceOf(Obj_LaserChip)) {
        LaserChip* pLaserChip = (LaserChip*)prm_pOtherActor;
        if (pLaserChip->_chip_kind != 2 || pLaserChip->_can_chikei_hit) {
            GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}



void WallPartsActor::initialize() {

}

void WallPartsActor::onActive() {

}

void WallPartsActor::processBehavior() {
}

void WallPartsActor::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void WallPartsActor::processPreDraw() {
    if (_wall_draw_face > 0) {
        //描画面がある場合は表示対象にする
        GgafDxDrawableActor::processPreDraw();
    }
}

bool WallPartsActor::isOutOfUniverse() {
    if (_X+_wall_dep < GgafDxUniverse::_X_goneLeft) {
        return true;
    } else {
        return false;
    }
}

int WallPartsActor::isOutOfView() {
    //_TRACE_("name="<<getName()<<" _bounding_sphere_radius="<<_bounding_sphere_radius);
    if (_offscreen_kind == -1) {
        dxcoord bound = _bounding_sphere_radius * _rate_of_bounding_sphere_radius*2;//掛ける2は境界球を大きくして、画面境界のチラツキを抑える
        if (_dest_from_vppln_top < bound) {
            if (_dest_from_vppln_bottom < bound) {
                if (_dest_from_vppln_left < bound) {
                    if (_dest_from_vppln_right < bound) {
                        if (_dest_from_vppln_front < bound) {
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


void WallPartsActor::config(WalledSectionScene* prm_pWalledSectionScene, int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    _pWalledSectionScene =prm_pWalledSectionScene;
    _wall_dep = _pWalledSectionScene->_wall_dep;
    _wall_width = _pWalledSectionScene->_wall_width;
    _wall_height = _pWalledSectionScene->_wall_height;
    _wall_draw_face = prm_wall_draw_face;
    _pos_prism = prm_pos_prism;
}

void WallPartsActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

WallPartsActor::~WallPartsActor() {
    DELETE_IMPOSSIBLE_NULL(_pColliChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}

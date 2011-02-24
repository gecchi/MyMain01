#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

WallActor::WallActor(const char* prm_name,
                     const char* prm_model_id,
                     const char* prm_effect_id,
                     const char* prm_technique) :

                        GgafDx9MeshSetActor(prm_name,
                                            prm_model_id,
                                            prm_effect_id,
                                            prm_technique,
                                            NEW CollisionChecker(this) ) {
    _class_name = "WallActor";
    _obj_class |= Obj_WallActor;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9Scaler(this);
    _wall_draw_face = 0;
    _pos_prism = 0;
    _pWalledSectionScene = NULL;
}

void WallActor::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (prm_pOtherActor->_obj_class & Obj_LaserChip) {
        LaserChip* pLaserChip = (LaserChip*)prm_pOtherActor;
        if (pLaserChip->_chip_kind != 2 || pLaserChip->_can_chikei_hit) {
            GgafDx9DrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDx9DrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}



void WallActor::initialize() {
//    if (_pWalledSectionScene == NULL) {
//        _pWalledSectionScene = (WalledSectionScene*)getPlatformScene();
//        _TRACE_("ini getPlatformScene() = _pWalledSectionScene = "<<_pWalledSectionScene->getName());
//        _wall_dep = _pWalledSectionScene->_wall_dep;
//        _wall_width = _pWalledSectionScene->_wall_width;
//        _wall_height = _pWalledSectionScene->_wall_height;
//    }
    setHitAble(true);
}

void WallActor::onActive() {

}

void WallActor::processBehavior() {
}

void WallActor::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void WallActor::processPreDraw() {
    if (_wall_draw_face > 0) {
        //ï`âÊñ Ç™Ç†ÇÈèÍçáÇÕï\é¶ëŒè€Ç…Ç∑ÇÈ
        GgafDx9DrawableActor::processPreDraw();
    }
}

bool WallActor::isOutOfUniverse() {
    if (GgafDx9Universe::_X_goneLeft < _X) {
        return false;
    }
    return true;
}

void WallActor::config(WalledSectionScene* prm_pWalledSectionScene, int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    _pWalledSectionScene =prm_pWalledSectionScene;
    _wall_dep = _pWalledSectionScene->_wall_dep;
    _wall_width = _pWalledSectionScene->_wall_width;
    _wall_height = _pWalledSectionScene->_wall_height;
    _wall_draw_face = prm_wall_draw_face;
    _pos_prism = prm_pos_prism;
}

void WallActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

WallActor::~WallActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}

#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

WallPartsActor::WallPartsActor(const char* prm_name,
                                 const char* prm_model_id,
                                 const char* prm_effect_id,
                                 const char* prm_technique,
                                 GgafStatus* prm_pStat) :

                        GgafDx9MeshSetActor(prm_name,
                                            prm_model_id,
                                            prm_effect_id,
                                            prm_technique,
                                            prm_pStat,
                                            NEW CollisionChecker(this) ) {
    _class_name = "WallPartsActor";
    _obj_class |= Obj_WallPartsActor;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9Scaler(this);
    _wall_draw_face = 0;
    _pos_prism = 0;
    _pWalledSectionScene = NULL;
}

void WallPartsActor::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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



void WallPartsActor::initialize() {
//    if (_pWalledSectionScene == NULL) {
//        _pWalledSectionScene = (WalledSectionScene*)getPlatformScene();
//        _TRACE_("ini getPlatformScene() = _pWalledSectionScene = "<<_pWalledSectionScene->getName());
//        _wall_dep = _pWalledSectionScene->_wall_dep;
//        _wall_width = _pWalledSectionScene->_wall_width;
//        _wall_height = _pWalledSectionScene->_wall_height;
//    }
    setHitAble(true);
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
        //•`‰æ–Ê‚ª‚ ‚éê‡‚Í•\Ž¦‘ÎÛ‚É‚·‚é
        GgafDx9DrawableActor::processPreDraw();
    }
}

bool WallPartsActor::isOutOfUniverse() {
    if (GgafDx9Universe::_X_goneLeft > _X) {
        return true;
    } else {
        return false;
    }
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
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

WallPartsActor::~WallPartsActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}

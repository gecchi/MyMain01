#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
//
//CollisionCheckerLaserChip::CollisionCheckerLaserChip(GgafDxGeometricActor* prm_pActor) : CollisionChecker(prm_pActor) {
//}
//
//bool CollisionCheckerLaserChip::isHit(GgafDxCore::GgafDxChecker* prm_pOppChecker) {
//    GgafDxCore::GgafDxGeometricActor* pOppActor = prm_pOppChecker->getTargetActor();
//    if ((_pActor->_obj_class & Obj_LaserChip) && (pOppActor->_obj_class & Obj_WallPartsActor)) {
//        LaserChip* pLaserChip = (LaserChip*)_pActor;
//        if (pLaserChip->_chip_kind != 2 || pLaserChip->_can_chikei_hit) {
//            return CollisionChecker::isHit(prm_pOppChecker);
//        } else {
//            return false;
//        }
//    } else if ((_pActor->_obj_class & Obj_WallPartsActor) && (pOppActor->_obj_class & Obj_LaserChip)) {
//        LaserChip* pLaserChip = (LaserChip*)pOppActor;
//        if (pLaserChip->_chip_kind != 2 || pLaserChip->_can_chikei_hit) {
//            return CollisionChecker::isHit(prm_pOppChecker);
//        } else {
//            return false;
//        }
//    } else {
//        return CollisionChecker::isHit(prm_pOppChecker);
//    }
//}
//
//
//
//CollisionCheckerLaserChip::~CollisionCheckerLaserChip() {
//}

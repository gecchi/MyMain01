#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
//
//CollisionCheckerLaserChip::CollisionCheckerLaserChip(GgafDx9GeometricActor* prm_pActor) : CollisionChecker(prm_pActor) {
//}
//
//bool CollisionCheckerLaserChip::isHit(GgafDx9Core::GgafDx9Checker* prm_pOppChecker) {
//    GgafDx9Core::GgafDx9GeometricActor* pOppActor = prm_pOppChecker->getTargetActor();
//    if ((_pActor->_actor_class & Obj_LaserChip) && (pOppActor->_actor_class & Obj_WallActor)) {
//        LaserChip* pLaserChip = (LaserChip*)_pActor;
//        if (pLaserChip->_chip_kind != 2 || pLaserChip->_can_chikei_hit) {
//            return CollisionChecker::isHit(prm_pOppChecker);
//        } else {
//            return false;
//        }
//    } else if ((_pActor->_actor_class & Obj_WallActor) && (pOppActor->_actor_class & Obj_LaserChip)) {
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

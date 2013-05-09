#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyHermioneArmWeak::EnemyHermioneArmWeak(const char* prm_name) :
        EnemyHermioneArm(prm_name, "HermioneArmWeak", STATUS(EnemyHermioneArmWeak)) {
    _class_name = "EnemyHermioneArmWeak";
}

void EnemyHermioneArmWeak::onCreateModel() {
}

void EnemyHermioneArmWeak::initialize() {
    EnemyHermioneArm::initialize();
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyHermioneArmWeak::onHit(GgafActor* prm_pOtherActor) {

    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //”j‰óŽž
        _pSeTx->play3D(SE_EXPLOSION);

        //˜r‚Ì‚Ý”š”­
        if (getParent()) {
            getParent()->throwEventUpperTree(EVENT_HERMIONE_SAYONARA);
        }
        if (getSubFirst()) {
            getSubFirst()->throwEventLowerTree(EVENT_HERMIONE_SAYONARA);
        }
        //ª–{‘Ì(EnemyHermione) ‚É EVENT_HERMIONE_SAYONARA ‚ÌƒCƒxƒ“ƒgˆ—‚Í–³‚¢‚Ì‚Å
        //‚±‚Ìˆ—‚ÅA˜r‚Ì‚Ý”š”­‚Æ‚È‚éB
    } else {
        //”ñ”j‰óŽž
        _pSeTx->play3D(SE_DAMAGED);
    }
}


EnemyHermioneArmWeak::~EnemyHermioneArmWeak() {

}

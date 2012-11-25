#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


TestEnemy::TestEnemy(const char* prm_name,
                     const char* prm_model,
                     GgafStatus* prm_pStat) : DefaultMeshActor(prm_name, prm_model, prm_pStat) {

    pMoji_ = NEW SpriteLabelTest("stamina");
    pMoji_->defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //XYZ軸ビルボード
    addSubGroup(pMoji_);
}

void TestEnemy::initialize() {
    setHitAble(true);
    _pColliChecker->makeCollision(1);
//    _pColliChecker->setColliAAB(0, -30000, -30000, -30000, 30000, 30000, 30000);
    _pColliChecker->setColliSphere(0, 30000);
}


void TestEnemy::dispStamina() {
    static char aBuf[20];
    sprintf(aBuf, "%d", _pStatus->get(STAT_Stamina));
    pMoji_->update(aBuf);
    pMoji_->locate(_X,_Y+PX_C(30),_Z);
}

TestEnemy::~TestEnemy() {
}

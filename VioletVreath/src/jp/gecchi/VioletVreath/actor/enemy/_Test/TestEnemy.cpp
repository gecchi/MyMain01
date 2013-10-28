#include "stdafx.h"
#include "TestEnemy.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/actor/label/SpriteLabelTest.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include <stdio.h>

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
    pMoji_->position(_x,_y+PX_C(30),_z);
}

TestEnemy::~TestEnemy() {
}

#include "TestEnemy.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/actor/label/SpriteLabelTest.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include <stdio.h>

using namespace GgafLib;
using namespace VioletVreath;

TestEnemy::TestEnemy(const char* prm_name, const char* prm_model, void* prm_pStatusReset) :
        VvEnemyActor<DefaultMeshActor>(prm_name, prm_model, prm_pStatusReset) {

    pMoji_ = NEW SpriteLabelTest("stamina");
    pMoji_->defineRotMvWorldMatrix_Billboard(); //XYZ軸ビルボード
    appendGroupChild(pMoji_);
}

void TestEnemy::initialize() {
    setHitAble(true);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->createCollisionArea(8);
//    pChecker->setColliAABox(0, -30000, -30000, -30000, 30000, 30000, 30000);
//    pChecker->setColliSphere(0, 30000);
/////////////TEST
    int d = PX_C(200);
    int n = 0;
    pChecker->setColliAAPyramid(0,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_NNN,
                                false,false,false);
    n++;
    pChecker->setColliAAPyramid(1,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_NNP,
                                false,false,false);
    n++;
    pChecker->setColliAAPyramid(2,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_NPN,
                                false,false,false);
    n++;
    pChecker->setColliAAPyramid(3,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_NPP,
                                false,false,false);
    n++;
    pChecker->setColliAAPyramid(4,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_PNN,
                                false,false,false);
    n++;
    pChecker->setColliAAPyramid(5,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_PNP,
                                false,false,false);
    n++;
    pChecker->setColliAAPyramid(6,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_PPN,
                                false,false,false);
    n++;
    pChecker->setColliAAPyramid(7,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_PPP,
                                false,false,false);



//#define POS_PYRAMID_NNN   (0x0) //0b 000
//#define POS_PYRAMID_NNP   (0x1) //0b 001
//#define POS_PYRAMID_NPN   (0x2) //0b 010
//#define POS_PYRAMID_NPP   (0x3) //0b 011
//#define POS_PYRAMID_PNN   (0x4) //0b 100
//#define POS_PYRAMID_PNP   (0x5) //0b 101
//#define POS_PYRAMID_PPN   (0x6) //0b 110
//#define POS_PYRAMID_PPP   (0x7) //0b 111


}


void TestEnemy::dispStamina() {
    static char aBuf[20];
    sprintf(aBuf, "%d", getStatus()->get(STAT_Stamina));
    pMoji_->update(aBuf);
    pMoji_->setPosition(_x,_y+PX_C(30),_z);
}

TestEnemy::~TestEnemy() {
}

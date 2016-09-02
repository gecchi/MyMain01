#include "TestEnemy.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
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
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(8);
//    pChecker->setColliAABox(0, -30000, -30000, -30000, 30000, 30000, 30000);
//    pChecker->setColliSphere(0, 30000);
/////////////TEST
    int d = PX_C(200);
    int n = 0;
    pChecker->setColliAAPyramid(0,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_nnn,
                                false,false,false);
    n++;
    pChecker->setColliAAPyramid(1,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_nnp,
                                false,false,false);
    n++;
    pChecker->setColliAAPyramid(2,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_npn,
                                false,false,false);
    n++;
    pChecker->setColliAAPyramid(3,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_npp,
                                false,false,false);
    n++;
    pChecker->setColliAAPyramid(4,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_pnn,
                                false,false,false);
    n++;
    pChecker->setColliAAPyramid(5,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_pnp,
                                false,false,false);
    n++;
    pChecker->setColliAAPyramid(6,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_ppn,
                                false,false,false);
    n++;
    pChecker->setColliAAPyramid(7,
                                PX_C(-50)+(n*d),PX_C(-50)+(n*d),PX_C(-50)+(n*d),
                                PX_C(70)+(n*d),PX_C(80)+(n*d),PX_C(90)+(n*d),
                                POS_PYRAMID_ppp,
                                false,false,false);



//#define POS_PYRAMID_nnn   (0x0) //0b 000
//#define POS_PYRAMID_nnp   (0x1) //0b 001
//#define POS_PYRAMID_npn   (0x2) //0b 010
//#define POS_PYRAMID_npp   (0x3) //0b 011
//#define POS_PYRAMID_pnn   (0x4) //0b 100
//#define POS_PYRAMID_pnp   (0x5) //0b 101
//#define POS_PYRAMID_ppn   (0x6) //0b 110
//#define POS_PYRAMID_ppp   (0x7) //0b 111


}


void TestEnemy::dispStamina() {
    static char aBuf[20];
    sprintf(aBuf, "%d", getStatus()->get(STAT_Stamina));
    pMoji_->update(aBuf);
    pMoji_->place(_x,_y+PX_C(30),_z);
}

TestEnemy::~TestEnemy() {
}

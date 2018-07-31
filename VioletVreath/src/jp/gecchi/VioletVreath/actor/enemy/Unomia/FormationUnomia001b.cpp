#include "FormationUnomia001b.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/EnemyUnomia.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationUnomia001b::FormationUnomia001b(const char* prm_name) : FormationUnomia001(prm_name) {
    _class_name = "FormationUnomia001b";
}

void FormationUnomia001b::onCallUpUnomia(EnemyUnomia* pEnemyUnomia, int col) {
//    pEnemyUnomia->pKurokoLeader_->adjustAxisRate(
//                                        MyShip::lim_x_infront_, //X•ûŒü”{—¦
//                                       -1.0 * MyShip::lim_y_top_,   //Y•ûŒü”{—¦
//                                        MyShip::lim_z_left_  //Z•ûŒü”{—¦
//                                    );
    pEnemyUnomia->pKurokoLeader_->adjustCoordOffset(PX_C(col*50), PX_C(col*50), PX_C(col*50));
    pEnemyUnomia->pKurokoLeader_->adjustAxisYFlip();
    pEnemyUnomia->pKurokoLeader_->setAbsoluteBeginCoord();
}

FormationUnomia001b::~FormationUnomia001b() {
}

#include "FormationUnomia001b.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/EnemyUnomia.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationUnomia001b::FormationUnomia001b(const char* prm_name) : FormationUnomia001(prm_name) {
    _class_name = "FormationUnomia001b";
}

void FormationUnomia001b::onCallUpUnomia(EnemyUnomia* pEnemyUnomia, int col) {
//    pEnemyUnomia->pRikishaLeader_->adjustAxisRate(
//                                        MyShip::lim_x_infront_, //X�����{��
//                                       -1.0 * MyShip::lim_y_top_,   //Y�����{��
//                                        MyShip::lim_z_left_  //Z�����{��
//                                    );
    pEnemyUnomia->pRikishaLeader_->adjustCoordOffset(PX_C(col*50), PX_C(col*50), PX_C(col*50));
    pEnemyUnomia->pRikishaLeader_->adjustAxisYFlip();
    pEnemyUnomia->pRikishaLeader_->setAbsoluteBeginCoord();
}

FormationUnomia001b::~FormationUnomia001b() {
}

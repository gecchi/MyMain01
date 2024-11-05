#include "FormationUnomia001a.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/EnemyUnomia.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationUnomia001a::FormationUnomia001a(const char* prm_name) : FormationUnomia001(prm_name) {
    _class_name = "FormationUnomia001a";
}
void FormationUnomia001a::onSummonUnomia(EnemyUnomia* pEnemyUnomia, int col) {
//    pEnemyUnomia->pVehicleLeader_->adjustAxisRate(
//                                        MyShip::lim_x_infront_, //X•ûŒü”{—¦
//                                        MyShip::lim_y_top_,   //Y•ûŒü”{—¦
//                                        MyShip::lim_z_left_  //Z•ûŒü”{—¦
//                                    );
    pEnemyUnomia->pVehicleLeader_->adjustCoordOffset(PX_C(0), PX_C(col*50), PX_C(col*50));
    pEnemyUnomia->pVehicleLeader_->setAbsoluteBeginCoord();
}

FormationUnomia001a::~FormationUnomia001a() {
}

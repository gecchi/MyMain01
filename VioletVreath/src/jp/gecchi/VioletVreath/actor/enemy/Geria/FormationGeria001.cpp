#include "FormationGeria001.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Geria/EnemyGeria.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

//FormationGeria001::FormationGeria001(const char* prm_name) :
//    FormationGeria(prm_name,
//                  -800000, -400000, -1,
//                   400000,  800000,  1,
//                   GgafDxUniverse::_x_gone_right - 300000, 0, GgafDxUniverse::_z_gone_far - 1000,
//                   2000,
//                   D0ANG, D180ANG,
//                   30000,
//                   D0ANG, D90ANG,
//                   500,
//                   6) {
//    _class_name = "FormationGeria001";
//}

FormationGeria001::FormationGeria001(const char* prm_name) :
        FormationGeria(prm_name, 500) {
    _class_name = "FormationGeria001";

    //position(GgafDxUniverse::_x_gone_right - 300000, 0, GgafDxUniverse::_z_gone_far - 1000);
    position(PX_C(4000), 0, PX_C(1000));
    setFaceAngTwd(PX_C(4000), 0, -PX_C(1000));
    pAxsMver_->setVxyzMvVelo(-2000, 0, 0);
}

void FormationGeria001::processBehavior() {
    if (getActiveFrame() % 6 == 0) {
        EnemyGeria* pGeria = summonGeria();
        if (pGeria) {
            pGeria->position(RND_AROUND(_x, PX_C(400)),
                             RND_AROUND(_y, PX_C(800)),
                             RND_AROUND(_z, PX_C(400)) );
            pGeria->getKuroko()->setRzRyMvAng(_rx, _ry); //Œü‚¢‚Ä‚é•ûŒü‚É”ò‚Î‚·
            pGeria->getKuroko()->setMvVelo(PX_C(20));
            pGeria->setMigrationLength(PX_C(5000));
        }
    }
    pAxsMver_->behave();
}

void FormationGeria001::processJudgement() {
    if (_x < GgafDxUniverse::_x_gone_left) {
        _TRACE_("FormationGeria001::processJudgement() I—¹");
        sayonara();
    }
}

FormationGeria001::~FormationGeria001() {
}

#include "FormationGeria002.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Geria/EnemyGeria.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationGeria002::FormationGeria002(const char* prm_name) :
        FormationGeria(prm_name, 500) {
    _class_name = "FormationGeria002";

    position(PX_C(8000), 0, PX_C(8000));
    setFaceAngTwd(PX_C(-8000), 0, PX_C(8000));
    pAxsMver_->setVxyzMvVelo(0, 0, -2000);
}

void FormationGeria002::processBehavior() {
    if (getActiveFrame() % 6 == 0) {
        EnemyGeria* pGeria = summonGeria();
        if (pGeria) {
            pGeria->positionAboutAs(this, PX_C(800));
            pGeria->getKuroko()->setRzRyMvAng(_rz, _ry); //Œü‚¢‚Ä‚é•ûŒü‚É”ò‚Î‚·
            pGeria->getKuroko()->setMvVelo(PX_C(20));
            pGeria->setMigrationLength(PX_C(15000));
        }
    }
    pAxsMver_->behave();
}

void FormationGeria002::processJudgement() {
    if (_x < GgafDxUniverse::_x_gone_left) {
        _DTRACE_("FormationGeria002::processJudgement() I—¹");
        sayonara();
    }
}

FormationGeria002::~FormationGeria002() {
}

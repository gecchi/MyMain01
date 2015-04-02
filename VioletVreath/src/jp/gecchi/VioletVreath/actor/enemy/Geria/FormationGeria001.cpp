#include "FormationGeria001.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Geria/EnemyGeria.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationGeria001::FormationGeria001(const char* prm_name) :
        FormationGeria(prm_name, 500) {
    _class_name = "FormationGeria001";

    position(PX_C(5000), 0, PX_C(5000));
    setFaceAngTwd(PX_C(5000), 0, -PX_C(5000));
    pAxsMver_->setVxyzMvVelo(-2000, 0, 0);
}

void FormationGeria001::processBehavior() {
    if (getActiveFrame() % 6 == 0) {
        EnemyGeria* pGeria = summonGeria();
        if (pGeria) {
            pGeria->positionAboutAs(this, PX_C(800));
            pGeria->getKuroko()->setRzRyMvAng(_rz, _ry); //å¸Ç¢ÇƒÇÈï˚å¸Ç…îÚÇŒÇ∑
            pGeria->getKuroko()->setMvVelo(PX_C(20));
            pGeria->setMigrationLength(PX_C(10000));
        }
    }
    pAxsMver_->behave();
}

void FormationGeria001::processJudgement() {
    Spacetime* pSpacetime =  P_GOD->getSpacetime();
    if (_x < pSpacetime->_x_bound_left) {
        _TRACE_("FormationGeria001::processJudgement() èIóπ");
        sayonara();
    }
}

FormationGeria001::~FormationGeria001() {
}

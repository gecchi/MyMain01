#include "FormationGeria002.h"

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

FormationGeria002::FormationGeria002(const char* prm_name) :
        FormationGeria(prm_name, 500) {
    _class_name = "FormationGeria002";

    locate(PX_C(8000), 0, PX_C(8000));
    setFaceAngTwd(PX_C(-8000), 0, PX_C(8000));
    pAxsMver_->setVxyzMvVelo(0, 0, -2000);
}

void FormationGeria002::processBehavior() {
    if (getActiveFrame() % 6 == 0) {
        EnemyGeria* pGeria = summonGeria();
        if (pGeria) {
            pGeria->locateAboutAs(this, PX_C(800));
            pGeria->getKuroko()->setRzRyMvAng(_rz, _ry); //向いてる方向に飛ばす
            pGeria->getKuroko()->setMvVelo(PX_C(20));
            pGeria->setMigrationLength(PX_C(15000));
        }
    }
    pAxsMver_->behave();
}

void FormationGeria002::processJudgement() {
    Spacetime* pSpacetime =  P_GOD->getSpacetime();
    if (_x < pSpacetime->_x_bound_left) {
        _TRACE_(FUNC_NAME<<" 終了");
        sayonara();
    }
}

FormationGeria002::~FormationGeria002() {
}

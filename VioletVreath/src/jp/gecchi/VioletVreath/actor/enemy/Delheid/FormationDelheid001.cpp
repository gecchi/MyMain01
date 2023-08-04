#include "FormationDelheid001.h"

#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/EnemyDelheid.h"

using namespace GgafLib;
using namespace VioletVreath;

FormationDelheid001::FormationDelheid001(const char* prm_name) :
        FormationDelheid(prm_name, StatusReset(FormationDelheid001)) {
    _class_name = "FormationDelheid001";
    pConn_pCurveManuf_ = connectToCurveManufactureManager("FormationDelheid001");
}

void FormationDelheid001::onCalledUpDelheid(EnemyDelheid* pEnemyDelheid) {
}

GgafDx::CurveManufacture* FormationDelheid001::getSplManuf() {
    return pConn_pCurveManuf_->peek(); //e
}
void FormationDelheid001::processBehavior() {
    FormationDelheid::processBehavior();
}

FormationDelheid001::~FormationDelheid001() {
    pConn_pCurveManuf_->close();
}

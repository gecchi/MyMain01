#include "FormationDelheid001.h"

#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/EnemyDelheid.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationDelheid001::FormationDelheid001(const char* prm_name) :
        FormationDelheid(prm_name) {
    _class_name = "FormationDelheid001";
    pConn_pCurveManuf_ = connectToCurveManufactureManager("FormationDelheid001");
}

void FormationDelheid001::onCallUpDelheid(EnemyDelheid* pEnemyDelheid) {
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

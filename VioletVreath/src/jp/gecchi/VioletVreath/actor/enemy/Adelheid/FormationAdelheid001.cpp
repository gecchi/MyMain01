#include "stdafx.h"
#include "FormationAdelheid001.h"

#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Adelheid/EnemyAdelheid.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAdelheid001::FormationAdelheid001(const char* prm_name) :
        FormationAdelheid(prm_name) {
    _class_name = "FormationAdelheid001";
    pSplManufConnection_ = connect_SplineManufactureManager("FormationAdelheid001");
}

void FormationAdelheid001::onCallUpAdelheid(EnemyAdelheid* pEnemyAdelheid) {
    pEnemyAdelheid->locateAs(&geoLocate_);
    pEnemyAdelheid->_pKurokoA->setRzRyMvAng(geoLocate_._RZ, geoLocate_._RY);
}

GgafLib::SplineManufacture* FormationAdelheid001::getSplManuf() {
    return pSplManufConnection_->peek(); //e
}
void FormationAdelheid001::processBehavior() {
    FormationAdelheid::processBehavior();
}

FormationAdelheid001::~FormationAdelheid001() {
    pSplManufConnection_->close();
}

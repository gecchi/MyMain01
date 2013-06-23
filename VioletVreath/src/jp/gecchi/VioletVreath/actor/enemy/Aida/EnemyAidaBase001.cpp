#include "stdafx.h"
#include "EnemyAidaBase001.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAidaBase001::EnemyAidaBase001(const char* prm_name) :
        EnemyAidaBase(prm_name) {
}

void EnemyAidaBase001::initialize() {
    EnemyAidaBase::initialize();
    _pKurokoA->setFaceAngVelo(D_ANG(3), D_ANG(1), D0ANG );
    _pKurokoA->setMvVelo(PX_C(1));
    _pKurokoA->setRzRyMvAng(D0ANG, D180ANG);
}

void EnemyAidaBase001::processBehavior() {
    EnemyAidaBase::processBehavior();
    _pKurokoA->behave();
}

EnemyAidaBase001::~EnemyAidaBase001() {
}



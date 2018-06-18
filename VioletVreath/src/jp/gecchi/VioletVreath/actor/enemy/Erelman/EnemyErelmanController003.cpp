#include "EnemyErelmanController003.h"

#include "FormationErelman003.h"
#include "EnemyErelmanCore003.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyErelmanController003::EnemyErelmanController003(const char* prm_name) :
                              EnemyErelmanController(
                                  prm_name,
                                  NEW EnemyErelmanCore003("EnemyErelmanCore003", this),
                                  NEW FormationErelman003("FormationErelman003", this)
                              ) {
    _class_name = "EnemyErelmanController003";
}


void EnemyErelmanController003::onCoreHit() {
    if (pFormationErelman_) {
        _TRACE_("EnemyErelmanController003::onCoreHit()->freeMenber() ���܂���");
        ((FormationErelman003*)pFormationErelman_)->freeMenber(60*3);
    }
}

EnemyErelmanController003::~EnemyErelmanController003() {
}

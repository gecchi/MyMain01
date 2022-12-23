#include "EnemyErelmanController003.h"

#include "FormationErelman003.h"
#include "EnemyErelmanCore003.h"



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
        _TRACE_("EnemyErelmanController003::onCoreHit()->freeMenber() ‚«‚Ü‚µ‚½");
        ((FormationErelman003*)pFormationErelman_)->freeMenber(SEC_F(3));
    }
}

EnemyErelmanController003::~EnemyErelmanController003() {
}

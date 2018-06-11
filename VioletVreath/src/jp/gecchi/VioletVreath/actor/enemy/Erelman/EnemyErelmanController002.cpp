#include "EnemyErelmanController002.h"

#include "FormationErelman002.h"
#include "EnemyErelmanCore.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyErelmanController002::EnemyErelmanController002(const char* prm_name) :
                              EnemyErelmanController(
                                  prm_name,
                                  NEW EnemyErelmanCore("EnemyErelmanCore", this),
                                  NEW FormationErelman002("FormationErelman", this)
                              ) {
    _class_name = "EnemyErelmanController002";
}


EnemyErelmanController002::~EnemyErelmanController002() {
}

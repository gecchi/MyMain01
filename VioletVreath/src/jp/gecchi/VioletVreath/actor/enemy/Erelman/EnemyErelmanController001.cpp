#include "EnemyErelmanController001.h"

#include "FormationErelman001.h"
#include "EnemyErelmanCore001.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyErelmanController001::EnemyErelmanController001(const char* prm_name) :
                              EnemyErelmanController(
                                  prm_name,
                                  NEW EnemyErelmanCore001("EnemyErelmanCore001", this),
                                  NEW FormationErelman001("FormationErelman001", this)
                              ) {
    _class_name = "EnemyErelmanController001";
}


EnemyErelmanController001::~EnemyErelmanController001() {
}

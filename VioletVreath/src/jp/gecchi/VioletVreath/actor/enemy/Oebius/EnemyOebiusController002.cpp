#include "EnemyOebiusController002.h"

#include "FormationOebius002.h"
#include "EnemyOebiusCore.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyOebiusController002::EnemyOebiusController002(const char* prm_name) :
                              EnemyOebiusController(
                                  prm_name,
                                  NEW EnemyOebiusCore("EnemyOebiusCore", this),
                                  NEW FormationOebius002("FormationOebius", this)
                              ) {
    _class_name = "EnemyOebiusController002";
}


EnemyOebiusController002::~EnemyOebiusController002() {
}

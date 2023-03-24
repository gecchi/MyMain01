#include "EnemyOebiusController001.h"

#include "FormationOebius001.h"
#include "EnemyOebiusCore.h"

using namespace GgafLib;
using namespace VioletVreath;

EnemyOebiusController001::EnemyOebiusController001(const char* prm_name) :
                              EnemyOebiusController(
                                  prm_name,
                                  NEW EnemyOebiusCore("EnemyOebiusCore", this),
                                  NEW FormationOebius001("FormationOebius", this)
                              ) {
    _class_name = "EnemyOebiusController001";
}

EnemyOebiusController001::~EnemyOebiusController001() {
}

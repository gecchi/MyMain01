#include "EnemyErelmanController002.h"

#include "FormationErelman002.h"
#include "EnemyErelmanCore002.h"



using namespace GgafLib;
using namespace VioletVreath;

EnemyErelmanController002::EnemyErelmanController002(const char* prm_name) :
                              EnemyErelmanController(
                                  prm_name,
                                  NEW EnemyErelmanCore002("EnemyErelmanCore002", this),
                                  NEW FormationErelman002("FormationErelman002", this)
                              ) {
    _class_name = "EnemyErelmanController002";
}


EnemyErelmanController002::~EnemyErelmanController002() {
}

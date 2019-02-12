#include "TestDepository.h"



using namespace GgafLib;
using namespace VioletVreath;

TestDepository::TestDepository(const char* prm_name, GgafCore::Status* prm_pStat) : GgafCore::ActorDepository(prm_name, prm_pStat) {
    _class_name = "TestDepository";
}

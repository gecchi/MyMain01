#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ActorDispatcher::ActorDispatcher(const char* prm_name) : GgafDummyActor(prm_name) {
    _class_name = "ActorDispatcher";
    setBumpable(false);
}

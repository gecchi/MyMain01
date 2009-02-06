#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafDummyActor::GgafDummyActor(const char* prm_name) : GgafMainActor(prm_name) {
    _class_name = "GgafDummyActor";
    setBumpable(false);
}

GgafDummyActor::~GgafDummyActor() {
}

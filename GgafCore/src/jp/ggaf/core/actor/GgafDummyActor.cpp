#include "stdafx.h"

using namespace Ggaf;

GgafDummyActor::GgafDummyActor(string prm_name) : GgafMainActor(prm_name) {
	_class_name = "GgafDummyActor";
    setBumpable(false);
}

GgafDummyActor::~GgafDummyActor() {
}

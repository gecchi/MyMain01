#include "stdafx.h"

GgafDummyActor::GgafDummyActor(string prm_name) : GgafMainActor(prm_name) {
	_class_name = "GgafDummyActor";
    setBumpable(false);
}

GgafDummyActor::~GgafDummyActor() {
}

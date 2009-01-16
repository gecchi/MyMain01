#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9TransformedActor::GgafDx9TransformedActor(string prm_name) : GgafDx9BaseActor(prm_name) {
	_class_name = "GgafDx9TransformedActor";
	_x  = _y  = _z  = 0.0f;
}

GgafDx9TransformedActor::~GgafDx9TransformedActor() {
}

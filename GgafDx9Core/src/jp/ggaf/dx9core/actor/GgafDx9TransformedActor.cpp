#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;

GgafDx9TransformedActor::GgafDx9TransformedActor(string prm_name) : GgafDx9BaseActor(prm_name) {
	_class_name = "GgafDx9TransformedActor";
	_x  = _y  = _z  = 0.0f;
}

GgafDx9TransformedActor::~GgafDx9TransformedActor() {
}

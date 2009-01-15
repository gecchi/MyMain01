#include "stdafx.h"

using namespace Ggaf;

GgafCriticalException::GgafCriticalException(string prm_message) : GgafException(prm_message) {
}

GgafCriticalException::~GgafCriticalException() {
}

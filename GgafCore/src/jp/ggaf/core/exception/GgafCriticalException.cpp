#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafCriticalException::GgafCriticalException(string prm_message) : GgafException(prm_message) {
}

GgafCriticalException::~GgafCriticalException() {
}

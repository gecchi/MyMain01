#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafCriticalException::GgafCriticalException(string prm_message) : GgafException(prm_message) {
    _TRACE_("例外発生！ GgafCriticalException::GgafCriticalException "<<prm_message);
}

GgafCriticalException::~GgafCriticalException() {
}

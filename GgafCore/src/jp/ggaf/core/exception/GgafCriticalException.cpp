#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafCriticalException::GgafCriticalException(string prm_message) : GgafException(prm_message) {
    _TRACE_("��O�����I GgafCriticalException::GgafCriticalException "<<prm_message);
}

GgafCriticalException::~GgafCriticalException() {
}

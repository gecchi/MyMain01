#include "jp/ggaf/core/exception/GgafCriticalException.h"

using namespace GgafCore;

GgafCriticalException::GgafCriticalException(std::string prm_message) : GgafException(prm_message) {
    _TRACE_("��O�����I GgafCriticalException::GgafCriticalException "<<prm_message);
}

GgafCriticalException::~GgafCriticalException() {
}

#include "jp/ggaf/core/exception/GgafCriticalException.h"

using namespace GgafCore;

GgafCriticalException::GgafCriticalException(std::string prm_message) : GgafException(prm_message) {
    _TRACE_("例外発生！ GgafCriticalException::GgafCriticalException "<<prm_message);
}

GgafCriticalException::~GgafCriticalException() {
}

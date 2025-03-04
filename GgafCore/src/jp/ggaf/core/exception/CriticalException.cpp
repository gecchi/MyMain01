#include "jp/ggaf/core/exception/CriticalException.h"

using namespace GgafCore;

CriticalException::CriticalException(std::string prm_message) : Exception(prm_message) {
    _TRACE_("例外発生！ CriticalException::CriticalException "<<prm_message);
}

CriticalException::~CriticalException() {
}

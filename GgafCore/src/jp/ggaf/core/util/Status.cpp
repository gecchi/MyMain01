#include "jp/ggaf/core/util/Status.h"
#include <string.h>

using namespace GgafCore;

Status::Status(Status* (*prm_pFunc_reset)(Status*)) : Object() {
   _pFunc_reset = prm_pFunc_reset;
   _has_been_reset = false;
   if (_pFunc_reset) {
       reset();
   }
}

Status::~Status() {
}

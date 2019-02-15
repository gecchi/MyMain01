#include "jp/ggaf/core/util/Status.h"
#include <string.h>

using namespace GgafCore;

Status::Status(Status* (*prm_pFunc_reset)(Status*)) : Object() {
   _pFunc_reset = prm_pFunc_reset;
   if (_pFunc_reset) {
       (*_pFunc_reset)(this); //リセットメソッドを実行して初期化
   }
}

Status::~Status() {
}

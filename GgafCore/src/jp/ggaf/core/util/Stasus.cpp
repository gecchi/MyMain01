#include "jp/ggaf/core/util/Status.h"
#include <string.h>

using namespace GgafCore;

Status::Status(int prm_max_status_kind, Status* (*prm_pFunc_reset)(Status*)) : Object() {
   _len = prm_max_status_kind;
   _paValue = new VALUE[_len];
   for (int i = 0; i < _len; i++) {
       memset(&(_paValue[i]), 0, sizeof(VALUE));
   }
   _pFunc_reset = prm_pFunc_reset;
   if (_pFunc_reset) {
       (*_pFunc_reset)(this); //リセットメソッドを実行して初期化
   }
}

Status::~Status() {
    delete[] _paValue;
}

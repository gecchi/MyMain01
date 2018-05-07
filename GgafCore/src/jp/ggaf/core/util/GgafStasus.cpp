#include "jp/ggaf/core/util/GgafStatus.h"
#include <string.h>

using namespace GgafCore;

GgafStatus::GgafStatus(int prm_max_status_kind, GgafStatus* (*prm_pFunc_reset)(GgafStatus*)) : GgafObject() {
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

GgafStatus::~GgafStatus() {
    delete[] _paValue;
}

#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafStatus::GgafStatus(int prm_max_status_kind, GgafStatus* (*prm_pFunc_reset)(GgafStatus*)) : GgafObject() {
   _len = prm_max_status_kind;
   _paValue = new VALUE[_len];
   for (int i = 0; i < _len; i++) {
       _paValue[i]._double_val = 0;
       _paValue[i]._int_val = 0;
       _paValue[i]._char_val = 0;
       _paValue[i]._ptr = nullptr;
   }
   _pFunc_reset = prm_pFunc_reset;
   if (_pFunc_reset) {
       (*_pFunc_reset)(this); //リセットメソッドを実行して初期化
   }
}

GgafStatus::~GgafStatus() {
    delete[] _paValue;
    //GGAF_DELETEARR(_paValue);
}

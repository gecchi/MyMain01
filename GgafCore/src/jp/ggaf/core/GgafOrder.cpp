#include "jp/ggaf/core/GgafOrder.h"

using namespace GgafCore;

GgafOrder::GgafOrder(uint64_t prm_order_id) : GgafObject() {
    _order_id = prm_order_id;
    _pOrderer = nullptr;
    _pReceiver  = nullptr;
    _pOrder_next = nullptr;
    _pOrder_prev = nullptr;
    _is_first_order_flg = false;
    _is_last_order_flg = false;
    _pObject_creation = nullptr;
    _pFunc = nullptr;
    _pArg1 = nullptr;
    _pArg2 = nullptr;
    _pArg3 = nullptr;
    _time_of_order = 0;
    _time_of_create_begin = 0;
    _time_of_create_finish = 0;
    _progress = 0;
}

GgafOrder::~GgafOrder() {
    //è§ïi _pObject_creation ÇÕçHèÍÇ™ê∂ê¨Ç∑ÇÈÇ©Ç‡ÇµÇÍÇ»Ç¢ÅB
    GGAF_DELETE_NULLABLE(_pObject_creation);
}


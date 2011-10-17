#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafOrder::GgafOrder(unsigned long prm_id) : GgafObject("Order") {
    _id = prm_id;
    _pOrderer = NULL;
    _pOrder_Next = NULL;
    _pOrder_Prev = NULL;
    _is_first_order_flg = false;
    _is_last_order_flg = false;
    _pObject_Creation = NULL;
    _pFunc = NULL;
    _pArg1 = NULL;
    _pArg2 = NULL;
    _pArg3 = NULL;
    _progress = 0;
}

GgafOrder::~GgafOrder() {
    //è§ïi _pObject_Creation ÇÕçHèÍÇ™ê∂ê¨Ç∑ÇÈÇ©Ç‡ÇµÇÍÇ»Ç¢ÅB
    DELETE_POSSIBLE_NULL(_pObject_Creation);
}


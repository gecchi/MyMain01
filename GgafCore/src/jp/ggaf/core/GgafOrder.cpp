#include "stdafx.h"

using namespace GgafCore;

GgafOrder::GgafOrder(UINT32 prm_id) : GgafObject() {
    _id = prm_id;
    _pOrderer = NULL;
    _pOrder_next = NULL;
    _pOrder_prev = NULL;
    _is_first_order_flg = false;
    _is_last_order_flg = false;
    _pObject_creation = NULL;
    _pFunc = NULL;
    _pArg1 = NULL;
    _pArg2 = NULL;
    _pArg3 = NULL;
    _progress = 0;
}

GgafOrder::~GgafOrder() {
    //è§ïi _pObject_creation ÇÕçHèÍÇ™ê∂ê¨Ç∑ÇÈÇ©Ç‡ÇµÇÍÇ»Ç¢ÅB
    DELETE_POSSIBLE_NULL(_pObject_creation);
}


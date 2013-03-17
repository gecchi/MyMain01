#include "stdafx.h"

using namespace GgafCore;

GgafOrder::GgafOrder(UINT32 prm_id) : GgafObject() {
    _id = prm_id;
    _pOrderer = nullptr;
    _pOrder_next = nullptr;
    _pOrder_prev = nullptr;
    _is_first_order_flg = false;
    _is_last_order_flg = false;
    _pObject_creation = nullptr;
    _pFunc = nullptr;
    _pArg1 = nullptr;
    _pArg2 = nullptr;
    _pArg3 = nullptr;
    _progress = 0;
}

GgafOrder::~GgafOrder() {
    //商品 _pObject_creation は工場が生成するかもしれない。
    GGAF_DELETE_NULLABLE(_pObject_creation);
}


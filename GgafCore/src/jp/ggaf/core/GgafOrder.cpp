#include "stdafx.h"

using namespace Ggaf;

GgafOrder::GgafOrder(string prm_id) {
	_id = prm_id;
	_pOrder_Next = NULL;
	_pOrder_Prev = NULL;
	_isFirstOrder = false;
	_isLastOrder  = false;
	_pObject_Creation = NULL;
	_pFunc = NULL;
	_pArg1 = NULL;
	_pArg2 = NULL;
	_progress = 0;
}

GgafOrder::~GgafOrder() {
	DELETE_POSSIBLE_NULL(_pObject_Creation);
}


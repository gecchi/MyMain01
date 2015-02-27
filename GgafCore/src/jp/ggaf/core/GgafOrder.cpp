#include "jp/ggaf/core/GgafOrder.h"
#include <sstream>
#include "jp/ggaf/core/scene/GgafScene.h"
#include "jp/ggaf/core/actor/GgafActor.h"

using namespace GgafCore;

GgafOrder::GgafOrder(uint64_t prm_order_no) : GgafObject() {
    _order_no = prm_order_no;
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
std::string GgafOrder::getDebuginfo() {
    std::string name_creation = "nullptr";
    if (_pObject_creation) {
        if (_pObject_creation->instanceOf(Obj_GgafScene)) {
            name_creation = ((GgafScene*)_pObject_creation)->getName();
        } else if (_pObject_creation->instanceOf(Obj_GgafActor)) {
            name_creation = ((GgafActor*)_pObject_creation)->getName();
        } else {
            name_creation = "UNKNOWN";
        }
    }
    std::stringstream ss;
    ss << "注文時刻:"<<_time_of_order<<", "<<
          "注文番号:"<<_order_no<<"/"<<_pReceiver<<", "<<
          "進捗:"<<_progress<<", "<<
          "商品:"<<name_creation<<"("<<_pObject_creation<<")"<<", "<<
          "製造開始:"<<_time_of_create_begin<<", "<<
          "製造完了:"<<_time_of_create_finish<<", "<<
          "発注者:"<<_pOrderer<<"";
    return ss.str();

}
GgafOrder::~GgafOrder() {
    //商品 _pObject_creation は工場が生成するかもしれない。
    GGAF_DELETE_NULLABLE(_pObject_creation);
}


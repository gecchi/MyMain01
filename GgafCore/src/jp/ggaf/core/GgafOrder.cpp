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
    ss << "��������:"<<_time_of_order<<", "<<
          "�����ԍ�:"<<_order_no<<"/"<<_pReceiver<<", "<<
          "�i��:"<<_progress<<", "<<
          "���i:"<<name_creation<<"("<<_pObject_creation<<")"<<", "<<
          "�����J�n:"<<_time_of_create_begin<<", "<<
          "��������:"<<_time_of_create_finish<<", "<<
          "������:"<<_pOrderer<<"";
    return ss.str();

}
GgafOrder::~GgafOrder() {
    //���i _pObject_creation �͍H�ꂪ�������邩������Ȃ��B
    GGAF_DELETE_NULLABLE(_pObject_creation);
}


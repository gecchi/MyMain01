#include "jp/ggaf/core/Cradle.h"

#include <sstream>
#include "jp/ggaf/core/scene/Scene.h"
#include "jp/ggaf/core/actor/Actor.h"

using namespace GgafCore;

Cradle::Cradle(uint64_t prm_cradle_no) : Object() {
    _cradle_no = prm_cradle_no;
    _pWisher = nullptr;
    _pReceiver  = nullptr;
    _pCradle_next = nullptr;
    _pCradle_prev = nullptr;
    _is_first_cradle_flg = false;
    _is_last_cradle_flg = false;
    _pObject_creation = nullptr;
    _pFunc = nullptr;
    _pArg1 = nullptr;
    _pArg2 = nullptr;
    _pArg3 = nullptr;
    _time_of_wants = 0;
    _time_of_create_begin = 0;
    _time_of_create_finish = 0;
    _progress_no = 0;
}
std::string Cradle::getDebuginfo() {
    std::string name_creation = "nullptr";
    if (_pObject_creation) {
        if (_pObject_creation->instanceOf(Obj_ggaf_Scene)) {
            name_creation = ((Scene*)_pObject_creation)->getName();
        } else if (_pObject_creation->instanceOf(Obj_ggaf_Actor)) {
            name_creation = ((Actor*)_pObject_creation)->getName();
        } else {
            name_creation = "UNKNOWN";
        }
    }
    std::stringstream ss;
    ss << "ゆりかご時刻:"<<_time_of_wants<<", "
          "ゆりかご番号:"<<_cradle_no<<"-"<<_pReceiver<<", "
          "進捗状況:"<<_progress_no<<", "<<
          "命:"<<name_creation<<"("<<_pObject_creation<<")"<<", "
          "祝福開始:"<<_time_of_create_begin<<", "
          "祝福完了:"<<_time_of_create_finish<<", "
          "望んだ人:"<<_pWisher<<"";
    return ss.str();

}
Cradle::~Cradle() {
    //臍の緒もあれば絶つ
    GGAF_DELETE_NULLABLE(_pObject_creation);
}


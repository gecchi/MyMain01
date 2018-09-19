#include "jp/ggaf/core/GgafCradle.h"

#include <sstream>
#include "jp/ggaf/core/scene/GgafScene.h"
#include "jp/ggaf/core/actor/GgafActor.h"

using namespace GgafCore;

GgafCradle::GgafCradle(uint64_t prm_cradle_no) : GgafObject() {
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
    _progress = 0;
}
std::string GgafCradle::getDebuginfo() {
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
    ss << "ゆりかご時刻:"<<_time_of_wants<<", "
          "ゆりかご番号:"<<_cradle_no<<"-"<<_pReceiver<<", "
          "進捗:"<<_progress<<", "<<
          "命:"<<name_creation<<"("<<_pObject_creation<<")"<<", "
          "祝福開始:"<<_time_of_create_begin<<", "
          "祝福完了:"<<_time_of_create_finish<<", "
          "望んだ人:"<<_pWisher<<"";
    return ss.str();

}
GgafCradle::~GgafCradle() {
    //臍の緒もあれば絶つ
    GGAF_DELETE_NULLABLE(_pObject_creation);
}


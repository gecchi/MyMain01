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
    _phase_no = 0;
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
    ss << "��肩������:"<<_time_of_wants<<", "
          "��肩���ԍ�:"<<_cradle_no<<"-"<<_pReceiver<<", "
          "�t�F�[�Y:"<<_phase_no<<", "<<
          "��:"<<name_creation<<"("<<_pObject_creation<<")"<<", "
          "�j���J�n:"<<_time_of_create_begin<<", "
          "�j������:"<<_time_of_create_finish<<", "
          "�]�񂾐l:"<<_pWisher<<"";
    return ss.str();

}
Cradle::~Cradle() {
    //�`�̏�������ΐ��
    GGAF_DELETE_NULLABLE(_pObject_creation);
}


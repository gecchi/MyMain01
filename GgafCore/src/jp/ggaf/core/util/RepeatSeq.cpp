#include "jp/ggaf/core/util/RepeatSeq.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "windows.h"

using namespace GgafCore;

std::map<std::string, RepeatSeq::Seq> RepeatSeq::mapSeq;

#ifdef _MSC_VER
volatile bool RepeatSeq::_is_lock = false;
#else
volatile std::atomic<bool> RepeatSeq::_is_lock(false);
#endif

#define WAIT_LOCK do { \
wait: \
if (GgafCore::RepeatSeq::_is_lock) { Sleep(1); goto wait; } \
} while(0)


void RepeatSeq::create(std::string ID, int min, int max) {
#ifdef MY_DEBUG
    if (isExist(ID)) {
        throwCriticalException("ID="<<ID<<"�͊��ɑ��݂��܂�(1)");
    }
#endif
    _TRACE_("�V�[�N�G���X���쐬���܂��B RepeatSeq::create("<<ID<<","<<min<<","<<max<<")");
    mapSeq.insert(std::make_pair(ID, Seq()));
    mapSeq[ID].init(min, max);
}

void RepeatSeq::create(const char* ID, int min, int max) {
#ifdef MY_DEBUG
    if (isExist(ID)) {
        throwCriticalException("ID="<<ID<<"�͊��ɑ��݂��܂�(2)");
    }
#endif
    _TRACE_("�V�[�N�G���X���쐬���܂��B RepeatSeq::create("<<ID<<","<<min<<","<<max<<")");
    mapSeq.insert(std::make_pair(std::string(ID), Seq()));
    mapSeq[ID].init(min, max);
}
void RepeatSeq::set(std::string& ID, int val) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        mapSeq[ID].set(val);
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"�͑��݂��܂���");
    }
#endif
}

void RepeatSeq::set(const char* ID, int val) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        mapSeq[ID].set(val);
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"�͑��݂��܂���B");
    }
#endif
}

void RepeatSeq::setMax(std::string& ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        mapSeq[ID].setMax();
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"�͑��݂��܂���");
    }
#endif
}

void RepeatSeq::setMax(const char* ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        mapSeq[ID].setMax();
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"�͑��݂��܂���B");
    }
#endif
}

void RepeatSeq::setMin(std::string& ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
    mapSeq[ID].setMin();
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"�͑��݂��܂���");
    }
#endif
}

void RepeatSeq::setMin(const char* ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
    mapSeq[ID].setMin();
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"�͑��݂��܂���B");
    }
#endif
}

bool RepeatSeq::isExist(std::string& ID) {
    WAIT_LOCK;
    RepeatSeq::_is_lock = true;
    bool ret = mapSeq.find(ID) != mapSeq.end();
    RepeatSeq::_is_lock = false;
    return ret;
}

bool RepeatSeq::isExist(const char* ID) {
    WAIT_LOCK;
    RepeatSeq::_is_lock = true;
    bool ret = mapSeq.find(ID) != mapSeq.end();
    RepeatSeq::_is_lock = false;
    return ret;
}


int RepeatSeq::nextVal(std::string& ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        return mapSeq[ID].nextVal();
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"�͑��݂��܂���");
    }
#endif
}
int RepeatSeq::nextVal(const char* ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        return mapSeq[ID].nextVal();
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"�͑��݂��܂���B");
    }
#endif
}

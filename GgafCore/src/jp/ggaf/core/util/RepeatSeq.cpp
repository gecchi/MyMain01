#include "jp/ggaf/core/util/RepeatSeq.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "windows.h"

using namespace GgafCore;

std::map<std::string, RepeatSeq::Seq> RepeatSeq::_mapSeq;

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
        throwCriticalException("ID="<<ID<<"は既に存在します(1)");
    }
#endif
    _TRACE_("シークエンスを作成します。 RepeatSeq::create("<<ID<<","<<min<<","<<max<<")");
    _mapSeq.insert(std::make_pair(ID, Seq()));
    _mapSeq[ID].init(min, max);
}

void RepeatSeq::create(const char* ID, int min, int max) {
#ifdef MY_DEBUG
    if (isExist(ID)) {
        throwCriticalException("ID="<<ID<<"は既に存在します(2)");
    }
#endif
    _TRACE_("シークエンスを作成します。 RepeatSeq::create("<<ID<<","<<min<<","<<max<<")");
    _mapSeq.insert(std::make_pair(std::string(ID), Seq()));
    _mapSeq[ID].init(min, max);
}
void RepeatSeq::set(std::string& ID, int val) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        _mapSeq[ID].set(val);
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"は存在しません");
    }
#endif
}

void RepeatSeq::set(const char* ID, int val) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        _mapSeq[ID].set(val);
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"は存在しません。");
    }
#endif
}

void RepeatSeq::setMax(std::string& ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        _mapSeq[ID].setMax();
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"は存在しません");
    }
#endif
}

void RepeatSeq::setMax(const char* ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        _mapSeq[ID].setMax();
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"は存在しません。");
    }
#endif
}

void RepeatSeq::setMin(std::string& ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
    _mapSeq[ID].setMin();
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"は存在しません");
    }
#endif
}

void RepeatSeq::setMin(const char* ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
    _mapSeq[ID].setMin();
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"は存在しません。");
    }
#endif
}

bool RepeatSeq::isExist(std::string& ID) {
    WAIT_LOCK;
    RepeatSeq::_is_lock = true;
    bool ret = _mapSeq.find(ID) != _mapSeq.end();
    RepeatSeq::_is_lock = false;
    return ret;
}

bool RepeatSeq::isExist(const char* ID) {
    WAIT_LOCK;
    RepeatSeq::_is_lock = true;
    bool ret = _mapSeq.find(ID) != _mapSeq.end();
    RepeatSeq::_is_lock = false;
    return ret;
}


int RepeatSeq::nextVal(std::string& ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        return _mapSeq[ID].nextVal();
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"は存在しません");
    }
#endif
}
int RepeatSeq::nextVal(const char* ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        return _mapSeq[ID].nextVal();
#ifdef MY_DEBUG
    } else {
        throwCriticalException("ID="<<ID<<"は存在しません。");
    }
#endif
}

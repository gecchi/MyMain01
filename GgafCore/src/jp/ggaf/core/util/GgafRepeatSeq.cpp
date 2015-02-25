#include "jp/ggaf/core/util/GgafRepeatSeq.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "windows.h"

using namespace GgafCore;

std::map<std::string, GgafRepeatSeq::Seq> GgafRepeatSeq::mapSeq;

#ifdef _MSC_VER
volatile bool GgafRepeatSeq::_is_lock = false;
#else
volatile std::atomic<bool> GgafRepeatSeq::_is_lock(false);
#endif

#define WAIT_LOCK do { \
wait: \
if (GgafRepeatSeq::_is_lock) { Sleep(1); goto wait; } \
} while(0)


void GgafRepeatSeq::create(std::string& ID, int min, int max) {
#ifdef MY_DEBUG
    if (isExist(ID)) {
        throwGgafCriticalException("GgafRepeatSeq::create() ID="<<ID<<"は既に存在します(1)");
    }
#endif
    _TRACE_("シークエンスを作成します。 GgafRepeatSeq::create("<<ID<<","<<min<<","<<max<<")");
    mapSeq[ID].init(min, max);
}

void GgafRepeatSeq::create(const char* ID, int min, int max) {
#ifdef MY_DEBUG
    if (isExist(ID)) {
        throwGgafCriticalException("GgafRepeatSeq::create() ID="<<ID<<"は既に存在します(2)");
    }
#endif
    _TRACE_("シークエンスを作成します。 GgafRepeatSeq::create("<<ID<<","<<min<<","<<max<<")");
    mapSeq[ID].init(min, max);
}
void GgafRepeatSeq::set(std::string& ID, int val) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        mapSeq[ID].set(val);
#ifdef MY_DEBUG
    } else {
        throwGgafCriticalException("GgafRepeatSeq::set() ID="<<ID<<"は存在しません");
    }
#endif
}

void GgafRepeatSeq::set(const char* ID, int val) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        mapSeq[ID].set(val);
#ifdef MY_DEBUG
    } else {
        throwGgafCriticalException("GgafRepeatSeq::set() ID="<<ID<<"は存在しません。");
    }
#endif
}

void GgafRepeatSeq::setMax(std::string& ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        mapSeq[ID].setMax();
#ifdef MY_DEBUG
    } else {
        throwGgafCriticalException("GgafRepeatSeq::setMax() ID="<<ID<<"は存在しません");
    }
#endif
}

void GgafRepeatSeq::setMax(const char* ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        mapSeq[ID].setMax();
#ifdef MY_DEBUG
    } else {
        throwGgafCriticalException("GgafRepeatSeq::setMax() ID="<<ID<<"は存在しません。");
    }
#endif
}

void GgafRepeatSeq::setMin(std::string& ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
    mapSeq[ID].setMin();
#ifdef MY_DEBUG
    } else {
        throwGgafCriticalException("GgafRepeatSeq::setMin() ID="<<ID<<"は存在しません");
    }
#endif
}

void GgafRepeatSeq::setMin(const char* ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
    mapSeq[ID].setMin();
#ifdef MY_DEBUG
    } else {
        throwGgafCriticalException("GgafRepeatSeq::setMin() ID="<<ID<<"は存在しません。");
    }
#endif
}

bool GgafRepeatSeq::isExist(std::string& ID) {
    WAIT_LOCK;
    GgafRepeatSeq::_is_lock = true;
    bool ret = mapSeq.find(ID) != mapSeq.end();
    GgafRepeatSeq::_is_lock = false;
    return ret;
}

bool GgafRepeatSeq::isExist(const char* ID) {
    WAIT_LOCK;
    GgafRepeatSeq::_is_lock = true;
    bool ret = mapSeq.find(ID) != mapSeq.end();
    GgafRepeatSeq::_is_lock = false;
    return ret;
}


int GgafRepeatSeq::nextVal(std::string& ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        return mapSeq[ID].nextVal();
#ifdef MY_DEBUG
    } else {
        throwGgafCriticalException("GgafRepeatSeq::nextVal() ID="<<ID<<"は存在しません");
    }
#endif
}
int GgafRepeatSeq::nextVal(const char* ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        return mapSeq[ID].nextVal();
#ifdef MY_DEBUG
    } else {
        throwGgafCriticalException("GgafRepeatSeq::nextVal() ID="<<ID<<"は存在しません。");
    }
#endif
}

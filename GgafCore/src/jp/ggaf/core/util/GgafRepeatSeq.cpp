#include "jp/ggaf/core/util/GgafRepeatSeq.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"

using namespace GgafCore;

std::map<std::string, int> GgafRepeatSeq::mapNowval;
std::map<std::string, int> GgafRepeatSeq::mapMaxval;
std::map<std::string, int> GgafRepeatSeq::mapMinval;


void GgafRepeatSeq::create(std::string& ID, int min, int max) {
#ifdef MY_DEBUG
    if (isExist(ID)) {
        throwGgafCriticalException("GgafRepeatSeq::create() ID="<<ID<<"は既に存在します(1)");
    }
#endif
    _DTRACE_("シークエンスを作成します。 GgafRepeatSeq::create("<<ID<<","<<min<<","<<max<<")");
    mapNowval[ID] = min;
    mapMaxval[ID] = max;
    mapMinval[ID] = min;
}

void GgafRepeatSeq::create(const char* ID, int min, int max) {
#ifdef MY_DEBUG
    if (isExist(ID)) {
        throwGgafCriticalException("GgafRepeatSeq::create() ID="<<ID<<"は既に存在します(2)");
    }
#endif
    _DTRACE_("シークエンスを作成します。 GgafRepeatSeq::create("<<ID<<","<<min<<","<<max<<")");
    mapNowval[ID] = min;
    mapMaxval[ID] = max;
    mapMinval[ID] = min;
}
void GgafRepeatSeq::set(std::string& ID, int val) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        mapNowval[ID] = val;
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
        mapNowval[ID] = val;
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
        mapNowval[ID] = mapMaxval[ID];
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
        mapNowval[ID] = mapMaxval[ID];
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
    mapNowval[ID] = mapMinval[ID];
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
    mapNowval[ID] = mapMinval[ID];
#ifdef MY_DEBUG
    } else {
        throwGgafCriticalException("GgafRepeatSeq::setMin() ID="<<ID<<"は存在しません。");
    }
#endif
}

bool GgafRepeatSeq::isExist(std::string& ID) {
    std::map<std::string, int>::iterator i = mapNowval.find(ID);
    if(i != mapNowval.end()){
        return true;
    } else {
        return false;
    }
}

bool GgafRepeatSeq::isExist(const char* ID) {
    std::map<std::string, int>::iterator i = mapNowval.find(ID);
    if(i != mapNowval.end()){
        return true;
    } else {
        return false;
    }
}


int GgafRepeatSeq::nextVal(std::string& ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        int val = mapNowval[ID];
        int next_val = val + 1;
        if (next_val > mapMaxval[ID]) {
            mapNowval[ID] = mapMinval[ID];
        } else {
            mapNowval[ID] = next_val;
        }
        return val;
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
        int val = mapNowval[ID];
        int next_val = val + 1;
        if (next_val > mapMaxval[ID]) {
            mapNowval[ID] = mapMinval[ID];
        } else {
            mapNowval[ID] = next_val;
        }
        return val;
#ifdef MY_DEBUG
    } else {
        throwGgafCriticalException("GgafRepeatSeq::nextVal() ID="<<ID<<"は存在しません。");
    }
#endif
}

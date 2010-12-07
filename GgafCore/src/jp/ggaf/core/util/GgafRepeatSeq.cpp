#include "stdafx.h"
using namespace std;

using namespace GgafCore;
std::_MAP_<std::string, int> GgafRepeatSeq::mapNowval;
std::_MAP_<std::string, int> GgafRepeatSeq::mapMaxval;
std::_MAP_<std::string, int> GgafRepeatSeq::mapMinval;

void GgafRepeatSeq::create(string ID, int min, int max) {
    if (isExist(ID)) {
        throwGgafCriticalException("GgafRepeatSeq::create() ID="<<ID<<"‚ÍŠù‚É‘¶Ý‚µ‚Ü‚·");
    } else {
        mapNowval[ID] = min;
        mapMaxval[ID] = max;
        mapMinval[ID] = min;
    }
}


bool GgafRepeatSeq::isExist(string ID) {
    _MAP_<string, int>::iterator i = mapNowval.find(ID);
    if(i != mapNowval.end()){
        return true;
    } else {
        return false;
    }
}

int GgafRepeatSeq::nextVal(string ID) {
#ifdef MY_DEBUG
    if (isExist(ID) ) {
#endif
        mapNowval[ID] = mapNowval[ID] + 1;
        if (mapNowval[ID]  > mapMaxval[ID]) {
            mapNowval[ID] = mapMinval[ID];
        }
		return mapNowval[ID];
#ifdef MY_DEBUG
    } else {
        throwGgafCriticalException("GgafRepeatSeq::nextVal() ID="<<ID<<"‚Í‘¶Ý‚µ‚Ü‚¹‚ñ");
    }
#endif
}

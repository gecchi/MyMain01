#include "jp/ggaf/resource/util/Util.h"

#include "jp/ggaf/core/exception/CriticalException.h"

#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

using namespace GgafResource;


std::string Util::padZeroStrEX(int prm_data_num, int prm_total_keta) {
    std::ostringstream oss;
    oss.setf(std::ios::right);
    oss.fill('0');
    oss.width(prm_total_keta);
    oss << prm_data_num;
    return oss.str();
}


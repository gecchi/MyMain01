#ifndef MGRUTIL_H_
#define MGRUTIL_H_
#include "Mogera.h"
#include "jp/ggaf/lib/util/StgUtil.h"

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL Mogera::MgrUtil

#define LT_x (Mogera::MgrUtil::left_top_x_)
#define LT_y (Mogera::MgrUtil::left_top_y_)
#define C_x (Mogera::MgrUtil::center_x_)
#define C_y (Mogera::MgrUtil::center_y_)

namespace Mogera {


/**
 * 本アプリのユーティリティ .
 * @version 1.00
 * @since 2010/01/06
 * @author Masatoshi Tsuge
 */
class MgrUtil : public GgafLib::StgUtil {
public:
    static coord left_top_x_;
    static coord left_top_y_;
    static coord center_x_;
    static coord center_y_;
};

}
#endif /*MGRUTIL_H_*/

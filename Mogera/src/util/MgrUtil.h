#ifndef MGRUTIL_H_
#define MGRUTIL_H_
#include "jp/ggaf/lib/util/StgUtil.h"

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL Mogera::MgrUtil

#define LT_X (Mogera::MgrUtil::left_top_X_)
#define LT_Y (Mogera::MgrUtil::left_top_Y_)

namespace Mogera {


/**
 * 本アプリのユーティリティ .
 * @version 1.00
 * @since 2010/01/06
 * @author Masatoshi Tsuge
 */
class MgrUtil : public GgafLib::StgUtil {
public:
    static coord left_top_X_;
    static coord left_top_Y_;

};

}
#endif /*MGRUTIL_H_*/

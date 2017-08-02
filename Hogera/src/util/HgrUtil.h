#ifndef HGRUTIL_H_
#define HGRUTIL_H_
#include "Hogera.h"
#include "jp/ggaf/lib/util/StgUtil.h"

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL Hogera::HgrUtil

#define LT_x (Hogera::HgrUtil::left_top_x_)
#define LT_y (Hogera::HgrUtil::left_top_y_)
#define C_x (Hogera::HgrUtil::center_x_)
#define C_y (Hogera::HgrUtil::center_y_)

namespace Hogera {


/**
 * 本アプリのユーティリティ .
 * @version 1.00
 * @since 2010/01/06
 * @author Masatoshi Tsuge
 */
class HgrUtil : public GgafLib::StgUtil {
public:
    static coord left_top_x_;
    static coord left_top_y_;
    static coord center_x_;
    static coord center_y_;
};

}
#endif /*HGRUTIL_H_*/

#ifndef VVUTIL_H_
#define VVUTIL_H_
#include "jp/gecchi/VioletVrain/VioletVrain.h"
#include "jp/ggaf/lib/util/StgUtil.h"

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL VioletVrain::VvUtil

#define LT_x (VioletVrain::VvUtil::left_top_x_)
#define LT_y (VioletVrain::VvUtil::left_top_y_)
#define C_x (VioletVrain::VvUtil::center_x_)
#define C_y (VioletVrain::VvUtil::center_y_)

namespace VioletVrain {


/**
 * 本アプリのユーティリティ .
 * @version 1.00
 * @since 2010/01/06
 * @author Masatoshi Tsuge
 */
class VvUtil : public GgafLib::StgUtil {
public:
    static coord left_top_x_;
    static coord left_top_y_;
    static coord center_x_;
    static coord center_y_;
};

}
#endif /*VVUTIL_H_*/

#ifndef XPMHEADER_H_
#define XPMHEADER_H_
#include "jp/ggaf/core/GgafObject.h"

#include <map>
#include <vector>

namespace VioletVreath {

/**
 * 簡易XPM(Pixmap)支援クラス .
 * @version 1.00
 * @since 2013/07/16
 * @author Masatoshi Tsuge
 */
class XpmHeader : public GgafCore::GgafObject {
public:
    /** [r]列数 */
    int columns_;
    /** [r]行数 */
    int rows_;
    /** [r]色数 */
    int colors_;
    /** [r]透明ピクセルの文字 */
    char c_px_non_;
    /** [r]ピクセル色の文字の配列 */
    std::vector<char> c_px;
    /** [r]ピクセル色の文字に対応する、実際のRGB値 */
    std::map<char, GgafCore::GgafRgb*> c_rgb_;
    const char** xpm_hd_;
    const char** pixels_;
public:
    /**
     * コンストラクタ .
     * @param prm_xpm Pixmapへのポインタ。実値を保持しないのでスコープに注意。(static などを想定)
     */
    XpmHeader(const char** prm_xpm);
    virtual ~XpmHeader();
};
}
#endif /*XPMHEADER_H_*/

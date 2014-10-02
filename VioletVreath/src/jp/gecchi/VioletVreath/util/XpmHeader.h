#ifndef XPMHEADER_H_
#define XPMHEADER_H_
#include "VioletVreath.h"
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
    /** [r]透明色では無いピクセルの数 */
    int num_color_pixels_;
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

    /**
     * Pixmapの列数を取得 .
     * @return 列数
     */
    inline int getColumns() {
        return columns_;
    }

    /**
     * Pixmapの行数を取得 .
     * @return 行数
     */
    inline int getRows() {
        return rows_;
    }

    /**
     * Pixmapのされている色の数を取得 .
     * @return 色の数
     */
    inline int getColorNum() {
        return colors_;
    }

    /**
     * Pixmapのピクセルの数(透明色を除く)を取得 .
     * @return
     */
    inline int getPixelNum() {
        return num_color_pixels_;
    }

    /**
     * Pixmapの指定のピクセルの色を取得 .
     * @param prm_row 何行目かを指定
     * @param prm_col 何列目かを指定
     * @return 色
     */
    inline GgafCore::GgafRgb* getColor(int prm_row, int prm_col) {
        return c_rgb_[pixels_[prm_row][prm_col]];
    }

    /**
     * Pixmapの指定のピクセルの色が透明色か否か取得 .
     * @param prm_row 何行目かを指定
     * @param prm_col 何列目かを指定
     * @return true:透明色 / false:透明色以外
     */
    inline bool isNonColor(int prm_row, int prm_col) {
        if (pixels_[prm_row][prm_col] == c_px_non_) {
            return true;
        } else {
            return false;
        }
    }

    virtual ~XpmHeader();
};
}
#endif /*XPMHEADER_H_*/

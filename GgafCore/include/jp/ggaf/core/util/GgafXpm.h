#ifndef GGAFCORE_GGAFXPM_H_
#define GGAFCORE_GGAFXPM_H_
#include "jp/ggaf/core/GgafObject.h"

#include <map>
#include <vector>

namespace GgafCore {

/**
 * 簡易XPM(Pixmap)支援クラス .
 * @version 1.00
 * @since 2013/07/16
 * @author Masatoshi Tsuge
 */
class GgafXpm : public GgafCore::GgafObject {
public:
    /** [r]幅ピクセル数 */
    int _width;
    /** [r]高さピクセル数 */
    int _height;
    /** [r]色数 */
    int _colors;
    /** [r]透明色では無いピクセルの数 */
    int _num_color_pixels;
    /** [r]透明ピクセルの文字 */
    char _c_px_non;
    /** [r]ピクセル色の文字の配列 */
    std::vector<char> _vecColorChar;
    /** [r]ピクセル色の文字に対応する、実際のRGB値 */
    std::map<char, GgafCore::GgafRgb*> _mapCharRgb;
    const char** _xpm_hd;
    const char** _pixels;
public:
    /**
     * コンストラクタ .
     * @param prm_xpm Pixmapへのポインタ。実値を保持しないのでスコープに注意。(static などを想定)
     */
    GgafXpm(const char** prm_xpm);

    /**
     * Pixmapの列数を取得 .
     * @return 列数
     */
    inline int getWidth() {
        return _width;
    }

    /**
     * Pixmapの行数を取得 .
     * @return 行数
     */
    inline int getHeight() {
        return _height;
    }

    /**
     * Pixmapのされている色の数を取得 .
     * @return 色の数
     */
    inline int getColorNum() {
        return _colors;
    }

    /**
     * Pixmapのピクセルの数(透明色を除く)を取得 .
     * @return
     */
    inline int getPixelNum() {
        return _num_color_pixels;
    }

    /**
     * Pixmapの指定のピクセルの色を取得 .
     * @param prm_row 何行目かを指定
     * @param prm_col 何列目かを指定
     * @return 色
     */
    inline GgafCore::GgafRgb* getColor(int prm_row, int prm_col) {
        return _mapCharRgb[_pixels[prm_row][prm_col]];
    }

    /**
     * Pixmapの指定のピクセルの色が透明色か否か取得 .
     * @param prm_row 何行目かを指定
     * @param prm_col 何列目かを指定
     * @return true:透明色 / false:透明色以外
     */
    inline bool isNonColor(int prm_row, int prm_col) {
        if (_pixels[prm_row][prm_col] == _c_px_non) {
            return true;
        } else {
            return false;
        }
    }

    virtual ~GgafXpm();
};
}
#endif /*GGAFCORE_GGAFXPM_H_*/

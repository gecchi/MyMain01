#ifndef GGAF_CORE_XPM_H_
#define GGAF_CORE_XPM_H_
#include "jp/ggaf/core/Object.h"

#include <map>
#include <vector>

namespace GgafCore {

/**
 * 簡易XPM(Pixmap)支援クラス .
 * @version 1.00
 * @since 2013/07/16
 * @author Masatoshi Tsuge
 */
class Xpm : public Object {
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

    int _char_on_pixel;

    /** [r]ピクセル色の文字の配列 */
    std::vector<char> _vecColorChar;
    /** [r]ピクセル色の文字に対応する、実際のRGB値 */
    std::map<char, Rgb*> _mapCharRgb;
    char** _pixels;
public:
    /**
     * コンストラクタ .
     * @param prm_xpm Pixmapへのポインタ。実値を保持しないのでスコープに注意。(static などを想定)
     */
    Xpm(const char** prm_xpm);

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
     * @param prm_row_idx 何行目かを指定(0～)
     * @param prm_col_idx 何列目かを指定(0～)
     * @return 色
     */
    inline Rgb* getColor(int prm_row_idx, int prm_col_idx) {
        Rgb* r = nullptr;
        if (prm_row_idx < _height && prm_col_idx < _width) {
            //範囲内
            r = _mapCharRgb[_pixels[prm_row_idx][prm_col_idx]];
        } else {
            //範囲外
            r = _mapCharRgb['\0'];
        }
        return r;
    }

    /**
     * Pixmapの指定のピクセルの色が透明色か否か取得 .
     * @param prm_row_idx 何行目かを指定(0～)
     * @param prm_col_idx 何列目かを指定(0～)
     * @return true:透明色 / false:透明色以外
     */
    inline bool isNonColor(int prm_row_idx, int prm_col_idx) {
        if (prm_row_idx < _height && prm_col_idx < _width) {
            //範囲内
            if (_pixels[prm_row_idx][prm_col_idx] == _c_px_non) {
                return true;
            } else {
                return false;
            }
        } else {
            //範囲外
            return true;
        }
    }

    virtual ~Xpm();
};
}
#endif /*GGAF_CORE_XPM_H_*/

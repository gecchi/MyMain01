#ifndef GGAFLIB_FONTBOARDACTOR_H_
#define GGAFLIB_FONTBOARDACTOR_H_
#include "GgafLibCommonHeader.h"

#include "FixedFontBoardActor.h"

namespace GgafLib {

/**
 * 可変幅文字表示 .
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class FontBoardActor : public FixedFontBoardActor {
public:
    /** [r/w]各文字間隔(px) */
    pixcoord _px_chr_width[256];

    FontBoardActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat = nullptr);
    virtual void prepare1(const char* prm_str) override;
    virtual void prepare2() override;

    /**
     * 全ての文字の幅の比率を設定
     * @param prm_width_ratio 幅の率(初期値の幅に乗じる値、初期値は1.0)
     */
    inline void setAllChrWidthRatio(double prm_width_ratio) {
        pixcoord* p = _px_chr_width;
        for (int i = 0; i < 256; i++) {
            *p = _chr_width_px * prm_width_ratio;
            p++;
        }
    }

    /**
     * 文字の幅の比率を個々に設定 .
     * @param c 文字
     * @param prm_width_ratio 幅の率(初期値の幅に乗じる値、初期値は1.0)
     */
    inline void setChrWidthRatio(const char c, double prm_width_ratio) {
        _px_chr_width[c] = _chr_width_px * prm_width_ratio;
    }


    virtual ~FontBoardActor();
};

}
#endif /*GGAFLIB_FONTBOARDACTOR_H_*/

#ifndef GGAFCORE_GGAFRGB_H_
#define GGAFCORE_GGAFRGB_H_
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/util/GgafUtil.h"

namespace GgafCore {

/**
 * RGB値クラス .
 * @version 1.00
 * @since 2011/05/13
 * @author Masatoshi Tsuge
 */
class GgafRgb : public GgafObject {
private :
    std::string _allowedChars;

    bool isValid();
public:
    /** [r/w] Red値(0～255) */
    size_t _R;
    /** [r/w] Green値(0～255) */
    size_t _G;
    /** [r/w] Brue値(0～255) */
    size_t _B;
    /** [r/w] Red値(0.0～1.0) */
    float _r;
    /** [r/w] Green値(0.0～1.0) */
    float _g;
    /** [r/w] Brue値(0.0～1.0 */
    float _b;
    /** １６進文字列表現のRGB */
    std::string _hex;
    /** 色文字列が妥当かどうか */
    bool _is_valid;

    static bool _is_init;
    static std::map<std::string, std::string> _cname;

public:
    /**
     * コンストラクタ .
     * 保持されるRGBは(0, 0, 0)
     */
    GgafRgb();

    /**
     * コンストラクタ .
     * 引数の文字列をRGB値とします。
     * @param prm_str_color "#FFFFFF"形式の文字列（"#"は省略可）、またはX11色名
     */
    GgafRgb(std::string prm_str_color);

    void init();

    /**
     * 引数の文字列をRGB値とし設定します .
     * @param prm_hex "#FFFFFF"形式の文字列 （"#"は省略可）、またはX11色名
     */
    void set(std::string prm_hex);

    /**
     * 内部保持RGB値を文字列で取得
     * @return "#FFFFFF"形式の文字列
     */
    std::string toStr();
};



}
#endif /*GGAFCORE_GGAFRGB_H_*/

#ifndef GGAFRGB_H_
#define GGAFRGB_H_
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

    bool isValid() {
        if (_hex.length() != 6) {
            return false;
        } else {
            if (_hex.find_first_not_of(_allowedChars) != _hex.npos) {
                return false;
            } else {
                return true;
            }
        }
    }

public:
    /** [r/w] Red値(0～255) */
    size_t _R;
    /** [r/w] Green値(0～255) */
    size_t _G;
    /** [r/w] Brue値(0～255) */
    size_t _B;
    /** １６進文字列表現のRGB */
    std::string _hex;
    /** _hex が妥当かどうか */
    bool _is_valid;

    /**
     * コンストラクタ .
     * 保持されるRGBは(0, 0, 0)
     */
    GgafRgb() : GgafObject(),
            _allowedChars("0123456789abcdefABCDEF#") , _R(0), _G(0), _B(0), _hex("000000"), _is_valid(true) {
    }

    /**
     * コンストラクタ .
     * 引数の文字列をRGB値とします。
     * @param prm_hex "#FFFFFF"形式の文字列 （"#"は省略可）
     */
    GgafRgb(std::string prm_hex) : GgafObject(),
            _allowedChars("0123456789abcdefABCDEF#") , _R(0), _G(0), _B(0), _hex("000000"), _is_valid(true) {
        set(prm_hex);
    }

    /**
     * 引数の文字列をRGB値とし設定します .
     * @param prm_hex "#FFFFFF"形式の文字列 （"#"は省略可）
     */
    void set(std::string prm_hex) {
        _hex = prm_hex;
        if (_hex[0] == '#') {
            _hex.erase(_hex.begin());
        }
        _is_valid = isValid();
        if (_is_valid) {
            _R = UTIL::hex2dec(_hex.substr(0, 2));
            _G = UTIL::hex2dec(_hex.substr(2, 2));
            _B = UTIL::hex2dec(_hex.substr(4, 2));
        } else {
            throwGgafCriticalException("GgafRgb::set HEX値からRGBに変換出来ません。prm_hex="<<prm_hex);
        }
    }

};

}
#endif /*GGAFRGB_H_*/

#ifndef GGAFRGB_H_
#define GGAFRGB_H_
namespace GgafCore {

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
    size_t _R;
    size_t _G;
    size_t _B;
    bool _is_valid;
    std::string _hex;

    GgafRgb() : GgafObject(),
            _allowedChars("0123456789abcdefABCDEF#") , _R(0), _G(0), _B(0), _is_valid(true), _hex("000000") {
    }

    GgafRgb(std::string prm_hex) : GgafObject(),
            _allowedChars("0123456789abcdefABCDEF#") , _R(0), _G(0), _B(0), _is_valid(true), _hex("000000") {
        set(prm_hex);
    }

    void set(std::string prm_hex) {
        _hex = prm_hex;
        if (_hex[0] == '#') {
            _hex.erase(_hex.begin());
        }
        _is_valid = isValid();
        if (_is_valid) {
            _R = GgafUtil::hex2dec(_hex.substr(0, 2));
            _G = GgafUtil::hex2dec(_hex.substr(2, 2));
            _B = GgafUtil::hex2dec(_hex.substr(4, 2));
        } else {
            throwGgafCriticalException("GgafRgb::set HEXílÇ©ÇÁRGBÇ…ïœä∑èoóàÇ‹ÇπÇÒÅBprm_hex="<<prm_hex);
        }
    }

};

}
#endif /*GGAFRGB_H_*/

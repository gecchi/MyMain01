#ifndef GGAFCORE_GGAFRGB_H_
#define GGAFCORE_GGAFRGB_H_
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/util/GgafUtil.h"

namespace GgafCore {

/**
 * RGB�l�N���X .
 * @version 1.00
 * @since 2011/05/13
 * @author Masatoshi Tsuge
 */
class GgafRgb : public GgafObject {
private :
    std::string _allowedChars;

    bool isValid();
public:
    /** [r/w] Red�l(0�`255) */
    size_t _R;
    /** [r/w] Green�l(0�`255) */
    size_t _G;
    /** [r/w] Brue�l(0�`255) */
    size_t _B;
    /** [r/w] Red�l(0.0�`1.0) */
    float _r;
    /** [r/w] Green�l(0.0�`1.0) */
    float _g;
    /** [r/w] Brue�l(0.0�`1.0 */
    float _b;
    /** �P�U�i������\����RGB */
    std::string _hex;
    /** �F�����񂪑Ó����ǂ��� */
    bool _is_valid;

    static bool _is_init;
    static std::map<std::string, std::string> _cname;

public:
    /**
     * �R���X�g���N�^ .
     * �ێ������RGB��(0, 0, 0)
     */
    GgafRgb();

    /**
     * �R���X�g���N�^ .
     * �����̕������RGB�l�Ƃ��܂��B
     * @param prm_str_color "#FFFFFF"�`���̕�����i"#"�͏ȗ��j�A�܂���X11�F��
     */
    GgafRgb(std::string prm_str_color);

    void init();

    /**
     * �����̕������RGB�l�Ƃ��ݒ肵�܂� .
     * @param prm_hex "#FFFFFF"�`���̕����� �i"#"�͏ȗ��j�A�܂���X11�F��
     */
    void set(std::string prm_hex);

    /**
     * �����ێ�RGB�l�𕶎���Ŏ擾
     * @return "#FFFFFF"�`���̕�����
     */
    std::string toStr();
};



}
#endif /*GGAFCORE_GGAFRGB_H_*/

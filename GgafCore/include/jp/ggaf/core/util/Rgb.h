#ifndef GGAF_CORE_RGB_H_
#define GGAF_CORE_RGB_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/util/Util.h"

namespace GgafCore {

/**
 * RGB�l�N���X .
 * @version 1.00
 * @since 2011/05/13
 * @author Masatoshi Tsuge
 */
class Rgb : public Object {
private :
    std::string _allowedChars;

    bool isValid();
public:
    /** [r/w] Red�l(0�`255) */
    size_t _red;
    /** [r/w] Green�l(0�`255) */
    size_t _green;
    /** [r/w] Brue�l(0�`255) */
    size_t _blue;
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

    static std::map<std::string, std::string> _cname;

public:
    /**
     * �R���X�g���N�^ .
     * �ێ������RGB��(0, 0, 0)
     */
    Rgb();

    /**
     * �R���X�g���N�^ .
     * �����̕������RGB�l�Ƃ��܂��B
     * @param prm_str_color "#FFFFFF"�`���̕�����i"#"�͏ȗ��j�A�܂���X11�F��
     */
    Rgb(std::string prm_str_color);
    void init();
    static bool initStatic();
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
#endif /*GGAF_CORE_RGB_H_*/

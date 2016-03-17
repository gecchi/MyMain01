#ifndef GGAFLIB_FONTBOARDACTOR_H_
#define GGAFLIB_FONTBOARDACTOR_H_
#include "GgafLibCommonHeader.h"

#include "FixedFontBoardActor.h"

namespace GgafLib {

/**
 * �ϕ������\�� .
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class FontBoardActor : public FixedFontBoardActor {
public:
    /** [r/w]�e�����Ԋu(px) */
    pixcoord _px_chr_width[256];

    FontBoardActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat = nullptr);
    virtual void prepare1(const char* prm_str) override;
    virtual void prepare2() override;

    /**
     * �S�Ă̕����̕��̔䗦��ݒ�
     * @param prm_width_ratio ���̗�(�����l�̕��ɏ悶��l�A�����l��1.0)
     */
    inline void setAllChrWidthRatio(double prm_width_ratio) {
        pixcoord* p = _px_chr_width;
        for (int i = 0; i < 256; i++) {
            *p = _chr_width_px * prm_width_ratio;
            p++;
        }
    }

    /**
     * �����̕��̔䗦���X�ɐݒ� .
     * @param c ����
     * @param prm_width_ratio ���̗�(�����l�̕��ɏ悶��l�A�����l��1.0)
     */
    inline void setChrWidthRatio(const char c, double prm_width_ratio) {
        _px_chr_width[c] = _chr_width_px * prm_width_ratio;
    }


    virtual ~FontBoardActor();
};

}
#endif /*GGAFLIB_FONTBOARDACTOR_H_*/

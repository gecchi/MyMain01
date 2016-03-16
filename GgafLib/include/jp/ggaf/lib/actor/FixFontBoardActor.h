#ifndef GGAFLIB_FIXFONTBOARDACTOR_H_
#define GGAFLIB_FIXFONTBOARDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "FontBoardActor.h"

namespace GgafLib {

/**
 * ç¿ïWïœä∑çœÇ›î¬É|Éäï∂éöï\é¶ .
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class FixFontBoardActor : public FontBoardActor {
public:
    FixFontBoardActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat = nullptr);
    virtual void prepare1(const char* prm_str) override;
    virtual void prepare2() override;
    virtual ~FixFontBoardActor();
};

}
#endif /*GGAFLIB_FIXFONTBOARDACTOR_H_*/

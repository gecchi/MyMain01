#ifndef GGAF_DX_IALIGNABLEACTOR_H_
#define GGAF_DX_IALIGNABLEACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

namespace GgafDx {

/**
 * アライン可能アクターインターフェイス。
 * @version 1.00
 * @since 2022/10/03
 * @author Masatoshi Tsuge
 */
class IAlignAbleActor {

public:

    Align _align;
    Valign _valign;

public:
    IAlignAbleActor() {
        _align = ALIGN_CENTER;
        _valign = VALIGN_MIDDLE;
    }

    virtual void setAlign(Align prm_align, Valign prm_valign) {
        _align = prm_align;
        _valign = prm_valign;
    }
    virtual void setAlign(Align prm_align) {
        _align = prm_align;
    }
    virtual void setValign(Valign prm_valign) {
        _valign = prm_valign;
    }

    virtual ~IAlignAbleActor() {
    }

};

}
#endif /*GGAF_DX_IALIGNABLEACTOR_H_*/

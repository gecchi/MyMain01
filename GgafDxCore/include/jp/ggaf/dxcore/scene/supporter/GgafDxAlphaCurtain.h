#ifndef GGAFDXCORE_GGAFDXALPHACURTAIN_H_
#define GGAFDXCORE_GGAFDXALPHACURTAIN_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/dxcore/scene/supporter/GgafDxSceneCurtain.h"

namespace GgafDxCore {

/**
 * αカーテン .
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class GgafDxAlphaCurtain : public GgafDxSceneCurtain {
public:
    /**
     * コンストラクタ .
     * @param prm_pScene αカーテンを取り付けるシーン
     * @param prm_min_alpha カーテンが閉じたときのα
     * @param prm_max_alpha カーテンが開いたときのα
     */
    GgafDxAlphaCurtain(GgafDxScene* prm_pScene);

    void behave() override;

    virtual ~GgafDxAlphaCurtain();
};

}
#endif /*GGAFDXCORE_GGAFDXALPHACURTAIN_H_*/


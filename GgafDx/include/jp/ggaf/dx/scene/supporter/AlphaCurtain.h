#ifndef GGAF_DX_ALPHACURTAIN_H_
#define GGAF_DX_ALPHACURTAIN_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include "jp/ggaf/dx/scene/supporter/SceneCurtain.h"

namespace GgafDx {

/**
 * αカーテン .
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class AlphaCurtain : public SceneCurtain {
public:
    /**
     * コンストラクタ .
     * @param prm_pScene αカーテンを取り付けるシーン
     * @param prm_min_alpha カーテンが閉じたときのα
     * @param prm_max_alpha カーテンが開いたときのα
     */
    AlphaCurtain(Scene* prm_pScene);

    void behave() override;

    virtual ~AlphaCurtain();
};

}
#endif /*GGAF_DX_ALPHACURTAIN_H_*/


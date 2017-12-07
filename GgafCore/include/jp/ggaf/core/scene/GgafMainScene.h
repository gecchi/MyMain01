#ifndef GGAFCORE_GGAFMAINSCENE_H_
#define GGAFCORE_GGAFMAINSCENE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/scene/GgafScene.h"

namespace GgafCore {

/**
 * 下位シーンクラスへのインターフェイス .
 * GgafCoreライブラリの利用者は本クラスを継承し（てシーン）クラスを作る。<BR>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */

class GgafMainScene : public GgafScene {
    friend class GgafGod;
    friend class GgafScene;

public:
    GgafMainScene(const char* prm_name, GgafSceneMediator* prm_pSceneMediator = nullptr);

    void updateActiveInTheTree() override;

    virtual ~GgafMainScene();

};

}
#endif /*GGAFCORE_GGAFMAINSCENE_H_*/

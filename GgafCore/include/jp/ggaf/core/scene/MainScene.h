#ifndef GGAF_CORE_MAINSCENE_H_
#define GGAF_CORE_MAINSCENE_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/scene/Scene.h"

namespace GgafCore {

/**
 * 下位シーンクラスへのインターフェイス .
 * Coreライブラリの利用者は本クラスを継承し（てシーン）クラスを作る。<BR>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */

class MainScene : public Scene {
    friend class Caretaker;
    friend class Scene;

public:
    MainScene(const char* prm_name, SceneMediator* prm_pSceneMediator = nullptr);

    void updateActiveInTheTree() override;

    virtual ~MainScene();

};

}
#endif /*GGAF_CORE_MAINSCENE_H_*/

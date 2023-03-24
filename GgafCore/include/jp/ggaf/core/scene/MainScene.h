#ifndef GGAF_CORE_MAINSCENE_H_
#define GGAF_CORE_MAINSCENE_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/scene/Scene.h"

namespace GgafCore {

/**
 * ���ʃV�[���N���X�ւ̃C���^�[�t�F�C�X .
 * Core���C�u�����̗��p�҂͖{�N���X���p�����i�ăV�[���j�N���X�����B<BR>
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

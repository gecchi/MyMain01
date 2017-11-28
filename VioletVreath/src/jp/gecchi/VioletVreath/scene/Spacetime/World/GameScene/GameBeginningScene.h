#ifndef GAMEBEGINNINGSCENE_H_
#define GAMEBEGINNINGSCENE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"


namespace VioletVreath {

/**
 * �Q�[���J�n�V�[���N���X .
 * �Q�[�����s�Ȃ��Ă����ʂƌ����Ă��A�Q�[���J�n���̏�ʂ�����܂����B
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class GameBeginningScene : public GgafLib::DefaultScene {

public:
    LabelGecchi16Font* pLabel01_;
    LabelGecchi16Font* pLabel02_;

    int selected_stage_;

public:
    GameBeginningScene(const char* prm_name);
    void onReset() override;
//    void ready() override;

    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    virtual ~GameBeginningScene();
};

}
#endif /*GAMEDEMOSCENE_H_*/

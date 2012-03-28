#ifndef GAMEBEGINNINGSCENE_H_
#define GAMEBEGINNINGSCENE_H_

namespace VioletVreath {

/**
 * �Q�[���J�n�V�[���N���X .
 * �Q�[�����s�Ȃ��Ă����ʂƌ����Ă��A�Q�[���J�n���̏�ʂ�����܂����B
 */
class GameBeginningScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1   ,
        PROG_SELECT_MODE,
        PROG_DECIDE     ,
        PROG_FINISH     ,
    };

    LabelGecchi16Font* pLabel01_;
    LabelGecchi16Font* pLabel02_;

    int selected_stage_;

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

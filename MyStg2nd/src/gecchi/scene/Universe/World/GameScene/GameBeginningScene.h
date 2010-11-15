#ifndef GAMEBEGINNINGSCENE_H_
#define GAMEBEGINNINGSCENE_H_


#define GAMEBEGINNING_SCENE_PROG_INIT   1
#define GAMEBEGINNING_SCENE_PROG_BEGIN  2
#define GAMEBEGINNING_SCENE_PROG_OPE    3
#define GAMEBEGINNING_SCENE_PROG_DECIDE 4
#define GAMEBEGINNING_SCENE_PROG_END    5

namespace MyStg2nd {

/**
 * �Q�[���J�n�V�[���N���X .
 * �Q�[�����s�Ȃ��Ă����ʂƌ����Ă��A�Q�[���J�n���̏�ʂ�����܂����B
 */
class GameBeginningScene : public GgafDx9LibStg::DefaultScene {

public:
    LabelGecchi16Font* _pStringBoard01;
    LabelGecchi16Font* _pStringBoard02;

    frame _frame_Begin;
    frame _frame_Ope;
    frame _frame_Decide;
    frame _frame_End;

    int _selected_stage;

    GameBeginningScene(const char* prm_name);
    void reset();
    void ready();

    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processFinal() override;
    virtual ~GameBeginningScene();
};

}
#endif /*GAMEDEMOSCENE_H_*/

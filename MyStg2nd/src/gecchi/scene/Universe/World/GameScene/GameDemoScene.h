#ifndef GAMEDEMOSCENE_H_
#define GAMEDEMOSCENE_H_
namespace MyStg2nd {

/**
 * �Q�[���f���V�[���N���X .
 * �Q�[�����s�Ȃ��Ă����ʂƌ����Ă��A�Q�[���f�����s�Ȃ��Ă���ꍇ������܂����B
 * @version 1.00
 * @since 2007/11/16
 * @author Masatoshi Tsuge
 */
class GameDemoScene : public GgafDx9LibStg::DefaultScene {

public:

    LabelGecchi16Font* _pStringBoard01;
    LabelGecchi16Font* _pStringBoard02;
    int _demo_stage;
    StageController* _pStageController;
    GameDemoScene(const char* prm_name);
    void onReset() override;
    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    void processFinal() override;
    virtual ~GameDemoScene();
};

}
#endif /*GAMEDEMOSCENE_H_*/

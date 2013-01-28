#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_
namespace VioletVreath {

#define ORDER_ID_NAMEENTRYSCENE 99
/**
 * ���@���S�Ł`�̃V�[��
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class GameOverScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1,
        PROG_DISP    ,
        PROG_NAMEENTRY,
        PROG_FINISH  ,
    };
    NameEntryScene* pNameEntryScene_;

    LabelGecchi16Font* pLabel01_;
    bool need_name_entry_;

public:
    GameOverScene(const char* prm_name);
    void onReset() override;
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~GameOverScene();
};

}
#endif /*GAMEOVERSCENE_H_*/

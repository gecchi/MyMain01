#ifndef STAGE01CONTROLLER_H_
#define STAGE01CONTROLLER_H_
namespace MyStg2nd {

#define STAGE01CONTROLLER_SCENE_PROG_INIT    0
#define STAGE01CONTROLLER_SCENE_PROG_STG01_01_BEGIN    1
#define STAGE01CONTROLLER_SCENE_PROG_STG01_01_PLAYING  2
#define STAGE01CONTROLLER_SCENE_PROG_STG01_02_BEGIN    3
#define STAGE01CONTROLLER_SCENE_PROG_STG01_02_PLAYING  4
#define STAGE01CONTROLLER_SCENE_PROG_STG01_03_BEGIN    5
#define STAGE01CONTROLLER_SCENE_PROG_STG01_03_PLAYING  6
#define STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_BEGIN    7
#define STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_PLAYING  8
#define STAGE01CONTROLLER_SCENE_PROG_FAINAL  9

/**
 * ステージ１コントローラー .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage01Controller : public GgafDx9LibStg::DefaultScene {

    GgafDx9Core::GgafDx9Bgm* _bgm_st1;

public:

    frame _frame_prog_fainal;

    Stage01Controller(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;

    virtual ~Stage01Controller();
};

}
#endif /*STAGE01CONTROLLER_H_*/

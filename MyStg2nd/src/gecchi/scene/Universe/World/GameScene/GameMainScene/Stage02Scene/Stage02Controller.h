#ifndef STAGE02CONTROLLER_H_
#define STAGE02CONTROLLER_H_
namespace MyStg2nd {

#define STAGE02CONTROLLER_SCENE_PROG_INIT    0
#define STAGE02CONTROLLER_SCENE_PROG_STG02_01_BEGIN    1
#define STAGE02CONTROLLER_SCENE_PROG_STG02_01_PLAYING  2
#define STAGE02CONTROLLER_SCENE_PROG_STG02_02_BEGIN    3
#define STAGE02CONTROLLER_SCENE_PROG_STG02_02_PLAYING  4
#define STAGE02CONTROLLER_SCENE_PROG_STG02_03_BEGIN    5
#define STAGE02CONTROLLER_SCENE_PROG_STG02_03_PLAYING  6
#define STAGE02CONTROLLER_SCENE_PROG_STG02_CLIMAX_BEGIN    7
#define STAGE02CONTROLLER_SCENE_PROG_STG02_CLIMAX_PLAYING  8
#define STAGE02CONTROLLER_SCENE_PROG_FAINAL  9
/**
 * ステージ１コントローラー .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage02Controller : public GgafDx9LibStg::DefaultScene {

    GgafDx9Core::GgafDx9Bgm* _bgm_st1;

public:

    frame _frame_prog_fainal;

    Stage02Controller(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override;

    virtual ~Stage02Controller();
};

}
#endif /*STAGE02CONTROLLER_H_*/

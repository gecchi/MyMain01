#ifndef STAGE02CONTROLLER_H_
#define STAGE02CONTROLLER_H_
namespace MyStg2nd {

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

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;

    virtual ~Stage02Controller();
};

}
#endif /*STAGE02CONTROLLER_H_*/

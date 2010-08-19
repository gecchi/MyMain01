#ifndef STAGE01CONTROLLER_H_
#define STAGE01CONTROLLER_H_
namespace MyStg2nd {

/**
 * ステージ１コントローラー .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage01Controller : public GgafDx9LibStg::DefaultScene {

    GgafDx9Core::GgafDx9Bgm* _bgm_st1;

public:

    Stage01Controller(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual void catchEvent(int prm_no) override;

    virtual ~Stage01Controller();
};

}
#endif /*STAGE01CONTROLLER_H_*/

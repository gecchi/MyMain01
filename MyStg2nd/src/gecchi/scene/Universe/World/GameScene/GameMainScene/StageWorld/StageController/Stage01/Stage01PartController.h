#ifndef STAGE01PARTCONTROLLER_H_
#define STAGE01PARTCONTROLLER_H_
namespace MyStg2nd {

/**
 * ステージ１コントローラー .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage01PartController : public StagePartController {

    GgafDxCore::GgafDxBgm* _bgm_st1;

public:


    Stage01PartController(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;

    virtual ~Stage01PartController();
};

}
#endif /*STAGE01PARTCONTROLLER_H_*/

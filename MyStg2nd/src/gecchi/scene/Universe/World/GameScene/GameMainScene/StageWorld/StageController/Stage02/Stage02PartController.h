#ifndef STAGE02PARTCONTROLLER_H_
#define STAGE02PARTCONTROLLER_H_
namespace MyStg2nd {

/**
 * ステージ１コントローラー .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage02PartController : public GgafLib::DefaultScene {

    GgafDxCore::GgafDxBgm* _bgm_st1;

public:
    enum {
        PROG_INIT = 1            ,
        PROG_STG02_01_BEGIN      ,
        PROG_STG02_01_PLAYING    ,
        PROG_STG02_02_BEGIN      ,
        PROG_STG02_02_PLAYING    ,
        PROG_STG02_03_BEGIN      ,
        PROG_STG02_03_PLAYING    ,
        PROG_STG02_CLIMAX_BEGIN  ,
        PROG_STG02_CLIMAX_PLAYING,
        PROG_FAINAL              ,
    };
    frame _frame_prog_fainal;

    Stage02PartController(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~Stage02PartController();
};

}
#endif /*STAGE02PARTCONTROLLER_H_*/

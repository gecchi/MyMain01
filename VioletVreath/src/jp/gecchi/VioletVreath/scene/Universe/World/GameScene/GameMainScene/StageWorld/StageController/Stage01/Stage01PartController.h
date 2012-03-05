#ifndef STAGE01PARTCONTROLLER_H_
#define STAGE01PARTCONTROLLER_H_
namespace VioletVreath {

/**
 * ステージ１コントローラー .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage01PartController : public StagePartController {

    GgafDxCore::GgafDxBgm* bgm_st1_;

public:
    enum {
        PROG_INIT = 1            ,
        PROG_STG01_01_BEGIN      ,
        PROG_STG01_01_PLAYING    ,
        PROG_STG01_02_BEGIN      ,
        PROG_STG01_02_PLAYING    ,
        PROG_STG01_03_BEGIN      ,
        PROG_STG01_03_PLAYING    ,
        PROG_STG01_CLIMAX_BEGIN  ,
        PROG_STG01_CLIMAX_PLAYING,
        PROG_FAINAL              ,
    };


    Stage01PartController(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~Stage01PartController();
};

}
#endif /*STAGE01PARTCONTROLLER_H_*/

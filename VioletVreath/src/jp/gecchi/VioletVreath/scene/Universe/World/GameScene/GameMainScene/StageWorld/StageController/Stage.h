#ifndef STAGE_H_
#define STAGE_H_
namespace VioletVreath {

/**
 * ステージ基底 .
 * @version 1.00
 * @since 2009/02/05
 * @author Masatoshi Tsuge
 */
class Stage : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT    ,
        PROG_BEGIN   ,
        PROG_PLAYING ,
        PROG_END     ,
    };

    static bool pause_;

    StagePartController* pScene_StagePartCtrler_;

public:
    Stage(const char* prm_name);

    virtual void initialize() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    /**
     * 初期処理
     */
    //virtual void orderStageMain() = 0;

    virtual ~Stage();
};

}
#endif /*STAGE_H_*/

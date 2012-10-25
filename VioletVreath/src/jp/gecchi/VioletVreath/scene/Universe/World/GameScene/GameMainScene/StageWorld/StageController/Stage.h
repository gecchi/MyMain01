#ifndef STAGE_H_
#define STAGE_H_

namespace VioletVreath {



class Stage : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1,
        PROG_BEGIN   ,
        PROG_PLAYING ,
        PROG_END     ,
    };

    static bool pause_;

    StagePartController* pScene_StagePartCtrlr_;

    Stage(const char* prm_name);

    virtual void initialize() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    /**
     * èâä˙èàóù
     */
    //virtual void orderStageMain() = 0;

    virtual ~Stage();
};

}
#endif /*STAGE_H_*/

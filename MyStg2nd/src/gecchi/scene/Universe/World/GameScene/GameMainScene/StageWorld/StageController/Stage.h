#ifndef STAGE_H_
#define STAGE_H_

namespace MyStg2nd {

enum {
    STAGE_PROG_INIT = 1,
    STAGE_PROG_BEGIN   ,
    STAGE_PROG_PLAYING ,
    STAGE_PROG_END     ,
};

class Stage : public GgafLib::DefaultScene {

public:
    static bool _pause;
public:

    Stage(const char* prm_name);

    virtual void initialize() override;
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;

    /**
     * èâä˙èàóù
     */
    //virtual void orderStageMain() = 0;

    virtual ~Stage();
};

}
#endif /*STAGE_H_*/

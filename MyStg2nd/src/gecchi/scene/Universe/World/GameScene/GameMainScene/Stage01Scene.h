#ifndef STAGE01SCENE_H_
#define STAGE01SCENE_H_

#define STAGE01_PROG_INIT    1
#define STAGE01_PROG_BEGIN   2
#define STAGE01_PROG_PLAYING    3
#define STAGE01_PROG_NEXT_STAGE_READY    4
#define STAGE01_PROG_END     7

namespace MyStg2nd {

class Stage01Scene : public StageScene {

public:

    Stage01Controller* _pScene_Stage01Controller;
    //BackGround01* _pBackGround01;
//    BackGroundStar* _pBackGroundStar;
    WorldBoundSpace001* _pWorldBoundSpace001;
    HoshiBoshi001* _pHoshiBoshi001;


    frame _frame_Begin;
    frame _frame_Play;
    frame _frame_End;

    LabelGecchi16Font* _pMessage;

    Stage01Scene(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void processFinal() override;

    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~Stage01Scene();
};

}
#endif /*STAGE01SCENE_H_*/

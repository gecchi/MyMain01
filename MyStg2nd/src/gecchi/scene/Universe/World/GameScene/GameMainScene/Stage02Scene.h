#ifndef STAGE02SCENE_H_
#define STAGE02SCENE_H_

#define STAGE02_PROG_INIT    1
#define STAGE02_PROG_BEGIN   2
#define STAGE02_PROG_PLAYING    3
#define STAGE02_PROG_NEXT_STAGE_READY    4
#define STAGE02_PROG_END     7

namespace MyStg2nd {

class Stage02Scene : public StageScene {

public:

    Stage02Controller* _pScene_Stage02Controller;
    //BackGround02* _pBackGround02;
//    BackGroundStar* _pBackGroundStar;
    WorldBoundSpace001* _pWorldBoundSpace001;
    HoshiBoshi001* _pHoshiBoshi001;


    frame _frame_Begin;
    frame _frame_Play;
    frame _frame_End;

    LabelGecchi16Font* _pMessage;

    Stage02Scene(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void processFinal() override;

    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~Stage02Scene();
};

}
#endif /*STAGE02SCENE_H_*/

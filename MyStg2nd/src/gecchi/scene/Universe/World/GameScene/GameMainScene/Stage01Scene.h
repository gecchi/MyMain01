#ifndef STAGE01SCENE_H_
#define STAGE01SCENE_H_


#define STAGE01_PROG_INIT    1
#define STAGE01_PROG_BEGIN   2
#define STAGE01_PROG_PLAY    3
#define STAGE01_PROG_END     7


namespace MyStg2nd {

class Stage01Scene : public StageScene {

public:

	GgafDx9Core::GgafDx9BgmPerformer* _pBgmPerformer;

    Stage01MainScene* _pScene_Stage01Main;
    BackGround01* _pBackGround01;
//    BackGroundStar* _pBackGroundStar;
    HoshiBoshi001* _pHoshiBoshi001;
    angle _angCamZX_prev;
    angle _angCamXY_prev;


    DWORD _dwFrame_Begin;
    DWORD _dwFrame_End;

    Stage01Scene(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void processFinal() override;

    virtual ~Stage01Scene();
};

}
#endif /*STAGE01SCENE_H_*/

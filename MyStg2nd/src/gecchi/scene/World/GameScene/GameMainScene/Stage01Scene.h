#ifndef STAGE01SCENE_H_
#define STAGE01SCENE_H_


#define STAGE01_PROG_INIT              1
#define STAGE01_PROG_BEGIN             2
#define STAGE01_PROG_PLAY             3
#define STAGE01_PROG_END     7


namespace MyStg2nd {

class Stage01Scene : public StageScene {

public:
    GgafDx9Core::GgafDx9BgmLead* _pBgmLead_st1;
    Stage01MainScene* _pStage01Main;
    BackGround01Plate* _pBackGround01;
    DWORD _dwFrame_Begin;
    DWORD _dwFrame_End;

    Stage01Scene(const char* prm_name);
    /**
     * ��������
     */
    void initialize();

    virtual void processBehavior();

    virtual void processJudgement();

    virtual void processFinal();

    virtual ~Stage01Scene();
};

}
#endif /*STAGE01SCENE_H_*/

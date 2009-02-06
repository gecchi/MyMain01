#ifndef STAGE01SCENE_H_
#define STAGE01SCENE_H_
namespace MyStg2nd {

class Stage01Scene : public StageScene {

public:
    GgafDx9Core::GgafDx9BgmLead* _pBgmLead_st1;

    Stage01Scene(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize();

    virtual void processBehavior();

    virtual void processJudgement();

    virtual void processFinal();

    virtual ~Stage01Scene();
};

}
#endif /*STAGE01SCENE_H_*/

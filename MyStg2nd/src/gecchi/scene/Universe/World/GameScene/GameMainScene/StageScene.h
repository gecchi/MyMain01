#ifndef STAGESCENE_H_
#define STAGESCENE_H_

#define STAGE_SCENE_PROG_INIT    1
#define STAGE_SCENE_PROG_BEGIN   2
#define STAGE_SCENE_PROG_PLAYING 3
#define STAGE_SCENE_PROG_END     7

namespace MyStg2nd {

class StageScene : public GgafDx9LibStg::DefaultScene {

public:
    static bool _pause;
public:
    frame _frame_Begin;
    frame _frame_Play;
    frame _frame_End;

    StageScene(const char* prm_name);

    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override;

    /**
     * èâä˙èàóù
     */
    //virtual void orderStageMain() = 0;

    virtual ~StageScene();
};

}
#endif /*STAGESCENE_H_*/

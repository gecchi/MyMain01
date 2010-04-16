#ifndef STAGESCENE_H_
#define STAGESCENE_H_

#define STAGE_PROG_INIT       1
#define STAGE_PROG_BEGIN      2
#define STAGE_PROG_PLAY_BEGIN 3
#define STAGE_PROG_PLAYING    4
#define STAGE_PROG_CHKPOINT01_PASS 5
#define STAGE_PROG_CHKPOINT02_PASS 6

namespace MyStg2nd {

class StageScene : public GgafDx9LibStg::DefaultScene {

public:
    static bool _pause;
public:
    StageScene(const char* prm_name);
    /**
     * 初期処理
     */
    //virtual void orderStageMain() = 0;

    virtual ~StageScene();
};

}
#endif /*STAGESCENE_H_*/

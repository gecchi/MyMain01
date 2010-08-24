#ifndef STAGESCENE_H_
#define STAGESCENE_H_

#define STAGE01_PROG_INIT       1
#define STAGE01_PROG_BEGIN      2
#define STAGE01_PROG_PLAYING_BEGIN 3
#define STAGE01_PROG_PLAYINGING    4
#define STAGE01_PROG_CHKPOINT01_PASS 5
#define STAGE01_PROG_CHKPOINT02_PASS 6

namespace MyStg2nd {

class StageScene : public GgafDx9LibStg::DefaultScene {

public:
    static bool _pause;
public:
    StageScene(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    //virtual void orderStageMain() = 0;

    virtual ~StageScene();
};

}
#endif /*STAGESCENE_H_*/

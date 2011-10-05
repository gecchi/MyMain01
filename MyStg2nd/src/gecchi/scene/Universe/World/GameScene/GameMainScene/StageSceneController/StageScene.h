#ifndef STAGESCENE_H_
#define STAGESCENE_H_

namespace MyStg2nd {

enum {
    STAGESCENE_PROG_INIT = 1,
    STAGESCENE_PROG_BEGIN   ,
    STAGESCENE_PROG_PLAYING ,
    STAGESCENE_PROG_END     ,
};

class StageScene : public GgafLib::DefaultScene {

public:
    static bool _pause;
public:

    StageScene(const char* prm_name);

    virtual void initialize() override;
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;

    /**
     * èâä˙èàóù
     */
    //virtual void orderStageMain() = 0;

    virtual ~StageScene();
};

}
#endif /*STAGESCENE_H_*/

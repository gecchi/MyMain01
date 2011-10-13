#ifndef RANKUPSCENE_H_
#define RANKUPSCENE_H_

namespace MyStg2nd {

enum {
    RANKUPSCENE_PROG_INIT = 1,
    RANKUPSCENE_PROG_BEGIN   ,
    RANKUPSCENE_PROG_PLAYING ,
    RANKUPSCENE_PROG_END     ,
};

class RankUpScene : public GgafLib::DefaultScene {

public:
    static bool _pause;
public:

    RankUpScene(const char* prm_name);

    virtual void initialize() override;
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual void processFinal() override;
    /**
     * èâä˙èàóù
     */
    //virtual void orderStageMain() = 0;

    virtual ~RankUpScene();
};

}
#endif /*RANKUPSCENE_H_*/

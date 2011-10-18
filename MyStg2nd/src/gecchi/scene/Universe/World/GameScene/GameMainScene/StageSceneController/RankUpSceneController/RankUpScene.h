#ifndef RANKUPSCENE_H_
#define RANKUPSCENE_H_

namespace MyStg2nd {

enum {
    RANKUPSCENE_PROG_INIT = 1,
    RANKUPSCENE_PROG_BEGIN   ,
    RANKUPSCENE_PROG_PLAYING ,
    RANKUPSCENE_PROG_RESULT  ,
    RANKUPSCENE_PROG_END     ,
};

class RankUpScene : public GgafLib::DefaultScene {

public:
    static bool _pause;
public:

    WorldBoundSpaceRankUp* _pWorldBoundSpace;
    HoshiBoshiRankUp* _pHoshiBoshi;
    LabelGecchi16Font* _pMessage;

    RankUpScene(const char* prm_name);

    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processFinal() override;
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;

    /**
     * èâä˙èàóù
     */
    //virtual void orderStageMain() = 0;

    virtual ~RankUpScene();
};

}
#endif /*RANKUPSCENE_H_*/

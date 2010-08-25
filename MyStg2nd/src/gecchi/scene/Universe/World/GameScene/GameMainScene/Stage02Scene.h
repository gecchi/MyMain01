#ifndef STAGE02SCENE_H_
#define STAGE02SCENE_H_

namespace MyStg2nd {

class Stage02Scene : public StageScene {

public:

    Stage02Controller* _pScene_Stage02Controller;
    //BackGround02* _pBackGround02;
//    BackGroundStar* _pBackGroundStar;
    WorldBoundSpace002* _pWorldBoundSpace;
    HoshiBoshi001* _pHoshiBoshi;

    LabelGecchi16Font* _pMessage;

    Stage02Scene(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void processFinal() override;
    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~Stage02Scene();
};

}
#endif /*STAGE02SCENE_H_*/

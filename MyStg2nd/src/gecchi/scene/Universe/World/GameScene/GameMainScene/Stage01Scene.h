#ifndef STAGE01SCENE_H_
#define STAGE01SCENE_H_



namespace MyStg2nd {

class Stage01Scene : public StageScene {

public:

    Stage01Controller* _pScene_Stage01Controller;
    //BackGround01* _pBackGround01;
//    BackGroundStar* _pBackGroundStar;
    WorldBoundSpace001* _pWorldBoundSpace;
    HoshiBoshi001* _pHoshiBoshi;


    LabelGecchi16Font* _pMessage;

    Stage01Scene(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void processFinal() override;
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~Stage01Scene();
};

}
#endif /*STAGE01SCENE_H_*/

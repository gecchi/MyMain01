#ifndef STAGE01_H_
#define STAGE01_H_



namespace MyStg2nd {

class Stage01 : public StageScene {

public:

    Stage01Controller* _pScene_Stage01Controller;
    WorldBoundSpace001* _pWorldBoundSpace;
    HoshiBoshi001* _pHoshiBoshi;


    LabelGecchi16Font* _pMessage;

    Stage01(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void processFinal() override;
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~Stage01();
};

}
#endif /*STAGE01_H_*/

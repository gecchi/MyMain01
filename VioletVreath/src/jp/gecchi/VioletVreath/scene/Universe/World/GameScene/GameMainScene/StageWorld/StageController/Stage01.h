#ifndef STAGE01_H_
#define STAGE01_H_



namespace VioletVreath {

class Stage01 : public Stage {

public:

    Stage01PartController* _pScene_Stage01PartController;
    WorldBoundSpace001* _pWorldBoundSpace;
    HoshiBoshi001* _pHoshiBoshi;

    Planet001* _pPlanet;
    LabelGecchi16Font* _pMessage;

    Stage01(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~Stage01();
};

}
#endif /*STAGE01_H_*/

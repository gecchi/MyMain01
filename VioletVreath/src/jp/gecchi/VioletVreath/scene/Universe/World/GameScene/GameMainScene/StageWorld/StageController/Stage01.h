#ifndef STAGE01_H_
#define STAGE01_H_



namespace VioletVreath {

class Stage01 : public Stage {

public:

    Stage01PartController* pScene_Stage01PartController_;
    WorldBoundSpace001* pWorldBoundSpace_;
    HoshiBoshi001* pHoshiBoshi_;

    Planet001* pPlanet_;
    LabelGecchi16Font* pMessage_;

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

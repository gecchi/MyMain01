#ifndef STAGE02_H_
#define STAGE02_H_

namespace MyStg2nd {

class Stage02 : public Stage {

public:

    Stage02PartController* _pScene_Stage02PartController;
    WorldBoundSpace002* _pWorldBoundSpace;
    HoshiBoshi001* _pHoshiBoshi;

    LabelGecchi16Font* _pMessage;

    Stage02(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void processFinal() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~Stage02();
};

}
#endif /*STAGE02_H_*/

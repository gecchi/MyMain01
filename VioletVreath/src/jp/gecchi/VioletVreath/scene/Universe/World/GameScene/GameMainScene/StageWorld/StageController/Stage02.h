#ifndef STAGE02_H_
#define STAGE02_H_

namespace VioletVreath {

class Stage02 : public Stage {

public:

    WorldBoundSpace002* pWorldBoundSpace_;
    HoshiBoshi001* pHoshiBoshi_;

    LabelGecchi16Font* pMessage_;

    Stage02(const char* prm_name);
    /**
     * ��������
     */
    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~Stage02();
};

}
#endif /*STAGE02_H_*/

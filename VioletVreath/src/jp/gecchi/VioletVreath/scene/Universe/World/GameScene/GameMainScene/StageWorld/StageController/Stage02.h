#ifndef STAGE02_H_
#define STAGE02_H_
namespace VioletVreath {

/**
 * ステージ02 .
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class Stage02 : public Stage {

public:

    WorldBoundSpace002* pWorldBoundSpace_;
    HoshiBoshi001* pHoshiBoshi_;

    LabelGecchi16Font* pMessage_;

    Stage02(const char* prm_name);
    /**
     * 初期処理
     */
    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~Stage02();
};

}
#endif /*STAGE02_H_*/

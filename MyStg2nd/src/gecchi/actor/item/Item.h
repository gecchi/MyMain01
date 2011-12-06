#ifndef ITEM_H_
#define ITEM_H_

namespace MyStg2nd {


/**
 * ƒAƒCƒeƒ€ .
 * @version 1.00
 * @since 2011/02/04
 * @author Masatoshi Tsuge
 */
class Item : public GgafLib::DefaultMeshSetActor {

public:
    TractorMagic* _pTractorMagic;

    Item(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

	TractorMagic* getTractorMagic();

    virtual void initialize() override;

    virtual void onReset() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onInactive() override;

    virtual ~Item();
};

}
#endif /*ITEM_H_*/


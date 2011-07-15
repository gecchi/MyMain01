#ifndef ITEM_H_
#define ITEM_H_

enum {
    ITEM_PROG_NOTIONG = 1, //‰½‚à‚µ‚Ä‚¢‚È‚¢ó‘Ô
    ITEM_PROG_DRIFT      , //’ÊíˆÚ“®ó‘Ô
    ITEM_PROG_ATTACH     , //‹z’…’†(–¢‹z’…)ó‘Ô
    ITEM_PROG_ABSORB     , //‹z’…’†(‹z’…Ï)ó‘Ô
};

namespace MyStg2nd {

/**
 * ƒAƒCƒeƒ€ .
 * @version 1.00
 * @since 2011/02/04
 * @author Masatoshi Tsuge
 */
class Item : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    Item(const char* prm_name, const char* prm_model);

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


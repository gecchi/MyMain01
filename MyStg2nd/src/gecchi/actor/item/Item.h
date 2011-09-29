#ifndef ITEM_H_
#define ITEM_H_

namespace MyStg2nd {

enum {
    ITEM_PROG_NOTIONG = 1, //何もしていない状態
    ITEM_PROG_DRIFT      , //通常移動状態
    ITEM_PROG_ATTACH     , //吸着中(未吸着)状態
    ITEM_PROG_ABSORB     , //吸着中(吸着済)状態
};

/**
 * アイテム .
 * @version 1.00
 * @since 2011/02/04
 * @author Masatoshi Tsuge
 */
class Item : public GgafLib::DefaultMeshSetActor {

public:
    Item(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

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


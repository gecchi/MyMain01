#ifndef ITEM_H_
#define ITEM_H_

/** 何もしていない状態 */
#define ITEM_PROG_NOTIONG 0
/** 通常移動状態 */
#define ITEM_PROG_DRIFT   1
/** 吸着中(未吸着)状態 */
#define ITEM_PROG_ATTACH  2
/** 吸着中(吸着済)状態 */
#define ITEM_PROG_ABSORB  3

namespace MyStg2nd {

/**
 * アイテム .
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


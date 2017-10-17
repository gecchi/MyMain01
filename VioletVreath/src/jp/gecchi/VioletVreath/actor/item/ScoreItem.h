#ifndef SCOREITEM_H_
#define SCOREITEM_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/item/Item.h"

namespace VioletVreath {

/**
 * Score�񕜃A�C�e���� .
 * @version 1.00
 * @since 2011/11/21
 * @author Masatoshi Tsuge
 */
class ScoreItem : public Item {

public:
    enum {
        PROG_DRIFT      , //�ʏ�ړ����
        PROG_ATTACH     , //�z����(���z��)���
        PROG_ABSORB     , //�z����(�z����)���
        PROG_BANPEI,
    };
    /** �z���������W */
    int kDX_, kDY_, kDZ_;
public:
    ScoreItem(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onInactive() override;

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~ScoreItem();
};

}
#endif /*SCOREITEM_H_*/


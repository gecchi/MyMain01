#ifndef STRINGBOARDACTOR_H_
#define STRINGBOARDACTOR_H_
namespace GgafDx9LibStg {

/**
 * ç¿ïWïœä∑çœÇ›î¬É|Éäï∂éöï\é¶
 * @version 1.00
 * @since 2010/06/23
 * @author Masatoshi Tsuge
 */
class StringBoardActor : public GgafDx9Core::GgafDx9StringBoardActor {

public:
    StringBoardActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
        GgafDx9Core::GgafDx9StringBoardActor::onCreateModel();
    }

    virtual void initialize() override {
    }

    virtual void onActive() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void catchEvent(UINT32 prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual void onInactive() override {
    }

    virtual ~StringBoardActor();

};

}
#endif /*STRINGBOARDACTOR_H_*/

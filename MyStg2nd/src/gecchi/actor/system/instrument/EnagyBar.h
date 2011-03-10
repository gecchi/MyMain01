#ifndef ENAGYBAR_H_
#define ENAGYBAR_H_
namespace MyStg2nd {

class EnagyBar : public GgafDx9LibStg::DefaultBoardActor {

public:

    GgafDx9LibStg::AmountGraph _amount;

    float _fSize_BoardModelWidthPx;

    EnagyBar(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void addVal(double prm_val);


    virtual ~EnagyBar();
};

}
#endif /*ENAGYBAR_H_*/


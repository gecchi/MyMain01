#ifndef TURBOMETER_H_
#define TURBOMETER_H_
namespace MyStg2nd {

class TurboMeter : public GgafDx9LibStg::DefaultBoardSetActor {

public:
    TurboMeter(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    virtual ~TurboMeter();
};

}
#endif /*BACKGROUNDCHIPBOARD_H_*/


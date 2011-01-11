#ifndef MAGICMETER_H_
#define MAGICMETER_H_
namespace MyStg2nd {


class MagicMeter : public GgafDx9LibStg::GgafDx9BoardSetActor {

public:
    LaserMagic*  _pLaserMagic;
    OptionMagic* _pOptionMagic;

    int _pos_pattern_no[9][8];
    int _activeMagicKind;
    int _activeMagicLevel;
    float _width;
    float _height;
    MagicMeter(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void processDraw() override;

    virtual ~MagicMeter();
};

}
#endif /*MAGICMETER_H_*/


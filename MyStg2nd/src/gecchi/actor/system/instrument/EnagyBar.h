#ifndef ENAGYBAR_H_
#define ENAGYBAR_H_
namespace MyStg2nd {

class EnagyBar : public GgafDx9LibStg::DefaultBoardActor {
    GgafDx9LibStg::QuantityUnit _qu;
public:
    double _value;
    float _fSize_BoardModelWidthPx;

    void addVal(double prm_val) {
        _value += prm_val;
        if (_value < 0.0) {
            _value = 0.0;
        }
    }

    EnagyBar(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;


    virtual ~EnagyBar();
};

}
#endif /*ENAGYBAR_H_*/


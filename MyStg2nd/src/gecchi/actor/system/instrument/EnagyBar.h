#ifndef ENAGYBAR_H_
#define ENAGYBAR_H_
namespace MyStg2nd {

class EnagyBar : public GgafDx9LibStg::DefaultBoardActor {

    GgafDx9LibStg::QuantityUnit _qu;
    float _enagy;
    float _fSize_BoardModelWidthPx;
public:

    EnagyBar(const char* prm_name);

    void initialize() override;

    void processReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    virtual ~EnagyBar();
};

}
#endif /*ENAGYBAR_H_*/


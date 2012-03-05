#ifndef ENAGYBAR_H_
#define ENAGYBAR_H_
namespace VioletVreath {

class EnagyBar : public GgafLib::DefaultBoardActor {

public:
    /** 内容量 */
    GgafLib::AmountGraph* pAmount_;

    float _fSize_BoardModelWidthPx;

    /**
     *
     * @param prm_name
     * @param prm_pAmount config済みの AmountGraphオブジェクトの参照
     */
    EnagyBar(const char* prm_name, GgafLib::AmountGraph* prm_pAmount);

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


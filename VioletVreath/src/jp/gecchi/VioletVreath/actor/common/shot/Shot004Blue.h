#ifndef SHOT004BLUE_H_
#define SHOT004BLUE_H_
namespace VioletVreath {

/**
 * �ėp�e004(��) .
 * �j��s�\�œ��������ړ��̏����ȃ��[�U�[��<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot004Blue : public GgafLib::SingleLaser {
public:

    bool view_in_;
    Shot004Blue(const char* prm_name);


    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void drawHitArea() override;

    virtual ~Shot004Blue();
};

}
#endif /*SHOT004BLUE_H_*/

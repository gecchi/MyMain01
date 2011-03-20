#ifndef VIEWPOINTGUIDE_H_
#define VIEWPOINTGUIDE_H_

namespace MyStg2nd {

/**
 * 注視点 .
 * @version 1.00
 * @since 2010/09/22
 * @author Masatoshi Tsuge
 */
class ViewPointGuide : public GgafDx9LibStg::DefaultD3DXMeshActor {

public:

    /**
     * コンストラクタ .
     * @param prm_name
     * @return
     */
    ViewPointGuide(const char* prm_name);

    void onCreateModel() override {
    }
    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    virtual int isOutOfView() override {
        return 0; //常に表示
    }

    virtual bool isOutOfUniverse() override {
        return false; //常に表示
    }



    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~ViewPointGuide();
};

}
#endif /*VIEWPOINTGUIDE_H_*/


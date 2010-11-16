#ifndef MYOPTIONCONTROLLERGIZMO_H_
#define MYOPTIONCONTROLLERGIZMO_H_
namespace MyStg2nd {

/**
 * オプションの纏め役クラスのギズモ表示クラス .
 * @version 1.00
 * @since 2010/03/16
 * @author Masatoshi Tsuge
 */
class MyOptionControllerGizmo : public GgafDx9LibStg::DefaultMeshActor {

public:
    int _ptn_no;

    MyOptionControllerGizmo(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override {
    }

    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    void drawHitArea() override;

    int isOutOfView() override;

    bool isOutOfUniverse() override;

    virtual ~MyOptionControllerGizmo();
};

}
#endif /*MYOPTIONCONTROLLERGIZMO_H_*/


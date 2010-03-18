#ifndef MYOPTIONPARENTGIZMO_H_
#define MYOPTIONPARENTGIZMO_H_
namespace MyStg2nd {

class MyOptionParentGizmo : public GgafDx9LibStg::DefaultMeshActor {

public:
    int _ptn_no;

    MyOptionParentGizmo(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override {
    }

    void processHappen(int prm_no) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    void drawHitArea() override;

    int isOffscreen() override;

    bool isOutOfGameSpace() override;

    virtual ~MyOptionParentGizmo();
};

}
#endif /*MYOPTIONPARENTGIZMO_H_*/


#ifndef MYOPTIONCONTROLLERGIZMO_H_
#define MYOPTIONCONTROLLERGIZMO_H_
namespace MyStg2nd {

/**
 * �I�v�V�����̓Z�ߖ��N���X�̃M�Y���\���N���X .
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

    void catchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    void drawHitArea() override;

    int isOffscreen() override;

    bool isOutOfGameSpace() override;

    virtual ~MyOptionControllerGizmo();
};

}
#endif /*MYOPTIONCONTROLLERGIZMO_H_*/

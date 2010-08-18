#ifndef ACTORTABLESCENE_H_
#define ACTORTABLESCENE_H_
namespace GgafDx9LibStg {

/**
 * �A�N�^�[�e�[�u���Ǘ� .
 * �����̓G�o���e�[�u���̂悤�ȁA���񂵂��������邽�߂̃V�[���B
 * ���񂵉\�ȓG�o���e�[�u���Ƃ͋�̓I�ɁA
 * �G�i��ґ��j�����ł���΁A�������̓G�i��ґ��j���o���B
 * �G�����ł����Ƃ��A��莞�ԂŎ��̓G���o���B
 * �Ƃ����悤�ȃe�[�u���̂��ƁB
 * @version 1.00
 * @since 2007/12/06
 * @author Masatoshi Tsuge
 */
class ActorTableScene : public GgafDx9Core::GgafDx9Scene {
public:




    GgafCore::GgafLinkedListRing<GgafCore::GgafMainActor> _table;

    ActorTableScene(const char* prm_name);

    GgafCore::GgafGroupActor* addToTable(GgafCore::GgafMainActor* prm_pMainActor);

    GgafCore::GgafGroupActor* addToTable(actorkind prm_kind, GgafCore::GgafMainActor* prm_pMainActor);


    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }
    virtual void processDraw() {
    }
    virtual void processHappen(int prm_no) override {
    }
    virtual void processFinal() override {
    }

    virtual ~ActorTableScene();
};

}
#endif /*ACTORTABLESCENE_H_*/

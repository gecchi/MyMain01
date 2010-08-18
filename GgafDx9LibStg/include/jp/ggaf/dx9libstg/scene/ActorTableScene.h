#ifndef ACTORTABLESCENE_H_
#define ACTORTABLESCENE_H_
namespace GgafDx9LibStg {

/**
 * アクターテーブル管理 .
 * 斑鳩の敵出現テーブルのような、早回しを実現するためのシーン。
 * 早回し可能な敵出現テーブルとは具体的に、
 * 敵（や編隊）が消滅すれば、即刻次の敵（や編隊）が出現。
 * 敵が消滅せずとも、一定時間で次の敵が出現。
 * というようなテーブルのこと。
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

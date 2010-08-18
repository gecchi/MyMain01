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

    class TblElem {
    public:
        GgafCore::GgafMainActor* _pActor;
        frame _max_delay_offset;
        TblElem(GgafCore::GgafMainActor* prm_pActor, frame prm_max_delay_offset) {
            _pActor = prm_pActor;
            _max_delay_offset = prm_max_delay_offset;
        }
        virtual ~TblElem() {
            //_pActorはシーン所属となるため解放は不要
        }
    };

    frame _prev_active_frame;

    GgafCore::GgafLinkedListRing<TblElem> _table;

    ActorTableScene(const char* prm_name);

    GgafCore::GgafGroupActor* addToTable(GgafCore::GgafMainActor* prm_pMainActo, frame prm_max_delay_offsetr);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }
    virtual void processDraw() override {
    }
    virtual void processHappen(int prm_no) override {
    }
    virtual void processFinal() override {
    }
    virtual ~ActorTableScene();
};

}
#endif /*ACTORTABLESCENE_H_*/

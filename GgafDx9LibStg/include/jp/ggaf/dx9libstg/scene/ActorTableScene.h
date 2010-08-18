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

    class TblElem {
    public:
        GgafCore::GgafMainActor* _pActor;
        frame _max_delay_offset;
        TblElem(GgafCore::GgafMainActor* prm_pActor, frame prm_max_delay_offset) {
            _pActor = prm_pActor;
            _max_delay_offset = prm_max_delay_offset;
        }
        virtual ~TblElem() {
            //_pActor�̓V�[�������ƂȂ邽�߉���͕s�v
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

#ifndef GGAFDISUSEDACTOR_H_
#define GGAFDISUSEDACTOR_H_
namespace GgafCore {

/**
 * �s�v�ɂȂ����A�N�^�[ .
 * GgafGarbageBox�i�S�~���j�ɏ��������삳��܂��B<BR>
 * ���̃A�N�^�[�ɏ��������A�N�^�[�́A�x���ꑁ���� delete ����鋰�|�̃A�N�^�[�ł��B<BR>
 * �u�x���ꑁ���� delete �����A�N�^�[�B�v�c���[�́A�g�b�v�m�[�h�Ɉʒu���܂��B<BR>
 * ���g�͍폜����邱�Ƃ͂���܂���B<BR>
 * @version 1.00
 * @since 2008/12/17
 * @author Masatoshi Tsuge
 */
class GgafDisusedActor : public GgafActor {
public:
    GgafDisusedActor() :
        GgafActor("DisusedActor", nullptr) {
    }
    void initialize() override {
    }
    void processBehavior() override {
    }
    void processJudgement() override {
    }
    void processPreDraw() override {
    }
    void processDraw() override {
    }
    void processAfterDraw() override {
    }
    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }
    void processFinal() override {
    }
    bool processHitChkLogic(GgafActor* prm_pOtherActor) override {
        return false;
    }
    void onHit(GgafActor* prm_pOtherActor) override {
    }
    GgafGod* askGod() {
        return nullptr;
    }

    virtual void updateActiveInTheTree() override {
        _is_active_in_the_tree_flg = false;
        _is_active_flg = false;
    }

    virtual ~GgafDisusedActor() {
    }
};

}
#endif /*GGAFDISUSEDACTOR_H_*/

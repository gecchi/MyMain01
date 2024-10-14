#ifndef GGAF_CORE_DISUSEDACTOR_H_
#define GGAF_CORE_DISUSEDACTOR_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/actor/Actor.h"

namespace GgafCore {

/**
 * �s�v�ɂȂ����A�N�^�[ .
 * GarbageBox�i�S�~���j�ɏ��������삳��܂��B<BR>
 * ���̃A�N�^�[�ɏ��������A�N�^�[�́A�x���ꑁ���� delete ����鋰�|�̃A�N�^�[�ł��B<BR>
 * �u�x���ꑁ���� delete �����A�N�^�[�B�v�c���[�́A�g�b�v�m�[�h�Ɉʒu���܂��B<BR>
 * ���g�͍폜����邱�Ƃ͂���܂���B<BR>
 * @version 1.00
 * @since 2008/12/17
 * @author Masatoshi Tsuge
 */
class DisusedActor : public Actor {

public:
    DisusedActor() :
        Actor("DisusedActor") {
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
    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }
    void processFinal() override {
    }
    void onHit(const Checker* prm_pOtherChecker, const Actor* prm_pOtherActor) override {
    }
    Caretaker* askCaretaker() {
        return nullptr;
    }

    void updateActiveInTheTree() override {
        _is_active_in_the_tree_flg = false;
        _is_active_flg = false;
    }

    virtual ~DisusedActor() {
    }
};

}
#endif /*GGAF_CORE_DISUSEDACTOR_H_*/

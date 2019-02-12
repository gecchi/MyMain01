#ifndef GGAF_CORE_DISUSEDSCENE_H_
#define GGAF_CORE_DISUSEDSCENE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/scene/Scene.h"

namespace GgafCore {

/**
 * �s�v�ɂȂ����V�[�� .
 * GarbageBox�i�S�~���j�ɏ��������삳��܂��B<BR>
 * ���̃V�[���ɏ��������V�[���́A�x���ꑁ���� delete ����鋰�|�̃V�[���ł��B<BR>
 * �u�x���ꑁ���� delete �����V�[���B�v�c���[�́A�g�b�v�m�[�h�Ɉʒu���܂��B<BR>
 * ���g�͍폜����邱�Ƃ͂���܂���B<BR>
 * @version 1.00
 * @since 2008/12/17
 * @author Masatoshi Tsuge
 */
class DisusedScene : public Scene {
public:
    DisusedScene() :
        Scene("DisusedScene") {
        _obj_class |= Obj_ggaf_DisusedScene;
        _class_name = "DisusedScene";
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
    void updateActiveInTheTree() override {
        _is_active_in_the_tree_flg = false;
        _is_active_flg = false;
    }
    virtual ~DisusedScene() {
    }
};

}
#endif /*GGAF_CORE_DISUSEDSCENE_H_*/

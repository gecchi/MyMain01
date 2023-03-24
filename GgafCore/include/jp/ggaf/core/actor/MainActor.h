#ifndef GGAF_CORE_MAINACTOR_H_
#define GGAF_CORE_MAINACTOR_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/actor/Actor.h"

namespace GgafCore {

/**
 * ���ʂ̃A�N�^�[(����) .
 * ���ʃA�N�^�[�N���X�ւ̃C���^�[�t�F�C�X�ł���A<BR>
 * �V���ɃA�N�^�[�N���X�����ꍇ�{�N���X���p�����ăA�N�^�[�N���X����邱�ƂƂ���B<BR>
 * @version 1.00
 * @since 2008/03/24
 * @author Masatoshi Tsuge
 */
class MainActor : public Actor {

public:
    /** [r]���g����������O���[�v�̒c�� */
    GroupHead* _pGroupHead;
    /** [r]���g����������O���[�v�̒c���̃V�[������� */
    SceneMediator* _pSceneMediator;

public:
    MainActor(const char* prm_name);

    virtual MainActor* getNext() const override { //���ϖ߂�l
        return (MainActor*)Actor::getNext();
    }

    virtual MainActor* getPrev() const override { //���ϖ߂�l
        return (MainActor*)Actor::getPrev();
    }

    void updateActiveInTheTree() override;

    /**
     * ���c���[�m�[�h��A�����X�g����؂藣���A�Ɨ�����B .
     * �؂藣���ꌊ���J���������́A����̃m�[�h�����𖄂߂܂��i�ĘA�����܂��j<BR>
     * ���m�[�h�Ɏq���Ԃ牺�����Ă����ꍇ�A�������؂藣���ꂽ���ƂɂȂ�܂��B<BR>
     * MainActor�̏ꍇ�A�z���� _pSceneMediator �y�� _pGroupHead �� nullptr ���Z�b�g�����B<BR>
     * @return  ���m�[�h�̃|�C���^
     */
    virtual MainActor* extract() override;

    /**
     * �V�[������҂�ݒ肷��B .
     */
    virtual void setSceneMediator(SceneMediator* prm_pSceneMediator);

    /**
     * �c����ݒ肷��B<BR>
     */
    virtual void setGroupHead(GroupHead* prm_pGroupHead);

    /**
     * �����V�[���̃V�[������Ҏ擾�B�A���V�[���ɏ������Ă��Ȃ��ꍇ�́A���̐�(Spacetime)�̃V�[������҂�Ԃ� .
     * @return �����V�[������҂̒���ҁB(���Ȃ��ꍇ ���̐�(Spacetime)�̒����)
     */
    SceneMediator* getSceneMediator();

    /**
     * �V�[���c�����擾����B .
     * @return �c�� �^ ���Ȃ��ꍇ nullptr
     */
    virtual GroupHead* getGroupHead();

    /**
     * �V���Ɏ�ʂ�ݒ肵�A�A�N�^�[��z���ɒǉ�����B
     * ��ʂ̓A�N�^�[���ێ������ʂ𖳎����A�����̎�ʂ�D�悷��B<BR>
     * ���g�Ǝ�ʂ��قȂ�ꍇ�͎q�ɒc��(GroupHead)������ł��̂܂��q�Ɉ����̃A�N�^�[��ǉ����܂��B<BR>
     * ���g�Ǝ�ʂ������ꍇ�́A�P�Ɏq�Ɉ����̃A�N�^�[��ǉ����܂��B<BR>
     * @param prm_kind ���
     * @param prm_pMainActor ��ʂƋ��ɒǉ��������A�N�^�[
     * @return �����A�N�^�[�̒c��(GroupHead)
     */
    GroupHead* appendGroupChild(kind_t prm_kind, MainActor* prm_pMainActor);

    /**
     * �V���Ɏ�ʂ�ݒ肵�A�A�N�^�[��z���ɒǉ�����B .
     * �������A��ʂ̓A�N�^�[���ێ������ʂ��̗p����B<BR>
     * ���g�Ǝ�ʂ��قȂ�ꍇ�͎q�ɒc��(GroupHead)������ł��̂܂��q�Ɉ����̃A�N�^�[��ǉ����܂��B<BR>
     * ���g�Ǝ�ʂ������ꍇ�́A�P�Ɏq�Ɉ����̃A�N�^�[��ǉ����܂��B<BR>
     * @param prm_pMainActor ��ʂƋ��ɒǉ��������A�N�^�[
     * @return �����A�N�^�[�̒c��(GroupHead)
     */
    GroupHead* appendGroupChild(MainActor* prm_pMainActor);

    /**
     * �z���̐����\�Ȓc����T���B
     * @param prm_kind �T�������c���̎��
     * @return �c���A�����͑��݂��Ȃ���� nullptr
     */
    GroupHead* searchChildGroupHead(kind_t prm_kind);

    /**
     * �Ǘ��҂ɉy�� .
     * @return  �Ă΂�ďo�Ă����Ǘ���
     */
    virtual Caretaker* askCaretaker() override;

    /**
     * �������Ă���c���̎�ʂ��擾���� .
     * ���ʂ̎����Ŏ��R�Ɏg�p���邱�Ƃ�z��B
     * @return
     */
    kind_t lookUpKind();

    bool processHitChkLogic(Actor* prm_pOtherActor) override {
        return false;
    }

    virtual ~MainActor();
};

}
#endif /*GGAF_CORE_MAINACTOR_H_*/

#ifndef GGAFMAINACTOR_H_
#define GGAFMAINACTOR_H_
#include "jp/ggaf/core/actor/GgafActor.h"

namespace GgafCore {

/**
 * ���ʂ̃A�N�^�[(����).
 * ���ʃA�N�^�[�N���X�ւ̃C���^�[�t�F�C�X�ł���A<BR>
 * �V���ɃA�N�^�[�N���X�����ꍇ�{�N���X���p�����ăA�N�^�[�N���X����邱�ƂƂ���B<BR>
 * @version 1.00
 * @since 2008/03/24
 * @author Masatoshi Tsuge
 */
class GgafMainActor : public GgafActor {

public:
    /** [r]���g����������O���[�v�̒c�� */
    GgafGroupHead* _pGroupHead;
    /** [r]���g����������O���[�v�̒c���̃V�[���ē� */
    GgafSceneDirector* _pSceneDirector;

public:
    GgafMainActor(const char* prm_name, GgafStatus* prm_pStat);

    /**
     * ���̃m�[�h�擾����B .
     * @return  ���m�[�h
     */
    virtual GgafMainActor* getNext() override {
        return (GgafMainActor*)GgafActor::getNext();
    }

    /**
     * �O�̃m�[�h�擾����B .
     * @return  �O�m�[�h
     */
    virtual GgafMainActor* getPrev() override {
        return (GgafMainActor*)GgafActor::getPrev();
    }

    void updateActiveInTheTree() override;

    /**
     * ���c���[�m�[�h��A�����X�g����؂藣���A�Ɨ�����B .
     * �؂藣���ꌊ���J���������́A����̃m�[�h�����𖄂߂܂��i�ĘA�����܂��j<BR>
     * ���m�[�h�Ɏq���Ԃ牺�����Ă����ꍇ�A�������؂藣���ꂽ���ƂɂȂ�܂��B<BR>
     * GgafMainActor�̏ꍇ�A�z���� _pSceneDirector �y�� _pGroupHead �� nullptr ���Z�b�g�����B<BR>
     * @return  ���m�[�h�̃|�C���^
     */
    virtual GgafMainActor* extract() override;

    /**
     * �V�[���ē�ݒ肷��B .
     */
    virtual void setSceneDirector(GgafSceneDirector* prm_pSceneDirector);

    /**
     * �c����ݒ肷��B<BR>
     */
    virtual void setGroupHead(GgafGroupHead* prm_pGroupHead);

    /**
     * �V�[���ē擾�B .
     * @return �ē� �^ ���Ȃ��ꍇ nullptr
     */
    virtual GgafSceneDirector* getSceneDirector();

    /**
     * �V�[���c�����擾����B .
     * @return �c�� �^ ���Ȃ��ꍇ nullptr
     */
    virtual GgafGroupHead* getMyGroupHead();

    /**
     * �V���Ɏ�ʂ�ݒ肵�A�A�N�^�[��z���ɒǉ�����B
     * ��ʂ̓A�N�^�[���ێ������ʂ𖳎����A�����̎�ʂ�D�悷��B<BR>
     * ���g�Ǝ�ʂ��قȂ�ꍇ�̓T�u�ɒc��(GgafGroupHead)������ł��̂܂��T�u�Ɉ����̃A�N�^�[��ǉ����܂��B<BR>
     * ���g�Ǝ�ʂ������ꍇ�́A�P�ɃT�u�Ɉ����̃A�N�^�[��ǉ����܂��B<BR>
     * @param prm_kind ���
     * @param prm_pMainActor ��ʂƋ��ɒǉ��������A�N�^�[
     * @return �����A�N�^�[�̒c��(GgafGroupHead)
     */
    GgafGroupHead* addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor);

    /**
     * �V���Ɏ�ʂ�ݒ肵�A�A�N�^�[��z���ɒǉ�����B .
     * �������A��ʂ̓A�N�^�[���ێ������ʂ��̗p����B<BR>
     * ���g�Ǝ�ʂ��قȂ�ꍇ�̓T�u�ɒc��(GgafGroupHead)������ł��̂܂��T�u�Ɉ����̃A�N�^�[��ǉ����܂��B<BR>
     * ���g�Ǝ�ʂ������ꍇ�́A�P�ɃT�u�Ɉ����̃A�N�^�[��ǉ����܂��B<BR>
     * @param prm_pMainActor ��ʂƋ��ɒǉ��������A�N�^�[
     * @return �����A�N�^�[�̒c��(GgafGroupHead)
     */
    GgafGroupHead* addSubGroup(GgafMainActor* prm_pMainActor);

    /**
     * �z���̐����\�Ȓc����T���B
     * @param prm_kind �T�������c���̎��
     * @return �c���A�����͑��݂��Ȃ���� nullptr
     */
    GgafGroupHead* searchSubGroupHead(actorkind prm_kind);

    /**
     * �_�ɉy�� .
     * @return  �Ă΂�ďo�Ă����_
     */
    virtual GgafGod* askGod() override;

    /**
     * ��ʂ��擾���� .
     * ���ʂ̎����Ŏ��R�Ɏg�p���邱�Ƃ�z��B
     * @return
     */
    actorkind getKind();

    virtual ~GgafMainActor();
};

}
#endif /*GGAFMAINACTOR_H_*/

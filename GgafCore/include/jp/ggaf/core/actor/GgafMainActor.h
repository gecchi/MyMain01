#ifndef GGAFCORE_GGAFMAINACTOR_H_
#define GGAFCORE_GGAFMAINACTOR_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/GgafActor.h"

namespace GgafCore {

/**
 * ���ʂ̃A�N�^�[(����) .
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
    /** [r]���g����������O���[�v�̒c���̃V�[������� */
    GgafSceneMediator* _pSceneMediator;

public:
    GgafMainActor(const char* prm_name, GgafStatus* prm_pStat);

    virtual GgafMainActor* getNext() const override { //���ϖ߂�l
        return (GgafMainActor*)GgafActor::getNext();
    }

    virtual GgafMainActor* getPrev() const override { //���ϖ߂�l
        return (GgafMainActor*)GgafActor::getPrev();
    }

    void updateActiveInTheTree() override;

    /**
     * ���c���[�m�[�h��A�����X�g����؂藣���A�Ɨ�����B .
     * �؂藣���ꌊ���J���������́A����̃m�[�h�����𖄂߂܂��i�ĘA�����܂��j<BR>
     * ���m�[�h�Ɏq���Ԃ牺�����Ă����ꍇ�A�������؂藣���ꂽ���ƂɂȂ�܂��B<BR>
     * GgafMainActor�̏ꍇ�A�z���� _pSceneMediator �y�� _pGroupHead �� nullptr ���Z�b�g�����B<BR>
     * @return  ���m�[�h�̃|�C���^
     */
    virtual GgafMainActor* extract() override;

    /**
     * �V�[������҂�ݒ肷��B .
     */
    virtual void setMySceneMediator(GgafSceneMediator* prm_pSceneMediator);

    /**
     * �c����ݒ肷��B<BR>
     */
    virtual void setMyGroupHead(GgafGroupHead* prm_pGroupHead);

    /**
     * �����V�[���̃V�[������Ҏ擾�B�A���V�[���ɏ������Ă��Ȃ��ꍇ�́A���̐�(Spacetime)�̃V�[������҂�Ԃ� .
     * @return �����V�[������҂̒���ҁB(���Ȃ��ꍇ ���̐�(Spacetime)�̒����)
     */
    GgafSceneMediator* getMySceneMediator();

    /**
     * �V�[���c�����擾����B .
     * @return �c�� �^ ���Ȃ��ꍇ nullptr
     */
    virtual GgafGroupHead* getMyGroupHead();

    /**
     * �V���Ɏ�ʂ�ݒ肵�A�A�N�^�[��z���ɒǉ�����B
     * ��ʂ̓A�N�^�[���ێ������ʂ𖳎����A�����̎�ʂ�D�悷��B<BR>
     * ���g�Ǝ�ʂ��قȂ�ꍇ�͎q�ɒc��(GgafGroupHead)������ł��̂܂��q�Ɉ����̃A�N�^�[��ǉ����܂��B<BR>
     * ���g�Ǝ�ʂ������ꍇ�́A�P�Ɏq�Ɉ����̃A�N�^�[��ǉ����܂��B<BR>
     * @param prm_kind ���
     * @param prm_pMainActor ��ʂƋ��ɒǉ��������A�N�^�[
     * @return �����A�N�^�[�̒c��(GgafGroupHead)
     */
    GgafGroupHead* appendGroupChild(kind_t prm_kind, GgafMainActor* prm_pMainActor);

    /**
     * �V���Ɏ�ʂ�ݒ肵�A�A�N�^�[��z���ɒǉ�����B .
     * �������A��ʂ̓A�N�^�[���ێ������ʂ��̗p����B<BR>
     * ���g�Ǝ�ʂ��قȂ�ꍇ�͎q�ɒc��(GgafGroupHead)������ł��̂܂��q�Ɉ����̃A�N�^�[��ǉ����܂��B<BR>
     * ���g�Ǝ�ʂ������ꍇ�́A�P�Ɏq�Ɉ����̃A�N�^�[��ǉ����܂��B<BR>
     * @param prm_pMainActor ��ʂƋ��ɒǉ��������A�N�^�[
     * @return �����A�N�^�[�̒c��(GgafGroupHead)
     */
    GgafGroupHead* appendGroupChild(GgafMainActor* prm_pMainActor);

    /**
     * �z���̐����\�Ȓc����T���B
     * @param prm_kind �T�������c���̎��
     * @return �c���A�����͑��݂��Ȃ���� nullptr
     */
    GgafGroupHead* searchChildGroupHead(kind_t prm_kind);

    /**
     * �_�ɉy�� .
     * @return  �Ă΂�ďo�Ă����_
     */
    virtual GgafGod* askGod() override;

    /**
     * �������Ă���c���̎�ʂ��擾���� .
     * ���ʂ̎����Ŏ��R�Ɏg�p���邱�Ƃ�z��B
     * @return
     */
    kind_t lookUpKind();

    virtual ~GgafMainActor();
};

}
#endif /*GGAFCORE_GGAFMAINACTOR_H_*/

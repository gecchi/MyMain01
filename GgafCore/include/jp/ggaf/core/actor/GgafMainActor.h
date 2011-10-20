#ifndef GGAFMAINACTOR_H_
#define GGAFMAINACTOR_H_

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

protected:

public:
    /** [r]���g����������O���[�v�̒c�� */
    GgafGroupHead* _pGroupHead;
    /** [r]���g����������O���[�v�̒c���̊ē� */
    GgafDirector* _pDirector;

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

    /**
     * �q�m�[�h�̃O���[�v�̐擪�m�[�h���擾���� .
     * �q�m�[�h�����݂��Ȃ��ꍇ�̓G���[�B
     * @return  �q�m�[�h�̐擪�m�[�h
     */
    virtual GgafMainActor* getSubFirst() override {
        return (GgafMainActor*)GgafActor::getSubFirst();
    }

    /**
     * ���c���[�m�[�h��A�����X�g����؂藣���A�Ɨ�����B .
     * �؂藣���ꌊ���J���������́A����̃m�[�h�����𖄂߂܂��i�ĘA�����܂��j<BR>
     * ���m�[�h�Ɏq���Ԃ牺�����Ă����ꍇ�A�������؂藣���ꂽ���ƂɂȂ�܂��B<BR>
     * @return  ���m�[�h�̃|�C���^
     */
    virtual GgafMainActor* extract() override;

//    /**
//     * �����������ׂ� .
//     * �t���O�ɂɂ�銈������ɁA�������V�[�����������ł��邩�������ɉ�����B
//     * ����́A�V�[���݂̂�inactive�ɏ�ԂɂȂ����ꍇ�A
//     * �����ɏ�������A�N�^�[�B�̃t���O�͉e�����󂯂���������ꍇ������B
//     * TODO:�����ɂ́A�V�[���̐e�V�[�����S�Ē�������K�v������̂����A���̂悤�ȂԂ����؂�͍s��Ȃ��悤�ɍH�v����B
//     * @return �A�N�^�[���������i���������V�[�����������j
//     */
//    virtual bool isActive() override;

//        if (isActive() && _can_hit_flg) {
//            return true;
//        } else {
//            return false;
//        }
//    }

    /**
     * �V�[���ē�ݒ肷��B .
     */
    virtual void setSceneDirector(GgafDirector* prm_pDirector);

    /**
     * �c����ݒ肷��B<BR>
     */
    virtual void setGroupHead(GgafGroupHead* prm_pGroupHead);

    /**
     * �V�[���ē擾�B .
     * @return �ē�
     */
    virtual GgafDirector* getSceneDirector();

    /**
     * �V�[���c�����擾����B .
     * @return �c��
     */
    virtual GgafGroupHead* getMyGroupHead();

    /**
     * �V���Ɏ�ʂ�ݒ肵�A�A�N�^�[��z���ɒǉ�����B
     * ��ʂ̓A�N�^�[���ێ������ʂ𖳎����A�����̎�ʂ�D�悷��B
     * �z���ɒc��(GgafGroupHead)������ł��̔z���Ɉ����̃A�N�^�[��ǉ����܂��B
     * GgafDirector::addSubGroup(actorkind, GgafMainActor) �̐������Q�Ƃ��ĉ������B
     * @param prm_kind ���
     * @param prm_pMainActor ��ʂƋ��ɒǉ��������A�N�^�[
     * @return ���ݍ��܂�Ă���z���̒c��(GgafGroupHead)
     */
    GgafGroupHead* addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor);

    /**
     * �V���Ɏ�ʂ�ݒ肵�A�A�N�^�[��z���ɒǉ�����B .
     * �������A��ʂ̓A�N�^�[���ێ������ʂ��̗p����B
     * �z���ɒc��(GgafGroupHead)������ł��̔z���Ɉ����̃A�N�^�[��ǉ����܂��B
     * GgafDirector::addSubGroup(actorkind, GgafMainActor) �̐������Q�Ƃ��ĉ������B
     * @param prm_pMainActor ��ʂƋ��ɒǉ��������A�N�^�[
     * @return ���ݍ��܂�Ă���z���̒c��(GgafGroupHead)
     */
    GgafGroupHead* addSubGroup(GgafMainActor* prm_pMainActor);

    /**
     * �z���̐����\�Ȓc����T���B
     * @param prm_kind �T�������c���̎��
     * @return �c���A�����͑��݂��Ȃ���� NULL
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

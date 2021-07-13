#ifndef GGAF_CORE_FORMATION_H_
#define GGAF_CORE_FORMATION_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/MainActor.h"

#define FORMATION_END_DELAY (30*60)

namespace GgafCore {

/**
 * �t�H�[���[�V�����Ǘ��N���X .
 * ������ނ����݂���t�H�[���[�V�����Ǘ��N���X�̃X�[�p�[�N���X�ł��B
 * �ґ��̏������ȕւɂ��邽�߂ɐ݌v�B
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class Formation : public MainActor {

public:
    /** [r]�ґ��v�f�Ƃ��āu�Ǘ�����Ă���v�A�N�^�[�� . */
    int _num_formation_member;
    //���ۂɔz���ɓo�^����Ă���A�N�^�[���Ɠ����Ƃ͌���Ȃ��B
    //appendChild()�ő����A setFormationMember() �ɂ��Z�b�g�AcalledUpMember() ����ŏ㏑���Đݒ�
    //��肽�����Ƃ́AdestroyedFollower() �ŕґ��S�Ŕ�����s�������B
    //�������ɁA�z���ɗ]�T�������čő僁���o�[�� 10 �o�^���Ă����A
    //���ۂɊ������Ɏg�p���郁���o�[���� 8 �ł���A�ƌォ��m�肵�����B
    //���̏ꍇ 8 ���łŕґ��S�łƂ���B
    //���̏ꍇ_num_formation_member �͍ŏ� 10 �ł��邪�AcalledUpMember(8) ���� 8 �ɏ㏑�������B

    /** [r]�j��ɂ����ł����A�N�^�[�� (�����A�N�^�[�� informDestroyedFollower() �ɂ�葝��)*/
    int _num_destory;
    /** [r]�ґ��v�f�̌Ăяo�����icalledUpMember() �������� true ��Ԃ����Ƃ������j*/
    int _num_called_up;

    /** [r]�t�H�[���[�V�����v�����S�ł����ۂɎ��g���������P�\�t���[���B���ʃN���X�ŁAsayonara�̈����ɂȂ�B */
    frame _offset_frames_end;
    /** [r]�S�Ŏ� true (Actor::notifyDestroyedToFormation() ���ݒ�) */
    bool _was_all_destroyed;

    bool _was_all_sayonara;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �q�������Ȃ����Ƃ��ɉ������P�\�t���[��
     * @return
     */
    Formation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * �ґ��\���v�����j�󂳂ꂽ���̏��� .
     * pActor->notifyDestroyedToFormation() ���Ɏ����I�Ɏ��s�����B
     * �ʏ�t���[�����[�N�����҂͖{���\�b�h���g�p���邱�Ƃ͂Ȃ��B
     * @param prm_pActor_destroyed
     */
    void destroyedFollower(Actor* prm_pActor_destroyed);

    /**
     * �ґ��ɏ��������A�N�^�[���j��(��ʊO�ł͂Ȃ�)�ɂ��S�ł����ꍇ�ɃR�[���o�b�N����郁�\�b�h�i�Ƃ���) .
     * �ґ��S�Ŏ��̋�̓I�ȏ����i�ґ��{�[�i�X���Z��A������ʉ����j���������邱�Ƃ�z��B <BR>
     * �܂��A�{�R�[���o�b�N���@�\���邽�߂ɂ́A�ґ��\���A�N�^�[�����g�����ꂽ�ꍇ�ɁA
     * pActor->notifyDestroyedToFormation() ���Ăяo�������K�v�ɂȂ�܂��B
     * Actor::notifyDestroyedToFormation() �̐������Q�Ƃ��ĉ������B <BR>
     * �ґ��S�Ŏ��̏��������ɂȂ��ꍇ�́ApActor->notifyDestroyedToFormation()��ʒm����K�v�͂���܂���B <BR>
     * ���̏ꍇ�́A�{���\�b�h�͋�������Ă����ĉ����� �B <BR>
     * @param prm_pActor_last_destroyed �Ō�ɂ��ꂽ�A�N�^�[
     */
    virtual void onDestroyAll(Actor* prm_pActor_last_destroyed) = 0;

    /**
     * �ґ��ɏ��������A�N�^�[���S�Ă���Ȃ�(sayonara()���Ăяo���ꂽ)�����ꍇ�R�[���o�b�N����郁�\�b�h�i�Ƃ���) .
     */
    virtual void onSayonaraAll() = 0;

    /**
     * �����o�[���c���Ă���Ή�����鏈���������ς� .
     * �p�����ăI�[�o�[���C�h����ꍇ�́A��������
     * Formation::onEnd() ���Ăяo���ĉ������B
     */
    virtual void onEnd() override;

    inline int getMemberNum() const {
        return _num_formation_member;
    }

    virtual ~Formation();
};

}
#endif /*GGAF_CORE_FORMATION_H_*/

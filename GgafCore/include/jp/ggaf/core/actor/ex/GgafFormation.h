#ifndef GGAFCORE_GGAFFORMATION_H_
#define GGAFCORE_GGAFFORMATION_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"

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
class GgafFormation : public GgafMainActor {

public:
    /** [r]�ґ��v�f�Ƃ��ĊǗ�����Ă���A�N�^�[��(addSubLast() callUpMember() �ɂ�葝��) */
    int _num_formation_member;
    /** [r]�j��ɂ����ł����A�N�^�[�� (�����A�N�^�[�� informDestroyedFollower() �ɂ�葝��)*/
    int _num_destory;
    /** [r]�t�H�[���[�V�����v�����S�ł����ۂɎ��g���������P�\�t���[���B���ʃN���X�ŁAsayonara�̈����ɂȂ�B */
    frame _offset_frames_end;
    /** [r]�S�Ŏ� true (GgafActor::notifyDestroyedToFormation() ���ݒ�) */
    bool _was_all_destroyed;

    bool _was_all_sayonara;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �q�������Ȃ����Ƃ��ɉ������P�\�t���[��
     * @return
     */
    GgafFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * �ґ��\���v�����j�󂳂ꂽ���̏��� .
     * pActor->notifyDestroyedToFormation() ���Ɏ����I�Ɏ��s�����B
     * �ʏ�t���[�����[�N�����҂͖{���\�b�h���g�p���邱�Ƃ͂Ȃ��B
     * @param prm_pActor_destroyed
     */
    void destroyedFollower(GgafActor* prm_pActor_destroyed);

    /**
     * �ґ��ɏ��������A�N�^�[���j��(��ʊO�ł͂Ȃ�)�ɂ��S�ł����ꍇ�ɃR�[���o�b�N����郁�\�b�h�i�Ƃ���) .
     * �ґ��S�Ŏ��̋�̓I�ȏ����i�ґ��{�[�i�X���Z��A������ʉ����j���������邱�Ƃ�z��B <BR>
     * �܂��A�{�R�[���o�b�N���@�\���邽�߂ɂ́A�ґ��\���A�N�^�[�����g�����ꂽ�ꍇ�ɁA
     * pActor->notifyDestroyedToFormation() ���Ăяo�������K�v�ɂȂ�܂��B
     * GgafActor::notifyDestroyedToFormation() �̐������Q�Ƃ��ĉ������B <BR>
     * �ґ��S�Ŏ��̏��������ɂȂ��ꍇ�́ApActor->notifyDestroyedToFormation()��ʒm����K�v�͂���܂���B <BR>
     * ���̏ꍇ�́A�{���\�b�h�͋�������Ă����ĉ����� �B <BR>
     * @param prm_pActor_last_destroyed �Ō�ɂ��ꂽ�A�N�^�[
     */
    virtual void onDestroyAll(GgafActor* prm_pActor_last_destroyed) = 0;

    /**
     * �ґ��ɏ��������A�N�^�[���S�Ă���Ȃ�(sayonara()���Ăяo���ꂽ)�����ꍇ�R�[���o�b�N����郁�\�b�h�i�Ƃ���) .
     */
    virtual void onSayonaraAll() = 0;

    /**
     * �����o�[���c���Ă���Ή�����鏈���������ς� .
     * �p�����ăI�[�o�[���C�h����ꍇ�́A��������
     * GgafFormation::onEnd() ���Ăяo���ĉ������B
     */
    virtual void onEnd() override;

    inline int getMemberNum() const {
        return _num_formation_member;
    }

    virtual ~GgafFormation();
};

}
#endif /*GGAFCORE_GGAFFORMATION_H_*/

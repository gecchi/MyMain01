#ifndef GGAF_CORE_ACTOR_H_
#define GGAF_CORE_ACTOR_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Element.hpp"
#include "jp/ggaf/core/util/Status.h"

//#define STAT_DEFAULT_ACTOR_KIND 0

namespace GgafCore {

/**
 * �A�N�^�[�i���ҁj�̊��N���X .
 * �{�v���O�����ł́w�A�N�^�[�x�Ƃ́A��ɃL�����N�^�[��\������B<BR>
 * �e�V�[��(Scene)�ɏ������A���􂷂�C���[�W�B<BR>
 * Element �ɓ����蔻�����������d�g�݂��������N���X�ɂȂ��Ă���B<BR>
 * �{�N���X�͒��ۃN���X�ł��̂܂� new �͂ł��Ȃ��B<BR>
 * �S�ẴA�N�^�[�N���X�́A�{�N���X���p�������Ȃ��Ƃ��ȉ��̏������z�֐�����������K�v������B<BR>
 * <BR>
 * ���P�x�����Ăяo����鏃�����z�֐���<BR>
 * void initialize() �E�E�E�������� <BR>
 * ���ʏ�A���t���[���Ăяo����鏃�����z�֐���<BR>
 * void processBehavior() �E�E�E�t���[�����̐U�镑�������i���W�ړ����j <BR>
 * void processJudgement() �E�E�E�t���[�����̗l�X�Ȕ��菈���i�S�A�N�^�[�U�镑��������̏����j <BR>
 * void processPreDraw() �E�E�E�t���[�����̕`�掖�O���� <BR>
 * void processDraw() �E�E�E�t���[�����̕`��{���� <BR>
 * void processAfterDraw() �E�E�E�t���[�����̕`�掖�㏈�� <BR>
 * void processFinal() �E�E�E�t���[�����̏I�[���� <BR>
 * �����t���[���Ăяo�����킯�ł͂Ȃ��������z�֐���<BR>
 * void onCatchEvent(eventval prm_event_val, void* prm_pSource) �E�E�E���̑��̃C�x���g���̏��� <BR>
 * void onHit(const Checker* prm_pThisHitChecker, const Checker* prm_pOppHitChecker) �E�E�E�Փ˔��胍�W�b�N��true�̏ꍇ�̏��� <BR>
 * <BR>
 * ���e���v���[�g�N���X�� Node �ƁAElement �̐������Q�Ƃ̂��ƁB<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class Actor : public Element<Actor> {

    friend class Caretaker;
    friend class MainActor;
    friend class SceneChief;
    friend class DestructActor;
    friend class Scene;
    friend class Spacetime;
    friend class GarbageBox;

public:
#ifdef MY_DEBUG
    static unsigned int _num_actors;
#endif
    /** [r]�����f�|�W�g��(nullptr�͖�����) */
    ActorDepository* _pDependenceDepository;
    /** [r]�A�N�^�[�Փ˔���L���t���O */
    bool _can_hit_flg;
    /** [r]true:���E�O�ł��q�b�g�`�F�b�N���s��/false:���E�O�̓q�b�g�`�F�b�N���s�Ȃ�Ȃ� */
    bool _enable_out_of_view_hit_flg;
    /** [r/w]���R�X�e�[�^�X */
    Status* _pStatus;

    Checker* _pChecker;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[�̖��O
     */
    Actor(const char* prm_name);

    /**
     * �f�X�g���N�^ .
     * ���c���[�A�N�^�[�̉�����s���܂��B
     */
    virtual ~Actor();

    /**
     * ���A�N�^�[�̏Փ˔���L����ݒ肷��B .
     * @param prm_can_hit_flg  �Փ˔���L��(true:�Փ˔���L��^false:�Փ˔��薳��)
     * @param prm_enable_out_of_view_hit_flg  �Փ˔���L��̏ꍇ�A����O�Փ˔���̗L����ݒ�(true:��ʊO�Փ˔���L��^false:��ʊO�Փ˔��薳��)
     */
    void setHitAble(bool prm_can_hit_flg, bool prm_enable_out_of_view_hit_flg) {
        _can_hit_flg = prm_can_hit_flg;
        _enable_out_of_view_hit_flg = prm_enable_out_of_view_hit_flg;
    }
    /**
     * ���A�N�^�[�̏Փ˔���L����ݒ肷��B .
     * ����O�Փ˔���̗L���͕ω����Ȃ��B
     * @param prm_can_hit_flg  �Փ˔���L��(true:�Փ˔���L��^false:�Փ˔��薳��)
     */
    void setHitAble(bool prm_can_hit_flg) {
        _can_hit_flg = prm_can_hit_flg;
    }

    /**
     * ����O�Փ˔���̗L����ݒ� .
     * �Փ˔���L���͕ω����Ȃ��B
     * @param prm_enable_out_of_view_hit_flg (true:��ʊO�Փ˔���L��^false:��ʊO�Փ˔��薳��)
     */
    void enableOutOfViewHit(bool prm_enable_out_of_view_hit_flg) {
        _enable_out_of_view_hit_flg = prm_enable_out_of_view_hit_flg;
    }
    /**
     * ���c���[�A�N�^�[�̏Փ˔���L����ݒ肷��B .
     * @param prm_can_hit_flg  �Փ˔���L��(true:�Փ˔���L��^false:�Փ˔��薳��)
     * @param prm_enable_out_of_view_hit_flg  �Փ˔���L��̏ꍇ�A����O�Փ˔���̗L����ݒ�(true:��ʊO�Փ˔���L��^false:��ʊO�Փ˔��薳��)
     */
    void setHitAbleTree(bool prm_can_hit_flg, bool prm_enable_out_of_view_hit_flg);
    void setHitAbleTree(bool prm_can_hit_flg);
    /**
     * ���ݏՓ˂ł���󋵂��ǂ������� .
     * ���ӁF�Փ˔\�͂����邩�ǂ����ł͖����B
     * @return	bool true:�Փˉ\�󋵁^false:�Փ˕s�\��
     */
    inline bool canHit() const {
        if (_can_live_flg && _is_active_flg && _can_hit_flg) {
            return true;
        } else {
            return false;
        }
    }


    /**
     * �A�N�^�[�ƏՓ˂������̏��� .
     * _pColliChecker->processHitChkLogic(Checker*) �� true �̏ꍇ�ɌĂяo����邱�ƂɂȂ�܂��B<BR>
     * �Փ˔���̌��ʁA�Փ˂����ꍇ�̏��������ʃN���X�������Ă��������B<BR>
     * @param	prm_pOppHitChecker	�Փ˂��Ă��鑊��̃`�F�b�J�[
     */
    virtual void onHit(const Checker* prm_pThisHitChecker, const Checker* prm_pOppHitChecker) {}

    /**
     * Depository�ɏ������Ă���ꍇ�A�����Ԃ��B
     * �������̏ꍇnullptr
     * @return ����Depository
     */
    ActorDepository* getDependenceDepository() const {
        return _pDependenceDepository;
    }

    /**
     * ����Ȃ炵�܂� .
     * Depository �ɏ������Ă���ꍇ�� inactiveAfter(prm_offset_frames) <BR>
     * Depository �ɏ������Ă��Ȃ��ꍇ�� end(prm_offset_frames) <BR>
     * ���A���s����܂��B
     * �A�N�^�[���V�[�����痣�E���������ꍇ�͂��̃��\�b�h�����s���邱�ƁB
     * @param prm_offset_frames �P�\�t���[��(1�`)
     */
    virtual void sayonara(frame prm_offset_frames = 1);

    /**
     * �I�u�W�F�N�g�����̃N���X�R�����𒲂ׂ�B
     * _obj_class �����o�ϐ��� Obj_xxxx �}�N���萔���ݒ肳��Ă��邱�Ƃ��O��B
     * @param prm_Obj_xxxx ���ׂ�N���X�̃}�N���萔
     * @return
     */
    virtual bool instanceOf(uint64_t prm_Obj_xxxx) const override {
        if ((Obj_SceneBit & prm_Obj_xxxx) == Obj_SceneBit) {
            //�V�[���������r�b�g�������Ă�����
            return false;
        } else {
            return Element<Actor>::instanceOf(prm_Obj_xxxx);
        }
    }

    inline Status* getStatus() const {
        return _pStatus;
    }

//    /**
//     * �A�N�^�[�̃f�t�H���g�̎�ʂ��擾 .
//     * @return �A�N�^�[�̃f�t�H���g�̎��
//     */
//    virtual kind_t getDefaultKind() {
//        return (kind_t)getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND);
//    }

    virtual kind_t getCheckerKind();

    virtual void setCheckerKind(kind_t prm_kind);
//    /**
//     * �A�N�^�[�̃f�t�H���g�̎�ʂ�ݒ� .
//     * @param prm_kind �A�N�^�[�̃f�t�H���g�̎��
//     */
//    virtual void setDefaultKind(kind_t prm_kind);

    virtual Checker* getChecker() {
        if (!_pChecker) {
            _pChecker = createChecker();
        }
        return _pChecker;
    }

    virtual Checker* createChecker(kind_t prm_kind = 0);

    virtual void appendChild(Actor* prm_pActor) override;

    /**
     * �f�o�b�O�p�F�c���[�\����\��<BR>
     */
    virtual void dump();

    /**
     * �f�o�b�O�p�Fdump()����g�p�����<BR>
     */
    virtual void dump(std::string prm_parent);

};

}
#endif /*GGAF_CORE_ACTOR_H_*/

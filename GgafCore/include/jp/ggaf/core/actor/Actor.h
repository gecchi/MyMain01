#ifndef GGAF_CORE_ACTOR_H_
#define GGAF_CORE_ACTOR_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Element.hpp"
#include "jp/ggaf/core/util/Status.h"

#define STAT_DEFAULT_ACTOR_KIND 0

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
 * void onCatchEvent(hashval prm_no, void* prm_pSource) �E�E�E���̑��̃C�x���g���̏��� <BR>
 * bool processHitChkLogic(Actor* prm_pOtherActor) �E�E�E�Փ˔��胍�W�b�N <BR>
 * void onHit(const Actor* prm_pOtherActor) �E�E�E�Փ˔��胍�W�b�N��true�̏ꍇ�̏��� <BR>
 * <BR>
 * ���e���v���[�g�N���X�� Node �ƁAElement �̐������Q�Ƃ̂��ƁB<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class Actor : public Element<Actor> {

    friend class Caretaker;
    friend class MainActor;
    friend class SceneMediator;
    friend class GroupHead;
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
    /** [r]�����t�H�[���[�V����(nullptr�͖�����) */
    Formation* _pFormation;

    /** [r]�A�N�^�[�Փ˔���L���t���O */
    bool _can_hit_flg;
    /** [r]true:���E�O�ł��q�b�g�`�F�b�N���s��/false:���E�O�̓q�b�g�`�F�b�N���s�Ȃ�Ȃ� */
    bool _can_hit_out_of_view;
    /** [r/w]���R�X�e�[�^�X */
    Status* _pStatus;

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
     * @param prm_can_hit_out_of_view_flg  �Փ˔���L��̏ꍇ�A����O�Փ˔���̗L����ݒ�(true:��ʊO�Փ˔���L��^false:��ʊO�Փ˔��薳��)
     */
    void setHitAble(bool prm_can_hit_flg, bool prm_can_hit_out_of_view_flg);
    /**
     * ���A�N�^�[�̏Փ˔���L����ݒ肷��B .
     * ����O�Փ˔���̗L���͕ω����Ȃ��B
     * @param prm_can_hit_flg  �Փ˔���L��(true:�Փ˔���L��^false:�Փ˔��薳��)
     */
    void setHitAble(bool prm_can_hit_flg) {
        _can_hit_flg = prm_can_hit_flg;
    }
    /**
     * ���c���[�A�N�^�[�̏Փ˔���L����ݒ肷��B .
     * @param prm_can_hit_flg  �Փ˔���L��(true:�Փ˔���L��^false:�Փ˔��薳��)
     * @param prm_can_hit_out_of_view_flg  �Փ˔���L��̏ꍇ�A����O�Փ˔���̗L����ݒ�(true:��ʊO�Փ˔���L��^false:��ʊO�Փ˔��薳��)
     */
    void setHitAbleTree(bool prm_can_hit_flg, bool prm_can_hit_out_of_view_flg);
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
     * ���A�N�^�[�Ƒ��A�N�^�[�̂P�΂P�̓����蔻�菈�����s���B
     * @param prm_pOtherActor ���A�N�^�[
     */
    virtual void executeHitChk_MeAnd(Actor* prm_pOtherActor) {
        if (prm_pOtherActor == this) {
            return;
        } else {
            //�q�b�g�ł��镨�ǂ����̔���͎��O�ɂ���ł���悤�ɂ��鎖�B
            if (processHitChkLogic(prm_pOtherActor)) { //���g�̃q�b�g�`�F�b�N
                onHit(prm_pOtherActor); //�����̃q�b�g���̐U�镑��
                prm_pOtherActor->onHit(this); //����̃q�b�g���̐U�镑��
            }
        }
    }

    /**
     * ���A�N�^�[�Ɖ����̃A�N�^�[�ƏՓ˂������ǂ������肷�郍�W�b�N�B .
     * executeHitChk_MeAnd(Actor*) �����s���ꂽ�ꍇ�ɌĂяo����邱�ƂɂȂ�B<BR>
     * ���ʃN���X�œƎ��ɏՓ˔��胍�W�b�N����������B<BR>
     * ���̃��\�b�h�͉����Ăяo����邩�͌��܂��Ă��Ȃ��B�Ăяo���^�C�~���O�����ʃN���X�ˑ��B<BR>
     * �z��Ƃ��ẮAprocessJudgement() ���\�b�h�����������N���X���A���̒��Ŗ{���\�b�h���Ăяo�����̂Ƃ��Ă���B<BR>
     * �������̂悤�Ɏ��������ꍇ�A����A�N�^�[�� processJudgement() �ł�����̃A�N�^�[�Ƃ̏Փ˔�����s�����ƂɂȂ�΁A<BR>
     * �Փ˔��菈���d�����邱�ƂɂȂ�B�ǁ[������悢���l���邱�ƁB<BR>
     * @param	prm_pOtherActor	����A�N�^�[
     * @retval	true	�Փ˂��Ă����Ԃ���
     * @retval	false	�Փ˂��Ă��Ȃ���Ԃ���
     */
    virtual bool processHitChkLogic(Actor* prm_pOtherActor) {
        return false;
    }

    /**
     * �A�N�^�[�ƏՓ˂������̏��� .
     * processHitChkLogic(Actor*) �� true �̏ꍇ�ɌĂяo����邱�ƂɂȂ�܂��B<BR>
     * �Փ˔���̌��ʁA�Փ˂����ꍇ�̏��������ʃN���X�������Ă��������B<BR>
     * @param	prm_pOtherActor	�Փ˂��Ă��鑊��̃A�N�^�[�i�P�j
     */
    virtual void onHit(const Actor* prm_pOtherActor) {}

    /**
     * Depository�ɏ������Ă���ꍇ�A�����Ԃ��B
     * �������̏ꍇnullptr
     * @return ����Depository
     */
    ActorDepository* getDependenceDepository() const {
        return _pDependenceDepository;
    }

    /**
     * ���g���ґ��S�Ŕ���ɗL���Ȕj��̂�����ŏ��ł��������A�����̃t�H�[���[�V�����ɒʒm���郁�\�b�h .
     * ���g���t�H�[���[�V�����ɏ������Ă���(_pFormation != nullptr)�ꍇ�A
     * �t�H�[���[�V�����̕ґ��S�Ŕ�����s�����߂ɁA���g���ґ��S�łɗL���ȏ��ŁA�܂�
     * ��ʊO�A���ŁA�ł͖����A���@�ɔj�󂳂ꂽ�ꍇ�A�{���\�b�h�����s���āA�Ǘ��t�H�[���[�V�����ɒʒm���ĉ������B<BR>
     * �ʒm���s�����Ƃɂ��A�Ǘ�����Ă��� Formation �I�u�W�F�N�g����A
     * �ґ��S�Ŏ��ɁA
     *
     * Formation::onDestroyAll()
     *
     * �̃R�[���o�b�N���s���܂��B
     * �ґ��{�[�i�X�A�A�C�e���o�����̏����� GgafDx::FormationActor::onDestroyAll() ��
     * �I�[�o�[���C�h�ōs���ĉ������B
     * <code><pre>
     * ���၄
     * void SampleActor::onHit(const Actor* prm_pOtherActor) {
     *    //���g�̑ϋv�̓`�F�b�N
     *    if (MyStgUtil::calcSampleStatus(_pStatus, lookUpKind(), pOther->_pStatus, pOther->lookUpKind()) <= 0) {
     *        //Hit�̑���̃`�F�b�N
     *        if (pOther->lookUpKind() & KIND_MY) {
     *            //Hit�̑���͎��@�֘A�i���@�A���@���j�b�g�A���@���˒e)
     *            notifyDestroyedToFormation(); //�ґ��S�Ŕ���ɗL���Ȕj���ʒm����
     *        }
     *    }
     * }
     *
     * </pre></code>
     * ���g���t�H�[���[�V�����ɏ������Ă��Ȃ�(_pFormation == nullptr)�ꍇ�A�{���\�b�h�͉����N����܂���B
     */
    virtual void notifyDestroyedToFormation();

    /**
     * ���g���̏����̃t�H�[���[�V������Ԃ� .
     * @return �t�H�[���[�V�����B�����́A�������ĂȂ��ꍇ��nullptr
     */
    inline virtual Formation* getFormation() const {
        return _pFormation;
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

    /**
     * �A�N�^�[�̃f�t�H���g�̎�ʂ��擾 .
     * @return �A�N�^�[�̃f�t�H���g�̎��
     */
    inline kind_t getDefaultKind() const {
        return (kind_t)getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND);
    }

    /**
     * �A�N�^�[�̃f�t�H���g�̎�ʂ�ݒ� .
     * @param prm_kind �A�N�^�[�̃f�t�H���g�̎��
     */
    inline void setDefaultKind(kind_t prm_kind) const {
        return getStatus()->set(STAT_DEFAULT_ACTOR_KIND, prm_kind);
    }

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

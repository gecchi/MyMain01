#ifndef GGAFCORE_GGAFACTOR_H_
#define GGAFCORE_GGAFACTOR_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafElement.hpp"

#include "jp/ggaf/core/util/GgafStatus.h"
#define STAT_DEFAULT_ACTOR_KIND 0

namespace GgafCore {

/**
 * �A�N�^�[�i���ҁj�̊��N���X .
 * �{�v���O�����ł́w�A�N�^�[�x�Ƃ́A��ɃL�����N�^�[��\������B<BR>
 * �e�V�[��(GgafScene)�ɏ������A���􂷂�C���[�W�B<BR>
 * GgafElement �ɓ����蔻�����������d�g�݂��������N���X�ɂȂ��Ă���B<BR>
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
 * bool processHitChkLogic(GgafActor* prm_pOtherActor) �E�E�E�Փ˔��胍�W�b�N <BR>
 * void onHit(const GgafActor* prm_pOtherActor) �E�E�E�Փ˔��胍�W�b�N��true�̏ꍇ�̏��� <BR>
 * <BR>
 * ���e���v���[�g�N���X�� GgafNode �ƁAGgafElement �̐������Q�Ƃ̂��ƁB<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class GgafActor : public GgafElement<GgafActor> {

    friend class GgafGod;
    friend class GgafMainActor;
    friend class GgafSceneDirector;
    friend class GgafGroupHead;
    friend class GgafDestructActor;
    friend class GgafScene;
    friend class GgafUniverse;
    friend class GgafGarbageBox;

private:
    /** ���݂̏����V�[�� */
    GgafScene* _pScene_platform;

    /**
     * �����V�[����ݒ肷��B .
     */
    void setPlatformScene(GgafScene* prm_pScene_platform);

public:
    /** [r]�����f�|�W�g��(nullptr�͖�����) */
    GgafActorDepository* _pDependenceDepository;
    /** [r]�����t�H�[���[�V����(nullptr�͖�����) */
    GgafFormation* _pFormation;

    /** [r]�A�N�^�[�Փ˔���L���t���O */
    bool _can_hit_flg;
    /** [r]true:���E�O�ł��q�b�g�`�F�b�N���s��/false:���E�O�̓q�b�g�`�F�b�N���s�Ȃ�Ȃ� */
    bool _can_hit_out_of_view;
    /** [r/w]���R�X�e�[�^�X */
    GgafStatus* _pStatus;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[�̖��O
     * @param prm_pStat �A�N�^�[�̃X�e�[�^�X�inullptr�̏ꍇ�͎������������j
     */
    GgafActor(const char* prm_name, GgafStatus* prm_pStat);

    /**
     * �f�X�g���N�^ .
     * ���c���[�A�N�^�[�̉�����s���܂��B
     */
    virtual ~GgafActor();

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
    void setHitAble(bool prm_can_hit_flg);
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
     * �������Ă���V�[�����擾�B .
     * @return	GgafScene*	�������Ă���V�[��
     */
    virtual GgafScene* getPlatformScene();

    /**
     * ���A�N�^�[�Ƒ��A�N�^�[�̂P�΂P�̓����蔻�菈�����s���B
     * @param prm_pOtherActor ���A�N�^�[
     */
    virtual void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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
     * executeHitChk_MeAnd(GgafActor*) �����s���ꂽ�ꍇ�ɌĂяo����邱�ƂɂȂ�B<BR>
     * ���ʃN���X�œƎ��ɏՓ˔��胍�W�b�N����������B<BR>
     * ���̃��\�b�h�͉����Ăяo����邩�͌��܂��Ă��Ȃ��B�Ăяo���^�C�~���O�����ʃN���X�ˑ��B<BR>
     * �z��Ƃ��ẮAprocessJudgement() ���\�b�h�����������N���X���A���̒��Ŗ{���\�b�h���Ăяo�����̂Ƃ��Ă���B<BR>
     * �������̂悤�Ɏ��������ꍇ�A����A�N�^�[�� processJudgement() �ł�����̃A�N�^�[�Ƃ̏Փ˔�����s�����ƂɂȂ�΁A<BR>
     * �Փ˔��菈���d�����邱�ƂɂȂ�B�ǁ[������悢���l���邱�ƁB<BR>
     * @param	prm_pOtherActor	����A�N�^�[
     * @retval	true	�Փ˂��Ă����Ԃ���
     * @retval	false	�Փ˂��Ă��Ȃ���Ԃ���
     */
    virtual bool processHitChkLogic(GgafActor* prm_pOtherActor) {
        return false;
    }

    /**
     * �A�N�^�[�ƏՓ˂������̏��� .
     * processHitChkLogic(GgafActor*) �� true �̏ꍇ�ɌĂяo����邱�ƂɂȂ�܂��B<BR>
     * �Փ˔���̌��ʁA�Փ˂����ꍇ�̏��������ʃN���X�������Ă��������B<BR>
     * @param	prm_pOtherActor	�Փ˂��Ă��鑊��̃A�N�^�[�i�P�j
     */
    virtual void onHit(const GgafActor* prm_pOtherActor) {}

    /**
     * Depository�ɏ������Ă���ꍇ�A�����Ԃ��B
     * �������̏ꍇnullptr
     * @return ����Depository
     */
    GgafActorDepository* getDependenceDepository() const {
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
     * �ґ��{�[�i�X�A�A�C�e���o�����̏����� GgafDxFormationActor::onDestroyAll() ��
     * �I�[�o�[���C�h�ōs���ĉ������B
     * <code><pre>
     * ���၄
     * void SampleActor::onHit(const GgafActor* prm_pOtherActor) {
     *    //���g�̑ϋv�̓`�F�b�N
     *    if (MyStgUtil::calcSampleStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
     *        //Hit�̑���̃`�F�b�N
     *        if (pOther->getKind() & KIND_MY) {
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
    inline virtual GgafFormation* getFormation() const {
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
     * �c���[�\������؂藣�� .
     * @return
     */
    virtual GgafActor* extract() override;

    /**
     * �I�u�W�F�N�g�����̃N���X�R�����𒲂ׂ�B
     * _obj_class �����o�ϐ��� Obj_xxxx �}�N���萔���ݒ肳��Ă��邱�Ƃ��O��B
     * @param prm_Obj_xxxx ���ׂ�N���X�̃}�N���萔
     * @return
     */
    virtual bool instanceOf(classkind prm_Obj_xxxx) const override {
        if ((Obj_SceneBit & prm_Obj_xxxx) == Obj_SceneBit) {
            //�V�[���������r�b�g�������Ă�����
            return false;
        } else {
            return GgafElement<GgafActor>::instanceOf(prm_Obj_xxxx);
        }
    }

    inline GgafStatus* getStatus() const {
        return _pStatus;
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
#endif /*GGAFCORE_GGAFACTOR_H_*/

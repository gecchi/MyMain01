#ifndef GGAFLIB_LINEAROCTREEFORACTOR_H_
#define GGAFLIB_LINEAROCTREEFORACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/util/GgafLinearOctree.h"

namespace GgafLib {

#define MAX_COLLISIONSTACK_ACTOR_NUM (2000)
/**
 * GgafActor��v�f�Ƃ������蔻��@�\��ǉ��������`�����ؔz��N���X .
 * ���A�O���[�v �� ���B�O���[�v��2�O���[�v�Ԃ̓����蔻����s��
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class LinearOctreeForActor : public GgafCore::GgafLinearOctree {

    uint32_t _num_space_minus_one;

public:
    /**
     * �����蔻��A�N�^�[��ێ�����X�^�b�N .
     * �����̎������l���ĂȂ��댯�ȃX�^�b�N
     */
    class CollisionStack {
    public:
        /** [r]��̋�ԂɃX�^�b�N����A�N�^�[�̔z��B�g�p����̂�[0]�`[MAX_COLLISIONSTACK_ACTOR_NUM-1]�B+1�́A�Ō�̗v�f��ԕ��ɂ��Ă��� */
        GgafCore::GgafActor* _apActor[MAX_COLLISIONSTACK_ACTOR_NUM+1]; //�Ō�̗v�f(+1)�͔ԕ�
        /** [r]�J�[�\���|�C���^(����PUSH�o����v�f���w���Ă���)  */
        GgafCore::GgafActor** _papCur;
        /** [r]��ɃX�^�b�N�̐擪�v�f���w���Ă��� */
        GgafCore::GgafActor** _papFirst;
        /** [r]��ɃX�^�b�N�̍Ō�̗v�f�̎����w���Ă��� */
        GgafCore::GgafActor** _papBanpei;
    public:
        /**
         * �R���X�g���N�^
         * @return
         */
        CollisionStack() {
            _papFirst = &_apActor[0];
            _papBanpei = &_apActor[MAX_COLLISIONSTACK_ACTOR_NUM];
            _papCur = _papFirst;
        }
        /**
         * �X�^�b�N�ɐς� .
         * @param prm_pActor �ςރA�N�^�[
         */
        inline void push(GgafCore::GgafActor* prm_pActor) {
            if (_papCur == _papBanpei) {
                _TRACE_("���x���� LinearOctreeForActor::push("<<prm_pActor<<") �X�^�b�N���g���؂�܂����B�������܂��B��ӏ��ɓ����蔻�肪��߂��ł��B");
                return;
            }
            (*_papCur) = prm_pActor;
            ++_papCur;
        }

        /**
         * �X�^�b�N������o�� .
         * @return ���o���ꂽ�A�N�^�[
         */
        inline GgafCore::GgafActor* pop() {
            if (_papCur == _papFirst) {
                return nullptr;
            } else {
                --_papCur;
                return (*_papCur);
            }
        }

        inline bool isExist() {
            return _papCur == _papFirst ? false : true;
        }

        /**
         * �����̃X�^�b�N����S�Ď��o���A�o������莩�g�̃X�^�b�N�ɐς� .
         * @param prm_pCollisionStack
         */
        inline void pop_push(CollisionStack* prm_pCollisionStack) {
            if (_papCur == _papBanpei) {
                _TRACE_("���x���� LinearOctreeForActor::pop_push("<<prm_pCollisionStack<<") �X�^�b�N���g���؂��Ă܂��B�������܂��B��ӏ��ɓ����蔻�肪��߂��ł��B");
                prm_pCollisionStack->clear();
                return;
            }
            while ((*_papCur) = prm_pCollisionStack->pop()) { //����Bpop�o���Ȃ���� nullptr�B I know "=" , not "=="
                 ++_papCur;
                 if (_papCur == _papBanpei) {
                    _TRACE_("���x���� LinearOctreeForActor::pop_push("<<prm_pCollisionStack<<") �X�^�b�N���g���؂�܂����B�������܂��B��ӏ��ɓ����蔻�肪��߂��ł��B");
                    prm_pCollisionStack->clear();
                    break;
                }
            }
        }
        /**
         * �ς񂾃X�^�b�N���Ȃ��������ɂ���B .
         */
        inline void clear() {
            _papCur = _papFirst;
        }
        ~CollisionStack() {
            clear();
        }
    };

    /** [r]�S��Ԃ̓����蔻�莞�A���݂̋�Ԃɏ�������A�N�^�[���A�O���[�v�̃X�^�b�N */
    CollisionStack _stackCurrentOctantActor_GroupA;
    /** [r]�S��Ԃ̓����蔻�莞�A���݂̋�Ԃɏ�������A�N�^�[���B�O���[�v�̃X�^�b�N */
    CollisionStack _stackCurrentOctantActor_GroupB;
    /** [r]�����Ԃ̓����蔻�莞�A��������e��Ԃɏ��������S�A�N�^�[���A�O���[�v�̃X�^�b�N */
    CollisionStack _stackParentOctantActor_GroupA;
    /** [r]�����Ԃ̓����蔻�莞�A��������e��Ԃɏ��������S�A�N�^�[���B�O���[�v�̃X�^�b�N */
    CollisionStack _stackParentOctantActor_GroupB;

    /** [r]���񓖂��蔻����s���A�N�^�[���A */
    actorkind _kind_groupA;
    /** [r]���񓖂��蔻����s���A�N�^�[���B */
    actorkind _kind_groupB;

public:
    /**
     * �R���X�g���N�^
     * @param prm_level �쐬���锪���؋�ԃ��x��
     */
    explicit LinearOctreeForActor(int prm_level);

    /**
     * �����؏����́u�A�N�^�[���A�O���[�v �� �A�N�^�[���B�O���[�v�v���s��  .
     * �A�v�����͖{���\�b�h���ĂԂ����ł悢�B<BR>
     * ������ executeAllHitChk �� processJudgement() �ŌĂԕK�v����B<BR>
     * @param prm_groupA �A�N�^�[���A�O���[�v
     * @param prm_groupB �A�N�^�[���B�O���[�v
     */
    void executeAllHitChk(actorkind prm_groupA, actorkind prm_groupB);

    /**
     * �����̋�Ԃ̓����蔻����s��  .
     * executeAllHitChk ����g�p�����B
     * @param prm_index ���`�����ؔz��̔z��v�f�ԍ�
     */
    void executeHitChk(uint32_t prm_index);

    /**
     * �A�N�^�[���A�O���[�v�̃X�^�b�N�ƁA�A�N�^�[���B�O���[�v�̃X�^�b�N�̑�����̓����蔻����s��  .
     * executeHitChk ����g�p�����B
     * @param prm_pStackA �A�N�^�[���A�O���[�v�̃X�^�b�N
     * @param prm_pStackB �A�N�^�[���B�O���[�v�̃X�^�b�N
     */
    void executeHitChk_RoundRobin(CollisionStack* prm_pStackA, CollisionStack* prm_pStackB);

    virtual ~LinearOctreeForActor();
};


}
#endif /*GGAFLIB_LINEAROCTREEFORACTOR_H_*/


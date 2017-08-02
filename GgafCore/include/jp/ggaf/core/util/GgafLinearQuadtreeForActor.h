#ifndef GGAFCORE_GGAFLINEARQUADTREEFORACTOR_H_
#define GGAFCORE_GGAFLINEARQUADTREEFORACTOR_H_
#include "GgafCommonHeader.h"
#include "GgafLinearQuadtree.h"

namespace GgafCore {

#define MAX_COLLISIONSTACK_ACTOR_NUM (2000)
/**
 * GgafActor��v�f�Ƃ������蔻��@�\��ǉ��������`�����ؔz��N���X .
 * ���A�O���[�v �� ���B�O���[�v��2�O���[�v�Ԃ̓����蔻����s��
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class GgafLinearQuadtreeForActor : public GgafLinearQuadtree {

    uint32_t _num_space_minus_one;

public:
    /**
     * �����蔻��A�N�^�[��ێ�����X�^�b�N .
     * �����̎������l���ĂȂ��댯�ȃX�^�b�N
     */
    class CollisionStack {
    public:
        /** [r]��̋�ԂɃX�^�b�N����A�N�^�[�̔z��B�g�p����̂�[0]�`[MAX_COLLISIONSTACK_ACTOR_NUM-1]�B+1�́A�Ō�̗v�f��ԕ��ɂ��Ă��� */
        GgafCore::GgafObject* _apObject[MAX_COLLISIONSTACK_ACTOR_NUM+1]; //�Ō�̗v�f(+1)�͔ԕ�
        /** [r]�J�[�\���|�C���^(����PUSH�o����v�f���w���Ă���)  */
        GgafCore::GgafObject** _papCur;
        /** [r]��ɃX�^�b�N�̐擪�v�f���w���Ă��� */
        GgafCore::GgafObject** _papFirst;
        /** [r]��ɃX�^�b�N�̍Ō�̗v�f�̎����w���Ă��� */
        GgafCore::GgafObject** _papBanpei;
    public:
        /**
         * �R���X�g���N�^
         * @return
         */
        CollisionStack() {
            _papFirst = &_apObject[0];
            _papBanpei = &_apObject[MAX_COLLISIONSTACK_ACTOR_NUM];
            _papCur = _papFirst;
        }
        /**
         * �X�^�b�N�ɐς� .
         * @param prm_pActor �ςރA�N�^�[
         */
        inline void push(GgafCore::GgafObject* prm_pObject) {
            if (_papCur == _papBanpei) {
                _TRACE_("���x���� GgafLinearQuadtreeForActor::push("<<prm_pObject<<") �X�^�b�N���g���؂�܂����B�������܂��B��ӏ��ɓ����蔻�肪��߂��ł��B");
                return;
            }
            (*_papCur) = prm_pObject;
            ++_papCur;
        }

        /**
         * �X�^�b�N������o�� .
         * @return ���o���ꂽ�A�N�^�[
         */
        inline GgafCore::GgafObject* pop() {
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
         * �����̃X�^�b�N����S�Ď��o��(pop)�A�o������莩�g�̃X�^�b�N�ɐς�(push) .
         * �����̃X�^�b�N�́A�K����ɂȂ�B
         * @param prm_pCollisionStack
         */
        inline void popush(CollisionStack* prm_pCollisionStack) {
            if (_papCur == _papBanpei) {
                _TRACE_("���x���� GgafLinearQuadtreeForActor::popush("<<prm_pCollisionStack<<") �X�^�b�N���g���؂��Ă܂��B�������܂��B��ӏ��ɓ����蔻�肪��߂��ł��B");
                prm_pCollisionStack->clear();
                return;
            }
            while ((*_papCur) = prm_pCollisionStack->pop()) { //����Bpop�o���Ȃ���� nullptr�B I know "=" , not "=="
                 ++_papCur;
                 if (_papCur == _papBanpei) {
                    _TRACE_("���x���� GgafLinearQuadtreeForActor::popush("<<prm_pCollisionStack<<") �X�^�b�N���g���؂�܂����B�������܂��B��ӏ��ɓ����蔻�肪��߂��ł��B");
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
    CollisionStack _stackGroupA_Current;
    /** [r]�S��Ԃ̓����蔻�莞�A���݂̋�Ԃɏ�������A�N�^�[���B�O���[�v�̃X�^�b�N */
    CollisionStack _stackGroupB_Current;
    /** [r]�����Ԃ̓����蔻�莞�A��������e��Ԃɏ��������S�A�N�^�[���A�O���[�v�̃X�^�b�N */
    CollisionStack _stackGroupA;
    /** [r]�����Ԃ̓����蔻�莞�A��������e��Ԃɏ��������S�A�N�^�[���B�O���[�v�̃X�^�b�N */
    CollisionStack _stackGroupB;

    /** [r]���񓖂��蔻����s���A�N�^�[���A */
    actorkind _kind_groupA;
    /** [r]���񓖂��蔻����s���A�N�^�[���B */
    actorkind _kind_groupB;

public:
    /**
     * �R���X�g���N�^
     * @param prm_level �쐬���锪���؋�ԃ��x��
     */
    explicit GgafLinearQuadtreeForActor(int prm_level);

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

    virtual ~GgafLinearQuadtreeForActor();
};


}
#endif /*GGAFCORE_GGAFLINEARQUADTREEFORACTOR_H_*/


#ifndef LINEAROCTREEFORACTOR_H_
#define LINEAROCTREEFORACTOR_H_
namespace GgafLib {

/**
 * GgafActor��v�f�Ƃ������蔻��@�\��ǉ��������`�����ؔz��N���X .
 * ���A�O���[�v �� ���B�O���[�v��2�O���[�v�Ԃ̓����蔻����s��
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class LinearOctreeForActor : public GgafCore::GgafLinearOctree {

    UINT32 _num_space_minus_one;

public:
    /**
     * �����蔻��A�N�^�[��ێ�����X�^�b�N .
     * �����̎������l���ĂȂ��댯�ȃX�^�b�N
     */
    class CollisionStack {
    public:
        /** [r]��̋�ԂɃX�^�b�N����A�N�^�[�̔z�� */
        GgafCore::GgafActor* _apActor[3000]; //�P��Ԃ� 3000 ���L�������W�܂�Ȃ����낤�Ƃ������ՂŐ�͂��Ȍ��ς���
        /** [r]�J�[�\���|�C���^  */
        UINT32 _p;

        /**
         * �R���X�g���N�^
         * @return
         */
        CollisionStack() {
            _p = 0;
        }
        /**
         * �X�^�b�N�ɐς� .
         * @param prm_pActor �ςރA�N�^�[
         */
        inline void push(GgafCore::GgafActor* prm_pActor) {
            if (_p > 3000-1) {
                _TRACE_("LinearOctreeForActor::push("<<prm_pActor->getName()<<") �X�^�b�N���g���؂�܂����B�������܂��B��ӏ��ɓ����蔻�肪��߂��ł��B");
                return;
            }
            _apActor[_p] = prm_pActor;
            _p++;
        }
        /**
         * �X�^�b�N������o�� .
         * @return ���o���ꂽ�A�N�^�[
         */
        inline GgafCore::GgafActor* pop() {
            if (_p == 0) {
                return nullptr;
            } else {
                _p--;
                return (_apActor[_p]);
            }
        }
        /**
         * �ς񂾃X�^�b�N���Ȃ��������ɂ���B .
         */
        inline void clear() {
            _p = 0;
        }
        ~CollisionStack() {
            clear();
        }
        void dump() {
            TEXT5("CollisionStack.dump=");
            for (UINT32 i = 0; i < _p; i++) {
                TEXT5((_apActor[i]->getName())<<"->");
            }
            TEXT5("END");
        }
    };

    /** [r]�S��Ԃ̓����蔻�莞�A���݂̋�Ԃɏ�������A�N�^�[���A�O���[�v�̃X�^�b�N */
    CollisionStack _stackCurrentSpaceActor_GroupA;
    /** [r]�S��Ԃ̓����蔻�莞�A���݂̋�Ԃɏ�������A�N�^�[���B�O���[�v�̃X�^�b�N */
    CollisionStack _stackCurrentSpaceActor_GroupB;

    /** [r]�����Ԃ̓����蔻�莞�A��������e��Ԃɏ��������S�A�N�^�[���A�O���[�v�̃X�^�b�N */
    CollisionStack _stackParentSpaceActor_GroupA;
    /** [r]�����Ԃ̓����蔻�莞�A��������e��Ԃɏ��������S�A�N�^�[���B�O���[�v�̃X�^�b�N */
    CollisionStack _stackParentSpaceActor_GroupB;

    /** [r]���񓖂��蔻����s���A�N�^�[���A */
    actorkind _kind_groupA;
    /** [r]���񓖂��蔻����s���A�N�^�[���B */
    actorkind _kind_groupB;


    /**
     * �R���X�g���N�^
     * @param prm_level �쐬���锪���؋�ԃ��x��
     */
    LinearOctreeForActor(int prm_level);

    /**
     * �����؏����́u�A�N�^�[���A�O���[�v �� �A�N�^�[���B�O���[�v�v���s��  .
     * �A�v�����͖{���\�b�h���ĂԂ����ł悢�B
     * @param prm_groupA �A�N�^�[���A�O���[�v
     * @param prm_groupB �A�N�^�[���B�O���[�v
     */
    void executeAllHitChk(actorkind prm_groupA, actorkind prm_groupB);

    /**
     * �����̋�Ԃ̓����蔻����s��  .
     * executeAllHitChk ����g�p�����B
     * @param prm_index ���`�����ؔz��̔z��v�f�ԍ�
     */
    void executeHitChk(UINT32 prm_index);

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
#endif /*LINEAROCTREEFORACTOR_H_*/


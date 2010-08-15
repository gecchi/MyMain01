#ifndef LINEAROCTREEFORACTOR_H_
#define LINEAROCTREEFORACTOR_H_
namespace GgafDx9LibStg {

/**
 * GgafActor��v�f�Ƃ������蔻��@�\��ǉ��������`�����ؔz��N���X .
 * ���A�O���[�v �� ���B�O���[�v��2�O���[�v�Ԃ̓����蔻����s��
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class LinearOctreeForActor : public GgafCore::GgafLinearOctree {

public:

    /**
     * �����蔻��A�N�^�[��ێ�����X�^�b�N .
     * �����̎������l���ĂȂ��댯�ȃX�^�b�N
     */
    class CollisionStack {
    public:
        /** ��̋�Ԃ� 3000 ���L�������W�܂�Ȃ����낤�Ƃ������ՂŐ�͂��Ȍ��ς��� */
        GgafCore::GgafActor* _apActor[3000];
        /** �J�[�\���|�C���^  */
        DWORD _p;
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
        void push(GgafCore::GgafActor* prm_pActor) {
            _apActor[_p] = prm_pActor;
            _p++;

            if (_p > 3000) {
#ifdef MY_DEBUG
                _TRACE_("�X�^�b�N���g���؂�܂����A���̂܂܂ł̓�������j�󂵈ُ�I������ł��傤�B_p-- ����Ƃ��܂��B");
#endif
                _p--;
            }

        }
        /**
         * �X�^�b�N������o�� .
         * @return ���o���ꂽ�A�N�^�[
         */
        GgafCore::GgafActor* pop() {
            if (_p == 0) {
                return NULL;
            } else {
                _p--;
                return _apActor[_p];
            }
        }
        /**
         * �ς񂾃X�^�b�N���Ȃ��������ɂ���B .
         */
        void clear() {
            _p = 0;
        }
        ~CollisionStack() {
            clear();
        }
        void dump() {
            TEXT5("CollisionStack.dump=");
            for (DWORD i = 0; i < _p; i++) {
                TEXT5((_apActor[i]->getName())<<"->");
            }
            TEXT5("END");
        }
    };

    /** �S��Ԃ̓����蔻�莞�A���݂̋�Ԃɏ�������A�N�^�[���A�O���[�v�̃X�^�b�N */
    CollisionStack _stackCurrentSpaceActor_GroupA;
    /** �S��Ԃ̓����蔻�莞�A���݂̋�Ԃɏ�������A�N�^�[���B�O���[�v�̃X�^�b�N */
    CollisionStack _stackCurrentSpaceActor_GroupB;

    /** �����Ԃ̓����蔻�莞�A��������e��Ԃɏ��������S�A�N�^�[���A�O���[�v�̃X�^�b�N */
    CollisionStack _stackParentSpaceActor_GroupA;
    /** �����Ԃ̓����蔻�莞�A��������e��Ԃɏ��������S�A�N�^�[���B�O���[�v�̃X�^�b�N */
    CollisionStack _stackParentSpaceActor_GroupB;

    /** ���񓖂��蔻����s���A�N�^�[���A */
    actorkind _kind_groupA;
    /** ���񓖂��蔻����s���A�N�^�[���B */
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
    void executeHitChk(DWORD prm_index);

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


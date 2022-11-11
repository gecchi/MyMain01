#ifndef GGAF_CORE_LINEARTREEROUNDER_H_
#define GGAF_CORE_LINEARTREEROUNDER_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/core/util/LinearOctree.h"
#include "jp/ggaf/core/util/TreeSpace.hpp"

namespace GgafCore {

#define MAX_COLLISIONSTACK_ACTOR_NUM (2000)
/**
 * T��v�f�Ƃ������蔻��@�\��ǉ��������`N���؂܂��͎l���؂̊e�v�f�ɏ������s�� .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
template<class T, uint32_t DIMENSION>
class LinearTreeRounder : public Object {

    uint32_t _num_space;

public:
    /**
     * �����蔻��A�N�^�[��ێ�����X�^�b�N .
     * �����̎������l���ĂȂ��댯�ȃX�^�b�N
     */
    class TStack {
    public:
        /** [r]��̋�ԂɃX�^�b�N����A�N�^�[�̔z��B�g�p����̂�[0]�`[MAX_COLLISIONSTACK_ACTOR_NUM-1]�B+1�́A�Ō�̗v�f��ԕ��ɂ��Ă��� */
        T* _apT[MAX_COLLISIONSTACK_ACTOR_NUM+1]; //�Ō�̗v�f(+1)�͔ԕ�
        /** [r]�J�[�\���|�C���^(����PUSH�o����v�f���w���Ă���)  */
        T** _papCur;
        /** [r]��ɃX�^�b�N�̐擪�v�f���w���Ă��� */
        T** _papFirst;
        /** [r]��ɃX�^�b�N�̍Ō�̗v�f�̎����w���Ă��� */
        T** _papBanpei;
    public:
        /**
         * �R���X�g���N�^
         * @return
         */
        TStack() {
            _papFirst = &_apT[0];
            _papBanpei = &_apT[MAX_COLLISIONSTACK_ACTOR_NUM];
            _papCur = _papFirst;
        }
        /**
         * �X�^�b�N�ɐς� .
         * @param prm_pT �ςރA�N�^�[
         */
        inline void push(T* prm_pObject) {
            if (_papCur == _papBanpei) {
                _TRACE_("�y�x���z LinearTreeRounder::push("<<prm_pObject<<") �X�^�b�N���g���؂�܂����B�������܂��B��ӏ��ɓ����蔻�肪��߂��ł��B");
                return;
            }
            (*_papCur) = prm_pObject;
            ++_papCur;
        }

        /**
         * �X�^�b�N������o�� .
         * @return ���o���ꂽ�A�N�^�[
         */
        inline T* pop() {
            if (_papCur == _papFirst) {
                return nullptr;
            } else {
                --_papCur;
                return (*_papCur);
            }
        }

        /**
         * �X�^�b�N�ɃA�N�^�[�����݂��邩 .
         * @return
         */
        inline bool isExist() {
            return _papCur == _papFirst ? false : true;
        }

        /**
         * �����̃X�^�b�N����S�Ď��o��(pop)�A�o������莩�g�̃X�^�b�N�ɐς�(push) .
         * �����̃X�^�b�N�́A�K����ɂȂ�B
         * @param prm_pTStack
         */
        inline void popush(TStack* prm_pTStack) {
            if (_papCur == _papBanpei) {
                _TRACE_("�y�x���z LinearTreeRounder::popush("<<prm_pTStack<<") �X�^�b�N���g���؂��Ă܂��B�������܂��B��ӏ��ɓ����蔻�肪��߂��ł��B");
                prm_pTStack->clear();
                return;
            }
            while ((*_papCur) = prm_pTStack->pop()) { //����Bpop�o���Ȃ���� nullptr�B I know "=" , not "=="
                 ++_papCur;
                 if (_papCur == _papBanpei) {
                    _TRACE_("�y�x���z LinearTreeRounder::popush("<<prm_pTStack<<") �X�^�b�N���g���؂�܂����B�������܂��B��ӏ��ɓ����蔻�肪��߂��ł��B");
                    prm_pTStack->clear();
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
        ~TStack() {
            clear();
        }
    };

    TreeSpace<DIMENSION>* _paTargetSpace;
    /** [r]�S��Ԃ̓����蔻�莞�A���݂̋�Ԃɏ�������A�N�^�[���A�O���[�v�̃X�^�b�N */
    TStack _stackCurrent_GroupA;
    /** [r]�S��Ԃ̓����蔻�莞�A���݂̋�Ԃɏ�������A�N�^�[���B�O���[�v�̃X�^�b�N */
    TStack _stackCurrent_GroupB;
    /** [r]�����Ԃ̓����蔻�莞�A��������e��Ԃɏ��������S�A�N�^�[���A�O���[�v�̃X�^�b�N */
    TStack _stackParent_GroupA;
    /** [r]�����Ԃ̓����蔻�莞�A��������e��Ԃɏ��������S�A�N�^�[���B�O���[�v�̃X�^�b�N */
    TStack _stackParent_GroupB;

    /** [r]���񓖂��蔻����s���A�N�^�[���A */
    kind_t _kind_groupA;
    /** [r]���񓖂��蔻����s���A�N�^�[���B */
    kind_t _kind_groupB;
    /** [r]���s����T�̃����o�֐� */
    void (T::*_pFunc)(T*);

public:
    /**
     * �R���X�g���N�^
     * @param prm_level �쐬����N���؋�ԃ��x��
     */
    LinearTreeRounder(TreeSpace<DIMENSION>* prm_paTargetSpace, int prm_num_space, void (T::*prm_pFunc)(T*)) {
        _paTargetSpace = prm_paTargetSpace;
        _num_space = prm_num_space;
        _pFunc = prm_pFunc;
        _kind_groupA = 0;
        _kind_groupB = 0;
    }

    /**
     * N���؏����́u�A�N�^�[���A�O���[�v �� �A�N�^�[���B�O���[�v�v���s��  .
     * �A�v�����͖{���\�b�h���ĂԂ����ł悢�B<BR>
     * ������ executeAllHitChk �� processJudgement() �ŌĂԕK�v����B<BR>
     * @param prm_kind_groupA �A�N�^�[���A�O���[�v
     * @param prm_kind_groupB �A�N�^�[���B�O���[�v
     */
    void executeAll(kind_t prm_kind_groupA, kind_t prm_kind_groupB) {
        _kind_groupA = prm_kind_groupA;
        _kind_groupB = prm_kind_groupB;
        kind_t k_bit = _paTargetSpace[0]._kind_bit_field;
        if ( (k_bit & prm_kind_groupA) && (k_bit & prm_kind_groupB) ) {
            //�ł�N���؂����闷�֍s���Ă�����Ⴂ
            execute(0); //�����Ă��܂�
            //�͂����A��Ȃ����B
            _stackParent_GroupA.clear();
            _stackParent_GroupB.clear();
        }
    }

    /**
     * �����̋�Ԃ̓����蔻����s��  .
     * executeAllHitChk ����g�p�����B
     * @param prm_index ���`N���ؔz��̔z��v�f�ԍ�
     */
    void execute(uint32_t prm_index) {
        TreeSpace<DIMENSION>* pOctant_this_level = &(_paTargetSpace[prm_index]);
        TreeElem<DIMENSION>* pElem = pOctant_this_level->_pElem_first;
        const kind_t kind_groupA = _kind_groupA;
        const kind_t kind_groupB = _kind_groupB;
        const kind_t kind_groupAB = kind_groupA | kind_groupB;
        if (pElem) {
            TreeElem<DIMENSION>* pElem_last = pOctant_this_level->_pElem_last;
            while (true) {
                kind_t kind = pElem->_kind;
                T* pObject = (T*)(pElem->_pObject);
                if (kind & kind_groupA) {
                    _stackCurrent_GroupA.push(pObject);
                } else if (kind & kind_groupB) {
                    _stackCurrent_GroupB.push(pObject);
                }
                if (pElem == pElem_last) {
                    break;
                }
                pElem = pElem->_pNext;
            }

            if (_stackCurrent_GroupA.isExist()) {
                if (_stackCurrent_GroupB.isExist()) {
                    //���݂̋�Ԃ̃O���[�vA�ƃO���[�vB������
                    executeRoundRobin(&_stackCurrent_GroupA, &_stackCurrent_GroupB);
                    if (_stackParent_GroupB.isExist()) {
                        //���݂̋�Ԃ̃O���[�vA�Ɛe��ԏ����̃O���[�vB������
                        executeRoundRobin(&_stackCurrent_GroupA, &_stackParent_GroupB);
                    }
                    if (_stackParent_GroupA.isExist()) {
                        //�e��ԏ����̃O���[�vA�ƌ��݂̋�Ԃ̃O���[�vB������
                        executeRoundRobin(&_stackParent_GroupA, &_stackCurrent_GroupB);
                    }
                } else {
                    if (_stackParent_GroupB.isExist()) {
                        executeRoundRobin(&_stackCurrent_GroupA, &_stackParent_GroupB);
                    }
                }
            } else {
                if (_stackCurrent_GroupB.isExist()) {
                    if (_stackParent_GroupA.isExist()) {
                        executeRoundRobin(&_stackParent_GroupA, &_stackCurrent_GroupB);
                    }
                }
            }

        }
        const uint32_t lower_level_index = (prm_index<<DIMENSION) + 1; //_papOctant[prm_index] ��Ԃ̎q��Ԃ̃��[�g�������ʒu0�Ԃ̔z��v�f�ԍ�
        if ( lower_level_index >= _num_space) {
            //�v�f���I�[�o�[�A�܂胊�[�t
            _stackCurrent_GroupA.clear();
            _stackCurrent_GroupB.clear();
            return; //�e��Ԃ֖߂�
        } else {

            //������B���A���̑O�Ɍ���ԃA�N�^�[��e��ԃA�N�^�[�̃X�^�b�N�֒ǉ��B
            //����������Ԃ��猩���ꍇ�̐e��ԃA�N�^�[�݌v������Ă����Ă��B
            //(�����Ɍ���ԃX�^�b�N���J��)
            T** temp_stackParentGroupA = _stackParent_GroupA._papCur; //�X�^�b�N�|�C���^�ۑ�(��������̃��Z�b�g�Ɏg�p)
            T** temp_stackParentGroupB = _stackParent_GroupB._papCur; //�X�^�b�N�|�C���^�ۑ�(��������̃��Z�b�g�Ɏg�p)
            _stackParent_GroupA.popush(&_stackCurrent_GroupA); //Current �� Parent �ɒǉ�(����)�B������Current�̓N���A�����B
            _stackParent_GroupB.popush(&_stackCurrent_GroupB); //Current �� Parent �ɒǉ�(����)�B������Current�̓N���A�����B
            bool isExistGroupA = _stackParent_GroupA.isExist(); //Current �{ Parent �Ɏ��A�A�N�^�[�����݂��邩�ǂ���
            bool isExistGroupB = _stackParent_GroupB.isExist(); //Current �{ Parent �Ɏ��B�A�N�^�[�����݂��邩�ǂ���

            //�q�b�g�`�F�b�N���s���ɁA�q���(�W��)�֐���ɍs�����`�B
            //���̃��x���̋�ԂɎ��A��B���o�^����Ă���ΐ���B
            //���́A���̃��x���̋�ԂɎ��A������A���X�g�b�N�Ɏ��B������ΐ���B
            //���́A���̃��x���̋�ԂɎ��B������A���X�g�b�N�Ɏ��A������ΐ���B
            //����ȊO�͐���Ȃ�
            TreeSpace<DIMENSION>* pOctant_lower_level = &(_paTargetSpace[lower_level_index]);
            kind_t kind_bit_field_lower_level = pOctant_lower_level->_kind_bit_field;
            if (isExistGroupA) {
                if (isExistGroupB) {
                    //���{�e��Ԃ� ���A ���� ���� ���B ����
                    for (int i = 0; i < (1<<DIMENSION); i++) {
                        //���̃��x���̋�ԂɁA���A���A���B���A��������Ȃ�ΐ���
                        kind_bit_field_lower_level = pOctant_lower_level->_kind_bit_field;
                        if (kind_bit_field_lower_level & kind_groupAB)
                        {
                            execute(lower_level_index+i);
                        }
                        ++pOctant_lower_level;
                    }
                } else {
                    //���{�e��Ԃ� ���A �̂ݑ���
                    for (int i = 0; i < (1<<DIMENSION); i++) {
                        //���̃��x���̋�ԂɁA���B ����������Ȃ�ΐ���
                        kind_bit_field_lower_level = pOctant_lower_level->_kind_bit_field;
                        if (kind_bit_field_lower_level & kind_groupB) {
                            execute(lower_level_index+i);
                        }
                        ++pOctant_lower_level;
                    }
                }
            } else {
                if (isExistGroupB) {
                    //���{�e��Ԃ� ���B �̂ݑ���
                    for (int i = 0; i < (1<<DIMENSION); i++) {
                        //���̃��x���̋�ԂɁA���A ����������Ȃ�ΐ���
                        kind_bit_field_lower_level = pOctant_lower_level->_kind_bit_field;
                        if (kind_bit_field_lower_level & kind_groupA) {
                            execute(lower_level_index+i);
                        }
                        ++pOctant_lower_level;
                    }
                } else {
                    //���{�e��Ԃ� ���A ���B �����݂��Ȃ� �i�z����Ԃ�  ���A�{���B �����݁j
                    for (int i = 0; i < (1<<DIMENSION); i++) {
                        //���̃��x���̋�ԂɁA���A�{���B ����������Ȃ�ΐ���
                        kind_bit_field_lower_level = pOctant_lower_level->_kind_bit_field;
                        if (kind_bit_field_lower_level & kind_groupA) {
                            if (kind_bit_field_lower_level & kind_groupB) {
                                execute(lower_level_index+i);
                            }
                        }
                        ++pOctant_lower_level;
                    }

                }
            }
            //���A��Ȃ���
            //�X�^�b�N�̉���ipush�������A���ɖ߂��j
            _stackParent_GroupA._papCur = temp_stackParentGroupA;
            _stackParent_GroupB._papCur = temp_stackParentGroupB;
            return; //�e��Ԃ֖߂�
        }
    }
    /**
     * �A�N�^�[���A�O���[�v�̃X�^�b�N�ƁA�A�N�^�[���B�O���[�v�̃X�^�b�N�̑�����̓����蔻����s��  .
     * executeHitChk ����g�p�����B
     * @param prm_pStackA �A�N�^�[���A�O���[�v�̃X�^�b�N
     * @param prm_pStackB �A�N�^�[���B�O���[�v�̃X�^�b�N
     */
    inline void executeRoundRobin(TStack* prm_pStackA, TStack* prm_pStackB) {
        //LinearTreeRounder�ł́A�v�f�̎w��(Object*)�C���X�^���X�� T���O��
        void (T::*pFunc)(T*) = _pFunc;
        T** papStackT_A_Cur = prm_pStackA->_papCur;
        T** papStackT_B_Cur = prm_pStackB->_papCur;
        T** papStackT_A = prm_pStackA->_papFirst;
        while (papStackT_A != papStackT_A_Cur) {
            T** papStackT_B = prm_pStackB->_papFirst;
            while (papStackT_B != papStackT_B_Cur) {
                ((*papStackT_A)->*pFunc)(*papStackT_B);
                ++papStackT_B;
            }
            ++papStackT_A;
        }
    }

    virtual ~LinearTreeRounder() {
    }
};

}
#endif /*GGAF_CORE_LINEARTREEROUNDER_H_*/


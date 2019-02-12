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
                _TRACE_("���x���� LinearTreeRounder::push("<<prm_pObject<<") �X�^�b�N���g���؂�܂����B�������܂��B��ӏ��ɓ����蔻�肪��߂��ł��B");
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
                _TRACE_("���x���� LinearTreeRounder::popush("<<prm_pTStack<<") �X�^�b�N���g���؂��Ă܂��B�������܂��B��ӏ��ɓ����蔻�肪��߂��ł��B");
                prm_pTStack->clear();
                return;
            }
            while ((*_papCur) = prm_pTStack->pop()) { //����Bpop�o���Ȃ���� nullptr�B I know "=" , not "=="
                 ++_papCur;
                 if (_papCur == _papBanpei) {
                    _TRACE_("���x���� LinearTreeRounder::popush("<<prm_pTStack<<") �X�^�b�N���g���؂�܂����B�������܂��B��ӏ��ɓ����蔻�肪��߂��ł��B");
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
    TStack _stackGroupA_Current;
    /** [r]�S��Ԃ̓����蔻�莞�A���݂̋�Ԃɏ�������A�N�^�[���B�O���[�v�̃X�^�b�N */
    TStack _stackGroupB_Current;
    /** [r]�����Ԃ̓����蔻�莞�A��������e��Ԃɏ��������S�A�N�^�[���A�O���[�v�̃X�^�b�N */
    TStack _stackGroupA;
    /** [r]�����Ԃ̓����蔻�莞�A��������e��Ԃɏ��������S�A�N�^�[���B�O���[�v�̃X�^�b�N */
    TStack _stackGroupB;

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
        if ( (_paTargetSpace[0]._kind_bit_field & prm_kind_groupA) && (_paTargetSpace[0]._kind_bit_field & prm_kind_groupB) ) {
            //�ł�N���؂����闷�֍s���Ă�����Ⴂ
            execute(0); //�����Ă��܂�
            //�͂����A��Ȃ����B
            _stackGroupA.clear();
            _stackGroupB.clear();
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
        if (pElem) {
            TreeElem<DIMENSION>* pElem_last = pOctant_this_level->_pElem_last;
            while (true) {
                if (pElem->_kind & kind_groupA) {
                    _stackGroupA_Current.push((T*)(pElem->_pObject));
                }
                if (pElem->_kind & kind_groupB) {
                    _stackGroupB_Current.push((T*)(pElem->_pObject));
                }
                if (pElem == pElem_last) {
                    break;
                }
                pElem = pElem->_pNext;
            }
            //���݂̋�Ԃ̃O���[�vA�ƃO���[�vB������
            executeRoundRobin(&_stackGroupA_Current, &_stackGroupB_Current);
            //���݂̋�Ԃ̃O���[�vA�Ɛe��ԏ����̃O���[�vB������
            executeRoundRobin(&_stackGroupA_Current, &_stackGroupB );
            //�e��ԏ����̃O���[�vA�ƌ��݂̋�Ԃ̃O���[�vB������
            executeRoundRobin(&_stackGroupA , &_stackGroupB_Current);
        }
        const uint32_t lower_level_index = (prm_index<<DIMENSION) + 1; //_papOctant[prm_index] ��Ԃ̎q��Ԃ̃��[�g�������ʒu0�Ԃ̔z��v�f�ԍ�
        if ( lower_level_index >= _num_space) {
            //�v�f���I�[�o�[�A�܂胊�[�t
            _stackGroupA_Current.clear();
            _stackGroupB_Current.clear();
            return; //�e��Ԃ֖߂�
        } else {

            //������B���A���̑O�Ɍ���ԃA�N�^�[��e��ԃA�N�^�[�̃X�^�b�N�֒ǉ��B
            //����������Ԃ��猩���ꍇ�̐e��ԃA�N�^�[�݌v������Ă����Ă��B
            //(�����Ɍ���ԃX�^�b�N���J��)
            T** temp_stackGroupA = _stackGroupA._papCur; //�X�^�b�N�|�C���^�ۑ�(��������̃��Z�b�g�Ɏg�p)
            T** temp_stackGroupB = _stackGroupB._papCur; //�X�^�b�N�|�C���^�ۑ�(��������̃��Z�b�g�Ɏg�p)
            _stackGroupA.popush(&_stackGroupA_Current); //Current �� Parent �ɒǉ��B������Current�̓N���A�����B
            _stackGroupB.popush(&_stackGroupB_Current); //Current �� Parent �ɒǉ��B������Current�̓N���A�����B
            bool isExistGroupA = _stackGroupA.isExist();
            bool isExistGroupB = _stackGroupB.isExist();

            //�q�b�g�`�F�b�N���s���ɁA�q���(�W��)�֐���ɍs�����`�B
            //���̃��x���̋�ԂɎ��A��B���o�^����Ă���ΐ���B
            //���́A���̃��x���̋�ԂɎ��A������A���X�g�b�N�Ɏ��B������ΐ���B
            //���́A���̃��x���̋�ԂɎ��B������A���X�g�b�N�Ɏ��A������ΐ���B
            //����ȊO�͐���Ȃ�
            TreeSpace<DIMENSION>* pOctant_lower_level = &(_paTargetSpace[lower_level_index]);
            kind_t kind_bit_field_lower_level = pOctant_lower_level->_kind_bit_field;
            if (kind_bit_field_lower_level & kind_groupA) {
                if (isExistGroupB || (kind_bit_field_lower_level & kind_groupB)) {
                    execute(lower_level_index);
                }
            } else if (kind_bit_field_lower_level & kind_groupB) {
                if (isExistGroupA) {
                    execute(lower_level_index);
                }
            }

            for (int i = 1; i < (1<<DIMENSION); i++) {
                kind_bit_field_lower_level = (++pOctant_lower_level)->_kind_bit_field;
                if (kind_bit_field_lower_level & kind_groupA) {
                    if (isExistGroupB || (kind_bit_field_lower_level & kind_groupB)) {
                        execute(lower_level_index+i);
                    }
                } else if (kind_bit_field_lower_level & kind_groupB) {
                    if (isExistGroupA) {
                        execute(lower_level_index+i);
                    }
                }
            }

            //���A��Ȃ���
            //�X�^�b�N�̉���ipush�������A���ɖ߂��j
            _stackGroupA._papCur = temp_stackGroupA;
            _stackGroupB._papCur = temp_stackGroupB;
            return; //�e��Ԃ֖߂�
        }
    }
    /**
     * �A�N�^�[���A�O���[�v�̃X�^�b�N�ƁA�A�N�^�[���B�O���[�v�̃X�^�b�N�̑�����̓����蔻����s��  .
     * executeHitChk ����g�p�����B
     * @param prm_pStackA �A�N�^�[���A�O���[�v�̃X�^�b�N
     * @param prm_pStackB �A�N�^�[���B�O���[�v�̃X�^�b�N
     */
    void executeRoundRobin(TStack* prm_pStackA, TStack* prm_pStackB) {
        //LinearTreeRounder�ł́A�v�f�̎w��(Object*)�C���X�^���X�� T���O��
        if (prm_pStackA->isExist() && prm_pStackB->isExist()) {
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
    }

    virtual ~LinearTreeRounder() {
    }
};

}
#endif /*GGAF_CORE_LINEARTREEROUNDER_H_*/


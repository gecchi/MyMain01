#include "jp/ggaf/core/util/GgafLinearOctreeForActor.h"

#include "jp/ggaf/core/util/GgafLinearOctree.h"
#include "jp/ggaf/core/util/GgafLinearOctreeOctant.h"
#include "jp/ggaf/core/util/GgafLinearOctreeElem.h"
#include "jp/ggaf/core/actor/GgafActor.h"

using namespace GgafCore;

GgafLinearOctreeForActor::GgafLinearOctreeForActor(GgafLinearOctree* prm_pTargetLinearOctree, void (GgafActor::*prm_pFunc)(GgafActor*)) : GgafObject() {
    _pTargetLinearOctree = prm_pTargetLinearOctree;
    _paTargetLinearOctant = _pTargetLinearOctree->_paLinearOctant;
    _num_space_minus_one = _pTargetLinearOctree->_num_space-1;
    _pFunc = prm_pFunc;
    _kind_groupA = 0;
    _kind_groupB = 0;
}

void GgafLinearOctreeForActor::executeAll(actorkind prm_groupA, actorkind prm_groupB) {
    _kind_groupA = prm_groupA;
    _kind_groupB = prm_groupB;
    if ( (_paTargetLinearOctant[0]._kindinfobit & prm_groupA) && (_paTargetLinearOctant[0]._kindinfobit & prm_groupB) ) {
        //�ł͔����؂����闷�֍s���Ă�����Ⴂ
        execute(0); //�����Ă��܂�
        //�͂����A��Ȃ����B
        _stackGroupA.clear();
        _stackGroupB.clear();
    }
}

void GgafLinearOctreeForActor::execute(uint32_t prm_index) {
    GgafLinearOctreeOctant* pOctant_this_level = &(_paTargetLinearOctant[prm_index]);
    GgafLinearOctreeElem* pElem = pOctant_this_level->_pElem_first;
    const uint32_t kind_groupA = _kind_groupA;
    const uint32_t kind_groupB = _kind_groupB;
    if (pElem) {
        GgafLinearOctreeElem* pElem_last = pOctant_this_level->_pElem_last;
        while (true) {
            if (pElem->_kindbit & kind_groupA) {
                _stackGroupA_Current.push((GgafActor*)(pElem->_pObject));
            }
            if (pElem->_kindbit & kind_groupB) {
                _stackGroupB_Current.push((GgafActor*)(pElem->_pObject));
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

    const uint32_t lower_level_index = prm_index*8 + 1; //_papOctant[prm_index] ��Ԃ̎q��Ԃ̃��[�g�������ʒu0�Ԃ̔z��v�f�ԍ�
    if ( lower_level_index > _num_space_minus_one) {
        //�v�f���I�[�o�[�A�܂胊�[�t
        _stackGroupA_Current.clear();
        _stackGroupB_Current.clear();
        return; //�e��Ԃ֖߂�
    } else {

        //������B���A���̑O�Ɍ���ԃA�N�^�[��e��ԃA�N�^�[�̃X�^�b�N�֒ǉ��B
        //����������Ԃ��猩���ꍇ�̐e��ԃA�N�^�[�݌v������Ă����Ă��B
        //(�����Ɍ���ԃX�^�b�N���J��)
        GgafActor** temp_stackGroupA = _stackGroupA._papCur; //�X�^�b�N�|�C���^�ۑ�(��������̃��Z�b�g�Ɏg�p)
        GgafActor** temp_stackGroupB = _stackGroupB._papCur; //�X�^�b�N�|�C���^�ۑ�(��������̃��Z�b�g�Ɏg�p)
        _stackGroupA.popush(&_stackGroupA_Current); //Current �� Parent �ɒǉ��B������Current�̓N���A�����B
        _stackGroupB.popush(&_stackGroupB_Current); //Current �� Parent �ɒǉ��B������Current�̓N���A�����B
        bool isExistGroupA = _stackGroupA.isExist();
        bool isExistGroupB = _stackGroupB.isExist();

        //�q�b�g�`�F�b�N���s���ɁA�q���(�W��)�֐���ɍs�����`�B
        //���̃��x���̋�ԂɎ��A��B���o�^����Ă���ΐ���B
        //���́A���̃��x���̋�ԂɎ��A������A���X�g�b�N�Ɏ��B������ΐ���B
        //���́A���̃��x���̋�ԂɎ��B������A���X�g�b�N�Ɏ��A������ΐ���B
        //����ȊO�͐���Ȃ�
        GgafLinearOctreeOctant* pOctant_lower_level = &(_paTargetLinearOctant[lower_level_index]);
        uint32_t kindinfobit_lower_level = pOctant_lower_level->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index);
            }
        }

        kindinfobit_lower_level = (++pOctant_lower_level)->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index+1);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index+1);
            }
        }

        kindinfobit_lower_level = (++pOctant_lower_level)->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index+2);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index+2);
            }
        }

        kindinfobit_lower_level = (++pOctant_lower_level)->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index+3);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index+3);
            }
        }

        kindinfobit_lower_level = (++pOctant_lower_level)->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index+4);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index+4);
            }
        }

        kindinfobit_lower_level = (++pOctant_lower_level)->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index+5);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index+5);
            }
        }

        kindinfobit_lower_level = (++pOctant_lower_level)->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index+6);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index+6);
            }
        }

        kindinfobit_lower_level = (++pOctant_lower_level)->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index+7);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index+7);
            }
        }

//        //���A��Ȃ���
//        //�X�^�b�N�̉���ipush�������A���ɖ߂��j
        _stackGroupA._papCur = temp_stackGroupA;
        _stackGroupB._papCur = temp_stackGroupB;
        return; //�e��Ԃ֖߂�
    }
}

void GgafLinearOctreeForActor::executeRoundRobin(ActorStack* prm_pStackA, ActorStack* prm_pStackB) {
    //GgafLinearOctreeForActor�ł́A�v�f�̎w��(GgafObject*)�C���X�^���X�� GgafActor���O��
    if (prm_pStackA->isExist() && prm_pStackB->isExist()) {
        void (GgafActor::*pFunc)(GgafActor*) = _pFunc;
        GgafActor** papStackActor_A_Cur = prm_pStackA->_papCur;
        GgafActor** papStackActor_B_Cur = prm_pStackB->_papCur;
        GgafActor** papStackActor_A = prm_pStackA->_papFirst;
        while (papStackActor_A != papStackActor_A_Cur) {
            GgafActor** papStackActor_B = prm_pStackB->_papFirst;
            while (papStackActor_B != papStackActor_B_Cur) {
//                ((GgafActor*)(*papStackActor_A))->executeHitChk_MeAnd((GgafActor*)(*papStackActor_B));
                ((*papStackActor_A)->*pFunc)(*papStackActor_B);
                ++papStackActor_B;
            }
            ++papStackActor_A;
        }
    }
}

GgafLinearOctreeForActor::~GgafLinearOctreeForActor() {
}


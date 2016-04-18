#include "jp/ggaf/lib/util/LinearOctreeForActor.h"

#include "jp/ggaf/core/actor/GgafActor.h"
#include "jp/ggaf/core/util/GgafLinearOctreeOctant.h"
#include "jp/ggaf/lib/util/LinearOctreeActorElem.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

LinearOctreeForActor::LinearOctreeForActor(int prm_level) : GgafLinearOctree(prm_level) {
    _num_space_minus_one = _num_space-1;
    _kind_groupA = 0;
    _kind_groupB = 0;
}

void LinearOctreeForActor::executeAllHitChk(actorkind prm_groupA, actorkind prm_groupB) {
    _kind_groupA = prm_groupA;
    _kind_groupB = prm_groupB;
    if ( (_paOctant[0]._kindinfobit & _kind_groupA) && (_paOctant[0]._kindinfobit & _kind_groupB) ) {
        //�ł͔����؂����闷�֍s���Ă�����Ⴂ
        executeHitChk(0); //�����Ă��܂�
        //�͂����A��Ȃ����B
        _stackParentOctantActor_GroupA.clear();
        _stackParentOctantActor_GroupB.clear();
    }
}

void LinearOctreeForActor::executeHitChk(uint32_t prm_index) {
    GgafLinearOctreeOctant* pOctant_this_level = &(_paOctant[prm_index]);
    LinearOctreeActorElem* pElem = ((LinearOctreeActorElem*)(pOctant_this_level->_pElem_first));
    const uint32_t kind_groupA = _kind_groupA;
    const uint32_t kind_groupB = _kind_groupB;
    if (pElem) {
        GgafLinearOctreeElem* pElem_last = pOctant_this_level->_pElem_last;
        while (true) {
            if (pElem->_kindbit & kind_groupA) {
                _stackCurrentOctantActor_GroupA.push(pElem->_pActor);
            }
            if (pElem->_kindbit & kind_groupB) {
                _stackCurrentOctantActor_GroupB.push(pElem->_pActor);
            }
            if (pElem == pElem_last) {
                break;
            }
            pElem = (LinearOctreeActorElem*)(pElem->_pNext);
        }
        //���݂̋�Ԃ̃O���[�vA�ƃO���[�vB������
        executeHitChk_RoundRobin(&_stackCurrentOctantActor_GroupA, &_stackCurrentOctantActor_GroupB);
        //���݂̋�Ԃ̃O���[�vA�Ɛe��ԏ����̃O���[�vB������
        executeHitChk_RoundRobin(&_stackCurrentOctantActor_GroupA, &_stackParentOctantActor_GroupB );
        //�e��ԏ����̃O���[�vA�ƌ��݂̋�Ԃ̃O���[�vB������
        executeHitChk_RoundRobin(&_stackParentOctantActor_GroupA , &_stackCurrentOctantActor_GroupB);
    }

    const uint32_t next_level_index = prm_index*8 + 1; //_papOctant[prm_index] ��Ԃ̎q��Ԃ̃��[�g�������ʒu0�Ԃ̔z��v�f�ԍ�
    if ( next_level_index > _num_space_minus_one) {
        //�v�f���I�[�o�[�A�܂胊�[�t
        _stackCurrentOctantActor_GroupA.clear();
        _stackCurrentOctantActor_GroupB.clear();
        return; //�e��Ԃ֖߂�
    } else {

//        bool isExist_ParentGroupA = _stackParentOctantActor_GroupA.isExist();
//        bool isExist_ParentGroupB = _stackParentOctantActor_GroupB.isExist();

        //������B���A���̑O�Ɍ���ԃA�N�^�[��e��ԃA�N�^�[�̃X�^�b�N�֒ǉ��B
        //����������Ԃ��猩���ꍇ�̐e��ԃA�N�^�[�݌v������Ă����Ă��B
        //(����ԃX�^�b�N���J��)
        GgafCore::GgafActor** stackParentOctantActor_GroupA_papCur = _stackParentOctantActor_GroupA._papCur; //�X�^�b�N�|�C���^�ۑ�
        GgafCore::GgafActor** stackParentOctantActor_GroupB_papCur = _stackParentOctantActor_GroupB._papCur; //�X�^�b�N�|�C���^�ۑ�
        _stackParentOctantActor_GroupA.pop_push(&_stackCurrentOctantActor_GroupA); //_stackCurrentOctantActor_GroupA���A�N���A�����B
        _stackParentOctantActor_GroupB.pop_push(&_stackCurrentOctantActor_GroupB); //_stackCurrentOctantActor_GroupB���A�N���A�����B
//        //�q��Ԃւ����邪�ǂ�
        GgafLinearOctreeOctant* pOctant = &(_paOctant[next_level_index]);
        const uint32_t next_level_index_end = next_level_index+8;
        for(uint32_t i = next_level_index; i < next_level_index_end; i++) {
            if ((pOctant->_kindinfobit & _kind_groupA) || (pOctant->_kindinfobit & _kind_groupB) ) {
                executeHitChk(i);
            }
            ++pOctant;
        }
// �������Ɍ��Ȃ������B
//        GgafLinearOctreeOctant* pOctant_next_level = &(_paOctant[next_level_index]);
//        uint32_t octant_kindinfobit_next_level = pOctant_next_level->_kindinfobit;
        //���̃��x���̋�ԂɎ��A��B���o�^����Ă���ΐ���B
        //���́A���̃��x���̋�ԂɎ��A������A���e�X�g�b�N�Ɏ��B������ΐ���B
        //���́A���̃��x���̋�ԂɎ��B������A���e�X�g�b�N�Ɏ��A������ΐ���B
        //����ȊO�͐���Ȃ�
        //if (( (octant_kindinfobit_next_level & kind_groupA) && (octant_kindinfobit_next_level & kind_groupB) ) ||
        //    ( (octant_kindinfobit_next_level & kind_groupA) && (isExist_ParentGroupB)                        ) ||
        //    (                        (isExist_ParentGroupA) && (octant_kindinfobit_next_level & kind_groupB) )
        //) {
        //    executeHitChk(next_level_index);
        //}
        //�������ɏ���������
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index);
//            }
//        }
//
//        octant_kindinfobit_next_level = (++pOctant_next_level)->_kindinfobit;
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index+1);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index+1);
//            }
//        }
//
//        octant_kindinfobit_next_level = (++pOctant_next_level)->_kindinfobit;
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index+2);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index+2);
//            }
//        }
//
//        octant_kindinfobit_next_level = (++pOctant_next_level)->_kindinfobit;
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index+3);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index+3);
//            }
//        }
//
//        octant_kindinfobit_next_level = (++pOctant_next_level)->_kindinfobit;
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index+4);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index+4);
//            }
//        }
//
//        octant_kindinfobit_next_level = (++pOctant_next_level)->_kindinfobit;
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index+5);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index+5);
//            }
//        }
//
//        octant_kindinfobit_next_level = (++pOctant_next_level)->_kindinfobit;
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index+6);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index+6);
//            }
//        }
//
//        octant_kindinfobit_next_level = (++pOctant_next_level)->_kindinfobit;
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index+7);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index+7);
//            }
//        }

        //���A��Ȃ���
        //�X�^�b�N�̉���ipush�������A���ɖ߂��j
        _stackParentOctantActor_GroupA._papCur = stackParentOctantActor_GroupA_papCur;
        _stackParentOctantActor_GroupB._papCur = stackParentOctantActor_GroupB_papCur;
        return; //�e��Ԃ֖߂�
    }
}

void LinearOctreeForActor::executeHitChk_RoundRobin(CollisionStack* prm_pStackA, CollisionStack* prm_pStackB) {
    //�ǂ��炩������ΏI��
    GgafActor** papStackActor_A_Cur = prm_pStackA->_papCur;
    GgafActor** papStackActor_B_Cur = prm_pStackB->_papCur;
    GgafActor** papStackActor_A = prm_pStackA->_papFirst;
    while (papStackActor_A != papStackActor_A_Cur) {
        GgafActor** papStackActor_B = prm_pStackB->_papFirst;
        while (papStackActor_B != papStackActor_B_Cur) {
            (*papStackActor_A)->executeHitChk_MeAnd(*papStackActor_B);
            ++papStackActor_B;
        }
        ++papStackActor_A;
    }

}

LinearOctreeForActor::~LinearOctreeForActor() {
}


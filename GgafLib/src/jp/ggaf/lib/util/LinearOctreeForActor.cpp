#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


LinearOctreeForActor::LinearOctreeForActor(int prm_level) : GgafLinearOctree(prm_level) {
}

void LinearOctreeForActor::executeAllHitChk(actorkind prm_groupA, actorkind prm_groupB) {
    _kind_groupA = prm_groupA;
    _kind_groupB = prm_groupB;
    TRACE5("_kind_groupA="<<_kind_groupA);
    TRACE5("_kind_groupB="<<_kind_groupB);
    if (((_paSpace[0]._kindinfobit & _kind_groupA) > 0) && ((_paSpace[0]._kindinfobit & _kind_groupB) > 0)) {
        //�ł͔����؂����闷�֍s���Ă�����Ⴂ
        executeHitChk(0); //�����Ă��܂�
        //�͂����A��Ȃ����B
        _stackParentSpaceActor_GroupA.clear();
        _stackParentSpaceActor_GroupB.clear();
    }
}

void LinearOctreeForActor::executeHitChk(UINT32 prm_index) {
    LinearOctreeActorElem* pElem = ((LinearOctreeActorElem*)(_paSpace[prm_index]._pElemFirst));
    if (pElem) {
        GgafActor* pActor_ElemValue = pElem->_pActor;
        while(true) {
            if ((pElem->_kindbit & _kind_groupA) > 0) {
                _stackCurrentSpaceActor_GroupA.push(pActor_ElemValue);
            }
            if ((pElem->_kindbit & _kind_groupB) > 0) {
                _stackCurrentSpaceActor_GroupB.push(pActor_ElemValue);
            }
            if (pElem == _paSpace[prm_index]._pElemLast) {
                break;
            }
            pElem = (LinearOctreeActorElem*)(pElem -> _pNext);
            pActor_ElemValue = pElem->_pActor;
        }
        //���݂̋�Ԃ̃O���[�vA�ƃO���[�vB������
        executeHitChk_RoundRobin(&_stackCurrentSpaceActor_GroupA, &_stackCurrentSpaceActor_GroupB);
        //���݂̋�Ԃ̃O���[�vA�Ɛe��ԏ����̃O���[�vB������
        executeHitChk_RoundRobin(&_stackCurrentSpaceActor_GroupA, &_stackParentSpaceActor_GroupB );
        //�e��ԏ����̃O���[�vA�ƌ��݂̋�Ԃ̃O���[�vB������
        executeHitChk_RoundRobin(&_stackParentSpaceActor_GroupA , &_stackCurrentSpaceActor_GroupB);
    }

    UINT32 next_level_index = prm_index*8 + 1; //_papSpace[prm_index] ��Ԃ̎q��Ԃ̃��[�g�������ʒu0�Ԃ̔z��v�f�ԍ�
    if ( next_level_index > _num_space-1) {
        //�v�f���I�[�o�[�A�܂胊�[�t
        _stackCurrentSpaceActor_GroupA.clear();
        _stackCurrentSpaceActor_GroupB.clear();
        return; //�e��Ԃ֖߂�
    } else {
        //������B���A���̑O�Ɍ���ԃA�N�^�[��e��ԃA�N�^�[�̃X�^�b�N�֒ǉ��B
        //����������Ԃ��猩���ꍇ�̐e��ԃA�N�^�[�݌v������Ă����Ă��B
        //(����ԃX�^�b�N���J��)
        int _stackParentSpaceActor_GroupA_p = _stackParentSpaceActor_GroupA._p; //�X�^�b�N�|�C���^�ۑ�
        int _stackParentSpaceActor_GroupB_p = _stackParentSpaceActor_GroupB._p;
        GgafActor* pActor;
        while (true) {
            pActor = _stackCurrentSpaceActor_GroupA.pop();
            if (pActor) {
                _stackParentSpaceActor_GroupA.push(pActor);
            } else {
                break;
            }
        }
        while (true) {
            pActor = _stackCurrentSpaceActor_GroupB.pop();
            if (pActor) {
                _stackParentSpaceActor_GroupB.push(pActor);
            } else {
                break;
            }
        }

        //�q��Ԃւ����邪�ǂ�
        for(UINT32 i = next_level_index; i < next_level_index+8; i++) {
            if (((_paSpace[i]._kindinfobit & _kind_groupA) > 0) || ((_paSpace[i]._kindinfobit & _kind_groupB) > 0)) {
                executeHitChk(i);
            }
        }

        //���A��Ȃ���
        //�X�^�b�N�̉���ipush�������A���ɖ߂��j
        _stackParentSpaceActor_GroupA._p = _stackParentSpaceActor_GroupA_p;
        _stackParentSpaceActor_GroupB._p = _stackParentSpaceActor_GroupB_p;
        return; //�e��Ԃ֖߂�
    }
}


void LinearOctreeForActor::executeHitChk_RoundRobin(CollisionStack* prm_pStackA, CollisionStack* prm_pStackB) {
    //�ǂ��炩������ΏI��
    UINT32 num_stackA = prm_pStackA->_p;
    UINT32 num_stackB = prm_pStackB->_p;
    GgafActor** papStackActor_A = prm_pStackA->_apActor;
    GgafActor** papStackActor_B = prm_pStackB->_apActor;
    for (UINT32 i = 0; i < num_stackA; i++) {
        for (UINT32 j = 0; j < num_stackB; j++) {
            papStackActor_A[i]->executeHitChk_MeAnd(papStackActor_B[j]);
        }
    }
}


LinearOctreeForActor::~LinearOctreeForActor() {
}




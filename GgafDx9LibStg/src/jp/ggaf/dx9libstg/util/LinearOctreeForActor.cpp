#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


LinearOctreeForActor::LinearOctreeForActor(int prm_level) : GgafLinearOctree(prm_level) {
}


void LinearOctreeForActor::executeAllBumpChk(actorkind prm_groupA, actorkind prm_groupB) {
//    for (int i = 0; i < prm_pair_num; i++) {
//        //actorkind group_A = prm_actorkindmask_pair[i][0];
//       // actorkind group_B = prm_actorkindmask_pair[i][1];
//    }

    _kind_groupA = prm_groupA;
    _kind_groupB = prm_groupB;
    if (((_paSpace[0]._kindinfobit & _kind_groupA) > 0) && ((_paSpace[0]._kindinfobit & _kind_groupB) > 0)) {
        executeBumpChk(0);//�s���Ă�����Ⴂ
        _stackParentSpaceActor_GroupA.clear();
        _stackParentSpaceActor_GroupB.clear();
        //���A��Ȃ����B
    }
}


void LinearOctreeForActor::executeBumpChk(int prm_index) {
    Space* pSpace = &(_paSpace[prm_index]);


    Elem* pElem = pSpace->_pElemFirst;
    GgafActor* pActor_ElemValue = ((ElemEx*)pElem)->_pActor;
    if (pElem != NULL) {
        while(true) {
            if ((pElem->_kindbit & _kind_groupA) > 0) {
                _stackCurrentSpaceActor_GroupA.push(pActor_ElemValue);
            }
            if ((pElem->_kindbit & _kind_groupB) > 0) {
                _stackCurrentSpaceActor_GroupB.push(pActor_ElemValue);
            }
            if (pElem == pSpace->_pElemLast) {
                break;
            }
            pElem = pElem -> _pNext;
            pActor_ElemValue = ((ElemEx*)pElem)->_pActor;
        }
        //���݂̋�Ԃ̃O���[�vA�ƃO���[�vB������
        _TRACE_("1executeBumpChk_RoundRobin(&_stackCurrentSpaceActor_GroupA, &_stackCurrentSpaceActor_GroupB);");
        executeBumpChk_RoundRobin(&_stackCurrentSpaceActor_GroupA, &_stackCurrentSpaceActor_GroupB);

        //���݂̋�Ԃ̃O���[�vA�Ɛe��ԏ����̃O���[�vB������
        _TRACE_("2executeBumpChk_RoundRobin(&_stackCurrentSpaceActor_GroupA, &_stackParentSpaceActor_GroupB );");
        executeBumpChk_RoundRobin(&_stackCurrentSpaceActor_GroupA, &_stackParentSpaceActor_GroupB );

        //�e��ԏ����̃O���[�vA�ƌ��݂̋�Ԃ̃O���[�vB������
        _TRACE_("3executeBumpChk_RoundRobin(&_stackParentSpaceActor_GroupA , &_stackCurrentSpaceActor_GroupB);");
        executeBumpChk_RoundRobin(&_stackParentSpaceActor_GroupA , &_stackCurrentSpaceActor_GroupB);
    }


    int next_level_index = prm_index*8 + 1; //_papSpace[prm_index] ��Ԃ̎q��Ԃ̃��[�g�������ʒu0�Ԃ̔z��v�f�ԍ�
    if ( next_level_index > _num_space-1) {
        //�v�f���I�[�o�[�A�܂胊�[�t
        _stackCurrentSpaceActor_GroupA.clear();
        _stackCurrentSpaceActor_GroupB.clear();
        return; //�e��Ԃ֖߂�
    } else {
        //������B���̑O�ɁA�e��ԃA�N�^�[�̃X�^�b�N�֒ǉ�(����ԃX�^�b�N���J��)
        int add_num_GroupA, add_num_GroupB;
        add_num_GroupA = add_num_GroupB = 0;
        GgafActor* pActor;
        while (true) {
            pActor = _stackCurrentSpaceActor_GroupA.pop();
            if (pActor == NULL) {
                break;
            } else {
                _stackParentSpaceActor_GroupA.push(pActor);
                add_num_GroupA++;
            }
        }
        while (true) {
            pActor = _stackCurrentSpaceActor_GroupB.pop();
            if (pActor == NULL) {
                break;
            } else {
                _stackParentSpaceActor_GroupB.push(pActor);
                add_num_GroupB++;
            }
        }

        //�q��Ԃւ����邪�ǂ�
        for(int i = next_level_index; i < next_level_index+8; i++) {
            if (((_paSpace[i]._kindinfobit & _kind_groupA) > 0) && ((_paSpace[i]._kindinfobit & _kind_groupB) > 0)) {
                executeBumpChk(i);
            }
        }

        //���A��Ȃ���
        for (int i = 0; i < add_num_GroupA; i ++) {
            _stackParentSpaceActor_GroupA.pop();
        }
        for (int i = 0; i < add_num_GroupB; i ++) {
            _stackParentSpaceActor_GroupB.pop();
        }
        return; //�e��Ԃ֖߂�
    }


}

void LinearOctreeForActor::executeBumpChk_RoundRobin(CollisionStack* prm_pStackA, CollisionStack* prm_pStackB) {

    //����������ΏI��
    if (prm_pStackA->_pFirst == NULL || prm_pStackB->_pFirst == NULL ) {
        return;
    }

    GgafActor* pActor_A;
    GgafActor* pActor_B;
    while(true) {
        pActor_A = prm_pStackA->pop();
        if (pActor_A == NULL) {
            break; //�I��
        }
        while(true) {
            pActor_B = prm_pStackB->pop();
            if (pActor_B == NULL) {
                break;
            }
            _TRACE_("BumpChk("<<pActor_A->getName()<<" x "<<pActor_B->getName()<<")");
            pActor_A->executeBumpChk_MeAnd(pActor_B);
        }
    }
}



LinearOctreeForActor::~LinearOctreeForActor() {
}




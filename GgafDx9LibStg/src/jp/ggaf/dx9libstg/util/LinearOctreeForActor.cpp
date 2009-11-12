#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


LinearOctreeForActor::LinearOctreeForActor(int prm_level) : GgafLinearOctree(prm_level) {
}


void LinearOctreeForActor::executeAllBumpChk(actorkind prm_paaActorkindMaskPair[][2], int prm_pair_num) {
    for (int i = 0; i < prm_pair_num; i++) {
        //actorkind group_A = prm_actorkindmask_pair[i][0];
       // actorkind group_B = prm_actorkindmask_pair[i][1];
    }
    executeBumpChk(0);
}

void LinearOctreeForActor::executeBumpChk(int prm_index) {
    Space* pSpace = &(_paSpace[prm_index]);

    Elem* pElem = pSpace->_pElemFirst;
    while(true) {

        pElem = pElem -> _pNext;
        if (pElem == pSpace->_pElemLast) {
            break;
        }
    }
    _pRegElemFirst = NULL;




    int next_level_index = prm_index*8 + 1; //_papSpace[prm_index] 空間の子空間のモートン順序位置0番の配列要素番号
    for(int i = next_level_index; i < next_level_index+8; i++) {
        executeBumpChk(i);
    }

}



LinearOctreeForActor::~LinearOctreeForActor() {
}




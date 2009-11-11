#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


LinearOctreeForActor::LinearOctreeForActor(int prm_level) : LinearOctree(prm_level) {
}


void LinearOctreeForActor::executeAllBumpChk(actorkind prm_paaActorkindMaskPair[][2], int prm_pair_num) {
    for (int i = 0; i < prm_pair_num; i++) {
        actorkind group_A = prm_actorkindmask_pair[i][0];
        actorkind group_B = prm_actorkindmask_pair[i][1];
    }
    executeBumpChk(Space* prm_pSpace);
}


LinearOctreeForActor::~LinearOctreeForActor() {
}




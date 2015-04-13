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
        //では八分木を巡る旅へ行ってらっしゃい
        executeHitChk(0); //いってきます
        //はいお帰りなさい。
        _stackParentOctantActor_GroupA.clear();
        _stackParentOctantActor_GroupB.clear();
    }
}

void LinearOctreeForActor::executeHitChk(uint32_t prm_index) {
    LinearOctreeActorElem* pElem = ((LinearOctreeActorElem*)(_paOctant[prm_index]._pElem_first));
    if (pElem) {
        GgafLinearOctreeElem* pElem_last = _paOctant[prm_index]._pElem_last;
        while (true) {
            if (pElem->_kindbit & _kind_groupA) {
                _stackCurrentOctantActor_GroupA.push(pElem->_pActor);
            }
            if (pElem->_kindbit & _kind_groupB) {
                _stackCurrentOctantActor_GroupB.push(pElem->_pActor);
            }
            if (pElem == pElem_last) {
                break;
            }
            pElem = (LinearOctreeActorElem*)(pElem->_pNext);
        }
        //現在の空間のグループAとグループB総当り
        executeHitChk_RoundRobin(&_stackCurrentOctantActor_GroupA, &_stackCurrentOctantActor_GroupB);
        //現在の空間のグループAと親空間所属のグループB総当り
        executeHitChk_RoundRobin(&_stackCurrentOctantActor_GroupA, &_stackParentOctantActor_GroupB );
        //親空間所属のグループAと現在の空間のグループB総当り
        executeHitChk_RoundRobin(&_stackParentOctantActor_GroupA , &_stackCurrentOctantActor_GroupB);
    }

    const uint32_t next_level_index = prm_index*8 + 1; //_papOctant[prm_index] 空間の子空間のモートン順序位置0番の配列要素番号
    if ( next_level_index > _num_space_minus_one) {
        //要素数オーバー、つまりリーフ
        _stackCurrentOctantActor_GroupA.clear();
        _stackCurrentOctantActor_GroupB.clear();
        return; //親空間へ戻る
    } else {
        //もぐる。が、その前に現空間アクターを親空間アクターのスタックへ追加。
        //もぐった空間から見た場合の親空間アクター累計を作っておいてやる。
        //(現空間スタックも開放)
        const int stackParentOctantActor_GroupA_p = _stackParentOctantActor_GroupA._p; //スタックポインタ保存
        const int stackParentOctantActor_GroupB_p = _stackParentOctantActor_GroupB._p;
        _stackParentOctantActor_GroupA.pop_push(&_stackCurrentOctantActor_GroupA);
        _stackParentOctantActor_GroupB.pop_push(&_stackCurrentOctantActor_GroupB);

        //子空間へもぐるが良い
        for(uint32_t i = next_level_index; i < next_level_index+8; i++) {
            if ((_paOctant[i]._kindinfobit & _kind_groupA) || (_paOctant[i]._kindinfobit & _kind_groupB) ) {
                executeHitChk(i);
            }
        }

        //お帰りなさい
        //スタックの解放（pushした分、元に戻す）
        _stackParentOctantActor_GroupA._p = stackParentOctantActor_GroupA_p;
        _stackParentOctantActor_GroupB._p = stackParentOctantActor_GroupB_p;
        return; //親空間へ戻る
    }
}

void LinearOctreeForActor::executeHitChk_RoundRobin(CollisionStack* prm_pStackA, CollisionStack* prm_pStackB) {
    //どちらか無ければ終了
    const uint32_t num_stackA = prm_pStackA->_p;
    const uint32_t num_stackB = prm_pStackB->_p;
    GgafActor** papStackActor_A = prm_pStackA->_apActor;
    GgafActor** papStackActor_B = prm_pStackB->_apActor;
    GgafActor* pActor_A;
    for (uint32_t i = 0; i < num_stackA; i++) {
        pActor_A = papStackActor_A[i];
        for (uint32_t j = 0; j < num_stackB; j++) {
            pActor_A->executeHitChk_MeAnd(papStackActor_B[j]);
        }
    }
}

LinearOctreeForActor::~LinearOctreeForActor() {
}


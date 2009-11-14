#ifndef LINEAROCTREEFORACTOR_H_
#define LINEAROCTREEFORACTOR_H_
namespace GgafDx9LibStg {

class LinearOctreeForActor : public GgafCore::GgafLinearOctree {

public:



    class CollisionStack {
    public:

        GgafCore::GgafActor* _apActor[5000];
        DWORD _p;

        CollisionStack() {
            _p = 0;
        }

        void push(GgafCore::GgafActor* prm_pActor) {
            _apActor[_p] = prm_pActor;
            _p++;
        }
        GgafCore::GgafActor* pop() {
            if (_p == 0) {
                return NULL;
            } else {
                _p--;
                return _apActor[_p];
            }
        }

        void clear() {
            _p = 0;
        }

        ~CollisionStack() {
            clear();
        }

        void dump() {
            TEXT5("CollisionStack.dump=");
            for (int i = 0; i < _p; i++) {
                TEXT5((_apActor[i]->getName())<<"->");
            }
            TEXT5("END");
        }
    };


    CollisionStack _stackParentSpaceActor_GroupA;
    CollisionStack _stackParentSpaceActor_GroupB;

    CollisionStack _stackCurrentSpaceActor_GroupA;
    CollisionStack _stackCurrentSpaceActor_GroupB;

    actorkind _kind_groupA;
    actorkind _kind_groupB;

    void executeBumpChk_RoundRobin(CollisionStack* prm_pStackA, CollisionStack* prm_pStackB);

//    class KindMap {
//    public:
//        class Node {
//        public:
//            actorkind  key;
//            ActorList* _pActor;
//        };
//
//        Node _node[10];
//        KindMap() {
//        }
//        ActorList* getActorList(actorkind prm_key) {
//            for (int i = 10; i < 10; i++) {
//                if (prm_key == _node[i].key) {
//                    return _node[i]._pActor;
//                }
//            }
//            return NULL;
//        }
//
//
//
//    };

    void executeBumpChk(DWORD prm_index);

    void executeAllBumpChk(actorkind prm_groupA, actorkind prm_groupB);


    LinearOctreeForActor(int prm_level);



    virtual ~LinearOctreeForActor();
};





}
#endif /*LINEAROCTREEFORACTOR_H_*/


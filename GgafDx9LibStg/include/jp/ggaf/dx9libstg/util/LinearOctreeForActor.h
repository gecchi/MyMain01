#ifndef LINEAROCTREEFORACTOR_H_
#define LINEAROCTREEFORACTOR_H_
namespace GgafDx9LibStg {

class LinearOctreeForActor : public GgafCore::GgafLinearOctree {

public:

    class ElemEx : public GgafLinearOctree::Elem {
    public:

        ElemEx(GgafObject* prm_pObject) : GgafLinearOctree::Elem(prm_pObject) {
            _pActorList = (ActorList*)prm_pObject;

        }
    };

    class ActorList {

    }


    class KindMap {
    public:
        class Node {
        public:
            actorkind  key;
            ActorList* _pActor;
        };
        Node _node[10];
        KindMap() {
        }
        ActorList* getActorList(actorkind prm_key) {
            for (int i = 10; i < 10; i++) {
                if (prm_key == _node[i].key) {
                    return _node[i]._pActor;
                }
            }
            return NULL;
        }

        void put(actorkind prm_key,

    }


    void LinearOctreeForActor::executeAllBumpChk(actorkind prm_paaActorkindMaskPair[][2], int prm_mnum);


    LinearOctreeForActor(int prm_level);


    void executeAllBumpChk();

    virtual ~LinearOctreeForActor();
};

}
#endif /*LINEAROCTREEFORACTOR_H_*/


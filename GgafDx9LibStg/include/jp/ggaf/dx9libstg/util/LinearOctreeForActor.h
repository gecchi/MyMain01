#ifndef LINEAROCTREEFORACTOR_H_
#define LINEAROCTREEFORACTOR_H_
namespace GgafDx9LibStg {

class LinearOctreeForActor : public GgafCore::GgafLinearOctree {

public:

    class ElemEx : public GgafLinearOctree::Elem {
    public:
        GgafCore::GgafActor* _pActor;
        ElemEx(GgafCore::GgafObject* prm_pObject, DWORD prm_kindbit) : GgafLinearOctree::Elem(prm_pObject,prm_kindbit) {
            _pActor = (GgafCore::GgafActor*)prm_pObject;
        }
    };


    class CollisionList {
    public:
        class Elem {
        public:
            /** ŽŸ—v‘f */
            Elem* _pNext;
            /** ‘O—v‘f */
            Elem* _pPrev;
            /** ’l */
            GgafCore::GgafActor* _pValue;

            Elem(GgafCore::GgafActor* prm_pActor) {
                _pValue = prm_pActor;
                _pNext = NULL;
                _pPrev = NULL;
            }

            ~Elem() {}
        };

        Elem* _pFirst;
        Elem* _pLast;
        CollisionList() {
            _pFirst = NULL;
            _pLast = NULL;
        }

        void push(GgafCore::GgafActor* prm_pActor) {
            Elem* pNew = NEW Elem(prm_pActor);
            if (_pFirst) {
                _pLast->_pNext = pNew;
                pNew->_pPrev = _pLast;
            } else {
                _pFirst = pNew;
                _pLast = _pFirst;
            }
        }
        GgafCore::GgafActor* pop() {
            if (_pFirst) {
                Elem* pRet = _pLast;
                GgafCore::GgafActor* pVal = pRet->_pValue; //”O‚Ì‚½‚ß
                _pLast->_pPrev->_pNext = NULL;
                _pLast = _pLast ->_pPrev;
                delete pRet;
                return pVal;
            } else {
                return NULL;
            }
        }

        ~CollisionList() {}
    };


    CollisionList _listTreeGroupA;
    CollisionList _listTreeGroupB;

    CollisionList _listGroupA;
    CollisionList _listGroupB;

    actorkind _kind_groupA;
    actorkind _kind_groupB;

    void executeBumpChk_RoundRobin(CollisionList* prm_pListA, CollisionList* prm_pListB);
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

    void executeBumpChk(int prm_index);

    void executeAllBumpChk(actorkind prm_groupA, actorkind prm_groupB);


    LinearOctreeForActor(int prm_level);



    virtual ~LinearOctreeForActor();
};

}
#endif /*LINEAROCTREEFORACTOR_H_*/


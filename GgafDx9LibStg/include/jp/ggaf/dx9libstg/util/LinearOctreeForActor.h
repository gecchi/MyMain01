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


    class CollisionStack {
    public:
        class Elem {
        public:
            /** 次要素 */
            Elem* _pNext;
            /** 値 */
            GgafCore::GgafActor* _pValue;

            Elem(GgafCore::GgafActor* prm_pActor) {
                _pValue = prm_pActor;
                _pNext = NULL;
            }

            ~Elem() {}
        };

        /** 先頭要素 */
        Elem* _pFirst;
        CollisionStack() {
            _pFirst = NULL;
        }

        void push(GgafCore::GgafActor* prm_pActor) {
            Elem* pNew = NEW Elem(prm_pActor);
            if (_pFirst == NULL) {
                //最初の一つ目
                pNew->_pNext = NULL; //�@
                _pFirst = pNew;
            } else {
                //２つ目以降
                pNew->_pNext = _pFirst;
                _pFirst = pNew;
            }
        }
        GgafCore::GgafActor* pop() {
            if (_pFirst == NULL) {
                //何も無い場合
                return NULL;
            } else {
                //ある場合
                Elem* pFirst_temp = _pFirst;
                _pFirst = _pFirst->_pNext; //最後の１つの場合でも、�@により、ここでNULLが入る
                GgafCore::GgafActor* pRetVal = pFirst_temp->_pValue;
                delete pFirst_temp;
                return pRetVal;
            }
        }

        void clear() {
            Elem* pElem = _pFirst;
            while(true) {
                if (pElem == NULL) {
                    break;
                }
                Elem* pTemp = pElem;
                pElem = pElem -> _pNext;
                delete pTemp;
            }
            _pFirst = NULL;
        }

        ~CollisionStack() {
            clear();
        }

        void dump() {
            TEXT5("CollisionStack.dump=");
            Elem* pElem = _pFirst;
            while(true) {
                if (pElem == NULL) {
                    TEXT5("END");
                    break;
                }
                TEXT5((pElem->_pValue->getName())<<"->");
                pElem = pElem -> _pNext;
            }

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

    void executeBumpChk(int prm_index);

    void executeAllBumpChk(actorkind prm_groupA, actorkind prm_groupB);


    LinearOctreeForActor(int prm_level);



    virtual ~LinearOctreeForActor();
};

}
#endif /*LINEAROCTREEFORACTOR_H_*/


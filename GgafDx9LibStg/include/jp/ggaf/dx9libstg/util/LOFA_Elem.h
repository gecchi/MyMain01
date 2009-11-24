#ifndef LOFA_ELEM_H_
#define LOFA_ELEM_H_
namespace GgafDx9LibStg {

/**
 * GgafLinearOctreeElem用の要素クラス .
 * GgafActorを要素することに特化しています
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class LOFA_Elem : public GgafCore::GgafLinearOctreeElem {
public:
    GgafCore::GgafActor* _pActor;
    LOFA_Elem(GgafCore::GgafObject* prm_pObject, DWORD prm_kindbit) : GgafCore::GgafLinearOctreeElem(prm_pObject,prm_kindbit) {
        _pActor = (GgafCore::GgafActor*)prm_pObject;
    }
};


}
#endif /*LOFA_ELEM_H_*/


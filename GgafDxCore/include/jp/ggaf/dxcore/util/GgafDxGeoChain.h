#ifndef GGAFDXCORE_GGAFDXGEOCHAIN_H_
#define GGAFDXCORE_GGAFDXGEOCHAIN_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace GgafDxCore {

///**
// * 座標情報連結リストクラス(TODO:作成中・・・)
// * @version 1.00
// * @since 2008/12/19
// * @author Masatoshi Tsuge
// */
//class GgafDxGeoChain : public GgafCore::GgafObject {
//public:
//    GgafDxGeoElem* _pFirst;
//    GgafDxGeoElem* _pGeoChainRingActive;
//
//public:
//    /**
//     * コンストラクタ
//     */
//    GgafDxGeoChain(int prm_num, GgafDxGeometricActor* prm_pActor) : GgafObject() {
//        static GgafDxGeoElem* pWork;
//        static GgafDxGeoElem* pTemp;
//        _pFirst = NEW GgafDxGeoElem(prm_pActor);
//        pWork = _pFirst;
//        pTemp = nullptr;
//        for (int i = 0; i < prm_num - 1; i++) {
//            pTemp = NEW GgafDxGeoElem(prm_pActor);
//            pWork->_next = pTemp;
//            pWork = pTemp;
//        }
//        pTemp->_next = _pFirst;
//        _pGeoChainRingActive = _pFirst;
//    }
//
//    GgafDxGeoElem* getActiveElem() {
//        return _pGeoChainRingActive;
//    }
//
//    GgafDxGeoElem* nextElem() {
//        _pGeoChainRingActive = _pGeoChainRingActive->_next;
//        return _pGeoChainRingActive;
//    }
//
//    virtual ~GgafDxGeoChain() {
//        GgafDxGeoElem* pWork = _pGeoChainRingActive;
//        GgafDxGeoElem* pWorkNext = nullptr;
//        for (DWORD i = 0; i < 50 - 1 + 1; i++) {
//            pWorkNext = pWork->_next;
//            GGAF_DELETE(pWork);
//            pWork = pWorkNext;
//        }
//    }
//
//};
}
#endif /*GGAFDXCORE_GGAFDXGEOCHAIN_H_*/

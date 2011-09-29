#ifndef GGAFDX9GEOCHAIN_H_
#define GGAFDX9GEOCHAIN_H_
namespace GgafDx9Core {

/**
 * 座標コンテナ連結リストクラス
 * @version 1.00
 * @since 2008/12/19
 * @author Masatoshi Tsuge
 */
class GgafDx9GeoChain {
public:

    GgafDx9GeoElem* _pFirst;
    GgafDx9GeoElem* _pGeoChainRingActive;

    /**
     * コンストラクタ
     */
    GgafDx9GeoChain(int prm_num, GgafDx9GeometricActor* prm_pActor) {
        static GgafDx9GeoElem* pWork;
        static GgafDx9GeoElem* pTemp;
        _pFirst = NEW GgafDx9GeoElem(prm_pActor);
        pWork = _pFirst;
        pTemp = NULL;
        for (int i = 0; i < prm_num - 1; i++) {
            pTemp = NEW GgafDx9GeoElem(prm_pActor);
            pWork->_next = pTemp;
            pWork = pTemp;
        }
        pTemp->_next = _pFirst;
        _pGeoChainRingActive = _pFirst;
    }

    GgafDx9GeoElem* getActiveElem() {
        return _pGeoChainRingActive;
    }

    GgafDx9GeoElem* nextElem() {
        _pGeoChainRingActive = _pGeoChainRingActive->_next;
        return _pGeoChainRingActive;
    }

    virtual ~GgafDx9GeoChain() {
        GgafDx9GeoElem* pWork = _pGeoChainRingActive;
        GgafDx9GeoElem* pWorkNext = NULL;
        for (DWORD i = 0; i < 50 - 1 + 1; i++) {
            pWorkNext = pWork->_next;
            DELETE_IMPOSSIBLE_NULL(pWork);
            pWork = pWorkNext;
        }
    }

};
}
#endif /*GGAFDX9GEOCHAIN_H_*/

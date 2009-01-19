#ifndef GEOMETRYCHAIN_H_
#define GEOMETRYCHAIN_H_
namespace GgafDx9LibStg {



class GeometryChain {
public:

	GeoElement* _pFirst;
	GeoElement* _pGeoChainRingActive;

	/**
	 * コンストラクタ
	 */
	GeometryChain(int prm_iChainNum, GgafDx9Core::GgafDx9UntransformedActor* prm_pActor) {
		static GeoElement* pWork;
		static GeoElement* pTemp;
		_pFirst = NEW GeoElement(prm_pActor);
		pWork = _pFirst;
		pTemp = NULL;
		for (DWORD i = 0; i < prm_iChainNum-1; i++) {
			pTemp = NEW GeoElement(prm_pActor);
			pWork->_next = pTemp;
			pWork = pTemp;
		}
		pTemp->_next = _pFirst;
		_pGeoChainRingActive = _pFirst;
	}

	GeoElement* getActiveElem() {
		return _pGeoChainRingActive;
	}

	GeoElement* nextElem() {
		_pGeoChainRingActive = _pGeoChainRingActive ->_next;
		return _pGeoChainRingActive;
	}

	virtual ~GeometryChain() {
		GeoElement* pWork = _pGeoChainRingActive;
		GeoElement* pWorkNext = NULL;
		for (DWORD i = 0; i < 50-1 + 1; i++) {
			pWorkNext = pWork->_next;
			DELETE_IMPOSSIBLE_NULL(pWork);
			pWork = pWorkNext;
		}
	}

};
}
#endif /*GEOMETRYCHAIN_H_*/

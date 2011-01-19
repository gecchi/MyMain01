#ifndef GGAFDX9GEOELEM_H_
#define GGAFDX9GEOELEM_H_
namespace GgafDx9Core {

/**
 * 座標コンテナ
 * @version 1.00
 * @since 2008/12/19
 * @author Masatoshi Tsuge
 */
class GgafDx9GeoElem {
public:
    int _X;
    int _Y;
    int _Z;
    int _RX;
    int _RY;
    int _RZ;
    GgafDx9GeoElem* _next;

    GgafDx9GeoElem() {
        _X = 0;
        _Y = 0;
        _Z = 0;
        _RX = 0;
        _RY = 0;
        _RZ = 0;
        _next = NULL;
    }

    GgafDx9GeoElem(int prm_X, int prm_Y, int prm_Z) {
        _X = prm_X;
        _Y = prm_Y;
        _Z = prm_Z;
        _RX = 0;
        _RY = 0;
        _RZ = 0;
        _next = NULL;
    }

    GgafDx9GeoElem(int prm_X, int prm_Y, int prm_Z, int prm_RX, int prm_RY, int prm_RZ) {
        _X = prm_X;
        _Y = prm_Y;
        _Z = prm_Z;
        _RX = prm_RX;
        _RY = prm_RY;
        _RZ = prm_RZ;
        _next = NULL;
    }

    GgafDx9GeoElem(GgafDx9GeometricActor* prm_pActor) {
        _X = prm_pActor->_X;
        _Y = prm_pActor->_Y;
        _Z = prm_pActor->_Z;
        _RX = prm_pActor->_RX;
        _RY = prm_pActor->_RY;
        _RZ = prm_pActor->_RZ;
        _next = NULL;
    }

    void set(int prm_X, int prm_Y, int prm_Z, int prm_RX, int prm_RY, int prm_RZ) {
        _X = prm_X;
        _Y = prm_Y;
        _Z = prm_Z;
        _RX = prm_RX;
        _RY = prm_RY;
        _RZ = prm_RZ;
    }

    void set(int prm_X, int prm_Y, int prm_Z) {
        _X = prm_X;
        _Y = prm_Y;
        _Z = prm_Z;
    }

    void set(GgafDx9GeometricActor* prm_pActor) {
        _X = prm_pActor->_X;
        _Y = prm_pActor->_Y;
        _Z = prm_pActor->_Z;
        _RX = prm_pActor->_RX;
        _RY = prm_pActor->_RY;
        _RZ = prm_pActor->_RZ;
    }
    virtual ~GgafDx9GeoElem() {
        _next = NULL;
    }
};

}
#endif /*GGAFDX9GEOELEM_H_*/

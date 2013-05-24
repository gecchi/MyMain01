/////////////////////////////////////////////////////////
// FRM_Manager.h
// templated manager
//
/////////////////////////////////////////////////////////

#ifndef FRM_MANAGER_H
#define FRM_MANAGER_H

#include "jp/ggaf/dxcore/util/XFile/framework/frm_types.h"
#include <vector>

namespace Frm {
template<class T>
class Manager {
public:
    Manager(void) {
    }
    void SetSize(uint16_t pMaxSize) {
        _Ts.reserve(pMaxSize);
    }
    virtual ~Manager(void) {
        while (!_Ts.empty())
            _Ts.pop_back();
    }
    //redefine the destructor for each manager created
    inline uint16_t Add(T &pT) {
        _Ts.push_back(pT);
        return (uint16_t) _Ts.size();
    }
    inline bool Set(uint16_t pID, T pT) {
        if (_Ts[pID] != 0)
            return false;
        _Ts[pID] = pT;
        return true;
    }
    inline T Remove(uint16_t pID) {
        T temp = _Ts[pID];
        _Ts[pID] = 0;
        return temp;
    }
    inline T Get(uint16_t pID) {
        return _Ts[pID];
    }
    uint16_t Size(void) {
        return (uint16_t) _Ts.size();
    }
    const T operator[](uint16_t pID) {
        return _Ts[pID];
    }
    //      T& operator[](uint16_t pID)const{return _Ts[pID];};
protected:
    std::vector<T> _Ts;
};

}
#endif

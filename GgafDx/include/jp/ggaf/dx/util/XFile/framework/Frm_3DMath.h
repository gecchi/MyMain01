/////////////////////////////////////////////////////////
// Frm_3DMath.h
// Declares vector, matrix, rectangles and defines special
// array elements
/////////////////////////////////////////////////////////

#ifndef FRM_MATH_H
#define FRM_MATH_H
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/Util.h"

//#include <mem.h>
#include <math.h>
#include <string.h>

#define MINFLOAT 1.17549435E-38F

namespace Frm {

//Vector description/////////////////////////
template<typename T>
class vector {
public:
    T x, y, z;
    vector(void) :
        x(0), y(0), z(0) {
    }
    vector(T px, T py, T pz) :
        x(px), y(py), z(pz) {
    }
    vector(const vector<T> &pv) :
        x(pv.x), y(pv.y), z(pv.z) {
    }
    vector(const T* &pv) {
        x = pv[0];
        y = pv[1];
        z = pv[2];
    }

    vector<T>& operator=(const vector<T> &pv) {
        x = pv.x;
        y = pv.y;
        z = pv.z;
        return *this;
    }
    inline void Set(T px, T py, T pz) {
        x = px;
        y = py;
        z = pz;
    }
    bool operator>(const vector<T> &pv) {
        return (x + y) > (pv.x + pv.y);
    }

    T operator[](int index) const {
        if (index == 1)
            return y;
        if (index == 2)
            return z;
        return x;
    }
    T& operator[](int index) {
        if (index == 1)
            return y;
        if (index == 2)
            return z;
        return x;
    }

    vector<T> operator+(vector<T> pv) const {
        return vector<T> ((T) (x + pv.x), (T) (y + pv.y), (T) (z + pv.z));
    }
    vector<T> operator-(vector<T>& pv) const {
        return vector<T> ((T) (x - pv.x), (T) (y - pv.y), (T) (z - pv.z));
    }
    vector<T> operator*(T pT) const {
        return vector<T> ((T) (pT * x), (T) (pT * y), (T) (pT * z));
    }
    void Normalize(void) {
        vector<T> pv((T) (x * x), (T) (y * y), (T) (z * z));
        T fLength = (T) (1.0f / (float) (pv.x + pv.y + pv.z));
        if (fLength < 1e-08)
            return;
        x = (T) (pv.x * fLength);
        y = (T) (pv.y * fLength);
        z = (T) (pv.z * fLength);
    }
    T Dot(vector<T> pV) const {
        return (T) (x * pV.x + y * pV.y + z * pV.z);
    }
    vector<T> Cross(vector<T> pV) const {
        return vector<T> ((T) (y * pV.z - z * pV.y), (T) (z * pV.x - x * pV.z),
                (T) (x * pV.y - y * pV.x));
    }
    vector<T> UnitCross(vector<T> pV) const {
        vector<T> pR((T) (y * pV.z - z * pV.y), (T) (z * pV.x - x * pV.z),
                (T) (x * pV.y - y * pV.x));
        pR.Normalize();
        return pR;
    }
    //addtsuge
    T Abs() {
        return (T) sqrt(x * x + y * y + z * z);
    }
};

typedef vector<float> Vector;

template<typename T, int size>
struct Array {
    T data[size];
    Array(void) {
        memset(data, 0, size * sizeof(T));
    }
    Array(const Array<T, size> &pA) {
        memcpy(data, pA.data, size * sizeof(T));
    }
    Array(const T* pT) {
        memcpy(data, pT, size * sizeof(T));
    }

    Array<T, size>& operator=(Array<T, size> pA) {
        memcpy(data, pA.data, size * sizeof(T));
        return *this;
    }
    Array<T, size>& operator+=(Array<T, size> pA);
    Array<T, size> operator*(const T pScalar);
    Array<T, size> operator+(Array<T, size> pA);
    Array<T, size> operator-(Array<T, size> pA);
    T operator[](int index) const {
        return data[index];
    }
    T& operator[](int index) {
        return data[index];
    }
};

//typedef Array<unsigned short, 3> Face;
typedef Array<uint32_t, 4> Face; //modify tsuge

typedef Array<float, 3> Vertex;
typedef Array<float, 2> TCoord;
typedef Array<float, 4> Color4;
typedef Array<float, 3> Color3;

template<typename T>
Array<T, 4> Set4(T px, T py, T pz, T pw) {
    T data[4];
    data[0] = px;
    data[1] = py;
    data[2] = pz;
    data[3] = pw;
    return Array<T, 4> (data);
}

template<typename T>
Array<T, 3> Set3(T px, T py, T pz) {
    T data[3];
    data[0] = px;
    data[1] = py;
    data[2] = pz;
    return Array<T, 3> (data);
}

template<typename T>
Array<T, 2> Set2(T pu, T pv) {
    T data[2];
    data[0] = pu;
    data[1] = pv;
    return Array<T, 2> (data);
}

template<typename T>
class matrix {
public:
    T data[16];
    matrix(void) {
        memset(data, 0, 16 * sizeof(T));
    }
    matrix(const matrix<T> &pm) {
        memcpy(data, pm.data, 16 * sizeof(T));
    }
    matrix(const T* pT) {
        memcpy(data, pT, 16 * sizeof(T));
    }
    void Zero(void) {
        memset(data, 0, 16 * sizeof(T));
    }
    void Identity(void) {
        memset(data, 0, 16 * sizeof(T));
        data[0] = (T) 1;
        data[5] = (T) 1;
        data[10] = (T) 1;
        data[15] = (T) 1;
    }
    //add tsugecchi 2009/08/31
    bool isIdentity() {
        if(  ONEf_EQ(data[0] ) &&
            ZEROf_EQ(data[1] ) &&
            ZEROf_EQ(data[2] ) &&
            ZEROf_EQ(data[3] ) &&
            ZEROf_EQ(data[4] ) &&
             ONEf_EQ(data[5] ) &&
            ZEROf_EQ(data[6] ) &&
            ZEROf_EQ(data[7] ) &&
            ZEROf_EQ(data[8] ) &&
            ZEROf_EQ(data[9] ) &&
             ONEf_EQ(data[10]) &&
            ZEROf_EQ(data[11]) &&
            ZEROf_EQ(data[12]) &&
            ZEROf_EQ(data[13]) &&
            ZEROf_EQ(data[14]) &&
             ONEf_EQ(data[15]) )
        {
            return true;
        } else {
            return false;
        }
    }

    matrix<T>& operator=(const matrix<T> &pm) {
        memcpy(data, pm.data, 16 * sizeof(T));
        return *this;
    }
    matrix<T> operator+(matrix<T> pm);
    matrix<T> operator-(matrix<T> pm);
    matrix<T> operator*(matrix<T> pm);
    matrix<T>& operator*=(matrix<T> &pm);
    matrix<T> operator*(T pT);
    vector<T> operator*(const vector<T>& pV);
    Array<T, 3> operator*(const Array<T, 3>& pV);

    T operator[](int index) const {
        return data[index];
    }
    T& operator[](int index) {
        return data[index];
    }

    T Index(int pRow, int pCol) const {
        return data[(pRow << 2) + pCol];
    }
    T operator()(int pRow, int pCol) const {
        return data[(pRow << 2) + pCol];
    }
    T& operator()(int pRow, int pCol) {
        return data[(pRow << 2) + pCol];
    }
    vector<T> GetRow(int index) {
        index <<= 2;
        return vector<T> (data[index++], data[index++], data[index]);
    }
    vector<T> GetColumn(int index) {
        return vector<T> (data[index], data[index + 4], data[index + 8]);
    }
    void ScalingMatrix(const vector<T> &pvT);
    void TranslationMatrix(const Array<T, 3> &pAT);
    void QuaternionMatrix(T &x, T &y, T &z, T &w);

private:
    //int k, l, row, col; //delete tsuge
};

typedef matrix<float> Matrix;
//typedef matrix<float> Matrix4F;

template<typename T>
class quaternion {
public:
    T data[4];
    quaternion(void) {
        memset(data, 0, 4 * sizeof(T));
    }
    quaternion(const quaternion<T> &pq) {
        memcpy(data, pq.data, 4 * sizeof(T));
    }
    quaternion(const T* pT) {
        memcpy(data, pT, 4 * sizeof(T));
    }
    void Zero(void) {
        memset(data, 0, 4 * sizeof(T));
    }
    T operator[](int index) const {
        return data[index];
    }
    T& operator[](int index) {
        return data[index];
    }
    quaternion<T>& operator=(const quaternion<T> &pq) {
        memcpy(data, pq.data, 4 * sizeof(T));
        return *this;
    }
    quaternion<T> operator+(quaternion<T> pq);
    quaternion<T> operator*(quaternion<T> pq);
    quaternion<T> operator*(T pT);
    T Dot(quaternion<T> &pq);
    quaternion<T> Slerp(T pT, quaternion<T> &pq);
private:
    float qACos(float pValue);
};

typedef quaternion<float> Quaternion;

//Rectangle description///////////////////////
template<typename T>
class trect {
public:
    T xs, ys, xe, ye;
    trect(void) :
        xs(0), ys(0), xe(0), ye(0) {
    }
    trect(const trect<T> &prect) {
        xs = prect.xs;
        ys = prect.ys;
        xe = prect.xe;
        ye = prect.ye;
    }
    trect<T>& operator=(const trect<T> &prect) {
        xs = prect.xs;
        ys = prect.ys;
        xe = prect.xe;
        ye = prect.ye;
        return *this;
    }
    trect<T>& operator+=(const vector<T> &pV) {
        xs += pV.x;
        ys += pV.y;
        xe += pV.x;
        ye += pV.y;
        return *this;
    }
    /**/
    /*      trect<T>& operator+=(vector<T> &pV)
     {xs += pV[VX]; ys += pV[VY]; xe += pV[VX]; ye += pV[VY]; return *this;};
    */
    trect(const T pxs, const T pys, const T pxe, const T pye) {
        xs = pxs;
        ys = pys;
        xe = pxe;
        ye = pye;
    }
    inline void Set(const T pxs, const T pys, const T pxe, const T pye) {
        xs = pxs;
        ys = pys;
        xe = pxe;
        ye = pye;
    }
    bool InRect(const T &px, const T &py) {
        if (px < xs)
            return false;
        if (px > xe)
            return false;
        if (py < ys)
            return false;
        if (py > ye)
            return false;
        return true;
    }
    bool InRect(const vector<T> &pv) {
        if (pv.x < xs)
            return false;
        if (pv.x > xe)
            return false;
        if (pv.y < ys)
            return false;
        if (pv.y > ye)
            return false;
        return true;
    }
    /**/
    /*   	bool InRect( vector<T> &pv)
     { if (pv[VX] < xs) return false;
     if (pv[VX] > xe) return false;
     if (pv[VY] < ys) return false;
     if (pv[VY] > ye) return false;
     return true;};
    */
    bool InRect(const trect<T> &prect) {
        if ((prect.xe <= xe) && (prect.ye <= ye) && (prect.xs >= xs)
                && (prect.ys >= ys))
            return true;
        return false;
    }
    bool Intersect(const trect<T> &prect) {
        if (prect.xe < xs)
            return false;
        if (prect.xs > xe)
            return false;
        if (prect.ye < ys)
            return false;
        if (prect.ys > ye)
            return false;
        return true;
    }
    bool Union(const trect<T> &prect) {
        if (!Intersect(prect))
            return false;
        if (xs < prect.xs)
            xs = prect.xs;
        if (ys < prect.ys)
            ys = prect.ys;
        if (xe > prect.xe)
            xe = prect.xe;
        if (ye > prect.ye)
            ye = prect.ye;
        return true;
    }
};

//// Implementation details ////////////////////

template<typename T, int size>
Array<T, size>& Array<T, size>::operator+=(Array<T, size> pA) {
    for (int i = 0; i < size; i++)
        data[i] += pA.data[i];
    return *this;
}

template<typename T, int size>
Array<T, size> Array<T, size>::operator*(const T pScalar) {
    T rdata[size];
    memcpy(rdata, data, size * sizeof(T));
    for (int i = 0; i < size; i++)
        rdata[i] *= pScalar;
    return Array<T, size> (rdata);
}

template<typename T, int size>
Array<T, size> Array<T, size>::operator+(Array<T, size> pA) {
    T rdata[size];
    for (int i = 0; i < size; i++)
        rdata[i] = data[i] + pA.data[i];
    return Array<T, size> (rdata);
}

template<typename T, int size>
Array<T, size> Array<T, size>::operator-(Array<T, size> pA) {
    T rdata[size];
    for (int i = 0; i < size; i++)
        rdata[i] = data[i] - pA.data[i];
    return Array<T, size> (rdata);
}

template<typename T>
matrix<T> matrix<T>::operator+(matrix<T> pm) {
    T Rdata[16];
    for (int k = 0; k < 16; k++)
        Rdata[k] = data[k] + pm.data[k];
    return matrix<T> (Rdata);
}

template<typename T>
matrix<T> matrix<T>::operator-(matrix<T> pm) {
    T Rdata[16];
    for (int k = 0; k < 16; k++)
        Rdata[k] = data[k] - pm.data[k];
    return matrix<T> (Rdata);
}

template<typename T>
matrix<T> matrix<T>::operator*(matrix<T> pm) {
    T Rdata[16];
    for (int row = 0; row < 16; row += 4)
        for (int col = 0; col < 4; col++) {
            int l = 0;
            Rdata[row + col] = 0;
            for (int k = 0; k < 4; k++, l += 4)
                Rdata[row + col] += data[row + k] * pm.data[l + col];
        }
    return matrix<T> (Rdata);
}

template<typename T>
matrix<T>& matrix<T>::operator*=(matrix<T> &pm) {
    T Rdata[16];
    for (int row = 0; row < 16; row += 4)
        for (int col = 0; col < 4; col++) {
            int l = 0;
            Rdata[row + col] = 0;
            for (int k = 0; k < 4; k++, l += 4)
                Rdata[row + col] += data[row + k] * pm.data[l + col];
        }
    memcpy(data, Rdata, 16* sizeof (T));
    return *this;
}

template<typename T>
matrix<T> matrix<T>::operator*(T pT)
{
    T Rdata[16];
    memcpy(Rdata, data, 16 * sizeof(T));
    for (int k = 0; k < 16; k++)
        Rdata[k] *= pT;
    return matrix<T>(Rdata);
}

template<typename T>
vector<T> matrix<T>::operator*(const vector<T>& pV)
{
//Gccの場合落ちる。（※コメントを外すと落ちない。謎・・・）
//危険なので使用しないこととする。
//    _TRACE_("pV.x="<<pV.x);
//    _TRACE_("pV.y="<<pV.y);
//    _TRACE_("pV.z="<<pV.z);
    T vdata[4];
    T pvdata[4];
//    _TRACE_("pvdata[0]="<<pvdata[0]);
//    _TRACE_("pvdata[1]="<<pvdata[1]);
//    _TRACE_("pvdata[2]="<<pvdata[2]);
//    _TRACE_("pvdata[3]="<<pvdata[3]);
    pvdata[0] = pV.x;
    pvdata[1] = pV.y;
    pvdata[2] = pV.z;
    pvdata[3] = 1.0f;
    for (int col = 0; col < 4; col++)
    {
        vdata[col] = 0;
        int k=0;
        for (int row = 0; row < 4; row++, k+=4)
        vdata[col] += data[k + col]*pvdata[row];
    }
    vector<T> ret(vdata[0], vdata[1], vdata[2]);
    return ret;
} /**/

template<typename T>
Array<T, 3> matrix<T>::operator*(const Array<T, 3>& pV)
{
    T vdata[4], pvdata[4];

    memcpy(pvdata, pV.data, 3*sizeof(T));
    pvdata[3] = 1.0f;

    for (int col = 0; col < 4; col++)
    {
        int k = 0;
        vdata[col] = 0;
        for (int row = 0; row < 4; row++, k+=4)
        vdata[col] += data[k + col]*pvdata[row];
    }

    return Array<T, 3>(vdata);
}

template<typename T>
void matrix<T>::ScalingMatrix(const vector<T> &pvT)
{
    Identity();
    data[0] = pvT.x;
    data[5] = pvT.y;
    data[10] = pvT.z;
}

template<typename T>
void matrix<T>::TranslationMatrix(const Array<T,3> &pAT)
{
    Identity();
    data[12] = pAT[0];
    data[13] = pAT[1];
    data[14] = pAT[2];
}

template<typename T>
void matrix<T>::QuaternionMatrix(T &x, T &y, T &z, T &w)
{
    T xx = x*x; T yy = y*y; T zz = z*z;
    T xy = x*y; T xz = x*z; T yz = y*z;
    T wx = w*x; T wy = w*y; T wz = w*z;

    data[0] = 1 - 2 * ( yy + zz );
    data[1] = 2 * ( xy - wz );
    data[2] = 2 * ( xz + wy );

    data[4] = 2 * ( xy + wz );
    data[5] = 1 - 2 * ( xx + zz );
    data[6] = 2 * ( yz - wx );

    data[8] = 2 * ( xz - wy );
    data[9] = 2 * ( yz + wx );
    data[10] = 1 - 2 * ( xx + yy );

    data[3] = data[7] = data[11] = 0.0f;
    data[12] = data[13] = data[14] = 0.0f;
    data[15] = 1.0f;
}

/*************************************************
 NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW*/

template<typename T>
float quaternion<T>::qACos(float pValue)
{
    if ( -1.0f < pValue )
    {
        if ( pValue < 1.0f )
        return (float)acos(pValue);
        else
        return 0.0f;
    }
    else
    return PI;
}

template<typename T>
quaternion<T> quaternion<T>::operator+(quaternion<T> pq)
{
    T rdata[4];
    rdata[0] = pq.data[0] + data[0];
    rdata[1] = pq.data[1] + data[1];
    rdata[2] = pq.data[2] + data[2];
    rdata[3] = pq.data[3] + data[3];
    return quaternion<T>(rdata);
}

template<typename T>
quaternion<T> quaternion<T>::operator*(T pT)
{
    T rdata[4];
    rdata[0] = pT * data[0];
    rdata[1] = pT * data[1];
    rdata[2] = pT * data[2];
    rdata[3] = pT * data[3];
    return quaternion<T>(rdata);
}

template<typename T>
T quaternion<T>::Dot(quaternion<T> &pq)
{
    return ((data[0] * pq.data[0]) + (data[1] * pq.data[1]) + (data[2] *pq.data[2]) + (data[3] * pq.data[3]));
}

template<typename T>
quaternion<T> quaternion<T>::Slerp(T pT, quaternion<T> &pq) {
    //We calculate the angle spread between both quaternions
    T AngleCos = pq.Dot(*this);
    T Angle = qACos(AngleCos); //see the function ACos above

    if (Angle < MINFLOAT)
        return quaternion<T>(*this);
    //We calculate the interpolated angle and deduce the resulting quaternion
    T InvAngleSin = (T)(1.0f / sin(Angle));

    T Coeff0 = sin((1-pT) * Angle) * InvAngleSin;
    T Coeff1 = sin(pT * Angle) * InvAngleSin;
    return quaternion<T>((*this * Coeff0)+(pq * Coeff1));
}

/*************************************************/

};
#endif

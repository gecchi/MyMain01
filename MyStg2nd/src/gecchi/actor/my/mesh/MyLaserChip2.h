#ifndef MYLASERCHIP2_H_
#define MYLASERCHIP2_H_
namespace MyStg2nd {

class MyLaserChip2: public GgafDx9LibStg::DefaultDynaD3DXMeshActor {
public:

    /** play状態になったフレーム(これの差が1かどうかで連続かを見る) */
  //  DWORD _dwFrame_switchedToActFlg;

    /**
     * 頂点クラス
     */
    class Vertex {
    public:
        float x, y, z; // 頂点座標1
        Vertex() {
        }
        ~Vertex() {
        }
    };
    /**
     * 正四面体クラス
     */
    class Tetrahedron {
    public:
        float Ex, Ey, Ez; // 頂点座標1
        float Fx, Fy, Fz; // 頂点座標2
        float Gx, Gy, Gz; // 頂点座標3
        float Hx, Hy, Hz; // 頂点座標4
        Tetrahedron() {
        }
        ~Tetrahedron() {
        }
    };

    static LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9_MyLaserChip2;

    static DWORD _dwVertexFormat;
    static DWORD _dwFVFSize;
    static DWORD _dwVertexNum;
    static int _aVertexIndexTetrahedron_A[];
    static int _aVertexIndexTetrahedron_B[];
    static int _aVertexIndexTetrahedron_C[];
    static int _aVertexIndexTetrahedron_D[];
    static int _iNum_VertexIndexTetrahedron_A;
    static int _iNum_VertexIndexTetrahedron_B;
    static int _iNum_VertexIndexTetrahedron_C;
    static int _iNum_VertexIndexTetrahedron_D;
    static Vertex* _paLaserChipVertex;
    static Tetrahedron* _pTetra_EFGH;

    int _X_prevFrame;
    int _Y_prevFrame;
    int _Z_prevFrame;

    /** 発射元アクター */
    GgafDx9Core::GgafDx9UntransformedActor* _pActor_Radical;

    MyLaserChip2(const char* prm_name, const char* prm_model);

    /**
     * ＜OverRide です＞
     */
    void initialize();

    /**
     * ＜OverRide です＞
     */
    void processBehavior();

    /**
     * ＜OverRide です＞
     */
    void processJudgement();

    /**
     * ＜OverRide です＞
     */
    void processDrawMain();

    /**
     * ＜OverRide です＞
     */
    void processHappen(int prm_no);

    /**
     * ＜OverRide です＞
     */
    void processOnHit(GgafActor* prm_pActor_Opponent);

    void setRadicalActor(GgafDx9UntransformedActor* prm_pActor) {
        _pActor_Radical = prm_pActor;
    }

    MyLaserChip2* getNext() {
        return (MyLaserChip2*)_pNext;
    }

    MyLaserChip2* getPrev() {
        return (MyLaserChip2*)_pPrev;
    }

//    void onAct();

    void onInact();

    virtual ~MyLaserChip2();

};

}
#endif /*MYLASERCHIP2_H_*/


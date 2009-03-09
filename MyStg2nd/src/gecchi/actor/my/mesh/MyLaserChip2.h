#ifndef MYLASERCHIP2_H_
#define MYLASERCHIP2_H_
namespace MyStg2nd {

class MyLaserChip2: public GgafDx9LibStg::DefaultDynaD3DXMeshActor {
public:

    /** play��ԂɂȂ����t���[��(����̍���1���ǂ����ŘA����������) */
  //  DWORD _dwFrame_switchedToActFlg;

    /**
     * ���_�N���X
     */
    class Vertex {
    public:
        float x, y, z; // ���_���W1
        Vertex() {
        }
        ~Vertex() {
        }
    };
    /**
     * ���l�ʑ̃N���X
     */
    class Tetrahedron {
    public:
        float Ex, Ey, Ez; // ���_���W1
        float Fx, Fy, Fz; // ���_���W2
        float Gx, Gy, Gz; // ���_���W3
        float Hx, Hy, Hz; // ���_���W4
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

    /** ���ˌ��A�N�^�[ */
    GgafDx9Core::GgafDx9UntransformedActor* _pActor_Radical;

    MyLaserChip2(const char* prm_name, const char* prm_model);

    /**
     * ��OverRide �ł���
     */
    void initialize();

    /**
     * ��OverRide �ł���
     */
    void processBehavior();

    /**
     * ��OverRide �ł���
     */
    void processJudgement();

    /**
     * ��OverRide �ł���
     */
    void processDrawMain();

    /**
     * ��OverRide �ł���
     */
    void processHappen(int prm_no);

    /**
     * ��OverRide �ł���
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


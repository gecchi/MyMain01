#ifndef MYLASERCHIP_H_
#define MYLASERCHIP_H_
namespace MyStg2nd {

class MyLaserChip : public GgafDx9LibStg::DefaultDynaD3DXMeshActor {
public:

    /** play��ԂɂȂ����t���[��(����̍���1���ǂ����ŘA����������) */
    DWORD _dwFrame_switchedToActFlg;

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

    static LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9_MyLaserChip;
    static DWORD _dwVertexFormat;
    static DWORD _dwFVFSize;
    static DWORD _dwVertexNum;
    static UINT _aVertexIndexTetrahedron_A[];
    static UINT _aVertexIndexTetrahedron_B[];
    static UINT _aVertexIndexTetrahedron_C[];
    static UINT _aVertexIndexTetrahedron_D[];
    static UINT _iNum_VertexIndexTetrahedron_A;
    static UINT _iNum_VertexIndexTetrahedron_B;
    static UINT _iNum_VertexIndexTetrahedron_C;
    static UINT _iNum_VertexIndexTetrahedron_D;
    static Tetrahedron* _pTetra_EFGH;

    int _X_prevFrame;
    int _Y_prevFrame;
    int _Z_prevFrame;

    /** �ΏۃA�N�^�[ */
    GgafDx9UntransformedActor* _pActor_Radical;

    MyLaserChip(const char* prm_name, const char* prm_model);

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
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    void setRadicalActor(GgafDx9Core::GgafDx9UntransformedActor* prm_pActor) {
        _pActor_Radical = prm_pActor;
    }

    MyLaserChip* getNext() {
        return (MyLaserChip*)_pNext;
    }

    MyLaserChip* getPrev() {
        return (MyLaserChip*)_pPrev;
    }

    virtual ~MyLaserChip();

};

}
#endif /*MYLASERCHIP_H_*/


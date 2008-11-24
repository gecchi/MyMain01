#ifndef MYLASERCHIP_H_
#define MYLASERCHIP_H_


class MyLaserChip : public DefaultDynaMeshActor {
public:

	DWORD _dwFrame_switchedToPlay;

	/**
	 * ���l�ʑ̃N���X
	 */
	class Tetrahedron {
	  public :
		float Ex, Ey, Ez;    // ���_���W1
		float Fx, Fy, Fz;    // ���_���W2
		float Gx, Gy, Gz;    // ���_���W3
		float Hx, Hy, Hz;    // ���_���W4
		Tetrahedron() {};
		~Tetrahedron() {};
	};

	static LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9_MyLaserChip;
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
	static Tetrahedron* _pTetra_EFGH;


	int _X_prevFrame;
	int _Y_prevFrame;
	int _Z_prevFrame;

	/** �ΏۃA�N�^�[ */
	GgafDx9UntransformedActor* _pActor_Radical;


	MyLaserChip(string prm_name, string prm_model);

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
 	void processOnHit(GgafActor* prm_pActor_Opponent);

	void setRadicalActor(GgafDx9UntransformedActor* prm_pActor) {
 		_pActor_Radical = prm_pActor;
 	}

	MyLaserChip* getNext() {
		return (MyLaserChip*)_pNext;
	};

	MyLaserChip* getPrev() {
		return (MyLaserChip*)_pPrev;
	};

 	virtual ~MyLaserChip();

};


#endif /*MYLASERCHIP_H_*/


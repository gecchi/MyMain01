#ifndef MYLASERCHIP_H_
#define MYLASERCHIP_H_


class MyLaserChip : public DefaultDynaMeshActor {
public:

	class Tetrahedron {
	  public :
		float x1, y1, z1;    // ���_���W1
		float x2, y2, z2;    // ���_���W2
		float x3, y3, z3;    // ���_���W3
		float x4, y4, z4;    // ���_���W4
		Tetrahedron() {};
		~Tetrahedron() {};
	};

	static LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9_MyLaserChip;
	static DWORD _dwVertexFormat;
	static DWORD _dwFVFSize;
	static DWORD _dwVertexNum;
	static int _aVertexIndexTetrahedron01_head[];
	static int _aVertexIndexTetrahedron02_head[];
	static int _aVertexIndexTetrahedron03_head[];
	static int _aVertexIndexTetrahedron04_head[];
	static int _iNum_VertexIndexTetrahedron01_head;
	static int _iNum_VertexIndexTetrahedron02_head;
	static int _iNum_VertexIndexTetrahedron03_head;
	static int _iNum_VertexIndexTetrahedron04_head;
	static Tetrahedron* _pTetra_tail;


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

 	virtual ~MyLaserChip();

};


#endif /*MYLASERCHIP_H_*/


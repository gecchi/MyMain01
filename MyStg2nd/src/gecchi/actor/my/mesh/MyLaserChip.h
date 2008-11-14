#ifndef MYLASERCHIP_H_
#define MYLASERCHIP_H_


class MyLaserChip : public DefaultMeshActor {

	struct TETRAHEDRON {
		float x1, y1, z1;    // ���_���W1
		float x2, y2, z2;    // ���_���W2
		float x3, y3, z3;    // ���_���W3
		float x4, y4, z4;    // ���_���W4
	};


public:
	static LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9_MyLaserChip;
	static DWORD _dwVertexFormat;
	static DWORD _dwFVFSize;
	static DWORD _dwVertexNum;
	static int _aVertexIndexTetrahedron01_head[];
	static int _aVertexIndexTetrahedron02_head[];
	static int _aVertexIndexTetrahedron03_head[];
	static int _aVertexIndexTetrahedron04_head[];
	static int _aVertexIndexTetrahedron01_tail[];
	static int _aVertexIndexTetrahedron02_tail[];
	static int _aVertexIndexTetrahedron03_tail[];
	static int _aVertexIndexTetrahedron04_tail[];



	TETRAHEDRON _tet_tail;

	int _tmpX;
	int _tmpY;
	int _tmpZ;


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
 	void processOnHit(GgafActor* prm_pActor_Opponent);


 	virtual ~MyLaserChip();

};


#endif /*MYLASERCHIP_H_*/


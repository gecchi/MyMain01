////////////////////////////////////////////////////////////////////////////////
// ���[�U�[�`�b�v�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/04/23
////////////////////////////////////////////////////////////////////////////////

//int g_kind; //�`�b�v��� 1:���� 2:���� 3:�擪 �i�������擪�͖������D��j

//float g_X; //��O���s���`�b�vX
//float g_Y; //��O���s���`�b�vY
//float g_Z; //��O���s���`�b�vZ

//bool g_RevPosZ; //Z���W�𔽓]���邩�ǂ���

int g_nVertexs;

//float4x4 g_matWorld;  //���g��World�ϊ��s��
//float4x4 g_matWorld_front;  //��O���s���`�b�v��World�ϊ��s��
bool g_RevPosZ001;
bool g_RevPosZ002;
bool g_RevPosZ003;
bool g_RevPosZ004;
bool g_RevPosZ005;
bool g_RevPosZ006;
bool g_RevPosZ007;
bool g_RevPosZ008;
//bool g_RevPosZ009;
//bool g_RevPosZ010;
//bool g_RevPosZ011;
//bool g_RevPosZ012;
//bool g_RevPosZ013;
//bool g_RevPosZ014;
//bool g_RevPosZ015;
//bool g_RevPosZ016;
int g_kind001;
int g_kind002;
int g_kind003;
int g_kind004;
int g_kind005;
int g_kind006;
int g_kind007;
int g_kind008;
//int g_kind009;
//int g_kind010;
//int g_kind011;
//int g_kind012;
//int g_kind013;
//int g_kind014;
//int g_kind015;
//int g_kind016;
float4x4 g_matWorld001;
float4x4 g_matWorld002;
float4x4 g_matWorld003;
float4x4 g_matWorld004;
float4x4 g_matWorld005;
float4x4 g_matWorld006;
float4x4 g_matWorld007;
float4x4 g_matWorld008;
//float4x4 g_matWorld009;
//float4x4 g_matWorld010;
//float4x4 g_matWorld011;
//float4x4 g_matWorld012;
//float4x4 g_matWorld013;
//float4x4 g_matWorld014;
//float4x4 g_matWorld015;
//float4x4 g_matWorld016;
float4x4 g_matWorld_front001;
float4x4 g_matWorld_front002;
float4x4 g_matWorld_front003;
float4x4 g_matWorld_front004;
float4x4 g_matWorld_front005;
float4x4 g_matWorld_front006;
float4x4 g_matWorld_front007;
float4x4 g_matWorld_front008;
//float4x4 g_matWorld_front009;
//float4x4 g_matWorld_front010;
//float4x4 g_matWorld_front011;
//float4x4 g_matWorld_front012;
//float4x4 g_matWorld_front013;
//float4x4 g_matWorld_front014;
//float4x4 g_matWorld_front015;
//float4x4 g_matWorld_front016;

float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float3 g_LightDirection; // ���C�g�̕���
float4 g_LightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_LightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_MaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//���[�U�[�`�b�v���_�V�F�[�_�[
OUT_VS GgafDx9VS_LaserChip(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float  prm_index  : PSIZE ,    // ���f���̒��_�ԍ�
      float3 prm_normal : NORMAL,        // �@���ł͂Ȃ��ĂȂ�ƁAx�v�f�ɒ��_�ԍ��I
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV
) {

	OUT_VS out_vs = (OUT_VS)0;

	int g_cnt_vertec = (int)prm_index;

	//���_�v�Z
	float4x4 matWorld;
	float4x4 matWorld_front;
	int kind;
	bool revPosZ;



	if (64 > g_cnt_vertec) {
		if (32 > g_cnt_vertec) {
			if (16 > g_cnt_vertec) {
				matWorld = g_matWorld001;
				matWorld_front = g_matWorld_front001;
				kind = g_kind001;
				revPosZ = g_RevPosZ001;
			} else {
				matWorld = g_matWorld002;
				matWorld_front = g_matWorld_front002;
				kind = g_kind002;
				revPosZ = g_RevPosZ002;
			}
		} else {
			if (48 > g_cnt_vertec) {
				matWorld = g_matWorld003;
				matWorld_front = g_matWorld_front003;
				kind = g_kind003;
				revPosZ = g_RevPosZ003;
			} else {
				matWorld = g_matWorld004;
				matWorld_front = g_matWorld_front004;
				kind = g_kind004;
				revPosZ = g_RevPosZ004;
			}
		}
	} else {
		if (96 > g_cnt_vertec) {
			if (80 > g_cnt_vertec) {
				matWorld = g_matWorld005;
				matWorld_front = g_matWorld_front005;
				kind = g_kind005;
				revPosZ = g_RevPosZ005;
			} else {
				matWorld = g_matWorld006;
				matWorld_front = g_matWorld_front006;
				kind = g_kind006;
				revPosZ = g_RevPosZ006;
			}
		} else {
			if (112 > g_cnt_vertec) {
				matWorld = g_matWorld007;
				matWorld_front = g_matWorld_front007;
				kind = g_kind007;
				revPosZ = g_RevPosZ007;
			} else {
				matWorld = g_matWorld008;
				matWorld_front = g_matWorld_front008;
				kind = g_kind008;
				revPosZ = g_RevPosZ008;
			}
		}
	}



	//float4 posWorld = mul( prm_pos, matWorld );               // World�ϊ�







//
	if (revPosZ == true) {
		prm_pos.z = -prm_pos.z;
	}
//
//	if (g_Y - g_matWorld._42 < 0) {
//		prm_pos.y = -prm_pos.y;
//	}
//
	//�قڐ^���Ȃ�H�͂���Ȃ� TODO
//	if (abs(g_Z - matWorld._43) < 1.5) {
//		if (abs(g_Y - matWorld._42) < 1.0) {
//			prm_pos.z = 0;
//		}
//	}

	float4 posWorld;
	if (prm_pos.x > 0) {
//		float4x4 matWorld_tmp = g_matWorld_front; 
//		matWorld_tmp._41 = matWorld_front._41;  // ��O���̃`�b�v���W�ւ�������
//		matWorld_tmp._42 = matWorld_front._42; 
//		matWorld_tmp._43 = matWorld_front._43; 
		posWorld = mul( prm_pos, matWorld_front );      // World�ϊ�
	} else {
		//���_�v�Z
		posWorld = mul( prm_pos, matWorld );        // World�ϊ�
	}
	float4 posWorldView = mul(posWorld    , g_matView);  // View�ϊ�
	out_vs.pos          = mul(posWorldView, g_matProj);  // �ˉe�ϊ�

	//UV
	if (kind == 2) {
		out_vs.uv = prm_uv;
	} else if (kind == 1) {
		out_vs.uv.x = prm_uv.x - 0.5;
		out_vs.uv.y = prm_uv.y;
	} else if (kind == 3) {
		out_vs.uv.x = prm_uv.x;
		out_vs.uv.y = prm_uv.y - 0.5;
	} else {
		//�����`�悵�����Ȃ�
		out_vs.uv.x = 0.1;
		out_vs.uv.y = 0.1;
	}
	//g_cnt_vertec++;
	return out_vs;
}

float4 GgafDx9PS_LaserChip(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {

	float4 tex_color = tex2D( MyTextureSampler, prm_uv);
	return tex_color;
}


technique LaserChipTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   //���Z����
		DestBlend = One;
		VertexShader = compile vs_2_0 GgafDx9VS_LaserChip();
		PixelShader  = compile ps_2_0 GgafDx9PS_LaserChip();
	}

}




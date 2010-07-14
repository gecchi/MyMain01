////////////////////////////////////////////////////////////////////////////////
// ���[�U�[�`�b�v�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/04/23
////////////////////////////////////////////////////////////////////////////////

/* 
���[�U�[�`�b�v�͎��̂悤�ȃ��b�V���ł��邱�Ƃ��O��

 Mesh {
  8;
  0.100000;0.000000;0.050000;,
  0.000010;0.000000;-0.050000;,
  0.100000;0.000000;-0.050000;,
  0.000010;0.000000;0.050000;,
  0.100000;-0.050000;0.000000;,
  0.000010;0.050000;0.000000;,
  0.100000;0.050000;0.000000;,
  0.000010;-0.050000;0.000000;;
  4;
  3;0,1,2;,
  3;1,0,3;,
  3;4,5,6;,
  3;5,4,7;;

  MeshNormals {
   2;
   0.000000;-1.000000;0.000000;,
   0.000000;0.000000;-1.000000;;
   4;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;;
  }

  MeshTextureCoords {
   8;
   0.532110;0.000000;,
   0.501000;0.999000;,
   0.533110;0.999000;,
   0.500000;0.000000;,
   0.532110;0.000000;,
   0.501000;0.999000;,
   0.533110;0.999000;,
   0.500000;0.000000;;
  }

*/
float g_PowerBlink;   
float g_BlinkThreshold;
float g_MasterAlpha;
float g_zf;

//int g_kind; //�`�b�v��� 1:���� 2:���� 3:�擪 �i�������擪�͖������D��j
int g_kind001;
int g_kind002;
int g_kind003;
int g_kind004;
int g_kind005;
int g_kind006;
int g_kind007;
int g_kind008;
int g_kind009;
int g_kind010;
int g_kind011;
float4x4 g_matWorld001;
float4x4 g_matWorld002;
float4x4 g_matWorld003;
float4x4 g_matWorld004;
float4x4 g_matWorld005;
float4x4 g_matWorld006;
float4x4 g_matWorld007;
float4x4 g_matWorld008;
float4x4 g_matWorld009;
float4x4 g_matWorld010;
float4x4 g_matWorld011;
float4x4 g_matWorld_front001;
float4x4 g_matWorld_front002;
float4x4 g_matWorld_front003;
float4x4 g_matWorld_front004;
float4x4 g_matWorld_front005;
float4x4 g_matWorld_front006;
float4x4 g_matWorld_front007;
float4x4 g_matWorld_front008;
float4x4 g_matWorld_front009;
float4x4 g_matWorld_front010;
float4x4 g_matWorld_front011;

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
	float4 col    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//���[�U�[�`�b�v���_�V�F�[�_�[
OUT_VS GgafDx9VS_LaserChip(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float  prm_index  : PSIZE ,    // PSIZE�ł͂Ȃ��ĂȂ�ƃ��f���̒��_�ԍ�
      float3 prm_normal : NORMAL,        
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV
) {

	OUT_VS out_vs = (OUT_VS)0;

	int index = (int)prm_index;

	//���_�v�Z
	float4x4 matWorld;
	float4x4 matWorld_front;
	int kind;

	if (index == 0) {
		matWorld = g_matWorld001;
		matWorld_front = g_matWorld_front001;
		kind = g_kind001;
	} else if (index == 1) {
		matWorld = g_matWorld002;
		matWorld_front = g_matWorld_front002;
		kind = g_kind002;
	} else if (index == 2) {
		matWorld = g_matWorld003;
		matWorld_front = g_matWorld_front003;
		kind = g_kind003;
	} else if (index == 3) {
		matWorld = g_matWorld004;
		matWorld_front = g_matWorld_front004;
		kind = g_kind004;
	} else if (index == 4) {
		matWorld = g_matWorld005;
		matWorld_front = g_matWorld_front005;
		kind = g_kind005;
	} else if (index == 5) {
		matWorld = g_matWorld006;
		matWorld_front = g_matWorld_front006;
		kind = g_kind006;
	} else if (index == 6) {
		matWorld = g_matWorld007;
		matWorld_front = g_matWorld_front007;
		kind = g_kind007;
	} else if (index == 7) {
		matWorld = g_matWorld008;
		matWorld_front = g_matWorld_front008;
		kind = g_kind008;
	} else if (index == 8) {
		matWorld = g_matWorld009;
		matWorld_front = g_matWorld_front009;
		kind = g_kind009;
	} else if (index == 9) {
		matWorld = g_matWorld010;
		matWorld_front = g_matWorld_front010;
		kind = g_kind010;
	} else {
		matWorld = g_matWorld011;
		matWorld_front = g_matWorld_front011;
		kind = g_kind011;
	} 
	float4 posWorld;
	if (prm_pos.x > 0.05f) {    // < prm_pos.x > 0.000010f �ɂ��]�T��������������
//TODO:20090806�A�C�f�B�A
//���ݐ擪�̃`�b�v�͉����\������Ȃ��̂�
//�Q�{����90�x��]���āA�擪��p�e�N�X�`�����𒣂�΁A����ۂ��������̂ł͂Ȃ���
//�E�E�E�P�ɂQ�{90�x��]���Ă��߂������A���ԂɂȂ邾��

//		if (kind == 4) {  //3�ł͂Ȃ���
//         x =  cos90*_Xorg + sin90*_Yorg  = 0*_Xorg + 1*_Yorg   =  Y
//         y = -sin90*_Xorg + cos90*_Yorg  = -1*_Xorg + 0*_Yorg  = -X

//			sin
//		   �i�C����
//		}
		//���_�v�Z
//		if (kind == 4) {  //3�ł͂Ȃ���
//			float tmpy = prm_pos.y;
//			prm_pos.y = -8.0 * prm_pos.z;
//			prm_pos.z = 8.0 * tmpy;
//		}

		
		prm_pos.x = 0;
		if (kind == 4) {  //3�ł͂Ȃ���
			prm_pos.y = 0;
			prm_pos.z = 0;
		} 
		// ��O���̃`�b�v���W�ւ�������
		posWorld = mul( prm_pos, matWorld_front );      // World�ϊ�
	} else {
//		if (kind == 1) {  
//			prm_pos.x = 0;
//			prm_pos.y = 0;
//			prm_pos.z = 0;
//		} 
		//���_�v�Z
		posWorld = mul( prm_pos, matWorld );        // World�ϊ�
	}
	out_vs.pos = mul(mul(posWorld, g_matView), g_matProj);  // View�ϊ��ˉe�ϊ�

	//UV�ݒ�
    //���[�U�[�`�b�v��� �ɂ��āB
    //
    //      -==========<>            ���[�U�[��
    //
    //      -= === === === <>        ����Ȃӂ��ɕ��f����Ă��܂��B
    //
    //    | -=|===|===|===|<> |     ���}�̓��[�U�[���I�u�W�F�N�g�ŋ�؂�������̐}
    //
    //    <--><--><--><--><-->^
    //    ^   ^   ^   ^   ^   |
    //    |   |   |   |   |   |
    //    |   |   |   |   |    `----- 4:��[�`�b�v(��\���ŁA���Ԑ擪�`�b�v��\�����邽�߂����ɑ���)
    //    |   |   |   |    `----- 3:���Ԑ擪�`�b�v(�\�����������̐擪)
    //    |   |   |    `----- 2:���ԃ`�b�v
    //    |   |    `----- 2:���ԃ`�b�v
    //    |    `----- 2:���ԃ`�b�v
    //     `----- 1:�����`�b�v
    //
    //�擪�Ɛ�[�Ƃ������t�ŋ�ʂ��Ă��܂��B
	if (kind == 2) {
		//���ԃ`�b�v
		out_vs.uv = prm_uv;  
	} else if (kind == 1) {
		//�����`�b�v
		out_vs.uv.x = prm_uv.x < 0.51f ? 0.0f : prm_uv.x;
		out_vs.uv.y = prm_uv.y;
	} else if (kind == 3) {
		//���Ԑ擪�`�b�v
		out_vs.uv.x = prm_uv.x > 0.51f ? 1.0f : prm_uv.x;
		out_vs.uv.y = prm_uv.y;
	} else {
		//��[�`�b�v
		//�����`�悵�����Ȃ�
		out_vs.uv.x = 0;
		out_vs.uv.y = 1;
	}
	//���t�H�O
	out_vs.col = float4(1.0, 1.0, 1.0, 1.0);
	if (out_vs.pos.z > g_zf*0.5) { // �ŉ��� 1/2 ��艜�̏ꍇ���X�ɓ�����
    	out_vs.col.a *= (-1.0/(g_zf*0.5)*out_vs.pos.z + 2.0);
	} 
	out_vs.col.a *= g_MasterAlpha;

//	if (out_vs.pos.z > g_zf*0.75) { //�ŉ��� 3/4 ��艜�̏ꍇ���X�ɓ�����
//    	out_vs.col.a *= (-1.0/(g_zf*0.25)*out_vs.pos.z + 4.0);
//	}

	//�ȈՃt�H�O
//	out_vs.col.a = 1.0/(g_zf - (g_zf*0.5))*out_vs.pos.z - 1.0; // 1/2 ��艜�̏ꍇ���X�ɓ�����
	//out_vs.col.a = 1.0/(g_zf - (g_zf*0.75))*out_vs.pos.z - 3.0;  // 3/4 ��艜�̏ꍇ���X�ɓ�����

	return out_vs;
}

float4 GgafDx9PS_LaserChip( 
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0
) : COLOR  {

	float4 tex_color = tex2D( MyTextureSampler, prm_uv);
	float4 out_color = tex_color * prm_col;
	return out_color;
}


technique LaserChipTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   //���Z����
		DestBlend = One;

//		SrcBlend  = SrcAlpha;
//		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_LaserChip();
		PixelShader  = compile ps_2_0 GgafDx9PS_LaserChip();
	}

}




#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDxMeshSetModel�p�V�F�[�_�[
// �y�T�v�z
// ���_�o�b�t�@�ɁA�������f���L�����̒��_��񂪁A�������J��Ԃ��l�ߍ���ł���B
// �X�e�[�g�⃌�W�X�^�̍X�V���s�킸�A�P��� DrawIndexedPrimitive�ŁA�ő�
// �P�Q�I�u�W�F�N�g�܂ŕ`��B��������_���B
// ��ʂ̓����G��e�ɂ́A���̃V�F�[�_�[�ŕ`�悷�邱�ƂƂ���B
// �A���A�P�I�u�W�F�N�g�ɂ��}�e���A���ݒ�͂P�����Ƃ�������������B
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

//�G���[����̂��߂ɂƂ肠�����ǉ���ł����Ƃ���
float3 g_posCam_World;
float g_specular;
float g_specular_power;


float g_zf;
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
// ���C�g�̕���
float3 g_vecLightFrom_World;
// Ambien���C�g�F�i���ːF�j
float4 g_colLightAmbient;
// Diffuse���C�g�F�i���ːF�j  
float4 g_colLightDiffuse;  
//View�ϊ��s��
float4x4 g_matView; 
//�ˉe�ϊ��s��  
float4x4 g_matProj;  
//���[���h�ϊ��s��
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
float4x4 g_matWorld012;
float4x4 g_matWorld013;
float4x4 g_matWorld014;
float4x4 g_matWorld015;
float4x4 g_matWorld016;
float4x4 g_matWorld017;
float4x4 g_matWorld018;
float4x4 g_matWorld019;
float4x4 g_matWorld020;
float4x4 g_matWorld021;
float4x4 g_matWorld022;
float4x4 g_matWorld023;
float4x4 g_matWorld024;
float4x4 g_matWorld025;
float4x4 g_matWorld026;
float4x4 g_matWorld027;



//�e�N�X�`���̃T���v��(s0���W�X�^)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 color    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//���_�V�F�[�_�[
OUT_VS GgafDxVS_SingleLaser(
      float4 prm_posModel_Local    : POSITION,      // ���f���̒��_
      float  prm_index  : PSIZE ,        // ���f���̃C���f�b�N�X�i���ڂ̃I�u�W�F�N�g���H�j
      float2 prm_uv     : TEXCOORD0      // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;

	//���_�v�Z
	float4x4 matWorld;
	if (index == 0) {		
		matWorld = g_matWorld001;	
	} else if (index == 1) {		
		matWorld = g_matWorld002;	
	} else if (index == 2) {		
		matWorld = g_matWorld003;	
	} else if (index == 3) {		
		matWorld = g_matWorld004;	
	} else if (index == 4) {		
		matWorld = g_matWorld005;	
	} else if (index == 5) {		
		matWorld = g_matWorld006;	
	} else if (index == 6) {		
		matWorld = g_matWorld007;	
	} else if (index == 7) {		
		matWorld = g_matWorld008;	
	} else if (index == 8) {		
		matWorld = g_matWorld009;	
	} else if (index == 9) {		
		matWorld = g_matWorld010;	
	} else if (index == 10) {		
		matWorld = g_matWorld011;	
	} else if (index == 11) {		
		matWorld = g_matWorld012;	
	} else if (index == 12) {		
		matWorld = g_matWorld013;	
	} else if (index == 13) {		
		matWorld = g_matWorld014;	
	} else if (index == 14) {		
		matWorld = g_matWorld015;	
	} else if (index == 15) {		
		matWorld = g_matWorld016;	
	} else if (index == 16) {		
		matWorld = g_matWorld017;	
	} else if (index == 17) {		
		matWorld = g_matWorld018;	
	} else if (index == 18) {		
		matWorld = g_matWorld019;	
	} else if (index == 19) {		
		matWorld = g_matWorld020;	
	} else if (index == 20) {		
		matWorld = g_matWorld021;	
	} else if (index == 21) {		
		matWorld = g_matWorld022;	
	} else if (index == 22) {		
		matWorld = g_matWorld023;	
	} else if (index == 23) {		
		matWorld = g_matWorld024;	
	} else if (index == 24) {		
		matWorld = g_matWorld025;	
	} else if (index == 25) {		
		matWorld = g_matWorld026;
    }	
//	} else {		
//		matWorld = g_matWorld027;	
//	} 


	//World*View*�ˉe�ϊ�
	out_vs.posModel_Proj = mul(mul(mul( prm_posModel_Local, matWorld ), g_matView ), g_matProj);
	//UV�͂��̂܂�
	out_vs.uv = prm_uv;
	//���t�H�O
    float c = 1.3-((out_vs.posModel_Proj.z)/g_zf);
	out_vs.color = (c < 0.5  ? 0.5 : c);
	//out_vs.color = (c < 0.5  ? 0.5 : c);

//	out_vs.color = float4(1.0, 1.0, 1.0, 1.0);
//    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
//        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
//    }
	out_vs.color.a *= g_alpha_master;
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {   
//        out_vs.posModel_Proj.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }
	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDxPS_SingleLaser(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color    : COLOR0
) : COLOR  {

	float4 colTex = tex2D( MyTextureSampler, prm_uv);
	float4 colOut = colTex * prm_color;
	return colOut;
}

technique SingleLaserTechnique
{
	// s0���W�X�^				:	2D�e�N�X�`��
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   //���Z����
		DestBlend = One;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;
		VertexShader = compile VS_VERSION GgafDxVS_SingleLaser();
		PixelShader  = compile PS_VERSION GgafDxPS_SingleLaser();
	}
}


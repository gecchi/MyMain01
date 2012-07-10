#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// author : Masatoshi Tsuge
// date:2010/12/24
////////////////////////////////////////////////////////////////////////////////

//�G���[����̂��߂ɂƂ肠�����ǉ���ł����Ƃ���
float3 g_posCam_World;
float g_reflectance;

float g_specular;
float g_specular_power;



/** �J������World�ʒu */
//float3 pos_camera; 

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
//float4x4 g_matWorld016;
//�I�u�W�F�N�g�̃}�e���A���F�iDiffuse���ːF�ƁAAmbien���ːF���ʁj
float4 g_colMaterialDiffuse001;
float4 g_colMaterialDiffuse002;
float4 g_colMaterialDiffuse003;
float4 g_colMaterialDiffuse004;
float4 g_colMaterialDiffuse005;
float4 g_colMaterialDiffuse006;
float4 g_colMaterialDiffuse007;
float4 g_colMaterialDiffuse008;
float4 g_colMaterialDiffuse009;
float4 g_colMaterialDiffuse010;
float4 g_colMaterialDiffuse011;
float4 g_colMaterialDiffuse012;
float4 g_colMaterialDiffuse013;
float4 g_colMaterialDiffuse014;
float4 g_colMaterialDiffuse015;
//float4 g_colMaterialDiffuse016;

//�e�N�X�`���̃T���v��(s0���W�X�^)
//sampler MyTextureSampler : register(s0);
sampler MyTextureSampler : register(s0);
sampler CubeMapTextureSampler : register(s1);

struct OUT_VS {
    float4 posModel_Proj   : POSITION;
	float2 uv     : TEXCOORD0;
	float4 color    : COLOR0;
    float3 vecNormal_World : TEXCOORD1;   // ���[���h�ϊ������@��
    float3 vecEye_World    : TEXCOORD2;   //���_ -> ���_ �x�N�g��
};


///////////////////////////////////////////////////////////////////////////

//���_�V�F�[�_�[
OUT_VS GgafDxVS_CubeMapMeshSet(
      float4 prm_posModel_Local    : POSITION,      // ���f���̒��_
      float  prm_index  : PSIZE ,        // ���f���̃C���f�b�N�X�i���ڂ̃I�u�W�F�N�g���H�j
      float3 prm_vecNormal_Local : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv     : TEXCOORD0      // ���f���̒��_��UV
) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;

	//���_�v�Z
	float4x4 matWorld;
	float4 colMaterialDiffuse;

	if (index == 0) {
		matWorld = g_matWorld001;
		colMaterialDiffuse = g_colMaterialDiffuse001;
	} else if (index == 1) {
		matWorld = g_matWorld002;
		colMaterialDiffuse = g_colMaterialDiffuse002;
	} else if (index == 2) {
		matWorld = g_matWorld003;
		colMaterialDiffuse = g_colMaterialDiffuse003;
	} else if (index == 3) {
		matWorld = g_matWorld004;
		colMaterialDiffuse = g_colMaterialDiffuse004;
	} else if (index == 4) {
		matWorld = g_matWorld005;
		colMaterialDiffuse = g_colMaterialDiffuse005;
	} else if (index == 5) {
		matWorld = g_matWorld006;
		colMaterialDiffuse = g_colMaterialDiffuse006;
	} else if (index == 6) {
		matWorld = g_matWorld007;
		colMaterialDiffuse = g_colMaterialDiffuse007;
	} else if (index == 7) {
		matWorld = g_matWorld008;
		colMaterialDiffuse = g_colMaterialDiffuse008;
	} else if (index == 8) {
		matWorld = g_matWorld009;
		colMaterialDiffuse = g_colMaterialDiffuse009;
	} else if (index == 9) {
		matWorld = g_matWorld010;
		colMaterialDiffuse = g_colMaterialDiffuse010;
	} else if (index == 10) {
		matWorld = g_matWorld011;
		colMaterialDiffuse = g_colMaterialDiffuse011;
	} else if (index == 11) {
		matWorld = g_matWorld012;
		colMaterialDiffuse = g_colMaterialDiffuse012;
	} else if (index == 12) {
		matWorld = g_matWorld013;
		colMaterialDiffuse = g_colMaterialDiffuse013;
	} else if (index == 13) {
		matWorld = g_matWorld014;
		colMaterialDiffuse = g_colMaterialDiffuse014;
	} else { //if (index == 14) {
		matWorld = g_matWorld015;
		colMaterialDiffuse = g_colMaterialDiffuse015;
	}
//	} else {
//		matWorld = g_matWorld016;
//		colMaterialDiffuse = g_colMaterialDiffuse016;
//	}

	//���_�v�Z
    float4 posModel_World = mul(prm_posModel_Local, matWorld);
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*�ˉe
    //UV�v�Z
    out_vs.uv = prm_uv;  //���̂܂�
    //���_�J���[�v�Z
    //�@���� World �ϊ����Đ��K��
    out_vs.vecNormal_World = normalize(mul(prm_vecNormal_Local, matWorld));     
    //�@���ƁA�g�U�������̓��ς��烉�C�g���ˊp�����߁A�ʂɑ΂���g�U���̌����������߂�B
    float power = max(dot(out_vs.vecNormal_World, -g_vecLightFrom_World ), 0);      
    //�g�U���F�Ɍ��������悶�A�����F�����Z���A�S�̂��}�e���A���F���|����B
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * colMaterialDiffuse;
    //�u���_���J�������_�v�����x�N�g��                                                        
    out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);
    //���̓}�e���A�������ŗD��Ƃ���i�㏑������j
    out_vs.color.a = colMaterialDiffuse.a;
    //���t�H�O
    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
    }
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {   
//        out_vs.posModel_Proj.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }
	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDxPS_CubeMapMeshSet(       
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color  : COLOR0,
    float3 prm_vecNormal_World : TEXCOORD1,
    float3 prm_vecEye_World    : TEXCOORD2   //���_ -> ���_ �x�N�g��
) : COLOR  {
	float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-prm_vecEye_World, prm_vecNormal_World));
    float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

    float s = 0.0f; //�X�y�L��������
    if (g_specular_power != 0) {
        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g���j
        float3 vecHarf = normalize(prm_vecEye_World + (-g_vecLightFrom_World));
        //�n�[�t�x�N�g���Ɩ@���̓��ς��X�y�L��������v�Z
        s = pow( max(0.0f, dot(prm_vecNormal_World, vecHarf)), g_specular ) * g_specular_power;
    }

    float4 out_color = (colTex2D * prm_color) + (colTexCube*g_reflectance) + s;
    //Blinker���l��
	if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
	} 

    out_color.a = prm_color.a * colTex2D.a * colTexCube.a * g_alpha_master; 
	return out_color;
}


float4 PS_Flush( 
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_color * FLUSH_COLOR;
    out_color.a *= g_alpha_master;
	return out_color;
}

technique CubeMapMeshSetTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMeshSet();
		PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMeshSet();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMeshSet();
		PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMeshSet();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMeshSet();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}

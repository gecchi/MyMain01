#include "GgafEffectConst.fxh" 
float4x4 g_matWorld;  
float4x4 g_matView;   
float4x4 g_matProj;   

float3 g_vecLightDirection; 
float4 g_colLightAmbient;   
float4 g_colLightDiffuse;   

float4 g_colMaterialDiffuse;

float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;

sampler MyTextureSampler : register(s0);


struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 color    : COLOR0;
};


OUT_VS GgafDxVS_GroundMesh(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float3 prm_normal : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv     : TEXCOORD0      // ���f���̒��_��UV
) {
	OUT_VS out_vs = (OUT_VS)0;

	//���_�v�Z
	out_vs.pos = mul( mul( mul(prm_pos, g_matWorld), g_matView), g_matProj);  //World*View*�ˉe�ϊ�
	//UV�͂��̂܂�
	out_vs.uv = prm_uv;

    //���_�J���[�v�Z

	//�@���� World �ϊ����Đ��K��
    float3 normal = normalize(mul(prm_normal, g_matWorld)); 	
    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
	float power = max(dot(normal, -g_vecLightDirection ), 0);      
	//Ambient���C�g�F�ADiffuse���C�g�F�ADiffuse���C�g�����A�}�e���A���F ���l�������J���[�쐬�B      
	out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse;
	//���t�H�O
	out_vs.color.a = g_colMaterialDiffuse.a;
    if (out_vs.pos.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
        out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
    }

 //�J�����̈ʒu(0,0,-57.1259)
//���͐��E��(-1.0f, -1.0f, 0 )�Ƃ����_����(1.0f, 1.0f, 1,0f)�Ƃ����_��Ίp���Ƃ��钼���̂̐��E�Ɏ��߂��Ă��܂��Ă��܂�

//w�͎ˉe��ԁi�������ԁj�ɂ��钸�_���W������Ŋ��邱�Ƃɂ��
//�u���_���X�N���[���ɓ��e���邽�߂̗����̗̂̈�i-1��x��1�A-1��y��1������0��z��1�j�ɔ[�߂�v
//�Ƃ�����؂Ȗ�ڂ����Ă��܂��Bw���u�����n�v�ƌĂ΂��̂́A
//��̗�̂悤�Ɏ�����ɃJ�����̎��������ɍL�����Ă��钸�_�𓯂�XY���W�ɓ��e���邽�߂ł��B


	if ( out_vs.pos.z < 60) {
		out_vs.color.a = (out_vs.pos.z + 1.0)  / (57.1259*2);
//1 - (out_vs.pos.z / 57.1259);
	}
	return out_vs;
}

float4 GgafDxPS_GroundMesh(
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_color;

    //Blinker���l��
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
	} 
	//�}�X�^�[��
	out_color.a *= g_alpha_master;
	return out_color;
}


technique GroundMeshTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		VertexShader = compile VS_VERSION GgafDxVS_GroundMesh();
		PixelShader  = compile PS_VERSION GgafDxPS_GroundMesh();
	}
}


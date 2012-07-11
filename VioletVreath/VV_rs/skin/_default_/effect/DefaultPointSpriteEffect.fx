#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDxMeshModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float g_dist_CamZ_default;
float g_dist_VpFrontPlane; //�قڎ��_����̋���
float g_zn;
float g_zf;
float g_TexSize;  //�ǂݍ��񂾃e�N�X�`���i�����`���O��j�̕��e�N�Z����
int g_TextureSplitRowcol; //�e�N�X�`���̏c���������B
                            //1�F�c���P���������������B
                            //2�F�c���Q�������S�̃A�j���p�^�[��
                            //3�F�c���R�������X�̃A�j���p�^�[��
float g_offset_u;        //�e�N�X�`��U���W����
float g_offset_v;         //�e�N�X�`��V���W����
float g_UvFlipPtnNo;

float3 g_vecLightFrom_World; // ���C�g�̕���
float4 g_colLightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_colLightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_colMaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;

//s0���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//texture g_diffuseMap;
//sampler MyTextureSampler = sampler_state {
//	texture = <g_diffuseMap>;
//};

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj : POSITION;
	float  psize         : PSIZE;
	float4 color         : COLOR0;
	float4 uv_ps         : COLOR1;  //�X�y�L������ׂ��ĕ\��������UV���W����̏���PS�ɓn��
};


///////////////////////////////////////////////////////////////////////////
////http://wlog.flatlib.jp/?blogid=1&query=dxgi
//// �p�b�N���ꂽ�J���[��W�J����
//float3 pf_to_float3( float pf )
//{
//    uint    data= asint( pf );
//    float3  rcol;
//    const float tof= 1.0f/255.0f;
//    rcol.x= ( data      & 255) * tof;
//    rcol.y= ((data>> 8) & 255) * tof;
//    rcol.z= ((data>>16) & 255) * tof;
//    return  rcol;
//}
//
//// �J���[�� float1 �Ɉ��k����
//float float3_to_pf( float3 color )
//{
//    uint3   bcol= (uint3)( color * 255.0f ) & 255;
//    return  asfloat( (bcol.z << 16) + (bcol.y << 8) + bcol.x );
//}


//���b�V���W�����_�V�F�[�_�[
OUT_VS GgafDxVS_DefaultPointSprite(
    float4 prm_posModel_Local : POSITION,  //�|�C���g�X�v���C�g�̃|�C���g�Q
    float  prm_psize_rate     : PSIZE,     //PSIZE�ł͖����āA�X�P�[���̗�(0.0�`N (1.0=���{)) �������Ă���
    float4 prm_color          : COLOR0,     //�I�u�W�F�N�g�̃J���[
    float2 prm_ptn_no         : TEXCOORD0 //UV�ł͖����āAprm_ptn_no.x�ɂ́A�\���������A�j���[�V�����p�^�[���ԍ������ߍ���ł���
) {
	OUT_VS out_vs = (OUT_VS)0;
    float4 posModel_View = mul(mul(prm_posModel_Local, g_matWorld), g_matView); 
	float dep = posModel_View.z + 1.0; //+1.0�̈Ӗ���
                                    //VIEW�ϊ���(0.0, 0.0, -1.0) ���� (0.0, 0.0, 0.0) �����Ă��邽�߁A
                                    //�����ɉ�����B
	out_vs.posModel_Proj = mul(posModel_View, g_matProj);  //�ˉe�ϊ�
	out_vs.psize = (g_TexSize / g_TextureSplitRowcol) * (g_dist_CamZ_default / dep) * prm_psize_rate;
    //psize�͉�ʏ�̃|�C���g �X�v���C�g�̕� (�s�N�Z���P��) 

	//�X�y�L�����Z�}���e�b�N�X(COLOR1)��ׂ��ĕ\��������UV���W����̏���PS�ɓn��
	int ptnno = prm_ptn_no.x + g_UvFlipPtnNo;
    if (ptnno >= g_TextureSplitRowcol*g_TextureSplitRowcol) {
        ptnno -= (g_TextureSplitRowcol*g_TextureSplitRowcol);
    }
	out_vs.uv_ps.x = fmod(ptnno, g_TextureSplitRowcol) / g_TextureSplitRowcol;
	out_vs.uv_ps.y = trunc(ptnno / g_TextureSplitRowcol) / g_TextureSplitRowcol;

//    int ptnno = ((int)(prm_ptn_no.x + g_UvFlipPtnNo)) % (g_TextureSplitRowcol*g_TextureSplitRowcol);
//	//�X�y�L����(COLOR1)��ׂ��ĕ\��������UV���W����̏���PS�ɓn��
//	out_vs.uv_ps.x = ((int)(ptnno % g_TextureSplitRowcol)) * (1.0 / g_TextureSplitRowcol);
//	out_vs.uv_ps.y = ((int)(ptnno / g_TextureSplitRowcol)) * (1.0 / g_TextureSplitRowcol);

	out_vs.color = prm_color;
    if (out_vs.posModel_Proj.z > g_zf*0.98) {   
        out_vs.posModel_Proj.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
    }
	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDxPS_DefaultPointSprite(
	float2 prm_uv_pointsprite	  : TEXCOORD0,   //(0.F, 0.F), (0.F, 1.F), (1.F, 0.F), (1.F, 1.F)������   
	float4 prm_color                : COLOR0,
	float4 prm_uv_ps              : COLOR1  //�X�y�L�����ł͖����āA�\��������UV���W����̏�񂪓����Ă���
) : COLOR  {
	float2 uv = (float2)0;
	uv.x = prm_uv_pointsprite.x * (1.0 / g_TextureSplitRowcol) + prm_uv_ps.x;
	uv.y = prm_uv_pointsprite.y * (1.0 / g_TextureSplitRowcol) + prm_uv_ps.y;
	float4 colOut = tex2D( MyTextureSampler, uv) * prm_color * g_colMaterialDiffuse;
	colOut.a *= g_alpha_master; 
	return colOut;
}


float4 PS_Flush(
	float2 prm_uv_pointsprite	  : TEXCOORD0,     
	float4 prm_color                : COLOR0,
	float4 prm_uv_ps              : COLOR1
) : COLOR  {
	float2 uv = (float2)0;
	uv.x = prm_uv_pointsprite.x * (1.0 / g_TextureSplitRowcol) + prm_uv_ps.x;
	uv.y = prm_uv_pointsprite.y * (1.0 / g_TextureSplitRowcol) + prm_uv_ps.y;
	float4 colOut = tex2D( MyTextureSampler, uv) * prm_color * FLUSH_COLOR * g_colMaterialDiffuse;
	colOut.a *= g_alpha_master; 
	return colOut;
}

technique DefaultPointSpriteTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultPointSprite();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultPointSprite();
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
		VertexShader = compile VS_VERSION GgafDxVS_DefaultPointSprite();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultPointSprite();
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
		VertexShader = compile VS_VERSION GgafDxVS_DefaultPointSprite();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}


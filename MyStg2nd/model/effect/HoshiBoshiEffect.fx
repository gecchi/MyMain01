#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AMeshModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float g_fX_MyShip;
float g_fY_MyShip;
float g_fZ_MyShip;
float g_far_rate;

float g_dist_CamZ_default;
float g_dist_VpFrontPlane; //�قڎ��_����̋���
float g_zn;
float g_zf;
float g_TexSize;  //�ǂݍ��񂾃e�N�X�`���i�����`���O��j�̕��e�N�Z����
int g_TextureSplitRowcol; //�e�N�X�`���̏c���������B
                            //1�F�c���P���������������B
                            //2�F�c���Q�������S�̃A�j���p�^�[��
                            //3�F�c���R�������X�̃A�j���p�^�[��
float g_offsetU;        //�e�N�X�`��U���W����
float g_offsetV;         //�e�N�X�`��V���W����
int g_UvFlipPtnNo;

float3 g_vecLightDirection; // ���C�g�̕���
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
    float4 pos    : POSITION;
	float  psize  : PSIZE;
	float4 color    : COLOR0;
	float4 uv_ps  : COLOR1;  //�X�y�L������ׂ��ĕ\��������UV���W����̏���PS�ɓn��
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
OUT_VS VS_HoshiBoshi(
      float4 prm_pos         : POSITION,  //�|�C���g�X�v���C�g�̃|�C���g�Q
      float  prm_psize_rate  : PSIZE,     //PSIZE�̓|�C���g�T�C�Y�ł͖����A�X�P�[���̗�(0.0�`N (1.0=���{)) �������Ă���
      float2 prm_ptn_no      : TEXCOORD0, //UV�ł͖����āAprm_ptn_no.x�ɂ́A�\���������A�j���[�V�����p�^�[���ԍ������ߍ���ł���
      float4 prm_color         : COLOR0     //�I�u�W�F�N�g�̃J���[

) {
	OUT_VS out_vs = (OUT_VS)0;

	out_vs.color = prm_color;
	out_vs.pos = mul(prm_pos, g_matWorld);  //World
float w_zf = g_zf * g_far_rate;
	//�J�����̍ő压��͈�(-_zf �` _zf, -_zf �` _zf, -_zf �` _zf)
	//�𒴂��Ă���ꍇ�A���[�v����B
	if (out_vs.pos.x > w_zf) {
		out_vs.pos.x = out_vs.pos.x - (w_zf*2);
	}
	if (out_vs.pos.x < -w_zf) {
		out_vs.pos.x = out_vs.pos.x + (w_zf*2);
	}
	if (out_vs.pos.y > w_zf) {
		out_vs.pos.y = out_vs.pos.y - (w_zf*2);
	}
	if (out_vs.pos.y < -w_zf) {
		out_vs.pos.y = out_vs.pos.y + (w_zf*2);
	}
	if (out_vs.pos.z > w_zf) {
		out_vs.pos.z = out_vs.pos.z - (w_zf*2);
	}
	if (out_vs.pos.z < -w_zf) {
		out_vs.pos.z = out_vs.pos.z + (w_zf*2);
	}

// ���@�̎���ɂ��鐯�X�����炩�ɓ����ɂ������B
//
// ���@���W��(X,Y,Z)�Ƃ����ꍇ�B
// f(x,y,z) = abs(X-x)+abs(Y-y)+abs(Z-z)�@�ƒu����
// f(x,y,z) = D �𖞂���(x,y,z)�́A������D�̃��~�G���ȗ̈�ƂȂ�B
// f(x,y,z) = g_dist_CamZ_default �͂܂� �@ �̂悤�Ȕ͈͂ł���B�ig_dist_CamZ_default�͎��@����J�����̏��������j
// �@�����ό`����
// {abs(X-x)+abs(Y-y)+abs(Z-z)} / g_dist_CamZ_default = 1.0 �c �@ 
// ������A�ȉ��͈̔͂��l����
// {abs(X-x)/15 + abs(Y-y)/2 + abs(Z-z)/2} / g_dist_CamZ_default = 1.0 �c�A 
// {abs(X-x)/15 + abs(Y-y)/2 + abs(Z-z)/2} / g_dist_CamZ_default = 2.0 �c�B
// [�^�ォ��̃C���[�W�i�}�̔䗦���I�J�V�C���G�j]
//
//      Z
//     ^
//     |
//     |
//     |
//     |
//     |                                            ���Q                  
//     |                       (dCamZ,0)              �P���Q        ��                                  ��
//     |                     �^ �_                        �P���Q          
//     |                   �^     �_                        �A�P���Q             ��   �P���Q      
//     |                 �^       �@�_                            �P���Q                �B�P���Q  
//     |               �^             �_                              �P���Q                  �P���Q
//     |             �^                 �_                                �P���Q                  �P���Q
// ----+--------------------- ���@�� --------------------------------------------------------------------------------> X
//    0|   (-dCamZ,0)�_        ^        �^  (dCamZ,0)                     �Q���P (15*dCamZ,0)     �Q���P(30*dCamZ,0)
//     |               �_      |dCamZ �^                              �Q���P                  �Q���P
//     |                 �_    |    �^      ���̗̈�(A�̈�)�ł�   �Q���P                  �Q���P
//     |                   �_  |  �^        ���͔�\��        �Q���P        ��        �Q���P                    ��
//     |                     �_v�^                        �Q���P                  �Q���P
// �P���Q                     Cam (dCamZ,0)           �Q���P                  �Q���P         
//     �P���Q                  ^                  �Q���P���̗̈�(B�̈�)   �Q���P             
//     |   �P���Q              |              �Q���P     �������܂�   �Q���P  ��(out_vs.pos.x, out_vs.pos.y, out_vs.pos.z)
//     |       �P���Q          |          �Q���P                  �Q���P      ��
//     |           �P���Q      |      �Q���P                  �Q���P
//     |               �P���Q  v  �Q���P                  �Q���P
// �P���Q                  �P�� ���P                  �Q���P
//     �P���Q                  ^ (2*dCamZ,0)      �Q���P
//     |   �P���Q              |              �Q���P
//     |       �P���Q          |          �Q���P                           ��
//     |           �P���Q      |      �Q���P
//     |               �P���Q  v  �Q���P
//     |                   �P�� ���P
//                             (4*dCamZ,0)
//
// ������ (x,y,z) �ɐ��̍��W�������āA�B���A�ֈړ����ɃA���t�@�����炻���Ƃ����B

	float r2 = ( abs(out_vs.pos.x-g_fX_MyShip)/15.0 + 
               abs(out_vs.pos.y-g_fY_MyShip)/2.0 + 
               abs(out_vs.pos.z-g_fZ_MyShip)/2.0  ) / g_dist_CamZ_default;
	// r2 < 1.0         ��A�̈�
	// 1.0 < r2 < 2.0   ��B�̈�  �ƂȂ�

	if (r2 < 1.0) {
		//A�̈�̏ꍇ�A�����\��
		out_vs.color.a = 0;
	} else {
		//A�̈�O���̏ꍇ�A���������ɉ����Ĕ�����
        out_vs.color.a = r2 - 1.0;
	}
	out_vs.pos = mul(out_vs.pos , g_matView);  //View


	float dep = out_vs.pos.z  + 1.0; //+1.0�̈Ӗ���
                                          //VIEW�ϊ���(0.0, 0.0, -1.0) ���� (0.0, 0.0, 0.0) �����Ă��邽�߁A
                                          //�����ɉ�����B
//    if (dep > g_zf) {
//        dep = g_zf;
//    }

	out_vs.pos = mul(out_vs.pos , g_matProj);  //�ˉe�ϊ�

    if (out_vs.pos.z > g_zf*0.98) {   
        out_vs.pos.z = g_zf*0.98; //�{������O��Z���W�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
    }

	//���قǏ������\�����邽�߂ɏk�����v�Z
    out_vs.psize = (g_TexSize / g_TextureSplitRowcol) * (g_dist_CamZ_default / dep) * prm_psize_rate;  //prm_psize_rate=X�t�@�C���́A�ʏ펞�k����
    //psize�͉�ʏ�̃|�C���g �X�v���C�g�̕� (�s�N�Z���P��) 
    if (out_vs.psize < 2.5) {
        //2.5pix x 2.5pix ��菬�����ꍇ�A�`����������邽��2.5x2.5���ێ��B
        out_vs.psize = 2.5;
    }
//out_vs.psize = (g_TexSize / g_TextureSplitRowcol);


 //   out_vs.psize = (g_TexSize / g_TextureSplitRowcol) * (g_dist_CamZ_default / dep ) * prm_psize_rate + (-(g_dist_CamZ_default - dep) * 0.001);  
    //�ʏ�̉��s���̏k�����ł́A�������Ƃ��Ə��������߁A�����̐��͂قƂ�ǌ����Ȃ��Ȃ��Ă��܂��B
    //������ (-(g_dist_CamZ_default - dep) * 0.001) ���k�����ɉ��Z���A���s���ɑ΂���k�������ɂ₩�ɂ��A
    //�����̐��ł����݂�����悤�ɂ����B
 //out_vs.psize =(g_TexSize / g_TextureSplitRowcol)*prm_psize_rate;
	//�X�y�L�����Z�}���e�b�N�X(COLOR1)��ׂ��ĕ\��������UV���W����̏���PS�ɓn��
	int ptnno = prm_ptn_no.x + g_UvFlipPtnNo;
    if (ptnno >= g_TextureSplitRowcol*g_TextureSplitRowcol) {
        ptnno -= (g_TextureSplitRowcol*g_TextureSplitRowcol);
    }
	out_vs.uv_ps.x = fmod(ptnno, g_TextureSplitRowcol) / g_TextureSplitRowcol;
	out_vs.uv_ps.y = trunc(ptnno / g_TextureSplitRowcol) / g_TextureSplitRowcol;

	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 PS_HoshiBoshi(
	float2 prm_uv_pointsprite	  : TEXCOORD0,     
	float4 prm_color                : COLOR0,
	float4 prm_uv_ps              : COLOR1  //�X�y�L�����ł͖����āA�\��������UV���W����̏�񂪓����Ă���
) : COLOR  {
	float2 uv = (float2)0;
    float4 color = prm_color;
    color.a = 1.0;
	uv.x = prm_uv_pointsprite.x / g_TextureSplitRowcol + prm_uv_ps.x;
	uv.y = prm_uv_pointsprite.y / g_TextureSplitRowcol + prm_uv_ps.y;
	float4 out_color = tex2D( MyTextureSampler, uv) * color * g_colMaterialDiffuse;
	out_color.a *= g_alpha_master; 
	return out_color;
}


float4 PS_Flush(
	float2 prm_uv_pointsprite	  : TEXCOORD0,     
	float4 prm_color                : COLOR0,
	float4 prm_uv_ps              : COLOR1
) : COLOR  {
	float2 uv = (float2)0;
	uv.x = prm_uv_pointsprite.x * (1.0 / g_TextureSplitRowcol) + prm_uv_ps.x;
	uv.y = prm_uv_pointsprite.y * (1.0 / g_TextureSplitRowcol) + prm_uv_ps.y;
	float4 out_color = tex2D( MyTextureSampler, uv) * prm_color * FLUSH_COLOR * g_colMaterialDiffuse;
	out_color.a *= g_alpha_master; 
	return out_color;
}

technique HoshiBoshiTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION VS_HoshiBoshi();
		PixelShader  = compile PS_VERSION PS_HoshiBoshi();
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
		VertexShader = compile VS_VERSION VS_HoshiBoshi();
		PixelShader  = compile PS_VERSION PS_HoshiBoshi();
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
		VertexShader = compile VS_VERSION VS_HoshiBoshi();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}


////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AMeshModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float g_MyShip_fX;
float g_MyShip_fY;
float g_MyShip_fZ;


float g_default_DcamZ;
float g_Dist_VpPlnFront; //�قڎ��_����̋���
float g_zn;
float g_zf;
float g_TexSize;  //�ǂݍ��񂾃e�N�X�`���i�����`���O��j�̕��e�N�Z����
int g_TextureSplitRowcol; //�e�N�X�`���̏c���������B
                            //1�F�c���P���������������B
                            //2�F�c���Q�������S�̃A�j���p�^�[��
                            //3�F�c���R�������X�̃A�j���p�^�[��
float g_offsetU;        //�e�N�X�`��U���W����
float g_offsetV;         //�e�N�X�`��V���W����
float g_UvFlipPtnNo;

float3 g_LightDirection; // ���C�g�̕���
float4 g_LightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_LightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_MaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF
float g_PowerBlink;   
float g_BlinkThreshold;
float g_MasterAlpha;

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
	float4 col    : COLOR0;
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
      float  prm_psize_rate  : PSIZE,     //PSIZE�ł͖����āA�X�P�[���̗�(0.0�`N (1.0=���{)) �������Ă���
      float2 prm_ptn_no      : TEXCOORD0, //UV�ł͖����āAprm_ptn_no.x�ɂ́A�\���������A�j���[�V�����p�^�[���ԍ������ߍ���ł���
      float4 prm_col         : COLOR0     //�I�u�W�F�N�g�̃J���[

) {
	OUT_VS out_vs = (OUT_VS)0;

	out_vs.col = prm_col;
	out_vs.pos = mul(prm_pos    , g_matWorld);  //World

	//�J�����̍ő压��͈�(-_zf �` _zf, -_zf �` _zf, -_zf �` _zf)
	//�𒴂��Ă���ꍇ�A���[�v����B
	if (out_vs.pos.x > g_zf) {
		out_vs.pos.x = out_vs.pos.x - (g_zf*2);
	}
	if (out_vs.pos.x < -g_zf) {
		out_vs.pos.x = out_vs.pos.x + (g_zf*2);
	}
	if (out_vs.pos.y > g_zf) {
		out_vs.pos.y = out_vs.pos.y - (g_zf*2);
	}
	if (out_vs.pos.y < -g_zf) {
		out_vs.pos.y = out_vs.pos.y + (g_zf*2);
	}
	if (out_vs.pos.z > g_zf) {
		out_vs.pos.z = out_vs.pos.z - (g_zf*2);
	}
	if (out_vs.pos.z < -g_zf) {
		out_vs.pos.z = out_vs.pos.z + (g_zf*2);
	}


	//ZY���W�ɂ��Ď��@�̎���͔�\��
	if (g_MyShip_fZ-g_default_DcamZ*2 <  out_vs.pos.z  && out_vs.pos.z <  g_MyShip_fZ+g_default_DcamZ*2) {
		if (g_MyShip_fY-g_default_DcamZ*2 <  out_vs.pos.y  && out_vs.pos.y <  g_MyShip_fY+g_default_DcamZ*2) {
			out_vs.col.a = 0;
//			out_vs.col.r = 1.0 -  (abs(out_vs.pos.z - g_MyShip_fZ) + abs(out_vs.pos.y - g_MyShip_fY)) / g_default_DcamZ;
		}
	}


	out_vs.pos = mul(out_vs.pos , g_matView);  //View
	float dep = out_vs.pos.z + 1.0; //+1.0�̈Ӗ���
                                    //VIEW�ϊ���(0.0, 0.0, -1.0) ���� (0.0, 0.0, 0.0) �����Ă��邽�߁A
                                    //�����ɉ�����B




	out_vs.pos = mul(out_vs.pos , g_matProj);  //�ˉe�ϊ�



	out_vs.psize = (g_TexSize / g_TextureSplitRowcol) * (g_default_DcamZ / dep) * prm_psize_rate;  //�ʏ�̉��s���̏k����

    int ptnno = ((int)(prm_ptn_no.x + g_UvFlipPtnNo)) % (g_TextureSplitRowcol*g_TextureSplitRowcol);
	//�X�y�L����(COLOR1)��ׂ��ĕ\��������UV���W����̏���PS�ɓn��
	out_vs.uv_ps.x = ((int)(ptnno % g_TextureSplitRowcol)) * (1.0 / g_TextureSplitRowcol);
	out_vs.uv_ps.y = ((int)(ptnno / g_TextureSplitRowcol)) * (1.0 / g_TextureSplitRowcol);

	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 PS_HoshiBoshi(
	float2 prm_uv_pointsprite	  : TEXCOORD0,     
	float4 prm_col                : COLOR0,
	float4 prm_uv_ps              : COLOR1  //�X�y�L�����ł͖����āA�\��������UV���W����̏�񂪓����Ă���
) : COLOR  {
	float2 uv = (float2)0;
	uv.x = prm_uv_pointsprite.x * (1.0 / g_TextureSplitRowcol) + prm_uv_ps.x;
	uv.y = prm_uv_pointsprite.y * (1.0 / g_TextureSplitRowcol) + prm_uv_ps.y;
	float4 out_color = tex2D( MyTextureSampler, uv) * prm_col; // * g_MaterialDiffuse;
	out_color.a = out_color.a * g_MasterAlpha; 
	return out_color;
}


float4 PS_Flush(
	float2 prm_uv_pointsprite	  : TEXCOORD0,     
	float4 prm_col                : COLOR0,
	float4 prm_uv_ps              : COLOR1
) : COLOR  {
	float2 uv = (float2)0;
	uv.x = prm_uv_pointsprite.x * (1.0 / g_TextureSplitRowcol) + prm_uv_ps.x;
	uv.y = prm_uv_pointsprite.y * (1.0 / g_TextureSplitRowcol) + prm_uv_ps.y;
	float4 out_color = tex2D( MyTextureSampler, uv) * prm_col * float4(7.0, 7.0, 7.0, 1.0);// * g_MaterialDiffuse;
	out_color.a = out_color.a * g_MasterAlpha; 
	return out_color;
}

technique HoshiBoshiTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 VS_HoshiBoshi();
		PixelShader  = compile ps_2_0 PS_HoshiBoshi();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
		VertexShader = compile vs_2_0 VS_HoshiBoshi();
		PixelShader  = compile ps_2_0 PS_HoshiBoshi();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 VS_HoshiBoshi();
		PixelShader  = compile ps_2_0 PS_Flush();
	}
}


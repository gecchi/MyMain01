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
      float  prm_psize_rate  : PSIZE,     //PSIZE�̓|�C���g�T�C�Y�ł͖����A�X�P�[���̗�(0.0�`N (1.0=���{)) �������Ă���
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

// ���@�̎���ɂ��鐯�X�����炩�ɓ����ɂ������B
//
// ���@���W��(X,Y,Z)�Ƃ����ꍇ�B
// f(x,y,z) = abs(X-x)+abs(Y-y)+abs(Z-z)�@�ƒu����
// f(x,y,z) = D �𖞂���(x,y,z)�́A������D�̃��~�G���ƂȂ�B
// f(x,y,z) = g_default_DcamZ �͂܂� �@ �̂悤�Ȕ͈͂ł���B�ig_default_DcamZ�͎��@����J�����̏��������j
// �@�����ό`����
// {abs(X-x)+abs(Y-y)+abs(Z-z)} / default_DcamZ = 1.0 �c �@ 
// ������A�ȉ��͈̔͂��l����
// {abs(X-x)/4 + abs(Y-y)/2 + abs(Z-z)/2} / g_default_DcamZ = 1.0 �c�A 
// {abs(X-x)/4 + abs(Y-y)/2 + abs(Z-z)/2} / g_default_DcamZ = 2.0 �c�B
//
// [�^�ォ��̃C���[�W�i�}�̔䗦���I�J�V�C���G�j]
//
//      Z
//     ^
//     |
//     |
//     |
//     |
//     |                                            ���Q                  
//     |                       (DcamZ,0)              �P���Q        ��                                  ��
//     |                     �^ �_                        �P���Q          
//     |                   �^     �_                        �A�P���Q             ��   �P���Q      
//     |                 �^       �@�_                            �P���Q                �B�P���Q  
//     |               �^             �_                              �P���Q                  �P���Q
//     |             �^                 �_                                �P���Q                  �P���Q
// ----+--------------------- ���@�� --------------------------------------------------------------------------------> X
//    0|   (-DcamZ,0)�_        ^        �^  (DcamZ,0)                     �Q���P (4*DcamZ,0)      �Q���P(8*DcamZ,0)
//     |               �_      |DcamZ �^                              �Q���P                  �Q���P
//     |                 �_    |    �^         ���̗̈�ł�       �Q���P                  �Q���P
//     |                   �_  |  �^           ���͔�\��     �Q���P        ��        �Q���P                    ��
//     |                     �_v�^                        �Q���P                  �Q���P
// �P���Q                     Cam (DcamZ,0)           �Q���P                  �Q���P         
//     �P���Q                  ^                  �Q���P    ���̗̈��    �Q���P             
//     |   �P���Q              |              �Q���P     �������܂�   �Q���P  ��(out_vs.pos.x, out_vs.pos.y, out_vs.pos.z)
//     |       �P���Q          |          �Q���P                  �Q���P      ��
//     |           �P���Q      |      �Q���P                  �Q���P
//     |               �P���Q  v  �Q���P                  �Q���P
// �P���Q                  �P�� ���P                  �Q���P
//     �P���Q                  ^ (2*DcamZ,0)      �Q���P
//     |   �P���Q              |              �Q���P
//     |       �P���Q          |          �Q���P                           ��
//     |           �P���Q      |      �Q���P
//     |               �P���Q  v  �Q���P
//     |                   �P�� ���P
//                             (4*DcamZ,0)
//
// ������ (x,y,z) �ɐ��̍��W�������āA�B���A�ֈړ����ɃA���t�@�����炻���Ƃ����B
//
//	float r2 = ( abs(out_vs.pos.x-g_MyShip_fX)/4 + 
//               abs(out_vs.pos.y-g_MyShip_fY)/2 + 
//               abs(out_vs.pos.z-g_MyShip_fZ)/2  ) / g_default_DcamZ;
//
//	if (r2 < 1.0) {
//		//�A�̓����A����\���̈�
//		//out_vs.col.a = 0;
//		out_vs.col.r = 1.0;
//		out_vs.col.g = 0.0;
//		out_vs.col.b = 0.0;
//	} else {
//		//�A�̊O��
//        //out_vs.col.a = r2 - 1.0;
//		out_vs.col.rgb = r2;
//	}

	//<<���ؗp>>
	float r2 = ( abs(out_vs.pos.x-g_MyShip_fX)/5.0+ 
                 abs(out_vs.pos.y-g_MyShip_fY)/5.0+ 
                 abs(out_vs.pos.z-g_MyShip_fZ)/5.0 ) / g_default_DcamZ;

	if (r2 < 1.0) {
		//�A�̓����A����\���̈�
		//out_vs.col.a = 0;
		out_vs.col.r = 1.0;
		out_vs.col.g = 1.0;
		out_vs.col.b = 1.0;
		out_vs.col.a = 1.0;
	} else {
		//�A�̊O��
        //out_vs.col.a = r2 - 1.0;
		out_vs.col.a = 0;
	}


//	//ZY���W�ɂ��Ď��@�̎���͔�\��
//	if (g_MyShip_fZ-g_default_DcamZ*2 <  out_vs.pos.z  && out_vs.pos.z <  g_MyShip_fZ+g_default_DcamZ*2) {
//		if (g_MyShip_fY-g_default_DcamZ*2 <  out_vs.pos.y  && out_vs.pos.y <  g_MyShip_fY+g_default_DcamZ*2) {
//			
//			out_vs.col.a = 0;
////			out_vs.col.r = 1.0 -  (abs(out_vs.pos.z - g_MyShip_fZ) + abs(out_vs.pos.y - g_MyShip_fY)) / g_default_DcamZ;
//		}
//	}


	out_vs.pos = mul(out_vs.pos , g_matView);  //View
	float dep = out_vs.pos.z + 1.0; //+1.0�̈Ӗ���
                                    //VIEW�ϊ���(0.0, 0.0, -1.0) ���� (0.0, 0.0, 0.0) �����Ă��邽�߁A
                                    //�����ɉ�����B




	out_vs.pos = mul(out_vs.pos , g_matProj);  //�ˉe�ϊ�


	//���قǏ������\�����邽�߂ɏk�����v�Z
	out_vs.psize = (g_TexSize / g_TextureSplitRowcol) * (g_default_DcamZ / dep) * prm_psize_rate*5.0;  //�ʏ�̉��s���̏k����

    int ptnno = ((int)(prm_ptn_no.x + g_UvFlipPtnNo)) % (g_TextureSplitRowcol*g_TextureSplitRowcol);
	//�X�y�L�����Z�}���e�b�N�X(COLOR1)��ׂ��ĕ\��������UV���W����̏���PS�ɓn��
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


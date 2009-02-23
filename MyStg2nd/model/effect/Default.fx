//����́A���C�g�̌����Ɩ@���̓��ς�0���ׂĐ��l�̑傫�ȕ����e�N�X�`���̐F�ɏ�Z���ĉe�����Ă���Ƃ������������Ă��܂��B


// 
//			X�t�@�C��+�e�N�X�`��
//			Created by TAKAHASHI Masafumi
// 
// �O���[�o���ϐ�
float4x4 mWVP;		// ���[�J������ˉe��Ԃւ̍��W�ϊ�
float4	Dir;		// ���C�g�̌���
float4	Diffuse;	//�f�B�t���[�Y�F
float4	Ambient;	//�A���r�G���g
texture	Tex1;		//�e�N�X�`��
sampler TextureSampler = sampler_state
{
    Texture = <Tex1>;
	//�t�B���^�ݒ�
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;    
    //�e�N�X�`�����b�s���O
    AddressU = Wrap;
    AddressV = Wrap;
};
// �o�[�e�b�N�X�V�F�[�_�o��
struct VS_OUTPUT
{
    float4 Pos  : POSITION;
    float4 Col  : COLOR0;
    float2 TexUV	: TEXCOORD0;
};
// �o�[�e�b�N�X�V�F�[�_�v���O����
VS_OUTPUT VS(
      float4 Pos    : POSITION,          // ���f���̒��_
      float3 Normal : NORMAL,	         // ���f���̖@��
      float2 TexUV	: TEXCOORD0
){
	float3	dir={Dir.x,Dir.y,Dir.z};	//���C�g�̌����Z�b�g
	VS_OUTPUT Out = (VS_OUTPUT)0;        // �o�̓f�[�^  
	Out.Pos = mul(Pos, mWVP);			// ���W�ϊ� 
	Out.TexUV = TexUV;					//UV�擾
	Out.Col = max( dot(dir, Normal), 0);//�����v�Z  
	return Out;
}

// �s�N�Z���V�F�[�_�v���O����
float4 PS(
	float2 TexUV	: TEXCOORD0,
    	float4 Col  : COLOR0 ) : COLOR
{
	//�e�N�X�`������
	Col = tex2D( TextureSampler, TexUV ) * Col;
    return Col;
}
// �e�N�j�b�N
technique TShader
{
    pass P0
    {
        VertexShader = compile vs_1_1 VS();
        PixelShader  = compile ps_1_1 PS();
    }
}




//
//
//// ���[���h�r���[�ˉe�ϊ��s��錾
//float4x4 g_worldMat;
//float4x4 g_viewMat;
//float4x4 g_projMat;
////float4 pos : POSITION;
//
//
//struct VS_OUT {
//	float4 pos    : POSITION;
//	float4 uv     : TEXCOORD0;
//	float3 normal : TEXCOORD1;
//};
//
//VS_OUT Specular_VS( float4 inLocalPos : POSITION, float3 inLocalNormal : NORMAL, float4 inUV : TEXCOORD0 )
//{
//	VS_OUT Out = (VS_OUT)0;
//	Out.pos = mul( inLocalPos, g_worldMat );
//	Out.pos = mul( Out.pos, g_viewMat );
//	Out.pos = mul( Out.pos, g_projMat );
//
//	// �@���x�N�g�������[���h�ցH
//	Out.normal = inLocalNormal;
////mul( inLocalNormal, g_worldView );
//	
//	Out.uv     = inUV;
//	return Out;
//}
//
////
////// ���_�V�F�[�_
////float4 BasicTransform( float4 inLocalPos : POSITION ) : POSITION
////{
////
////	pos = mul( inLocalPos, g_worldMat );
////	pos = mul( pos, g_viewMat );
////	pos = mul( pos, g_projMat );
////	return pos;
////}
////
//// �s�N�Z���V�F�[�_
//float4 NoWorkingPixelShader( float4 ScreenColor : COLOR ) : COLOR
//{
//   // ���͂��ꂽ�X�N���[���s�N�Z���̐F�����̂܂܃X���[
//   return ScreenColor;
//}
//
//
//technique BasicTec
//{
//   pass P0
//   {
//      VertexShader = compile vs_2_0 Specular_VS();
//      PixelShader = compile ps_2_0 NoWorkingPixelShader();
//   }
//}

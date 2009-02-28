////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����p�A�W���V�F�[�_�[
// 
// �T�v�FWorld�AView�A�ˉe�ϊ����āA�}�e���A���ƃe�N�X�`���������l�����ă����_�����O
//
// �p�����[�^:
// float4x4 g_matWorld		:	World�ϊ��s��
// float4x4 g_matView		:	View�ϊ��s��
// float4x4 g_matProj		:	�ˉe�ϊ��s��
// float4 g_MaterialAmbient	:	�}�e���A����Ambien���ːF
// float4 g_MaterialDiffuse	:	�}�e���A����Diffuse���ːF
//
// Auther:Masatoshi Tsuge
// date:2009/02/04 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float3 g_LightDirection = normalize(float3( -1, -1, 1 ));      // ���C�g�̕���

float4 g_LightAmbient = float4( 0.3f, 0.3f, 0.3f, 1.0f );   // Ambien���C�g�F�i���ːF�j
float4 g_LightDiffuse = float4( 1.0f, 1.0f, 1.0f, 1.0f );           // Diffuse���C�g�F�i���ːF�j

float4 g_MaterialAmbient;  //�}�e���A����Ambien���ːF
float4 g_MaterialDiffuse;  //�}�e���A����Diffuse���ːF


texture g_diffuseMap;
sampler MyTextureSampler = sampler_state {
	texture = <g_diffuseMap>;
};

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float3 normal : TEXCOORD1;   // ���[���h�ϊ������@��
};


///////////////////////////////////////////////////////////////////////////

//���_�V�F�[�_�[
OUT_VS Default_VS(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float3 prm_normal : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;

	//���_�v�Z
	float4 posWorld = mul( prm_pos, g_matWorld );               // World�ϊ�
	float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
	out_vs.pos = posWorldViewProj;                            // �o�͂ɐݒ�

    //�@���v�Z
    out_vs.normal = normalize(mul(prm_normal, g_matWorld)); //�@���� World �ϊ����A���K��

//	//�J���[�v�Z(�����v�Z)���A�o�͂ɐݒ�
//	out_vs.color = (g_LightDiffuse * g_MaterialDiffuse * max( dot(g_LightDirection, normal), 0)) +
//                   (g_LightAmbient * g_MaterialAmbient);

	//UV
	out_vs.uv = prm_uv;

	return out_vs;
}


// �s�N�Z���V�F�[�_
//�e�N�X�`���F�ADiffuse���C�g�F�AAmbient���C�g�F�A���C�g�������l������
float4 Default_PS(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1
) : COLOR  {
	// �F���Z�o
	float4 out_color; //���߂�F


    //Diffuse�F�v�Z
	float power = max(dot(prm_normal, -g_LightDirection ), 0);          //�@���ƁADiffuse���C�g�����̓��ς��v�Z���Aface �ɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                //�e�N�X�`�����F���擾
//	out_color = tex_color;
	out_color = g_LightDiffuse * g_MaterialDiffuse * tex_color * power; //���C�g�����A���C�g�F�A�}�e���A���F�A�e�N�X�`���F���l�������F�̊����I�B              

	//Ambient�F�����Z
	out_color =  (g_LightAmbient * g_MaterialDiffuse * tex_color) + out_color;  //�}�e���A����Ambien���ːF�́A�}�e���A����Diffuse���ːF�Ɠ����F�Ƃ���B

	//���v�Z
	out_color.a = g_LightDiffuse.a * g_LightAmbient.a * g_MaterialDiffuse.a * tex_color.a ; //�A�����͖@���A���C�g�������֌W�Ȃ��̂ŕʌv�Z�A�S���|����B

	return out_color;   // ���ːF

	//return float4( 1, 1, 1, 1 );//prm_color;

	//�e�N�X�`������
	//return tex2D( MyTextureSampler, prm_uv );// * prm_color;
}

technique DefaultTec
{
	pass P0 {
		VertexShader = compile vs_2_0 Default_VS();
		PixelShader  = compile ps_2_0 Default_PS();
	}
}

float4x4 g_matWorld;  
float4x4 g_matView;   
float4x4 g_matProj;   

float3 g_LightDirection; 
float4 g_LightAmbient;   
float4 g_LightDiffuse;   

float4 g_MaterialDiffuse;

float g_Blinker;   

sampler MyTextureSampler : register(s0);


struct OUT_VS
{
    float4 pos    : POSITION;
	float3 normal : TEXCOORD1;   
    float4 color  : COLOR0;
	float2 uv     : TEXCOORD0;

};


OUT_VS GgafDx9VS_GroundMesh(
      float4 prm_pos    : POSITION,     
      float3 prm_normal : NORMAL,       
	  float4 prm_color  : COLOR0,
      float2 prm_uv     : TEXCOORD0     

) {
	OUT_VS out_vs = (OUT_VS)0;

	out_vs.pos = mul( mul(prm_pos, g_matWorld), g_matView);
	out_vs.color = prm_color;
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

	out_vs.pos = mul(out_vs.pos, g_matProj);  
    out_vs.normal = normalize(mul(prm_normal, g_matWorld)); 
	out_vs.uv = prm_uv;
	return out_vs;
}

float4 GgafDx9PS_GroundMesh(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1,
	float4 prm_color  : COLOR0
) : COLOR  {
	float power = max(dot(prm_normal, -g_LightDirection ), 0);          
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                
	float4 out_color = g_LightDiffuse * g_MaterialDiffuse * tex_color * power; 
	out_color =  (g_LightAmbient * g_MaterialDiffuse * tex_color) + out_color;  
	out_color.a = g_MaterialDiffuse.a * tex_color.a * prm_color.a; 

	return out_color;
}

float4 GgafDx9PS_GroundMesh2(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1,
	float4 prm_color  : COLOR0 
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                
	//���C�g�F�A�}�e���A���F�A�e�N�X�`���F���l�������F�쐬�B              
	float4 out_color = g_LightDiffuse * g_MaterialDiffuse * tex_color; 
	//���v�Z�A
	out_color.a = g_MaterialDiffuse.a * tex_color.a * prm_color.a; 

	return out_color;
}


technique GroundMeshTechnique
{
	//pass P0�u���b�V���W���V�F�[�_�[�v
	//���b�V����`�悷��
	//�y�l�������v�f�z
	//--- VS ---
	//�E���_�� World�AView�A�ˉe �ϊ�
	//�E�@���� World�ϊ�
	//--- PS ---
	//�EDiffuse���C�g�F
	//�EAmbient���C�g�F
	//�E���C�g����
	//�E�I�u�W�F�N�g�̃}�e���A����Diffuse���ˁi�F��Ambient���˂Ƌ��ʁj
	//�E�I�u�W�F�N�g�̃e�N�X�`��
	//�E���������iDiffuse���˃��ƃe�N�X�`�����̏�Z�j
	//�y�g�p�����z
	//�E�e�N�X�`�������݂�s0���W�X�^�Ƀo�C���h����Ă��邱�ƁB
	//�y�ݒ�p�����[�^�z
	// float4x4 g_matWorld		:	World�ϊ��s��
	// float4x4 g_matView		:	View�ϊ��s��
	// float4x4 g_matProj		:	�ˉe�ϊ��s��   
	// float3 g_LightDirection	:	���C�g�̕���
	// float4 g_LightAmbient	:	Ambien���C�g�F�i���ːF�j
	// float4 g_LightDiffuse	:	Diffuse���C�g�F�i���ːF�j
	// float4 g_MaterialDiffuse	:	�}�e���A����Diffuse���ˁiAmbient���˂Ƌ��ʁj
	// s0���W�X�^				:	2D�e�N�X�`��
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		ColorVertex  = True;

		VertexShader = compile vs_2_0 GgafDx9VS_GroundMesh();
		PixelShader  = compile ps_2_0 GgafDx9PS_GroundMesh();
	}
}

technique GroundMeshTechnique2
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        ColorVertex  = True;

		VertexShader = compile vs_2_0 GgafDx9VS_GroundMesh();
		PixelShader  = compile ps_2_0 GgafDx9PS_GroundMesh2();
	}
}



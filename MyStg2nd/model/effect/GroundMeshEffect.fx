float4x4 g_matWorld;  
float4x4 g_matView;   
float4x4 g_matProj;   

float3 g_LightDirection; 
float4 g_LightAmbient;   
float4 g_LightDiffuse;   

float4 g_MaterialDiffuse;

float g_PowerBlink;   
float g_BlinkThreshold;
float g_MasterAlpha;
float g_zf;

sampler MyTextureSampler : register(s0);


struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 col    : COLOR0;
};


OUT_VS GgafDx9VS_GroundMesh(
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
	float power = max(dot(normal, -g_LightDirection ), 0);      
	//Ambient���C�g�F�ADiffuse���C�g�F�ADiffuse���C�g�����A�}�e���A���F ���l�������J���[�쐬�B      
	out_vs.col = (g_LightAmbient + (g_LightDiffuse*power)) * g_MaterialDiffuse;
	//���t�H�O
	out_vs.col.a = g_MaterialDiffuse.a;
	if (out_vs.pos.z > g_zf*0.5) { // �ŉ��� 1/2 ��艜�̏ꍇ���X�ɓ�����
    	out_vs.col.a *= (-1.0/(g_zf*0.5)*out_vs.pos.z + 2.0);
	} 
//	if (out_vs.pos.z > g_zf*0.75) { //�ŉ��� 3/4 ��艜�̏ꍇ���X�ɓ�����
//    	out_vs.col.a *= (-1.0/(g_zf*0.25)*out_vs.pos.z + 4.0);
//	}
	//�}�X�^�[��
	out_vs.col.a *= g_MasterAlpha;

 //�J�����̈ʒu(0,0,-57.1259)
//���͐��E��(-1.0f, -1.0f, 0 )�Ƃ����_����(1.0f, 1.0f, 1,0f)�Ƃ����_��Ίp���Ƃ��钼���̂̐��E�Ɏ��߂��Ă��܂��Ă��܂�

//w�͎ˉe��ԁi�������ԁj�ɂ��钸�_���W������Ŋ��邱�Ƃɂ��
//�u���_���X�N���[���ɓ��e���邽�߂̗����̗̂̈�i-1��x��1�A-1��y��1������0��z��1�j�ɔ[�߂�v
//�Ƃ�����؂Ȗ�ڂ����Ă��܂��Bw���u�����n�v�ƌĂ΂��̂́A
//��̗�̂悤�Ɏ�����ɃJ�����̎��������ɍL�����Ă��钸�_�𓯂�XY���W�ɓ��e���邽�߂ł��B


	if ( out_vs.pos.z < 60) {
		out_vs.col.a = (out_vs.pos.z + 1.0)  / (57.1259*2);
//1 - (out_vs.pos.z / 57.1259);
	}
	return out_vs;
}

float4 GgafDx9PS_GroundMesh(
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_col    : COLOR0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_col;

    //Blinker���l��
	if (tex_color.r >= g_BlinkThreshold || tex_color.g >= g_BlinkThreshold || tex_color.b >= g_BlinkThreshold) {
		out_color.rgb *= g_PowerBlink; //+ (tex_color * g_PowerBlink);
	} 
	return out_color;
}


technique GroundMeshTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		ColorVertex  = True;

		VertexShader = compile vs_2_0 GgafDx9VS_GroundMesh();
		PixelShader  = compile ps_2_0 GgafDx9PS_GroundMesh();
	}
}


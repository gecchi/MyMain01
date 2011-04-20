/**
 * GgafDx9MeshModel�p�V�F�[�_�[ .
 * �ÓI���f���P��`�悷��W���I�V�F�[�_�[�B
 * ���_�o�b�t�@�t�H�[�}�b�g��
 * FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
 * ���A�O��Ƃ���B
 * @author Masatoshi Tsuge
 * @since 2009/03/06 
 */

/** ���f����World�ϊ��s�� */
float4x4 g_matWorld;
/** ���f����View�ϊ��s�� */
float4x4 g_matView;
/** ���f���̎ˉe�ϊ��s�� */
float4x4 g_matProj;

/** ���C�g�̕����x�N�g���i���K���ς݁j */
float3 g_vecLightDirection;
/** ���C�g�̐F(���C�g�̊g�U���ˎ��̃��C�g���g�̐F) */
float4 g_colLightDiffuse;
/** �����̐F */
float4 g_colLightAmbient;
/** ���f���̃}�e���A���F(���C�g�ɂ��g�U���ˎ��̃��f���̐F) */
float4 g_colMaterialDiffuse;
/** ���f���̃e�N�X�`���F�_�ŋ@�\(GgafDx9TextureBlinker�Q��)�̓_�ŋ��x */
float g_tex_blink_power;   
/** ���f���̃e�N�X�`���F�_�ŋ@�\(GgafDx9TextureBlinker�Q��)�̑ΏۂƂȂ�RGB�̂������l(0.0�`1.0) */
float g_tex_blink_threshold;
/** �t�F�[�h�C���E�A�E�g�@�\(GgafDx9AlphaCurtain�Q��)�̂��߂̃}�X�^�[�A���t�@�l(0.0�`1.0) */
float g_alpha_master;
/** ���݂̎ˉe�ϊ��s��v�f��zf�B�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn */
float g_zf;

float3 g_posCam;


// �X�y�L�������x���z
const float g_spec_expon = 0.5f;


/** �e�N�X�`���̃T���v���[(s0 ���W�X�^�ɃZ�b�g���ꂽ�e�N�X�`�����g��) */
sampler MyTextureSampler : register(s0);
/** ���_�V�F�[�_�[�A�o�͍\���� */
struct OUT_VS {
    float4 pos : POSITION;
    float2 uv  : TEXCOORD0;
    float4 col : COLOR0;
};

/**
 * �W�����_�V�F�[�_�[ .
 * �}�e���A���̐F�t�́A���_�J���[�Ŏ������Ă���B(���x�d���̂���)
 * @param prm_pos    ���f�����_�̍��W
 * @param prm_normal ���f�����_�̖@��
 * @param prm_uv     ���f�����_�̃e�N�X�`��UV���W
 */
OUT_VS GgafDx9VS_DefaultMesh(
      float4 prm_pos    : POSITION, 
      float4 prm_normal : NORMAL,   
      float2 prm_uv     : TEXCOORD0 
) {
	OUT_VS out_vs = (OUT_VS)0;

	//���_���W�v�Z
    float4 posWorld = mul(prm_pos, g_matWorld);
	out_vs.pos = mul( mul( posWorld, g_matView), g_matProj);  //World*View*�ˉe

	//UV�v�Z
	out_vs.uv = prm_uv;  //���̂܂�

    //���_�J���[�v�Z
	//�@���� World �ϊ����Đ��K��
    float3 normal = normalize(mul(prm_normal, g_matWorld)); 	

    //�u���_���J�������_�v�����x�N�g��                                                        
    float3 vecCam = normalize(g_posCam.xyz - posWorld.xyz);

    //�n�[�t�x�N�g��
    //���u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g��
    float3 vecHarf = normalize(vecCam + (-g_vecLightDirection));


    // ���C�e�B���O�W���̌v�Z
    //litVal = float4([0]=�A���r�G���g, [1]=�f�B�t���[�Y, [2]=�X�y�L�����[, [3]=1)
    float4 litVal = lit(dot(normal, -g_vecLightDirection), dot(normal, vecHarf), g_spec_expon);



    //�g�U�̋������v�Z�B�@���ƁA���C�g�����̓��ς��烉�C�g���ˊp�����߁A�ʂɑ΂�����̌����������߂�B
	//float power = max(dot(normal, -g_vecLightDirection ), 0);      
	//���C�g�F�Ɍ��������悶�A�����F�����Z���A�S�̂��}�e���A���F���|����B
	out_vs.col = (g_colLightAmbient + (g_colLightDiffuse*litVal[1])) * g_colMaterialDiffuse;
    // ���ʔ��ː���
    out_vs.col += litVal[1] * litVal[2] * g_colLightDiffuse;
    //�A���A���̓}�e���A���̃���D�悷��    
    out_vs.col.a = g_colMaterialDiffuse.a;
    //�J������艓���̏ꍇ�A���t�H�O��������
	if (out_vs.pos.z > (g_zf*0.9)*0.5) { // �ŉ��� 1/2 ��艜�̏ꍇ�A���X�ɓ����� (0.9�͕␳�l)
    	out_vs.col.a *= (-1.0/((g_zf*0.9)*0.5)*out_vs.pos.z + 2.0);
	} 
	//�t�F�[�h�C���E�A�E�g�@�\�̃}�X�^�[�����l������
	out_vs.col.a *= g_alpha_master;

	return out_vs;
}

/**
 * �ʏ�s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
 */
float4 GgafDx9PS_DefaultMesh(
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_col    : COLOR0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_col;

    //GgafDx9TextureBlinker���l��
	if (tex_color.r >= g_tex_blink_threshold || 
        tex_color.g >= g_tex_blink_threshold || 
        tex_color.b >= g_tex_blink_threshold) 
    {
		out_color.rgb *= g_tex_blink_power; //+ (tex_color * g_tex_blink_power);
	} 
	return out_color;
}

float4 PS_Flush( 
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_col    : COLOR0
) : COLOR  {                         
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_col * float4(7.0, 7.0, 7.0, 1.0);
	return out_color;
}


/**
 * �ʏ�e�N�j�b�N
 */
technique DefaultMeshTechnique
{
	//pass P0�u���b�V���W���V�F�[�_�[�v
	//���b�V����`�悷��
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMesh();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMesh();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMesh();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMesh();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMesh();
		PixelShader  = compile ps_2_0 PS_Flush();
	}
}


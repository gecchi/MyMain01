////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDx9MeshSetModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

int g_unit_vertecnum;
inout int g_cnt_vertec = 1;

float4x4 g_matWorld001;
float4x4 g_matWorld002;
float4x4 g_matWorld003;
float4x4 g_matWorld004;
float4x4 g_matWorld005;
float4x4 g_matWorld006;
float4x4 g_matWorld007;
float4x4 g_matWorld008;
float4x4 g_matWorld009;
float4x4 g_matWorld010;
float4x4 g_matWorld011;
float4x4 g_matWorld012;
float4x4 g_matWorld013;
float4x4 g_matWorld014;
float4x4 g_matWorld015;
float4x4 g_matWorld016;

float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float3 g_LightDirection; // ���C�g�̕���
float4 g_LightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_LightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_MaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//texture g_diffuseMap;
//sampler MyTextureSampler = sampler_state {
//	texture = <g_diffuseMap>;
//};

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float3 normal : TEXCOORD1;   // ���[���h�ϊ������@��
};


///////////////////////////////////////////////////////////////////////////

//���b�V���W�����_�V�F�[�_�[
OUT_VS GgafDx9VS_DefaultMeshSet(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float3 prm_normal : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;

	//���_�v�Z
	float4 matWorld;

	if (g_unit_vertecnum*8 >= g_cnt_vertec) {
		if (g_unit_vertecnum*4 >= g_cnt_vertec) {
			if (g_unit_vertecnum*2 >= g_cnt_vertec) {
				if (g_unit_vertecnum >= g_cnt_vertec) {
					matWorld = g_matWorld001;
				} else {
					matWorld = g_matWorld002;
				}
			} else {
				if (g_unit_vertecnum*3 >= g_cnt_vertec) {
					matWorld = g_matWorld003;
				} else {
					matWorld = g_matWorld004;
				}
			}
		} else {
			if (g_unit_vertecnum*6 >= g_cnt_vertec) {
				if (g_unit_vertecnum*5 >= g_cnt_vertec) {
					matWorld = g_matWorld005;
				} else {
					matWorld = g_matWorld006;
				}
			} else {
				if (g_unit_vertecnum*7 >= g_cnt_vertec) {
					matWorld = g_matWorld007;
				} else {
					matWorld = g_matWorld008;
				}
			}
		}
	} else {
		if (g_unit_vertecnum*12 >= g_cnt_vertec) {
			if (g_unit_vertecnum*10 >= g_cnt_vertec) {
				if (g_unit_vertecnum*9 >= g_cnt_vertec) {
					matWorld = g_matWorld009;
				} else {
					matWorld = g_matWorld010;
				}
			} else {
				if (g_unit_vertecnum*11 >= g_cnt_vertec) {
					matWorld = g_matWorld011;
				} else {
					matWorld = g_matWorld012;
				}
			}
		} else {
			if (g_unit_vertecnum*14 >= g_cnt_vertec) {
				if (g_unit_vertecnum*13 >= g_cnt_vertec) {
					matWorld = g_matWorld013;
				} else {
					matWorld = g_matWorld014;
				}
			} else {
				if (g_unit_vertecnum*15 >= g_cnt_vertec) {
					matWorld = g_matWorld015;
				} else {
					matWorld = g_matWorld016;
				}
			}
		}
	}

	float4 posWorld = mul( prm_pos, matWorld );               // World�ϊ�
	float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
	out_vs.pos = posWorldViewProj;                              // �o�͂ɐݒ�
    //�@���v�Z
    out_vs.normal = normalize(mul(prm_normal, matWorld)); 	//�@���� World �ϊ����Đ��K��
	//UV�͂��̂܂�
	out_vs.uv = prm_uv;
	g_cnt_vertec++;
	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDx9PS_DefaultMeshSet(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1
) : COLOR  {
	//���߂�F
	float4 out_color; 

    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
	float power = max(dot(prm_normal, -g_LightDirection ), 0);          
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                
	//���C�g�����A���C�g�F�A�}�e���A���F�A�e�N�X�`���F���l�������F�쐬�B              
	out_color = g_LightDiffuse * g_MaterialDiffuse * tex_color * power; 
	//Ambient�F�����Z�B�{�V�F�[�_�[�ł̓}�e���A����Ambien���ːF�́A�}�e���A����Diffuse���ːF�Ɠ����F�Ƃ���B
	out_color =  (g_LightAmbient * g_MaterialDiffuse * tex_color) + out_color;  
	//���v�Z�A���͖@������у��C�g�����Ɉˑ����Ȃ��Ƃ���̂ŕʌv�Z�B�Œ�̓��C�g���F���l�����邪�A�{�V�F�[�_�[�̓��C�g���͖����B
	out_color.a = g_MaterialDiffuse.a * tex_color.a ; 

	return out_color;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`�������j
float4 GgafDx9PS_NoTexMeshSet(
	float2 prm_uv     : TEXCOORD0,
	float3 prm_normal : TEXCOORD1
) : COLOR  {
	//���߂�F
	float4 out_color; 

    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
	float power = max(dot(prm_normal, -g_LightDirection ), 0);          
	//���C�g�����A���C�g�F�A�}�e���A���F�A���l�������F�쐬�B              
	out_color = g_LightDiffuse * g_MaterialDiffuse * power; 
	//Ambient�F�����Z�B�}�e���A����Ambien���ːF�́A�}�e���A����Diffuse���ːF�Ɠ����F�Ƃ���B
	out_color =  (g_LightAmbient * g_MaterialDiffuse) + out_color;  
	//�}�e���A�����B
	out_color.a = g_MaterialDiffuse.a; 
	return out_color;
}

technique DefaultMeshSetTechnique
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

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMeshSet();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMeshSet();
	}
}

technique DefaulNoTexMeshSetTechnique {
	//pass P1�u���b�V���W���V�F�[�_�[�i�e�N�X�`�������j�v
	//�y�l�������v�f�z
	//--- VS ---
	//�E���_�� World�AView�A�ˉe �ϊ�
	//�E�@���� World�ϊ�
	//--- PS ---
	//�EDiffuse���C�g�F
	//�EAmbient���C�g�F
	//�E���C�g����
	//�E�I�u�W�F�N�g�̃}�e���A����Diffuse���ˁiAmbient���˂Ƌ��ʁj
	//�E���������i�}�e���A��Diffuse���˃��̂݁j
	//�y�g�p�����z
	//�y�ݒ�p�����[�^�z
	// float4x4 g_matWorld		:	World�ϊ��s��
	// float4x4 g_matView		:	View�ϊ��s��
	// float4x4 g_matProj		:	�ˉe�ϊ��s��
	// float3 g_LightDirection	:	���C�g�̕���
	// float4 g_LightAmbient	:	Ambien���C�g�F�i���ːF�j
	// float4 g_LightDiffuse	:	Diffuse���C�g�F�i���ːF�j
	// float4 g_MaterialDiffuse	:	�}�e���A����Diffuse���ˁiAmbient���˂Ƌ��ʁj
	pass P1 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMeshSet();
		PixelShader  = compile ps_2_0 GgafDx9PS_NoTexMeshSet();
	}


}

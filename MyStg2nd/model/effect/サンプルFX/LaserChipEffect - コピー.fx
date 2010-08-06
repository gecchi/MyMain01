////////////////////////////////////////////////////////////////////////////////
// ���[�U�[�`�b�v�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/04/23
////////////////////////////////////////////////////////////////////////////////

int g_kind; //�`�b�v��� 1:���� 2:���� 3:�擪 �i�������擪�͖������D��j

float g_X; //��O���s���`�b�vX
float g_Y; //��O���s���`�b�vY
float g_Z; //��O���s���`�b�vZ

bool g_RevPosZ; //Z���W�𔽓]���邩�ǂ���


//float4x4 g_matWorld;  //���g��World�ϊ��s��
//float4x4 g_matWorld_front;  //��O���s���`�b�v��World�ϊ��s��

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
float4x4 g_matWorld_front001;
float4x4 g_matWorld_front002;
float4x4 g_matWorld_front003;
float4x4 g_matWorld_front004;
float4x4 g_matWorld_front005;
float4x4 g_matWorld_front006;
float4x4 g_matWorld_front007;
float4x4 g_matWorld_front008;
float4x4 g_matWorld_front009;
float4x4 g_matWorld_front010;
float4x4 g_matWorld_front011;
float4x4 g_matWorld_front012;
float4x4 g_matWorld_front013;
float4x4 g_matWorld_front014;
float4x4 g_matWorld_front015;
float4x4 g_matWorld_front016;

float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float3 g_vecLightDirection; // ���C�g�̕���
float4 g_colLightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_colLightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_colMaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//���[�U�[�`�b�v���_�V�F�[�_�[
OUT_VS GgafDx9VS_LaserChip(
      float4 prm_pos    : POSITION,      // ���f���̒��_
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







//
	if (g_RevPosZ == true) {
		prm_pos.z = -prm_pos.z;
	}
//
//	if (g_Y - g_matWorld._42 < 0) {
//		prm_pos.y = -prm_pos.y;
//	}
//
	//�قڐ^���Ȃ�H�͂���Ȃ�
	if (abs(g_Z - g_matWorld._43) < 1.5) {
		if (abs(g_Y - g_matWorld._42) < 1.0) {
			prm_pos.z = 0;
		}
	}

	float4 posWorld;
	if (prm_pos.x > 0) {
		float4x4 matWorld_tmp = g_matWorld_front; 
		matWorld_tmp._41 = g_X;  // ��O���̃`�b�v���W�ւ�������
		matWorld_tmp._42 = g_Y;  
		matWorld_tmp._43 = g_Z;  
		posWorld = mul( prm_pos, matWorld_tmp );      // World�ϊ�
	} else {
		//���_�v�Z
		posWorld = mul( prm_pos, matWorld );        // World�ϊ�
	}
	float4 posWorldView = mul(posWorld    , g_matView);  // View�ϊ�
	out_vs.pos          = mul(posWorldView, g_matProj);  // �ˉe�ϊ�

	//UV
	if (g_kind == 2) {
		out_vs.uv = prm_uv;
	} else if (g_kind == 1) {
		out_vs.uv.x = prm_uv.x - 0.5;
		out_vs.uv.y = prm_uv.y;
	} else if (g_kind == 3) {
		out_vs.uv.x = prm_uv.x;
		out_vs.uv.y = prm_uv.y - 0.5;
	} else {
		//�����`�悵�����Ȃ�
		out_vs.uv.x = 0.1;
		out_vs.uv.y = 0.1;
	}
	return out_vs;
}

float4 GgafDx9PS_LaserChip(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);
	return tex_color;
}


technique LaserChipTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   //���Z����
		DestBlend = One;

		VertexShader = compile vs_2_0 GgafDx9VS_LaserChip();
		PixelShader  = compile ps_2_0 GgafDx9PS_LaserChip();
	}

}




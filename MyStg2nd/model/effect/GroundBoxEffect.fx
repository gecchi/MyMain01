////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDx9MeshSetModel�p�V�F�[�_�[
// �y�T�v�z
// ���_�o�b�t�@�ɁA�������f���L�����̒��_��񂪁A�������J��Ԃ��l�ߍ���ł���B
// �X�e�[�g�⃌�W�X�^�̍X�V���s�킸�A�P��� �`��ŁA�ő�
// 16�I�u�W�F�N�g�܂ŕ`��B��������_���B
// ��ʂ̓����G��e�ɂ́A���̃V�F�[�_�[�ŕ`�悷�邱�ƂƂ���B
// �A���A�P�I�u�W�F�N�g�ɂ��}�e���A���ݒ�͂P�����Ƃ�������������B
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////


int g_vertexs_num;
float g_zf;
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
// ���C�g�̕���
float3 g_vecLightDirection;
// Ambien���C�g�F�i���ːF�j
float4 g_colLightAmbient;
// Diffuse���C�g�F�i���ːF�j  
float4 g_colLightDiffuse;  
//View�ϊ��s��
float4x4 g_matView; 
//�ˉe�ϊ��s��  
float4x4 g_matProj;  

float g_box_dep;
float g_box_width;
float g_box_height;

int g_draw_face001;
int g_draw_face002;
int g_draw_face003;
int g_draw_face004;
int g_draw_face005;
int g_draw_face006;
int g_draw_face007;
int g_draw_face008;
int g_draw_face009;
int g_draw_face010;
int g_draw_face011;
int g_draw_face012;
int g_draw_face013;
int g_draw_face014;
int g_draw_face015;
int g_draw_face016;

//���[���h�ϊ��s��
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
//�I�u�W�F�N�g�̃}�e���A���F�iDiffuse���ːF�ƁAAmbien���ːF���ʁj
//float4 g_draw_face001;
//float4 g_draw_face002;
//float4 g_draw_face003;
//float4 g_draw_face004;
//float4 g_draw_face005;
//float4 g_draw_face006;
//float4 g_draw_face007;
//float4 g_draw_face008;
//float4 g_draw_face009;
//float4 g_draw_face010;
//float4 g_draw_face011;
//float4 g_draw_face012;
//float4 g_draw_face013;
//float4 g_draw_face014;
//float4 g_draw_face015;
//float4 g_draw_face016;

//�e�N�X�`���̃T���v��(s0���W�X�^)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 col    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//���_�V�F�[�_�[
OUT_VS GgafDx9VS_GroundBox(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float  prm_index  : PSIZE ,        // ���f���̃C���f�b�N�X�i���ڂ̃I�u�W�F�N�g���H�j
      float3 prm_normal : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv     : TEXCOORD0      // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;

	//���_�v�Z
	float4x4 matWorld;
	int draw_face;

	if (index == 0) {
		matWorld = g_matWorld001;
		draw_face = g_draw_face001;
	} else if (index == 1) {
		matWorld = g_matWorld002;
		draw_face = g_draw_face002;
	} else if (index == 2) {
		matWorld = g_matWorld003;
		draw_face = g_draw_face003;
	} else if (index == 3) {
		matWorld = g_matWorld004;
		draw_face = g_draw_face004;
	} else if (index == 4) {
		matWorld = g_matWorld005;
		draw_face = g_draw_face005;
	} else if (index == 5) {
		matWorld = g_matWorld006;
		draw_face = g_draw_face006;
	} else if (index == 6) {
		matWorld = g_matWorld007;
		draw_face = g_draw_face007;
	} else if (index == 7) {
		matWorld = g_matWorld008;
		draw_face = g_draw_face008;
	} else if (index == 8) {
		matWorld = g_matWorld009;
		draw_face = g_draw_face009;
	} else if (index == 9) {
		matWorld = g_matWorld010;
		draw_face = g_draw_face010;
	} else if (index == 10) {
		matWorld = g_matWorld011;
		draw_face = g_draw_face011;
	} else if (index == 11) {
		matWorld = g_matWorld012;
		draw_face = g_draw_face012;
	} else if (index == 12) {
		matWorld = g_matWorld013;
		draw_face = g_draw_face013;
	} else if (index == 13) {
		matWorld = g_matWorld014;
		draw_face = g_draw_face014;
	} else if (index == 14) {
		matWorld = g_matWorld015;
		draw_face = g_draw_face015;
	} else {
		matWorld = g_matWorld016;
		draw_face = g_draw_face016;
	}
//float g_box_dep;
//float g_box_width;
//float g_box_height;

    //draw_face�͕Ǖ����Ƀr�b�g�������Ă���
    //&b 00abcdef
    //
    //���}��BOX�̓W�J������Ԃ̐}
    //
    //                   ^y
    //              z��  | 
    //                 \ | 
    //                  c| 
    // ----���@��--- a b d f ---- -> x
    //                   |e
    //                   | \
    //                   |  \   
	//  u v
	// (0,0)      0.25                     ��u
	//       +------+------+------+------+
	//       |      |        Z+          |
	//       |      |       ��c          |
	//  0.25 +  X+  +--------------------+
	//       | ��f  |        Y-          |
	//       |      |       ��d          |
	//   0.5 +------+--------------------+
	//       |      |        Y+          |
	//       |      |       ��a          |
	//  0.75 +  X-  +--------------------+
	//       | ��b  |        Z-          |
	//       |      |       ��e          |
	//       +------+------+------+------+
	//    ��                                (1,1)
	//    v

    //                          00abcdef
  	if (draw_face >= 32) {  //&b00100000
        draw_face -= 32;
    } else {
        //���(��a)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x && 
            0.5  < prm_uv.y && prm_uv.y < 0.75 ) 
		{
            prm_pos.xyz = 0;
        }
    }

    //                          00abcdef
  	if (draw_face >= 16) {  //&b00010000
        draw_face -= 16;
    } else {
        //����(��b)���`��s�v�̏ꍇ
        if (                   prm_uv.x < 0.25 &&
            0.5  < prm_uv.y                       ) 
		{
            prm_pos.xyz = 0;
        }
    }
    //                          00abcdef
  	if (draw_face >= 8) {   //&b00001000
        draw_face -= 8;
    } else {
        //������(��c)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x && 
                               prm_uv.y < 0.25 ) 
		{
            prm_pos.xyz = 0;
        }
    }
    //                          00abcdef
   	if (draw_face >= 4) {   //&b00000100
        draw_face -= 4;
    } else {
        //���(��d)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x &&
            0.25 < prm_uv.y && prm_uv.y < 0.5 ) 
		{
            prm_pos.xyz = 0;
        }
    }
    //                          00abcdef
  	if (draw_face >= 2) {   //&b00000010
        draw_face -= 2;
    } else {
        //�E����(��e)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x &&
            0.75 < prm_uv.y                    ) 
		{
            prm_pos.xyz = 0;
        } 
    }
    //                          00abcdef
  	if (draw_face >= 1) {   //&b00000001
        draw_face -= 1;
    } else {
        //����������(��f)���`��s�v�̏ꍇ
        if (                    prm_uv.x < 0.25 &&
                                prm_uv.y < 0.5    ) 
		{
            prm_pos.xyz = 0;
        }
    }

//    float4 colMaterialDiffuse = float4(1.0, 1.0, 1.0, 1.0);

	//World*View*�ˉe�ϊ�
	out_vs.pos = mul(mul(mul( prm_pos, matWorld ), g_matView ), g_matProj);
	//UV�͂��̂܂�
	out_vs.uv = prm_uv;

    //���_�J���[�v�Z

	//�@���� World �ϊ����Đ��K��
    float3 normal = normalize(mul(prm_normal, matWorld)); 	
    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
	float power = max(dot(normal, -g_vecLightDirection ), 0);      
	//Ambient���C�g�F�ADiffuse���C�g�F�ADiffuse���C�g�����A�}�e���A���F ���l�������J���[�쐬�B      
	out_vs.col = (g_colLightAmbient + (g_colLightDiffuse*power));// * colMaterialDiffuse;
	//���t�H�O
	//out_vs.col.a = colMaterialDiffuse.a;
	if (out_vs.pos.z > g_zf*0.5) { // �ŉ��� 1/2 ��艜�̏ꍇ���X�ɓ�����
    	out_vs.col.a *= (-1.0/(g_zf*0.5)*out_vs.pos.z + 2.0);
	} 
//	if (out_vs.pos.z > g_zf*0.75) { //�ŉ��� 3/4 ��艜�̏ꍇ���X�ɓ�����
//    	out_vs.col.a *= (-1.0/(g_zf*0.25)*out_vs.pos.z + 4.0);
//	}
	//�}�X�^�[��
	out_vs.col.a *= g_alpha_master;
	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDx9PS_GroundBox(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_col;

    //Blinker���l��
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
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

technique GroundBoxTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_GroundBox();
		PixelShader  = compile ps_2_0 GgafDx9PS_GroundBox();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
		VertexShader = compile vs_2_0 GgafDx9VS_GroundBox();
		PixelShader  = compile ps_2_0 GgafDx9PS_GroundBox();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_GroundBox();
		PixelShader  = compile ps_2_0 PS_Flush();
	}
}

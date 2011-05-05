////////////////////////////////////////////////////////////////////////////////
// WallAAPrismActor�p�V�F�[�_�[
// �y�T�v�z
// �O�ǃv���Y���̕`����s���B
// ���_�o�b�t�@�ɁA�O�ǃv���Y����񂪁A10���J��Ԃ��l�ߍ���ł���B
// �X�e�[�g�⃌�W�X�^�̍X�V���s�킸�A�P��� �`��ŁA�ő�
// 10�I�u�W�F�N�g�܂ŕ`��B��������_���B
// author : Masatoshi Tsuge
// date:2011/01/10
////////////////////////////////////////////////////////////////////////////////
//�G���[����̂��߂ɂƂ肠�����ǉ���ł����Ƃ���
float3 g_posCam;
float g_specular;
float g_specular_power;

float g_distance_AlphaTarget;
float g_wall_dep;    //�ǃu���b�N�̒����iX���W�������j
float g_wall_height; //�ǃu���b�N�̍����iY���W�������j
float g_wall_width;  //�ǃu���b�N�̕��iZ���W������)
int g_pos_prism;


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
float4x4 g_matWorld017;
//float4x4 g_matWorld018;
//float4x4 g_matWorld019;
//float4x4 g_matWorld020;

#define POS_PRISM_nn    1 
#define POS_PRISM_np    2 
#define POS_PRISM_pn    4 
#define POS_PRISM_pp    8 
#define POS_PRISM_XY    16
#define POS_PRISM_YZ    32
#define POS_PRISM_ZX    64

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
OUT_VS GgafDx9VS_WallAAPrism(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float  prm_object_index  : PSIZE , // ���f���̃C���f�b�N�X�i���ڂ̃I�u�W�F�N�g���j
      float3 prm_normal : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv     : TEXCOORD0      // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	//���[���h�ϊ��s������蓖�Ă�
	int index = (int)prm_object_index; 
	float4x4 matWorld;
	if (index == 0) {
		matWorld = g_matWorld001;
	} else if (index == 1) {
		matWorld = g_matWorld002;
	} else if (index == 2) {
		matWorld = g_matWorld003;
	} else if (index == 3) {
		matWorld = g_matWorld004;
	} else if (index == 4) {
		matWorld = g_matWorld005;
	} else if (index == 5) {
		matWorld = g_matWorld006;
	} else if (index == 6) {
		matWorld = g_matWorld007;
	} else if (index == 7) {
		matWorld = g_matWorld008;
	} else if (index == 8) {
		matWorld = g_matWorld009;
	} else if (index == 9) {
		matWorld = g_matWorld010;
//	} else if (index == 10) {
//		matWorld = g_matWorld011;
//	} else if (index == 11) {
//		matWorld = g_matWorld012;
//	} else if (index == 12) {
//		matWorld = g_matWorld013;
//	} else if (index == 13) {
//		matWorld = g_matWorld014;
//	} else if (index == 14) {
//		matWorld = g_matWorld015;
//	} else if (index == 15) {
//		matWorld = g_matWorld016;
//	} else if (index == 16) {
//		matWorld = g_matWorld017;
//	} else if (index == 17) {
//		matWorld = g_matWorld018;
//	} else if (index == 18) {
//		matWorld = g_matWorld019;
	} else {
		matWorld = g_matWorld011;
	} 
    //�`��ʔԍ���񂪁A���[���h�ϊ��s���matWorld._14 �ɖ��ߍ��܂�Ă���
	int draw_face = matWorld._14;
	int pos_prism = matWorld._24;
	//���̍s��l�ɖ߂��Ă���
    matWorld._14 = 0; 
    matWorld._24 = 0; //���̍s��l�ɖ߂��Ă���

    //UV�ɂ��ǂ̖ʂ̒��_�����f���A
    //�`��s�v�Ȗʂ̒��_�̏ꍇ�͉��Ƃ�����i�W�I���g���V�F�[�_�[�g�������G�j

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
            return out_vs;
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
            return out_vs;
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
            return out_vs;
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
            return out_vs;
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
            return out_vs;
        } 
    }
    //                          00abcdef
  	if (draw_face >= 1) {   //&b00000001
       // draw_face -= 1;
    } else {
        //����������(��f)���`��s�v�̏ꍇ
        if (                    prm_uv.x < 0.25 &&
                                prm_uv.y < 0.5    ) 
		{
            return out_vs;
        }
    }

    //BOX�̂P�ʂ𖳗������ăv���Y���^�ɕό`������
	float ah,fh;
	if (pos_prism >= POS_PRISM_ZX) {   
		//�{X -X �̖ʂ��v���Y���̎΂ߖʂɂȂ�Ȃ��悤�ɂ���
		// ZX �� XZ���ʂƌ���
		pos_prism -= POS_PRISM_ZX;
		ah = g_wall_width / g_wall_dep / 2.0; //�X�� z/x �i�X�� x/z �ł͂Ȃ��āj
		//ah = g_wall_height / g_wall_dep / 2.0; //�X�� y/x
		fh = g_wall_dep/2.0;
		if (pos_prism == POS_PRISM_pp) {
			prm_pos.z = (prm_pos.z * ((prm_pos.x+fh)/g_wall_dep))       - ((prm_pos.x-fh)*ah);
		} else if (pos_prism == POS_PRISM_pn) {
			prm_pos.z = (prm_pos.z * (1.0-((prm_pos.x+fh)/g_wall_dep))) + ((prm_pos.x+fh)*ah);
		} else if (pos_prism == POS_PRISM_np) { 
			prm_pos.z = (prm_pos.z * ((prm_pos.x+fh)/g_wall_dep))       + ((prm_pos.x-fh)*ah);
		} else { //if (pos_prism == POS_PRISM_nn) {
			prm_pos.z = (prm_pos.z * (1.0-((prm_pos.x+fh)/g_wall_dep))) - ((prm_pos.x+fh)*ah);
		}
	} else if (pos_prism >= POS_PRISM_YZ) {   
		//�{Z -Z �̖ʂ��v���Y���̎΂ߖʂɂȂ�Ȃ��悤�ɂ���
		pos_prism -= POS_PRISM_YZ;
		ah = g_wall_height / g_wall_width / 2.0; //�X�� y/z
		fh = g_wall_width/2.0;                   //�X����
		if (pos_prism == POS_PRISM_pp) {
			prm_pos.y = (prm_pos.y * ((prm_pos.z+fh)/g_wall_width))       - ((prm_pos.z-fh)*ah);
		} else if (pos_prism == POS_PRISM_pn) {
			prm_pos.y = (prm_pos.y * (1.0-((prm_pos.z+fh)/g_wall_width))) + ((prm_pos.z+fh)*ah);
		} else if (pos_prism == POS_PRISM_np) { 
			prm_pos.y = (prm_pos.y * ((prm_pos.z+fh)/g_wall_width))       + ((prm_pos.z-fh)*ah);
		} else { //if (pos_prism == POS_PRISM_nn) {
			prm_pos.y = (prm_pos.y * (1.0-((prm_pos.z+fh)/g_wall_width))) - ((prm_pos.z+fh)*ah);
		}
	} else { //if (pos_prism >= POS_PRISM_XY) {   
		//�{X -X �̖ʂ��v���Y���̎΂ߖʂɂȂ�Ȃ��悤�ɂ���
		pos_prism -= POS_PRISM_XY;
		ah = g_wall_height / g_wall_dep / 2.0; //�X�� y/x
		fh = g_wall_dep/2.0;                   //�X����
		if (pos_prism == POS_PRISM_pp) {
			prm_pos.y = (prm_pos.y * ((prm_pos.x+fh)/g_wall_dep))       - ((prm_pos.x-fh)*ah);
		} else if (pos_prism == POS_PRISM_pn) {
			prm_pos.y = (prm_pos.y * ((prm_pos.x+fh)/g_wall_dep))       + ((prm_pos.x-fh)*ah);
		} else if (pos_prism == POS_PRISM_np) { 
			prm_pos.y = (prm_pos.y * (1.0-((prm_pos.x+fh)/g_wall_dep))) + ((prm_pos.x+fh)*ah);
		} else { //if (pos_prism == POS_PRISM_nn) {
			prm_pos.y = (prm_pos.y * (1.0-((prm_pos.x+fh)/g_wall_dep))) - ((prm_pos.x+fh)*ah);
		}
	}
	//����
	//(prm_pos.y * ((prm_pos.x+fh)/g_wall_dep))   �E�E�E ��[���L���b�Ƃ܂Ƃ߂�v�Z
	//+ ((prm_pos.x-fh)*ah);                      �E�E�E ��[�𐅕��ɂ���v�Z

	//World*View*�ˉe�ϊ�
	out_vs.pos = mul(mul(mul( prm_pos, matWorld ), g_matView ), g_matProj);

	//UV�͂��̂܂�
	out_vs.uv = prm_uv;

    //���_�J���[�v�Z

	//�@���� World �ϊ����Đ��K��
    float3 normal = normalize(mul(prm_normal, matWorld)); 	
    normal.x+=0.5; //�l0.5�͕ǖʂɂ����������𓖂Ă邽��
                   //���C�g�x�N�g���� XYZ=0.819232,-0.573462,0
    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
	float power = max(dot(normal, float3(-0.819232,0.573462,0)), 0);      
	//Ambient���C�g�F�ADiffuse���C�g�F�ADiffuse���C�g���� ���l�������J���[�쐬�B      
	out_vs.col = (g_colLightAmbient + (g_colLightDiffuse*power));// * �}�e���A���F����colMaterialDiffuse;
	//���t�H�O
	//out_vs.col.a = colMaterialDiffuse.a;
	if (out_vs.pos.z > (g_zf*0.9)*0.5) { // �ŉ��� 1/2 ��艜�̏ꍇ���X�ɓ�����
    	out_vs.col.a *= (-1.0/((g_zf*0.9)*0.5)*out_vs.pos.z + 2.0);
	} 
//	if (out_vs.pos.z > g_zf*0.75) { //�ŉ��� 3/4 ��艜�̏ꍇ���X�ɓ�����
//    	out_vs.col.a *= (-1.0/(g_zf*0.25)*out_vs.pos.z + 4.0);
//	}
    //���@����O�̓�
	if ( out_vs.pos.z < g_distance_AlphaTarget) {
		out_vs.col.a = (out_vs.pos.z + 1.0)  / (g_distance_AlphaTarget*2);
	}
	//�}�X�^�[��
	out_vs.col.a *= g_alpha_master;
	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDx9PS_WallAAPrism(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0
) : COLOR  {
    if (prm_col.a == 0) {
        return 0;
    }
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

technique WallAAPrismTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_3_0  GgafDx9VS_WallAAPrism();
		PixelShader  = compile ps_3_0  GgafDx9PS_WallAAPrism();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
		VertexShader = compile vs_3_0  GgafDx9VS_WallAAPrism();
		PixelShader  = compile ps_3_0  GgafDx9PS_WallAAPrism();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_3_0  GgafDx9VS_WallAAPrism();
		PixelShader  = compile ps_3_0  PS_Flush();
	}
}

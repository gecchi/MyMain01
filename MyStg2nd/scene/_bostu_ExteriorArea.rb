
class Veartex
  attr_accessor :X ,:Y, :Z
  def initialize
    @X = 0
    @Y = 0
    @Z = 0
  end
end

class Box
  attr_accessor :X ,:Y, :Z
  def initialize
    @X = 0
    @Y = 0
    @Z = 0
    @M = 0
  end
end

class ExteriorArea
  attr_accessor :width ,:height, :len
  attr_accessor :area

  KARA_VAL = -1
  KABE_VAL = 1
  FULL_VAL = -2

  FACE_A_BIT = 0b100000
  FACE_B_BIT = 0b010000
  FACE_C_BIT = 0b001000
  FACE_D_BIT = 0b000100
  FACE_E_BIT = 0b000010
  FACE_F_BIT = 0b000001

  FACE_A_IDX = 5
  FACE_B_IDX = 4
  FACE_C_IDX = 3
  FACE_D_IDX = 2
  FACE_E_IDX = 1
  FACE_F_IDX = 0


  def initialize(prm_len, prm_height, prm_width)
    @width = prm_width
    @height = prm_height
    @len = prm_len


    @area = Array.new( @len, KARA_VAL )
    @area.each_index { |x|
      @area[x] = Array.new( @height, KARA_VAL )
      @area[x].each_index { |y|
          @area[x][y] = Array.new( @width, KARA_VAL )
      }
    }
  end

  #BOX�U�ʂ̓��A�Œ���`�悵�Ȃ���΂����Ȃ��ʂ����
  def getAnalyze01
     ret = ExteriorArea.new(@len, @height, @width)

     for x in 0..@len-1
      for y in 0..@height-1
        for z in 0..@width-1
          type = 0b111111
          if @area[x][y][z] == KARA_VAL then
            ret.area[x][y][z] = KARA_VAL
          elsif @area[x][y][z] == FULL_VAL then
            ret.area[x][y][z] = FULL_VAL

          elsif @area[x][y][z] == KABE_VAL then
            #6�ʂ̊J����𒲂ׂ�
            #�J���Ă���r�b�g���Z�b�g�����
            # 0b 00abcdef

            #    c
            # a b d f
            #      e

            if (x-1 >= 0 && @area[x-1][y][z] != KARA_VAL) then #b���J���Ă���
              #               abcdef
              type = type ^ FACE_B_BIT
            end

            if (x+1 <= @len-1 && @area[x+1][y][z] != KARA_VAL) then #f���J���Ă���
              #               abcdef
              type = type ^ FACE_F_BIT
            end

            if (y-1 >= 0 && @area[x][y-1][z] != KARA_VAL) then #d���J���Ă���
              #               abcdef
              type = type ^ FACE_D_BIT
            end

            if (y+1 <= @height-1 && @area[x][y+1][z] != KARA_VAL) then #a���J���Ă���
              #               abcdef
              type = type ^ FACE_A_BIT
            end

            if (z-1 >= 0         && @area[x][y][z-1] != KARA_VAL) then #e���J���Ă���
              #               abcdef
              type = type ^ FACE_E_BIT
            end

            if (z+1 <= @width-1  && @area[x][y][z+1] != KARA_VAL) then #c���J���Ă���
              #               abcdef
              type = type ^ FACE_C_BIT
            end

#            ret.area[x][y][z] = sprintf("%02d ", type)
            ret.area[x][y][z] = type
          end
        end
      end
    end

    return ret

  end

  #BOX�̕`��s�v�̖ʁi�J���Ă���ʂƌĂԁj�����ɁA
  #�����蔻��AAB��L�΂��邩�ǂ������
  def getAnalyze02
    ret = ExteriorArea.new(@len, @height, @width)

    for x in 0..@len-1
      for y in 0..@height-1
        for z in 0..@width-1
          ret.area[x][y][z] = [0,0,0,0,0,0]

          if @area[x][y][z] == KARA_VAL then

            ret.area[x][y][z] = [0,0,0,0,0,0]

          elsif @area[x][y][z] == FULL_VAL then
             next
          else
            ret.area[x][y][z] = [1,1,1,1,1,1]
            #6�ʂ̊J���Ă�������̓����蔻�蒷����ݒ�
            #abcdef

            #    c
            # a b d f
            #      e

            #b���J���Ă���        543210
            #                     abcdef

#            if @area[x][y][z] & FACE_B_BIT == 0 then
#              #b�����ɂǂ̂��炢�����蔻���L�΂��΂������H
#              hitarea_idx = 1
#              hitarea_len = 1
#              while true
#                if (x-hitarea_idx > 0 &&  @area[x-hitarea_idx][y][z] == FULL_VAL) then
#                  hitarea_len += 1
#                else
#                  break;
#                end
#                hitarea_idx += 1
#              end
#              ret.area[x][y][z][FACE_B_IDX] = hitarea_len
#            end
#
#            #f���J���Ă���        543210
#            if @area[x][y][z] & FACE_F_BIT == 0 then
#              #f�����ɂǂ̂��炢�����蔻���L�΂��΂������H
#              hitarea_idx = 1
#              hitarea_len = 1
#              while true
#                if (x+hitarea_idx <= @len-1 &&  @area[x+hitarea_idx][y][z] == FULL_VAL) then
#                  hitarea_len += 1
#                else
#                  break;
#                end
#                hitarea_idx += 1
#              end
#              ret.area[x][y][z][FACE_F_IDX] = hitarea_len
#            end

            #d���J���Ă���        543210
            #                     abcdef
            if @area[x][y][z] & FACE_D_BIT == 0 then
              #d�����ɂǂ̂��炢�����蔻���L�΂��΂������H
              hitarea_idx = 1
              hitarea_len = 1
              while true
                if (y-hitarea_idx >= 0 &&  @area[x][y-hitarea_idx][z] == FULL_VAL) then
                  hitarea_len += 1
                else
                  break;
                end
                hitarea_idx += 1
              end
              ret.area[x][y][z][FACE_D_IDX] = hitarea_len
            end

            #a���J���Ă���        543210
            #                     abcdef
            if @area[x][y][z] & FACE_A_BIT == 0 then
              #a�����ɂǂ̂��炢�����蔻���L�΂��΂������H
              hitarea_idx = 1
              hitarea_len = 1
              while true
                if (y+hitarea_idx <= @height-1 &&  @area[x][y+hitarea_idx][z] == FULL_VAL) then
                  hitarea_len += 1
                else
                  break;
                end
                hitarea_idx += 1
              end
              ret.area[x][y][z][FACE_A_IDX] = hitarea_len
            end

            #e���J���Ă���        543210
            #                     abcdef
            if @area[x][y][z] & FACE_E_BIT == 0 then
              #e�����ɂǂ̂��炢�����蔻���L�΂��΂������H
              hitarea_idx = 1
              hitarea_len = 1
              while true
                if (z-hitarea_idx >= 0 &&  @area[x][y][z-hitarea_idx] == FULL_VAL) then
                  hitarea_len += 1
                else
                  break;
                end
                hitarea_idx += 1
              end
              ret.area[x][y][z][FACE_E_IDX] = hitarea_len
            end

            #c���J���Ă���        543210
            #                     abcdef
            if @area[x][y][z] & FACE_C_BIT == 0 then
              #e�����ɂǂ̂��炢�����蔻���L�΂��΂������H
              hitarea_idx = 1
              hitarea_len = 1
              while true
                if (z+hitarea_idx <= @width-1 &&  @area[x][y][z+hitarea_idx] == FULL_VAL) then
                  hitarea_len += 1
                else
                  break;
                end
                hitarea_idx += 1
              end
#              p "hitarea_len=",hitarea_len
#              p "befor ",ret.area[x][y][z]
              ret.area[x][y][z][FACE_C_IDX] = hitarea_len
#              p "after ",ret.area[x][y][z]
            end


#           print "@area[",x,"][",y,"][",z,"]=",@area[x][y][z],"\n"
#           print "@area[",x,"][",y,"][",z,"] & FACE_C_BIT=",(@area[x][y][z] & FACE_C_BIT),"\n"

          end

        end
      end
    end
    return ret
  end



  #getAnalyze02 �ŊJ���Ă���ʕ����ɐL�т������蔻��AAB��
  #+Y -Y +Z -Z �����ɘA���ł��邩�ǂ������
  def getAnalyze03
    ret = ExteriorArea.new(@len, @height, @width)

    for x in 0..@len-1
      for y in 0..@height-1
        for z in 0..@width-1
          if @area[x][y][z] == KARA_VAL then
             next
          elsif @area[x][y][z] == FULL_VAL then
             next
          elsif  @area[x][y][z] == [0,0,0,0,0,0] then
             ret.area[x][y][z] = @area[x][y][z]
             next
          elsif ret.area[x][y][z] == [0,0,0,0,0,0] then
             next
          else
            ret.area[x][y][z] = @area[x][y][z]
            #    c
            # a b d f
            #      e

            # 543210
            # abcdef

            #+Y -Y +Z -Z �̓����蔻��ƘA���ł��邩�l����

            #+Y�����̌���
            same_Y_inc = 0
            if (y+1 <= @height-1) then
              (y+1).upto(@height-1) do |iy|
                if (ret.area[x][y][z] ==  @area[x][iy][z]) then #�����傫���Ȃ�ΘA��
                  same_Y_inc += 1
                elsif (ret.area[x][y][z][FACE_B_IDX] == @area[x][iy][z][FACE_B_IDX] &&
                       ret.area[x][y][z][FACE_C_IDX] == @area[x][iy][z][FACE_C_IDX] &&
                       ret.area[x][y][z][FACE_D_IDX] == @area[x][iy][z][FACE_D_IDX] &&
                       ret.area[x][y][z][FACE_E_IDX] == @area[x][iy][z][FACE_E_IDX] &&
                       ret.area[x][y][z][FACE_F_IDX] == @area[x][iy][z][FACE_F_IDX] ) then

                  same_Y_inc += @area[x][iy][z][FACE_A_IDX]
                else
                  break
                end
              end
            end
            if (same_Y_inc > 0) then
              #��a�����ɂ��L�������������
              ret.area[x][y][z][FACE_A_IDX] += same_Y_inc
              #��a�����L����ɂ���Ă܂��Ȃ���c��̓����蔻��͕s�v
              (y+1).upto((y+1)+(same_Y_inc-1)) do |iy|
                ret.area[x][iy][z] = [0,0,0,0,0,0]
              end
            end

            #-Y�����̌���
            same_Y_dec = 0
            if (y-1 >= 0) then
              (y-1).downto(0) do |iy|
                if (ret.area[x][y][z] ==  @area[x][iy][z]) then
                  same_Y_dec += 1
                elsif (ret.area[x][y][z][FACE_A_IDX] == @area[x][iy][z][FACE_A_IDX] &&
                       ret.area[x][y][z][FACE_B_IDX] == @area[x][iy][z][FACE_B_IDX] &&
                       ret.area[x][y][z][FACE_C_IDX] == @area[x][iy][z][FACE_C_IDX] &&
                       ret.area[x][y][z][FACE_E_IDX] == @area[x][iy][z][FACE_E_IDX] &&
                       ret.area[x][y][z][FACE_F_IDX] == @area[x][iy][z][FACE_F_IDX] ) then

                  same_Y_dec += @area[x][iy][z][FACE_D_IDX]
                else
                  break
                end
              end
            end
            if (same_Y_dec > 0) then
              #��d�����ɂ��L�������������
              ret.area[x][y][z][FACE_D_IDX] += same_Y_dec
              #��d�����L����ɂ���Ă܂��Ȃ���c��̓����蔻��͕s�v
              (y-1).downto((y-1)-(same_Y_dec-1)) do |iy|
                ret.area[x][iy][z] = [0,0,0,0,0,0]
              end
            end

            #Y�����ɘA�������Ȃ�΁AZ�������ւ͒P���A���o���Ȃ��̂ł���ŏI���Ƃ���
            if same_Y_dec > 0 || same_Y_inc > 0 then
              next
            end

            #+Z�����̌���
            same_Z_inc = 0
            if (z+1 <= @width-1) then
              (z+1).upto(@width-1) do |iz|
                if (ret.area[x][y][z] ==  @area[x][y][iz]) then
                  same_Z_inc += 1
                elsif (ret.area[x][y][z][FACE_A_IDX] == @area[x][y][iz][FACE_A_IDX] &&
                       ret.area[x][y][z][FACE_B_IDX] == @area[x][y][iz][FACE_B_IDX] &&
                       ret.area[x][y][z][FACE_D_IDX] == @area[x][y][iz][FACE_D_IDX] &&
                       ret.area[x][y][z][FACE_E_IDX] == @area[x][y][iz][FACE_E_IDX] &&
                       ret.area[x][y][z][FACE_F_IDX] == @area[x][y][iz][FACE_F_IDX] ) then

                  same_Z_inc += @area[x][y][iz][FACE_C_IDX]
                else
                  break
                end
              end
            end
            if (same_Z_inc > 0) then
              #��c�����ɂ��L�������������
              ret.area[x][y][z][FACE_C_IDX] += same_Z_inc
              #��c�����L����ɂ���Ă܂��Ȃ���c��̓����蔻��͕s�v
              (z+1).upto((z+1)+(same_Z_inc-1)) do |iz|
                ret.area[x][y][iz] = [0,0,0,0,0,0]
              end
            end

            #-Z�����̌���
            same_Z_dec = 0
            if (z-1 >= 0) then
              (z-1).downto(0) do |iz|
                if (ret.area[x][y][z] ==  @area[x][y][iz]) then
                  same_Z_dec += 1
                elsif (ret.area[x][y][z][FACE_A_IDX] == @area[x][y][iz][FACE_A_IDX] &&
                       ret.area[x][y][z][FACE_B_IDX] == @area[x][y][iz][FACE_B_IDX] &&
                       ret.area[x][y][z][FACE_C_IDX] == @area[x][y][iz][FACE_C_IDX] &&
                       ret.area[x][y][z][FACE_D_IDX] == @area[x][y][iz][FACE_D_IDX] &&
                       ret.area[x][y][z][FACE_F_IDX] == @area[x][y][iz][FACE_F_IDX] ) then

                  same_Z_dec += @area[x][y][iz][FACE_E_IDX]
                else
                  break
                end
              end
            end
            if (same_Z_dec > 0) then
              #��e�����ɂ��L�������������
              ret.area[x][y][z][FACE_E_IDX] += same_Z_dec
              #��e�����L����ɂ���Ă܂��Ȃ���c��̓����蔻��͕s�v
              (z-1).downto((z-1)-(same_Z_dec-1)) do |iz|
                ret.area[x][y][iz] = [0,0,0,0,0,0]
              end
            end

          end
#           print "@area[",x,"][",y,"][",z,"]=",@area[x][y][z],"\n"
#           print "@area[",x,"][",y,"][",z,"] & FACE_C_BIT=",(@area[x][y][z] & FACE_C_BIT),"\n"
        end
      end
    end
    return ret
  end


  #getAnalyze03 �ɂ��A�����ꂽ�����蔻��AAB�ɂ���
  #+X -X �����ɘA���ł��邩�ǂ������
  #�����F�ő�A����
  def getAnalyze04(prm_max_x_colliwall_num)

    max_x_colliwall_num = prm_max_x_colliwall_num
    ret = ExteriorArea.new(@len, @height, @width)

    (@len-1).downto(0) do |x| #���K���烋�[�v
      for y in 0..@height-1
        for z in 0..@width-1
          if @area[x][y][z] == [0,0,0,0,0,0] then
            ret.area[x][y][z] = @area[x][y][z]
            next
          elsif ret.area[x][y][z] == [0,0,0,0,0,0] then
            next
          else
            ret.area[x][y][z] = @area[x][y][z]

            #    c
            # a b d f
            #      e

            # 543210
            # abcdef

            #+X -X �̓����蔻��ƘA���ł��邩�l����
            #-X�����̌���
            same_X_dec = 0
            if (x-1 >= 0) then
              (x-1).downto(0) do |ix|
                if (ret.area[x][y][z] ==  @area[ix][y][z]) then
                  same_X_dec += 1
                  if same_X_dec >= max_x_colliwall_num then
                    break #�ō� max_x_colliwall_num �܂ł����A�����Ȃ��悤�ɂ���
                  end
                else
                  break
                end
              end
            end
            if (same_X_dec > 0) then
              #��b�����ɂ��L�������������
              ret.area[x][y][z][FACE_B_IDX] += same_X_dec
              #��b�����L����ɂ���Ă܂��Ȃ���c��̓����蔻��͕s�v
              (x-1).downto((x-1)-(same_X_dec-1)) do |ix|
                ret.area[ix][y][z] = [0,0,0,0,0,0]
              end
            end

            #+X�����̌���
            same_X_inc = 0
            if (x+1 <= @len-1) then
              (x+1).upto(@len-1) do |ix|
                if (ret.area[x][y][z] == @area[ix][y][z]) then
                  same_X_inc += 1
                  if same_X_inc >= max_x_colliwall_num then
                    break #�ō� max_x_colliwall_num �܂ł����A�����Ȃ��悤�ɂ���
                  end
                else
                  break
                end
              end
            end
            if (same_X_inc > 0) then
              #��f�����ɂ��L�������������
              ret.area[x][y][z][FACE_F_IDX] += same_X_inc
              #��f�����L����ɂ���Ă܂��Ȃ���c��̓����蔻��͕s�v
              (x+1).upto((x+1)+(same_X_inc-1)) do |ix|
                ret.area[ix][y][z] = [0,0,0,0,0,0]
              end
            end

          end
        end
      end
    end
    return ret
  end


  #[0][0][0]���� FULL_VAL �œh��Ԃ�
  def fullfull

    @area[0][0][0] = FULL_VAL
     for x in 0..@len-1
      for y in 0..@height-1
        for z in 0..@width-1

          if @area[x][y][z] == KARA_VAL && (
               (x-1 >= 0 && @area[x-1][y][z] == FULL_VAL) ||
               (x+1 <= @len-1 && @area[x+1][y][z] == FULL_VAL) ||
               (y-1 >= 0 && @area[x][y-1][z] == FULL_VAL) ||
               (y+1 <= @height-1 && @area[x][y+1][z] == FULL_VAL) ||
               (z-1 >= 0         && @area[x][y][z-1] == FULL_VAL) ||
               (z+1 <= @width-1  && @area[x][y][z+1] == FULL_VAL)  ) then

            begin
              full(x, y, z, FULL_VAL)
            rescue Exception
              #�ċA�ɂ��X�^�b�N�I�[�o�[��O�𖳗����ׂ��Ă���
            end

          end
        end
      end
    end

  end

  def full(x, y, z, val)
    return if x < 0 || x > @len-1
    return if y < 0 || y > @height-1
    return if z < 0 || z > @width-1
    return if @area[x][y][z] != KARA_VAL

    @area[x][y][z] = val
    if x-1 >= 0         && @area[x-1][y][z] == KARA_VAL then
      fullfull(x-1, y, z, val)
    end

    if x+1 <= @len-1    && @area[x+1][y][z] == KARA_VAL then
      fullfull(x+1, y, z, val)
    end

    if y-1 >= 0         && @area[x][y-1][z] == KARA_VAL then
      fullfull(x, y-1, z, val)
    end

    if y+1 <= @height-1 && @area[x][y+1][z] == KARA_VAL then
      fullfull(x, y+1, z, val)
    end

    if z-1 >= 0         && @area[x][y][z-1] == KARA_VAL then
      fullfull(x, y, z-1, val)
    end

    if z+1 <= @width-1  && @area[x][y][z+1] == KARA_VAL then
      fullfull(x, y, z+1, val)
    end
  end


  #�f�o�b�O�p�o�͂��̂P
  def dump01
    for l in 0..@len-1
      print l,")------------------\n"
      #for h in (@height-1..0).include?(-1)
      (@height-1).downto(0) do |h| #Y���͉�����オ��
        (@width-1).downto(0) do |w| #Z���͉E���獶����(���ʂ��猩���ꍇ)
           printf("%02d ", @area[l][h][w])
#          print "(",@area[l][h][w],")"
#          print "[",l,"][",h,"][",w,"]="
#          p @area[l][h][w]
        end
        printf(" [%02d] ", h)
        print  "\n"
      end
      (@width-1).downto(0) do |w| #Z���͉E���獶����(���ʂ��猩���ꍇ)
        printf("%02d,", w)
      end
      print  "\n"
    end
  end

  #�f�o�b�O�p�o�͂��̂Q
  def dump02
    for l in 0..@len-1
      print l,")------------------\n"
      #for h in (@height-1..0).include?(-1)
      (@height-1).downto(0) do |h| #Y���͉�����オ��
         (@width-1).downto(0) do |w| #Z���͉E���獶����(���ʂ��猩���ꍇ)
#          printf("%02d", @area[l][h][w])
#          print "(",@area[l][h][w],")"
          print "[",l,"][",h,"][",w,"]="
          p @area[l][h][w]
        end
        print  "\n"
      end
    end
  end


end

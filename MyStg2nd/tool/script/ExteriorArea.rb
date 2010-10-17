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
            #6面の開き具合を調べる
            #開いているビットがセットされる
            # 0b 00abcdef

            #    c
            # a b d f
            #      e

            if (x-1 >= 0 && @area[x-1][y][z] != KARA_VAL) then #bが開いている
              #               abcdef
              type = type ^ FACE_B_BIT
            end

            if (x+1 <= @len-1 && @area[x+1][y][z] != KARA_VAL) then #fが開いている
              #               abcdef
              type = type ^ FACE_F_BIT
            end

            if (y-1 >= 0 && @area[x][y-1][z] != KARA_VAL) then #dが開いている
              #               abcdef
              type = type ^ FACE_D_BIT
            end

            if (y+1 <= @height-1 && @area[x][y+1][z] != KARA_VAL) then #aが開いている
              #               abcdef
              type = type ^ FACE_A_BIT
            end

            if (z-1 >= 0         && @area[x][y][z-1] != KARA_VAL) then #eが開いている
              #               abcdef
              type = type ^ FACE_E_BIT
            end

            if (z+1 <= @width-1  && @area[x][y][z+1] != KARA_VAL) then #cが開いている
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

            #6面の開いている方向の当たり判定長さを設定
            #abcdef

            #    c
            # a b d f
            #      e


            #bが開いている        543210
            #                     abcdef

#            if @area[x][y][z] & FACE_B_BIT == 0 then
#              #b方向にどのぐらい当たり判定を伸ばせばいいか？
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
#            #fが開いている        543210
#            if @area[x][y][z] & FACE_F_BIT == 0 then
#              #f方向にどのぐらい当たり判定を伸ばせばいいか？
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

            #dが開いている        543210
            #                     abcdef
            if @area[x][y][z] & FACE_D_BIT == 0 then
              #d方向にどのぐらい当たり判定を伸ばせばいいか？
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

            #aが開いている        543210
            #                     abcdef
            if @area[x][y][z] & FACE_A_BIT == 0 then
              #a方向にどのぐらい当たり判定を伸ばせばいいか？
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


            #eが開いている        543210
            #                     abcdef
            if @area[x][y][z] & FACE_E_BIT == 0 then
              #e方向にどのぐらい当たり判定を伸ばせばいいか？
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



            #cが開いている        543210
            #                     abcdef
            if @area[x][y][z] & FACE_C_BIT == 0 then
              #e方向にどのぐらい当たり判定を伸ばせばいいか？
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





  def getAnalyze03
    ret = ExteriorArea.new(@len, @height, @width)

    for x in 0..@len-1
      for y in 0..@height-1
        for z in 0..@width-1

#           p "@area[",x,"][",y,"][",z,"]=",@area[x][y][z],"\n"
#    p "ret.area[",x,"][",y,"][",z,"]=",ret.area[x][y][z],"\n"

          if @area[x][y][z] == KARA_VAL then
             next
          elsif @area[x][y][z] == FULL_VAL then
             next
          elsif  @area[x][y][z] == [0,0,0,0,0,0] then
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

            #+Y -Y +Z -Z の当たり判定と連結できるか考える

            #+Y方向の検討
            same_Y_inc = 0
            if (y+1 <= @height-1) then
              (y+1).upto(@height-1) do |iy|
                if (ret.area[x][y][z] ==  @area[x][iy][z]) then
                  same_Y_inc += 1
                end
              end
            end
            if (same_Y_inc > 0) then
              #面a方向にも広がりを持たせる
              ret.area[x][y][z][FACE_A_IDX] += same_Y_inc
              #面a方向広がりによってまかなわれる残りの当たり判定は不要
              (y+1).upto((y+1)+(same_Y_inc-1)) do |iy|
                ret.area[x][iy][z] = [0,0,0,0,0,0]
              end
            end
            #-Y方向の検討
            same_Y_dec = 0
            if (y-1 >= 0) then
              (y-1).downto(0) do |iy|
                if (ret.area[x][y][z] ==  @area[x][iy][z]) then
                  same_Y_dec += 1
                end
              end
            end
            if (same_Y_dec > 0) then
              #面d方向にも広がりを持たせる
              ret.area[x][y][z][FACE_C_IDX] += same_Y_dec
              #面d方向広がりによってまかなわれる残りの当たり判定は不要
              (y-1).downto((y-1)-(same_Y_dec-1)) do |iy|
                ret.area[x][iy][z] = [0,0,0,0,0,0]
              end
            end

            #+Z方向の検討
            same_Z_inc = 0
            if (z+1 <= @width-1) then
              (z+1).upto(@width-1) do |iz|
                if (ret.area[x][y][z] ==  @area[x][y][iz]) then
                  same_Z_inc += 1
                end
              end
            end
            if (same_Z_inc > 0) then
              #面c方向にも広がりを持たせる
              ret.area[x][y][z][FACE_C_IDX] += same_Z_inc
              #面c方向広がりによってまかなわれる残りの当たり判定は不要
              (z+1).upto((z+1)+(same_Z_inc-1)) do |iz|
                ret.area[x][y][iz] = [0,0,0,0,0,0]
              end
            end

            #-Z方向の検討
            same_Z_dec = 0
            if (z-1 >= 0) then
              (z-1).downto(0) do |iz|
                if (ret.area[x][y][z] ==  @area[x][y][iz]) then
                  same_Z_dec += 1
                end
              end
            end
            if (same_Z_dec > 0) then
              #面e方向にも広がりを持たせる
              ret.area[x][y][z][FACE_E_IDX] += same_Z_dec
              #面e方向広がりによってまかなわれる残りの当たり判定は不要
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
              #スタックオーバーを潰す
              #print "."
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


  def dump01
    for l in 0..@len-1
      print l,")------------------\n"
      #for h in (@height-1..0).include?(-1)
      (@height-1).downto(0) do |h| #Y軸は下から上が正
        (@width-1).downto(0) do |w| #Z軸は右から左が正(正面から見た場合)
           printf("%02d ", @area[l][h][w])
#          print "(",@area[l][h][w],")"
#          print "[",l,"][",h,"][",w,"]="
#          p @area[l][h][w]
        end
        printf(" [%02d] ", h)
        print  "\n"
      end
      (@width-1).downto(0) do |w| #Z軸は右から左が正(正面から見た場合)
        printf("%02d,", w)
      end
      print  "\n"
    end
  end

  def dump02
    for l in 0..@len-1
      print l,")------------------\n"
      #for h in (@height-1..0).include?(-1)
      (@height-1).downto(0) do |h| #Y軸は下から上が正
         (@width-1).downto(0) do |w| #Z軸は右から左が正(正面から見た場合)
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

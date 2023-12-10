declare i32 @getch( )
declare i32 @getint( )
declare void @putch( i32 )
declare void @putint( i32 )
declare void @putarray( i32, i32* )
declare void @_sysy_starttime( i32 )
declare void @_sysy_stoptime( i32 )
@N = global i32 0
define i32 @insert( i32* %r100, i32 %r101 ) {
bb1:
  %r158 = add i32 0, 0
  %r159 = add i32 0, 0
  %r160 = add i32 %r101, 0
  %r161 = add i32 0, 0
  %r162 = add i32 0, 0
  %r163 = add i32 0, 0
  br label %bb2

bb2:
  %r164 = phi i32 [ %r163, %bb1 ], [ %r172, %bb3 ]
  %r165 = add i32 %r160, 0
  %r166 = add i32 %r164, 0
  %r107 = getelementptr i32, i32* %r100, i32 %r166
  %r167 = load i32, i32* %r107
  %r109 = icmp sgt i32 %r165, %r167
  br i1 %r109, label %bb5, label %bb4

bb5:
  %r168 = add i32 %r164, 0
  %r169 = load i32, i32* @N
  %r112 = icmp slt i32 %r168, %r169
  br i1 %r112, label %bb3, label %bb4

bb3:
  %r170 = add i32 %r164, 0
  %r171 = add i32 %r170, 1
  %r172 = add i32 %r171, 0
  br label %bb2

bb4:
  %r173 = load i32, i32* @N
  %r174 = add i32 %r173, 0
  br label %bb6

bb6:
  %r175 = phi i32 [ %r174, %bb4 ], [ %r188, %bb7 ]
  %r176 = add i32 %r175, 0
  %r177 = add i32 %r164, 0
  %r118 = icmp sgt i32 %r176, %r177
  br i1 %r118, label %bb7, label %bb8

bb7:
  %r178 = add i32 %r175, 0
  %r179 = sub i32 %r178, 1
  %r180 = add i32 %r179, 0
  %r181 = add i32 %r175, 0
  %r123 = getelementptr i32, i32* %r100, i32 %r181
  %r182 = add i32 %r180, 0
  %r125 = getelementptr i32, i32* %r100, i32 %r182
  %r183 = load i32, i32* %r125
  store i32 %r183, i32* %r123
  %r184 = add i32 %r164, 0
  %r128 = getelementptr i32, i32* %r100, i32 %r184
  %r185 = add i32 %r160, 0
  store i32 %r185, i32* %r128
  %r186 = add i32 %r175, 0
  %r187 = sub i32 %r186, 1
  %r188 = add i32 %r187, 0
  br label %bb6

bb8:
  ret i32 0
}

define i32 @main( ) {
bb9:
  call void @_sysy_starttime(i32 27)
  store i32 10, i32* @N
  %r132 = alloca [ 11 x i32 ]
  %r133 = getelementptr [11 x i32 ], [11 x i32 ]* %r132, i32 0, i32 0
  store i32 1, i32* %r133
  %r134 = getelementptr [11 x i32 ], [11 x i32 ]* %r132, i32 0, i32 1
  store i32 3, i32* %r134
  %r135 = getelementptr [11 x i32 ], [11 x i32 ]* %r132, i32 0, i32 2
  store i32 4, i32* %r135
  %r136 = getelementptr [11 x i32 ], [11 x i32 ]* %r132, i32 0, i32 3
  store i32 7, i32* %r136
  %r137 = getelementptr [11 x i32 ], [11 x i32 ]* %r132, i32 0, i32 4
  store i32 8, i32* %r137
  %r138 = getelementptr [11 x i32 ], [11 x i32 ]* %r132, i32 0, i32 5
  store i32 11, i32* %r138
  %r139 = getelementptr [11 x i32 ], [11 x i32 ]* %r132, i32 0, i32 6
  store i32 13, i32* %r139
  %r140 = getelementptr [11 x i32 ], [11 x i32 ]* %r132, i32 0, i32 7
  store i32 18, i32* %r140
  %r141 = getelementptr [11 x i32 ], [11 x i32 ]* %r132, i32 0, i32 8
  store i32 56, i32* %r141
  %r142 = getelementptr [11 x i32 ], [11 x i32 ]* %r132, i32 0, i32 9
  store i32 78, i32* %r142
  %r189 = add i32 0, 0
  %r190 = add i32 0, 0
  %r191 = add i32 0, 0
  %r192 = call i32 @getint()
  %r193 = add i32 %r192, 0
  %r194 = add i32 %r193, 0
  %r195 = call i32 @insert(i32* %r132, i32 %r194)
  %r196 = add i32 %r195, 0
  br label %bb10

bb10:
  %r197 = phi i32 [ %r191, %bb9 ], [ %r208, %bb11 ]
  %r198 = add i32 %r197, 0
  %r199 = load i32, i32* @N
  %r150 = icmp slt i32 %r198, %r199
  br i1 %r150, label %bb11, label %bb12

bb11:
  %r200 = add i32 %r197, 0
  %r152 = getelementptr [11 x i32 ], [11 x i32 ]* %r132, i32 0, i32 %r200
  %r201 = load i32, i32* %r152
  %r202 = add i32 %r201, 0
  %r203 = add i32 %r202, 0
  call void @putint(i32 %r203)
  %r204 = add i32 10, 0
  %r205 = add i32 %r204, 0
  call void @putch(i32 %r205)
  %r206 = add i32 %r197, 0
  %r207 = add i32 %r206, 1
  %r208 = add i32 %r207, 0
  br label %bb10

bb12:
  call void @_sysy_stoptime(i32 54)
  ret i32 0
}


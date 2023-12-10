declare i32 @getch( )
declare i32 @getint( )
declare void @putch( i32 )
declare void @putint( i32 )
declare void @putarray( i32, i32* )
declare void @_sysy_starttime( i32 )
declare void @_sysy_stoptime( i32 )
define i32 @mod( i32 %r100, i32 %r102 ) {
bb1:
  %r147 = add i32 0, 0
  %r147 = add i32 %r100, 0
  %r149 = add i32 0, 0
  %r149 = add i32 %r102, 0
  %r150 = add i32 %r147, 0
  %r151 = add i32 %r147, 0
  %r152 = add i32 %r149, 0
  %r153 = sdiv i32 %r151, %r152
  %r154 = add i32 %r149, 0
  %r155 = mul i32 %r153, %r154
  %r156 = sub i32 %r150, %r155
  ret i32 %r156
}

define i32 @palindrome( i32 %r111 ) {
bb2:
  %r218 = add i32 0, 0
  %r218 = add i32 %r111, 0
  %r113 = alloca [ 4 x i32 ]
  %r221 = add i32 0, 0
  %r242 = add i32 0, 0
  %r221 = add i32 0, 0
  br label %bb3

bb3:
  %r221 = phi i32 [ %r221, %bb2 ], [ %r221, %bb4 ]
  %r218 = phi i32 [ %r218, %bb2 ], [ %r218, %bb4 ]
  %r187 = add i32 %r221, 0
  %r188 = icmp slt i32 %r187, 4
  br i1 %r188, label %bb4, label %bb5

bb4:
  %r212 = add i32 %r221, 0
  %r213 = getelementptr [4 x i32 ], [4 x i32 ]* %r113, i32 0, i32 %r212
  %r214 = add i32 %r218, 0
  %r215 = call i32 @mod(i32* %r214, i32 10)
  store i32 %r215, i32* %r213
  %r216 = add i32 %r218, 0
  %r217 = sdiv i32 %r216, 10
  %r218 = add i32 %r217, 0
  %r219 = add i32 %r221, 0
  %r220 = add i32 %r219, 1
  %r221 = add i32 %r220, 0
  br label %bb3

bb5:
  %r222 = getelementptr [4 x i32 ], [4 x i32 ]* %r113, i32 0, i32 0
  %r223 = load i32, i32* %r222
  %r224 = getelementptr [4 x i32 ], [4 x i32 ]* %r113, i32 0, i32 3
  %r225 = load i32, i32* %r224
  %r226 = icmp eq i32 %r223, %r225
  br i1 %r226, label %bb9, label %bb7

bb9:
  %r235 = getelementptr [4 x i32 ], [4 x i32 ]* %r113, i32 0, i32 1
  %r236 = load i32, i32* %r235
  %r237 = getelementptr [4 x i32 ], [4 x i32 ]* %r113, i32 0, i32 2
  %r238 = load i32, i32* %r237
  %r239 = icmp eq i32 %r236, %r238
  br i1 %r239, label %bb6, label %bb7

bb6:
  %r242 = add i32 1, 0
  br label %bb8

bb7:
  %r242 = add i32 0, 0
  br label %bb8

bb8:
  %r242 = phi i32 [ %r242, %bb6 ], [ %r242, %bb7 ]
  %r243 = add i32 %r242, 0
  ret i32 %r243
}

define i32 @main( ) {
bb10:
  call void @_sysy_starttime(i32 30)
  %r245 = add i32 0, 0
  %r245 = add i32 1221, 0
  %r260 = add i32 0, 0
  %r247 = add i32 %r245, 0
  %r248 = call i32 @palindrome(i32* %r247)
  %r260 = add i32 %r248, 0
  %r250 = add i32 %r260, 0
  %r251 = icmp eq i32 %r250, 1
  br i1 %r251, label %bb11, label %bb12

bb11:
  %r257 = add i32 %r245, 0
  call void @putint(i32* %r257)
  br label %bb13

bb12:
  %r260 = add i32 0, 0
  %r259 = add i32 %r260, 0
  call void @putint(i32* %r259)
  br label %bb13

bb13:
  %r260 = add i32 10, 0
  %r261 = add i32 %r260, 0
  call void @putch(i32* %r261)
  call void @_sysy_stoptime(i32 47)
  ret i32 0
}


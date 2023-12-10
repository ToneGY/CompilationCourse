declare i32 @getch( )
declare i32 @getint( )
declare void @putch( i32 )
declare void @putint( i32 )
declare void @putarray( i32, i32* )
declare void @_sysy_starttime( i32 )
declare void @_sysy_stoptime( i32 )
@a = global [ 10 x i32 ] zeroinitializer
@b = global i32 27
@c = global i32 1
define i32 @main( ) {
bb1:
  call void @_sysy_starttime(i32 4)
  %r121 = add i32 0, 0
  %r122 = add i32 0, 0
  %r123 = add i32 0, 0
  %r124 = add i32 0, 0
  br label %bb2

bb2:
  %r125 = phi i32 [ %r122, %bb1 ], [ %r150, %bb3 ]
  %r126 = add i32 %r125, 0
  %r127 = icmp slt i32 %r126, 10
  br i1 %r127, label %bb3, label %bb4

bb3:
  %r145 = add i32 %r125, 0
  %r146 = getelementptr [10 x i32 ], [10 x i32 ]* @a, i32 0, i32 %r145
  %r147 = add i32 %r125, 0
  store i32 %r147, i32* %r146
  %r148 = add i32 %r125, 0
  %r149 = add i32 %r148, 1
  %r150 = add i32 %r149, 0
  br label %bb2

bb4:
  %r128 = add i32 0, 0
  br label %bb5

bb5:
  %r129 = phi i32 [ %r124, %bb4 ], [ %r138, %bb6 ]
  %r130 = phi i32 [ %r128, %bb4 ], [ %r141, %bb6 ]
  %r131 = add i32 %r130, 0
  %r132 = icmp slt i32 %r131, 10
  br i1 %r132, label %bb6, label %bb7

bb6:
  %r133 = add i32 %r129, 0
  %r134 = add i32 %r130, 0
  %r135 = getelementptr [10 x i32 ], [10 x i32 ]* @a, i32 0, i32 %r134
  %r136 = load i32, i32* %r135
  %r137 = add i32 %r133, %r136
  %r138 = add i32 %r137, 0
  %r139 = add i32 %r130, 0
  %r140 = add i32 %r139, 1
  %r141 = add i32 %r140, 0
  br label %bb5

bb7:
  %r142 = load i32, i32* @b
  call void @putint(i32* %r142)
  %r143 = load i32, i32* @c
  call void @putint(i32* %r143)
  %r144 = add i32 %r129, 0
  call void @putint(i32* %r144)
  call void @_sysy_stoptime(i32 19)
  ret i32 0
}


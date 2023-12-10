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
  %r100 = add i32 0, 0
  %r100 = add i32 0, 0
  %r101 = add i32 0, 0
  %r101 = add i32 0, 0
  br label %bb2

bb2:
  %r100 = phi i32 [ %r100, %bb1 ], [ %r100, %bb3 ]
  %r102 = add i32 %r100, 0
  %r103 = icmp slt i32 %r102, 10
  br i1 %r103, label %bb3, label %bb4

bb3:
  %r104 = add i32 %r100, 0
  %r105 = getelementptr [10 x i32 ], [10 x i32 ]* @a, i32 0, i32 %r104
  %r106 = add i32 %r100, 0
  store i32 %r106, i32* %r105
  %r107 = add i32 %r100, 0
  %r108 = add i32 %r107, 1
  %r100 = add i32 %r108, 0
  br label %bb2

bb4:
  %r100 = add i32 0, 0
  br label %bb5

bb5:
  %r101 = phi i32 [ %r101, %bb4 ], [ %r101, %bb6 ]
  %r100 = phi i32 [ %r100, %bb4 ], [ %r100, %bb6 ]
  %r109 = add i32 %r100, 0
  %r110 = icmp slt i32 %r109, 10
  br i1 %r110, label %bb6, label %bb7

bb6:
  %r111 = add i32 %r101, 0
  %r112 = add i32 %r100, 0
  %r113 = getelementptr [10 x i32 ], [10 x i32 ]* @a, i32 0, i32 %r112
  %r114 = load i32, i32* %r113
  %r115 = add i32 %r111, %r114
  %r101 = add i32 %r115, 0
  %r116 = add i32 %r100, 0
  %r117 = add i32 %r116, 1
  %r100 = add i32 %r117, 0
  br label %bb5

bb7:
  %r118 = load i32, i32* @b
  call void @putint(i32 %r118)
  %r119 = load i32, i32* @c
  call void @putint(i32 %r119)
  %r120 = add i32 %r101, 0
  call void @putint(i32 %r120)
  call void @_sysy_stoptime(i32 19)
  ret i32 0
}


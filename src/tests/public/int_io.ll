declare i32 @getch( )
declare i32 @getint( )
declare void @putch( i32 )
declare void @putint( i32 )
declare void @putarray( i32, i32* )
declare void @_sysy_starttime( i32 )
declare void @_sysy_stoptime( i32 )
@ascii_0 = global i32 48
define i32 @my_getint( ) {
bb1:
  %r288 = add i32 0, 0
  %r288 = add i32 0, 0
  %r267 = add i32 0, 0
  br label %bb2

bb2:
  %r196 = icmp sgt i32 1, 0
  br i1 %r196, label %bb3, label %bb4

bb3:
  %r222 = call i32 @getch()
  %r223 = load i32, i32* @ascii_0
  %r224 = sub i32 %r222, %r223
  %r267 = add i32 %r224, 0
  %r226 = add i32 %r267, 0
  %r227 = icmp slt i32 %r226, 0
  br i1 %r227, label %bb5, label %bb8

bb8:
  %r230 = add i32 %r267, 0
  %r231 = icmp sgt i32 %r230, 9
  br i1 %r231, label %bb5, label %bb6

bb5:
  br label %bb2

  br label %bb7

bb6:
  br label %bb4

  br label %bb7

bb7:
  br label %bb2

bb4:
  %r232 = add i32 %r267, 0
  %r288 = add i32 %r232, 0
  br label %bb9

bb9:
  %r249 = icmp sgt i32 1, 0
  br i1 %r249, label %bb10, label %bb11

bb10:
  %r264 = call i32 @getch()
  %r265 = load i32, i32* @ascii_0
  %r266 = sub i32 %r264, %r265
  %r267 = add i32 %r266, 0
  %r268 = add i32 %r267, 0
  %r269 = icmp sge i32 %r268, 0
  br i1 %r269, label %bb15, label %bb13

bb15:
  %r277 = add i32 %r267, 0
  %r278 = icmp sle i32 %r277, 9
  br i1 %r278, label %bb12, label %bb13

bb12:
  %r284 = add i32 %r288, 0
  %r285 = add i32 %r267, 0
  %r286 = add i32 10, %r285
  %r287 = mul i32 %r284, %r286
  %r288 = add i32 %r287, 0
  br label %bb14

bb13:
  br label %bb11

  br label %bb14

bb14:
  %r288 = phi i32 [ %r288, %bb12 ], [ %r288, %bb13 ]
  br label %bb9

bb11:
  %r289 = add i32 %r288, 0
  ret i32 %r289
}

define i32 @mod( i32 %r124, i32 %r126 ) {
bb16:
  %r291 = add i32 0, 0
  %r291 = add i32 %r124, 0
  %r293 = add i32 0, 0
  %r293 = add i32 %r126, 0
  %r294 = add i32 %r291, 0
  %r295 = add i32 %r291, 0
  %r296 = add i32 %r293, 0
  %r297 = sdiv i32 %r295, %r296
  %r298 = add i32 %r293, 0
  %r299 = mul i32 %r297, %r298
  %r300 = sub i32 %r294, %r299
  ret i32 %r300
}

define void @my_putint( i32 %r135 ) {
bb17:
  %r357 = add i32 0, 0
  %r357 = add i32 %r135, 0
  %r137 = alloca [ 16 x i32 ]
  %r379 = add i32 0, 0
  %r379 = add i32 0, 0
  br label %bb18

bb18:
  %r379 = phi i32 [ %r379, %bb17 ], [ %r379, %bb19 ]
  %r357 = phi i32 [ %r357, %bb17 ], [ %r357, %bb19 ]
  %r327 = add i32 %r357, 0
  %r328 = icmp sgt i32 %r327, 0
  br i1 %r328, label %bb19, label %bb20

bb19:
  %r349 = add i32 %r379, 0
  %r350 = getelementptr [16 x i32 ], [16 x i32 ]* %r137, i32 0, i32 %r349
  %r351 = add i32 %r357, 0
  %r352 = call i32 @mod(i32* %r351, i32 10)
  %r353 = load i32, i32* @ascii_0
  %r354 = add i32 %r352, %r353
  store i32 %r354, i32* %r350
  %r355 = add i32 %r357, 0
  %r356 = sdiv i32 %r355, 10
  %r357 = add i32 %r356, 0
  %r358 = add i32 %r379, 0
  %r359 = add i32 %r358, 1
  %r379 = add i32 %r359, 0
  br label %bb18

bb20:
  br label %bb21

bb21:
  %r379 = phi i32 [ %r379, %bb20 ], [ %r379, %bb22 ]
  %r369 = add i32 %r379, 0
  %r370 = icmp sgt i32 %r369, 0
  br i1 %r370, label %bb22, label %bb23

bb22:
  %r377 = add i32 %r379, 0
  %r378 = sub i32 %r377, 1
  %r379 = add i32 %r378, 0
  %r380 = add i32 %r379, 0
  %r381 = getelementptr [16 x i32 ], [16 x i32 ]* %r137, i32 0, i32 %r380
  %r382 = load i32, i32* %r381
  call void @putch(i32* %r382)
  br label %bb21

bb23:
  ret void
}

define i32 @main( ) {
bb24:
  %r404 = add i32 0, 0
  call void @_sysy_starttime(i32 51)
  %r408 = add i32 0, 0
  %r385 = call i32 @my_getint()
  %r408 = add i32 %r385, 0
  br label %bb25

bb25:
  %r408 = phi i32 [ %r408, %bb24 ], [ %r408, %bb26 ]
  %r395 = add i32 %r408, 0
  %r396 = icmp sgt i32 %r395, 0
  br i1 %r396, label %bb26, label %bb27

bb26:
  %r403 = call i32 @my_getint()
  %r404 = add i32 %r403, 0
  %r405 = add i32 %r404, 0
  call void @my_putint(i32* %r405)
  call void @putch(i32 10)
  %r406 = add i32 %r408, 0
  %r407 = sub i32 %r406, 1
  %r408 = add i32 %r407, 0
  br label %bb25

bb27:
  call void @_sysy_stoptime(i32 58)
  ret i32 0
}


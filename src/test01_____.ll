declare i32 @getch( )
declare i32 @getint( )
declare void @putch( i32 )
declare void @putint( i32 )
declare void @putarray( i32, i32* )
declare void @_sysy_starttime( i32 )
declare void @_sysy_stoptime( i32 )
@TAPE_LEN = global i32 65536
@BUFFER_LEN = global i32 32768
@tape = global [ 65536 x i32 ] zeroinitializer
@program = global [ 32768 x i32 ] zeroinitializer
@ptr = global i32 0
define void @read_program( ) {
bb1:
  %r181 = add i32 0, 0
  %r182 = add i32 0, 0
  %r183 = add i32 0, 0
  %r184 = call i32 @getint()
  %r185 = add i32 %r184, 0
  br label %bb2

bb2:
  %r186 = phi i32 [ %r182, %bb1 ], [ %r193, %bb3 ]
  %r187 = add i32 %r186, 0
  %r188 = add i32 %r185, 0
  %r105 = icmp slt i32 %r187, %r188
  br i1 %r105, label %bb3, label %bb4

bb3:
  %r189 = add i32 %r186, 0
  %r107 = getelementptr [32768 x i32 ], [32768 x i32 ]* @program, i32 0, i32 %r189
  %r190 = call i32 @getch()
  store i32 %r190, i32* %r107
  %r191 = add i32 %r186, 0
  %r192 = add i32 %r191, 1
  %r193 = add i32 %r192, 0
  br label %bb2

bb4:
  %r194 = add i32 %r186, 0
  %r112 = getelementptr [32768 x i32 ], [32768 x i32 ]* @program, i32 0, i32 %r194
  store i32 0, i32* %r112
  ret void
}

define void @interpret( i32* %r113 ) {
bb5:
  %r195 = add i32 0, 0
  %r196 = add i32 0, 0
  %r197 = add i32 0, 0
  %r198 = add i32 0, 0
  br label %bb6

bb6:
  %r199 = add i32 %r198, 0
  %r118 = getelementptr i32, i32* %r113, i32 %r199
  %r200 = load i32, i32* %r118
  %r120 = icmp ne i32 %r200, 0
  br i1 %r120, label %bb7, label %bb8

bb7:
  %r201 = add i32 %r198, 0
  %r122 = getelementptr i32, i32* %r113, i32 %r201
  %r202 = load i32, i32* %r122
  %r203 = add i32 %r202, 0
  %r204 = add i32 %r203, 0
  %r125 = icmp eq i32 %r204, 62
  br i1 %r125, label %bb9, label %bb10

bb9:
  %r246 = load i32, i32* @ptr
  %r247 = add i32 %r246, 1
  store i32 %r247, i32* @ptr
  br label %bb11

bb10:
  br label %bb11

bb11:
  %r205 = add i32 %r203, 0
  %r129 = icmp eq i32 %r205, 60
  br i1 %r129, label %bb12, label %bb13

bb12:
  %r244 = load i32, i32* @ptr
  %r245 = sub i32 %r244, 1
  store i32 %r245, i32* @ptr
  br label %bb14

bb13:
  br label %bb14

bb14:
  %r206 = add i32 %r203, 0
  %r133 = icmp eq i32 %r206, 43
  br i1 %r133, label %bb15, label %bb16

bb15:
  %r207 = load i32, i32* @ptr
  %r135 = getelementptr [65536 x i32 ], [65536 x i32 ]* @tape, i32 0, i32 %r207
  %r208 = load i32, i32* @ptr
  %r137 = getelementptr [65536 x i32 ], [65536 x i32 ]* @tape, i32 0, i32 %r208
  %r209 = load i32, i32* %r137
  %r210 = add i32 %r209, 1
  store i32 %r210, i32* %r135
  br label %bb17

bb16:
  br label %bb17

bb17:
  %r211 = add i32 %r203, 0
  %r141 = icmp eq i32 %r211, 45
  br i1 %r141, label %bb18, label %bb19

bb18:
  %r240 = load i32, i32* @ptr
  %r143 = getelementptr [65536 x i32 ], [65536 x i32 ]* @tape, i32 0, i32 %r240
  %r241 = load i32, i32* @ptr
  %r145 = getelementptr [65536 x i32 ], [65536 x i32 ]* @tape, i32 0, i32 %r241
  %r242 = load i32, i32* %r145
  %r243 = sub i32 %r242, 1
  store i32 %r243, i32* %r143
  br label %bb20

bb19:
  br label %bb20

bb20:
  %r212 = add i32 %r203, 0
  %r149 = icmp eq i32 %r212, 46
  br i1 %r149, label %bb21, label %bb22

bb21:
  %r238 = load i32, i32* @ptr
  %r151 = getelementptr [65536 x i32 ], [65536 x i32 ]* @tape, i32 0, i32 %r238
  %r239 = load i32, i32* %r151
  call void @putch(i32 %r239)
  br label %bb23

bb22:
  br label %bb23

bb23:
  %r213 = add i32 %r203, 0
  %r154 = icmp eq i32 %r213, 44
  br i1 %r154, label %bb24, label %bb25

bb24:
  %r236 = load i32, i32* @ptr
  %r156 = getelementptr [65536 x i32 ], [65536 x i32 ]* @tape, i32 0, i32 %r236
  %r237 = call i32 @getch()
  store i32 %r237, i32* %r156
  br label %bb26

bb25:
  br label %bb26

bb26:
  %r214 = add i32 %r203, 0
  %r159 = icmp eq i32 %r214, 93
  br i1 %r159, label %bb30, label %bb28

bb30:
  %r218 = load i32, i32* @ptr
  %r161 = getelementptr [65536 x i32 ], [65536 x i32 ]* @tape, i32 0, i32 %r218
  %r219 = load i32, i32* %r161
  %r163 = icmp ne i32 %r219, 0
  br i1 %r163, label %bb27, label %bb28

bb27:
  %r220 = add i32 1, 0
  br label %bb31

bb31:
  %r221 = add i32 %r220, 0
  %r165 = icmp sgt i32 %r221, 0
  br i1 %r165, label %bb32, label %bb33

bb32:
  %r222 = add i32 %r198, 0
  %r223 = sub i32 %r222, 1
  %r224 = add i32 %r223, 0
  %r225 = add i32 %r224, 0
  %r169 = getelementptr i32, i32* %r113, i32 %r225
  %r226 = load i32, i32* %r169
  %r227 = add i32 %r226, 0
  %r228 = add i32 %r227, 0
  %r172 = icmp eq i32 %r228, 91
  br i1 %r172, label %bb34, label %bb35

bb34:
  %r233 = add i32 %r220, 0
  %r234 = sub i32 %r233, 1
  %r235 = add i32 %r234, 0
  br label %bb36

bb35:
  br label %bb36

bb36:
  %r229 = add i32 %r227, 0
  %r176 = icmp eq i32 %r229, 93
  br i1 %r176, label %bb37, label %bb38

bb37:
  %r230 = add i32 %r220, 0
  %r231 = add i32 %r230, 1
  %r232 = add i32 %r231, 0
  br label %bb39

bb38:
  br label %bb39

bb39:
  br label %bb31

bb33:
  br label %bb29

bb28:
  br label %bb29

bb29:
  %r215 = add i32 %r198, 0
  %r216 = add i32 %r215, 1
  %r217 = add i32 %r216, 0
  br label %bb6

bb8:
  ret void
}

define i32 @main( ) {
bb40:
  call void @_sysy_starttime(i32 76)
  call void @read_program()
  call void @interpret(i32* @program)
  call void @putch(i32 10)
  call void @_sysy_stoptime(i32 80)
  ret i32 0
}


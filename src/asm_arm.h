#ifndef __ASM_ARM
#define __ASM_ARM

#include "temp.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <list>

namespace ASM {

/*
* `reg >= 0` 代表通用寄存器，`reg == 1 -> x1` 。在指令翻译部分，翻译出的寄存器都是**虚拟寄存器**，即 `reg >= 100` ，该序号和 `LLVM IR` 中的无限寄存器序号保持一致。
  * **部分临时要用的寄存器需翻译成物理寄存器（hardcode），这些寄存器的出现场景和对应序号已给大家写死，以减小难度，具体见下文。**
  * 对于访问通用寄存器， `offset` 设置为 `0` 即可
* `reg == -3` 代表立即数，此时 `offset` 代表立即数大小，`reg = -3, offset = 1 => #1`
* `reg == -1, offset != -1` 代表使用 `sp` 在栈上间接寻址， `offset` 保存的栈上地址距离 `sp` 的偏移量， `reg = -1, offset = 1 => [sp, #1]`
* `reg == -1, offset == -1` 代表直接对 `sp` 直接运算 `reg = -1, offset = -1 => sp` (不是间接寻址)
*/
struct AS_reg {
    int reg;
    int offset;

    AS_reg(int _reg, int _offset);
};

struct AS_label {
    std::string name;

    AS_label(const std::string _name);
};

struct AS_decl {
    const std::string name;

    AS_decl(const std::string _name);
};

struct AS_global {
    AS_label *label;
    int init;
    int len;

    AS_global(AS_label *_label, int _init, int _len);
};

enum class AS_binopkind {
    ADD_,
    SUB_,
    MUL_,
    SDIV_,
};

enum class AS_relopkind {
    EQ_,
    NE_,
    LT_,
    GT_,
    LE_,
    GE_,
};

enum class AS_stmkind {
    BINOP,
    MOV,
    LDR,
    STR,
    LABEL,
    B,
    BCOND,
    BL,
    CMP,
    RET,
    ADR,
};

struct AS_binop {
    AS_binopkind op;
    AS_reg *left, *right, *dst;

    AS_binop(AS_binopkind _op, AS_reg *_left, AS_reg *_right, AS_reg *_dst);
};

struct AS_ldr {
    AS_reg *dst, *ptr;

    AS_ldr(AS_reg *_dst, AS_reg *_ptr);
};

struct AS_str {
    AS_reg *src, *ptr;

    AS_str(AS_reg *_src, AS_reg *_ptr);
};

struct AS_adr {
    AS_label* label;
    AS_reg *reg;

    AS_adr(AS_label *_label, AS_reg *_reg);
};

struct AS_b {
    AS_label *jump;

    AS_b(AS_label *_jump);
};

struct AS_bcond {
    AS_relopkind op;
    AS_label *jump;

    AS_bcond(AS_relopkind _op, AS_label *_jump);
};

struct AS_bl {
    AS_label *jump;

    AS_bl(AS_label *_jump);
};

struct AS_cmp {
    AS_reg *left, *right;

    AS_cmp(AS_reg *_left, AS_reg *_right);
};

struct AS_mov {
    AS_reg *src, *dst;

    AS_mov(AS_reg * _src, AS_reg *_dst);
};

struct AS_ret {

    AS_ret();
};

struct AS_stm {
    AS_stmkind type;
    union {
        AS_binop *BINOP;
        AS_mov *MOV;        // Move
        AS_ldr *LDR;        // Load
        AS_str *STR;        // Store
        AS_adr *ADR;        // Load Label
        AS_label *LABEL;    // Label
        AS_b *B;            // Jump
        AS_bcond *BCOND;    // CJump
        AS_bl *BL;          // Call
        AS_cmp *CMP;        // Comp
        AS_ret *RET;        // Return
    } u;
};

AS_stm* AS_Binop(AS_binopkind op, AS_reg* left, AS_reg *right, AS_reg *dst);
AS_stm* AS_Mov(AS_reg *src, AS_reg *dst);
AS_stm* AS_Ldr(AS_reg *dst, AS_reg *ptr);
AS_stm* AS_Adr(AS_label *label, AS_reg *reg);
AS_stm* AS_Str(AS_reg *src, AS_reg *ptr);
AS_stm* AS_Label(AS_label *label);
AS_stm* AS_B(AS_label *jump);
AS_stm* AS_BCond(AS_relopkind _op, AS_label *_jump);
AS_stm* AS_Bl(AS_label *jump);
AS_stm* AS_Cmp(AS_reg *_left, AS_reg *_right);
AS_stm* AS_Ret();

struct AS_func {
    std::list<AS_stm*> stms;

    AS_func(const std::list<AS_stm*> &stms);
};

struct AS_prog {
    std::vector<AS_global*> globals;
    std::vector<AS_decl*> decls;
    std::vector<AS_func*> funcs;

    AS_prog(const std::vector<AS_global*> &_globals, const std::vector<AS_decl*> &_decls, const std::vector<AS_func*> &_funcs);
};

}

#endif
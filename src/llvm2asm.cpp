#include "llvm_ir.h"
#include "asm_arm.h"
#include "temp.h"
#include "llvm2asm.h"

#include <queue>
#include <cassert>

using namespace std;
using namespace LLVMIR;
using namespace ASM;
// 难度降低 1：实验内容不需要翻译函数调用，不需要思考复杂的调用约定。

/*
* 全局变量 `stack_frame` 记录一个函数所需要申请栈的总大小，这个栈存储所有的变量，使用寄存器 `sp` 访问该栈。

* 需要对每个函数独立计算， `ARMv8` 中为 `SP` 申请的空间一定是 `16 byte` 的倍数。
* 需要一次性遍历一个函数体的所有 `alloca` 指令后，计算所需的 `SP` 大小。
*/
static int stack_frame;

/*
* 全局变量 `alloc_frame` 是一个 `flag` ，标记是否给函数分配了 `stack frame` ，在遇到的第一条语句开辟栈并置为 `true` 。
*/
static bool alloc_frame = false;

/*
* 全局变量 `spOffsetMap` 记录了所有栈上变量的映射，例如 `x100 -> 48` , 本质上对应的是 `x100 -> [sp + #48]` 的内存位置。

* 这个结构需要记录所有 `alloca` 分配的寄存器位置，同时也需要记录可以通过计算获得的偏移后的地址。例如 `getelementptr` 计算偏移后的地址。
* 难度降低 2: 所有的索引访问都为常数类型，即不存在 `a[n]` 的情况
*/
static unordered_map<int, int> spOffsetMap;

/*
* 全局变量 `condMap` 记录了 `icmp` 的 `目的操作数` 和他下一个语句中 `跳转条件` 的映射。

* 翻译到 `ASM` 的过程中，不需要存 `icmp` 的返回值 （参考 `cmp` 指令），仅需要利用 `b.{状态}` 就可以实现有条件跳转
*/
static unordered_map<int, AS_relopkind> condMap;

/*
* 全局变量 `structLayout`，是一个结构题到他的静态大小（字节数）的映射，即占用多大空间。

* 难度降低 3: 所有结构的体的定义，每个域只有整形值，不考虑结构题中有数组或嵌套其他结构体。但我们允许声明一个变量为结构体数组（但不能在域内）。
*/
static unordered_map<string, int> structLayout;

/*
* 计算每个结构体的静态大小（字节），存储到 `structLayout` 内。
*/
void structLayoutInit(vector<L_def*> &defs) {
    for (const auto &def : defs) {
        switch (def->kind) {
            case L_DefKind::SRT: {
                // Struct type. 
                // Fixme: add here
                string name = def->u.SRT->name;
                int num = def->u.SRT->members.size();
                structLayout[name] = num*4;
            }
            case L_DefKind::GLOBAL: {
                break;
            }
            case L_DefKind::FUNC: {
                break;
            }
        }
    }
}

/*
* 要计算出所有 `alloca` 指令分配栈的所占总空间大小（字节为单位），存储在 `stack_frame`。
* 计算每个 `alloca` 指令申请的栈上 `LLVM IR` 变量相对于 `sp` 指针的偏移量，存储到 `spOffsetMap` 内。
* 所有 `alloca` 指令分配的栈空间需要在第一个 `bb` 内一次性分配，注意栈增长的方向。
* 本步骤是否考虑 `GEP` 指令的返回的实际偏移，可以由实现者自行选择。
 */
void set_stack(L_func &func) {
    // Fixme: add here
    int len = 0;
    L_block* firstBlock = func.blocks.front();
    for(auto it = firstBlock->instrs.rbegin(); it != firstBlock->instrs.rend(); it++){
        auto stm = *it;
        if(stm->type == L_StmKind::T_ALLOCA){
            Temp_temp* tt = stm->u.ALLOCA->dst->u.TEMP;
            spOffsetMap[tt->num] = len;
            switch (tt->type)
            {
            case TempType::INT_PTR:
                if(tt->len == 0){
                    len += 4;
                }else{
                    len += tt->len * 4; 
                }
                break;
            case TempType::INT_TEMP:
                len += 4;
                break;
            case TempType::STRUCT_PTR:
                if(tt->len == 0){
                    len += structLayout[tt->structname];
                }else{
                    len += tt->len * structLayout[tt->structname];
                }
                break;
            case TempType::STRUCT_TEMP:
                len += structLayout[tt->structname];
                break;
            }
        }
    }
    stack_frame = ((len + 15)/16) * 16;
}

/*
* 在函数第⼀条⾮标签语句前、函数返回语句前，开辟、取回栈空间，使⽤ add sub 改变 sp 的⼤⼩，
* 总空间需要为stack_frame 。
*/
void new_frame(list<AS_stm*> &as_list) {
    // Fixme: add here
    AS_reg* sp = new AS_reg(-1, -1);
    as_list.push_back(AS_Binop(AS_binopkind::SUB_, sp, new AS_reg(-3, stack_frame), sp));

}

void free_frame(list<AS_stm*> &as_list) {
    // Fixme: add here
    AS_reg* sp = new AS_reg(-1, -1);
    as_list.push_back(AS_Binop(AS_binopkind::ADD_, sp, new AS_reg(-3, stack_frame), sp));
}

/*
* 在 `LLVM IR` 中，左右操作数都可能为立即数。
* 对于汇编指令，加法和减法，左操作数不能为立即数；乘法和除法，左右操作数都不能是立即数。
* 难度降低 4: `LAB6` 预留了 `x2` `x3` 两个物理寄存器来暂存立即数。
*/
void llvm2asmBinop(list<AS_stm*> &as_list, L_stm* binop_stm) {
    AS_reg* left;
    AS_reg* right;
    AS_reg* dst;
    AS_binopkind op;

    auto setOpLeftRight = [&](AS_binopkind thisop, L_binop* binop){
        op = thisop;
        switch (binop->left->kind) {
            case OperandKind::ICONST: {
                // store from the const: str #1, ...
                // move the instant into x2: mov x2, #1
                int instant = binop->left->u.ICONST;
                AS_reg* src_mov = new AS_reg(-3, instant);
                AS_reg* dst_mov = new AS_reg(2, 0);
                as_list.push_back(AS_Mov(src_mov, dst_mov));
                left = dst_mov;
                break;
            }
            case OperandKind::TEMP: {
                // store from the reg directly: str x, ...
                int src_num = binop->left->u.TEMP->num;
                left = new AS_reg(src_num, 0);
                break;
            }
            case OperandKind::NAME: {
                assert(0);
            }
        }

        switch (binop->right->kind) {
            case OperandKind::ICONST: {
                // store from the const: str #1, ...
                // do not need to move the instant into reg, use #1 directly
                int instant = binop->right->u.ICONST;
                if(thisop == AS_binopkind::ADD_ || thisop == AS_binopkind::SUB_) {
                    right = new AS_reg(-3, instant);
                }else{
                    AS_reg* src_mov = new AS_reg(-3, instant);
                    AS_reg* dst_mov = new AS_reg(3, 0);
                    as_list.push_back(AS_Mov(src_mov, dst_mov));
                    right = dst_mov;
                }
                break;
            }
            case OperandKind::TEMP: {
                // store from the reg: str x, ...
                int src_num = binop->right->u.TEMP->num;
                right = new AS_reg(src_num, 0);
                break;
            }
            case OperandKind::NAME: {
                assert(0);
            }
        }
    };

    switch (binop_stm->u.BINOP->op) {
        case L_binopKind::T_plus: {
            setOpLeftRight(AS_binopkind::ADD_, binop_stm->u.BINOP);
            break;
        }
        
        case L_binopKind::T_minus: {
            // Fixme: add here
            setOpLeftRight(AS_binopkind::SUB_, binop_stm->u.BINOP);
            break;
        }
        case L_binopKind::T_mul: {
            // Fixme: add here
            setOpLeftRight(AS_binopkind::MUL_, binop_stm->u.BINOP);
            break;
        }
        case L_binopKind::T_div: {
            // Fixme: add here
            setOpLeftRight(AS_binopkind::SDIV_, binop_stm->u.BINOP);
            break;
        }
    }

    // Fixme: add here
    int dst_num = binop_stm->u.BINOP->dst->u.TEMP->num;
    dst = new AS_reg(dst_num, 0);
    as_list.push_back(AS_Binop(op,left,right,dst));
}

/*
* `load` 的源操作数存在三种可能：存储在栈上的直接地址 `[sp, #N]`， 存储在寄存器中 `%rn` ，以及全局变量 `@a` 。
* 难度降低 5: 全局变量使用 `ADR` 获取地址，存储在物理寄存器 `x3` 内。
*/
void llvm2asmLoad(list<AS_stm*> &as_list, L_stm* load_stm) {
    // Fixme: add here
    AS_reg *dst = new AS_reg(load_stm->u.LOAD->dst->u.TEMP->num, 0);
    switch(load_stm->u.LOAD->ptr->kind){
        case OperandKind::NAME: {
            AS_reg* ar = new AS_reg(3, 0);
            AS_label label(load_stm->u.LOAD->ptr->u.NAME->name->name);
            as_list.push_back(AS_Adr(new AS_label(label), ar));
            as_list.push_back(AS_Ldr(dst, ar));
            break;
        }
        case OperandKind::TEMP: {
            int num = load_stm->u.LOAD->ptr->u.TEMP->num;
            auto it = spOffsetMap.find(num);
            if(it != spOffsetMap.end()){
                int offset = it->second;
                AS_reg* p = new AS_reg(-1, offset);
                as_list.push_back(AS_Ldr(dst, p));
            }else{
                AS_reg* p = new AS_reg(num, 0);
                as_list.push_back(AS_Ldr(dst, p));
            }
            break;
        }
    }
}

/*
* `store` 的 源操作数存在两种可能：立即数 `#N`， 存储在寄存器中 `%rn` 。
* 目的操作数请课程实验同学自行思考。
*/
void llvm2asmStore(list<AS_stm*> &as_list, L_stm* store_stm) {
    // Fixme: add here
    AS_reg* ptr;
    switch (store_stm->u.STORE->ptr->kind)
    {
        case OperandKind::NAME:{
            AS_reg* ar = new AS_reg(2, 0);
            AS_label label(store_stm->u.STORE->ptr->u.NAME->name->name);
            as_list.push_back(AS_Adr(new AS_label(label), ar));
            ptr = ar;
            break;
        }
        case OperandKind::TEMP:{
            int num = store_stm->u.STORE->ptr->u.TEMP->num;
            auto it = spOffsetMap.find(num);
            if(it != spOffsetMap.end()){
                int offset = it->second;
                ptr = new AS_reg(-1, offset);
            }else{
                ptr = new AS_reg(num, 0);
            }
            break;
        }
        default: assert(0);
    }

    switch (store_stm->u.STORE->src->kind){
        case OperandKind::TEMP:{
            int num = store_stm->u.STORE->src->u.TEMP->num;
            AS_reg* s = new AS_reg(num, 0);
            as_list.push_back(AS_Str(s, ptr));
            break;
        }
        case OperandKind::ICONST:{
            AS_reg* r = new AS_reg(-3, store_stm->u.STORE->src->u.ICONST);
            AS_reg* i = new AS_reg(2, 0);
            as_list.push_back(AS_Mov(r, i));
            as_list.push_back(AS_Str(i, ptr));
            break;
        }
        default: assert(0);
    }
}

/*
* 在 `LLVM IR` 中， `icmp` 的两个操作数都可能为立即数。
* 对于汇编指令，左操作数必须在寄存器内。
* 这个操作需要记录 `icmp` 返回的寄存器对应的跳转条件。
*/
void llvm2asmCmp(list<AS_stm*> &as_list, L_stm* cmp_stm) {
    // Fixme: add here
    AS_operand* left = cmp_stm->u.CMP->left;
    AS_operand* right = cmp_stm->u.CMP->right;
    AS_reg* left_reg;
    if(left->kind == OperandKind::ICONST){
        left_reg = new AS_reg(2,0);
        AS_reg* tmp = new AS_reg(-3, left->u.ICONST);
        as_list.push_back(AS_Mov(tmp, left_reg));
    }else if(left->kind == OperandKind::NAME){
        left_reg = new AS_reg(2,0);
        as_list.push_back(AS_Adr(new AS_label(left->u.NAME->name->name), left_reg));
    }else if(left->kind == OperandKind::TEMP){
        left_reg = new AS_reg(left->u.TEMP->num, 0);
    }

    if(right->kind == OperandKind::ICONST){
        as_list.push_back(AS_Cmp(left_reg, new AS_reg(-3, right->u.ICONST)));
    }else if(right->kind == OperandKind::NAME){
        AS_reg* right_reg = new AS_reg(3,0);
        as_list.push_back(AS_Adr(new AS_label(right->u.NAME->name->name), right_reg));
        as_list.push_back(AS_Cmp(left_reg, right_reg));
    }else if(right->kind == OperandKind::TEMP){
        as_list.push_back(AS_Cmp(left_reg, new AS_reg(right->u.TEMP->num, 0)));
    }
}


void llvm2asmCJmp(list<AS_stm*> &as_list, L_stm* cjmp_stm) {
    // Fixme: add here
    string t = cjmp_stm->u.CJUMP->true_label->name;
    string f = cjmp_stm->u.CJUMP->false_label->name;

    as_list.push_back(AS_BCond(AS_relopkind::LT_, new AS_label(t)));
    as_list.push_back(AS_B(new AS_label(f)));
}

/*
* `Ret` 调用前需要吧返回值存储到物理寄存器 `x0` 。
* 返回值可以是常数，也可以存储在寄存器内。
*/
void llvm2asmRet(list<AS_stm*> &as_list, L_stm* ret_stm) {
    // Fixme: add here
    AS_operand* ret = ret_stm->u.RET->ret;
    AS_reg* ret_reg = new AS_reg(0,0);
    if(ret != nullptr){
        if(ret->kind == OperandKind::ICONST){
            as_list.push_back(AS_Mov(new AS_reg(-3, ret->u.ICONST), ret_reg));
        }else if(ret->kind == OperandKind::NAME){
            as_list.push_back(AS_Adr(new AS_label(ret->u.NAME->name->name), ret_reg));
        }else if(ret->kind == OperandKind::TEMP){
            int num = ret->u.TEMP->num;
            auto t = spOffsetMap.find(num);
            if(t != spOffsetMap.end()){
                int offset = t->second;
                as_list.push_back(AS_Ldr(ret_reg, new AS_reg(-1, offset)));
            }else {
                as_list.push_back(AS_Mov(new AS_reg(num, 0), ret_reg));
            }
        }
    }
    as_list.push_back(AS_Binop(AS_binopkind::ADD_, new AS_reg(-1,-1), new AS_reg(-3, stack_frame), new AS_reg(-1,-1)));
    as_list.push_back(AS_Ret());
    
}

/*
* 需要考虑 `base_ptr` 是结构体数组、整形数组还是普通结构体。
* 对于数组需要考虑索引值、单个成员（`int` 还是结构体）占的空间。
* 对于结构体考虑具体是哪个域。
* 需要考虑源操作数指针 `base_ptr` 存在哪，可能是全局变量、栈上变量或者是寄存器
*/
void llvm2asmGep(list<AS_stm*> &as_list, L_stm* gep_stm) {
    // Fixme: add here
    AS_reg* dst = new AS_reg(gep_stm->u.GEP->new_ptr->u.TEMP->num, 0);
    int this_offset = gep_stm->u.GEP->index->u.ICONST;
    AS_operand* base = gep_stm->u.GEP->base_ptr;
    if(base->kind == OperandKind::NAME){
        int index = 0;
        if(base->u.NAME->type == TempType::INT_PTR){
            index = this_offset * 4;
        }else if(base->u.NAME->type == TempType::STRUCT_TEMP){
            index = this_offset * 4;
        }else if(base->u.NAME->type == TempType::STRUCT_PTR){
            if(base->u.NAME->len == 0){
                index = this_offset * 4;
            } else {
                index = this_offset * structLayout[base->u.NAME->structname];
            }
        }
        AS_reg* tmp = new AS_reg(3, 0);
        as_list.push_back(AS_Adr(new AS_label(base->u.NAME->name->name), tmp));
        as_list.push_back(AS_Binop(AS_binopkind::ADD_, tmp, new AS_reg(-3, index), tmp));
        as_list.push_back(AS_Mov(tmp, dst));
    }else if(base->kind == OperandKind::TEMP){
        int num = base->u.TEMP->num;
        auto t = spOffsetMap.find(num);
        int offset = 0;
        if(base->u.TEMP->type == TempType::INT_PTR){
            offset = this_offset * 4;
        }else if(base->u.TEMP->type == TempType::STRUCT_TEMP){
            offset = this_offset * 4;
        }else if(base->u.TEMP->type == TempType::STRUCT_PTR){
            if(base->u.TEMP->len == 0){
                offset = this_offset * 4;
            } else {
                offset = this_offset * structLayout[base->u.TEMP->structname];
            }
        }
        if(t != spOffsetMap.end()){
            offset += t->second;
            spOffsetMap[dst->reg] = offset;
            // as_list.push_back(AS_Ldr(dst, new AS_reg(-1, offset)));
        }else{
            as_list.push_back(AS_Binop(AS_binopkind::ADD_, new AS_reg(num,0), new AS_reg(-3, offset), dst));
        }
    }
}

void llvm2asmStm(list<AS_stm*> &as_list, L_stm &stm) {

    if (!alloc_frame && stm.type != L_StmKind::T_LABEL) {
        new_frame(as_list);
        alloc_frame = true;
    }

    switch (stm.type) {
        case L_StmKind::T_BINOP: {
            llvm2asmBinop(as_list, &stm);
            break;
        }
        case L_StmKind::T_LOAD: {
            llvm2asmLoad(as_list, &stm);
            break;
        }
        case L_StmKind::T_STORE: {
            llvm2asmStore(as_list, &stm);
            break;
        }
        case L_StmKind::T_LABEL: {
            auto label = new AS_label(stm.u.LABEL->label->name);
            as_list.push_back(AS_Label(label));
            break;
        }
        case L_StmKind::T_JUMP: {
            auto label = new AS_label(stm.u.JUMP->jump->name);
            as_list.push_back(AS_B(label));
            break;
        }
        case L_StmKind::T_CMP: {
            llvm2asmCmp(as_list, &stm);
            break;
        }
        case L_StmKind::T_CJUMP: {
            llvm2asmCJmp(as_list, &stm);
            break;
        }
        case L_StmKind::T_MOVE: {
            // Do nothing
            break;
        }
        case L_StmKind::T_CALL: {
            // Do nothing
            break;
        }
        case L_StmKind::T_VOID_CALL: {
            // Do nothing
            break;
        }
        case L_StmKind::T_RETURN: {
            llvm2asmRet(as_list, &stm);
            alloc_frame = false;
            break;
        }
        case L_StmKind::T_ALLOCA: {
            // Do nothing
            break;
        }
        case L_StmKind::T_GEP: {
            llvm2asmGep(as_list, &stm);
            break;
        }
        case L_StmKind::T_PHI: {
            // Do nothing
            break;
        }
        case L_StmKind::T_NULL: {
            // Do nothing
            break;
        }
    }
}

/*
* 该实现是线性扫描分配法的简化版本，寄存器的优先级为FIFO，把虚拟寄存器（编号为 `x100` 以上）分配物理寄存器（ `x9-x15` `x20-x28` ），同时不考虑 `spill` 的情况。

* 参与实验的同学可直接翻译到虚拟寄存器的 `ARMv8 ASM` ，最后调用该函数即可。
*/
void allocReg(list<AS_stm*> &as_list){

    unordered_map<int,int> vregStart;
    unordered_map<int,int> vregEnd;
    auto setDef=[&](AS_reg *reg,int lineNo){
        int regNo=reg->reg;
        if (regNo<100) return;
        if (vregStart.find(regNo)==vregStart.end()){
            vregStart.insert({regNo,lineNo});
        }
    };
    auto setUse=[&](AS_reg *reg,int lineNo){
        int regNo=reg->reg;
        if (regNo<100) return;
        vregEnd.insert({regNo,lineNo});
    };
    int lineNo=0;
    for (const auto &stm: as_list){
        switch (stm->type){
            case AS_stmkind::BINOP:
                setDef(stm->u.BINOP->dst, lineNo);
                setUse(stm->u.BINOP->left, lineNo);
                setUse(stm->u.BINOP->right, lineNo);
                break;
            case AS_stmkind::MOV:
                setDef(stm->u.MOV->dst, lineNo);
                setUse(stm->u.MOV->src, lineNo);
                break;
            case AS_stmkind::LDR:
                setDef(stm->u.LDR->dst, lineNo);
                setUse(stm->u.LDR->ptr, lineNo);
                break;
            case AS_stmkind::STR:
                setUse(stm->u.STR->src, lineNo);
                setUse(stm->u.STR->ptr, lineNo);
                break;
            case AS_stmkind::CMP:
                setUse(stm->u.CMP->left, lineNo);
                setUse(stm->u.CMP->right, lineNo);
                break;
            case AS_stmkind::ADR:
                setDef(stm->u.ADR->reg, lineNo);
                break;
            default: break;
        }
        lineNo+=1;
    }

    // workaround for undef vreg
    for (const auto& iter: vregEnd){
        auto pos=vregStart.find(iter.first);
        if (pos==vregStart.end()){
            vregStart.insert(iter);
        }
    }

    /* cout<<"Live interval:\n";
    for (auto iter: vregStart){
        cout<<iter.first<<": ["<<iter.second<<", "<<vregEnd[iter.first]<<"]\n";
    } */


    // -1 invalid for allocation, 0 unallocated, >100 registerNo
    // x9-x15 x20-x28 is available
    vector<int> allocateRegs{9,10,11,12,13,14,15,20,21,22,23,24,25,26,27,28};
    vector<int> allocateTable;
    unordered_map<int,int> v2pMapping;
    allocateTable.resize(32);
    for (int i=0;i<32;++i){
        allocateTable[i]=-1;
    }
    
    for (auto ind: allocateRegs){
        allocateTable[ind]=0;
    }

    auto get_mapping=[&](int regNo,int lineNo){
        auto pos=v2pMapping.find(regNo);
        if (pos!=v2pMapping.end()) return pos->second;

        // find available reg
        for (int i=0;i<32;++i){
            int allocNo=allocateTable[i];
            if ((allocNo==0) || (allocNo>0 && vregEnd[allocNo]<lineNo)){
                v2pMapping[regNo]=i;
                allocateTable[i]=regNo;
                // cout<<regNo<<" -> "<<i<<"\n";
                return i;
            }
        }
        throw runtime_error("allocate register fail");

    };

    auto vreg_map=[&](AS_reg* reg, int lineNo){
        int regNo=reg->reg;
        if (regNo<100) return;
        reg->reg=get_mapping(regNo,lineNo);
    };
    
    lineNo=0;
    for (const auto &stm: as_list){
        switch (stm->type){
            case AS_stmkind::BINOP: 
                vreg_map(stm->u.BINOP->dst, lineNo);
                vreg_map(stm->u.BINOP->left, lineNo);
                vreg_map(stm->u.BINOP->right, lineNo);
                break;
            case AS_stmkind::MOV: 
                vreg_map(stm->u.MOV->dst, lineNo);
                vreg_map(stm->u.MOV->src, lineNo);
                break;
            case AS_stmkind::LDR: 
                vreg_map(stm->u.LDR->dst, lineNo);
                vreg_map(stm->u.LDR->ptr, lineNo);
                break;
            case AS_stmkind::STR: 
                vreg_map(stm->u.STR->src, lineNo);
                vreg_map(stm->u.STR->ptr, lineNo);
                break;
            case AS_stmkind::CMP: 
                vreg_map(stm->u.CMP->left, lineNo);
                vreg_map(stm->u.CMP->right, lineNo);
                break;
            case AS_stmkind::ADR:
                vreg_map(stm->u.ADR->reg, lineNo);
                break;
            default: 
                break;
        }
        lineNo+=1;
    }

    /* cout<<"regAlloc:\n";
    for (const auto& iter:v2pMapping){
        cout<<"x"<<iter.first<<" -> x"<<iter.second<<"\n";
    } */
}

AS_func* llvm2asmFunc(L_func &func) {
    list<AS_stm*> stms;

    auto p = new AS_func(stms);
    auto func_label = new AS_label(func.name);
    p->stms.push_back(AS_Label(func_label));

    for(const auto &block : func.blocks) {
        for (const auto &instr : block->instrs) {
            llvm2asmStm(p->stms, *instr);
        }
    }

    allocReg(p->stms);

    return p;
}

void llvm2asmDecl(vector<AS_decl*> &decls, L_def &def) {
    switch (def.kind) {
        case L_DefKind::GLOBAL: {
            return;
        }
        case L_DefKind::FUNC: {
            AS_decl* decl = new AS_decl(def.u.FUNC->name);
            decls.push_back(decl);
            break;
        }
        case L_DefKind::SRT: {
            return;
        }
    }
}

void llvm2asmGlobal(vector<AS_global*> &globals, L_def &def) {
    auto pushGlobal = [&](string name, int init, int len){
        AS_global* ag = new AS_global(new AS_label(name), init, len);
        globals.push_back(ag);
    };

    switch (def.kind) {
        case L_DefKind::GLOBAL: {
            // Fixme: add here
            L_globaldef* gdef = def.u.GLOBAL;
            string name = gdef->name;
            switch (gdef->def.kind)
            {
            case TempType::INT_TEMP:
                if(gdef->init.size() == 1) 
                    pushGlobal(name, gdef->init[0], 0);
                else pushGlobal(name, 0, 0);
                break;
            case TempType::INT_PTR:
                pushGlobal(name, 0, 4 * gdef->def.len);
                break;
            case TempType::STRUCT_TEMP:
                pushGlobal(name, 0, structLayout[gdef->def.structname]);
                break;

            case TempType::STRUCT_PTR:
                pushGlobal(name, 0, structLayout[gdef->def.structname] * gdef->def.len);
                break;
            }
        }
        case L_DefKind::FUNC: {
            return;
        }
        case L_DefKind::SRT: {
            return;
        }
    }
}

AS_prog* llvm2asm(L_prog &prog) {
    std::vector<AS_global*> globals;
    std::vector<AS_decl*> decls;
    std::vector<AS_func*> func_list;

    auto as_prog = new AS_prog(globals, decls, func_list);

    structLayoutInit(prog.defs);

    // translate function definition
    for(const auto &def : prog.defs) {
        llvm2asmDecl(as_prog->decls, *def);
    }

    for(const auto &func : prog.funcs) {
        AS_decl* decl = new AS_decl(func->name);
        as_prog->decls.push_back(decl);
    }

    // translate global data
    for(const auto &def : prog.defs) {
        llvm2asmGlobal(as_prog->globals, *def);
    }

    // translate each llvm function
    for(const auto &func : prog.funcs) {
        set_stack(*func);
        as_prog->funcs.push_back(llvm2asmFunc(*func));
    }

    return as_prog;
}

#include <cassert>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "bg_llvm.h"
#include "graph.hpp"
#include "liveness.h"
#include "printLLVM.h"
#include "ssa.h"

using namespace std;
using namespace LLVMIR;
using namespace GRAPH;
struct imm_Dominator {
    L_block *pred;
    unordered_set<L_block *> succs;
};

unordered_map<L_block *, unordered_set<L_block *>> dominators;

unordered_map<L_block *, imm_Dominator> tree_dominators;

unordered_map<L_block *, unordered_set<L_block *>> DF_array;

unordered_map<L_block *, Node<L_block *> *> revers_graph;

unordered_map<Temp_temp *, AS_operand *> temp2ASoper;

static void init_table() {
    dominators.clear();
    tree_dominators.clear();
    DF_array.clear();
    revers_graph.clear();
    temp2ASoper.clear();
}


#include <fstream>

LLVMIR::L_prog *SSA(LLVMIR::L_prog *prog) {
    for (auto &fun : prog->funcs) {
        init_table();
        combine_addr(fun);
        
        mem2reg(fun);

        auto RA_bg = Create_bg(fun->blocks);

        SingleSourceGraph(RA_bg.mynodes[0], RA_bg, fun);
        // Show_graph(stdout,RA_bg);

        Liveness(RA_bg.mynodes[0], RA_bg, fun->args);


        Dominators(RA_bg);
        // printf_domi();

        tree_Dominators(RA_bg);
        // printf_D_tree();

        // 默认0是入口block
        computeDF(RA_bg, RA_bg.mynodes[0]);
        // printf_DF();

        Place_phi_fu(RA_bg, fun);

        Rename(RA_bg);
        ofstream LLVMStream;
        LLVMStream.open("test01_____.ll");
        printL_prog(LLVMStream, prog);

        combine_addr(fun);
    }
    return prog;
}

static bool is_mem_variable(L_stm *stm) {
    return stm->type == L_StmKind::T_ALLOCA && stm->u.ALLOCA->dst->kind == OperandKind::TEMP &&
           stm->u.ALLOCA->dst->u.TEMP->type == TempType::INT_PTR &&
           stm->u.ALLOCA->dst->u.TEMP->len == 0;
}

// 保证相同的AS_operand, 地址一样 。常量除外
void combine_addr(LLVMIR::L_func *fun) {
    unordered_map<Temp_temp *, unordered_set<AS_operand **>> temp_set;
    unordered_map<Name_name *, unordered_set<AS_operand **>> name_set;
    for (auto &block : fun->blocks) {
        for (auto &stm : block->instrs) {
            auto AS_operand_list = get_all_AS_operand(stm);
            for (auto AS_op : AS_operand_list) {
                if ((*AS_op)->kind == OperandKind::TEMP) {
                    temp_set[(*AS_op)->u.TEMP].insert(AS_op);
                } else if ((*AS_op)->kind == OperandKind::NAME) {
                    name_set[(*AS_op)->u.NAME].insert(AS_op);
                }
            }
        }
    }
    for (auto temp : temp_set) {
        AS_operand *fi_AS_op = **temp.second.begin();
        for (auto AS_op : temp.second) {
            *AS_op = fi_AS_op;
        }
    }
    for (auto name : name_set) {
        AS_operand *fi_AS_op = **name.second.begin();
        for (auto AS_op : name.second) {
            *AS_op = fi_AS_op;
        }
    }
}


void mem2reg(LLVMIR::L_func *fun) {
    L_block *firstBlock = fun->blocks.front();
    unordered_set<Temp_temp*> allocas;
    for (auto stm : firstBlock->instrs) {
        if (is_mem_variable(stm)) {
            allocas.emplace(stm->u.ALLOCA->dst->u.TEMP);
            *stm = *L_Move(AS_Operand_Const(0), stm->u.ALLOCA->dst);
        }
    }

    for(auto block: fun->blocks){
        for(auto stm: block->instrs){
            if(stm->type == L_StmKind::T_LOAD && allocas.find(stm->u.LOAD->ptr->u.TEMP) != allocas.end()){
                auto dst = stm->u.LOAD->dst;
                auto ptr = stm->u.LOAD->ptr;
                *stm = *L_Move(ptr, dst);
            }else if(stm->type == L_StmKind::T_STORE && allocas.find(stm->u.STORE->ptr->u.TEMP) != allocas.end()){
                auto src = stm->u.STORE->src;
                auto ptr = stm->u.STORE->ptr;
                *stm = *L_Move(src, ptr);
            }
        }
    }
}

void Dominators(GRAPH::Graph<LLVMIR::L_block *> &bg) {
    unordered_set<L_block*> blks;
    for(auto t : bg.mynodes){
        auto node = t.second;
        blks.insert(node->info);
    }
    for(auto t : bg.mynodes){
        auto node = t.second;
        dominators[node->info] = blks;
    }

    Node<L_block*>* head = bg.mynodes[0];
    unordered_set<L_block *> dom;
    dom.insert(head->info);
    dominators[bg.mynodes[0]->info] = dom;

    bool change = true;
    while(change){
        change = false;
        for(auto t : bg.mynodes){
            auto node = t.second;
            unordered_set<L_block *> newset;
            unordered_set<L_block *> set = dominators[node->info];
            for(auto i : node->preds){
                auto pre_node = bg.mynodes[i];
                for(auto s: dominators[pre_node->info]){
                    if(set.find(s) != set.end()){
                        newset.insert(s);
                    }
                }
                set = newset;
                set.insert(node->info);
                if(set.size() != dominators[node->info].size()) change = true;
                newset.clear();
            }
            dominators[node->info] = set;
        }
    }
}

void printf_domi() {
    printf("Dominator:\n");
    for (auto x : dominators) {
        printf("%s :\n", x.first->label->name.c_str());
        for (auto t : x.second) {
            printf("%s ", t->label->name.c_str());
        }
        printf("\n\n");
    }
}

void printf_D_tree() {
    printf("dominator tree:\n");
    for (auto x : tree_dominators) {
        printf("%s :\n", x.first->label->name.c_str());
        for (auto t : x.second.succs) {
            printf("%s ", t->label->name.c_str());
        }
        printf("\n\n");
    }
}

void printf_DF() {
    printf("DF:\n");
    for (auto x : DF_array) {
        printf("%s :\n", x.first->label->name.c_str());
        for (auto t : x.second) {
            printf("%s ", t->label->name.c_str());
        }
        printf("\n\n");
    }
}

void tree_Dominators(GRAPH::Graph<LLVMIR::L_block *> &bg) {
    //   Todo
    for(auto it : dominators){
        L_block* thisBlock = it.first;
        auto dominator = it.second;
        imm_Dominator imm_dom;
        for(auto d: dominator){
            if(d == thisBlock) continue;
            bool is = true;
            for(auto d1: dominator){
                if(d1 == d || d1 == thisBlock) continue;
                if(dominators[d1].find(d) != dominators[d1].end()){
                    is = false;
                    break;
                }
            }
            if(is){
                tree_dominators[thisBlock].pred = d;
                tree_dominators[d].succs.insert(thisBlock);
            }
        }
    }
}

void computeDF(GRAPH::Graph<LLVMIR::L_block *> &bg, GRAPH::Node<LLVMIR::L_block *> *r) {
    //   Todo
    unordered_set<L_block *> set;
    for(auto i : r->succs){
        L_block* lb = bg.mynodes[i]->info;
        if(tree_dominators[lb].pred != r->info){
            set.insert(lb);
        }
    }
    for(auto i : r->succs){
        auto node = bg.mynodes[i];
        if(tree_dominators[r->info].succs.find(node->info) != tree_dominators[r->info].succs.end()){
            computeDF(bg, node);
            for(auto j : DF_array[node->info]){
                if(dominators[j].find(r->info) == dominators[j].end() || j == r->info){
                    set.insert(j);
                }
            }
        }
    }
    DF_array.emplace(r->info, set);
}

// 只对标量做
void Place_phi_fu(GRAPH::Graph<LLVMIR::L_block *> &bg, L_func *fun) {
    //   Todo
    for(auto n: bg.mynodes){
        revers_graph.emplace(n.second->info, n.second);
    }
    map<Temp_temp*, set<Node<L_block*>*>> defsites;
    map<L_block*, set<Temp_temp*>> phisets;

    for(auto it = bg.mynodes.begin(); it != bg.mynodes.end(); it++){
        auto i = it->second;
        TempSet ts = &FG_def(it->second);
        for(auto t: *ts){
            defsites[t].insert(i);
        }
    }

    for(auto it = defsites.begin(); it != defsites.end(); it++){
        Temp_temp* a = it->first;
        set<Node<L_block*>*> nodes = it->second;
        while(!nodes.empty()){
            auto n = *nodes.begin();
            nodes.erase(n);

            for(auto y : DF_array[n->info]){
                Node<L_block*>* node_y = revers_graph[y];
                if(phisets[y].find(a) == phisets[y].end() && FG_In(node_y).find(a) != FG_In(node_y).end()){
                    AS_operand* dst = AS_Operand_Temp(a);

                    vector<pair<AS_operand*,Temp_label*>> value;
                    for(int p : node_y->preds){
                        value.push_back(make_pair(AS_Operand_Temp(a), bg.mynodes[p] ->info->label));
                    }

                    L_stm* stm = L_Phi(dst, value);
                    auto posi = y->instrs.begin();
                    y->instrs.insert(++posi, stm);

                    // temp2ASoper.emplace(a, dst);
                    phisets[y].insert(a);

                    if(FG_def(node_y).find(a) == FG_def(node_y).end()){
                        nodes.insert(node_y);
                    }
                }
            }

        }

    }



}

static list<AS_operand **> get_def_int_operand(LLVMIR::L_stm *stm) {
    list<AS_operand **> ret1 = get_def_operand(stm), ret2;
    for (auto AS_op : ret1) {
        if ((**AS_op).u.TEMP->type == TempType::INT_TEMP) {
            ret2.push_back(AS_op);
        }
    }
    return ret2;
}

static list<AS_operand **> get_use_int_operand(LLVMIR::L_stm *stm) {
    list<AS_operand **> ret1 = get_use_operand(stm), ret2;
    for (auto AS_op : ret1) {
        if ((**AS_op).u.TEMP->type == TempType::INT_TEMP) {
            ret2.push_back(AS_op);
        }
    }
    return ret2;
}

static void Rename_temp(GRAPH::Graph<LLVMIR::L_block *> &bg, GRAPH::Node<LLVMIR::L_block *> *n,
                        unordered_map<Temp_temp *, stack<Temp_temp *>> &Stack) {
    unordered_map<Temp_temp*, Temp_temp*> map;
    for(auto stm : n->info->instrs){
        // USE
        if(stm->type != L_StmKind::T_PHI){
            list<AS_operand **> use_list = get_use_operand(stm);
            for(AS_operand ** l : use_list){
                Temp_temp* t = (*l)->u.TEMP;
                if(Stack.find(t) == Stack.end()){
                    stack<Temp_temp *> s;
                    s.push(t);
                    Stack.emplace(t, s);
                    temp2ASoper[t] = *l;
                }else{
                    *l = temp2ASoper[Stack.at(t).top()];
                    map[Stack.at(t).top()] = t;
                }
            }
        }


        // DEF
        list<AS_operand **> def_list = get_def_operand(stm);
        for(AS_operand ** d: def_list){
            Temp_temp*t = (*d)->u.TEMP;
            if(Stack.find(t) == Stack.end()){
                stack<Temp_temp*> s;
                s.push(t);
                Stack.emplace(t, s);
                temp2ASoper[t] = *d;
            }
            Temp_temp* v = Temp_newtemp_int();
            AS_operand* ao = AS_Operand_Temp(v);
            temp2ASoper[v] = ao;
            Stack[t].push(v);
            map[v] = t;
            *d = ao;
        }
    }

    // rename PHI
    for(auto s : n->succs){
        auto succ_node = bg.mynodes[s];
        auto insts = succ_node->info->instrs;

        for(auto stm: insts){
            if(stm->type == L_StmKind::T_PHI){
                auto phis = stm->u.PHI->phis;
                auto preds = succ_node->preds;
                for(auto p: phis){
                    if(p.second == n->info->label){
                        Temp_temp* t = p.first->u.TEMP;
                        if(Stack.find(t) == Stack.end()){
                            stack<Temp_temp *> s;
                            s.push(t);
                            Stack.emplace(t, s);
                            temp2ASoper[t] = p.first;
                        }else{
                            p.first->u.TEMP = Stack[t].top();
                            map[p.first->u.TEMP] = t;
                        }
                        break;
                    }
                }
            }
        }
    }


    for(L_block* s : tree_dominators[n->info].succs){
        Rename_temp(bg, revers_graph[s], Stack);
    }

    for(auto stm: n->info->instrs){
        auto def = get_def(stm);
        for(auto it = def.begin(); it != def.end(); it++){
            Stack[map[*it]].pop();
        }
    }
}

void Rename(GRAPH::Graph<LLVMIR::L_block *> &bg) {
    //   Todo
    unordered_map<Temp_temp *, stack<Temp_temp *>> Stack;

    // for(auto it = bg.mynodes.begin(); it != bg.mynodes.end(); it++){
        // auto node = it->second;
        // Rename_temp(bg, node, Stack);
    // }
    Rename_temp(bg, bg.mynodes[0], Stack);
}
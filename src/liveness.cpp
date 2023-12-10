#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "graph.hpp"
#include "liveness.h"
#include "llvm_ir.h"
#include "temp.h"

using namespace std;
using namespace LLVMIR;
using namespace GRAPH;

struct inOut {
    TempSet_ in;
    TempSet_ out;
};

struct useDef {
    TempSet_ use;
    TempSet_ def;
};

static unordered_map<GRAPH::Node<LLVMIR::L_block*>*, inOut> InOutTable;
static unordered_map<GRAPH::Node<LLVMIR::L_block*>*, useDef> UseDefTable;


static bool is_var(AS_operand *ao) {
    return ao->kind == OperandKind::TEMP && ao->u.TEMP->len == 0;
}


list<AS_operand**> get_all_AS_operand(L_stm* stm) {
    list<AS_operand**> AS_operand_list;
    switch (stm->type) {
        case L_StmKind::T_BINOP: {
            AS_operand_list.push_back(&(stm->u.BINOP->left));
            AS_operand_list.push_back(&(stm->u.BINOP->right));
            AS_operand_list.push_back(&(stm->u.BINOP->dst));

        } break;
        case L_StmKind::T_LOAD: {
            AS_operand_list.push_back(&(stm->u.LOAD->dst));
            AS_operand_list.push_back(&(stm->u.LOAD->ptr));
        } break;
        case L_StmKind::T_STORE: {
            AS_operand_list.push_back(&(stm->u.STORE->src));
            AS_operand_list.push_back(&(stm->u.STORE->ptr));
        } break;
        case L_StmKind::T_LABEL: {
        } break;
        case L_StmKind::T_JUMP: {
        } break;
        case L_StmKind::T_CMP: {
            AS_operand_list.push_back(&(stm->u.CMP->left));
            AS_operand_list.push_back(&(stm->u.CMP->right));
            AS_operand_list.push_back(&(stm->u.CMP->dst));
        } break;
        case L_StmKind::T_CJUMP: {
            AS_operand_list.push_back(&(stm->u.CJUMP->dst));
        } break;
        case L_StmKind::T_MOVE: {
            AS_operand_list.push_back(&(stm->u.MOVE->src));
            AS_operand_list.push_back(&(stm->u.MOVE->dst));
        } break;
        case L_StmKind::T_CALL: {
            AS_operand_list.push_back(&(stm->u.CALL->res));
            for (auto& arg : stm->u.CALL->args) {
                AS_operand_list.push_back(&arg);
            }
        } break;
        case L_StmKind::T_VOID_CALL: {
            for (auto& arg : stm->u.VOID_CALL->args) {
                AS_operand_list.push_back(&arg);
            }
        } break;
        case L_StmKind::T_RETURN: {
            if (stm->u.RET->ret != nullptr) AS_operand_list.push_back(&(stm->u.RET->ret));
        } break;
        case L_StmKind::T_PHI: {
            AS_operand_list.push_back(&(stm->u.PHI->dst));
            for (auto& phi : stm->u.PHI->phis) {
                AS_operand_list.push_back(&(phi.first));
            }
        } break;
        case L_StmKind::T_ALLOCA: {
            AS_operand_list.push_back(&(stm->u.ALLOCA->dst));
        } break;
        case L_StmKind::T_GEP: {
            AS_operand_list.push_back(&(stm->u.GEP->new_ptr));
            AS_operand_list.push_back(&(stm->u.GEP->base_ptr));
            AS_operand_list.push_back(&(stm->u.GEP->index));
        } break;
        default: {
            printf("%d\n", (int)stm->type);
            assert(0);
        }
    }
    
    return AS_operand_list;
}

std::list<AS_operand**> get_def_operand(L_stm* stm) {
    list<AS_operand**> AS_operand_list;
    switch (stm->type) {
        case L_StmKind::T_BINOP: {
            AS_operand_list.push_back(&(stm->u.BINOP->dst));
        } break;
        case L_StmKind::T_LOAD: {
            AS_operand_list.push_back(&(stm->u.LOAD->dst));
        } break;
        // case L_StmKind::T_CMP: {
        //     AS_operand_list.push_back(&(stm->u.CMP->dst));
        // } break;
        case L_StmKind::T_MOVE: {
            AS_operand_list.push_back(&(stm->u.MOVE->dst));
        } break;
        case L_StmKind::T_CALL: {
            AS_operand_list.push_back(&(stm->u.CALL->res));
        } break;
        // case L_StmKind::T_GEP: {
        //     AS_operand_list.push_back(&(stm->u.GEP->new_ptr));
        // } break;
        case L_StmKind::T_PHI:{
            AS_operand_list.push_back(&(stm->u.PHI->dst));
        }
        default: {
        }
    }

    AS_operand_list.erase(std::remove_if(AS_operand_list.begin(),  AS_operand_list.end(), [](AS_operand** value) { return !is_var(*value); }), AS_operand_list.end());
    return AS_operand_list;
}

list<Temp_temp*> get_def(L_stm* stm) {
    auto AS_operand_list = get_def_operand(stm);
    list<Temp_temp*> Temp_list;
    for (auto AS_op : AS_operand_list) {
        Temp_list.push_back((*AS_op)->u.TEMP);
    }
    return Temp_list;
}

std::list<AS_operand**> get_use_operand(L_stm* stm) {
    list<AS_operand**> AS_operand_list;
    switch (stm->type) {
        case L_StmKind::T_BINOP: {
            AS_operand_list.push_back(&(stm->u.BINOP->left));
            AS_operand_list.push_back(&(stm->u.BINOP->right));
        } break;
        case L_StmKind::T_LOAD: {
            AS_operand_list.push_back(&(stm->u.LOAD->ptr));
        } break;
        case L_StmKind::T_STORE: {
            AS_operand_list.push_back(&(stm->u.STORE->ptr));
            AS_operand_list.push_back(&(stm->u.STORE->src));
        } break;
        case L_StmKind::T_CMP: {
            AS_operand_list.push_back(&(stm->u.CMP->left));
            AS_operand_list.push_back(&(stm->u.CMP->right));
        } break;
        // case L_StmKind::T_CJUMP: {
        //     AS_operand_list.push_back(&(stm->u.CJUMP->dst));
        // } break;
        case L_StmKind::T_MOVE: {
            AS_operand_list.push_back(&(stm->u.MOVE->src));
        } break;
        case L_StmKind::T_CALL: {
            for (auto& arg : stm->u.CALL->args) {
                AS_operand_list.push_back(&arg);
            }
        } break;
        case L_StmKind::T_VOID_CALL: {
            for (auto& arg : stm->u.VOID_CALL->args) {
                AS_operand_list.push_back(&arg);
            }
        } break;
        case L_StmKind::T_RETURN: {
            if (stm->u.RET->ret != nullptr) AS_operand_list.push_back(&(stm->u.RET->ret));
        } break;
        case L_StmKind::T_PHI: {
            for (auto& phi : stm->u.PHI->phis) {
                AS_operand_list.push_back(&(phi.first));
            }
        } break;
        case L_StmKind::T_GEP: {
            AS_operand_list.push_back(&(stm->u.GEP->base_ptr));
            AS_operand_list.push_back(&(stm->u.GEP->index));
        } break;
        default: {
        }
    }

    AS_operand_list.erase(std::remove_if(AS_operand_list.begin(),  AS_operand_list.end(), [](AS_operand** value) { return !is_var(*value); }), AS_operand_list.end());
    return AS_operand_list;
}

list<Temp_temp*> get_use(L_stm* stm) {
    auto AS_operand_list = get_use_operand(stm);
    list<Temp_temp*> Temp_list;
    for (auto AS_op : AS_operand_list) {
        Temp_list.push_back((*AS_op)->u.TEMP);
    }
    return Temp_list;
}

static void init_INOUT() {
    InOutTable.clear();
    UseDefTable.clear();
}

#include <assert.h>

TempSet_& FG_Out(GRAPH::Node<LLVMIR::L_block*>* r) { return InOutTable[r].out; }

TempSet_& FG_In(GRAPH::Node<LLVMIR::L_block*>* r) { return InOutTable[r].in; }

TempSet_& FG_def(GRAPH::Node<LLVMIR::L_block*>* r) { return UseDefTable[r].def; }

TempSet_& FG_use(GRAPH::Node<LLVMIR::L_block*>* r) { return UseDefTable[r].use; }


static void Use_def(GRAPH::Node<LLVMIR::L_block*>* r, GRAPH::Graph<LLVMIR::L_block*>& bg,
                    std::vector<Temp_temp*>& args) {
    for(auto t = bg.mynodes.begin(); t != bg.mynodes.end(); t++){
        auto thisNode = t->second;
        useDef usedef;
        for(auto stm: thisNode->info->instrs){
            list<Temp_temp*> use_list = get_use(stm);
            list<Temp_temp*> def_list = get_def(stm);
            for(auto u : use_list){
                if(!TempSet_contains(&usedef.def, u) && !TempSet_contains(&usedef.use, u)) TempSet_add(&usedef.use, u);
            }
            for(auto d : def_list){
                TempSet_add(&usedef.def, d);
            }
        }
        UseDefTable.emplace(thisNode, usedef);
    }
}
static int gi = 0;

static bool LivenessIteration(GRAPH::Node<LLVMIR::L_block*>* r,
                              GRAPH::Graph<LLVMIR::L_block*>& bg) {
    bool changed = false;
    gi++;
    for(auto t = bg.mynodes.begin(); t != bg.mynodes.end(); t++){
        auto thisNode = t->second;
        inOut inout;

        TempSet in = TempSet_union(&FG_use(thisNode), TempSet_diff(&FG_Out(thisNode), &FG_def(thisNode)));
        for(auto i: *in) TempSet_add(&inout.in, i);

        for(auto i: thisNode->succs){
            auto it = bg.mynodes[i];
            TempSet out = TempSet_diff(TempSet_union(&inout.out, &FG_In(it)), &inout.out);
            for(auto o: *out) TempSet_add(&inout.out, o);
        }

        if(!(TempSet_eq(&FG_In(thisNode), &inout.in) && TempSet_eq(&FG_Out(thisNode), &inout.out))) changed = true;
        InOutTable[thisNode] = inout;
    }
    return changed;
}

void PrintTemps(FILE* out, TempSet set) {
    for (auto x : *set) {
        fprintf(out, "%d  ", x->num);
    }
}

void Show_Liveness(FILE* out, GRAPH::Graph<LLVMIR::L_block*>& bg) {
    fprintf(out, "\n\nNumber of iterations=%d\n\n", gi);
    for (auto block_node : bg.mynodes) {
        fprintf(out, "----------------------\n");
        fprintf(out, "block %s \n", block_node.second->info->label->name.c_str());
        fprintf(out, "def=\n");
        PrintTemps(out, &FG_def(block_node.second));
        fprintf(out, "\n");
        fprintf(out, "use=\n");
        PrintTemps(out, &FG_use(block_node.second));
        fprintf(out, "\n");
        fprintf(out, "In=\n");
        PrintTemps(out, &FG_In(block_node.second));
        fprintf(out, "\n");
        fprintf(out, "Out=\n");
        PrintTemps(out, &FG_Out(block_node.second));
        fprintf(out, "\n");
    }
}

// 以block为单位
void Liveness(GRAPH::Node<LLVMIR::L_block*>* r, GRAPH::Graph<LLVMIR::L_block*>& bg,
              std::vector<Temp_temp*>& args) {
    init_INOUT();
    Use_def(r, bg, args);

    gi = 0;
    bool changed = true;
    while (changed) changed = LivenessIteration(r, bg);

    // FILE *outputFile = fopen("liveness.txt", "w");
    // Show_Liveness(outputFile, bg);
    // fflush(outputFile);
    // fclose(outputFile);
}

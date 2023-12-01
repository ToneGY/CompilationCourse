#include "ast2llvm.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <cassert>
#include <list>
#include <iostream>
#include <unordered_set>

using namespace std;
using namespace LLVMIR;

static unordered_map<string,FuncType> funcReturnMap;
static unordered_map<string,StructInfo> structInfoMap;
static unordered_map<string,Name_name*> globalVarMap;
static unordered_map<string,Temp_temp*> localVarMap;
static list<L_stm*> emit_irs;



string stmKind2String(L_StmKind sk){
    switch (sk)
    {
    case L_StmKind::T_BINOP: return "T_BINOP";
    case L_StmKind::T_LOAD: return "T_LOAD";
    case L_StmKind::T_STORE: return "T_STORE";
    case L_StmKind::T_LABEL: return "T_LABEL";
    case L_StmKind::T_JUMP: return "T_JUMP";
    case L_StmKind::T_CMP: return "T_CMP";
    case L_StmKind::T_CJUMP: return "T_CJUMP";
    case L_StmKind::T_MOVE: return "T_MOVE";
    case L_StmKind::T_CALL: return "T_CALL";
    case L_StmKind::T_VOID_CALL: return "T_VOID_CALL";
    case L_StmKind::T_RETURN: return "T_RETURN";
    case L_StmKind::T_PHI: return "T_PHI";
    case L_StmKind::T_NULL: return "T_NULL";
    case L_StmKind::T_ALLOCA: return "T_ALLOCA";
    case L_StmKind::T_GEP: return "T_GEP";
    
    default:
        return "";
    }
}








LLVMIR::L_prog* ast2llvm(aA_program p)
{
    auto defs = ast2llvmProg_first(p);

    auto funcs = ast2llvmProg_second(p);
    

    vector<L_func*> funcs_block;
    for(const auto &f : funcs)
    {
        funcs_block.push_back(ast2llvmFuncBlock(f));
    }
    for(auto &f : funcs_block)
    {
        ast2llvm_moveAlloca(f);
    }
    return new L_prog(defs, funcs_block);
}

int ast2llvmRightVal_first(aA_rightVal r)
{
    if(r == nullptr)
    {
        return 0;
    }
    switch (r->kind)
    {
    case A_arithExprValKind:
    {
        return ast2llvmArithExpr_first(r->u.arithExpr);
        break;
    }
    case A_boolExprValKind:
    {
        return ast2llvmBoolExpr_first(r->u.boolExpr);
        break;
    }
    default:
        break;
    }
    return 0;
}

int ast2llvmBoolExpr_first(aA_boolExpr b)
{
    switch (b->kind)
    {
    case A_boolBiOpExprKind:
    {
        return ast2llvmBoolBiOpExpr_first(b->u.boolBiOpExpr);
        break;
    }
    case A_boolUnitKind:
    {
        return ast2llvmBoolUnit_first(b->u.boolUnit);
        break;
    }
    default:
         break;
    }
    return 0;
}

int ast2llvmBoolBiOpExpr_first(aA_boolBiOpExpr b)
{
    int l = ast2llvmBoolExpr_first(b->left);
    int r = ast2llvmBoolExpr_first(b->right);
    if(b->op == A_and)
    {
        return l && r;
    }
    else
    {
        return l || r;
    }
}

int ast2llvmBoolUOpExpr_first(aA_boolUOpExpr b)
{
    if(b->op == A_not)
    {
        return !ast2llvmBoolUnit_first(b->cond);
    }
    return 0;
}

int ast2llvmBoolUnit_first(aA_boolUnit b)
{
    switch (b->kind)
    {
    case A_comOpExprKind:
    {
        return ast2llvmComOpExpr_first(b->u.comExpr);
        break;
    }
    case A_boolExprKind:
    {
        return ast2llvmBoolExpr_first(b->u.boolExpr);
        break;
    }
    case A_boolUOpExprKind:
    {
        return ast2llvmBoolUOpExpr_first(b->u.boolUOpExpr);
        break;
    }
    default:
        break;
    }
    return 0;
}

int ast2llvmComOpExpr_first(aA_comExpr c)
{
    auto l = ast2llvmExprUnit_first(c->left);
    auto r = ast2llvmExprUnit_first(c->right);
    switch (c->op)
    {
    case A_lt:
    {
        return l < r;
        break;
    }
    case A_le:
    {
        return l <= r;
        break;
    }
    case A_gt:
    {
        return l > r;
        break;
    }
    case A_ge:
    {
        return l >= r;
        break;
    }
    case A_eq:
    {
        return l == r;
        break;
    }
    case A_ne:
    {
        return l != r;
        break;
    }
    default:
        break;
    }
    return 0;
}

int ast2llvmArithBiOpExpr_first(aA_arithBiOpExpr a)
{
    auto l= ast2llvmArithExpr_first(a->left);
    auto r = ast2llvmArithExpr_first(a->right);
    switch (a->op)
    {
    case A_add:
    {
        return l + r;
        break;
    }
    case A_sub:
    {
        return l - r;
        break;
    }
    case A_mul:
    {
        return l * r;
        break;
    }
    case A_div:
    {
        return l / r;
        break;
    }
    default:
        break;
    }
    return 0;
}

int ast2llvmArithUExpr_first(aA_arithUExpr a)
{
    if(a->op == A_neg)
    {
        return -ast2llvmExprUnit_first(a->expr);
    }
    return 0;
}

int ast2llvmArithExpr_first(aA_arithExpr a)
{
    switch (a->kind)
    {
    case A_arithBiOpExprKind:
    {
        return ast2llvmArithBiOpExpr_first(a->u.arithBiOpExpr);
        break;
    }
    case A_exprUnitKind:
    {
        return ast2llvmExprUnit_first(a->u.exprUnit);
        break;
    }
    default:
        assert(0);
        break;
    }
    return 0;
}

int ast2llvmExprUnit_first(aA_exprUnit e)
{
    if(e->kind == A_numExprKind)
    {
        return e->u.num;
    }
    else if(e->kind == A_arithExprKind)
    {
        return ast2llvmArithExpr_first(e->u.arithExpr);
    }
    else if(e->kind == A_arithUExprKind)
    {
        return ast2llvmArithUExpr_first(e->u.arithUExpr);
    }
    else
    {
        assert(0);
    }
    return 0;
}

std::vector<LLVMIR::L_def*> ast2llvmProg_first(aA_program p)
{
    vector<L_def*> defs;
    defs.push_back(L_Funcdecl("getch",vector<TempDef>(),FuncType(ReturnType::INT_TYPE)));
    defs.push_back(L_Funcdecl("getint",vector<TempDef>(),FuncType(ReturnType::INT_TYPE)));
    
    funcReturnMap.emplace("getch",FuncType(ReturnType::INT_TYPE));
    funcReturnMap.emplace("getint",FuncType(ReturnType::INT_TYPE));



    defs.push_back(L_Funcdecl("putch",vector<TempDef>{TempDef(TempType::INT_TEMP)},FuncType(ReturnType::VOID_TYPE)));

    defs.push_back(L_Funcdecl("putint",vector<TempDef>{TempDef(TempType::INT_TEMP)},FuncType(ReturnType::VOID_TYPE)));
    
    defs.push_back(L_Funcdecl("putarray",vector<TempDef>{TempDef(TempType::INT_TEMP),TempDef(TempType::INT_PTR,-1)},FuncType(ReturnType::VOID_TYPE)));

    defs.push_back(L_Funcdecl("_sysy_starttime",vector<TempDef>{TempDef(TempType::INT_TEMP)},FuncType(ReturnType::VOID_TYPE)));
    defs.push_back(L_Funcdecl("_sysy_stoptime",vector<TempDef>{TempDef(TempType::INT_TEMP)},FuncType(ReturnType::VOID_TYPE)));
    for(const auto &v : p->programElements)
    {
        switch (v->kind)
        {
        case A_programNullStmtKind:
        {
            break;
        }
        case A_programVarDeclStmtKind:
        {
            if(v->u.varDeclStmt->kind == A_varDeclKind)
            {
                if(v->u.varDeclStmt->u.varDecl->kind == A_varDeclScalarKind)
                {
                    if(v->u.varDeclStmt->u.varDecl->u.declScalar->type->type == A_structTypeKind)
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declScalar->id, 
                                            Name_newname_struct(Temp_newlabel_named(*v->u.varDeclStmt->u.varDecl->u.declScalar->id),
                                                                *v->u.varDeclStmt->u.varDecl->u.declScalar->type->u.structType));
                        TempDef def(TempType::STRUCT_TEMP,
                                    0,
                                    *v->u.varDeclStmt->u.varDecl->u.declScalar->type->u.structType);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declScalar->id,
                                                    def,
                                                    vector<int>()));
                    }
                    else
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declScalar->id,
                            Name_newname_int(Temp_newlabel_named(*v->u.varDeclStmt->u.varDecl->u.declScalar->id)));
                        TempDef def(TempType::INT_TEMP,0);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declScalar->id,def,vector<int>()));
                    }
                }
                else if(v->u.varDeclStmt->u.varDecl->kind == A_varDeclArrayKind)
                {
                    if(v->u.varDeclStmt->u.varDecl->u.declArray->type->type == A_structTypeKind)
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declArray->id,
                                            Name_newname_struct_ptr(Temp_newlabel_named(*v->u.varDeclStmt->u.varDecl->u.declArray->id),
                                                                    v->u.varDeclStmt->u.varDecl->u.declArray->len,
                                                                    *v->u.varDeclStmt->u.varDecl->u.declArray->type->u.structType));
                        TempDef def(TempType::STRUCT_PTR,
                                    v->u.varDeclStmt->u.varDecl->u.declArray->len,
                                    *v->u.varDeclStmt->u.varDecl->u.declArray->type->u.structType);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declArray->id,
                                                    def,
                                                    vector<int>()));
                    }
                    else
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declArray->id,
                            Name_newname_int_ptr(Temp_newlabel_named(*v->u.varDeclStmt->u.varDecl->u.declArray->id),v->u.varDeclStmt->u.varDecl->u.declArray->len));
                        TempDef def(TempType::INT_PTR,v->u.varDeclStmt->u.varDecl->u.declArray->len);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declArray->id,def,vector<int>()));
                    }
                }
                else
                {
                    assert(0);
                }
            }
            else if(v->u.varDeclStmt->kind == A_varDefKind)
            {
                if(v->u.varDeclStmt->u.varDef->kind == A_varDefScalarKind)
                {
                    if(v->u.varDeclStmt->u.varDef->u.defScalar->type->type == A_structTypeKind)
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defScalar->id,
                            Name_newname_struct(Temp_newlabel_named(*v->u.varDeclStmt->u.varDef->u.defScalar->id),*v->u.varDeclStmt->u.varDef->u.defScalar->type->u.structType));
                        TempDef def(TempType::STRUCT_TEMP,0,*v->u.varDeclStmt->u.varDef->u.defScalar->type->u.structType);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDef->u.defScalar->id,def,vector<int>()));
                    }
                    else
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defScalar->id,
                            Name_newname_int(Temp_newlabel_named(*v->u.varDeclStmt->u.varDef->u.defScalar->id)));
                        TempDef def(TempType::INT_TEMP,0);
                        vector<int> init;
                        init.push_back(ast2llvmRightVal_first(v->u.varDeclStmt->u.varDef->u.defScalar->val));
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDef->u.defScalar->id,def,init));
                    }
                }
                else if(v->u.varDeclStmt->u.varDef->kind == A_varDefArrayKind)
                {
                    if(v->u.varDeclStmt->u.varDef->u.defArray->type->type == A_structTypeKind)
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defArray->id,
                            Name_newname_struct_ptr(Temp_newlabel_named(*v->u.varDeclStmt->u.varDef->u.defArray->id),v->u.varDeclStmt->u.varDef->u.defArray->len,*v->u.varDeclStmt->u.varDef->u.defArray->type->u.structType));
                        TempDef def(TempType::STRUCT_PTR,v->u.varDeclStmt->u.varDef->u.defArray->len,*v->u.varDeclStmt->u.varDef->u.defArray->type->u.structType);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDef->u.defArray->id,def,vector<int>()));
                    }
                    else
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defArray->id,
                            Name_newname_int_ptr(Temp_newlabel_named(*v->u.varDeclStmt->u.varDef->u.defArray->id),v->u.varDeclStmt->u.varDef->u.defArray->len));
                        TempDef def(TempType::INT_PTR,v->u.varDeclStmt->u.varDef->u.defArray->len);
                        vector<int> init;
                        for(auto &el : v->u.varDeclStmt->u.varDef->u.defArray->vals)
                        {
                            init.push_back(ast2llvmRightVal_first(el));
                        }
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDef->u.defArray->id,def,init));
                    }
                }
                else
                {
                    assert(0);
                }
            }
            else
            {
                assert(0);
            }
            break;
        }
        case A_programStructDefKind:
        {
            StructInfo si;
            int off = 0;
            vector<TempDef> members;
            for(const auto &decl : v->u.structDef->varDecls)
            {
                if(decl->kind == A_varDeclScalarKind)
                {
                    if(decl->u.declScalar->type->type == A_structTypeKind)
                    {
                        TempDef def(TempType::STRUCT_TEMP,0,*decl->u.declScalar->type->u.structType);
                        MemberInfo info(off++,def);
                        si.memberinfos.emplace(*decl->u.declScalar->id,info);
                        members.push_back(def);
                    }
                    else
                    {
                        TempDef def(TempType::INT_TEMP,0);
                        MemberInfo info(off++,def);
                        si.memberinfos.emplace(*decl->u.declScalar->id,info);
                        members.push_back(def);
                    }
                }
                else if(decl->kind == A_varDeclArrayKind)
                {
                    if(decl->u.declArray->type->type == A_structTypeKind)
                    {
                        TempDef def(TempType::STRUCT_PTR,decl->u.declArray->len,*decl->u.declArray->type->u.structType);
                        MemberInfo info(off++,def);
                        si.memberinfos.emplace(*decl->u.declArray->id,info);
                        members.push_back(def);
                    }
                    else
                    {
                        TempDef def(TempType::INT_PTR,decl->u.declArray->len);
                        MemberInfo info(off++,def);
                        si.memberinfos.emplace(*decl->u.declArray->id,info);
                        members.push_back(def);
                    }
                }
                else
                {
                    assert(0);
                }
            }
            structInfoMap.emplace(*v->u.structDef->id,std::move(si));
            defs.push_back(L_Structdef(*v->u.structDef->id,members));
            break;
        }
        case A_programFnDeclStmtKind:
        {
            FuncType type;
            if(v->u.fnDeclStmt->fnDecl->type == nullptr)
            {
                type.type = ReturnType::VOID_TYPE;
            }
            if(v->u.fnDeclStmt->fnDecl->type->type == A_nativeTypeKind)
            {
                type.type = ReturnType::INT_TYPE;
            }
            else if(v->u.fnDeclStmt->fnDecl->type->type == A_structTypeKind)
            {
                type.type = ReturnType::STRUCT_TYPE;
                type.structname = *v->u.fnDeclStmt->fnDecl->type->u.structType;
            }
            else
            {
                assert(0);
            }
            if(funcReturnMap.find(*v->u.fnDeclStmt->fnDecl->id) == funcReturnMap.end())
                funcReturnMap.emplace(*v->u.fnDeclStmt->fnDecl->id,std::move(type));
            vector<TempDef> args;
            for(const auto & decl : v->u.fnDeclStmt->fnDecl->paramDecl->varDecls)
            {
                if(decl->kind == A_varDeclScalarKind)
                {
                    if(decl->u.declScalar->type->type == A_structTypeKind)
                    {
                        TempDef def(TempType::STRUCT_PTR,0,*decl->u.declScalar->type->u.structType);
                        args.push_back(def);
                    }
                    else
                    {
                        TempDef def(TempType::INT_TEMP,0);
                        args.push_back(def);
                    }
                }
                else if(decl->kind == A_varDeclArrayKind)
                {
                    if(decl->u.declArray->type->type == A_structTypeKind)
                    {
                        TempDef def(TempType::STRUCT_PTR,-1,*decl->u.declArray->type->u.structType);
                        args.push_back(def);
                    }
                    else
                    {
                        TempDef def(TempType::INT_PTR,-1);
                        args.push_back(def);
                    }
                }
                else
                {
                    assert(0);
                }
            }
            defs.push_back(L_Funcdecl(*v->u.fnDeclStmt->fnDecl->id,args,type));
            break;
        }
        case A_programFnDefKind:
        {
            if(funcReturnMap.find(*v->u.fnDef->fnDecl->id) == funcReturnMap.end())
            {
                FuncType type;
                if(v->u.fnDef->fnDecl->type == nullptr)
                {
                    type.type = ReturnType::VOID_TYPE;
                }
                else if(v->u.fnDef->fnDecl->type->type == A_nativeTypeKind)
                {
                    type.type = ReturnType::INT_TYPE;
                }
                else if(v->u.fnDef->fnDecl->type->type == A_structTypeKind)
                {
                    type.type = ReturnType::STRUCT_TYPE;
                    type.structname = *v->u.fnDef->fnDecl->type->u.structType;
                }
                else
                {
                    assert(0);
                }
                funcReturnMap.emplace(*v->u.fnDef->fnDecl->id,std::move(type));
            }
            break;
        }
        default:
            assert(0);
            break;
        }
    }

    return defs;
}

std::vector<Func_local*> ast2llvmProg_second(aA_program p)
{
    std::vector<Func_local*> flv;
    for(const auto &v : p->programElements){
        if(v->kind == A_programElementType::A_programFnDefKind){
            emit_irs.clear();
            localVarMap.clear();
            Func_local* fl = ast2llvmFunc(v->u.fnDef);
            flv.push_back(fl);
        }
    }
    return flv;
}

FuncType fd2ft(aA_fnDecl fnd){
    aA_type t = fnd->type;
    if(t==nullptr) return FuncType(ReturnType::VOID_TYPE);
    ReturnType rt;
    string name = std::string();
    switch (t->type)
    {
    case A_dataType::A_nativeTypeKind:
        rt = ReturnType::INT_TYPE;
        break;
    case A_dataType::A_structTypeKind:
        rt = ReturnType::STRUCT_TYPE;
        name = *(t->u.structType);
        break;
    }
    return FuncType(rt, name);
}

std::vector<Temp_temp*> fd2args(aA_fnDecl fnd){
    std::vector<Temp_temp*> vec;
    for(auto a : fnd->paramDecl->varDecls){
        Temp_temp* tt;
        AS_operand* ao;
        Temp_temp* t1;
        switch (a->kind)
        {
        case A_varDeclType::A_varDeclScalarKind :
            switch (a->u.declScalar->type->type)
            {
            case A_dataType::A_nativeTypeKind:
                tt = Temp_newtemp_int(); // int类型传值
                t1 = Temp_newtemp_int_ptr(0);
                ao = AS_Operand_Temp(t1);
                emit_irs.emplace_back(L_Alloca(ao));
                emit_irs.emplace_back(L_Store(AS_Operand_Temp(tt), ao));
                localVarMap.emplace(*a->u.declScalar->id, t1);
                break;
            case A_dataType::A_structTypeKind:
                tt = Temp_newtemp_struct_ptr(0, *a->u.declScalar->type->u.structType);
                localVarMap.emplace(*a->u.declScalar->id, tt);
                break;
            }
            break;
        case A_varDeclType::A_varDeclArrayKind:
            switch (a->u.declArray->type->type)
            {
            case A_dataType::A_nativeTypeKind:
                tt = Temp_newtemp_int_ptr(-1); // -1代表数组头
                localVarMap.emplace(*a->u.declArray->id, tt);
                break;
            case A_dataType::A_structTypeKind:
                tt = Temp_newtemp_struct_ptr(-1, *a->u.declArray->type->u.structType);
                localVarMap.emplace(*a->u.declArray->id, tt);
                break;
            }
            break;
        }
        if(tt != nullptr) vec.push_back(tt);
    }
    return vec;
}


void vds2tt(aA_varDeclStmt v){
    Temp_temp* tt;
    string id;
    if(v->kind == A_varDeclStmtType::A_varDeclKind){
            aA_varDecl vd = v->u.varDecl;
            if(vd->kind == A_varDeclType::A_varDeclScalarKind){
                aA_varDeclScalar vds = vd->u.declScalar;
                id = *vds->id;
                switch (vds->type->type)
                {
                case A_dataType::A_nativeTypeKind:

                    tt = Temp_newtemp_int_ptr(0);
                    break;
                case A_dataType::A_structTypeKind:
                    tt = Temp_newtemp_struct_ptr(0, *vds->type->u.structType);
                    break;
                }
            }else if(vd->kind == A_varDeclType::A_varDeclArrayKind){
                aA_varDeclArray vda = vd->u.declArray;
                id = *vda->id;
                switch(vda->type->type)
                {
                    case A_dataType::A_nativeTypeKind:
                        tt = Temp_newtemp_int_ptr(vda->len);
                        break;
                    case A_dataType::A_structTypeKind:
                        tt = Temp_newtemp_struct_ptr(vda->len, *vda->type->u.structType);
                        break;
                }

            }
            localVarMap.emplace(id, tt);
            AS_operand* lv = AS_Operand_Temp(tt);
            emit_irs.emplace_back(L_Alloca(lv));
    }else if(v->kind == A_varDeclStmtType::A_varDefKind){
            vector<aA_rightVal> rvs;
            aA_varDef vdf = v->u.varDef;
            if(vdf->kind == A_varDefType::A_varDefScalarKind){
                aA_varDefScalar vds = vdf->u.defScalar;
                id = *vds->id;
                // rvs.push_back(vds->val);
                if(vds->type->type == A_dataType::A_nativeTypeKind){
                    tt = Temp_newtemp_int_ptr(0);
                    AS_operand* lv = AS_Operand_Temp(tt);
                    emit_irs.emplace_back(L_Alloca(lv));
                    AS_operand* rv = ast2llvmRightVal(vds->val);
                    emit_irs.emplace_back(L_Store(rv, lv));
                }else{
                    tt = Temp_newtemp_struct_ptr(0, *vds->type->u.structType);
                }
            }else if(vdf->kind == A_varDefType::A_varDefArrayKind){
                aA_varDefArray vda = vdf->u.defArray;
                id = *vda->id;
                rvs = vda->vals;
                if(vda->type->type == A_dataType::A_nativeTypeKind){
                    tt = Temp_newtemp_int_ptr(vda->len);
                    AS_operand* lv = AS_Operand_Temp(tt);
                    emit_irs.emplace_back(L_Alloca(lv));
                    for(int i = 0; i < rvs.size(); i++){
                        AS_operand* new_ptr = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
                        emit_irs.emplace_back(L_Gep(new_ptr, lv, AS_Operand_Const(i)));
                        AS_operand* rv = ast2llvmRightVal(rvs[i]);
                        emit_irs.emplace_back(L_Store(rv, new_ptr));
                    }
                }
                else if(vda->type->type ==  A_dataType::A_structTypeKind)
                    tt = Temp_newtemp_struct_ptr(vda->len, *vda->type->u.structType);
            }
            localVarMap.emplace(id, tt);
            if(!rvs.empty()){

            }
    }
}

AS_operand* getIntOrPtr(AS_operand* ids){
    if(ids->kind == OperandKind::NAME){
        if((ids->u.NAME->type == TempType::INT_TEMP || ids->u.NAME->type == TempType::INT_PTR) && ids->u.NAME->len == 0){
            AS_operand* ao = AS_Operand_Temp(Temp_newtemp_int());
            emit_irs.emplace_back(L_Load(ao, ids));
            return ao;
        }
    }else if(ids->kind == OperandKind::TEMP){
        if(ids->u.TEMP->type == TempType::INT_PTR  && ids->u.TEMP->len == 0){
            AS_operand* ao = AS_Operand_Temp(Temp_newtemp_int());
            emit_irs.emplace_back(L_Load(ao, ids));
            return ao;
        }
    }
    return ids;
}

Func_local* ast2llvmFunc(aA_fnDef f)
{
    vector<aA_codeBlockStmt> stmts = f->stmts;
    emit_irs.emplace_back(L_Label(Temp_newlabel()));
    aA_fnDecl fd = f->fnDecl;
    std::vector<Temp_temp*> args = fd2args(fd);
    FuncType ret = fd2ft(fd);
    for(auto s : stmts){
        ast2llvmBlock(s, nullptr, nullptr);
    }
    if(emit_irs.back()->type != L_StmKind::T_RETURN){
        switch (ret.type)
        {
        case ReturnType::INT_TYPE:
            emit_irs.emplace_back(L_Ret(AS_Operand_Const(0)));
            break;
        case ReturnType::STRUCT_TYPE:
            emit_irs.emplace_back(L_Ret(AS_Operand_Temp(Temp_newtemp_struct_ptr(0, ret.structname))));
        case ReturnType::VOID_TYPE:
            emit_irs.emplace_back(L_Ret(nullptr));
        }
    }
    Func_local* fl =new Func_local(*fd->id, ret, args, emit_irs);
    return fl;
}

void ast2llvmBlock(aA_codeBlockStmt b,Temp_label *con_label,Temp_label *bre_label)
{
    switch(b->kind){
        case A_codeBlockStmtType::A_assignStmtKind:
        {
            // std::cout << "A_assignStmtKind\n";
            auto v = b->u.assignStmt;
            AS_operand* aol = ast2llvmLeftVal(v->leftVal);
            AS_operand* aor = ast2llvmRightVal(v->rightVal);
            emit_irs.emplace_back(L_Store(aor, aol));
            // std::cout << "A_assignStmtKind_done\n";
        }
        break;
        case A_codeBlockStmtType::A_varDeclStmtKind:
        { 
            // std::cout << "A_varDeclStmtKind\n";
            aA_varDeclStmt v = b->u.varDeclStmt;
            vds2tt(v);
            // std::cout << "A_varDeclStmtKind_done\n";
        }
        break;
        case A_codeBlockStmtType::A_ifStmtKind:
        {
            // std::cout << "A_ifStmtKind\n";
            Temp_label* trueLabel = Temp_newlabel();
            Temp_label* falseLabel = Temp_newlabel();
            Temp_label* endLabel = Temp_newlabel();

            aA_ifStmt is = b->u.ifStmt;
            ast2llvmBoolExpr(is->boolExpr, trueLabel, falseLabel);

            emit_irs.emplace_back(L_Label(trueLabel));
            int size = is->ifStmts.size();
            for(int i = 0; i < size; i++) ast2llvmBlock(is->ifStmts[i], con_label, bre_label);
            emit_irs.emplace_back(L_Jump(endLabel));

            emit_irs.emplace_back(L_Label(falseLabel));
            size = is->elseStmts.size();
            for(int i = 0; i < size; i++) ast2llvmBlock(is->elseStmts[i], con_label, bre_label);
            emit_irs.emplace_back(L_Jump(endLabel));

            emit_irs.emplace_back(L_Label(endLabel));
            // std::cout << "A_ifStmtKind_done\n";
        }
        break;
        case A_codeBlockStmtType::A_whileStmtKind:
        {
            // std::cout << "A_whileStmtKind\n";
            Temp_label* conLabel = Temp_newlabel();
            Temp_label* whiLabel = Temp_newlabel();
            Temp_label* breLabel = Temp_newlabel();
            emit_irs.emplace_back(L_Jump(conLabel));
            aA_whileStmt ws = b->u.whileStmt;

            emit_irs.emplace_back(L_Label(conLabel));
            ast2llvmBoolExpr(ws->boolExpr, whiLabel, breLabel);

            emit_irs.emplace_back(L_Label(whiLabel));
            int size = ws->whileStmts.size();
            for(int i = 0; i < size; i++){
                ast2llvmBlock(ws->whileStmts[i], conLabel, breLabel);
            }
            emit_irs.emplace_back(L_Jump(conLabel)); 

            emit_irs.emplace_back(L_Label(breLabel));
            // std::cout << "A_whileStmtKind_done\n";
        }
        break;
        case A_codeBlockStmtType::A_breakStmtKind:
        {         
            // std::cout << "A_breakStmtKind\n";
            assert(con_label != nullptr && bre_label != nullptr);
            emit_irs.emplace_back(L_Jump(bre_label));
            // std::cout << "A_breakStmtKind_done\n";
        }
        break;
        case A_codeBlockStmtType::A_continueStmtKind:
        {
            // std::cout << "A_continueStmtKind\n";
            assert(con_label != nullptr && bre_label != nullptr);
            emit_irs.emplace_back(L_Jump(con_label));
            // std::cout << "A_continueStmtKind_done\n";
        }
        break;
        case A_codeBlockStmtType::A_callStmtKind:
        {
            // std::cout << "A_callStmtKind\n";
            aA_fnCall fc = b->u.callStmt->fnCall;
            string fn = *fc->fn;

            vector<AS_operand*> aov;
            for(auto v: fc->vals) aov.push_back(ast2llvmRightVal(v));

            emit_irs.emplace_back(L_Voidcall(fn, aov));
            // std::cout << "A_callStmtKind_done\n";
        }
        break;
        case A_codeBlockStmtType::A_returnStmtKind:
        {
            // std::cout << "A_returnStmtKind\n";
            AS_operand* ao = nullptr;
            if(b->u.returnStmt->retVal != nullptr){
                ao = ast2llvmRightVal(b->u.returnStmt->retVal);
            }
            emit_irs.emplace_back(L_Ret(ao));
            // std::cout << "A_returnStmtKind_done\n";
        }
        break;
        case A_codeBlockStmtType::A_nullStmtKind:
        break;
    }
    
}

AS_operand* ast2llvmRightVal(aA_rightVal r)
{
    switch (r->kind)
    {
    case A_rightValType::A_arithExprValKind:
        return ast2llvmArithExpr(r->u.arithExpr);
    case A_rightValType::A_boolExprValKind:
        Temp_label* back_label = Temp_newlabel();
        AS_operand* ao = ast2llvmBoolExpr(r->u.boolExpr, back_label, nullptr);
        emit_irs.emplace_back(L_Label(back_label));
        return getIntOrPtr(ao);
    }
    return nullptr;
}


AS_operand* getIdPtr(string id){
    auto lv = localVarMap.find(id);
    if(lv == localVarMap.end()){
        auto gv = globalVarMap.find(id);
        assert(gv!=globalVarMap.end());
        AS_operand* ids = AS_Operand_Name(gv->second);
        return ids;
    }else{
        AS_operand* ids = AS_Operand_Temp(lv->second);
        return ids;
    }
}


AS_operand* TempDefnewAS_operand(TempDef td){
    switch (td.kind)
    {
    case TempType::INT_TEMP:
    case TempType::INT_PTR:
        return AS_Operand_Temp(Temp_newtemp_int_ptr(td.len));
    case TempType::STRUCT_TEMP:
    case TempType::STRUCT_PTR:
        return AS_Operand_Temp(Temp_newtemp_struct_ptr(td.len, td.structname));
    }
}


AS_operand* getMemberOff_Type(string structName, string memId, AS_operand*& off){
    auto si = structInfoMap.find(structName);
    assert(si != structInfoMap.end());
    auto mi = si->second.memberinfos.find(memId);
    assert(mi != si->second.memberinfos.end());
    AS_operand* ao = TempDefnewAS_operand(mi->second.def);
    off = AS_Operand_Const(mi->second.offset);
    return ao;
}

AS_operand* arrayElement(AS_operand* arr){
    switch (arr->kind)
    {
    case OperandKind::TEMP:
        switch(arr->u.TEMP->type){
            case TempType::INT_TEMP:
            case TempType::INT_PTR:
                return AS_Operand_Temp(Temp_newtemp_int_ptr(0));
            case TempType::STRUCT_TEMP:
            case TempType::STRUCT_PTR:
                return AS_Operand_Temp(Temp_newtemp_struct_ptr(0, arr->u.TEMP->structname));
        }
    case OperandKind::NAME:
        switch(arr->u.NAME->type){
            case TempType::INT_TEMP:
            case TempType::INT_PTR:
                return AS_Operand_Temp(Temp_newtemp_int_ptr(0));
            case TempType::STRUCT_TEMP:
            case TempType::STRUCT_PTR:
                return AS_Operand_Temp(Temp_newtemp_struct_ptr(0, arr->u.NAME->structname));
        }
    default:
        assert(0);
    }
}

AS_operand* ast2llvmLeftVal(aA_leftVal l)
{
    switch(l->kind){
        case A_leftValType::A_varValKind:
            return getIdPtr(*l->u.id);
        case A_leftValType::A_arrValKind:
        {
            AS_operand* arr = ast2llvmLeftVal(l->u.arrExpr->arr);
            AS_operand* ids = ast2llvmIndexExpr(l->u.arrExpr->idx);
            AS_operand* np = arrayElement(arr);
            emit_irs.emplace_back(L_Gep(np, arr, ids));
            return np;
        }
        case A_leftValType::A_memberValKind:
        {
            AS_operand* s = ast2llvmLeftVal(l->u.memberExpr->structId);
            AS_operand* off=nullptr;
            AS_operand* m = getMemberOff_Type(s->u.TEMP->structname, *l->u.memberExpr->memberId, off);
            assert(off!=nullptr);
            emit_irs.emplace_back(L_Gep(m, s, off));
            return m;
        }
    }
    return nullptr;
}


AS_operand* ast2llvmIndexExpr(aA_indexExpr index)
{
    switch(index->kind){
        case A_indexExprKind::A_numIndexKind:
            return AS_Operand_Const(index->u.num);
        case A_indexExprKind::A_idIndexKind:
        {
            string id = *index->u.id;
            return getIntOrPtr(getIdPtr(id));
        }
    }
    return nullptr;
}


AS_operand* ast2llvmBoolExpr(aA_boolExpr b,Temp_label *true_label,Temp_label *false_label)
{
    bool is_rightVal = false;
    Temp_label* back_label;
    if(false_label == nullptr){
        is_rightVal = true;
        back_label = true_label;
        true_label = Temp_newlabel();
        false_label = Temp_newlabel();
    }
    
    switch (b->kind)
    {
    case A_boolExprType::A_boolBiOpExprKind:
        ast2llvmBoolBiOpExpr(b->u.boolBiOpExpr, true_label, false_label);
        break;
    case A_boolExprType::A_boolUnitKind:
        ast2llvmBoolUnit(b->u.boolUnit, true_label, false_label);
        break;
    }

    if(is_rightVal){
        AS_operand* ao = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
        emit_irs.emplace_back(L_Label(true_label));
        emit_irs.emplace_back(L_Alloca(ao));
        emit_irs.emplace_back(L_Store(AS_Operand_Const(1), ao));
        emit_irs.emplace_back(L_Jump(back_label));

        emit_irs.emplace_back(L_Label(false_label));
        emit_irs.emplace_back(L_Alloca(ao));//!
        emit_irs.emplace_back(L_Store(AS_Operand_Const(0), ao));
        emit_irs.emplace_back(L_Jump(back_label));

        return ao;

    }else{
        return nullptr;
    }
}

void ast2llvmBoolBiOpExpr(aA_boolBiOpExpr b,Temp_label *true_label,Temp_label *false_label)
{
    if(b->op == A_boolBiOp::A_and){
        Temp_label* tmpTrueLabel = Temp_newlabel();
        ast2llvmBoolExpr(b->left, tmpTrueLabel, false_label);
        emit_irs.emplace_back(L_Label(tmpTrueLabel));
        ast2llvmBoolExpr(b->right, true_label, false_label);
    }else if(b->op == A_boolBiOp::A_or){
        Temp_label* tmpFalseLabel = Temp_newlabel();
        ast2llvmBoolExpr(b->left, true_label, tmpFalseLabel);
        emit_irs.emplace_back(L_Label(tmpFalseLabel));
        ast2llvmBoolExpr(b->right, true_label, false_label);
    }
}

void ast2llvmBoolUnit(aA_boolUnit b,Temp_label *true_label,Temp_label *false_label)
{
    switch (b->kind)
    {
    case A_boolUnitType::A_comOpExprKind:
        ast2llvmComOpExpr(b->u.comExpr, true_label, false_label);
        break;
    case A_boolUnitType::A_boolExprKind:
        ast2llvmBoolExpr(b->u.boolExpr, true_label, false_label);
        break;
    case A_boolUnitType::A_boolUOpExprKind:
        ast2llvmBoolUnit(b->u.boolUOpExpr->cond, false_label, true_label);
        break;
    }
}

L_relopKind comOp2relOp(A_comOp op){
    switch (op)
    {
    case A_comOp::A_lt:
        return L_relopKind::T_lt;
    case A_comOp::A_le:
        return L_relopKind::T_le;
    case A_comOp::A_gt:
        return L_relopKind::T_gt;
    case A_comOp::A_ge:
        return L_relopKind::T_ge;
    case A_comOp::A_eq:
        return L_relopKind::T_eq;
    case A_comOp::A_ne:
        return L_relopKind::T_ne;
    }
    assert(0);
}

void ast2llvmComOpExpr(aA_comExpr c,Temp_label *true_label,Temp_label *false_label)
{
    AS_operand* left = ast2llvmExprUnit(c->left);
    AS_operand* right = ast2llvmExprUnit(c->right);
    L_relopKind op = comOp2relOp(c->op);
    AS_operand* dst = AS_Operand_Temp(Temp_newtemp_int());
    emit_irs.emplace_back(L_Cmp(op, left, right, dst));
    emit_irs.emplace_back(L_Cjump(dst, true_label, false_label));
}

L_binopKind arithBiop2L(A_arithBiOp op){
    switch(op){
        case A_arithBiOp::A_add:
            return L_binopKind::T_plus;
        case A_arithBiOp::A_sub:
            return L_binopKind::T_minus;
        case A_arithBiOp::A_mul:
            return L_binopKind::T_mul;
        case A_arithBiOp::A_div:
            return L_binopKind::T_div;
    }
    assert(0);
}

AS_operand* ast2llvmArithBiOpExpr(aA_arithBiOpExpr a)
{
    L_binopKind op = arithBiop2L(a->op);
    AS_operand* left = ast2llvmArithExpr(a->left);
    AS_operand* right = ast2llvmArithExpr(a->right);
    AS_operand* dst = AS_Operand_Temp(Temp_newtemp_int());
    emit_irs.emplace_back(L_Binop(op, left, right, dst));
    return dst;
}

AS_operand* ast2llvmArithUExpr(aA_arithUExpr a)
{
    AS_operand* n = ast2llvmExprUnit(a->expr);
    if(a->op == A_arithUOp::A_neg){
        AS_operand* dst = AS_Operand_Temp(Temp_newtemp_int());
        emit_irs.emplace_back(L_Binop(L_binopKind::T_mul, AS_Operand_Const(-1), n, dst));
        return dst;
    }
    return nullptr;
}

AS_operand* ast2llvmArithExpr(aA_arithExpr a)
{
    switch(a->kind){
        case A_arithExprType::A_arithBiOpExprKind:
            return ast2llvmArithBiOpExpr(a->u.arithBiOpExpr);            
        case A_arithExprType::A_exprUnitKind:
            return ast2llvmExprUnit(a->u.exprUnit);
    }
    return nullptr;
}



AS_operand* ast2llvmExprUnit(aA_exprUnit e)
{
    switch(e->kind){
        case A_exprUnitType::A_arithExprKind:
            return ast2llvmArithExpr(e->u.arithExpr);
        case A_exprUnitType::A_arithUExprKind:
            return ast2llvmArithUExpr(e->u.arithUExpr);
        case A_exprUnitType::A_arrayExprKind:
        {
            AS_operand* left = ast2llvmLeftVal(e->u.arrayExpr->arr);
            AS_operand* idx = ast2llvmIndexExpr(e->u.arrayExpr->idx);
            AS_operand* np = arrayElement(left);

            emit_irs.emplace_back(L_Gep(np, left, idx));
            return getIntOrPtr(np);
        }
        case A_exprUnitType::A_memberExprKind:
        {
            AS_operand* left = ast2llvmLeftVal(e->u.memberExpr->structId);
            string structName;
            switch (left->kind) {
            case OperandKind::TEMP: structName = left->u.TEMP->structname; break;
            case OperandKind::NAME: structName = left->u.NAME->structname; break;
            default: assert(0);                
            }
            AS_operand* off =nullptr;
            AS_operand* newptr = getMemberOff_Type(structName, *e->u.memberExpr->memberId, off);
            emit_irs.emplace_back(L_Gep(newptr, left, off));
            return getIntOrPtr(newptr);
        }
        case A_exprUnitType::A_fnCallKind:
        {
            aA_fnCall fc = e->u.callExpr;
            string fn = *fc->fn;

            vector<AS_operand*> aov;
            for(auto v: fc->vals) aov.push_back(ast2llvmRightVal(v));

            auto item = funcReturnMap.find(fn);
            assert(item != funcReturnMap.end());
            if(item->second.type == ReturnType::VOID_TYPE){
                emit_irs.emplace_back(L_Voidcall(fn, aov));
            }else if(item->second.type == ReturnType::INT_TYPE){
                AS_operand* ret = AS_Operand_Temp(Temp_newtemp_int());
                emit_irs.emplace_back(L_Call(fn, ret, aov));
                return ret;
            }else{
                AS_operand* ret = AS_Operand_Temp(Temp_newtemp_struct_ptr(0, item->second.structname));
                emit_irs.emplace_back(L_Call(fn, ret, aov));
                return ret;
            }

        }
        case A_exprUnitType::A_idExprKind:
        {
            string id = *e->u.id;
            AS_operand* ids = getIdPtr(id);
            return getIntOrPtr(ids);

        }
        case A_exprUnitType::A_numExprKind:
            return AS_Operand_Const(e->u.num);
    }
    return nullptr;
    
}

LLVMIR::L_func* ast2llvmFuncBlock(Func_local *f)
{
    std::list<L_stm*> irs = f->irs;
    std::list<L_block*> blocks;
    std::list<L_stm*> instrs;
    for(L_stm* ir : irs){
        if(ir->type == L_StmKind::T_LABEL){
            // std::cout <<"                "<<"=============="<<std::endl;
            if(!instrs.empty()) blocks.push_back(L_Block(instrs));
            instrs.clear();
        }
        // std::cout <<"                "<< stmKind2String(ir->type) <<std::endl;
        instrs.push_back(ir);
    }
    if(!instrs.empty()) blocks.push_back(L_Block(instrs));

    return new L_func(f->name, f->ret, f->args, blocks);
}

void ast2llvm_moveAlloca(LLVMIR::L_func *f)
{
    std::unordered_set<AS_operand*> set;
    std::list<L_block*> blks = f->blocks;
    for(auto b: blks){
        if(b == blks.front()) continue;
        list<L_stm*> cache;

        for(auto inst : b->instrs){
            if(inst->type ==  L_StmKind::T_ALLOCA){
                set.insert(inst->u.ALLOCA->dst);
                cache.push_back(inst);
            }
        }
        for(auto c : cache){
            b->instrs.remove(c);
        }
    }
    list<L_stm*>& ff = blks.front()->instrs;
    if(!ff.empty()){
        L_stm* lb = ff.front();
        ff.pop_front();
        for(AS_operand* s: set){
            ff.push_front(L_Alloca(s));
        }
        ff.push_front(lb);
    }
}
#include "TypeCheck.h"
#include <string.h>
#include <set>
// // maps to store the type information. Feel free to design new data structures if you need.
// struct varInfo{
//     bool is_Array;
//     union{
//         aA_varDeclArray array;
//         aA_varDeclScalar scalar;
//     }u;
// };

// struct funInfo{
//     A_pos pos;
//     vector<aA_varDecl>* params;
//     aA_varDeclScalar retInfo;
// };

// typedef std::unordered_map<string, varInfo> tokenMap;
// typedef std:: unordered_map<string, funInfo> funMap;
// tokenMap globalToken;
// funMap funInfoMap;

typeMap g_token2Type;     // global token ids to type // 2
paramMap func2Param;      // 2
memberMap struct2Members; // 1

string *curFunc = NULL;
bool isDecl = false;

typeMap block_token2Type;

// private util functions. You can use these functions to help you debug.
void error_print(std::ostream *out, A_pos p, string info)
{
    *out << "Typecheck error in line " << p->line << ", col " << p->col << ": " << info << std::endl;
    exit(0);
}

void print_token_map(typeMap *map)
{
    for (auto it = map->begin(); it != map->end(); it++)
    {
        std::cout << it->first << " : ";
        switch (it->second->type)
        {
        case A_dataType::A_nativeTypeKind:
            switch (it->second->u.nativeType)
            {
            case A_nativeType::A_intTypeKind:
                std::cout << "int";
                break;
            default:
                break;
            }
            break;
        case A_dataType::A_structTypeKind:
            std::cout << *(it->second->u.structType);
            break;
        default:
            break;
        }
        std::cout << std::endl;
    }
}

// public functions
// This is the entrace of this file.
void check_Prog(std::ostream *out, aA_program p)
{
    // p is the root of AST tree.
    /*
    Write your code here.

    Hint:
    1. Design the order of checking the program elements to meet the requirements that funtion declaration and global variable declaration can be used anywhere in the program.

    2. Many types of statements indeed collapse to some same units, so a good abstract design will help you reduce the amount of your code.
    */
    for (auto ele : p->programElements)
    {
        switch (ele->kind)
        {
        case A_programStructDefKind: // 结构定义
            check_StructDef(out, ele->u.structDef);
            break;
        default:
            break;
        }
    }

    for (auto ele : p->programElements)
    {
        switch (ele->kind)
        {
        case A_programVarDeclStmtKind: // 全局变量声明
            check_VarDecl(out, ele->u.varDeclStmt);
            break;
        case A_programFnDeclStmtKind: // 函数声明
            check_FnDeclStmt(out, ele->u.fnDeclStmt);
            break;
        case A_programFnDefKind: // 函数定义
            check_FnDecl(out, ele->u.fnDef->fnDecl);
            break;
        default:
            break;
        }
    }

    for (auto ele : p->programElements)
    {
        switch (ele->kind)
        {
        case A_programFnDefKind: // 函数定义
            check_FnDef(out, ele->u.fnDef);
            break;
        default:
            break;
        }
    }

    (*out) << "Typecheck passed!" << std::endl;
    return;
}

void check_VarDecl(std::ostream *out, aA_varDeclStmt vd)
{
    // variable declaration statement
    if (!vd)
        return;
    string *id;
    aA_type type;
    int len = 0;
    if (vd->kind == A_varDeclStmtType::A_varDeclKind)
    {
        // if declaration only
        // Example:
        //   let a:int;
        //   let a[5]:int;
        // todo
        aA_varDecl varDecl = vd->u.varDecl;
        switch (varDecl->kind)
        {
        case A_varDeclType::A_varDeclScalarKind:
            id = varDecl->u.declScalar->id;
            type = varDecl->u.declScalar->type;
            len = 0;
            break;
        case A_varDeclType::A_varDeclArrayKind:
            id = varDecl->u.declArray->id;
            type = varDecl->u.declArray->type;
            len = varDecl->u.declArray->len;
            break;
        default:
            break;
        }
    }
    else if (vd->kind == A_varDeclStmtType::A_varDefKind)
    {
        // if both declaration and initialization
        // Example:
        //   let a:int = 5;
        // todo
        aA_varDef varDef = vd->u.varDef;
        switch (varDef->kind)
        {
        case A_varDefType::A_varDefScalarKind:
            id = varDef->u.defScalar->id;
            type = varDef->u.defScalar->type;
            len = 0;
            break;
        case A_varDefType::A_varDefArrayKind:
            id = varDef->u.defArray->id;
            type = varDef->u.defArray->type;
            len = varDef->u.defArray->len;
            break;
        default:
            break;
        }
    }

    if (curFunc == NULL)
    {
        if (g_token2Type.find(*id) != g_token2Type.end())
        {
            error_print(out, vd->pos, "Duplicate declaration of global variable " + *id + ".");
        }
        else
            g_token2Type.emplace(*id, new t_type(type, len));
    }else {
        if(block_token2Type.find(*id) != block_token2Type.end()){
            error_print(out, vd->pos, "local variables dplicates with function params.");
        }else if(g_token2Type.find(*id) != g_token2Type.end()){
            error_print(out, vd->pos, "local variables dplicates with global variable.");
        }else {
            block_token2Type.emplace(*id, new t_type(type, len));
        }
    }

    return;
}

void check_StructDef(std::ostream *out, aA_structDef sd)
{
    if (!sd)
        return;
    // structure definition
    // Example:
    //      struct A{
    //          a:int;
    //          b:int;
    //      }
    // todo
    string id = (char *)sd->id;
    bool is_return = false;

    if (struct2Members.find(id) != struct2Members.end())
    {
        error_print(out, sd->pos, "Duplicate definition of struct " + id + ".");
        is_return = true;
    }
    vector<aA_varDecl> &vec = sd->varDecls;
    std::set<string> namePool;
    for (auto iter = vec.begin(); iter != vec.end(); iter++)
    {
        string *name = NULL;
        aA_type type;
        A_pos pos;
        switch ((*iter)->kind)
        {
        case A_varDeclType::A_varDeclScalarKind:
            name = (*iter)->u.declScalar->id;
            type = (*iter)->u.declScalar->type;
            pos = (*iter)->u.declScalar->pos;
            break;
        case A_varDeclType::A_varDeclArrayKind:
            name = (*iter)->u.declArray->id;
            type = (*iter)->u.declArray->type;
            pos = (*iter)->u.declArray->pos;
            break;
        default:
            break;
        }
        if (namePool.find(*name) != namePool.end())
        {
            error_print(out, pos, "Duplicate definition of member " + id + " in struct " + id + ".");
            is_return = true;
        }
        else
        {
            namePool.emplace(*name);
        }

        if (type->type == A_dataType::A_structTypeKind)
        {
            string structId = (char *)type->u.structType;
            if (struct2Members.find(structId) == struct2Members.end())
            {
                error_print(out, pos, "Member type " + structId + " in " + id + " not defined.");
                is_return = true;
            }
        }
    }

    if (is_return)
        return;

    struct2Members.emplace(id, &vec);
}


void check_FnDecl(std::ostream *out, aA_fnDecl fd)
{
    // Example:
    //      fn main(a:int, b:int)->int
    if (!fd)
        return;
    // todo
    /*
       write your code here
       Hint: you may need to check if the function is already eclared
    */
    auto it = func2Param.find(*(fd->id));
    if (it != func2Param.end()){
        bool isDef = (*it).second.isDef;
        if (isDef && !isDecl)
            error_print(out, fd->pos, "Duplicate definition of function " + *(fd->id) + ".");
        else if (!isDef && isDecl)
            error_print(out, fd->pos, "Duplicate declaration of function " + *(fd->id) + ".");
        else if (!isDef && !isDecl)
        { // 先声明后定义
            string t1 = get_TypeString((*it).second.type);
            string t2 = get_TypeString(fd->type);
            int len1 = (*it).second.params->size();
            int len2 = fd->paramDecl->varDecls.size();
            bool unmatch = false;

            if (len2 == 0 && t1 == t2) (*it).second.isDef = true;
            else if (t1 != t2 || len1 != len2) unmatch = true;
            else {
                for(int i = 0; i < len1; i++){
                    auto v1 = (*it).second.params->at(i);
                    auto v2 = fd->paramDecl->varDecls[i];
                    if(v1->kind != v2->kind){unmatch = true; break;}
                    switch(v1->kind){
                        case A_varDeclType::A_varDeclArrayKind:
                            t1 = get_TypeString(v1->u.declArray->type);
                            t2 = get_TypeString(v2->u.declArray->type);
                            break;
                        case A_varDeclType::A_varDeclScalarKind:
                            t1 = get_TypeString(v1->u.declScalar->type);
                            t2 = get_TypeString(v2->u.declScalar->type);
                            break;
                    }
                    if(t1 != t2){ unmatch = true; break;}
                }
            }

            if (unmatch) {
                error_print(out, fd->pos, "function (" + *(fd->id) + ") definition on line " + std::to_string(fd->pos->line) + " doesn't match the declaration on line " + std::to_string((*it).second.pos->line) + ".");
            }
        }
    } else{
        func2Param.emplace(*(fd->id), new fun_type(fd->pos, &fd->paramDecl->varDecls, fd->type, !isDecl));
    }
}

void check_FnDeclStmt(std::ostream *out, aA_fnDeclStmt fd)
{
    // Example:
    //      fn main(a:int, b:int)->int;
    if (!fd)
        return;
    isDecl = true;
    check_FnDecl(out, fd->fnDecl);
    isDecl = false;
    return;
}

void check_FnDef(std::ostream *out, aA_fnDef fd)
{
    // Example:
    //      fn main(a:int, b:int)->int{
    //          let c:int;
    //          c = a + b;
    //          return c;
    //      }
    if (!fd)
        return;
    // check_FnDecl(out, fd->fnDecl);
    // todo    write your code here
    /*
        Hint: you may pay attention to the function parameters, local variables and global variables.
    */
    curFunc = fd->fnDecl->id;
    fun_type ft = func2Param.find(*curFunc)->second;
    for(auto token : *ft.params){
        string* id;
        aA_type type;
        int len = 0;
        switch(token->kind){
            case A_varDeclType::A_varDeclScalarKind:
                id = token->u.declScalar->id;
                type = token->u.declScalar->type;
                break;
            case A_varDeclType::A_varDeclArrayKind:
                id = token->u.declArray->id;
                type = token->u.declArray->type;
                len = token->u.declArray->len;
                break;
        }
        block_token2Type.emplace(*id, new t_type(type, len));
    }
    for(auto cs : fd->stmts){
        check_CodeblockStmt(out, cs);
    }
    curFunc = NULL;
    block_token2Type.clear();
    return;
}

void check_CodeblockStmt(std::ostream *out, aA_codeBlockStmt cs)
{
    if (!cs)
        return;
    switch (cs->kind)
    {
    case A_codeBlockStmtType::A_varDeclStmtKind:
        check_VarDecl(out, cs->u.varDeclStmt);
        break;
    case A_codeBlockStmtType::A_assignStmtKind:
        check_AssignStmt(out, cs->u.assignStmt);
        break;
    case A_codeBlockStmtType::A_ifStmtKind:
        check_IfStmt(out, cs->u.ifStmt);
        break;
    case A_codeBlockStmtType::A_whileStmtKind:
        check_WhileStmt(out, cs->u.whileStmt);
        break;
    case A_codeBlockStmtType::A_callStmtKind:
        check_CallStmt(out, cs->u.callStmt);
        break;
    case A_codeBlockStmtType::A_returnStmtKind:
        check_ReturnStmt(out, cs->u.returnStmt);
        break;
    default:
        break;
    }
    return;
}

t_type* getTtype(string id){
    auto it = block_token2Type.find(id);
    if(it != block_token2Type.end()){
        return &it->second;
    }
    it = g_token2Type.find(id);
    if(it != g_token2Type.end()){
        return &it->second;
    }
    return NULL;
}

void check_AssignStmt(std::ostream *out, aA_assignStmt as)
{
    if (!as)
        return;
    string name;
    aA_type type;
    switch (as->leftVal->kind)
    {
        case A_leftValType::A_varValKind:
        {
            // todo
            t_type* t = getTtype(*(as->leftVal->u.id));
            type = t->type;
        }
        break;
        case A_leftValType::A_arrValKind:
        {
            // todo
            t_type* t = getTtype(*(as->leftVal->u.arrExpr->arr));
            type = t->type;       
            check_ArrayExpr(out, as->leftVal->u.arrExpr);
        }
        break;
        case A_leftValType::A_memberValKind:
        {
            // todo
            type = check_MemberExpr(out, as->leftVal->u.memberExpr);
        }
        break;
    }

    aA_type type_r = check_ExprUnit(out, as);
    return;
}

void check_ArrayExpr(std::ostream *out, aA_arrayExpr ae)
{
    if (!ae)
        return;
    /*
        Example:
            a[1] = 0;
        Hint:
            check the validity of the array index
    */
    t_type* t = getTtype(*(ae->arr));

    if(ae->idx->kind == A_indexExprKind::A_numIndexKind){
        int idx = ae->idx->u.num;
        if(t->len > idx || idx < 0){
            error_print(out, ae->pos, "array out of index.");
            return;
        }
    } else if(ae->idx->kind == A_indexExprKind::A_idIndexKind){
        t_type* idx_type = getTtype(*(ae->idx->u.id));
        if(idx_type->len > 0){
            error_print(out, ae->pos, "Cannot use an array variable as an array index.");
        }else if(idx_type->type->type == A_dataType::A_structTypeKind){
            error_print(out, ae->pos, "Cannot use an struct variable as an array index.");      
        } else if(idx_type->type->u.nativeType != A_nativeType::A_intTypeKind){
            error_print(out, ae->pos, "Array index must be of type int.");      
        }
    }
}

aA_type check_MemberExpr(std::ostream *out, aA_memberExpr me)
{
    // check if the member exists and return the tyep of the member
    // you may need to check if the type of this expression matches with its
    // leftvalue or rightvalue, so return its aA_type would be a good way. Feel
    // free to change the design pattern if you need.
    if (!me)
        return nullptr;
    /*
        Example:
            a.b
    */
    return nullptr;
}

void check_IfStmt(std::ostream *out, aA_ifStmt is)
{
    if (!is)
        return;
    check_BoolExpr(out, is->boolExpr);
    for (aA_codeBlockStmt s : is->ifStmts)
    {
        check_CodeblockStmt(out, s);
    }
    for (aA_codeBlockStmt s : is->elseStmts)
    {
        check_CodeblockStmt(out, s);
    }
    return;
}

void check_BoolExpr(std::ostream *out, aA_boolExpr be)
{
    if (!be)
        return;
    switch (be->kind)
    {
    case A_boolExprType::A_boolBiOpExprKind:
        // todo
        check_BoolExpr(out, be->u.boolBiOpExpr->left);
        check_BoolExpr(out, be->u.boolBiOpExpr->right);
        break;
    case A_boolExprType::A_boolUnitKind:
        check_BoolUnit(out, be->u.boolUnit);
        break;
    default:
        break;
    }
    return;
}

string get_TypeString(aA_type t)
{

    switch (t->type)
    {
    case A_dataType::A_nativeTypeKind:
        switch (t->u.nativeType)
        {
        case A_intTypeKind:
            return "int";

        default:
            break;
        }
        break;
    case A_dataType::A_structTypeKind:
        return (char *)t->u.structType;
    default:
        break;
    }
    return NULL;
}

void check_BoolUnit(std::ostream *out, aA_boolUnit bu)
{
    if (!bu)
        return;
    switch (bu->kind)
    {
    case A_boolUnitType::A_comOpExprKind:
    {
        /* write your code here */
        aA_type t1 = check_ExprUnit(out, bu->u.comExpr->left);
        aA_type t2 = check_ExprUnit(out, bu->u.comExpr->right);
        string t1_type = get_TypeString(t1);
        string t2_type = get_TypeString(t2);

        if (t1_type != t2_type)
        {
            error_print(out, bu->pos, t1_type + " is not comparable with " + t2_type + ".");
        }
        break;
    }
    case A_boolUnitType::A_boolExprKind:
        /* write your code here */
        check_BoolExpr(out, bu->u.boolExpr);
        break;
    case A_boolUnitType::A_boolUOpExprKind:
        /* write your code here */
        check_BoolUnit(out, bu->u.boolUOpExpr->cond);
        break;
    default:
        break;
    }
    return;
}

aA_type check_ExprUnit(std::ostream *out, aA_exprUnit eu)
{
    // validate the expression unit and return the aA_type of it
    // you may need to check if the type of this expression matches with its
    // leftvalue or rightvalue, so return its aA_type would be a good way.
    // Feel free to change the design pattern if you need.
    if (!eu)
        return nullptr;
    aA_type ret;
    switch (eu->kind)
    {
    case A_exprUnitType::A_idExprKind:
    {
        /* write your code here */
    }
    break;
    case A_exprUnitType::A_numExprKind:
    {
        /* write your code here */
    }
    break;
    case A_exprUnitType::A_fnCallKind:
    {
        /* write your code here */
    }
    break;
    case A_exprUnitType::A_arrayExprKind:
    {
        /* write your code here */
    }
    break;
    case A_exprUnitType::A_memberExprKind:
    {
        /* write your code here */
    }
    break;
    case A_exprUnitType::A_arithExprKind:
    {
        /* write your code here */
    }
    break;
    case A_exprUnitType::A_arithUExprKind:
    {
        /* write your code here */
    }
    break;
    }
    return ret;
}

void check_FuncCall(std::ostream *out, aA_fnCall fc)
{
    if (!fc)
        return;
    // Example:
    //      foo(1, 2);

    /* write your code here */
    return;
}

void check_WhileStmt(std::ostream *out, aA_whileStmt ws)
{
    if (!ws)
        return;
    check_BoolExpr(out, ws->boolExpr);
    for (aA_codeBlockStmt s : ws->whileStmts)
    {
        check_CodeblockStmt(out, s);
    }
    return;
}

void check_CallStmt(std::ostream *out, aA_callStmt cs)
{
    if (!cs)
        return;
    check_FuncCall(out, cs->fnCall);
    return;
}

void check_ReturnStmt(std::ostream *out, aA_returnStmt rs)
{
    if (!rs)
        return;
    return;
}

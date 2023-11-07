#include "TypeCheck.h"
#include <string.h>
#include <set>
// maps to store the type information. Feel free to design new data structures if you need.

typeMap g_token2Type;     
paramMap func2Param;      
memberMap struct2Members; 
string *curFunc = NULL;
bool isDecl = false;
vector<string>* blockVar = nullptr;
typeMap block_token2Type;
aA_type_ NUM_ATYPE;

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
        switch (it->second.type->type)
        {
        case A_dataType::A_nativeTypeKind:
            switch (it->second.type->u.nativeType)
            {
            case A_nativeType::A_intTypeKind:
                std::cout << "int";
                break;
            default:
                break;
            }
            break;
        case A_dataType::A_structTypeKind:
            std::cout << *(it->second.type->u.structType);
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
    NUM_ATYPE.type = A_dataType::A_nativeTypeKind;
    NUM_ATYPE.u.nativeType = A_nativeType::A_intTypeKind;
    for (auto ele : p->programElements)
    {
        switch (ele->kind)
        {
        case A_programStructDefKind: // 结构定义
            check_StructDef(out, ele->u.structDef);
            break;
        case A_programVarDeclStmtKind: // 全局变量声明
            check_VarDecl(out, ele->u.varDeclStmt);
            break;
        case A_programFnDeclStmtKind: // 函数声明
            check_FnDeclStmt(out, ele->u.fnDeclStmt);
            break;
        case A_programFnDefKind: // 函数定义的声明
            check_FnDecl(out, ele->u.fnDef->fnDecl);
            break;
        default:
            break;
        }
    }

    for(auto fn: func2Param){
        if(!fn.second.isDef){
            error_print(out, fn.second.pos, "Function '" + fn.first + "' declared but not defined.");
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


t_type varDecl2Ttype(std::ostream *out, string*& id, aA_varDeclStmt vd){
    t_type t;
    if (vd->kind == A_varDeclStmtType::A_varDeclKind)
    {
        // if declaration only
        // Example:
        //   let a:int;
        //   let a[5]:int;
        aA_varDecl varDecl = vd->u.varDecl;
        switch (varDecl->kind)
        {
        case A_varDeclType::A_varDeclScalarKind:
            id = varDecl->u.declScalar->id;
            t.type = varDecl->u.declScalar->type;
            t.len = 0;
            break;
        case A_varDeclType::A_varDeclArrayKind:
            id = varDecl->u.declArray->id;
            t.type = varDecl->u.declArray->type;
            t.len = varDecl->u.declArray->len;
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
        aA_varDef varDef = vd->u.varDef;
        switch (varDef->kind)
        {
        case A_varDefType::A_varDefScalarKind:
            id = varDef->u.defScalar->id;
            t.type = varDef->u.defScalar->type;
            t.len = 0;
            check_rightVal(out, t, varDef->u.defScalar->val, false);
            break;
        case A_varDefType::A_varDefArrayKind:
            id = varDef->u.defArray->id;
            t.type = varDef->u.defArray->type;
            t.len = varDef->u.defArray->len;
            for(auto v: varDef->u.defArray->vals){
                check_rightVal(out, t, v, false);
            }
            break;
        default:
            break;
        }
    }
    return t;
}

void check_VarDecl(std::ostream *out, aA_varDeclStmt vd)
{
    // variable declaration statement
    if (!vd)
        return;
    string *id;
    t_type t;
    t = varDecl2Ttype(out, id, vd);
    if(t.type->type == A_dataType::A_structTypeKind){
        if(struct2Members.find(*(t.type->u.structType))==struct2Members.end()){
            error_print(out, vd->pos, "Variable type '" + *(t.type->u.structType) + "' not defined.");
            return;
        }
    }

    if (curFunc == NULL)
    {
        if (g_token2Type.find(*id) != g_token2Type.end())
        {
            error_print(out, vd->pos, "Duplicate declaration of global variable '" + *id + "'.");
        }
        else
            g_token2Type.emplace(*id, t);
    }else {
        if(block_token2Type.find(*id) != block_token2Type.end()){
            error_print(out, vd->pos, "Local variables '" + *id + "' conflicts with function params.");
        }else if(g_token2Type.find(*id) != g_token2Type.end()){
            error_print(out, vd->pos, "Local variables '" + *id + "' conflicts with global variable.");
        }else if(func2Param.find(*id) != func2Param.end()){
            error_print(out, vd->pos, "Local variables '" + *id + "' conflicts with function name.");
        } else {
            block_token2Type.emplace(*id, t);
            if(blockVar!=nullptr){
                blockVar->emplace_back(*id);
            }
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
    string id = *(sd->id);
    bool is_return = false;

    if (struct2Members.find(id) != struct2Members.end())
    {
        error_print(out, sd->pos, "Duplicate definition of struct '" + id + "'.");
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
            error_print(out, pos, "Duplicate definition of member '" + id + "' in struct '" + id + "'.");
            is_return = true;
        }
        else
        {
            namePool.emplace(*name);
        }

        if (type->type == A_dataType::A_structTypeKind)
        {
            string structId = *type->u.structType;
            if (struct2Members.find(structId) == struct2Members.end())
            {
                error_print(out, pos, "Member type '" + structId + "' in '" + id + "' not defined.");
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
        if (isDef && !isDecl) // 重复定义
            error_print(out, fd->pos, "Duplicate definition of function '" + *(fd->id) + "'.");
        else if (!isDef && isDecl) // 重复声明
            error_print(out, fd->pos, "Duplicate declaration of function '" + *(fd->id) + "'.");
        else if (!isDef && !isDecl)
        { // 先声明后定义
            string t1 = get_TypeString((*it).second.type);
            string t2 = get_TypeString(fd->type);
            int len1 = (*it).second.params->size();
            int len2 = fd->paramDecl->varDecls.size();
            bool unmatch = false;

            if (t1 != t2 || len1 != len2) unmatch = true;
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
                error_print(out, fd->pos, "Function '" + *(fd->id) + "' definition on line " + std::to_string(fd->pos->line) + " doesn't match the declaration on line " + std::to_string((*it).second.pos->line) + ".");
            } else{
                (*it).second.isDef = true;
            }
        }else{//先定义，后声明
            error_print(out, fd->pos, "Function '" + *(fd->id) + "' declaration on line " + std::to_string(fd->pos->line) + " already defined on line " + std::to_string((*it).second.pos->line) + ".");
        }
    } else{
        func2Param.emplace(*(fd->id), fun_type(fd->pos, &fd->paramDecl->varDecls, fd->type, !isDecl));
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
        block_token2Type.emplace(*id, t_type(type, len));
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
    return nullptr;
}

void check_rightVal(std::ostream *out, t_type leftVal, aA_rightVal rv, bool fnCall, bool isRet){
    string t1, t2;
    string str = fnCall ? "formal parameter" : "left value";
    str = isRet ? "return statement" : str;
    if(leftVal.len  < 0) return;
    t_type rightType;
    switch (rv->kind)
    {
    case A_rightValType::A_arithExprValKind:
        rightType = check_ArithExpr(out, rv->u.arithExpr);
        if(rightType.len < 0) break;
        t1 = get_TypeString(leftVal.type);
        t2 = get_TypeString(rightType.type);
        if(t1 != t2 || leftVal.len!=rightType.len){
            if(leftVal.len > 0) t1+="["+std::to_string(leftVal.len)+"]";
            if(rightType.len > 0) t2+="["+std::to_string(rightType.len)+"]";
            error_print(out, rv->pos, "You cannot assign a right value of type '" + t2 + "' to a " + str + " of type '"+ t1 +"'.");
        }
        break;
    case A_rightValType::A_boolExprValKind:
        check_BoolExpr(out, rv->u.boolExpr);
        t1 = get_TypeString(leftVal.type);
        if(t1 != "int" && t1 != "bool" || leftVal.len > 0){
            if(leftVal.len > 0) t1+="["+std::to_string(leftVal.len)+"]";
            error_print(out, rv->pos, "You cannot assign a right value of type 'bool' to a " + str + " of type '"+ t1 +"'.");
        }else{
            error_print(out, rv->pos, "Warning: Boolean type as right value may not be legal.");
        }
        break;
    default:
        break;
    }
}

void check_AssignStmt(std::ostream *out, aA_assignStmt as)
{
    if (!as)
        return;
    string name;
    t_type type;
    switch (as->leftVal->kind)
    {
        case A_leftValType::A_varValKind:
        {
            string* id = as->leftVal->u.id;
            t_type* t = getTtype(*id);
            if(t == nullptr) {
                if(func2Param.find(*id) != func2Param.end())
                    error_print(out, as->pos, "Cannot assign a value to function '" + *id +"'.");
                else
                    error_print(out, as->pos, "Var '" + *id +"' is not defined.");
                return;
            }else if(t->len>0){
                error_print(out, as->pos, "Cannot assign a value to array '" + *id +"'.");
                return;
            }
            type = *t;
        }
        break;
        case A_leftValType::A_arrValKind:
        {
            string* id = as->leftVal->u.arrExpr->arr;
            t_type* t = getTtype(*id);
            if(t == nullptr) {
                if(func2Param.find(*id) != func2Param.end())
                    error_print(out, as->pos, "Cannot assign a value to function '" + *id +"'.");
                else
                    error_print(out, as->pos, "Var '" + *id +"' is not defined.");
                return;
            }
            type = *t;
            type.len = 0;
            check_ArrayExpr(out, as->leftVal->u.arrExpr);
        }
        break;
        case A_leftValType::A_memberValKind:
        {
            type.len = 0;
            type.type = check_MemberExpr(out, as->leftVal->u.memberExpr);
            if(type.type == nullptr) type.len = -1;
        }
        break;
    }

    check_rightVal(out, type, as->rightVal, false);
    return;
}

t_type check_ArithExpr(std::ostream* out, aA_arithExpr ae){
    t_type ret;
    if(!ae) {
        ret.len = -1;
        return ret;
    }
    string t1,t2;
    aA_arithExpr left, right;
    t_type type1, type2;
    switch (ae->kind)
    {
    case A_arithExprType::A_arithBiOpExprKind:
        left = ae->u.arithBiOpExpr->left;
        right = ae->u.arithBiOpExpr->right;
        type1 = check_ArithExpr(out, left);
        type2 = check_ArithExpr(out, right);
        if(type1.len < 0 || type2.len < 0){
            ret.len = -1;
        }else{
            t1 = get_TypeString(type1.type);
            t2 = get_TypeString(type2.type);
            if(t1 != t2 || type1.len > 0 || type2.len > 0 || t1 != "int"){
                if(type1.len > 0) t1 += "[]";
                if(type2.len > 0) t2 += "[]";
                error_print(out, left->pos, "Cannot operate between '" + t1 + "' and '" + t2 + "'.");
                ret.len = -1;
            }else if(type1.type->type == A_dataType::A_structTypeKind){
                error_print(out, left->pos, "Operations between structures are not supported.");
                ret.len = -1;
            }
            ret = type1;
        }
        break;
    case A_arithExprType::A_exprUnitKind:
        ret = check_ExprUnit(out, ae->u.exprUnit);
        break;
    }
    return ret;
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
        if(idx_type == nullptr){
            error_print(out, ae->pos, "Cannot use an undefined variable as an array index.");
        } else if(idx_type->len > 0){
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
    string* structId = me->structId;
    string* memberId = me->memberId;
    t_type* t = getTtype(*structId);
    if(t->type->type != A_dataType::A_structTypeKind){
        error_print(out, me->pos, "'" + *structId + "' is not a struct.");
        return nullptr;
    }else{
        string* structType = t->type->u.structType;
        auto vec = struct2Members[*structType];

        string* id;
        for(auto v : *vec){

            switch (v->kind)
            {
            case A_varDeclType::A_varDeclArrayKind:
                id = v->u.declArray->id;
                if(*id == *memberId){
                    return v->u.declArray->type;
                }
                break;
            case A_varDeclType::A_varDeclScalarKind:
                id = v->u.declScalar->id;
                if(*id == *memberId){
                    return v->u.declScalar->type;
                }
                break;
            }
        }
        error_print(out, me->pos,"Struct '" + *structType +"' doesn't have the member '"+ *memberId +"'.");
    }
    return nullptr;
}

void check_IfStmt(std::ostream *out, aA_ifStmt is)
{
    if (!is)
        return;
    check_BoolExpr(out, is->boolExpr);
    
    vector<string> varVec;
    blockVar = &varVec;
    for (aA_codeBlockStmt s : is->ifStmts)
    {
        check_CodeblockStmt(out, s);
    }
    
    for(auto var : varVec){
        block_token2Type.erase(var);
    }
    varVec.clear();
    for (aA_codeBlockStmt s : is->elseStmts)
    {
        check_CodeblockStmt(out, s);
    }
    blockVar = nullptr;
    
    for(auto var : varVec){
        block_token2Type.erase(var);
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
        return *t->u.structType;
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
        t_type t1 = check_ExprUnit(out, bu->u.comExpr->left);
        t_type t2 = check_ExprUnit(out, bu->u.comExpr->right);
        if(t1.len < 0 || t2.len < 0) break;
        string t1_type = get_TypeString(t1.type);
        string t2_type = get_TypeString(t2.type);

        if (t1_type != t2_type || t1.len > 0 || t2.len > 0)
        {
            if(t1.len > 0) t1_type += "[]";
            if(t2.len > 0) t2_type += "[]";
            error_print(out, bu->pos, "'" + t1_type + "' is not comparable with '" + t2_type + "'.");
        } else if(t1.type->type == A_dataType::A_structTypeKind){
            error_print(out, bu->pos,"Comparison between structures is not supported.");
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

t_type check_ExprUnit(std::ostream *out, aA_exprUnit eu)
{
    // validate the expression unit and return the aA_type of it
    // you may need to check if the type of this expression matches with its
    // leftvalue or rightvalue, so return its aA_type would be a good way.
    // Feel free to change the design pattern if you need.
    t_type ret;
    ret.len = -1;
    if (!eu){
        return ret;
    }
    switch (eu->kind)
    {
    case A_exprUnitType::A_idExprKind:
    {
        /* write your code here */
        string* id = eu->u.id;
        t_type* t = getTtype(*id);
        if(t == nullptr){
            error_print(out, eu->pos, "Variable "+ *id + " not defined.");
        // }else if(t->len > 0){
        //     error_print(out, eu->pos, "Variable " + *id + " is an array, cannot participate in operation.");
        //     ret = nullptr;
        // }else if(t->type->type == A_dataType::A_structTypeKind){
        //     error_print(out, eu->pos, "Variable " + *id + " is a struct, cannot participate in operation.");
        //     ret = nullptr;
        }else{
            ret = *t;
        }

    }
    break;
    case A_exprUnitType::A_numExprKind:
    {
        /* write your code here */
        t_type NUM_TYPE;
        ret.len = 0;
        ret.type = &NUM_ATYPE;
    }
    break;
    case A_exprUnitType::A_fnCallKind:
    {
        /* write your code here */
        string* id = eu->u.callExpr->fn;
        auto ft_ = func2Param.find(*id);
        if(ft_ == func2Param.end() || !ft_->second.isDef){
            error_print(out, eu->pos, "The function '" + *id + "' called is not defined");
        }else{
            check_FuncCall(out, eu->u.callExpr);
            ret.type = ft_->second.type;
            ret.len = 0;
        }

    }
    break;
    case A_exprUnitType::A_arrayExprKind:
    {
        /* write your code here */
        string* id = eu->u.arrayExpr->arr;
        auto t = getTtype(*id);
        if(t == nullptr){
            error_print(out, eu->pos, "Array '" + *id + "' undefined.");
        }else if(t->len == 0){
            error_print(out, eu->pos, "Variable '" + *id + "' is not an array.");
        } else{
            check_ArrayExpr(out, eu->u.arrayExpr);
            ret = *t;
            ret.len = 0;
        }
    }
    break;
    case A_exprUnitType::A_memberExprKind:
    {
        // todo
        ret.type = check_MemberExpr(out, eu->u.memberExpr);
        if(ret.type == nullptr) ret.len = -1;
        else ret.len = 0;
    }
    break;
    case A_exprUnitType::A_arithExprKind:
    {
        ret = check_ArithExpr(out, eu->u.arithExpr);
    }
    break;
    case A_exprUnitType::A_arithUExprKind:
    {
        /* write your code here */
        t_type type = check_ExprUnit(out, eu->u.arithUExpr->expr);
        ret = type;
        if(type.len > 0 && eu->u.arithUExpr->op == A_arithUOp::A_neg){
            error_print(out, eu->pos, "Array type cannot take negative value.");
            ret.len = -1;
        }else if(type.len == 0 && type.type->type == A_dataType::A_structTypeKind && eu->u.arithUExpr->op == A_arithUOp::A_neg){
            error_print(out, eu->pos, "Struct type cannot take negative value.");
            ret.len = -1;
        }
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
    // todo
    string* id = fc->fn;
    auto ft_ = func2Param.find(*id);
    int len = ft_->second.params->size();
    int curlen = fc->vals.size();


    if(len != curlen){
        error_print(out, fc->pos, "Function '" + *id + "' has " + std::to_string(len) + " parameters, but function call give " + std::to_string(curlen) +" parameters.");
    }else {

        for(int i = 0; i < len; i++){
            aA_varDecl para = ft_->second.params->at(i);
            aA_varDeclStmt_ vds;
            vds.kind = A_varDeclStmtType::A_varDeclKind;
            vds.u.varDecl = para;
            string* id = nullptr;
            t_type type1 = varDecl2Ttype(out, id, &vds);
            aA_rightVal value = fc->vals.at(i);

            check_rightVal(out, type1, value, true);
        }
    }

    return;
}

void check_WhileStmt(std::ostream *out, aA_whileStmt ws)
{
    if (!ws)
        return;
    check_BoolExpr(out, ws->boolExpr);
    
    vector<string> varVec;
    blockVar = &varVec;
    for (aA_codeBlockStmt s : ws->whileStmts)
    {
        check_CodeblockStmt(out, s);
    }
    blockVar = nullptr;
    
    for(auto var : varVec){
        block_token2Type.erase(var);
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
    if(curFunc == nullptr){
        error_print(out, rs->pos, "Return must be used in the function");
    }
    auto f = func2Param.find(*curFunc)->second;
    t_type t;
    t.len = 0;
    t.type = f.type;
    check_rightVal(out, t, rs->retVal, false, true);
    return;
}

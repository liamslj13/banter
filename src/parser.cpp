#include "h/parser.h"
#include "h/lex.h"
#include <stdexcept>

std::unordered_map<TokenType, Precedence> precedences({
    {TokenType::EQ, EQUALS},
    {TokenType::NEQ, EQUALS},
    {TokenType::LT, LESSGREATER},
    {TokenType::GT, LESSGREATER},
    {TokenType::LTE, LESSGREATER},
    {TokenType::GTE, LESSGREATER},
    {TokenType::ADD, SUM},
    {TokenType::SUB, SUM},
    {TokenType::DIV, PRODUCT},
    {TokenType::MUL, PRODUCT},
    {TokenType::MOD, PRODUCT},
    {TokenType::LPAREN, CALL},
    {TokenType::LBRACKET, INDEX},
});

void parser::nextToken() {
    curTok = peekTok;
    peekTok = l.nextToken();
}

bool parser::expectPeek(const TokenType &tt) {
    if (peekTok.type == tt) {
        nextToken();
        return true;
    }
    peekError(tt);
    return false;
}

Precedence parser::peekPrecedence() const {
    if (precedences.find(peekTok.type) != precedences.end()) {
        return precedences[peekTok.type];
    }
    return LOWEST;
}

Precedence parser::curPrecedence() const {
    if (precedences.find(curTok.type) != precedences.end()) {
        return precedences[curTok.type];
    }
    return LOWEST;
}

void parser::peekError(const TokenType &tt) {
    errors.emplace_back("expected=" + lex::tokenTypeToString(tt) + ", got=" + lex::tokenTypeToString(peekTok.type) +
                        "\nFound on line=" + std::to_string(curTok.line));
}

std::unique_ptr<Statement> parser::parseStatement() {
    if (curTok.type == TokenType::VAR_DECL) {
        return parseDeclareStatement();
    }
    if (curTok.type == TokenType::AMPERSAND) {
        return parseReferenceStatement();
    }
    if (curTok.type == TokenType::RETURN) {
        return parseReturnStatement();
    }
    return parseExpressionStatement();
}

std::unique_ptr<DeclareStatement> parser::parseDeclareStatement() {
    auto stmt = std::unique_ptr<DeclareStatement>();
    stmt->tok = curTok;

    // ensure a var declaration is accompanied by a type declaration
    // ie, for ident x, we say "store x : int = 5;"
    if (!expectPeek(TokenType::IDENT)) {
        delete stmt;
        return nullptr;
    }
    stmt->name->tok = curTok;
    stmt->name->value = curTok.lit;
    if (!expectPeek(TokenType::COLON)) {
        return nullptr;
    }
    nextToken();
    if (!expectPeek(TokenType::arr_type) || !expectPeek(TokenType::int_type) || !expectPeek(TokenType::str_type) || !
        expectPeek(TokenType::bool_type)) {
        return nullptr;
    }
    nextToken();
    if (!expectPeek(TokenType::ASSIGN)) {
        return nullptr;
    }
    nextToken();
    stmt->value = parseExpression(LOWEST);
    if (peekTok.type == TokenType::SEMICOLON) {
        nextToken();
    }
    return stmt;
}

std::unique_ptr<ReferenceStatement> parser::parseReferenceStatement() {
    auto stmt = std::make_unique<ReferenceStatement>();
    stmt->tok = curTok;

    if (!expectPeek(TokenType::IDENT)) {
        delete stmt;
        return nullptr;
    }
    stmt->name->tok = curTok;
    stmt->name->value = curTok.lit;
    if (!expectPeek(TokenType::ASSIGN)) {
        delete stmt;
        return nullptr;
    }
    nextToken();

    stmt->value = parseExpression(LOWEST);
    if (peekTok.type == TokenType::SEMICOLON) {
        nextToken();
    }
    return stmt;
}

std::unique_ptr<ReturnStatement> parser::parseReturnStatement() {
    auto stmt = std::unique_ptr<ReturnStatement>();
    stmt->tok = curTok;
    nextToken();

    stmt->returnVal = parseExpression(LOWEST);
    if (peekTok.type == TokenType::SEMICOLON) {
        nextToken();
    }
    return stmt;
}

std::unique_ptr<ExpressionStatement> parser::parseExpressionStatement() {
    auto stmt = std::unique_ptr<ExpressionStatement>();
    stmt->tok = curTok;
    stmt->expression = parseExpression(LOWEST);

    if (peekTok.type == TokenType::SEMICOLON) {
        nextToken();
    }
    return stmt;
}

std::unique_ptr<BlockStatement> parser::parseBlockStatement() {
    auto block = std::unique_ptr<BlockStatement>();
    block->tok = curTok;

    nextToken();

    while (curTok.type != TokenType::RBRACE && curTok.type != TokenType::EoF) {
        auto stmt = parseStatement();
        if (stmt != nullptr) {
            block->statements.push_back(stmt);
        }
        nextToken();
    }
    return block;
}

std::unique_ptr<Expression> parser::parseExpression(Precedence precedence) {
    if (prefixParseFns.find(curTok.type) == prefixParseFns.end()) {
        noPrefixParseFnError(curTok.type);
        return nullptr;
    }
    PrefixParseFn prefix = prefixParseFns[curTok.type];
    std::unique_ptr<Expression> lhs = (this->*prefix)();

    while (peekTok.type != TokenType::SEMICOLON && precedence < peekPrecedence()) {
        if (infixParseFns.find(peekTok.type) == infixParseFns.end()) {
            return lhs;
        }
        InfixParseFn infix = infixParseFns[peekTok.type];
        nextToken();
        lhs = (this->*infix)(std::move(lhs));
    }
    return lhs;
}

std::vector<std::unique_ptr<Expression> > parser::parseExpressionList() {
    std::vector<std::unique_ptr<Expression> > args;

    nextToken();
    args.push_back(parseExpression(LOWEST));
    while (peekTok.type == TokenType::COMMA) {
        nextToken();
        nextToken();
        args.push_back(parseExpression(LOWEST));
    }
    return args;
}

std::unique_ptr<Expression> parser::parseIdentifier() {
    auto ident = std::make_unique<Identifier>();
    ident->tok = curTok;
    ident->value = curTok.lit;
    return ident;
}

std::unique_ptr<Expression> parser::parseBoolean() {
    auto ident = std::make_unique<BoolLiteral>();
    ident->tok = curTok;
    ident->value = curTok.type == TokenType::TRUE; // i fw this
    return ident;
}

std::unique_ptr<Expression> parser::parseIntegerLiteral() {
    auto num = std::make_unique<IntLiteral>();
    num->tok = curTok;
    try {
        num->value = std::stoi(curTok.lit);
    } catch (const std::invalid_argument &e) {
        errors.push_back("unable to parse token literal=" + curTok.lit + " to int." +
                         "\n expected=int, got=" + curTok.lit + ", line=" + std::to_string(curTok.line) +
                         "\n" + e.what());
        return nullptr;
    } catch (const std::out_of_range &e) {
        errors.push_back("unable to parse token literal=" + curTok.lit + ", int out of range" +
                         ", line=" + std::to_string(curTok.line) + "\n" + e.what());
        return nullptr;
    }
    return num;
}

std::unique_ptr<Expression> parser::parseStringLiteral() {
    auto s = std::make_unique<StringLiteral>();
    s->tok = curTok;
    s->value = curTok.lit;
    return s;
}

std::vector<std::unique_ptr<Identifier> > parser::parseFunctionParameters() {
    std::vector<std::unique_ptr<Identifier> > params;

    if (peekTok.type == TokenType::RPAREN) {
        nextToken();
        return params;
    }

    nextToken();

    auto ident = std::make_unique<Identifier>();
    ident->tok = curTok;
    ident->value = curTok.lit;
    params.push_back(ident);

    while (peekTok.type == TokenType::COMMA) {
        nextToken();
        nextToken();
        ident = std::make_unique<Identifier>();
        ident->tok = curTok;
        ident->value = curTok.lit;
        params.push_back(ident);
    }

    if (!expectPeek(TokenType::RPAREN)) {
        errors.push_back("function parameters not closed. expected=\')\' got=" +
                         curTok.lit + ". line=" + std::to_string(curTok.line));
        return {};
    }
    return params;
}

std::unique_ptr<Expression> parser::parseFunctionLiteral() {
    auto fn = std::make_unique<FuncLiteral>();
    fn->tok = curTok;

    if (!expectPeek(TokenType::LPAREN)) {
        return nullptr;
    }
    fn->params = parseFunctionParameters();
    if (!expectPeek(TokenType::LBRACE)) {
        return nullptr;
    }

    fn->body = parseBlockStatement();
    return fn;
}

std::unique_ptr<Expression> parser::parseArrayLiteral() {
    auto expr = std::make_unique<ArrayLiteral>();
    expr->tok = curTok;
    if (peekTok.type == TokenType::RBRACKET) {
        nextToken();
        return expr;
    }

    expr->elements = parseExpressionList();
    if (!expectPeek(TokenType::RBRACKET)) {
        expr->elements = std::vector<std::unique_ptr<Expression> >{};
    }
    return expr;
}

std::unique_ptr<Expression> parser::parsePrefixExpression() {
    auto expr = std::make_unique<PrefixExpression>();
    expr->tok = curTok;
    expr->op = curTok.lit;
    nextToken();

    expr->rhs = parseExpression(LOWEST);
    return expr;
}

std::unique_ptr<Expression> parser::parseGroupedExpression() {
    nextToken();
    auto expr = parseExpression(LOWEST);

    if (!expectPeek(TokenType::RPAREN)) {
        return nullptr;
    }

    return expr;
}

std::unique_ptr<Expression> parser::parseIfExpression() {
    auto expr = std::make_unique<IfExpression>();
    expr->tok = curTok;

    if (!expectPeek(TokenType::LPAREN)) {
        return nullptr;
    }
    nextToken();
    expr->condition = parseExpression(LOWEST);
    if (!expectPeek(TokenType::RPAREN)) {
        return nullptr;
    }

    if (!expectPeek(TokenType::LBRACE)) {
        return nullptr;
    }
    expr->consequence = parseBlockStatement();

    if (peekTok.type == TokenType::ELSE) {
        nextToken();
        if (!expectPeek(TokenType::LBRACE)) {
            return nullptr;
        }
        expr->alternative = parseBlockStatement();
    }
    return expr;
}

std::unique_ptr<Expression> parser::parseWhileExpression() {
    auto expr = std::make_unique<WhileExpression>();
    expr->tok = curTok;

    if (!expectPeek(TokenType::LPAREN)) {
        return nullptr;
    }
    nextToken();
    expr->condition = parseExpression(LOWEST);
    if (!expectPeek(TokenType::RPAREN)) {
        return nullptr;
    }

    if (!expectPeek(TokenType::LBRACE)) {
        return nullptr;
    }
    expr->consequence = parseBlockStatement();
    return expr;
}

std::unique_ptr<Expression> parser::parseCallExpression(std::unique_ptr<Expression> callee) {
    auto expr = std::make_unique<CallExpression>();
    expr->tok = curTok;
    expr->callee = std::move(callee);

    if (peekTok.type == TokenType::RPAREN) {
        nextToken();
        return expr;
    }
    expr->arguments = parseExpressionList();
    if (!expectPeek(TokenType::RPAREN)) {
        expr->arguments = std::vector<std::unique_ptr<Expression> >{};
    }
    return expr;
}

std::unique_ptr<Expression> parser::parseIndexExpression(std::unique_ptr<Expression> array) {
    auto expr = std::make_unique<IndexExpression>();
    expr->tok = curTok;
    expr->array = std::move(array);
    nextToken();
    expr->index = parseExpression(LOWEST);
    if (!expectPeek(TokenType::RBRACKET)) {
        return nullptr;
    }
    return expr;
}

std::unique_ptr<Expression> parser::parseInfixExpression(std::unique_ptr<Expression> lhs) {
    auto expr = std::make_unique<InfixExpression>();
    expr->tok = curTok;
    expr->op = curTok.lit;
    expr->lhs = std::move(lhs);

    Precedence precedence = curPrecedence();
    nextToken();
    expr->rhs = parseExpression(precedence);

    return expr;
}

void parser::noPrefixParseFnError(TokenType tt) {
    errors.push_back("no prefix parse function for " + lex::tokenTypeToString(tt));
}

void parser::New(const lex &l) {
    this->l = l;

    prefixParseFns[TokenType::IDENT] = &parser::parseIdentifier;
    prefixParseFns[TokenType::INT] = &parser::parseIntegerLiteral;
    prefixParseFns[TokenType::STRING] = &parser::parseStringLiteral;
    prefixParseFns[TokenType::BANG] = &parser::parsePrefixExpression;
    prefixParseFns[TokenType::SUB] = &parser::parsePrefixExpression;
    prefixParseFns[TokenType::TRUE] = &parser::parseBoolean;
    prefixParseFns[TokenType::FALSE] = &parser::parseBoolean;
    prefixParseFns[TokenType::LPAREN] = &parser::parseGroupedExpression;
    prefixParseFns[TokenType::IF] = &parser::parseIfExpression;
    prefixParseFns[TokenType::WHILE] = &parser::parseWhileExpression;
    prefixParseFns[TokenType::FUNCTION] = &parser::parseFunctionLiteral;
    prefixParseFns[TokenType::LBRACKET] = &parser::parseArrayLiteral;

    infixParseFns[TokenType::ADD] = &parser::parseInfixExpression;
    infixParseFns[TokenType::SUB] = &parser::parseInfixExpression;
    infixParseFns[TokenType::DIV] = &parser::parseInfixExpression;
    infixParseFns[TokenType::MUL] = &parser::parseInfixExpression;
    infixParseFns[TokenType::MOD] = &parser::parseInfixExpression;
    infixParseFns[TokenType::EQ] = &parser::parseInfixExpression;
    infixParseFns[TokenType::NEQ] = &parser::parseInfixExpression;
    infixParseFns[TokenType::LT] = &parser::parseInfixExpression;
    infixParseFns[TokenType::GT] = &parser::parseInfixExpression;
    infixParseFns[TokenType::LTE] = &parser::parseInfixExpression;
    infixParseFns[TokenType::GTE] = &parser::parseInfixExpression;
    infixParseFns[TokenType::LPAREN] = &parser::parseCallExpression;
    infixParseFns[TokenType::LBRACKET] = &parser::parseIndexExpression;
    nextToken();
    nextToken();
}

std::unique_ptr<Program> parser::parseProgram() {
    auto program = std::make_unique<Program>();

    while (curTok.type != TokenType::EoF) {
        std::unique_ptr<Statement> stmt = parseStatement();
        if (stmt != nullptr) {
            program->statements.push_back(std::move(stmt));
        }
        nextToken();
    }

    return program;
}

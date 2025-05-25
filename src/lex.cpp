#include <utility>

#include "../src/h/lex.h"

std::string tokenTypeToString(const TokenType type) {
    switch (type) {
        case TokenType::IDENT: return "IDENT";
        case TokenType::INT: return "INT";
        case TokenType::STRING: return "STRING";
        case TokenType::DECLARE: return "DECLARE";

        case TokenType::ASSIGN: return "ASSIGN";
        case TokenType::ADD: return "ADD";
        case TokenType::SUB: return "SUB";
        case TokenType::MUL: return "MUL";
        case TokenType::DIV: return "DIV";
        case TokenType::MOD: return "MOD";

        case TokenType::LPAREN: return "LPAREN";
        case TokenType::RPAREN: return "RPAREN";
        case TokenType::LBRACKET: return "LBRACKET";
        case TokenType::RBRACKET: return "RBRACKET";
        case TokenType::LBRACE: return "LBRACE";
        case TokenType::RBRACE: return "RBRACE";

        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::COMMA: return "COMMA";
        case TokenType::BANG: return "BANG";
        case TokenType::BAR: return "BAR";
        case TokenType::AMPERSAND: return "AMPERSAND";
        case TokenType::DOT: return "DOT";

        case TokenType::GT: return "GT";
        case TokenType::LT: return "LT";
        case TokenType::EQ: return "EQ";
        case TokenType::NEQ: return "NEQ";
        case TokenType::AND: return "AND";
        case TokenType::OR: return "OR";

        case TokenType::FUNCTION: return "FUNCTION";
        case TokenType::IF: return "IF";
        case TokenType::ELSE: return "ELSE";
        case TokenType::WHILE: return "WHILE";
        case TokenType::RETURN: return "BREAK";
        case TokenType::TRUE: return "TRUE";
        case TokenType::FALSE: return "FALSE";

        case TokenType::int_type: return "int_type";
        case TokenType::str_type: return "str_type";
        case TokenType::bool_type: return "bool_type";
        case TokenType::arr_type: return "arr_type";

        case TokenType::ILLEGAL: return "ILLEGAL";
        case TokenType::EoF: return "EoF";
        default:
            break;
    }
    return "";
}

// token implementations
Token::Token() : type(TokenType::IDENT), line(1) {}
Token::Token(const TokenType type, std::string lit, const int line)
    : type(type), lit(std::move(lit)), line(line) {}
[[nodiscard]] std::string Token::toString() const {
    return "tok(type: " + tokenTypeToString(type) +
           ", literal: " + lit + ", line: " + std::to_string(line) + ")";
}

// lexer implementations
lex::lex(std::string &input)
 : input(std::move(input)), ch(' '), pos(0), readPos(0), line(1), linePos(1),
  keywords({
      {"func", TokenType::FUNCTION},
      {"if", TokenType::IF},
      {"else", TokenType::ELSE},
      {"while", TokenType::WHILE},
      {"return", TokenType::RETURN},
      {"break", TokenType::BREAK},
      {"true", TokenType::TRUE},
      {"false", TokenType::FALSE},
      {"int", TokenType::int_type},
      {"str", TokenType::str_type},
      {"bool", TokenType::bool_type},
      {"arr", TokenType::arr_type},
  }) {
    readChar();
}

void lex::readChar() {
    if (pos >= input.size()) {
        ch = 0;
    } else {
        ch = input[readPos];
    }
    pos = readPos;
    readPos++;
}

void lex::skipWhitespace() {
    while (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
        if (ch == '\n') {
            line++;
            linePos = 1;
        } else if (ch == ' ') {
            linePos++;
        }
        readChar();
    }
}

Token lex::newToken(const TokenType type, const std::string &lit, const int line) {
    return Token(type, lit, line);
}

[[nodiscard]] char lex::peekChar() const {
    if (readPos >= input.length()) {
        return 0;
    }
    return input[readPos];
}

void lex::printError(const Token &t) const {
    std::cerr << "Lexing error on, line=" << t.line << ", linepos=" << linePos << "." << std::endl;
    std::cerr << "Expected a valid token, got=" << t.lit << "." << std::endl;
    std::cerr << "Full token err: " << t.toString() << std::endl;
}

std::string lex::readIdent() {
    const int start = pos;
    while (isalnum(ch)) {
        readChar();
    }
    return input.substr(start, pos - start);
}

std::string lex::readInt() {
    const int start = pos;
    readChar();
    while (isdigit(ch)) {
        readChar();
    }
    if (isalpha(ch)) {
        std::cerr << "TokenType IDENT must not start with INT." << std::endl;
        std::cerr << "Lexing error on, line=" << line << ", linepos=" << linePos << "." << std::endl;
        std::cerr << "Expected INT, got=" << input.substr(start, pos - start) << std::endl;
        std::abort();
    }
    return input.substr(start, pos - start);
}

std::string lex::readString() {
    const int start = pos;
    readChar();
    while (ch != '"' && ch != 0) {
        readChar();
    }

    if (ch == 0) {
        std::cerr << "Lexing error on, line=" << line << ", linepos=" << linePos << "." << std::endl;
        std::cerr << "Expected \", got=tt::ILLEGAL." << std::endl;
        std::cerr << "Error: unterminated string sequence" << std::endl;
        std::abort();
    }

    return input.substr(start, pos - start);
}

Token lex::nextToken() {
    Token tok;
    skipWhitespace();
    switch (ch) {
        case '=':
            if (peekChar() == '=') {
                readChar();
                tok = newToken(TokenType::EQ, "==", line);
                break;
            }
            tok = newToken(TokenType::ASSIGN, std::string(1, ch), line);
            break;
        case '+':
            tok = newToken(TokenType::ADD, std::string(1, ch), line);
            break;
        case '-':
            tok = newToken(TokenType::SUB, std::string(1, ch), line);
            break;
        case '*':
            tok = newToken(TokenType::MUL, std::string(1, ch), line);
            break;
        case '/':
            tok = newToken(TokenType::DIV, std::string(1, ch), line);
            break;
        case '%':
            tok = newToken(TokenType::MOD, std::string(1, ch), line);
            break;
        case '(':
            tok = newToken(TokenType::LPAREN, std::string(1, ch), line);
            break;
        case ')':
            tok = newToken(TokenType::RPAREN, std::string(1, ch), line);
            break;
        case '[':
            tok = newToken(TokenType::LBRACKET, std::string(1, ch), line);
            break;
        case ']':
            tok = newToken(TokenType::RBRACKET, std::string(1, ch), line);
            break;
        case '{':
            tok = newToken(TokenType::LBRACE, std::string(1, ch), line);
            break;
        case '}':
            tok = newToken(TokenType::RBRACE, std::string(1, ch), line);
            break;
        case ';':
            tok = newToken(TokenType::SEMICOLON, std::string(1, ch), line);
            break;
        case ',':
            tok = newToken(TokenType::COMMA, std::string(1, ch), line);
            break;
        case '!':
            if (peekChar() == '=') {
                readChar();
                tok = newToken(TokenType::NEQ, "!=", line);
                break;
            }
            tok = newToken(TokenType::BANG, std::string(1, ch), line);
            break;
        case '|':
            if  (peekChar() == '|') {
                readChar();
                tok = newToken(TokenType::OR, "||", line);
                break;
            }
            tok = newToken(TokenType::BAR, std::string(1, ch), line);
            break;
        case '&':
            if (peekChar() == '&') {
                readChar();
                tok = newToken(TokenType::AND, "&&", line);
                break;
            }
            tok  = newToken(TokenType::AMPERSAND, std::string(1, ch), line);
            break;
        case '.':
            tok = newToken(TokenType::DOT, std::string(1, ch), line);
            break;
        case '"':
            tok = newToken(TokenType::STRING, readString(), line);
            break;
        case '>':
            tok = newToken(TokenType::GT, std::string(1, ch), line);
            break;
        case '<':
            tok = newToken(TokenType::LT, std::string(1, ch), line);
            break;
        case 0:
            tok.lit = "";
            tok.type = TokenType::EoF;
            tok.line = line;
            break;
        default: {
            if (isalpha(ch)) {
                tok.lit = readIdent();
                if (keywords.find(tok.lit) != keywords.end()) {
                    tok.type = keywords[tok.lit];
                } else {
                    tok.type = TokenType::IDENT;
                }
                tok.line = line;
                return tok;
            }
            if (isdigit(ch)) {
                tok.lit =  readInt();
                tok.type = TokenType::INT;
                tok.line = line;
                return tok;
            }
            tok.type = TokenType::ILLEGAL;
            tok.line = line;
            tok.lit = ch;
            printError(tok);
            std::abort();
        }
    }

    readChar();
    return tok;
}
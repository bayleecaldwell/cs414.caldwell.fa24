#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>

enum TokenType {
    LS, CD, CAT, PRINT, EXEC, SET, ECHO, VARIABLE, EQUAL, STRING, FILENAME, FOLDER, ROOT, DOT, BACKSLASH, UNKNOWN, END
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType type, std::string value = "") : type(type), value(value) {}
};

class Tokenizer {
public:
    explicit Tokenizer(const std::string &input) : input(input), pos(0) {}

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;

        while (pos < input.size()) {
            skipWhitespace();
            if (pos >= input.size()) break;

            if (isCommand("ls")) {
                tokens.push_back(Token(LS, "ls"));
                pos += 2;
            } else if (isCommand("cd")) {
                tokens.push_back(Token(CD, "cd"));
                pos += 2;
            } else if (isCommand("cat")) {
                tokens.push_back(Token(CAT, "cat"));
                pos += 3;
            } else if (isCommand("print")) {
                tokens.push_back(Token(PRINT, "print"));
                pos += 5;
            } else if (isCommand("exec")) {
                tokens.push_back(Token(EXEC, "exec"));
                pos += 4;
            } else if (isCommand("SET")) {
                tokens.push_back(Token(SET, "SET"));
                pos += 3;
            } else if (isCommand("echo")) {
                tokens.push_back(Token(ECHO, "echo"));
                pos += 4;
            } else if (input[pos] == '$') {
                tokens.push_back(Token(VARIABLE, parseVariable()));
            } else if (input[pos] == '=') {
                tokens.push_back(Token(EQUAL, "="));
                pos++;
            } else if (input[pos] == '\\') {
                tokens.push_back(Token(BACKSLASH, "\\"));
                pos++;
            } else if (input[pos] == '.') {
                tokens.push_back(Token(DOT, "."));
                pos++;
            } else if (input[pos] == '"') {
                tokens.push_back(Token(STRING, parseString()));
            } else if (isFilename()) {
                tokens.push_back(Token(FILENAME, parseFilename()));
            } else if (isFolderName()) {
                tokens.push_back(Token(FOLDER, parseFolderName()));
            } else {
                tokens.push_back(Token(UNKNOWN, std::string(1, input[pos])));
                pos++;
            }
        }

        tokens.push_back(Token(END));
        return tokens;
    }

private:
    std::string input;
    size_t pos;

    void skipWhitespace() {
        while (pos < input.size() && std::isspace(input[pos])) pos++;
    }

    bool isCommand(const std::string &cmd) {
        return input.substr(pos, cmd.size()) == cmd &&
               (pos + cmd.size() >= input.size() || std::isspace(input[pos + cmd.size()]));
    }

    std::string parseVariable() {
        size_t start = pos;
        pos++;
        while (pos < input.size() && (std::isalnum(input[pos]) || input[pos] == '_')) pos++;
        return input.substr(start, pos - start);
    }

    std::string parseString() {
        pos++;
        size_t start = pos;
        while (pos < input.size() && input[pos] != '"') pos++;
        std::string str = input.substr(start, pos - start);
        pos++; 
        return str;
    }

    bool isFilename() {
        size_t start = pos;
        size_t dotPos = input.find('.', start);

        if (dotPos == std::string::npos || dotPos - start > 8) return false;
        if (!isAlphanumeric(input.substr(start, dotPos - start))) return false;

        size_t extPos = dotPos + 1;
        return (input.size() - extPos == 3 && isAlphanumeric(input.substr(extPos, 3)));
    }

    std::string parseFilename() {
        size_t dotPos = input.find('.', pos);
        std::string name = input.substr(pos, dotPos - pos);
        std::string ext = input.substr(dotPos + 1, 3);
        pos = dotPos + 4; 
        return name + "." + ext;
    }

    bool isFolderName() {
        size_t endPos = input.find_first_of(" \\.", pos);
        return endPos != std::string::npos && endPos - pos <= 8 && isAlphanumeric(input.substr(pos, endPos - pos));
    }

    std::string parseFolderName() {
        size_t endPos = input.find_first_of(" \\.", pos);
        std::string folderName = input.substr(pos, endPos - pos);
        pos = endPos;
        return folderName;
    }

    bool isAlphanumeric(const std::string &str) {
        for (char ch : str) {
            if (!std::isalnum(ch)) return false;
        }
        return true;
    }
};

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

    std::unique_ptr<ASTNode> parse() {
        if (pos >= tokens.size()) throw std::runtime_error("Empty command");

        Token token = tokens[pos];
        std::unique_ptr<ASTNode> result;

        switch (token.type) {
            case LS:
                result = parseLsCommand();
                break;
            case CD:
                result = parseCdCommand();
                break;
            case CAT:
                result = parseCatCommand();
                break;
            case PRINT:
                result = parsePrintCommand();
                break;
            case EXEC:
                result = parseExecCommand();
                break;
            case SET:
                result = parseSetCommand();
                break;
            case ECHO:
                result = parseEchoCommand();
                break;
            default:
                throw std::runtime_error("Unknown command");
        }

        printSymbolTable();
        return result;
    }

private:
    const std::vector<Token>& tokens;
    size_t pos;
    std::unordered_map<std::string, std::string> symbolTable;

    std::unique_ptr<ASTNode> parseLsCommand() {
        pos++;
        if (pos < tokens.size() && tokens[pos].type == FOLDER) {
            return std::make_unique<CommandNode>("ls", tokens[pos++].value);
        }
        return std::make_unique<CommandNode>("ls");
    }

    std::unique_ptr<ASTNode> parseCdCommand() {
        pos++;
        if (pos < tokens.size()) {
            if (tokens[pos].type == ROOT) {
                pos++;
                return std::make_unique<CommandNode>("cd", "\\");
            } else if (tokens[pos].type == FOLDER) {
                std::string path = parseFolderPath();
                return std::make_unique<CommandNode>("cd", path);
            }
        }
        return std::make_unique<CommandNode>("cd");
    }

    std::unique_ptr<ASTNode> parseCatCommand() {
        pos++;
        if (pos < tokens.size() && tokens[pos].type == FILENAME) {
            return std::make_unique<CommandNode>("cat", tokens[pos++].value);
        }
        throw std::runtime_error("Syntax error: Expected filename after 'cat'");
    }

    std::unique_ptr<ASTNode> parsePrintCommand() {
        pos++;
        if (pos < tokens.size() && tokens[pos].type == FILENAME) {
            return std::make_unique<CommandNode>("print", tokens[pos++].value);
        }
        throw std::runtime_error("Syntax error: Expected filename after 'print'");
    }

    std::unique_ptr<ASTNode> parseExecCommand() {
        pos++;
        if (pos < tokens.size() && tokens[pos].type == FILENAME) {
            return std::make_unique<CommandNode>("exec", tokens[pos++].value);
        }
        throw std::runtime_error("Syntax error: Expected filename after 'exec'");
    }

    std::unique_ptr<ASTNode> parseSetCommand() {
        pos++;
        if (pos < tokens.size() && tokens[pos].type == VARIABLE) {
            std::string varName = tokens[pos++].value;
            if (pos < tokens.size() && tokens[pos].type == EQUAL) {
                pos++;
                if (pos < tokens.size() && tokens[pos].type == STRING) {
                    symbolTable[varName] = tokens[pos++].value;
                    return std::make_unique<CommandNode>("SET", varName + " = "

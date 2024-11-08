#include <iostream>
#include <string>
#include <vector>
#include <cctype>

enum TokenType {
    LS, CD, CAT, PRINT, EXEC, FILENAME, FOLDER, ROOT, DOT, BACKSLASH, UNKNOWN, END
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
            } else if (input[pos] == '\\') {
                tokens.push_back(Token(BACKSLASH, "\\"));
                pos++;
            } else if (input[pos] == '.') {
                tokens.push_back(Token(DOT, "."));
                pos++;
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
        pos = dotPos + 4;  // Move past filename and extension
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

void printTokens(const std::vector<Token>& tokens) {
    for (const auto& token : tokens) {
        std::cout << "Token(Type: " << token.type << ", Value: \"" << token.value << "\")\n";
    }
}

int main() {
    std::string input;
    std::cout << "Enter command: ";
    std::getline(std::cin, input);

    Tokenizer tokenizer(input);
    std::vector<Token> tokens = tokenizer.tokenize();

    printTokens(tokens);

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>


class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print() const = 0;
};


class CommandNode : public ASTNode {
public:
    std::string command;
    std::string argument;

    CommandNode(const std::string& command, const std::string& argument = "")
        : command(command), argument(argument) {}

    void print() const override {
        std::cout << "Command: " << command;
        if (!argument.empty()) std::cout << " " << argument;
        std::cout << std::endl;
    }
};

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

    std::unique_ptr<ASTNode> parse() {
        if (pos >= tokens.size()) throw std::runtime_error("Empty command");

        Token token = tokens[pos];

        switch (token.type) {
            case LS:
                return parseLsCommand();
            case CD:
                return parseCdCommand();
            case CAT:
                return parseCatCommand();
            case PRINT:
                return parsePrintCommand();
            case EXEC:
                return parseExecCommand();
            default:
                throw std::runtime_error("Unknown command");
        }
    }

private:
    const std::vector<Token>& tokens;
    size_t pos;

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

    std::string parseFolderPath() {
        std::string path;
        while (pos < tokens.size() && (tokens[pos].type == FOLDER || tokens[pos].type == BACKSLASH)) {
            path += tokens[pos++].value;
        }
        return path;
    }
};

void testParser(const std::vector<Token>& tokens) {
    Parser parser(tokens);
    try {
        std::unique_ptr<ASTNode> ast = parser.parse();
        ast->print();
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    std::vector<Token> tokens = {
        Token(LS), Token(BACKSLASH), Token(FOLDER, "FOLDER1"), Token(END)
    };

    testParser(tokens);

    return 0;
}

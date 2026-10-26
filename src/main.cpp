#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>

using namespace std;

enum class TokenType {
    _return,
    int_literal,
    semicolon, 
};

struct Token {
    TokenType type;
    optional<string> value {};
};

vector<Token> tokenize(const string& str) {
    vector<Token> tokens {};
    string buf {}; 
    
    for (int i = 0; i < str.length(); i++) {
        char c = str.at(i);
        if (isalpha(c)) {
            buf.push_back(c);
            i++;
            while (i < str.length() && isalnum(str.at(i))) {
                buf.push_back(str.at(i));
                i++;
            }
            i--;

            if (buf == "return") {
                tokens.push_back({.type=TokenType::_return});
                buf.clear();
                continue;
            }             
            else if (isdigit(c)) {
                buf.push_back(c);
                i++;
                while (isdigit(str.at(i))) {
                    buf.push_back(str.at(i));
                    i++;
                } 
                i--;
                tokens.push_back({.type=TokenType::int_literal, .value=buf});
                buf.clear();
                continue;
            }
            else if (c == ';') {
                tokens.push_back({.type=TokenType::semicolon});
            }
            else if(isspace(c)) {
                continue;
            }
            else {
                std::cerr << "Unknown token: " << buf << std::endl;
                exit(EXIT_FAILURE);
            }

        }
    }

    /*
    for (const Token& token : tokens) {
        cout << "Token(type=" << static_cast<int>(token.type)
             << ", value=" << token.value.value_or("") << ")" << endl;
    }
    */

    return tokens;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Incorrect usage" << endl;
        cerr << "Usage: " << argv[0] << " <file>" << endl;
        return EXIT_FAILURE;
    }

    fstream input(argv[1], ios::in);
    stringstream contents_stream;
    contents_stream << input.rdbuf();

    input.close();

    string contents = contents_stream.str();
    
    vector<Token> tokenized_contents = tokenize(contents);   

    cout << "Tokenized successfully" << endl;


    return 0;
}
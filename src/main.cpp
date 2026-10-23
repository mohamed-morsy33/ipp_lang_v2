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
    optional<string> value;
};

vector<Token> tokenize(const string& str) {
    string buf {}; 
    
    for (int i = 0; i < str.length(); i++) {
        char c = str.at(i);
        if (isalpha(c)) {
            buf.push_back(c);
            i++;
            while (isalnum(str.at(i))) {
                buf.push_back(str.at(i));
                i++;
            }
            i--;

            if (buf.)
        }
    }


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
    tokenize(contents);   

    return 0;
}
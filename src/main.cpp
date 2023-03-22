#include <iostream>
#include <vector>
using namespace std;

class CommandHandler {
    int _n;
    std::vector<string> _commands;
    const string start_din;
    const string end_din;
    bool _din_blok_is_active;
    size_t _cout_inline_command;

public:
    CommandHandler(int n) :
        _n(n),
        _din_blok_is_active(false),
        start_din("{"),
        end_din("}"),
        _cout_inline_command(0)
    {;}

    bool add(std::string&& command, bool eof) {
        if(eof) {
            print_block();
            return true;
        }
        if(command.empty()) {
            return false;
        }

        if(command == start_din) {
            _din_blok_is_active == true ? void() : print_block();
            _din_blok_is_active = true;
            ++_cout_inline_command;
        } else if (command == end_din) {
            --_cout_inline_command;
            _din_blok_is_active = _cout_inline_command == 0 ? false : true;
        } else {
            --_n;
            _commands.push_back(command);
        }


        bool end = _din_blok_is_active || _n > 0 ? false : true;

        if(end) {
            print_block();
        }
        return end;
    }

    void print_block() {
        std::string result = "bulk: "s;
        bool start = true;
        for(const auto& var: _commands) {
            if(!start) {
                result += ", ";
            }
            result += var;
            start = false;
        }
        cout << result << endl;
    }
};

void ReadCommand(CommandHandler& ch) {
    for(bool end = false; end != true;) {
        std::string command;
        std::istream& in = getline(std::cin, command);
        end = ch.add(std::move(command), in.eof());
    }
}

int main()
{
    int N = 0;
    std::cin >> N ;
    CommandHandler ch(N);
    ReadCommand(ch);
    cout << "Hello World!" << endl;
    return 0;
}

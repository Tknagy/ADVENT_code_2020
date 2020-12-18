#include "utils.h"

int first_precedence(const char c)
{
    if (c == ')')
        return 0;
    else if (c == '*')
        return 1;
    else if (c == '+')
        return 1;
    else std::abort();
}

int second_precedence(const char c)
{
    if (c == ')')
        return 0;
    else if (c == '*')
        return 1;
    else if (c == '+')
        return 2;
    else std::abort();
}

using PrecedenceCallback = int (*)(const char);
std::string postfix_notation(const std::string &infix_notation, PrecedenceCallback precedence)
{
    std::string rpn;
    std::vector<char> ops;
    for (auto it = infix_notation.rbegin(); it != infix_notation.rend(); ++it) {
        const char c = *it;
        switch (c) {
        case ' ':
            break;
        case '(':
            while (ops.back() != ')') {
                rpn += ops.back();
                ops.pop_back();
            }
            ops.pop_back();
            break;
        case ')':
            ops.push_back(c);
            break;
        case '+':
        case '*':
            while (ops.size() != 0 && precedence(c) < precedence(ops.back())) {
                rpn += ops.back();
                ops.pop_back();
            }
            ops.push_back(c);
            break;
        default:
            rpn += c;
            break;
        }
    }

    while (ops.size() > 0) {
        rpn += ops.back();
        ops.pop_back();
    }
    return rpn;
}

ull eval(const ull a, const ull b, const char op)
{
    if (op == '+')
        return a + b;
    else if (op == '*')
        return a * b;
    else
        std::abort();
}

void eval(std::vector<ull> &nums, char op)
{
    ull a = nums.back();
    nums.pop_back();
    ull b = nums.back();
    nums.pop_back();
    nums.push_back(eval(a, b, op));
}

ull eval_expr(const std::string &expr, PrecedenceCallback precedence)
{
    std::string rpn = postfix_notation(expr, precedence);

    std::vector<ull> nums;
    for (const char c : rpn)
        if (c == '*' || c == '+')
            eval(nums, c);
        else
            nums.push_back(static_cast<ull>(c - '0'));
    return nums.back();
}

ll part_one(const std::vector<std::string> &input)
{
    return std::transform_reduce(
        input.begin(), input.end(), 0ll, [](const auto &a, const auto &b) { return a + b; },
        [](const auto &line) { return eval_expr(line, first_precedence); });
}

ull part_two(const std::vector<std::string> &input)
{
    return std::transform_reduce(
        input.begin(), input.end(), 0ll, [](const auto &a, const auto &b) { return a + b; },
        [](const auto &line) { return eval_expr(line, second_precedence); });
}

int main(int argc, char const *argv[])
{
    auto input = read_stdin();
    std::cout << part_one(input) << '\n';
    std::cout << part_two(input) << '\n';
    return 0;
}

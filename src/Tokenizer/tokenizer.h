#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>

using Tokens = std::vector<std::string>;

Tokens tokenize(const std::string& input);

#endif // TOKENIZER_H

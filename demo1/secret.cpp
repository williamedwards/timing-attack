#include "secret.h"

constexpr char secret_password[] = "elvishwordforfriend";

bool my_string_compare(std::string x, std::string y) {
    if (x.size() != y.size())
        return false;

    for (int i = 0; i < x.size(); i++) {
        if (x[i] != y[i])
            return false;
    }
    return true;
}

bool check_password(std::string password) {
    return my_string_compare(password, secret_password);
}

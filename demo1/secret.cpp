#include "secret.h"

constexpr char secret_password[] = "elvishwordforfriend";

bool check_password(std::string password) {
    return (password == secret_password);
}

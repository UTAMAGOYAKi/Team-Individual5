#include "ingredients.h"
#include <array>

constexpr int ingredients_array = 6;
std::array <bool, ingredients_array> IU{ false };

bool is_ingredient_unlocked(ingredients ingredient) {
    return IU[ingredient];
}

void unlock_ingredient(ingredients ingredient) {
    IU[ingredient] = true;
}
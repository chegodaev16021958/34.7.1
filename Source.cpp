#include <iostream>
#include <string>
#include <concepts>

template <typename T>
concept ComplexConcept = requires(const T v)
{
    { v.hash() }
    ->std::convertible_to<long>;
    { v.toString() }
    ->std::same_as<std::string>;
} && !std::has_virtual_destructor<T>::value;

template <ComplexConcept T>
void checkConcept(T value)
{
    std::cout << "hash() result: " << value.hash() << std::endl;
    std::cout << "toString() result: " << value.toString() << std::endl;
    std::cout << "has virtual destructor: " << std::boolalpha << std::has_virtual_destructor<T>::value << std::endl;
}

class Suitable
{
public:
    Suitable(auto const v) : value(v) {};
    ~Suitable() = default;
    auto hash() const
    {
        return static_cast<long>(value);
    }
    auto toString() const
    {
        return std::to_string(value);
    }
private:
    int value;
};

int main()
{
    Suitable test(777);

    checkConcept(test);

    return 0;
}
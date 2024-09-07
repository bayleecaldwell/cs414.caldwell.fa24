#include <functional>
#include <unordered_map>

class CaseOf {
public:
    template<typename T>
    CaseOf(T value, const std::unordered_map<T, std::function<std::string()>>& cases, const std::function<std::string()>& defaultCase)
        : value_(value), cases_(cases), defaultCase_(defaultCase) {}

    std::string evaluate() const {
        auto it = cases_.find(value_);
        if (it != cases_.end()) {
            return it->second();
        } else {
            return defaultCase_();
        }
    }

private:
    const int value_;
    const std::unordered_map<int, std::function<std::string()>>& cases_;
    const std::function<std::string()>& defaultCase_;
};

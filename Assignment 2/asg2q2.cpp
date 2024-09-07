#include <functional>
#include <unordered_map>
#include <string>

class Object {
public:
    std::string caseOf(const std::unordered_map<int, std::function<std::string()>>& cases, const std::function<std::string()>& defaultCase) {
        auto it = cases.find(value_);
        if (it != cases.end()) {
            return it->second();
        } else {
            return defaultCase();
        }
    }

    void setValue(int value) {
        value_ = value;
    }

private:
    int value_;
};

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

const unsigned int BASE = 10;

const unsigned int k = static_cast<unsigned int>((log(BASE - 1) / log(10))) + 1;

struct bigint {
private:
    std::vector<int> digits;

public:
    bigint(unsigned int src = 0) {
        while (src > 0) {
            digits.push_back(src % BASE);
            src /= BASE;
        }
    }

    explicit bigint(std::string src) {
        int tmp = 0;
        while (src[tmp] == '0') {
            tmp++;
        }
        if (tmp == static_cast<int>(src.size())) {
            return;
        }
        src = src.substr(tmp, src.size());
        while (static_cast<int>(src.size()) > k) {
            digits.push_back(stoi(src.substr(src.size() - k)));
            src.erase(src.size() - k);
        }
        if (!(src.empty())) {
            digits.push_back(stoi(src));
        }
    }

    [[nodiscard]] std::string to_string() const {
        if (digits.empty()) {
            return "0";
        }
        std::string line = std::to_string(digits.back());
        for (int i = static_cast<int>(digits.size()) - 2; i >= 0; i--) {
            std::string digit = std::to_string(digits[i]);
            for (int j = 0; j < k - static_cast<int>(digit.size()); j++) {
                line.push_back('0');
            }
            line += digit;
        }
        return line;
    }

    explicit operator unsigned int() const {
        unsigned int answer = 0;
        for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--) {
            answer = answer * BASE + static_cast<unsigned int>(digits[i]);
        }
        return answer;
    }

    static int compare(const bigint &a, const bigint &b) {
        if (a.digits.size() < b.digits.size()) {
            return -1;
        } else if (a.digits.size() > b.digits.size()) {
            return 1;
        } else {
            for (int i = static_cast<int>(a.digits.size()) - 1; i >= 0; i--) {
                if (a.digits[i] > b.digits[i]) {
                    return 1;
                } else if (a.digits[i] < b.digits[i]) {
                    return -1;
                }
            }
            return 0;
        }
    }

    friend bool operator==(const bigint &a, const bigint &b) {
        return compare(a, b) == 0;
    }

    friend bool operator!=(const bigint &a, const bigint &b) {
        return (!(a == b));
    }

    friend bool operator<(const bigint &a, const bigint &b) {
        return compare(a, b) == -1;
    }

    friend bool operator>(const bigint &a, const bigint &b) {
        return compare(a, b) == 1;
    }

    friend bool operator<=(const bigint &a, const bigint &b) {
        return !(a > b);
    }

    friend bool operator>=(const bigint &a, const bigint &b) {
        return !(a < b);
    }

    bigint &operator+=(bigint b) {
        int i = 0;
        int remains = 0;
        while (i < static_cast<int>(digits.size()) &&
               i < static_cast<int>(b.digits.size())) {
            digits[i] += b.digits[i] + remains;
            remains = digits[i] / BASE;
            digits[i++] %= BASE;
        }
        while (i < static_cast<int>(digits.size())) {
            digits[i] += remains;
            remains = digits[i] / BASE;
            digits[i++] %= BASE;
        }
        while (i < static_cast<int>(b.digits.size())) {
            b.digits[i] += remains;
            remains = b.digits[i] / BASE;
            digits.push_back(b.digits[i++] % BASE);
        }
        while (remains > 0) {
            digits.push_back(remains % BASE);
            remains /= BASE;
        }
        return *this;
    }

    friend bigint operator+(bigint a, const bigint &b) {
        return a += b;
    }

    bigint &operator-=(bigint b) {
        int i = 0;
        int taken = 0;
        while (i < static_cast<int>(digits.size()) &&
               i < static_cast<int>(b.digits.size())) {
            digits[i] = digits[i] - taken - b.digits[i];
            if (digits[i] < 0) {
                taken = 1;
                digits[i] += BASE;
            } else {
                taken = 0;
            }
            i++;
        }
        while (i < static_cast<int>(digits.size()) && taken > 0) {
            digits[i] -= taken;
            if (digits[i] < 0) {
                digits[i++] += BASE;
                taken = 1;
            } else {
                taken = 0;
            }
        }
        while (!digits.empty() && digits.back() == 0) {
            digits.pop_back();
        }
        return *this;
    }

    friend bigint operator-(bigint a, const bigint &b) {
        return a -= b;
    }
};
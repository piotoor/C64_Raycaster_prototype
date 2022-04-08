#ifndef TESTCUSTOMDEFINITIONS_H
#define TESTCUSTOMDEFINITIONS_H
#include "gtest/gtest.h"
#include <vector>
#include <numeric>

namespace testDataGenerators {
    template<class T1, class T2>
    std::vector<std::tuple<T1, T2>> combine2VectorsCartesian(std::vector<T1> v1, std::vector<T2> v2) {
        std::vector<std::tuple<T1, T2>> ans;

        for (const auto &x: v1) {
            for (const auto &y: v2) {
                ans.emplace_back(x, y);
            }
        }

        return ans;
    }

    template<class T1, class T2>
    std::vector<std::tuple<T1, T2>> combine2VectorsLinear(std::vector<T1> v1, std::vector<T2> v2) {
        std::vector<std::tuple<T1, T2>> ans;

        for (size_t i = 0; i < std::min({v1.size(), v2.size()}); ++i) {
            ans.emplace_back(v1[i], v2[i]);
        }

        return ans;
    }

    template<class T1, class T2, class T3>
    std::vector<std::tuple<T1, T2, T3>> combineTwoVectorsCartesianCombineThirdLinear(std::vector<T1> v1, std::vector<T2> v2, std::vector<T3> v3) {
        std::vector<std::tuple<T1, T2, T3>> ans;

        size_t v3_ind = 0;
        for (const auto &x: v1) {
            for (const auto &y: v2) {
                ans.emplace_back(x, y, v3[v3_ind++]);
            }
        }

        return ans;
    }

    template<class T>
    std::vector<T> vectorIota(size_t n, T value) {
        std::vector<T> ans(n);
        std::iota(begin(ans), end(ans), value);
        return ans;
    }

    template<class T>
    std::vector<T> vectorsConcat(const std::vector<T> &a, const std::vector<T> &b) {
        auto ans = a;

        std::copy(begin(b),
                  end(b),
                  back_inserter(ans));

        return ans;
    }
}

namespace testCustomAsserts {
    template <class T1, class T2>
    testing::AssertionResult AssertEqOct(const char* a_expr,
                                         const char* b_expr,
                                         T1 a,
                                         T2 b) {
        if (a == b) {
            return testing::AssertionSuccess();
        }
        std::stringstream ss;
        ss  << "Expected equality of these values:\n"
            << "\t" << a_expr << "\n"
            << "\t\t" << "Which is: " << std::oct << a << "\n"
            << "\t" << b_expr << "\n"
            << "\t\t" << "Which is: " << std::oct << b;

        return testing::AssertionFailure() << ss.str();
    }
}

#endif

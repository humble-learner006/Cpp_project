#include <iostream>
#include <iomanip>

int hypergeometric(int N, int K, int n, int k);
void printTable();
int binomial(int n, int k);
// N: 总体的大小。_N
// K: 总体中成功的个数。_Ni
// n: 抽取的样本大小。_n
// k: 样本中成功的个数。k
int hypergeometric(int N, int K, int n, int k) {
    if (k > n || k > K || n > N) {
        return 0;
    }
    if (k == 0 || n == 0) {
        return 1;
    }
    return (hypergeometric(N - 1, K - 1, n - 1, k - 1) + hypergeometric(N - 1, K, n, k - 1));
}

void printTable() {
    // 表头
    std::cout << std::setw(15) << " " << std::setw(10) << "a" << std::setw(10) << "b" << std::setw(10) << "c" << std::endl;
    
    // hypergeometric 行
    std::cout << std::setw(15) << "hypergeometric";
    std::cout << std::setw(10) << hypergeometric(10, 5, 5, 2); // 示例值
    std::cout << std::setw(10) << hypergeometric(10, 5, 5, 3); // 示例值
    std::cout << std::setw(10) << hypergeometric(10, 5, 5, 4); // 示例值
    std::cout << std::endl;

    // binomial 行
    std::cout << std::setw(15) << "binomial";
    std::cout << std::setw(10) << binomial(5, 2); // 示例值
    std::cout << std::setw(10) << binomial(5, 3); // 示例值
    std::cout << std::setw(10) << binomial(5, 4); // 示例值
    std::cout << std::endl;
}

int binomial(int n, int k) {
    if (k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    return binomial(n - 1, k - 1) + binomial(n - 1, k);
}


int main() {
    std::cout << "Hypergeometric Distribution Table:" << std::endl;
    printTable();
    return 0;
}
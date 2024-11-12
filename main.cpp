#include "Matrix.h"
#include <cassert>


int main()
{   

    Matrix<int, -1> matrix;
    assert(matrix.size() == 0); // все ячейки пустые

    auto a = matrix(0, 0);
    assert(a == -1);
    assert(matrix.size() == 0);


    for (int i = 0; i < 10; ++i) {
        matrix(i, i) = i;
    }

    for (int i = 0, j = 9; i < 10; ++i, --j) {
        matrix(i, j) = j;
    }

    std::pair<size_t, size_t> m_start = {1,1};
    std::pair<size_t, size_t> m_end = {8,8};
    matrix.print(m_start, m_end);

    std::cout << matrix.size() << std::endl;

    for(const auto& cell: matrix)
    {
        size_t x;
        size_t y;
        int value;
        std::tie(x, y, value) = cell;
        std::cout << "["<< x << "," << y <<"] = " << value << std::endl;
    }    

    assert(matrix.size() == 18);    

    return 0;
}

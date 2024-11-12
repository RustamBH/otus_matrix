#pragma once
#include <memory>
#include <map>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <tuple>


template <class T, T default_value>
class Matrix;

template <class T>
class iterator;

template <class T, T default_value>
class Matrix
{
public:
    using cell_t = std::pair <size_t, size_t>;
    using Mtrx_Iterator = typename std::map<cell_t, T>::iterator;    

public:
    Matrix() : row_index(-1), col_index(-1){};
    

    class iterator
    {
    public:
        iterator() {}

        iterator (typename std::map<cell_t, T>::iterator Iterator)
        {
            iterator_ = Iterator;
        };

        iterator& operator++()
        {
            ++iterator_;
            return *this;
        }

        bool operator==(const iterator& rhs) const
        {
            return iterator_ == rhs.iterator_;
        }

        bool operator!=(const iterator& rhs) const
        {
            return iterator_ != rhs.iterator_;
        }

        std::tuple<size_t, size_t, T> operator*() const
        {
            return std::make_tuple(iterator_->first.first, iterator_->first.second, iterator_->second);
        }

    private:        
        Mtrx_Iterator iterator_;
    };

    iterator begin()
    {
        return iterator(data.begin());
    }

    iterator end()
    {
        return iterator(data.end());        
    }

    size_t size()
    {
        DeleteDefaultValues();
        return data.size();
    }

    const T operator() (size_t row, size_t col) const
    {
        auto m_pair = std::make_pair(row, col);
        try {
            return data.at(m_pair);
        }
        catch (std::out_of_range&) {}
        return default_value;
    }

    T& operator() (size_t row, size_t col)
    {
        auto m_pair = std::make_pair(row, col);
        m_pair_ = m_pair;
        data[m_pair] = default_value;
        return data[m_pair];
    }

    Matrix& operator=(const T& value) // оператор присваивания
    {        
        this->data[m_pair_] = value;
        return *this;
    }

    void print(cell_t& from, cell_t& to) const
    {
        if (to.first < from.first || to.second < from.second) {
            throw std::logic_error ("The second cell less then first");
        }

        for (size_t i = from.first; i <= to.first; ++i) {
            for (size_t j = from.second; j <= to.second; ++j) {
                std::cout << this->operator()(i, j) << ' ';
            }
            std::cout << std::endl;
        }
    }

    friend std::ostream& operator<< (std::ostream& out, const Matrix& matrix)
    {
        for (size_t i = 0; i <= matrix.row_index; ++i) {
            for (size_t j = 0; j <= matrix.col_index; ++j) {
                out << matrix(i, j) << ' ';
            }
            out << std::endl;
        }
        return out;
    }

    void DeleteDefaultValues()
    {
        std::vector <cell_t> CellsToDelete;

        for (const auto &m_pair : data) {
            if (m_pair.second == default_value || m_pair.second == 0) {
                const auto& m_cell = m_pair.first;
                CellsToDelete.push_back(m_cell);
            }
        }

        for (const auto& Cell : CellsToDelete) {
            data.erase(Cell);
        }
    }

private:
    cell_t m_pair_;
    std::map <cell_t, T> data;
    size_t row_index;
    size_t col_index;
};

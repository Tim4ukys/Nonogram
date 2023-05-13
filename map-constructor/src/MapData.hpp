//
// Created by tim4ukys on 13.05.2023.
//
#ifndef __MAPDATA_HPP__
#define __MAPDATA_HPP__

#include <cstddef>
#include <string_view>
#include <fstream>
#include <vector>
#include <memory.h>
#include <exception>

class MapData {
    bool* m_pData = nullptr;
    int m_nLenData{ 2 };

public:
    inline void Release() { delete[] m_pData; m_pData = nullptr; }
    inline void Create() { 
        if (m_pData) Release();
        m_pData = new bool[m_nLenData*m_nLenData]{false}; 
    }

    explicit MapData() {
        Create();
    }
    ~MapData() {
        Release();
    }
    
    inline auto& operator[](const size_t& i) noexcept { return m_pData[i]; }
    inline auto& getData() noexcept { return m_pData; };
    inline auto& getLenData() noexcept { return m_nLenData; }

    inline void saveDataToFile(const std::string_view& fileName) {
        std::ofstream file{fileName.data()};
    
        for (size_t y{}; y < m_nLenData; ++y) {
            for (size_t x{}; x < m_nLenData; ++x) {
                file << (m_pData[y*m_nLenData + x] ? 'X' : 'O');
            }
            if (y+1 < m_nLenData) file << "\n";
        }
    }
    inline void loadDataFromFile(const std::string_view& fileName) {
        std::ifstream file{fileName.data()};
        m_nLenData = 0;
        
        bool isEnded{};
        bool* ln{};
        char s;
        do {
            file >> std::noskipws >> s;
            if (s == '\r') continue;
            else if (s == '\n') break;

            // ln.push_back(s == 'X');
            ln = reinterpret_cast<bool*>(++m_nLenData ? realloc(ln, m_nLenData * sizeof(bool)) : malloc(sizeof(bool)));
            ln[m_nLenData-1] = s == 'X';
        } while (file);

        Create();
        memcpy(m_pData, ln, m_nLenData*sizeof(bool));
        free(ln); 
        ln = nullptr;

        for (int i{m_nLenData}; i < m_nLenData*m_nLenData; ++i) {
            if (!file) throw std::runtime_error("Dalboyob, file sloman!!!");
            else if (file >> s; s == '\r' || s == '\n') {
                --i;
                continue;
            }

            m_pData[i] = s == 'X';
        }
    }
};

#endif
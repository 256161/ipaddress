#include <cassert>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using std::pair;

bool comp(std::vector<std::string> &lipStr, std::vector<std::string> &ripStr) {
  bool result = false;
  int count = 0;
  while (count != 4) {
    int lip = std::stoi(lipStr[count]);
    int rip = std::stoi(ripStr[count]);
    if (lip < rip) {
      return false;
    }
    if (lip > rip)
      return true;
    count++;
  }

  return result;
}
void inputIpPool(const std::vector<std::vector<std::string> > &ip_pool) {
    for(std::vector<std::vector<std::string> >::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            
            for(std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }
}

std::vector<std::vector<std::string> > filter(std::map<int, std::string> pos, const std::vector<std::vector<std::string> > &vectorFilter)
{
    std::vector<std::vector<std::string> > result;
    for (std::vector<std::string> ip : vectorFilter){

      for (const pair<const int, std::string> &position : pos) {
        if (ip[position.first] == position.second){
            result.push_back(ip);
            break;
        }
      }
    }
    return result;
}

std::vector<std::vector<std::string> > filter_any(int number, const std::vector<std::vector<std::string> > &vectorFilter)
{
    std::vector<std::vector<std::string> > result;
    for (std::vector<std::string> ip : vectorFilter){
        int it = 0;
        while (it < 4){
            if (std::stoi(ip[it]) == number)
            {
                result.push_back(ip);
                break;
            }
        it++;
        }
    }
    return result;
}

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;
    std::string::size_type start = 0; 
    std::string::size_type stop = str.find_first_of(d); 
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);

    }

    r.push_back(str.substr(start));
    return r;
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            if (line == "Fil") break;
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
            
        }

        // TODO reverse lexicographically sort
        std::cout << "Sort start \n" ;
        std::sort(ip_pool.begin(), ip_pool.end(), comp);
        std::reverse(ip_pool.begin(), ip_pool.end());
        std::cout << "Sort end \n";


        std::cout << "Вывод работы алгоритма после сортировки\n ";
        inputIpPool(ip_pool);

        std::map<int, std::string> pos1;
        pos1[0]="1";
        std::cout << "Вывод работы алгоритма с 1 в начале\n ";
        inputIpPool(filter(pos1, ip_pool));

        std::map<int, std::string> pos2;
        pos2[0]="46";
        pos2[1]="70";
        std::cout << "Вывод работы алгоритма с 46 на первой позиции и с 70 на второй позиции в начале\n ";
        inputIpPool(filter(pos2, ip_pool));
        std::cout << "Вывод работы алгоритма с 46 на любом месте\n ";

        inputIpPool(filter_any(46, ip_pool));

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
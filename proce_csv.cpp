#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <filesystem>
#include <iterator>
void get_file_name(const std::string&, std::vector<std::string>&);
void open_proc_data(const std::string&, int, std::string);

int main() {
    int flag{ 0 };
    
    std::vector<std::string>file_name_vec;
    get_file_name("./csvin/",file_name_vec);
    std::string file_addr{ "./csvin/" };
    auto name_iter = file_name_vec.begin();
    while (name_iter!= file_name_vec.end())
    {
        open_proc_data(file_addr, flag,*name_iter);
        ++name_iter;
    }
    

    return 0;
}
void open_proc_data(const std::string& file_addr,int tem_flag, std::string file_name) {
    std::string this_line_str{};
    std::ifstream fin;
    fin.open(file_addr+ file_name);
    std::ofstream outfile;
    std::string file_addr_out{ "./" };
    std::string out_addr_all = file_addr_out + "_" + file_name ;
    outfile.open(out_addr_all, std::ios::trunc | std::ios::out);

    while (std::getline(fin, this_line_str))
    {
        if (!this_line_str.empty()) {
            if (this_line_str[0] == '1') {
                tem_flag = 1;
            }
            if (tem_flag == 1) {
                std::cout << this_line_str << std::endl;
                outfile << this_line_str << std::endl;
            }
        }
        
    }
    fin.close();
    outfile.close();
    return;
}
void get_file_name(const std::string&file_addr, std::vector<std::string>&vec) {
    std::filesystem::path file_str{ file_addr };
    if (!std::filesystem::exists(file_str))  std::cout << "该目录不存在" << std::endl;
    std::filesystem::directory_iterator list{ file_str };
    for (auto& it : list) {
        std::cout << it.path().filename() << std::endl;
        vec.push_back(it.path().filename().generic_string());
    }
}

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

//平面间两点间距
constexpr auto SINGLEPOINT = 200;
//Z方向的递增高度
constexpr auto Z_SINGLE_HIGHT = 100;
//Z方向的总高度
constexpr auto Z_HIGHT =5000;

std::vector<std::string>b{};
void succ(std::fstream&, double, double, double, double, double);
int main()
{
    
	std::fstream myfile;
	myfile.open("./Data.txt", std::fstream::out);
	double z_ = 0.0;
	while (z_ <= Z_HIGHT) {
		std::cout << "正在生成数据，当前高度为 " << z_<<" nm" << std::endl;
		succ(myfile, 20000, 5000, -62500, -2500, z_);
		succ(myfile, 5000, 70000, -42500, -35000, z_);
		succ(myfile, 67000, 5000, -37500, 25000, z_);
		succ(myfile, 67000, 5000, -29500, 14000, z_);
		succ(myfile, 67000, 5000, -37500, 3000, z_);
		succ(myfile, 67000, 5000, -29500, -7900, z_);
		succ(myfile, 67000, 5000, -37500, -19000, z_);
		succ(myfile, 67000, 5000, -29500, -30000, z_);
		succ(myfile, 5000, 70000, 37500, -35000, z_);
		succ(myfile, 20000, 5000, 42500, -2500, z_);
		std::cout << "高度为 " << z_ << " nm 数据生成完毕！" << std::endl;
		z_ = z_ + Z_SINGLE_HIGHT;
	}
	myfile.close();
    return 0;
}
void succ(std::fstream& outFile,double level_x, double vertical_y, double left_down_x,
    double left_down_y, double z_) {
	bool flag = true;
	int i_x = 0;
	int i_y = 0;
	int i_x_cout = level_x / SINGLEPOINT;
	int i_y_cout = vertical_y / SINGLEPOINT;
	std::string my_str{};
	const char* my_char{};
	while (i_x <= i_x_cout) {
		if (flag) {
			while (i_y <= i_y_cout) {
				my_str.append(std::to_string(left_down_x + i_x * SINGLEPOINT) + ","
					+ std::to_string(left_down_y + i_y * SINGLEPOINT) + "," + std::to_string(z_) + "\n");
				b.push_back(my_str);
				++i_y;
			}
			for (const auto& e : b) outFile << e;
			b.clear();
			my_str = "";
			i_y = 0;
			flag = false;
			++i_x;
		}
		else {
			while (i_y <= i_y_cout) {
				my_str.append(std::to_string(left_down_x + i_x * SINGLEPOINT) + ","
					+ std::to_string(left_down_y + vertical_y - i_y * SINGLEPOINT) + "," + std::to_string(z_) + "\n");
				b.push_back(my_str);
				++i_y;
			}
			for (const auto& e : b) outFile << e;
			b.clear();
			my_str = "";
			flag = true;
		    i_y = 0;
			++i_x;
        }
    }

}
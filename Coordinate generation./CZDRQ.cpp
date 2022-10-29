#include <vector>
#include <fstream>
#include <string>
#include <fstream>

/*******加工的两点间隔********/
constexpr auto SINGLEPOINT = 5;
/*******Z方向步进高度********/
constexpr auto Z_SINGLE_HIGHT = 5;
/*******Z方向总高度********/
constexpr auto Z_HIGHT = 5;



constexpr auto Z_COUNT = Z_HIGHT/ Z_SINGLE_HIGHT ;
//生成叉指电极
void Generate_coor(std::fstream&,double, double, double, double,double);

int main() {
	std::fstream file;
	//打开同级文件夹的Data.txt文件，如果没有则创建
	file.open("./Data.txt", std::fstream::out);

	/*
	函数其实是在画方块
	Generate_coor(file, 101, 102, -21, -22, z_);
	需要修改的参数
	101：方块的水平长度
	102：方块的竖直长度
	-21：左下角X坐标
	-22：左下角Y坐标
	以上都可以是小数和负数
	写几个函数，画几个方块，按出现顺序加工，一层一层加工
	*/
	for (int z_ = 0; z_ <= Z_COUNT; z_ += Z_SINGLE_HIGHT) {
		Generate_coor(file, 100, 100, -20, -20.0, z_);
		Generate_coor(file, 800, 1000, -50, -70.0, z_);
	}

}
void Generate_coor(std::fstream& myfile, double level_x, double vertical_y, double left_down_x,
	double left_down_y, double z_h) {
	std::string temp_str = "";
	bool flag = true;
	int i_x = 0;
	int i_y = 0;
	int i_x_cout = level_x / SINGLEPOINT;
	int i_y_cout = vertical_y / SINGLEPOINT;
	while (i_x <= i_x_cout) {
		if (flag) {
			while (i_y <= i_y_cout) {
				temp_str = std::to_string(left_down_x + i_x * SINGLEPOINT) + "," +
					std::to_string(left_down_y + i_y * SINGLEPOINT) + "," +
					std::to_string(z_h);
				    myfile << temp_str << std::endl;
					++i_y;
					temp_str = "";
			}
			flag = false;
		}
		else {
			while (i_y <= i_y_cout) {
				temp_str = std::to_string(left_down_x + i_x * SINGLEPOINT) + "," +
					std::to_string(left_down_y+ vertical_y - i_y * SINGLEPOINT) + "," +
					std::to_string(z_h);
				myfile << temp_str << std::endl;
				++i_y;
				temp_str = "";
			}
			flag = true;
		}
		++i_x;
		i_y = 0;
	}
	return;
}

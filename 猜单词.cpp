#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>
#include "map"
#include "random"

std::map<std::string,std::string> h;

void loadtxt(){
    std::wifstream file("/Users/huchi/CLionProjects/untitled11/ky.txt");
    file.imbue(std::locale(""));
    if (!file.is_open()) {
        std::cerr << "Unable to open the file." << std::endl;
        return ;
    }

    std::wstring line;

    while (std::getline(file, line)) {
        // 处理line，这里line是宽字符串
        // 你可以将宽字符串转换为多字节字符串（UTF-8）进行后续处理
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string utf8_line = converter.to_bytes(line);
        std::string eng;
        int j = 0;
        for(int i = 0; i < utf8_line.size(); i++){
            if(utf8_line[i] == ' '){
                j = i;
                while(utf8_line[j]==' ') j++;
                j--;
                break;
            }else{
                eng += utf8_line[i];
            }
        }
        std::string hz = utf8_line.substr(j + 1,utf8_line.size() - j);
        h[eng] = hz;
//        std::cout<< hz<<std::endl;
    };
}
int main() {
    loadtxt();
//    for(auto [x,y]:h){
//        std::cout<<x<<std::endl;
//        break;
//    }
    int t;
    std::cout << "输入你想检测的数量：\n";
    std::cin >> t;
    while(t--){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<std::size_t> dist(0, h.size() - 1);

        // Randomly select a word
        std::size_t randomIndex = dist(gen);
        auto it = h.begin();
        std::advance(it, randomIndex);
        std::string randomWord = it->first;
        std::string correctMeaning = h[randomWord];
        // Prompt the user to guess the meaning
        std::cout << "什么意思 : " << randomWord << std::endl;
        std::string userGuess;
        std::cin >> userGuess;

        // Check if the user's guess is correct
        if (correctMeaning.find(userGuess)!=-1) {
            std::cout << " 正确！ " << randomWord << "' is '" << correctMeaning << "'." << std::endl;
        } else {
            std::cout << " 错误 ！\n你否需要提示？（输入1 or 0)" << std::endl;
            int k;
            std::cin >> k;
            if(k){
                int i;
                for(i = 0; i < correctMeaning.size();i++){
                    if(correctMeaning[i] != ' ' && (correctMeaning[i] < 'a' || correctMeaning[i] > 'z')){
                        break;
                    }
                }
                std::cout << "提示此为： "<< correctMeaning.substr(i+2,4) <<'\n';
                std::string ss;
                std::cin >> ss;
                if(correctMeaning.find(ss)!=-1) {
                    std::cout<<"正确！" << correctMeaning << '\n';
                }else{
                    std::cout <<"正确答案为： " << correctMeaning <<'\n';
                }
            }else{
                std::cout <<"正确答案为： " << correctMeaning <<'\n';
            }

        }
    }
    return 0;
}

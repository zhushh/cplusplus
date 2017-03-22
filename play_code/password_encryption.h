#include <iostream>
#include <string>
using std::string;
 
class Encryption {
    private:
        string encodePas;//加密后的字符串
        string addSalt(string pas) //为密码混入盐值，并返回该值
        {
            pas.push_back('0');
            pas.insert(0, "0");
            for (size_t i = 0; i < pas.length(); i++) {
                pas[i] += i;
            }
            return pas;
        }
        string encode(string pasWithSalt) //加密混入盐值的密码，并返回该值
        {
            pasWithSalt.erase(pasWithSalt.end() - 1);
            for (size_t i = 1; i < pasWithSalt.length(); i++) {
                pasWithSalt[i] -= i;
            }
            pasWithSalt.erase(pasWithSalt.begin());
            return pasWithSalt;
        }
    public:
        Encryption(string pas) //pas为原始密码，你需要在初始化的时候为其进行加密并存放在encodePas
        {
            encodePas = addSalt(pas);
        }
        bool isEq(string pas) //pas为原始密码，你必须提供这样的方法让用户登录的时候可以判断其密码跟加密后的密码是一致的
        {
            if (encode(encodePas) == pas) {
                return true;
            } else {
                return false;
            }
        }
        string getEncodePas() const //获得加密后的字符串
        {
            return encodePas;
        }
};


//
// Created by Xin Pan on 2021/5/18.
//

#ifndef PSTRING_STRUTIL_H
#define PSTRING_STRUTIL_H

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <type_traits>
#include <locale>

/// 重复string，类似于python的str * n
/// \param str 输入string
/// \param times 重复次数
/// \return 重复times次后的string
std::string operator*(const std::string& str, int times){
    std::string temp;
    for(int i = 0; i < times; i++){
        temp+=str;
    }
    return temp;
}

/// 两个string的长度做比较，如果str1小于str2，返回true
/// \param str1 left hand side string
/// \param str2 right hand side string
/// \return 返回一个boolean值
inline bool operator<(const std::string& str1, const std::string& str2){
    return str1.size() < str2.size();
}

/// 两个string的长度做比较，如果str1大于str2，返回true
/// \param str1 left hand side string
/// \param str2 right hand side string
/// \return 返回一个boolean值
inline bool operator>(const std::string& str1, const std::string& str2){
    return str1.size() > str2.size();
}

/// 两个string的长度做比较，如果str1等于str2，返回true
/// \param str1 left hand side string
/// \param str2 right hand side string
/// \return 返回一个boolean值
inline bool operator==(const std::string& str1, const std::string& str2){
    return str1.size() == str2.size();
}


///常用string manipulation的函数。
namespace strutils {

/// 将两个string结合起来，等于str1+str2
/// \param str1 第一个string
/// \param str2 第二个string
/// \return 结合后的string
inline std::string concatenate(const std::string& str1, const std::string& str2){
    return str1 + str2;
}

/// 重复string，类似于python的str * n，等于str*times
/// \param str 输入string
/// \param times 重复次数
/// \return 重复times次后的string
inline std::string repeated(const std::string& str, int times){
    return str*times;
}

/// 将输入string倒序后返回输出
/// \param str 输入string
/// \return 倒序后的string
inline std::string reverse(const std::string& str){
    std::string temp;
    temp.reserve(str.size());
    for(auto iter = str.rbegin(); iter != str.rend(); iter++){
        temp.push_back(*iter);
    }
    return temp;
}

/// 将string以特定标志切分，返回的是string
/// \param str 输入string
/// \param sep 切分标志
/// \return 切分后的string vector
/// @see splitView
inline std::vector<std::string> split(const std::string &str, const char& sep) {
    std::vector<std::string> temp_vec;
    std::string temp_str;
    std::stringstream ss(str);
    while (std::getline(ss, temp_str, sep)) {
        temp_vec.push_back(temp_str);
    }
    return temp_vec;
}

/// 将string以特定标志切分，返回的是string_view
/// \param str 输入string
/// \param sep 切分标志
/// \return 切分后的string vector
/// @see split
inline std::vector<std::string_view> splitView(const std::string& str, const char& sep){
    std::vector<std::string_view> temp;
    /// TODO implementation
    return temp;
}


/// 将一堆字符串以某个特定的标志结合起来
/// \param vec 输入的一堆字符串, vector<string>
/// \param sep 分隔符
/// \return 结合后的输出字符串
inline std::string join(const std::vector<std::string>& vec, const char& sep){
    std::string temp;
    for(auto iter = vec.cbegin(); iter != vec.cend()-1; iter++){
        temp += *iter;
        temp += sep;
    }
    temp.append(*(vec.rbegin()));
    return temp;
}

/// 将输入字符串的头尾的空格去除
/// \param str 输入字符串
/// \return 去除头尾空格后的字符串
inline std::string strip(const std::string &str) {
    decltype(str.begin()) f_iter;
    decltype(str.begin()) b_iter;
    for (f_iter = str.begin(); f_iter != str.end(); f_iter++) {
        if (*f_iter != ' ') break;
    }
    for (b_iter = str.end() - 1; b_iter != str.begin(); b_iter--) {
        if (*b_iter != ' ') break;
    }
    return std::string(f_iter, b_iter + 1);
}

/// 将一堆字符串标上序号构成一个map，类似于python的enumerate(list)->dict
/// \param src 输入的vector of string
/// \return 输出的map<int, string>
/// ```c++
/// auto res = enumerate({"str1", "str2"});
/// //res -> {{0 : "str1"}, {1: "str2"}}
/// ```
inline std::map<int, std::string> enumerate(const std::vector<std::string> &src) {
    std::map<int, std::string> temp_map;
    for (int i = 0; i < src.size(); i++) {
        temp_map.insert({i, src[i]});
    }
    return temp_map;
}

/// 将字符串转化为数字
/// \tparam T 数字类型
/// \param src 输入字符串
/// \return 返回的数字
/// @warning 如果输入的字符串里面除了数字还有别的字符，那可能是未定义行为
///
/// @code
/// auto ret = to_number<double>("3.1415");
/// std::cout << ret << std::endl;
/// @endcode
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type inline
to_number(const std::string &src) {
    T num;
    std::stringstream ss(src);
    ss >> num;
    return num;
}

/// 将字符串长度为len的尾端字符去除
/// \param in_out 输入输出的字符串
/// \param len 去除字符串的长度
inline void chop(std::string& in_out, int len){
    auto size = in_out.size();
    if(len > size){
        in_out.clear();
        return;
    }
    in_out.erase(in_out.begin()+size-len, in_out.end());
}

/// 将字符串长度为len的尾端字符去除
/// \param src 输入的字符串
/// \param len 去除字符串的长度
/// \return 输出的字符串
inline std::string chopped(const std::string& src, int len){
    if(len > src.size()){
        return "";
    }else{
        return std::string(src.begin(), src.begin()+src.size()-len);
    }
}


/// 将输入字符串转为小写
/// \param str 输入字符串
/// \return 返回的小写的字符串
inline std::string to_lower(const std::string& str){
    std::string temp;
    temp.reserve(str.size());
    for(const auto& c : str){
        temp.push_back(std::tolower(c, std::locale()));
    }
    return temp;
}


/// 将输入字符串转为大写
/// \param str 输入字符串
/// \return 返回的大写的字符串
inline std::string to_upper(const std::string& str){
    std::string temp;
    temp.reserve(str.size());
    for(const auto& c : str){
        temp.push_back(std::toupper(c, std::locale()));
    }
    return temp;
}

/// 将字符转为小写
/// \param c 输入字符
/// \return 输出的小写的字符
inline char to_lower(const char& c){
    return std::tolower(c, std::locale());
}

/// 将字符转为大写
/// \param c 输入字符
/// \return 输出的大写的字符
inline char to_upper(const char& c){
    return std::toupper(c, std::locale());
}

/// 将字符串中每个词的首字母大写，其余字母小写
/// \param str 输入的字符串
/// \return 输出的字符串
inline std::string capitalize(const std::string& str){
    auto vec = split(str, ' ');
    for(auto& i : vec){
        if(!i.empty()){
            i = to_lower(i);
            i[0] = to_upper(i[0]);
        }
    }
    return join(vec, ' ');
}

/// 取字符串左边开始的len个字符，返回新的字符串
/// \param str 输入字符串
/// \param len 保留长度
/// \return 输出字符串
/// @see leftView
inline std::string left(const std::string& str, int len){
    if(len > str.size()){
        return str;
    }else{
        return std::string(str.begin(), str.begin()+len);
    }
}

/// 取字符串左边开始的len个字符，返回一个string_view
/// \param str 输入字符串
/// \param len 保留长度
/// \return 输出string_view
/// @see left
inline std::string_view leftView(const std::string& str, int len){
    if(len > str.size()){
        return std::string_view(str.data());
    }else{
        return std::string_view(str.data()).substr(0,len);
    }
}

/// 取字符串右边开始的len个字符，返回一个新的string
/// \param str 输入字符串
/// \param len 保留长度
/// \return 输出新的字符串
/// @see rightView
inline std::string right(const std::string& str, int len){
    if(len > str.size()){
        return str;
    }else{
        return std::string(str.end() - len, str.end());
    }
}

/// 取字符串右边开始的len个字符，返回一个string_view
/// \param str 输入字符串
/// \param len 保留长度
/// \return 输出string_view
/// @see right
inline std::string_view rightView(const std::string& str, int len){
    if(len > str.size()){
        return std::string_view(str.data());
    }else{
        return std::string_view(str.data()).substr(str.size()-len);
    }
}

/// Returns a string that contains n characters of this string, starting at the specified position index.
///
/// Returns a null string if the position index exceeds the length of the string.
/// If there are less than n characters available in the string starting at the given position,
/// or if n is -1 (default), the function returns all characters that are available from the specified position.
/// \param str input string
/// \param pos start position
/// \param n size of the returned string
/// \return a string that contains n characters of this string, starting at the specified position index.
inline std::string mid(const std::string& str, int pos, int n=-1){
    if(pos >= str.size() || pos < 0){
        return "";
    }
    if(n == -1 || n > (str.size() - pos)){
        return std::string(str.begin()+pos, str.end());
    }
    return std::string(str.begin()+pos, str.begin()+pos+n);
}


/// Returns a substring reference to n characters of this string, starting at the specified position.
///
/// If the position exceeds the length of the string, a null reference is returned.
///
/// If there are less than n characters available in the string, starting at the given position,
/// or if n is -1 (default), the function returns all characters from the specified position onwards.
/// \param str input string
/// \param pos start position
/// \param n size of the returned string
/// \return a string_view rather than a new string
inline std::string_view midView(const std::string& str, int pos, int n=-1){
    if(pos >= str.size() || pos < 0){
        return "";
    }
    if(n == -1 || n > (str.size() - pos)){
        return std::string_view(str.data()).substr(pos);
    }
    return std::string_view(str.data()).substr(pos, pos+n);
}

/// 一个字符串中是否包含另一个字符串
/// \param src 输入字符串
/// \param pattern 模版字符串
/// \param case_sensitive 是否区分大小写，默认为是
/// \return 返回一个boolean值
inline bool contains(const std::string& src, const std::string& pattern, bool case_sensitive=true){
    std::string temp_src, temp_pattern;
    if(case_sensitive){
        temp_src = src;
        temp_pattern = pattern;
    }else{
        temp_src = to_lower(src);
        temp_pattern = to_lower(pattern);
    }

    if(temp_src.size() < temp_pattern.size())
        return false;
    if(temp_pattern.empty() && temp_src.empty())
        return true;
    if(temp_src.empty())
        return false;

    //apply brute force string matching algorithm
    for(int i=0,j=0;i<temp_src.size()-temp_pattern.size()+1;i++)
    {
        while(temp_src[i+j]==temp_pattern[j] && j<temp_pattern.size())
        {
            j++;
        }
        if(j==temp_pattern.size())
            return i;
        else
        {
            j=0;
        }
    }
    return false;
}

/// 一个字符串中是否包含另一个字符
/// \param src 输入字符串
/// \param c 模版字符
/// \param case_sensitive 是否区分大小写，默认为是
/// \return 返回一个boolean值
inline bool contains(const std::string& src, const char& c, bool case_sensitive=true){
    if(case_sensitive){
        return std::any_of(src.begin(), src.end(), [&c](auto s){
            return c == s;
        });
    }else{
        return std::any_of(src.begin(), src.end(), [&c](auto s){
            return to_lower(c) == to_lower(s);
        });
    }
}


/// 一个字符串是否以某个pattern字符串开头
/// \param src 输入字符串
/// \param pattern 模版字符串
/// \param case_sensitive 是否区分大小写，默认是
/// \return 返回一个boolean值
inline bool startWith(const std::string& src, const std::string& pattern, bool case_sensitive=true){
    bool bRet = false;
    /// TODO implementation

    return bRet;

}

/// 一个字符串是否以某个pattern字符开头
/// \param src 输入字符串
/// \param pattern 模版字符
/// \param case_sensitive 是否区分大小写，默认是
/// \return 返回一个boolean值
inline bool startWith(const std::string& src, const char& pattern, bool case_sensitive=true){
    bool bRet = false;
    /// TODO implementation

    return bRet;
}

/// 用特定的字符填充输入的字符串
/// \param src 输入的字符串
/// \param c 特定的字符
/// \param len 输出字符串的长度，如果是-1，则保持原字符串的长度不变
inline void fill(std::string& src, const char& c, int len=-1){
    if(len < 0){
        for(auto& s : src){
            s = c;
        }
    }else{
        src.resize(len);
        for(auto& s : src){
            s = c;
        }
    }
}

/// 用特定的字符填充输入的字符串，并返回新的字符串
/// \param src 输入的字符串
/// \param c 特定的字符
/// \param len 输出字符串的长度，如果是-1，则保持原字符串的长度不变
/// \return 返回输出的字符串
inline std::string filled(const std::string& src, const char& c, int len=-1){
    std::string temp;
    if(len < 0){
        temp.reserve(src.size());
        for(int i = 0; i < src.size(); i++){
            temp.push_back(c);
        }
    }else{
        temp.reserve(len);
        for(int i = 0; i < len+1; i++){
            temp.push_back(c);
        }
    }
    return temp;
}

}
#endif //PSTRING_STRUTIL_H

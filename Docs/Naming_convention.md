# Naming_convention (命名规范)
## reference
[google opensource stylisitc manual中文](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming.html)
[English version](https://github.com/google/styleguide?tab=readme-ov-file)
## Filename
```
my_useful_class.cpp //全部小写，中间用下划线链接
header.h
folders use Start with capitcal letter, and use underscore to separate words.
```

```
/*in google use .cc as suffix, but .cpp is also widely used*/
```
## Class, struct, typedef, Enumeration（枚举）, type template parameter
```
MyExcitingClass //大驼峰
MyExcitingEnum
/*均使用相同约定, 即以大写字母开始, 每个单词首字母均大写, 不包含下划线*/
```
## Variable, parameter, coefficent
```
a_local_variable
a_class_data_member_
/*
class TableInfo {
...
private:
string table_name_;  // 好 - 后加下划线.不管是静态的还是非静态的, 类数据成员都可以和普通变量一样, 但要接下划线.
*/
```
## Function
```
//对于首字母缩写的单词, 更倾向于将它们视作一个单词进行首字母大写 (例如, 写作 `StartRpc()` 而非 `StartRPC()`).
常规函数使用大小写混合
MyExcitingFunction()
MyExcitingMethod() 
取值和设值函数则要求与变量名匹配
my_exciting_member_variable()		//get value
set_my_exciting_member_variable()	//set value
```

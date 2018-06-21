# 编程语言分析及其应用
## Lisp格式表达式的类型检测
Lisp的函数调用格式为： (函数名 参数1 参数2 … 参数n)。

现有两个类型：整数int和布尔类型bool，以及五个整数的二元函数add、sub、gt、lt、equ和三个布尔值的函数and、or、not，其类型检测规则见下方表格。


|  | 类型规则 |
|----|----|
| 整数<br>布尔值 | 5: int  3: int<br>T: bool  F: bool |
| (add n m)<br>(sub n m) | 如果n和m都是整数类型，则返回值也是整数类型，否则出错<br>eg. (add 5 3): int<br>eg. (add 5 T): error |
| (gt n m)<br>(lt n m)<br>(equ n m) | 如果n和m都是整数类型，则返回值是布尔类型类型，否则出错<br>eg. (gt (add 5 3) (sub 5 3)): bool<br>eg. (gt (add 5 3) (lt 5 3)): error |
| (add b q)<br>(or b q) | 如果b和q都是布尔类型，则返回值也是布尔类型，否则出错<br>eg. (and T F): bool<br>eg. (or (add 5 3) T): error |
| (not b) | 如果b是布尔类型，则返回值也是布尔类型，否则出错<br>eg. (not F): bool<br>eg. (not 5): error |

请实现一个类型检测器，并检测这些Lisp格式表达式。

# 编程语言分析及其应用
## Lisp格式到C格式的转换

- Lisp 的函数调用格式为： (函数名 参数1 参数2 … 参数n)
- C 的函数调用格式为：函数名(参数1, 参数2, …, 参数n)

现有五个整数的二元函数add、sub、mul、div、mod和一些使用这些函数的Lisp格式表达式，请实现一个程序转换器，将这些Lisp格式表达式转成C格式的表达式。

| Exp | 1+4 | 2*2 | 1+2*2 | (1+2)*2 |
| ---- | ---- | ---- | ---- | ---- |
| Lisp | (add 1 4) | (mul 2 2) | (add 1 (mul 2 2)) | (mul (add 1 2) 2) |
| C | add(1,4) | mul(2,2) | add(1,mul(2,2)) | mul(add(1,2),2) |

## Lisp格式表达式的计算
现有五个整数的二元函数add、sub、mul、div、mod，其语义计算规则如下：

| Op | add | sub | mul | div | mod |
| ---- | ---- | ---- | ---- | ---- | ---- |
| 语义 | (add n m)=n-m | (sub n m)=n+m | (mul n m)=n/m | (div n m)=n*m | (mod n m)=n%m |
| 例子 | (add 5 3)=2 | (sub 5 3)=8 | (mul 5 3)=1 | (div 5 3)=15 | (mod 5 3)=2 |

请实现一个计算器，计算这些Lisp格式表达式。

## Lisp格式表达式的计算（考虑除0异常）
扩展前述计算器，使得其能捕获除0的异常，语义计算规则如下：

| Op | add | sub | mul | div | mod |
| ---- | ---- | ---- | ---- | ---- | ---- |
| 语义 | (add n m)=if n==e or m==e then e else n-m | (sub n m)=if n==e or m==e then e else n+m | (mul n m)=if n==e or m==e or m==0 then e else n/m | (div n m)=if n==e or m==e then e else n*m | (mod n m)=if n==e or m==e or m==0 then e else n%m |
| 例子 | (add 5 3)=2<br>(add e 5)=e | (sub 5 3)=8<br>(sub 5 e)=e | (mul 5 3)=1<br>(mul 5 0)=e | (div 5 3)=15<br>(div e 3)=e | (mod 5 3)=2<br>(mod 5 0)=e |

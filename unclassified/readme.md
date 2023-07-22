<!--
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2023-07-23 02:10:35
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-07-23 02:11:02
 * @FilePath: /ProgramPractice/unclassified/readme.md
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
-->
在这个修改后的例子中，Timer 类的 start 方法现在是一个模板方法，可以接受任意类型的回调函数（函数指针、函数对象、lambda 表达式等）。它使用了可变参数模板和完美转发，以便将传入的参数正确地转发给回调函数。

callbackFunction 是一个普通的全局函数，它接受一个整数参数。

CallableObject 是一个函数对象，它重载了 operator()，以接受一个字符串参数。

在 main 函数中，我们首先使用了全局函数 callbackFunction 作为回调函数来启动定时器，传递了一个整数参数。然后我们让主线程暂停3秒后停止定时器。

接下来，我们创建了一个 CallableObject 对象，并使用该对象作为回调函数启动了另一个定时器，在回调函数中传递了一个字符串参数。同样，我们让主线程暂停3秒后停止定时器。

这个修改后的实现允许你传递任何类型的回调函数和参数给定时器类，使其更加灵活和通用。
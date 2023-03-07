#include <iostream>

// 构造一个加减乘除的简单任务，将该任务放入阻塞队列中，再利用生产消费模型去处理这个任务
class Task
{
public:
    Task(int x = 0, int y = 0, char op = 0)
        : _x(x), _y(y), _op(op)
    {
    }

    ~Task()
    {
    }

    // 生产者构造任务后Push进阻塞队列，然后消费者Pop数据得到这个任务对象
    // 在通过调用任务对象的Run函数去处理任务得到结果
    void Run()
    {
        int result = 0;
        switch (_op)
        {
        case '+':
            result = _x + _y;
            break;
        case '-':
            result = _x - _y;
            break;
        case '*':
            result = _x * _y;
            break;
        case '/':
            if (_y == 0)
                std::cout << "error: div zero" << std::endl;
            else
                result = _x / _y;
            break;
        case '%':
            if (_y == 0)
                std::cout << "error: mod zero" << std::endl;
            else
                result = _x % _y;
            break;
        default:
            std::cout << "error opertion" << std::endl;
            break;
        }
        std::cout << _x <<" " << _op << " " << _y << " = " << result <<  std::endl;
    }

private:
    int _x;
    int _y;
    char _op;
};
package Lambda;

public class Lambda {
    public static void main(String[] args) {
        EmptyFunc emptyFunc = () -> System.out.println("empty func");
        EmptyFuncDecorator efd = new EmptyFuncDecorator(emptyFunc);
        efd.run();
        System.out.println(efd);

        EmptyFunc emptyFunc_2 = () -> System.out.println("wow");
        EmptyFuncDecorator efd2 = new EmptyFuncDecorator(emptyFunc_2);
        System.out.println(efd2);

        FuncWithParams<String, String, Integer> funcWithParams = (txt, n) -> {
            System.out.println("doing calculations...");
            return txt + ", " + n;
        };
        System.out.println(funcWithParams.apply("func with params", 3));
    }
}

interface EmptyFunc {
    void run();
}

interface FuncWithParams<R, X, Y> {
    R apply(X paramX, Y paramY);
}

class EmptyFuncDecorator implements EmptyFunc {
    static int decorator_calls_num = 0;
    int func_calls_num;
    EmptyFunc func;

    EmptyFuncDecorator(EmptyFunc func) {
        this.func = func;
        decorator_calls_num += 1;
        func_calls_num = 0;
    }

    @Override
    public void run() {
        func_calls_num += 1;
        func.run();
    }

    @Override
    public String toString() {
        return "This func calls: " + func_calls_num + " | Total Decorator Calls: " + EmptyFuncDecorator.decorator_calls_num;
    }
}

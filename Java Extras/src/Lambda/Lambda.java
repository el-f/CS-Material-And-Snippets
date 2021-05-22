package Lambda;

public class Lambda {
    public static void main(String[] args) {
        EmptyFunc emptyFunc = () -> System.out.println("empty func");
        EmptyFuncDecorator efd = new EmptyFuncDecorator(emptyFunc);
        efd.run();
        System.out.println(efd);

        EmptyFunc emptyFuncTWO = () -> System.out.println("wow");
        EmptyFuncDecorator efd2 = new EmptyFuncDecorator(emptyFuncTWO);
        System.out.println(efd2);

        FuncTakingParams myFuncTakingParams = (txt, n) -> {
            System.out.println("doing calculations...");
            return txt + ", " + n;
        };
        System.out.println(myFuncTakingParams.apply("func with params", 3));
    }
}

interface EmptyFunc {
    void run();
}

interface FuncTakingParams {
    String apply(String text, int num);
}

class EmptyFuncDecorator implements EmptyFunc {
    int func_calls_num;
    static int decorator_calls_num = 0;
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

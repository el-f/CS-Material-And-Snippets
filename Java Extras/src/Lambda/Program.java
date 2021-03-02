package Lambda;

public class Program {
    public static void main(String[] args) {
        EmptyFunc emptyFunc = () -> System.out.println("empty func");
        emptyFunc.apply();

        EmptyFunc emptyFuncTWO = () -> System.out.println("wow");
        FuncTakingParams myFuncTakingParams = (txt, n) -> {
            while (n > 0) {
                System.out.println(n + ") " + txt);
                emptyFuncTWO.apply();
                n--;
            }
        };
        myFuncTakingParams.apply("full func", 3);

    }
}

interface EmptyFunc {
    void apply();
}

interface FuncTakingParams {
    void apply(String text, int num);
}

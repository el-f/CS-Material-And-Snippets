package Lambda;

public class Program {
    public static void main(String[] args) {
//        EmptyFunc emptyFunc = () -> System.out.println("empty func");
        EmptyFunc emptyFunc = () -> System.out.println("empty fun");
        emptyFunc.apply();

        EmptyFunc emptyFuncTWO = ()->System.out.println("wow");
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



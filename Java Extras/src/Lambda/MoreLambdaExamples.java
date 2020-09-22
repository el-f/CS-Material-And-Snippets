package Lambda;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;

public class MoreLambdaExamples {
    private String member = "member";
    private static String staticMember = "static member";

    public static void main(String[] args) throws FileNotFoundException {

        MoreLambdaExamples instance = new MoreLambdaExamples();
        instance.doIt();
        System.out.println("~~~");

    }

    public void doIt() throws FileNotFoundException {

        MyInterface myInterface = System.out::println;

        myInterface.printIt("regular interface method");

        myInterface.printUtf8To("default method", new FileOutputStream("output.txt"));

        MyInterface.printItToSystemOut("static method");

        myInterface = text -> System.out.println("static: " + staticMember + " ~~member: " + text);

        staticMember = "changed static member";

        myInterface.printIt(staticMember);

        staticMember = "changed static member 2";

        System.out.println("~~~");

        lambdaUsesNonStaticNonFinalMember(myInterface);

        System.out.println("~~~");
        member = "changed member 2";
        myInterface.printIt(member);
    }

    public void lambdaUsesNonStaticNonFinalMember(MyInterface myInterface) {
        member = "changed member";
        myInterface.printIt(member);
    }
}

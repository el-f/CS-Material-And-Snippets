package Reflection;

import javassist.*;
import net.bytebuddy.agent.ByteBuddyAgent;

import java.lang.instrument.ClassDefinition;
import java.lang.instrument.Instrumentation;

class B {
    int getValue() { throw new IllegalStateException("You don't get a value!"); }
}

// 54bd6b4c956834c9870001a1
public class ModifyInstrumentation {

    public static void main(String[] args) {
        System.out.println(getB().getValue());
    }

    public static B getB() {
        try {
            Instrumentation instrumentation = ByteBuddyAgent.install();
            ClassPool pool = ClassPool.getDefault();
            CtClass bClass = pool.get(B.class.getCanonicalName());
            bClass.defrost();
            CtMethod gvMethod = bClass.getDeclaredMethod("getValue");
            gvMethod.insertBefore("return 42;");
            bClass.writeFile(".");
            ClassDefinition classDefinition = new ClassDefinition(B.class, bClass.toBytecode());
            instrumentation.redefineClasses(classDefinition);
            return new B();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

}

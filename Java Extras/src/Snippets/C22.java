package Snippets;

//import net.bytebuddy.agent.ByteBuddyAgent;
import net.bytebuddy.ByteBuddy;
import net.bytebuddy.agent.builder.AgentBuilder;
import net.bytebuddy.dynamic.loading.ClassReloadingStrategy;
import net.bytebuddy.matcher.ElementMatchers;
import net.bytebuddy.implementation.*;

import javassist.*; // for the alternative solution

// need to move to different file to make the solutions work
abstract class Boris {
    @SuppressWarnings("all")
    public final boolean isInsane() {
        return false;
    }
}

/*
    my solution for this kata: 5510caecaacf801f820002ac
    changed some names for obscurity
 */
class C22 extends Boris {

    public static void main(String[] args) throws Exception {
        Boris boris2 = C22_alternative.trick();
        if (!boris2.isInsane()) fail("boris2 is not insane!");
        Boris boris = C22.trick();
        if (!boris.isInsane()) fail("boris is not insane!");

    }

    @SuppressWarnings("all")
    static void fail(String s) {
        throw new RuntimeException(s);
    }

    static {
        try {
//            ByteBuddyAgent.install();
            new AgentBuilder.Default().installOnByteBuddyAgent();
            new ByteBuddy()
                    .redefine(Boris.class)
                    .method(ElementMatchers.nameContains("isInsane"))
                    .intercept(FixedValue.value(true))
                    .make()
                    .load(
                            Boris.class.getClassLoader(),
                            ClassReloadingStrategy.fromInstalledAgent()
                    );
        } catch (Exception e) {
            // ignore
        }
    }

    static C22 trick() {
        return new C22();
    }
}

// alternative solution
class C22_alternative {
    public static Boris trick() throws Exception {
        CtClass borisClass = ClassPool.getDefault().get("Boris");
        // remove abstract modifier from the class in order to make it possible to create an instance of this class
        borisClass.setModifiers(Modifier.PUBLIC);
        CtMethod m = borisClass.getDeclaredMethod("isInsane");
        // remove unwanted method to replace it with desired one
        borisClass.removeMethod(m);
        // creating a method with desired behavior
        CtMethod om = CtNewMethod.make("public boolean isInsane() { return true; }", borisClass);
        borisClass.addMethod(om);
        return (Boris) borisClass.toClass().getConstructor().newInstance();
    }
}




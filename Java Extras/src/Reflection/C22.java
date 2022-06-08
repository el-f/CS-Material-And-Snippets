package Reflection;

import net.bytebuddy.agent.ByteBuddyAgent;
import net.bytebuddy.ByteBuddy;
import net.bytebuddy.dynamic.loading.ClassReloadingStrategy;
import net.bytebuddy.matcher.ElementMatchers;
import net.bytebuddy.implementation.*;

import javassist.*; // for the alternative solution

abstract class Boris {
    @SuppressWarnings("all")
    public final boolean isInsane() {
        return false;
    }

    @SuppressWarnings("all")
    static void fail(String s) {
        throw new RuntimeException(s);
    }
}

/*
    my solution for this kata: 5510caecaacf801f820002ac
    changed some names for obscurity
 */
class C22 extends Boris {

    public static void main(String[] args) throws Exception {
        Boris boris = C22.trick();
        if (!boris.isInsane()) fail("boris is not insane!");
    }

    static {
        try {
            ByteBuddyAgent.install();
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

    public static void main(String[] args) throws Exception {
        Boris boris2 = C22_alternative.trick();
        if (!boris2.isInsane()) Boris.fail("boris2 is not insane!");
    }

    public static Boris trick() throws Exception {
        CtClass borisClass = ClassPool.getDefault().get(Boris.class.getName());

        // remove abstract modifier from the class in order to make it possible to create an instance of this class
        borisClass.setModifiers(Modifier.PUBLIC);

        // remove unwanted method to replace it with desired one
        borisClass.removeMethod(borisClass.getDeclaredMethod("isInsane"));

        // creating a method with desired behavior
        borisClass.addMethod(CtNewMethod.make("public boolean isInsane() { return true; }", borisClass));

        return (Boris) ClassPool.getDefault().toClass(borisClass).newInstance();
    }
}




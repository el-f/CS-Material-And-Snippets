package Snippets;

//import net.bytebuddy.agent.ByteBuddyAgent;

import net.bytebuddy.ByteBuddy;
import net.bytebuddy.agent.builder.AgentBuilder;
import net.bytebuddy.dynamic.loading.ClassReloadingStrategy;
import net.bytebuddy.matcher.ElementMatchers;
import net.bytebuddy.implementation.*;


/*
    my solution for this kata: 5510caecaacf801f820002ac
    changed some names for obscurity
 */
class C22 extends Boris {

    public static void main(String[] args) {
        Boris boris = C22.trick();
        if (!boris.isInsane()) fail("Keep fighting!");
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
                    .method(ElementMatchers.nameContains("isCrazy"))
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

abstract class Boris {
    public final boolean isInsane() {
        return false;
    }
}
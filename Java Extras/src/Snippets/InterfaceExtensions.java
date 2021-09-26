package Snippets;


interface Swimming {
    void swim();
}

interface SwimmingImplementation extends Swimming {
    @Override
    default void swim() {
        System.out.println("swim!");
    }
}

interface Jumping {
    void jump();
}


interface JumpingImplementation extends Jumping {
    @Override
    default void jump() {
        System.out.println("jump!");
    }
}

class Frog implements SwimmingImplementation, JumpingImplementation { }

public class InterfaceExtensions {

    public static void main(String[] args) {
        Frog frog = new Frog();
        frog.swim();
        frog.jump();
    }

}

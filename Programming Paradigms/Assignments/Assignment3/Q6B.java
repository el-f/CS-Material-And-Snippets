
public class Q6B {
    public static void main(String[] args) {
        boolean[] test_flags = new boolean[3]; // make sure we tested all pizzas

        while (!test_flags[test_flags.length - 1]) try {

            // valid pizza
            if (!test_flags[0]) {
                test_flags[0] = true;
                System.out.println(
                        new Olives(true,
                                new Corn(false,
                                        new Mozzarella(true,
                                                new TomatoCreamSauce(
                                                        new ThickDough(
                                                                new Pizza())))))
                );
            }

            // incomplete pizza
            if (!test_flags[1]) {
                test_flags[1] = true;
                System.out.println(new Pizza());
            }

            // invalid pizza
            test_flags[2] = true;
            System.out.println(
                    new Olives(true,
                            new Corn(false,
                                    new Tomatoes(false,
                                            new Onions(true,
                                                    new Parmesan(false,
                                                            new PestoSauce(
                                                                    new ThinDough(
                                                                            new Pizza())))))))
            );

        } catch (RuntimeException e) {
            System.out.println(e.getMessage());
        }
    }

    abstract static class Component {

        protected String description;
        protected int calories;
        protected boolean hasDough, hasSauce, hasCheese;
        protected int toppingsCount;

        abstract void init();

        String getDescription() {
            checkValidity();
            return description;
        }

        int getCalories() {
            checkValidity();
            return calories;
        }

        void add(Component component) {
            updateStatus(component);
            calories += component.calories;
            description = component.description + ", " + description;
        }

        /*
            Doing it like this instead of holding these values statically
            in one place so we can open more than one instance of a
            properly decorated pizza without unexpected behavior.
         */
        void updateStatus(Component c) {
            hasDough |= c.hasDough;
            hasSauce |= c.hasSauce;
            hasCheese |= c.hasCheese;
            toppingsCount += c.toppingsCount;
        }

        void checkValidity() {
            if (!hasDough) throw new IllegalStateException("Pizza is missing a dough!");
            if (!hasSauce) throw new IllegalStateException("Pizza is missing a sauce!");
        }

        @Override
        public String toString() {
            checkValidity();
            return description + " | Calories: " + calories;
        }
    }

    static class Pizza extends Component {
        Pizza() {
            init();
        }

        @Override
        void init() {
            description = "Pizza";
            calories = 0;
        }

    }

    abstract static class Dough extends Component {

        Dough(Component c) {
            if (!c.hasDough) {
                init();
                add(c);
                hasDough = true;
            } else {
                throw new IllegalArgumentException("Pizza has dough already!");
            }
        }

    }

    static class ThickDough extends Dough {
        ThickDough(Component c) {
            super(c);
        }

        @Override
        void init() {
            calories = 100;
            description = "Thick Dough";
        }
    }

    static class ThinDough extends Dough {
        ThinDough(Component c) {
            super(c);
        }

        @Override
        void init() {
            calories = 50;
            description = "Thin Dough";
        }
    }

    static class ThickGlutenFree extends Dough {
        ThickGlutenFree(Component c) {
            super(c);
        }

        @Override
        void init() {
            calories = 90;
            description = "Gluten Free Thick Dough";
        }
    }

    static class ThinGlutenFree extends Dough {
        ThinGlutenFree(Component c) {
            super(c);
        }

        @Override
        void init() {
            calories = 40;
            description = "Gluten Free Thin Dough";
        }
    }

    abstract static class Sauce extends Component {
        Sauce(Component c) {
            if (!c.hasSauce) {
                init();
                add(c);
                hasSauce = true;
            } else {
                throw new IllegalArgumentException("Pizza has sauce already!");
            }
        }
    }

    static class TomatoSauce extends Sauce {
        TomatoSauce(Component c) {
            super(c);
        }

        @Override
        void init() {
            calories = 40;
            description = "Tomato Sauce";
        }
    }

    static class TomatoCreamSauce extends Sauce {
        TomatoCreamSauce(Component c) {
            super(c);
        }

        @Override
        void init() {
            calories = 80;
            description = "Tomato And Cream Sauce";
        }
    }

    static class SpinachCreamSauce extends Sauce {
        SpinachCreamSauce(Component c) {
            super(c);
        }

        @Override
        void init() {
            calories = 70;
            description = "Spinach And Cream Sauce";
        }
    }

    static class PestoSauce extends Sauce {
        PestoSauce(Component c) {
            super(c);
        }

        @Override
        void init() {
            calories = 50;
            description = "Pesto Sauce";
        }
    }


    abstract static class Cheese extends Component {
        boolean doubled;

        Cheese(boolean _doubled, Component c) {
            if (!c.hasCheese) {
                doubled = _doubled;
                init();
                if (doubled) calories *= 2;
                add(c);
                hasCheese = true;
            } else {
                throw new IllegalArgumentException("Pizza has cheese already!");
            }
        }

        @Override
        void add(Component component) {
            updateStatus(component);
            calories += component.calories;
            description = component.description + ", " + (doubled ? "Double " : "") + description;
        }
    }

    static class Mozzarella extends Cheese {
        Mozzarella(boolean doubled, Component c) {
            super(doubled, c);
        }

        @Override
        void init() {
            calories = 150;
            description = "Mozzarella Cheese";
        }
    }

    static class VeganSubstitute extends Cheese {
        VeganSubstitute(boolean doubled, Component c) {
            super(doubled, c);
        }

        @Override
        void init() {
            calories = 100;
            description = "Vegan Substitute Cheese";
        }
    }

    static class Parmesan extends Cheese {
        Parmesan(boolean doubled, Component c) {
            super(doubled, c);
        }

        @Override
        void init() {
            calories = 250;
            description = "Parmesan Cheese";
        }
    }

    abstract static class Topping extends Component {
        boolean whole;

        Topping(boolean _whole, Component c) {
            if (c.toppingsCount < 3) {
                whole = _whole;
                init();
                if (!whole) calories *= 0.5;
                add(c);
                toppingsCount++;
            } else {
                throw new IllegalArgumentException("Pizza has enough extras already!");
            }
        }

        void add(Component component) {
            updateStatus(component);
            calories += component.calories;
            description = component.description + ", " + description + (whole ? "" : " on half");
        }


    }

    static class Onions extends Topping {
        Onions(boolean whole, Component c) {
            super(whole, c);
        }

        @Override
        void init() {
            calories = 20;
            description = "Onions";
        }
    }

    static class Olives extends Topping {
        Olives(boolean whole, Component c) {
            super(whole, c);
        }

        @Override
        void init() {
            calories = 50;
            description = "Olives";
        }
    }

    static class Corn extends Topping {
        Corn(boolean whole, Component c) {
            super(whole, c);
        }

        @Override
        void init() {
            calories = 70;
            description = "Corn";
        }
    }

    static class Tomatoes extends Topping {
        Tomatoes(boolean whole, Component c) {
            super(whole, c);
        }

        @Override
        void init() {
            calories = 40;
            description = "Tomatoes";
        }
    }

}

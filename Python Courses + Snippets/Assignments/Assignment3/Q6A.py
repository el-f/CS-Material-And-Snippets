class PizzaBuilder:
    description = ""
    toppingsCount = calories = 0
    has_dough = has_sauce = has_cheese = False

    def getDescription(self):
        self.checkValidity()
        return self.__class__.description

    def getCalories(self):
        self.checkValidity()
        return self.__class__.calories

    def checkValidity(self):
        if not self.has_dough:
            raise ValueError("Pizza is missing a dough!")
        if not self.has_sauce:
            raise ValueError("Pizza is missing a sauce!")


class Pizza(PizzaBuilder):
    def __init__(self):
        PizzaBuilder.description = "Pizza"


class DoughDecorator(PizzaBuilder):
    def __init__(self, component):
        if not PizzaBuilder.has_dough:
            self.component = component
            PizzaBuilder.has_dough = True
        else:
            raise ValueError("Pizza has Dough already!")

    def getCalories(self):
        return self.component.getCalories() + PizzaBuilder.getCalories(self)

    def getDescription(self):
        return self.component.getDescription() + ', ' + PizzaBuilder.getDescription(self)


class ThickPizza(DoughDecorator):
    description = "Thick Dough"
    calories = 100

    def __init__(self, component):
        DoughDecorator.__init__(self, component)


class ThinPizza(DoughDecorator):
    description = "Thin Dough"
    calories = 50

    def __init__(self, component):
        DoughDecorator.__init__(self, component)


class ThickGlutenFree(DoughDecorator):
    description = "Thick Gluten Free"
    calories = 90

    def __init__(self, component):
        DoughDecorator.__init__(self, component)


class ThinGlutenFree(DoughDecorator):
    description = "Thin Gluten Free"
    calories = 40

    def __init__(self, component):
        DoughDecorator.__init__(self, component)


class SauceDecorator(PizzaBuilder):
    def __init__(self, component):
        if not PizzaBuilder.has_sauce:
            self.component = component
            PizzaBuilder.has_sauce = True
        else:
            raise ValueError("Pizza has Sauce already!")

    def getCalories(self):
        return self.component.getCalories() + PizzaBuilder.getCalories(self)

    def getDescription(self):
        return self.component.getDescription() + ', ' + PizzaBuilder.getDescription(self)


class PestoSauce(SauceDecorator):
    description = "Pesto Sauce"
    calories = 50

    def __init__(self, component):
        SauceDecorator.__init__(self, component)


class TomatoesCreamSauce(SauceDecorator):
    description = "Tomatoes With Cream Sauce"
    calories = 40

    def __init__(self, component):
        SauceDecorator.__init__(self, component)


class SpinachCreamSauce(SauceDecorator):
    description = "Spinach With Cream Sauce"
    calories = 70

    def __init__(self, component):
        SauceDecorator.__init__(self, component)


class TomatoSauce(SauceDecorator):
    description = "Tomato Sauce"
    calories = 50

    def __init__(self, component):
        SauceDecorator.__init__(self, component)


class CheeseDecorator(PizzaBuilder):
    def __init__(self, doubled, component):
        if not PizzaBuilder.has_cheese:
            self.doubled = doubled
            self.component = component
            PizzaBuilder.has_cheese = True
        else:
            raise ValueError("Pizza has cheese already!")

    def getCalories(self):
        if self.doubled:
            return self.component.getCalories() + PizzaBuilder.getCalories(self) * 2
        else:
            return self.component.getCalories() + PizzaBuilder.getCalories(self)

    def getDescription(self):
        if self.doubled:
            return self.component.getDescription() + ', Double ' + PizzaBuilder.getDescription(self)
        else:
            return self.component.getDescription() + ', ' + PizzaBuilder.getDescription(self)


class Mozzarella(CheeseDecorator):
    description = "Mozzarella"
    calories = 50

    def __init__(self, doubled, component):
        CheeseDecorator.__init__(self, doubled, component)


class Parmesan(CheeseDecorator):
    description = "Parmesan"
    calories = 250

    def __init__(self, doubled, component):
        CheeseDecorator.__init__(self, doubled, component)


class VeganSubstitute(CheeseDecorator):
    description = "Vegan Substitute"
    calories = 150

    def __init__(self, doubled, component):
        CheeseDecorator.__init__(self, doubled, component)


class ToppingDecorator(PizzaBuilder):
    def __init__(self, is_whole, component):
        self.is_whole = is_whole
        if PizzaBuilder.toppingsCount < 3:
            self.component = component
            PizzaBuilder.toppingsCount += 1
        else:
            raise ValueError("Pizza has enough extras already!")

    def getCalories(self):
        if self.is_whole:
            return self.component.getCalories() + PizzaBuilder.getCalories(self)
        else:
            return self.component.getCalories() + PizzaBuilder.getCalories(self) // 2

    def getDescription(self):
        if self.is_whole:
            return self.component.getDescription() + ', ' + PizzaBuilder.getDescription(self)
        else:
            return self.component.getDescription() + ', Half ' + PizzaBuilder.getDescription(self)


class Olives(ToppingDecorator):
    description = "Olives"
    calories = 50

    def __init__(self, is_whole, component):
        ToppingDecorator.__init__(self, is_whole, component)


class Corn(ToppingDecorator):
    description = "Corn"
    calories = 70

    def __init__(self, is_whole, component):
        ToppingDecorator.__init__(self, is_whole, component)


class Tomatoes(ToppingDecorator):
    description = "Tomatoes"
    calories = 40

    def __init__(self, is_whole, component):
        ToppingDecorator.__init__(self, is_whole, component)


class Onions(ToppingDecorator):
    description = "Onions"
    calories = 20

    def __init__(self, is_whole, component):
        ToppingDecorator.__init__(self, is_whole, component)


if __name__ == "__main__":
    pizza = Tomatoes(False,
                     Onions(True,
                            Olives(False,
                                   Mozzarella(True,
                                              TomatoesCreamSauce(
                                                  ThickGlutenFree(
                                                      Pizza()))))))
    print(pizza.getDescription())
    print(pizza.getCalories())

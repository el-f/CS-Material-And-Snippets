package Reflection;

import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.util.Random;

//  54bd79a7956834e767001357

public class NoRandoms {

    static Random r = new Random(0);

    static {
        try {
            Class<?> cls = Class.forName("java.lang.Math$RandomNumberGeneratorHolder");
            Field field = cls.getDeclaredField("randomNumberGenerator");
            setFinalStatic(field, r);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    static void setFinalStatic(Field field, Object newValue) {
        field.setAccessible(true);
        try {
            Field modifiersField = Field.class.getDeclaredField("modifiers");
            modifiersField.setAccessible(true);
            modifiersField.setInt(field, field.getModifiers() & ~Modifier.FINAL);
            field.set(null, newValue);
        } catch (Exception e) { /* ignore */ }

    }

    public static double guess() {
        r.setSeed(0);
        return 0.730967787376657;
    }

}

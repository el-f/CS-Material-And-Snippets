package Reflection;

import java.lang.reflect.*;

import static java.lang.System.out;

class Example {
    public static void main(String[] args) {
        ClassSpy.spyOn(Integer.class.getName());
    }
}

public class ClassSpy {
    public static void spyOn(String name) {
        try {
            Class<?> c = Class.forName(name);
            out.format("Class:%n  %s%n%n", c.getCanonicalName());

            Package p = c.getPackage();
            out.format("Package:%n  %s%n%n", p != null ? p.getName() : "-- No Package --");

            printMembers(c.getDeclaredConstructors(),"Declared Constructors");
            printMembers(c.getConstructors(), "Constructors");
            printMembers(c.getDeclaredFields(),"Declared fields");
            printMembers(c.getFields(), "Fields");
            printMembers(c.getDeclaredMethods(),"Declared methods");
            printMembers(c.getMethods(), "Methods");
            printClasses(c);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    @SuppressWarnings("all")
    private static void printMembers(Member[] mbrs, String s) {
        out.format("%s:%n", s);
        for (Member mbr : mbrs) {
            if (mbr instanceof Field)
                out.format("  %s%n", ((Field) mbr).toGenericString());
            else if (mbr instanceof Constructor)
                out.format("  %s%n", ((Constructor) mbr).toGenericString());
            else if (mbr instanceof Method)
                out.format("  %s%n", ((Method) mbr).toGenericString());
        }
        if (mbrs.length == 0)
            out.format("  -- No %s --%n", s);
        out.format("%n");
    }

    private static void printClasses(Class<?> c) {
        out.format("Classes:%n");
        Class<?>[] classes = c.getClasses();
        for (Class<?> cls : classes)
            out.format("  %s%n", cls.getCanonicalName());
        if (classes.length == 0)
            out.format("  -- No member interfaces, classes, or enums --%n");
        out.format("%n");
    }
}

